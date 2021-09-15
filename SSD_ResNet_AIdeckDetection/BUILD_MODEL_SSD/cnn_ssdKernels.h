#ifndef __CNN_SSDKERNEL_H__
#define __CNN_SSDKERNEL_H__

#include "AutoTilerLibTypes.h"
#include "CNN_BasicKernels.h"
#include "cnn_ssd.h"
#define _cnn_ssd_L1_Memory_SIZE 47792
#define _cnn_ssd_L2_Memory_SIZE 46000
extern char *cnn_ssd_L1_Memory; /* Size given for generation: 48736 bytes, used: 47792 bytes */
extern char *cnn_ssd_L2_Memory; /* Size used for generation: 46000 bytes */
extern void S3_Conv2d_8x1x3x3_MaxPool_2x2_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out);
extern void S6_Conv2d_16x8x3x3_MaxPool_2x2_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out);
extern void S9_Conv2d_16x16x3x3_MaxPool_2x2_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out);
extern void S12_Conv2d_32x16x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out);
extern void S13_MaxPool_2x2(
		short int * __restrict__ In,
		short int * __restrict__ Out);
extern void S16_Conv2d_18x32x3x3(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out);
extern void S20_Conv2d_24x32x3x3(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out);
extern void S24_Conv2d_64x32x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out);
extern void S25_MaxPool_2x2(
		short int * __restrict__ In,
		short int * __restrict__ Out);
extern void S28_Conv2d_18x64x3x3(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out);
extern void S32_Conv2d_24x64x3x3(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out);
extern void S36_Conv2d_128x64x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out);
extern void S37_MaxPool_2x2(
		short int * __restrict__ In,
		short int * __restrict__ Out);
extern void S40_Conv2d_18x128x3x3(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out);
extern void S44_Conv2d_24x128x3x3(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out);
extern void S48_Conv2d_128x128x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out);
extern void S51_Conv2d_18x128x3x3(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out);
extern void S55_Conv2d_24x128x3x3(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out);
extern int cnn_ssdCNN_Construct();
extern int cnn_ssdCNN_Destruct();
extern int cnn_ssdCNN(
		signed short * __restrict__ Input_1,
		signed short * __restrict__ Output_1,
		signed short * __restrict__ Output_2,
		signed short * __restrict__ Output_3,
		signed short * __restrict__ Output_4,
		signed short * __restrict__ Output_5,
		signed short * __restrict__ Output_6,
		signed short * __restrict__ Output_7,
		signed short * __restrict__ Output_8);
extern unsigned int AT_GraphPerf[18];
extern char * AT_GraphNodeNames[18];
extern unsigned int AT_GraphOperInfosNames[18];
#endif
