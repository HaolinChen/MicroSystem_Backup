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
#define FROM_CAMERA 1
// #define USE_STREAMER 1
#define MUTE 1
// #define TOTAL_CYCLE 1
// #define PERFORMANCE_DEBUG 1

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
// All includes for classification
#include "resnetKernels.h"
#include "resnetInfo.h"
#include "ResizeBasicKernels.h"

struct pi_device ili;
struct pi_device device;
static pi_buffer_t buffer;

//TODO: how what are these parameters
#define MOUNT 1
#define UNMOUNT 0
#define CID 0
#define SAVE_DET 1
#define SAVE_GESTURE_DET 0
// #define TARGET_NUM      2
#define RESIZE 1

#if MUTE
#define PRINTF(...) ((void)0)
#else
#define PRINTF printf
#endif

struct pi_device HyperRam;
static struct pi_hyperram_conf conf;

AT_HYPERFLASH_FS_EXT_ADDR_TYPE cnn_ssd_L3_Flash = 0;
AT_HYPERFLASH_FS_EXT_ADDR_TYPE resnet_L3_Flash = 0;

#define FIX2FP(Val, Precision) ((float)(Val) / (float)(1 << (Precision)))

// #define INPUT_1_Q S0_Op_input_1_Q
#define INPUT_1_Q 15

// cnn_ssd
#define OUTPUT_1_Q S17_Op_output_1_Q
#define OUTPUT_2_Q S21_Op_output_2_Q
#define OUTPUT_3_Q S29_Op_output_3_Q
#define OUTPUT_4_Q S33_Op_output_4_Q
#define OUTPUT_5_Q S40_Op_output_5_Q
#define OUTPUT_6_Q S44_Op_output_6_Q
// #define OUTPUT_7_Q S52_Op_output_7_Q
// #define OUTPUT_8_Q S56_Op_output_8_Q
// resnet
#define NUM_CLASSES 7

PI_L2 short int *tmp_buffer_classes, *tmp_buffer_boxes;

typedef short int IMAGE_IN_T;

L2_MEM IMAGE_IN_T *ImageIn;
L2_MEM short int *ImageIn_2;

extern PI_L2 Alps *anchor_layer_1;
extern PI_L2 Alps *anchor_layer_2;
extern PI_L2 Alps *anchor_layer_3;
// extern PI_L2 Alps *anchor_layer_4;

short int *Output_1;
short int *Output_2;
short int *Output_3;
short int *Output_4;
short int *Output_5;
short int *Output_6;
// short int *Output_7;
// short int *Output_8;
short int *Output;

PI_L2 bboxs_t bbxs;
static short int *out_buff;

static uint32_t pic_idx = 0;

unsigned int Wi = 324, Hi = 244;
// unsigned int Wi = 160, Hi = 128;
unsigned int W = 160, H = 128; //nn related
// resnet
unsigned int W_2 = 160, H_2 = 160; //nn related
uint16_t gesture_now = 0;
uint16_t pic_num = 59;
short GESTURE_FLAG = 0;

short max_person_id = 0;
short max_person_confidence = 0;
short max_gesture_id = 0;
short max_gesture_confidence = 0;
// short map0_used = 0;
// short map1_used = 0;
// short map2_used = 0;
// short map3_used = 0;

void writeDetImg(unsigned char *imageinchar, uint16_t Img_num, int16_t score)
{

    static char imgName[80];
    //Save Images to Local
    float score_fp = FIX2FP(score, 15);
    sprintf(imgName, "../../../OUTPUT/ssd_resnet_camera/optimization/gap8/num%d_score%f.ppm", Img_num, score_fp);
    PRINTF("Dumping image %s\n", imgName);

    WriteImageToFile(imgName, W, H, imageinchar);
}

void writeDetImg_resnet(unsigned char *imageinchar, uint16_t Img_num, int outclass1)
{
    //write Detected Bbox to Image and save to imgName
    static char imgName[80];

    //Save Images to Local
    sprintf(imgName, "../../../samples_codetest/gap8_gesture_prepare/pic_output/%d/num%ld_label%ld.pgm", gesture_now, Img_num, outclass1);
    PRINTF("Dumping image %s\n", imgName);

    WriteImageToFile(imgName, W_2, H_2, imageinchar);
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
    uint8_t set_value = 3;
    uint8_t reg_value;
    pi_camera_reg_set(device, IMG_ORIENTATION, &set_value);
    pi_time_wait_us(1000000);
    pi_camera_reg_get(device, IMG_ORIENTATION, &reg_value);
    if (set_value != reg_value)
    {
        PRINTF("Failed to rotate camera image\n");
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
    PRINTF("Start read output %d from hyper ram...\n", num);
    out_buff = (short int *)pmsis_l2_malloc(W * H * sizeof(short int) * (start_fp + 1));
    int start_num = W * H * start_fp;
    if (out_buff == NULL)
    {
        PRINTF("L2_buff alloc failed !\n");
        pmsis_exit(-1);
    }
    pi_ram_read(&HyperRam, output, out_buff, W * H * sizeof(short int) * (start_fp + 1));
    PRINTF("Read output done.\n");
    /* Verification. */
    for (uint32_t i = 0; i < H; i++)
    {
        for (uint32_t j = 0; j < W; j++)
        {
            PRINTF("%d ", out_buff[i * W + j + start_num]);
        }
        PRINTF("\n");
    }
    PRINTF("\n");
    pmsis_l2_malloc_free(out_buff, W * H * sizeof(short int) * (start_fp + 1));
}

void test_l2(short int *output, short W, short num)
{
    PRINTF("Output %d:\n", num);
    for (uint32_t i = 0; i < W; i++)
    {
        for (uint32_t j = 0; j < W; j++)
        {
            PRINTF("%d ", output[i * W + j]);
        }
        PRINTF("\n");
    }
    PRINTF("\n");
}

static int initSSD()
{

    bbxs.bbs = pmsis_l2_malloc(sizeof(bbox_t) * MAX_BB);

    if (bbxs.bbs == NULL)
    {
        PRINTF("Bounding Boxes Allocation Error...\n");
        return 1;
    }

    bbxs.num_bb = 0;

    initAnchorLayer_1();
    initAnchorLayer_2();
    initAnchorLayer_3();
    // initAnchorLayer_4();

    return 0;
}

void convertCoordBboxes(bboxs_t *boundbxs, float scale_x, float scale_y)
{

    for (int counter = 0; counter < boundbxs->num_bb; counter++)
    {
        if (boundbxs->bbs[counter].alive == 1)
        {
            boundbxs->bbs[counter].x = (int)(FIX2FP(boundbxs->bbs[counter].x, 20) * scale_x);
            boundbxs->bbs[counter].y = (int)(FIX2FP(boundbxs->bbs[counter].y, 20) * scale_y);
            boundbxs->bbs[counter].w = (int)(FIX2FP(boundbxs->bbs[counter].w, 26) * scale_x);
            boundbxs->bbs[counter].h = (int)(FIX2FP(boundbxs->bbs[counter].h, 26) * scale_y);
            boundbxs->bbs[counter].x = boundbxs->bbs[counter].x - (boundbxs->bbs[counter].w / 2);
            boundbxs->bbs[counter].y = boundbxs->bbs[counter].y - (boundbxs->bbs[counter].h / 2);
        }
    }
}

void printBboxes(bboxs_t *boundbxs)
{
    PRINTF("\n\n======================================================");
    PRINTF("\nDetected Bounding boxes                                 ");
    PRINTF("\n======================================================\n");
    PRINTF("BoudingBox:  score     cx     cy     w     h    class");
    PRINTF("\n------------------------------------------------------\n");

    for (int counter = 0; counter < boundbxs->num_bb; counter++)
    {
        if (boundbxs->bbs[counter].alive)
            PRINTF("bbox [%02d] : %.5f     %03d    %03d     %03d    %03d     %02d\n",
                   counter,
                   FIX2FP(boundbxs->bbs[counter].score, 15),
                   boundbxs->bbs[counter].x,
                   boundbxs->bbs[counter].y,
                   boundbxs->bbs[counter].w,
                   boundbxs->bbs[counter].h,
                   boundbxs->bbs[counter].class);
    } //
}

void printBboxes_forPython(bboxs_t *boundbxs)
{
    PRINTF("\n\n======================================================");
    PRINTF("\nThis can be copy-pasted to python to draw BoudingBoxs   ");
    PRINTF("\n\n");

    for (int counter = 0; counter < boundbxs->num_bb; counter++)
    {
        if (boundbxs->bbs[counter].alive)
            PRINTF("rect = patches.Rectangle((%d,%d),%d,%d,linewidth=1,edgecolor='r',facecolor='none')\nax.add_patch(rect)\n",
                   boundbxs->bbs[counter].x,
                   boundbxs->bbs[counter].y,
                   boundbxs->bbs[counter].w,
                   boundbxs->bbs[counter].h);
    } //
}

int rect_intersect_area(short a_x, short a_y, short a_w, short a_h,
                        short b_x, short b_y, short b_w, short b_h)
{

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

    int x = MAX(a_x, b_x);
    int y = MAX(a_y, b_y);

    int size_x = MIN(a_x + a_w, b_x + b_w) - x;
    int size_y = MIN(a_y + a_h, b_y + b_h) - y;

    if (size_x <= 0 || size_x <= 0)
        return 0;
    else
        return size_x * size_y;

#undef MAX
#undef MIN
}

void non_max_suppress(bboxs_t *boundbxs)
{

    int idx, idx_int;
    //Non-max supression
    // PRINTF("Box num: %d \n", boundbxs->num_bb);
    for (idx = 0; idx < boundbxs->num_bb; idx++)
    {
        //check if rect has been removed (-1)
        if (boundbxs->bbs[idx].alive == 0)
            continue;

        for (idx_int = 0; idx_int < boundbxs->num_bb; idx_int++)
        {
            if (boundbxs->bbs[idx_int].alive == 0 || idx_int == idx)
                continue;
            if (boundbxs->bbs[idx_int].class != boundbxs->bbs[idx].class)
                continue;

            //check the intersection between rects
            int intersection = rect_intersect_area(boundbxs->bbs[idx].x, boundbxs->bbs[idx].y, boundbxs->bbs[idx].w, boundbxs->bbs[idx].h,
                                                   boundbxs->bbs[idx_int].x, boundbxs->bbs[idx_int].y, boundbxs->bbs[idx_int].w, boundbxs->bbs[idx_int].h);

            if (intersection >= NON_MAX_THRES)
            { //is non-max
                //supress the one that has lower score that is alway the internal index, since the input is sorted
                boundbxs->bbs[idx_int].alive = 0;
            }
        }
    }
}

static void RunNN()
{

#ifndef TOTAL_CYCLE
    unsigned int ti, ti_nn;

    gap_cl_starttimer();
    gap_cl_resethwtimer();
    ti = gap_cl_readhwtimer();
#endif

    cnn_ssdCNN(ImageIn, Output_1, Output_2, Output_3, Output_4, Output_5, Output_6);
#ifndef TOTAL_CYCLE
    ti_nn = gap_cl_readhwtimer() - ti;
    PRINTF("Cycles NN : %10d\n", ti_nn);
#endif
    // test_l2(Output_3, 5, 3);
    // test_hyper_ram();
}

static void Resize(KerResizeBilinear_ArgT *KerArg)
{
    PRINTF("Resizing...\n");
    unsigned int ti, ti_nn;
#ifndef TOTAL_CYCLE
    gap_cl_starttimer();
    gap_cl_resethwtimer();
    ti = gap_cl_readhwtimer();
#endif
    AT_FORK(gap_ncore(), (void *)KerResizeBilinear, (void *)KerArg);
#ifndef TOTAL_CYCLE
    ti_nn = gap_cl_readhwtimer() - ti;
    PRINTF("Cycles resize : %10d\n", ti_nn);
#endif
}

static void RunRESNET()
{
    PRINTF("\n===RunResNet===\n");
#ifndef TOTAL_CYCLE
    unsigned int ti, ti_nn;
    gap_cl_starttimer();
    gap_cl_resethwtimer();
    ti = gap_cl_readhwtimer();
#endif
    resnetCNN(ImageIn_2, Output);
#ifndef TOTAL_CYCLE
    ti_nn = gap_cl_readhwtimer() - ti;
    PRINTF("Cycles NN : %10d\n", ti_nn);
#endif
}

/////////////////////
//SSD Code
/////////////////////

static void RunSSD()
{

#ifndef TOTAL_CYCLE
    unsigned int ti, ti_ssd;
    gap_cl_resethwtimer();
    ti = gap_cl_readhwtimer();
#endif

    //Set Boundinx Boxes to 0
    bbxs.num_bb = 0;
    for (int counter = 0; counter < MAX_BB; counter++)
    {
        bbxs.bbs[counter].alive == 0;
    }
    short box_num = 0;

    SDD3Dto2DSoftmax_20_16_18(Output_1, tmp_buffer_classes, OUTPUT_1_Q, 3);
    SDD3Dto2D_20_16_24(Output_2, tmp_buffer_boxes, 0, 0);
    Predecoder20_16(tmp_buffer_classes, tmp_buffer_boxes, anchor_layer_1, &bbxs, OUTPUT_2_Q);

    // if (bbxs.num_bb != box_num)
    // {
    //     box_num = bbxs.num_bb;
    //     map0_used++;
    // }

    SDD3Dto2DSoftmax_10_8_18(Output_3, tmp_buffer_classes, OUTPUT_3_Q, 3);
    SDD3Dto2D_10_8_24(Output_4, tmp_buffer_boxes, 0, 0);
    Predecoder10_8(tmp_buffer_classes, tmp_buffer_boxes, anchor_layer_2, &bbxs, OUTPUT_4_Q);

    SDD3Dto2DSoftmax_5_4_18(Output_5, tmp_buffer_classes, OUTPUT_5_Q, 3);
    SDD3Dto2D_5_4_24(Output_6, tmp_buffer_boxes, 0, 0);
    Predecoder5_4(tmp_buffer_classes, tmp_buffer_boxes, anchor_layer_3, &bbxs, OUTPUT_6_Q);

    // SDD3Dto2DSoftmax_2_2_18(Output_7, tmp_buffer_classes, OUTPUT_7_Q, 3);
    // SDD3Dto2D_2_2_24(Output_8, tmp_buffer_boxes, 0, 0);
    // Predecoder2_2(tmp_buffer_classes, tmp_buffer_boxes, anchor_layer_4, &bbxs, OUTPUT_8_Q);

    // bbox_t temp;

    // int changed = 0;
    // do
    // {
    //     changed = 0;
    //     for (int i = 0; i < bbxs.num_bb - 1; i++)
    //     {
    //         if (bbxs.bbs[i].score < bbxs.bbs[i + 1].score)
    //         {
    //             temp = bbxs.bbs[i];
    //             bbxs.bbs[i] = bbxs.bbs[i + 1];
    //             bbxs.bbs[i + 1] = temp;
    //             changed = 1;
    //         }
    //     }
    // } while (changed);

    // printBboxes(&bbxs);

    for (int i = 0; i < bbxs.num_bb; i++)
    {
        if (bbxs.bbs[i].class == 1 && max_person_confidence < bbxs.bbs[i].score)
        {
            max_person_confidence = bbxs.bbs[i].score;
            max_person_id = i;
        }
        else if (bbxs.bbs[i].class == 2 && max_gesture_confidence < bbxs.bbs[i].score)
        {

            max_gesture_confidence = bbxs.bbs[i].score;
            max_gesture_id = i;
        }
        bbxs.bbs[i].alive = 0;
    }
    if (max_person_confidence != 0)
    {
        bbxs.bbs[max_person_id].alive = 1;
    }
    if (max_gesture_confidence != 0)
    {
        bbxs.bbs[max_gesture_id].alive = 1;
    }

    convertCoordBboxes(&bbxs, 160, 128);
    // printBboxes(&bbxs);
    // non_max_suppress(&bbxs);
    // printBboxes_forPython(&bbxs);
#ifndef TOTAL_CYCLE
    ti_ssd = gap_cl_readhwtimer() - ti;
    PRINTF("Cycles SSD: %10d\n", ti_ssd);
#endif
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

void drawBboxes(bboxs_t *boundbxs, uint8_t *img)
{

    for (int counter = 0; counter < boundbxs->num_bb; counter++)
    {
        if (boundbxs->bbs[counter].alive)
        {
            DrawRectangle(img, H, W, boundbxs->bbs[counter].x - 1, boundbxs->bbs[counter].y - 1, boundbxs->bbs[counter].w + 2, boundbxs->bbs[counter].h + 2, 255);
        }
    }
}

void cropTargets(bboxs_t *boundbxs, int box_number, unsigned char *img_in, unsigned char *img_out)
{

    int crop_X1 = (W_2 - boundbxs->bbs[box_number].w) / 2;
    int crop_X2 = (W_2 + boundbxs->bbs[box_number].w) / 2;
    int crop_Y1 = (H_2 - boundbxs->bbs[box_number].h) / 2;
    int crop_Y2 = (H_2 + boundbxs->bbs[box_number].h) / 2;
    for (int y = 0; y < H_2; y++)
    {
        for (int x = 0; x < W_2; x++)
        {
            if (y >= crop_Y1 && y <= crop_Y2 && x >= crop_X1 && x <= crop_X2)
            {
                img_out[y * W_2 + x] = img_in[(y - crop_Y1 + boundbxs->bbs[box_number].y) * W + (x - crop_X1 + boundbxs->bbs[box_number].x)];
            }
            else
            {
                img_out[y * W_2 + x] = 128;
            }
        }
    }
}

int start()
{

    char ImageName[80];

    int ret_state;
    int ret_state_2;

    static char dirction[15];

    PRINTF("Entering main controller\n");

    pi_freq_set(PI_FREQ_DOMAIN_FC, FREQ_FC * 1000 * 1000);
    pi_freq_set(PI_FREQ_DOMAIN_CL, FREQ_CL * 1000 * 1000);

#ifdef FROM_CAMERA

    // unsigned char *ImageInChar = (unsigned char *) pmsis_l2_malloc( Wi * Hi * sizeof(unsigned char));
    // if (ImageInChar == 0)
    // {
    //     PRINTF("Failed to allocate Memory for Image (%d bytes)\n", Wi * Hi * sizeof(IMAGE_IN_T));
    //     pmsis_exit(-6);
    // }
    // ImageIn = (IMAGE_IN_T *)ImageInChar;

    // buffer.data = ImageInChar;
    // buffer.stride = 0;

    // // WIth Himax, propertly configure the buffer to skip boarder pixels
    // pi_buffer_init(&buffer, PI_BUFFER_TYPE_L2, ImageInChar);
    // pi_buffer_set_stride(&buffer, 0);
    // pi_buffer_set_format(&buffer, W, H, 1, PI_BUFFER_FORMAT_GRAY);

    if (open_camera_himax(&device))
    {
        PRINTF("Failed to open camera\n");
        pmsis_exit(-2);
    }

#else //reading image from host pc

    // unsigned char *ImageInChar = (unsigned char *) pmsis_l2_malloc( W * H * sizeof(unsigned char));
    // unsigned char *ImageInChar_2 = (unsigned char *) pmsis_l2_malloc( W_2 * H_2 * sizeof(unsigned char));
    // if (ImageInChar == 0 || ImageInChar_2 == 0)
    // {
    //     PRINTF("Failed to allocate Memory for Image (%d bytes)\n", W * H * sizeof(IMAGE_IN_T));
    //     pmsis_exit(-6);
    // }

#endif

#if defined(USE_STREAMER)

    if (open_wifi(&wifi))
    {
        PRINTF("Failed to open wifi\n");
        return -1;
    }
    PRINTF("WIFI connected\n"); // check this with NINA printout

    streamer1 = open_streamer("cam");
    if (streamer1 == NULL)
        return -1;
    PRINTF("Streamer set up\n");

#endif

    /* Init & open ram. */
    pi_hyperram_conf_init(&conf);
    pi_open_from_conf(&HyperRam, &conf);
    if (pi_ram_open(&HyperRam))
    {
        PRINTF("Error ram open !\n");
        pmsis_exit(-5);
    }

    pi_ram_alloc(&HyperRam, &Output_1, 18 * 16 * 20 * sizeof(short int));
    pi_ram_alloc(&HyperRam, &Output_2, 24 * 16 * 20 * sizeof(short int));
    pi_ram_alloc(&HyperRam, &Output_3, 18 * 8 * 10 * sizeof(short int));
    pi_ram_alloc(&HyperRam, &Output_4, 24 * 8 * 10 * sizeof(short int));
    pi_ram_alloc(&HyperRam, &Output_5, 18 * 4 * 5 * sizeof(short int));
    pi_ram_alloc(&HyperRam, &Output_6, 24 * 4 * 5 * sizeof(short int));
    // pi_ram_alloc(&HyperRam, &Output_7, 18 * 2 * 2 * sizeof(short int));
    // pi_ram_alloc(&HyperRam, &Output_8, 24 * 2 * 2 * sizeof(short int));

    // Output_3 = (short int *) pmsis_l2_malloc( 12 * 30 * 30 * sizeof(short int));

    pi_ram_alloc(&HyperRam, &tmp_buffer_classes, 18 * 16 * 20 * sizeof(short int));
    pi_ram_alloc(&HyperRam, &tmp_buffer_boxes, 24 * 16 * 20 * sizeof(short int));

    if (Output_1 == NULL || Output_2 == NULL || Output_3 == NULL || Output_4 == NULL || Output_5 == NULL || Output_6 == NULL)
    {
        PRINTF("Error Allocating OUTPUTs in L3\n");
        pmsis_exit(-7);
    }

    if (tmp_buffer_classes == NULL || tmp_buffer_classes == NULL)
    {
        PRINTF("Error Allocating SSD Temp buffers in L3\n");
        pmsis_exit(-7);
    }

    Output = (short int *)pmsis_l2_malloc(NUM_CLASSES * sizeof(short int));
    if (Output == NULL)
    {
        PRINTF("Error Allocating OUTPUTs in L2\n");
        pmsis_exit(-7);
    }

    /* Configure And open cluster. */
    struct pi_device cluster_dev;
    struct pi_cluster_conf cl_conf;
    cl_conf.id = 0;
    pi_open_from_conf(&cluster_dev, (void *)&cl_conf);
    if (pi_cluster_open(&cluster_dev))
    {
        PRINTF("Cluster open failed !\n");
        pmsis_exit(-7);
    }

    PRINTF("================ Memory Alocate=================\n");

    if (initSSD())
    {
        PRINTF("NN Init exited with an error\n");
        pmsis_exit(-6);
    }

    struct pi_cluster_task *task = pmsis_l2_malloc(sizeof(struct pi_cluster_task));
    struct pi_cluster_task *task_resnet = pmsis_l2_malloc(sizeof(struct pi_cluster_task));
    if (task == NULL || task_resnet == NULL)
    {
        PRINTF("Alloc Error! \n");
        pmsis_exit(-5);
    }

    unsigned char *ImageInChar = (unsigned char *)pmsis_l2_malloc(W * H * sizeof(short int));
    unsigned char *ImageInCamera = (unsigned char *)pmsis_l2_malloc(Wi * Hi * sizeof(unsigned char));

    //SSD Allocations
    SSDKernels_L1_Memory = pmsis_l1_malloc(_SSDKernels_L1_Memory_SIZE);
    SSDKernels_L2_Memory = pmsis_l2_malloc(_SSDKernels_L2_Memory_SIZE);

    if (SSDKernels_L1_Memory == NULL || SSDKernels_L2_Memory == NULL)
    {
        PRINTF("SSD L1 and/or L2 allocation error\n");
        pmsis_exit(-3);
    }

    if (ret_state_2 = resnetCNN_Construct())
    {
        PRINTF("Graph constructor exited with error: %d\n", ret_state_2);
        pmsis_exit(-4);
    }
    PRINTF("ResNet Constructor was OK!\n");

    if (ret_state = cnn_ssdCNN_Construct())
    {
        PRINTF("Graph constructor exited with an error code: %d\n", ret_state);
        pmsis_exit(-4);
    }
    PRINTF("CNN_SSD Constructor was OK!\n");

    short iter = 1;
    uint16_t count = 0;

#ifdef PERFORMANCE_DEBUG
    float detect_count = 0;
    float right_count = 0;
    float detect_rate = 0.0;
    float right_rate = 0.0;
#endif

    while (iter)
    {

#ifndef FROM_CAMERA

        sprintf(ImageName, "../../../samples_codetest/gap8_gesture_prepare/pic_input/%d/label%ld_num%ld.pgm", gesture_now, gesture_now, count);
        //Reading Image from Bridge
        PRINTF("\n\n******************CYCLE START******************\n\n\n");
        PRINTF("Loading Image from File\n");
        if ((ReadImageFromFile(ImageName, &Wi, &Hi, ImageInCamera, Wi * Hi * sizeof(unsigned char)) == 0) || (Wi != Wi) || (Hi != Hi))
        {
            PRINTF("Failed to load image %s or dimension mismatch Expects [%dx%d], Got [%dx%d]\n", ImageName, W, H, Wi, Hi);
            pmsis_exit(-6);
        }

#ifdef TOTAL_CYCLE
        unsigned int t_start, t_end;
        gap_cl_starttimer();
        gap_cl_resethwtimer();
        t_start = gap_cl_readhwtimer();
#endif

        //Resize Targets
        PRINTF("\n-------- STRAT RESIZE ORIGINAL PICTURE ----------\n");
        memset(task, 0, sizeof(struct pi_cluster_task));
        task->entry = &Resize;
        task->stack_size = (uint32_t)CLUSTER_STACK_SIZE;
        task->slave_stack_size = (uint32_t)CLUSTER_SLAVE_STACK_SIZE;

        KerResizeBilinear_ArgT ResizeArg;
        ResizeArg.In = ImageInCamera;
        ResizeArg.Win = Wi;
        ResizeArg.Hin = Hi;
        ResizeArg.Out = ImageInChar;
        ResizeArg.Wout = W;
        ResizeArg.Hout = H;
        ResizeArg.HTileOut = H;
        ResizeArg.FirstLineIndex = 0;
        task->arg = &ResizeArg;
        pi_cluster_send_task_to_cl(&cluster_dev, task);
        // pmsis_l2_malloc_free(ImageInCamera, Wi * Hi * sizeof(unsigned char));

        ImageIn = (IMAGE_IN_T *)ImageInChar;
        for (int i = W * H - 1; i >= 0; i--)
        {
            ImageIn[i] = (int16_t)ImageInChar[i] << INPUT_1_Q - 8; //Input is naturally Q8
        }
#else

#ifdef TOTAL_CYCLE
        unsigned int t_start, t_end;
        gap_cl_starttimer();
        gap_cl_resethwtimer();
        t_start = gap_cl_readhwtimer();
#endif
        pic_num++;
        ImageIn = (IMAGE_IN_T *)ImageInChar;
        pi_camera_control(&device, PI_CAMERA_CMD_START, 0);
        pi_camera_capture(&device, ImageInCamera, Wi * Hi);
        pi_camera_control(&device, PI_CAMERA_CMD_STOP, 0);
        //Resize Targets
        PRINTF("\n-------- STRAT RESIZE ORIGINAL PICTURE ----------\n");
        memset(task, 0, sizeof(struct pi_cluster_task));
        task->entry = &Resize;
        task->stack_size = (uint32_t)CLUSTER_STACK_SIZE;
        task->slave_stack_size = (uint32_t)CLUSTER_SLAVE_STACK_SIZE;

        KerResizeBilinear_ArgT ResizeArg;
        ResizeArg.In = ImageInCamera;
        ResizeArg.Win = Wi;
        ResizeArg.Hin = Hi;
        ResizeArg.Out = ImageInChar;
        ResizeArg.Wout = W;
        ResizeArg.Hout = H;
        ResizeArg.HTileOut = H;
        ResizeArg.FirstLineIndex = 0;
        task->arg = &ResizeArg;
        pi_cluster_send_task_to_cl(&cluster_dev, task);
        for (int i = W * H - 1; i >= 0; i--)
        {
            ImageIn[i] = (int16_t)ImageInChar[i] << INPUT_1_Q - 8; //Input is naturally Q8
        }
#endif

        PRINTF("\n-------- STRAT RUN CNN_SSD ----------\n");

        memset(task, 0, sizeof(struct pi_cluster_task));
        task->entry = RunNN;
        task->arg = (void *)NULL;
        task->stack_size = (uint32_t)CLUSTER_STACK_SIZE;
        task->slave_stack_size = (uint32_t)CLUSTER_SLAVE_STACK_SIZE;

        pi_cluster_send_task_to_cl(&cluster_dev, task);

        // test_hyper_ram(Output_5, 5, 4, 5, 0);

        memset(task, 0, sizeof(struct pi_cluster_task));
        task->entry = RunSSD;
        task->arg = (void *)NULL;
        task->stack_size = (uint32_t)CLUSTER_STACK_SIZE;
        task->slave_stack_size = (uint32_t)CLUSTER_SLAVE_STACK_SIZE;
        pi_cluster_send_task_to_cl(&cluster_dev, task);

        for (int y = 0; y < H; y++)
        {
            for (int x = 0; x < W; x++)
            {
                ImageInChar[y * W + x] = (unsigned char)(ImageIn[(y * W) + (x)] >> INPUT_1_Q - 8);
            }
        }

        int box_num = 0;
        //-------------Start Draw BBs-------------------//
        if (SAVE_DET == 1)
        {
            // while ((bbxs.bbs[box_num].alive == 0 || bbxs.bbs[box_num].class != 2) && box_num < bbxs.num_bb) //Only want person confidence
            // {
            //     box_num++;
            // }
            if (bbxs.bbs[max_person_id].alive != 0)
            {
                box_num = max_person_id;
            }
            drawBboxes(&bbxs, ImageInChar);
            writeDetImg(ImageInChar, count, bbxs.bbs[box_num].score);
        }
        //-------------End Draw BBs-------------------//

        box_num = 0;
        // while ((bbxs.bbs[box_num].alive == 0 || bbxs.bbs[box_num].class != 2) && box_num < bbxs.num_bb) //Only want gesture box
        // {
        //     box_num++;
        // }
        // if (box_num < bbxs.num_bb)
        // {
        //     GESTURE_FLAG = 1;
        // }
        if (max_gesture_confidence != 0)
        {
            GESTURE_FLAG = 1;
            box_num = max_gesture_id;
        }

        if (GESTURE_FLAG == 0)
        {
#ifdef TOTAL_CYCLE
            t_end = gap_cl_readhwtimer() - t_start;
            printf("Cycles total from PC: %15d\n", t_end);
            printf("SSD gesture: 0\n");
#endif
        }
        else
        {
#ifdef PERFORMANCE_DEBUG
            detect_count++;
#endif

            unsigned char *ImageInChar_2 = (unsigned char *)pmsis_l2_malloc(W_2 * H_2 * sizeof(IMAGE_IN_T));
            if (RESIZE)
            {

                //Resize Targets
                PRINTF("\n-------- STRAT RESIZE TARGETS ----------\n");
                int resize_W = bbxs.bbs[box_num].w;
                int resize_H = bbxs.bbs[box_num].h;
                int resize_X = bbxs.bbs[box_num].x;
                int resize_Y = bbxs.bbs[box_num].y;

                unsigned char *ImageTemp = (unsigned char *)pmsis_l2_malloc(resize_W * resize_H * sizeof(unsigned char));
                for (int y = 0; y < resize_H; y++)
                {
                    for (int x = 0; x < resize_W; x++)
                    {
                        ImageTemp[y * resize_W + x] = ImageInChar[(y + resize_Y) * W + (x + resize_X)];
                    }
                }
                memset(task, 0, sizeof(struct pi_cluster_task));
                task->entry = &Resize;
                task->stack_size = (uint32_t)CLUSTER_STACK_SIZE;
                task->slave_stack_size = (uint32_t)CLUSTER_SLAVE_STACK_SIZE;

                KerResizeBilinear_ArgT ResizeArg;
                ResizeArg.In = ImageTemp;
                ResizeArg.Win = resize_W;
                ResizeArg.Hin = resize_H;
                ResizeArg.Out = ImageInChar_2;
                ResizeArg.Wout = W_2;
                ResizeArg.Hout = H_2;
                ResizeArg.HTileOut = H_2;
                ResizeArg.FirstLineIndex = 0;
                task->arg = &ResizeArg;
                pi_cluster_send_task_to_cl(&cluster_dev, task);
                pmsis_l2_malloc_free(ImageTemp, resize_W * resize_H * sizeof(unsigned char));
            }
            else
            {
                //Crop Targets
                PRINTF("\n-------- STRAT CROP TARGETS ----------\n");
                cropTargets(&bbxs, box_num, ImageInChar, ImageInChar_2);
            }

            // Adjust float to fix
            // sprintf(ImageName, "../../../samples_codetest/gap8_gesture_prepare/pic_output/0/num11_label6.pgm");
            // ReadImageFromFile(ImageName, &Wi, &Hi, ImageInChar_2, Wi * Hi * sizeof(unsigned char));
            ImageIn_2 = (short int *)ImageInChar_2;
            for (int i = W_2 * H_2 - 1; i >= 0; i--)
            {
                ImageIn_2[i] = (short int)ImageInChar_2[i] << INPUT_1_Q - 8;
            }

            PRINTF("\n-------- STRAT RUN RESNET ----------\n");

            memset(task_resnet, 0, sizeof(struct pi_cluster_task));
            task_resnet->entry = RunRESNET;
            task_resnet->arg = (void *)NULL;
            task_resnet->stack_size = (uint32_t)CLUSTER_STACK_SIZE;
            task_resnet->slave_stack_size = (uint32_t)CLUSTER_SLAVE_STACK_SIZE;
            //Dispatch task on cluster
            pi_cluster_send_task_to_cl(&cluster_dev, task_resnet);
            //Check Results
            int outclass, MaxPrediction = 0;
            for (int i = 0; i < NUM_CLASSES; i++)
            {
                PRINTF("Class%d confidence:\t%d\n", i, Output[i]);
                if (Output[i] > MaxPrediction)
                {
                    outclass = i;
                    MaxPrediction = Output[i];
                }
            }
#ifdef PERFORMANCE_DEBUG
            if (outclass == gesture_now)
            {
                right_count++;
            }
#endif

#ifndef MUTE
            switch (outclass)
            {
            case 0:
                strcpy(dirction, "backward");
                break;
            case 1:
                strcpy(dirction, "down");
                break;
            case 2:
                strcpy(dirction, "forward");
                break;
            case 3:
                strcpy(dirction, "left");
                break;
            case 4:
                strcpy(dirction, "right");
                break;
            case 5:
                strcpy(dirction, "up");
                break;
            case 6:
                strcpy(dirction, "no_gesture");
                break;
            }
#endif
            PRINTF("Predicted class:\t%d\n", outclass);
            PRINTF("Predicted direction:\t%s\n", dirction);
            PRINTF("With confidence:\t%d\n", MaxPrediction);
            PRINTF("=== Task ended \n ");

#ifdef TOTAL_CYCLE
            t_end = gap_cl_readhwtimer() - t_start;
            printf("Cycles total from PC: %15d\n", t_end);
            printf("SSD gesture: 1\n");
#endif

            if (SAVE_GESTURE_DET == 1)
            {
                for (int y = 0; y < H_2; y++)
                {
                    for (int x = 0; x < W_2; x++)
                    {
                        ImageInChar_2[y * W_2 + x] = (unsigned char)(ImageIn_2[(y * W_2) + (x)] >> INPUT_1_Q - 8);
                    }
                }
                writeDetImg_resnet(ImageInChar_2, count, outclass);
            }

            pmsis_l2_malloc_free(ImageInChar_2, W_2 * H_2 * sizeof(short int));

            GESTURE_FLAG = 0;
        }

#if defined(USE_STREAMER)
        // Send image to the streamer to see the result
        frame_streamer_send_async(streamer1, &buffer, pi_task_callback(&task1, streamer_handler, (void *)&stream1_done));
#endif

        count = count + 1;
        if (count == pic_num)
        {
            iter = 0;
        }

        max_person_id = 0;
        max_person_confidence = 0;
        max_gesture_id = 0;
        max_gesture_confidence = 0;

#ifdef PERFORMANCE_DEBUG
        detect_rate = detect_count / pic_num;
        right_rate = right_count / detect_count;
        printf("Label%d detect rate: %f , right rate: %f.\n", gesture_now, detect_rate, right_rate);
        // printf("Map usage: Map0: %d, Map1: %d, Map2: %d, Map3: %d.\n", map0_used, map1_used, map2_used, map3_used);
#endif

        //Send to Screen
        // pi_display_write(&ili, &buffer, 40, 60, 160, 120);
        // #endif
    }

    //put CNN Destruct out loop
    cnn_ssdCNN_Destruct();
    resnetCNN_Destruct();

    pi_cluster_close(&cluster_dev);

    PRINTF("Loop Ended!!!!!!\n");
#ifdef PERFORMANCE_DEBUG
    detect_rate = detect_count / pic_num;
    right_rate = right_count / detect_count;
    printf("Label%d detect rate: %f , right rate: %f.\n", gesture_now, detect_rate, right_rate);
    // printf("Map usage: Map0: %d, Map1: %d, Map2: %d, Map3: %d.\n", map0_used, map1_used, map2_used, map3_used);
#endif

    pmsis_exit(0);
    return 0;
}

int main(void)
{
    return pmsis_kickoff((void *)start);
}
