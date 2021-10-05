#include<stdio.h>

//include sdk head files
#include "Gap.h"
#include "pmsis.h"

#include "resnetKernels.h"
// #include "postproc.h"
// #include "ImgIO.h"
// #include "ImageDraw.h"
#include "resnetInfo.h"

#include "bsp/camera/himax.h"
#include "bsp/buffer.h"

#define FIX2FP(Val, Precision)    ((float) (Val) / (float) (1<<(Precision)))

#define INPUT_1_Q S0_Op_input_1_Q

#define NUM_CLASSES 	7

#define SAVE_DET 1

//Global defines
struct pi_device HyperRam;
struct pi_hyperram_conf hyper_conf;

struct pi_device uart_device;

struct pi_device cam_device;
static pi_buffer_t cam_buffer;


AT_HYPERFLASH_FS_EXT_ADDR_TYPE resnet_L3_Flash = 0;

L2_MEM short int *ImageIn;
short int * Output;
char model_name[] = "resnet.tflite";

static uint32_t idx=0;

unsigned int Wi = 324, Hi = 244;
unsigned int W = 160, H = 160;//nn related

void writeDetImg(unsigned char *ImageInChar, int outclass1){
    //write Detected Bbox to Image and save to imgName
    for(int y=0; y<H; y++)
    {
        for(int x=0;x<W;x++)
        {
            ImageInChar[y*W+x] = (unsigned char)(ImageIn[(y*W)+(x)] >> INPUT_1_Q-8);
        }
    }
    static char imgName[50];

    //Save Images to Local
    sprintf(imgName, "../../../OUTPUT/ssd_resnet/img_OUT_%ld_class%d_1.ppm", idx, outclass1);
    printf("Dumping image %s\n", imgName);

    WriteImageToFile(imgName, W, H, ImageInChar);
    idx++;
}
static void RunNN()
{
    printf("===RunNN===");
    unsigned int ti,ti_nn;
    gap_cl_starttimer();
    gap_cl_resethwtimer();
    ti = gap_cl_readhwtimer();

    resnetCNN(ImageIn, Output);
    ti_nn = gap_cl_readhwtimer()-ti;
    printf("Cycles NN : %10d\n",ti_nn);
}

static int open_camera_himax(struct pi_device *device)
{
  struct pi_himax_conf cam_conf;

  pi_himax_conf_init(&cam_conf);

  pi_open_from_conf(device, &cam_conf);
  if (pi_camera_open(device))
    return -1;

  // rotate image 180
  pi_camera_control(device, PI_CAMERA_CMD_START, 0);
  uint8_t set_value=3;
  uint8_t reg_value;
  pi_camera_reg_set(device, IMG_ORIENTATION, &set_value);
  pi_time_wait_us(1000000);
  pi_camera_reg_get(device, IMG_ORIENTATION, &reg_value);
  if (set_value!=reg_value)
  {
    printf("Failed to rotate camera image\n");
    return -1;
  }
  pi_camera_control(device, PI_CAMERA_CMD_STOP, 0);
  pi_camera_control(device, PI_CAMERA_CMD_AEG_INIT, 0);

  return 0;
}

static int open_uart(struct pi_device *uart_device1)
{
    struct pi_uart_conf uart_conf;

    pi_uart_conf_init(&uart_conf);
    uart_conf.baudrate_bps = 115200;
    //uart_conf.enable_tx = 1;
    //uart_conf.enable_rx = 0;

    pi_open_from_conf(&uart_device1, &uart_conf);
    if (pi_uart_open(&uart_device1))
       return -1;

    return 0;
}

int start()
{   //main app process
    //0. Voltage-Frequency settings
	uint32_t voltage =1200;
    static char dirction[15];
	pi_freq_set(PI_FREQ_DOMAIN_FC, FREQ_FC*1000*1000);
	pi_freq_set(PI_FREQ_DOMAIN_CL, FREQ_CL*1000*1000);
	//PMU_set_voltage(voltage, 0);
	printf("Set VDD voltage as %.2f, FC Frequency as %d MHz, CL Frequency = %d MHz\n", 
		(float)voltage/1000, FREQ_FC, FREQ_CL);
    
    //1. Initialize & open ram
  	pi_hyperram_conf_init(&hyper_conf);
    pi_open_from_conf(&HyperRam, &hyper_conf);
	if (pi_ram_open(&HyperRam))
	{
		printf("Error ram open !\n");
		pmsis_exit(-3);
	}
    printf("HyperRAM config done\n");

    //2. Allocate l2 for input image
    /*
    read image from camera or host pc
    allocate l2 input image
    */
    char *ImageName ="../../../test_samples/test01.pgm"; //main code inside BUILD/GAP_V3/GCC_RISCV


#ifdef FROM_CAMERA

    unsigned char *ImageInChar = (unsigned char *) pmsis_l2_malloc( Wi * Hi * sizeof(short int));
    if(ImageInChar==0)
    {
        printf("Failed to allocate Memory for Image (%d bytes)\n",W*H*sizeof(unsigned char));
        pmsis_exit(-6);
    }
    ImageIn = (short int *)ImageInChar;

    cam_buffer.data = ImageInChar;
    cam_buffer.stride = 0;

    pi_buffer_init(&cam_buffer, PI_BUFFER_TYPE_L2, ImageInChar);
    pi_buffer_set_stride(&cam_buffer, 0);
    pi_buffer_set_format(&cam_buffer, W, H, 1, PI_BUFFER_FORMAT_GRAY);

    if (open_camera_himax(&cam_device))
    {
        printf("Failed to open camera\n");
        pmsis_exit(-1);
    }

#else

    unsigned char *ImageInChar = (unsigned char *) pmsis_l2_malloc( W * H * sizeof(short int));
    if(ImageInChar==0)
    {
        printf("Failed to allocate Memory for Image (%d bytes)\n",W*H*sizeof(unsigned char));
        pmsis_exit(-6);
    }
    
    printf("Loading Image from File\n");

    if(ReadImageFromFile(ImageName, &Wi, &Hi, ImageInChar, W * H * sizeof(unsigned char))==0 ||(Wi!=W)||(Hi!=H))
    {
        printf("Failed to load image %s or dimension mismatch Expects [%dx%d], Got [%dx%d]\n", ImageName, W, H, Wi, Hi);
        pmsis_exit(-6);
    }
    ImageIn=(short int *)ImageInChar;
    // printf("===ImageIn sizeof(ImageIn)=%d\n",sizeof(ImageIn));
    
    for (int i = W * H - 1; i >= 0; i--)
    {
        ImageIn[i] = (int16_t)ImageInChar[i] << INPUT_1_Q-8; //Input is naturally Q8
    }
    // printf("===2ImageIn sizeof(ImageIn)=%d\n",sizeof(ImageIn));

#endif

    //3. Allocate output buffer
    printf("==output_size %d \n",NUM_CLASSES);
    Output = (short int *) pmsis_l2_malloc( NUM_CLASSES*sizeof(short int));
    if(Output==NULL)
    {
        printf("Error Allocating OUTPUTs in L2\n");
        pmsis_exit(-7);
    }
    printf("===output sizeof(Output)= %d\n",sizeof(Output));
    //4. Configure And open cluster.
    struct pi_device cluster_dev;
    struct pi_cluster_conf cl_conf;
    cl_conf.id = 0; //pi_cluster_conf_init(&conf);
    pi_open_from_conf(&cluster_dev, (void *) &cl_conf);
    if (pi_cluster_open(&cluster_dev))
    {
        printf("Cluster open failed !\n");
        pmsis_exit(-7);
    }

    printf("=== Network Constructor Network Constructor ===\n");
    //5. Network Constructor
	// IMPORTANT: MUST BE CALLED AFTER THE CLUSTER IS ON!
	int ret_state;
	if (ret_state= resnetCNN_Construct())
	{
	  printf("Graph constructor exited with error: %d\n", ret_state);
	  pmsis_exit(-4);
	}
	printf("Network Constructor was OK!\n");

    //6. Task setup
    struct pi_cluster_task *task = pmsis_l2_malloc(sizeof(struct pi_cluster_task));
    printf("3 \n");
    if(task==NULL) {
        printf("Alloc Error! \n");
        pmsis_exit(-5);
    }

    pi_freq_set(PI_FREQ_DOMAIN_CL,FREQ_CL*1000*1000);

    if (open_uart(&uart_device))
    {
        printf("Failed to open uart\n");
        pmsis_exit(-2);
    }
        
    pi_uart_open(&uart_device);

    int iter=1;
    while(iter)
    {
        printf("enter while, iter = %d.\n", iter);
        #ifndef FROM_CAMERA
            iter = 0;
        #else
            pi_camera_control(&cam_device, PI_CAMERA_CMD_START, 0);
            pi_camera_capture(&cam_device, ImageInChar, Wi*Hi);
            pi_camera_control(&cam_device, PI_CAMERA_CMD_STOP, 0);
            int Xoffset = (Wi - W)/2;
            int Yoffset = (Hi - H)/2;
            for(int y=0;y<H;y++)
            {
                for(int x=0;x<W;x++)
                {
                    ImageIn[y*W+x] = ((short int)ImageInChar[((y+Yoffset)*Wi)+(x+Xoffset)]) << INPUT_1_Q-8;
                }
            }
        #endif

        // printf("=== Task setup\n");
        memset(task, 0, sizeof(struct pi_cluster_task));
        task->entry = RunNN;
        task->arg = (void *) NULL;
        task->stack_size = (uint32_t) CLUSTER_STACK_SIZE;
        task->slave_stack_size = (uint32_t) CLUSTER_SLAVE_STACK_SIZE;
        //Dispatch task on cluster
        pi_cluster_send_task_to_cl(&cluster_dev, task);
        //Check Results
	    int outclass, MaxPrediction = 0;
	    for(int i=0; i<NUM_CLASSES; i++){
        printf("Class%d confidence:\t%d\n", i,Output[i]);
		if (Output[i] > MaxPrediction){
			outclass = i;
			MaxPrediction = Output[i];
		}
        }
        printf("\nModel:\t%s\n\n", model_name);
        switch(outclass)
        {
            case 0: strcpy(dirction,"backward");
            case 1: strcpy(dirction, "down");
            case 2: strcpy(dirction,"forward");
            case 3: strcpy(dirction,"left");
            case 4: strcpy(dirction,"right");
            case 5: strcpy(dirction,"up");
            case 6: strcpy(dirction,"no_gesture");
        }
	    printf("Predicted class:\t%d\n", outclass);
        printf("Predicted direction:\t%s\n", dirction);
	    printf("With confidence:\t%d\n", MaxPrediction);
        printf("=== Task ended \n ");
        #ifdef FROM_CAMERA
            // UART send data
            pi_uart_write(&uart_device, &outclass, 1);
            printf("uart write Value\n");
            iter--;
        #endif
        
        if(SAVE_DET==1) writeDetImg(ImageInChar, outclass);
        
    }
	
    //7. Netwrok Destructor and close cluster
	resnetCNN_Destruct();
    printf("=== CNN_Destruct\n");
    //8. postprocess
    //Draw BBs
    // drawBboxes(&bbxs,ImageInChar);

    //9. finally close cluster
	pi_cluster_close(&cluster_dev);
    printf("End \n");

    //check results, if not correct pmsis_exit(-1);
	pmsis_exit(0);


    return 0;
}



int main(void)
{
    printf("\n\n\t *** NN on GAP ***\n");
    return pmsis_kickoff((void *) start); //start app
}
