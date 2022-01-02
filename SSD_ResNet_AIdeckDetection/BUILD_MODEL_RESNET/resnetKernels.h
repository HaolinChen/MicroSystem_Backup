#ifndef __RESNETKERNEL_H__
#define __RESNETKERNEL_H__

#include "AutoTilerLibTypes.h"
#include "CNN_BasicKernels.h"
#include "resnet.h"
#define _resnet_L1_Memory_SIZE 18720
#define _resnet_L2_Memory_SIZE 18720
extern char *resnet_L1_Memory; /* Size given for generation: 18736 bytes, used: 18720 bytes */
extern char *resnet_L2_Memory; /* Size used for generation: 18720 bytes */
extern void S4_Conv2d_8x1x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out);
extern void S7_Conv2d_8x8x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out);
extern void S10_Conv2d_8x8x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out);
extern void S13_Conv2d_8x8x3x3(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out);
extern void S14_MatAdd_8x39x39(
		short int * __restrict__ In1,
		short int * __restrict__ In2,
		short int * __restrict__ Out);
extern void S17_Conv2d_8x8x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out);
extern void S20_Conv2d_8x8x3x3(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out);
extern void S21_MatAdd_8x39x39(
		short int * __restrict__ In1,
		short int * __restrict__ In2,
		short int * __restrict__ Out);
extern void S24_Conv2d_16x8x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out);
extern void S27_Conv2d_16x8x1x1(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out);
extern void S30_Conv2d_16x16x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out);
extern void S31_MatAdd_16x20x20(
		short int * __restrict__ In1,
		short int * __restrict__ In2,
		short int * __restrict__ Out);
extern void S34_Conv2d_16x16x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out);
extern void S37_Conv2d_16x16x3x3(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out);
extern void S38_MatAdd_16x20x20(
		short int * __restrict__ In1,
		short int * __restrict__ In2,
		short int * __restrict__ Out);
extern void S41_Conv2d_32x16x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out);
extern void S44_Conv2d_32x16x1x1(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out);
extern void S47_Conv2d_32x32x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out);
extern void S48_MatAdd_32x10x10(
		short int * __restrict__ In1,
		short int * __restrict__ In2,
		short int * __restrict__ Out);
extern void S51_Conv2d_32x32x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out);
extern void S54_Conv2d_32x32x3x3(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out);
extern void S55_MatAdd_32x10x10(
		short int * __restrict__ In1,
		short int * __restrict__ In2,
		short int * __restrict__ Out);
extern void S58_Conv2d_64x32x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out);
extern void S61_Conv2d_64x32x1x1(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out);
extern void S64_Conv2d_64x64x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out);
extern void S65_MatAdd_64x5x5(
		short int * __restrict__ In1,
		short int * __restrict__ In2,
		short int * __restrict__ Out);
extern void S68_Conv2d_64x64x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out);
extern void S71_Conv2d_64x64x3x3(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out);
extern void S72_MatAdd_64x5x5(
		short int * __restrict__ In1,
		short int * __restrict__ In2,
		short int * __restrict__ Out);
extern void S73_AveragePool_2x2(
		short int * __restrict__ In,
		short int * __restrict__ Out);
extern void S76_Linear_7x256(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out);
extern void S77_SoftMax(
		short int * __restrict__ In,
		short int * __restrict__ Out);
extern int resnetCNN_Construct();
extern int resnetCNN_Destruct();
extern int resnetCNN(
		signed short * __restrict__ Input_1,
		signed short * __restrict__ Output_1);
#endif
