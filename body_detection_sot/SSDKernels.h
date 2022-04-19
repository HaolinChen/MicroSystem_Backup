#ifndef __SSDKERNEL_H__
#define __SSDKERNEL_H__

#include "AutoTilerLibTypes.h"
#include "SSDBasicKernels.h"
#define _SSDKernels_L1_Memory_SIZE 37992
#define _SSDKernels_L2_Memory_SIZE 37992
extern char *SSDKernels_L1_Memory; /* Size given for generation: 38000 bytes, used: 37992 bytes */
extern char *SSDKernels_L2_Memory; /* Size used for generation: 37992 bytes */
extern void SDD3Dto2DSoftmax_80_60_12(
		short * In,
		short * Out,
		unsigned char Q,
		unsigned short n_classes);
extern void SDD3Dto2D_80_60_24(
		short * In,
		short * Out,
		unsigned char Q,
		unsigned short n_classes);
extern void Predecoder80_60(
		short * Classes,
		short * Boxes,
		void  * Ancor_layer,
		void  * BoundingBoxes,
		int Boxes_Q);
extern void SDD3Dto2DSoftmax_40_30_14(
		short * In,
		short * Out,
		unsigned char Q,
		unsigned short n_classes);
extern void SDD3Dto2D_40_30_28(
		short * In,
		short * Out,
		unsigned char Q,
		unsigned short n_classes);
extern void Predecoder40_30(
		short * Classes,
		short * Boxes,
		void  * Ancor_layer,
		void  * BoundingBoxes,
		int Boxes_Q);
extern void SDD3Dto2DSoftmax_20_15_16(
		short * In,
		short * Out,
		unsigned char Q,
		unsigned short n_classes);
extern void SDD3Dto2D_20_15_32(
		short * In,
		short * Out,
		unsigned char Q,
		unsigned short n_classes);
extern void Predecoder20_15(
		short * Classes,
		short * Boxes,
		void  * Ancor_layer,
		void  * BoundingBoxes,
		int Boxes_Q);
extern void SDD3Dto2DSoftmax_10_7_14(
		short * In,
		short * Out,
		unsigned char Q,
		unsigned short n_classes);
extern void SDD3Dto2D_10_7_28(
		short * In,
		short * Out,
		unsigned char Q,
		unsigned short n_classes);
extern void Predecoder10_7(
		short * Classes,
		short * Boxes,
		void  * Ancor_layer,
		void  * BoundingBoxes,
		int Boxes_Q);
#endif
