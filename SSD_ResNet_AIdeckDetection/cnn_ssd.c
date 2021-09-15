/*
 * Copyright (C) 2017 GreenWaves Technologies
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 *
 */

#include "stdio.h"

/* PMSIS BSP includes */
#include "pmsis.h"
#include "Gap.h"
#include "bsp/display/ili9341.h"
#include "bsp/camera/himax.h"
#include "bsp/ram.h"
#include "bsp/ram/hyperram.h"

// Delete the following code to disable the camera and the wifi
// change 1 to 0 is not useful
// #define FROM_CAMERA 1
// #define USE_STREAMER 1

#if defined(USE_STREAMER)
#include "bsp/transport/nina_w10.h"
#include "tools/frame_streamer.h"
#endif /* USE_STREAMER */

// All includes for body detection
#include "setup.h"
#include "cnn_ssdKernels.h"
#include "SSDKernels.h"
#include "SSDParams.h"
#include "cnn_ssdInfo.h"

#if SILENT
#define PRINTF(...) ((void) 0)
#else
#define PRINTF printf
#endif

struct pi_device ili;
struct pi_device device;
static pi_buffer_t buffer;

//TODO: how what are these parameters
#define MOUNT           1
#define UNMOUNT         0
#define CID             0
#define SAVE_DET        1
#define TARGET_NUM      1

struct pi_device HyperRam;
static struct pi_hyperram_conf conf;

AT_HYPERFLASH_FS_EXT_ADDR_TYPE cnn_ssd_L3_Flash = 0;

#define FIX2FP(Val, Precision)    ((float) (Val) / (float) (1<<(Precision)))

#define INPUT_1_Q S0_Op_input_1_Q

// onnx 
// #define OUTPUT_1_Q S29_Op_output_1_Q
// #define OUTPUT_2_Q S33_Op_output_2_Q
// #define OUTPUT_3_Q S50_Op_output_3_Q
// #define OUTPUT_4_Q S54_Op_output_4_Q
// #define OUTPUT_5_Q S71_Op_output_5_Q
// #define OUTPUT_6_Q S75_Op_output_6_Q
// #define OUTPUT_7_Q S91_Op_output_7_Q
// #define OUTPUT_8_Q S95_Op_output_8_Q
// cnn_ssd
#define OUTPUT_1_Q S17_Op_output_1_Q
#define OUTPUT_2_Q S21_Op_output_2_Q
#define OUTPUT_3_Q S29_Op_output_3_Q
#define OUTPUT_4_Q S33_Op_output_4_Q
#define OUTPUT_5_Q S41_Op_output_5_Q
#define OUTPUT_6_Q S45_Op_output_6_Q
#define OUTPUT_7_Q S52_Op_output_7_Q
#define OUTPUT_8_Q S56_Op_output_8_Q



PI_L2 short int *tmp_buffer_classes, *tmp_buffer_boxes;

typedef short int MNIST_IMAGE_IN_T;

L2_MEM MNIST_IMAGE_IN_T *ImageIn;

extern PI_L2 Alps * anchor_layer_1;
extern PI_L2 Alps * anchor_layer_2;
extern PI_L2 Alps * anchor_layer_3;
extern PI_L2 Alps * anchor_layer_4;


short int * Output_1; 
short int * Output_2; 
short int * Output_3; 
short int * Output_4; 
short int * Output_5; 
short int * Output_6; 
short int * Output_7; 
short int * Output_8;

PI_L2 bboxs_t bbxs;

static  short int *out_buff;

static uint32_t idx=0;

unsigned int Wi = 324, Hi = 244;
unsigned int W = 160, H = 128;//nn related

void writeDetImg(unsigned char *ImageInChar, uint16_t Img_num, int16_t score){

    static char imgName[50];
    //Save Images to Local
    // sprintf(imgName, "../../../img_OUT_%ld_class%d.ppm", idx, outclass1);
    float score_fp = FIX2FP(score,15);
    sprintf(imgName, "../../../OUTPUT/ssd_resnet/%d_%f.ppm", Img_num, score_fp);
    printf("Dumping image %s\n", imgName);

    WriteImageToFile(imgName, W, H, ImageInChar);
    idx++;
}

#ifdef FROM_CAMERA
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
#endif

#if defined(USE_STREAMER)
//  Initialize structs and function for streamer through wifi
static pi_task_t task1;
static struct pi_device wifi;
static frame_streamer_t *streamer1;
static volatile int stream1_done;

static void streamer_handler(void *arg)
{
  *(int *)arg = 1;
  if (stream1_done) 
  {
  }
}

static int open_wifi(struct pi_device *device)
{
  struct pi_nina_w10_conf nina_conf;

  pi_nina_w10_conf_init(&nina_conf);

  nina_conf.ssid = "";
  nina_conf.passwd = "";
  nina_conf.ip_addr = "192.168.0.0";
  nina_conf.port = 5555;
  pi_open_from_conf(device, &nina_conf);
  if (pi_transport_open(device))
    return -1;

  return 0;
}

static frame_streamer_t *open_streamer(char *name)
{
  struct frame_streamer_conf frame_streamer_conf;

  frame_streamer_conf_init(&frame_streamer_conf);

  frame_streamer_conf.transport = &wifi;
  frame_streamer_conf.format = FRAME_STREAMER_FORMAT_JPEG;
  frame_streamer_conf.width = W;
  frame_streamer_conf.height = H;
  frame_streamer_conf.depth = 1;
  frame_streamer_conf.name = name;

  return frame_streamer_open(&frame_streamer_conf);
} /* USE_STREAMER */

#endif

void test_hyper_ram(short int *output, short W, short H, short num, short start_fp)
{
    printf("Start read output %d from hyper ram...\n", num);
    out_buff = (short int *) pmsis_l2_malloc(W*H*sizeof(short int)*(start_fp+1));
    int start_num = W*H*start_fp;
    if (out_buff == NULL)
    {
        printf("L2_buff alloc failed !\n");
        pmsis_exit(-1);
    }
    pi_ram_read(&HyperRam, output, out_buff, W*H*sizeof(short int)*(start_fp+1));
    printf("Read output done.\n");
    /* Verification. */
    for (uint32_t i=0; i<H; i++)
    {
        for (uint32_t j=0; j<W; j++)
        {
            printf("%d ", out_buff[i*W+j + start_num]);
        }
        printf("\n");
    }
    printf("\n");
    pmsis_l2_malloc_free(out_buff, W*H*sizeof(short int)*(start_fp+1));
}

void test_l2(short int *output, short W, short num)
{
    printf("Output %d:\n", num);
    for (uint32_t i=0; i<W; i++)
    {
        for (uint32_t j=0; j<W; j++)
        {
            printf("%d ", output[i*W+j]);
        }
        printf("\n");
    }
    printf("\n");
}

static int initSSD(){

    bbxs.bbs = pmsis_l2_malloc(sizeof(bbox_t)*MAX_BB);

    if(bbxs.bbs==NULL){
        printf("Bounding Boxes Allocation Error...\n");
        return 1;
    }

    bbxs.num_bb = 0;    

    initAnchorLayer_1();
    initAnchorLayer_2();
    initAnchorLayer_3();
    initAnchorLayer_4();

    return 0;

}


void convertCoordBboxes(bboxs_t *boundbxs,float scale_x,float scale_y){

    for (int counter=0;counter< boundbxs->num_bb;counter++){
        if(boundbxs->bbs[counter].alive==1){
            boundbxs->bbs[counter].x = (int)(FIX2FP(boundbxs->bbs[counter].x,20) * scale_x);
            boundbxs->bbs[counter].y = (int)(FIX2FP(boundbxs->bbs[counter].y,20) * scale_y);
            boundbxs->bbs[counter].w = (int)(FIX2FP(boundbxs->bbs[counter].w,26) * scale_x);
            boundbxs->bbs[counter].h = (int)(FIX2FP(boundbxs->bbs[counter].h,26) * scale_y);
            boundbxs->bbs[counter].x = boundbxs->bbs[counter].x - (boundbxs->bbs[counter].w/2);
            boundbxs->bbs[counter].y = boundbxs->bbs[counter].y - (boundbxs->bbs[counter].h/2);
        }
    }
}


void printBboxes(bboxs_t *boundbxs){
    PRINTF("\n\n======================================================");
    PRINTF("\nDetected Bounding boxes                                 ");
    PRINTF("\n======================================================\n");
    PRINTF("BoudingBox:  score     cx     cy     w     h    class");
    PRINTF("\n------------------------------------------------------\n");

    for (int counter=0;counter< boundbxs->num_bb;counter++){
        if(boundbxs->bbs[counter].alive)
            PRINTF("bbox [%02d] : %.5f     %03d    %03d     %03d    %03d     %02d\n",
                counter,
                FIX2FP(boundbxs->bbs[counter].score,15 ),
                boundbxs->bbs[counter].x,
                boundbxs->bbs[counter].y,
                boundbxs->bbs[counter].w,
                boundbxs->bbs[counter].h,
                boundbxs->bbs[counter].class);
    }//
}


void printBboxes_forPython(bboxs_t *boundbxs){
    PRINTF("\n\n======================================================");
    PRINTF("\nThis can be copy-pasted to python to draw BoudingBoxs   ");
    PRINTF("\n\n");

    for (int counter=0;counter< boundbxs->num_bb;counter++){
        if(boundbxs->bbs[counter].alive)
            PRINTF("rect = patches.Rectangle((%d,%d),%d,%d,linewidth=1,edgecolor='r',facecolor='none')\nax.add_patch(rect)\n",
                boundbxs->bbs[counter].x,
                boundbxs->bbs[counter].y,
                boundbxs->bbs[counter].w,
                boundbxs->bbs[counter].h);
    }//
}


int rect_intersect_area( short a_x, short a_y, short a_w, short a_h,
                         short b_x, short b_y, short b_w, short b_h ){

    #define MIN(a,b) ((a) < (b) ? (a) : (b))
    #define MAX(a,b) ((a) > (b) ? (a) : (b))

    int x = MAX(a_x,b_x);
    int y = MAX(a_y,b_y);

    int size_x = MIN(a_x+a_w,b_x+b_w) - x;
    int size_y = MIN(a_y+a_h,b_y+b_h) - y;

    if(size_x <=0 || size_x <=0)
        return 0;
    else
        return size_x*size_y; 

    #undef MAX
    #undef MIN
}


void non_max_suppress(bboxs_t * boundbxs){

    int idx,idx_int;

    //Non-max supression
     for(idx=0;idx<boundbxs->num_bb;idx++){
        //check if rect has been removed (-1)
        if(boundbxs->bbs[idx].alive==0)
            continue;
 
        for(idx_int=0;idx_int<boundbxs->num_bb;idx_int++){

            if(boundbxs->bbs[idx_int].alive==0 || idx_int==idx)
                continue;

            //check the intersection between rects
            int intersection = rect_intersect_area(boundbxs->bbs[idx].x,boundbxs->bbs[idx].y,boundbxs->bbs[idx].w,boundbxs->bbs[idx].h,
                                                   boundbxs->bbs[idx_int].x,boundbxs->bbs[idx_int].y,boundbxs->bbs[idx_int].w,boundbxs->bbs[idx_int].h);

            if(intersection >= NON_MAX_THRES){ //is non-max
                //supress the one that has lower score that is alway the internal index, since the input is sorted
                boundbxs->bbs[idx_int].alive =0;
            }
        }
    }

    // filter the boxes nums again
    for(idx=0;idx<boundbxs->num_bb;idx++){
        if(idx < TARGET_NUM)
        {
            boundbxs->bbs[idx].alive=1;
        }
        else
        {
            boundbxs->bbs[idx].alive=0;
        }
    }
}


static void RunNN()
{

    unsigned int ti,ti_nn,ti_ssd;

    gap_cl_starttimer();
    gap_cl_resethwtimer();
    ti = gap_cl_readhwtimer();

    cnn_ssdCNN(ImageIn, Output_1, Output_2, Output_3, Output_4, Output_5, Output_6, Output_7, Output_8);

    ti_nn = gap_cl_readhwtimer()-ti;
    PRINTF("Cycles NN : %10d\n",ti_nn);
    // test_l2(Output_3, 5, 3);
    // test_l2(Output_4, 5, 4);
    // test_l2(Output_5, 5, 5);
    // test_l2(Output_6, 5, 6);
    // test_l2(Output_7, 7, 7);
    // test_l2(Output_8, 7, 8);
    // test_hyper_ram();
}

    /////////////////////
    //SSD Code
    /////////////////////

static void RunSSD()
{

    unsigned int ti,ti_ssd;

    gap_cl_resethwtimer();
    ti = gap_cl_readhwtimer();

    //Set Boundinx Boxes to 0
    bbxs.num_bb = 0;
    for (int counter=0;counter< MAX_BB;counter++){
        bbxs.bbs[counter].alive==0;
    }

    SDD3Dto2DSoftmax_20_16_18(Output_1,tmp_buffer_classes,OUTPUT_1_Q,3);
    SDD3Dto2D_20_16_24(Output_2,tmp_buffer_boxes,0,0);
    Predecoder20_16(tmp_buffer_classes, tmp_buffer_boxes, anchor_layer_1, &bbxs,OUTPUT_2_Q);

    SDD3Dto2DSoftmax_10_8_18(Output_3,tmp_buffer_classes,OUTPUT_3_Q,3);
    SDD3Dto2D_10_8_24(Output_4,tmp_buffer_boxes,0,0);
    Predecoder10_8(tmp_buffer_classes, tmp_buffer_boxes, anchor_layer_2, &bbxs,OUTPUT_4_Q);

    SDD3Dto2DSoftmax_5_4_18(Output_5,tmp_buffer_classes,OUTPUT_5_Q,3);
    SDD3Dto2D_5_4_24(Output_6,tmp_buffer_boxes,0,0);
    Predecoder5_4(tmp_buffer_classes, tmp_buffer_boxes, anchor_layer_3,&bbxs,OUTPUT_6_Q);
    
    SDD3Dto2DSoftmax_2_2_18(Output_7,tmp_buffer_classes,OUTPUT_7_Q,3);
    SDD3Dto2D_2_2_24(Output_8,tmp_buffer_boxes,0,0);
    Predecoder2_2(tmp_buffer_classes, tmp_buffer_boxes, anchor_layer_4, &bbxs,OUTPUT_8_Q);



    bbox_t temp;

    int changed=0;
    do{
        changed=0;
        for(int i=0; i<bbxs.num_bb-1;i++){
            if(bbxs.bbs[i].score < bbxs.bbs[i+1].score){
                temp          = bbxs.bbs[i];
                bbxs.bbs[i]   = bbxs.bbs[i+1];
                bbxs.bbs[i+1] = temp;
                changed=1;
            }
        }
    }while(changed);

    convertCoordBboxes(&bbxs,160,128); 
    non_max_suppress(&bbxs);

    ti_ssd = gap_cl_readhwtimer()-ti;

    // printBboxes(&bbxs);
    // printBboxes_forPython(&bbxs);
    
    PRINTF("Cycles SSD: %10d\n",ti_ssd);

}

static int open_display(struct pi_device *device)
{
  struct pi_ili9341_conf ili_conf;

  pi_ili9341_conf_init(&ili_conf);

  pi_open_from_conf(device, &ili_conf);

  if (pi_display_open(device))
    return -1;

  if (pi_display_ioctl(device, PI_ILI_IOCTL_ORIENTATION, (void *)PI_ILI_ORIENTATION_180))
    return -1;

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

void drawBboxes(bboxs_t *boundbxs, uint8_t *img){

     for (int counter=0;counter< boundbxs->num_bb;counter++){
        if(boundbxs->bbs[counter].alive){
            DrawRectangle(img, H, W, boundbxs->bbs[counter].x, boundbxs->bbs[counter].y, boundbxs->bbs[counter].w, boundbxs->bbs[counter].h, 255);
        }
    }
}

int checkResults(bboxs_t *boundbxs){
    int totAliveBB=0;
    int x,y,w,h;

    for (int counter=0;counter< boundbxs->num_bb;counter++){
        if(boundbxs->bbs[counter].alive){
            totAliveBB++;
            x = boundbxs->bbs[counter].x;
            y = boundbxs->bbs[counter].y;
            w = boundbxs->bbs[counter].w;
            h = boundbxs->bbs[counter].h;
        }
    }

    //Cabled check of result (not nice but effective) with +/- 3 px tollerance
    if(totAliveBB!=1) return -1;
    if( x > 74 + 2 || x < 74 - 2 )         return -1;
    if( y > 28 + 2 || y < 28 - 2 )         return -1;
    if( w > 24 + 2 || w < 24 - 2 )         return -1;
    if( h > 71 + 2 || h < 71 - 2 )         return -1;

    return 0;

}

int start()
{

    char *ImageName;

    //Input image size
    int ret_state;

    PRINTF("Entering main controller\n");

    pi_freq_set(PI_FREQ_DOMAIN_FC,FREQ_FC*1000*1000);

#ifdef FROM_CAMERA

    unsigned char *ImageInChar = (unsigned char *) pmsis_l2_malloc( Wi * Hi * sizeof(unsigned char));
    if (ImageInChar == 0)
    {
        printf("Failed to allocate Memory for Image (%d bytes)\n", Wi * Hi * sizeof(MNIST_IMAGE_IN_T));
        pmsis_exit(-6);
    }
    ImageIn = (MNIST_IMAGE_IN_T *)ImageInChar;


    buffer.data = ImageInChar;
    buffer.stride = 0;

    // WIth Himax, propertly configure the buffer to skip boarder pixels
    pi_buffer_init(&buffer, PI_BUFFER_TYPE_L2, ImageInChar);
    pi_buffer_set_stride(&buffer, 0);
    pi_buffer_set_format(&buffer, W, H, 1, PI_BUFFER_FORMAT_GRAY);


    if (open_camera_himax(&device))
    {
        printf("Failed to open camera\n");
        pmsis_exit(-2);
    }

#else //reading image from host pc

    // sprintf(ImgName, "../../../OUTPUT/cnn_ssd_OUTPUT%ld.ppm", idx);
    // ImageName = "../../../test_samples/aideck_samples/converted/live_33.pgm";
    unsigned char *ImageInChar = (unsigned char *) pmsis_l2_malloc( W * H * sizeof(MNIST_IMAGE_IN_T));
    if (ImageInChar == 0)
    {
        printf("Failed to allocate Memory for Image (%d bytes)\n", W * H * sizeof(MNIST_IMAGE_IN_T));
        pmsis_exit(-6);
    }

    // //Reading Image from Bridge
    // PRINTF("Loading Image from File\n");
    // if ((ReadImageFromFile(ImageName, &Wi, &Hi, ImageInChar, W * H * sizeof(unsigned char)) == 0) || (Wi != W) || (Hi != H))
    // {
    //     printf("Failed to load image %s or dimension mismatch Expects [%dx%d], Got [%dx%d]\n", ImageName, W, H, Wi, Hi);
    //     pmsis_exit(-6);
    // }

    // ImageIn = (MNIST_IMAGE_IN_T *)ImageInChar;

    // for (int i = W * H - 1; i >= 0; i--)
    // {
    //     ImageIn[i] = (int16_t)ImageInChar[i] << INPUT_1_Q-8; //Input is naturally Q8
    // }

#endif

#if defined(USE_STREAMER)

    if (open_wifi(&wifi))
    {
        printf("Failed to open wifi\n");
        return -1;
    }
    printf("WIFI connected\n"); // check this with NINA printout

    streamer1 = open_streamer("cam");
    if (streamer1 == NULL)
        return -1;
    printf("Streamer set up\n");

#endif

    /* Init & open ram. */
    pi_hyperram_conf_init(&conf);
    pi_open_from_conf(&HyperRam, &conf);
    if (pi_ram_open(&HyperRam))
    {
        printf("Error ram open !\n");
        pmsis_exit(-5);
    }

    pi_ram_alloc(&HyperRam, &Output_1, 18 * 16* 20 * sizeof(short int));
    pi_ram_alloc(&HyperRam, &Output_2, 24 * 16* 20 * sizeof(short int));
    pi_ram_alloc(&HyperRam, &Output_3, 18 *  8* 10 * sizeof(short int));
    pi_ram_alloc(&HyperRam, &Output_4, 24 *  8* 10 * sizeof(short int));
    pi_ram_alloc(&HyperRam, &Output_5, 18 *  4*  5 * sizeof(short int));  
    pi_ram_alloc(&HyperRam, &Output_6, 24 *  4*  5 * sizeof(short int));
    pi_ram_alloc(&HyperRam, &Output_7, 18 *  2*  2 * sizeof(short int));
    pi_ram_alloc(&HyperRam, &Output_8, 24 *  2*  2 * sizeof(short int));

    // Output_3 = (short int *) pmsis_l2_malloc( 12 * 30 * 30 * sizeof(short int));

    pi_ram_alloc(&HyperRam, &tmp_buffer_classes, 18 * 16* 20   * sizeof(short int));
    pi_ram_alloc(&HyperRam, &tmp_buffer_boxes  , 24 * 16* 20   * sizeof(short int));

    if(Output_1==NULL || Output_2==NULL || Output_3==NULL || Output_4==NULL || Output_5==NULL || Output_6==NULL || Output_7==NULL || Output_8==NULL )
    {
        printf("Error Allocating OUTPUTs in L3\n");
        pmsis_exit(-7);
    }

    if(tmp_buffer_classes==NULL || tmp_buffer_classes==NULL)
    {
        printf("Error Allocating SSD Temp buffers in L3\n");
        pmsis_exit(-7);
    }

    #ifndef __EMUL__
    /* Configure And open cluster. */
    struct pi_device cluster_dev;
    struct pi_cluster_conf cl_conf;
    cl_conf.id = 0;
    pi_open_from_conf(&cluster_dev, (void *) &cl_conf);
    if (pi_cluster_open(&cluster_dev))
    {
        printf("Cluster open failed !\n");
        pmsis_exit(-7);
    }

    #endif

    if(initSSD())
    {
        printf("NN Init exited with an error\n");
        pmsis_exit(-6);
    }
    
    PRINTF("Running NN\n");

    struct pi_cluster_task *task = pmsis_l2_malloc(sizeof(struct pi_cluster_task));
    if(task==NULL) {
        printf("Alloc Error! \n");
        pmsis_exit(-5);
    }
    
    short iter=1;
    uint16_t count=0;
    uint16_t pic_num = 0;
    pi_freq_set(PI_FREQ_DOMAIN_CL,FREQ_CL*1000*1000);

    while(iter){

        #ifndef FROM_CAMERA
        
            switch (count)
            {
            case 0:
                pic_num = 21; ImageName = "../../../samples_ssd/21.pgm"; iter = 0; break;
            default:
                break;
            }
            count = count + 1;
            // sprintf(ImageName, "../../../test_samples/%d.pgm", pic_num);
            //Reading Image from Bridge
            PRINTF("Loading Image from File\n");
            if ((ReadImageFromFile(ImageName, &Wi, &Hi, ImageInChar, W * H * sizeof(unsigned char)) == 0) || (Wi != W) || (Hi != H))
            {
                printf("Failed to load image %s or dimension mismatch Expects [%dx%d], Got [%dx%d]\n", ImageName, W, H, Wi, Hi);
                pmsis_exit(-6);
            }

            ImageIn = (MNIST_IMAGE_IN_T *)ImageInChar;

            for (int i = W * H - 1; i >= 0; i--)
            {
                ImageIn[i] = (int16_t)ImageInChar[i] << INPUT_1_Q-8; //Input is naturally Q8
            }
        #else
            pi_camera_control(&device, PI_CAMERA_CMD_START, 0);
            pi_camera_capture(&device, ImageInChar, Wi*Hi);
            pi_camera_control(&device, PI_CAMERA_CMD_STOP, 0);
            int Xoffset = (Wi - W)/2;
            int Yoffset = (Hi - H)/2;
            for(int y=0;y<H;y++){
                for(int x=0;x<W;x++){
                    ImageIn[y*W+x] = ((short int)ImageInChar[((y+Yoffset)*Wi)+(x+Xoffset)]) << S0_Op_input_1_Q-8;
                }
            }
        #endif

        if (ret_state=cnn_ssdCNN_Construct())
        {
            printf("Graph constructor exited with an error code: %d\n",ret_state);
            pmsis_exit(-4);
        }

        memset(task, 0, sizeof(struct pi_cluster_task));
        task->entry = RunNN;
        task->arg = (void *) NULL;
        task->stack_size = (uint32_t) CLUSTER_STACK_SIZE;
        task->slave_stack_size = (uint32_t) CLUSTER_SLAVE_STACK_SIZE;
    
        pi_cluster_send_task_to_cl(&cluster_dev, task);
        #ifdef NN_PERF
        {
            unsigned int TotalCycles = 0, TotalOper = 0;
            printf("\n");
            for (int i=0; i<(sizeof(AT_GraphPerf)/sizeof(unsigned int)); i++) {
                printf("%45s: Cycles: %10d, Operations: %10d, Operations/Cycle: %f\n", AT_GraphNodeNames[i], AT_GraphPerf[i], AT_GraphOperInfosNames[i], ((float) AT_GraphOperInfosNames[i])/ AT_GraphPerf[i]);
                TotalCycles += AT_GraphPerf[i]; TotalOper += AT_GraphOperInfosNames[i];
            }
            printf("\n");
            printf("%45s: Cycles: %10d, Operations: %10d, Operations/Cycle: %f\n", "Total", TotalCycles, TotalOper, ((float) TotalOper)/ TotalCycles);
            printf("\n");
        }
        #endif  /* NN_PERF */

        cnn_ssdCNN_Destruct();

        // test_hyper_ram(Output_5, 5, 4, 5, 0);
        // test_hyper_ram(Output_5, 5, 4, 5, 1);
        // test_hyper_ram(Output_5, 5, 4, 5, 2);

        //SSD Allocations
        SSDKernels_L1_Memory = pmsis_l1_malloc(_SSDKernels_L1_Memory_SIZE);
        SSDKernels_L2_Memory = pmsis_l2_malloc(_SSDKernels_L2_Memory_SIZE);

        if(SSDKernels_L1_Memory==NULL || SSDKernels_L2_Memory==NULL)
        {
            printf("SSD L1 and/or L2 allocation error\n");
            pmsis_exit(-3);
        }


        memset(task, 0, sizeof(struct pi_cluster_task));
        task->entry = RunSSD;
        task->arg = (void *) NULL;
        task->stack_size = (uint32_t) CLUSTER_STACK_SIZE;
        task->slave_stack_size = (uint32_t) CLUSTER_SLAVE_STACK_SIZE;
        pi_cluster_send_task_to_cl(&cluster_dev, task);

        pmsis_l1_malloc_free(SSDKernels_L1_Memory,_SSDKernels_L1_Memory_SIZE);
        pmsis_l2_malloc_free(SSDKernels_L2_Memory,_SSDKernels_L2_Memory_SIZE);

        //Draw BBs
        // drawBboxes(&bbxs,ImageInChar);


        // #ifdef FROM_CAMERA
        for(int y=0;y<H;y++){
            for(int x=0;x<W;x++){
                ImageInChar[y*W+x] = (unsigned char)(ImageIn[(y*W)+(x)] >> INPUT_1_Q-8);
            }
        }
        //Draw BBs
        drawBboxes(&bbxs,ImageInChar);

        #if defined(USE_STREAMER)
        // Send image to the streamer to see the result
        frame_streamer_send_async(streamer1, &buffer, pi_task_callback(&task1, streamer_handler, (void *)&stream1_done));
        #endif

        #ifndef FROM_CAMERA
            if(SAVE_DET==1) writeDetImg(ImageInChar, pic_num, bbxs.bbs[0].score);
        #endif
        //Send to Screen
        // pi_display_write(&ili, &buffer, 40, 60, 160, 120);
        // #endif
    }

    pi_cluster_close(&cluster_dev);


    PRINTF("Ended\n");
    
    // if(checkResults(&bbxs)==0){
    //     printf("Correct results!\n");
    //     pmsis_exit(0);
    // }
    // else{
    //     printf("Wrong results!\n");
    //     pmsis_exit(-1);
    // }
    pmsis_exit(0);
    return 0;
}


int main(void)
{
  return pmsis_kickoff((void *) start);
}
