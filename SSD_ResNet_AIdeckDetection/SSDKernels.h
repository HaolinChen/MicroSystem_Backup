#ifndef __SSDKERNEL_H__
#define __SSDKERNEL_H__

#include "AutoTilerLibTypes.h"
#include "SSDBasicKernels.h"
#define _SSDKernels_L1_Memory_SIZE 14984
#define _SSDKernels_L2_Memory_SIZE 14984
extern char *SSDKernels_L1_Memory; /* Size given for generation: 15000 bytes, used: 14984 bytes */
extern char *SSDKernels_L2_Memory; /* Size used for generation: 14984 bytes */
extern void SDD3Dto2DSoftmax_20_16_18(
		short * In,
		short * Out,
		unsigned char Q,
		unsigned short n_classes);
extern void SDD3Dto2D_20_16_24(
		short * In,
		short * Out,
		unsigned char Q,
		unsigned short n_classes);
extern void Predecoder20_16(
		short * Classes,
		short * Boxes,
		void  * Ancor_layer,
		void  * BoundingBoxes,
		int Boxes_Q);
extern void SDD3Dto2DSoftmax_10_8_18(
		short * In,
		short * Out,
		unsigned char Q,
		unsigned short n_classes);
extern void SDD3Dto2D_10_8_24(
		short * In,
		short * Out,
		unsigned char Q,
		unsigned short n_classes);
extern void Predecoder10_8(
		short * Classes,
		short * Boxes,
		void  * Ancor_layer,
		void  * BoundingBoxes,
		int Boxes_Q);
extern void SDD3Dto2DSoftmax_5_4_18(
		short * In,
		short * Out,
		unsigned char Q,
		unsigned short n_classes);
extern void SDD3Dto2D_5_4_24(
		short * In,
		short * Out,
		unsigned char Q,
		unsigned short n_classes);
extern void Predecoder5_4(
		short * Classes,
		short * Boxes,
		void  * Ancor_layer,
		void  * BoundingBoxes,
		int Boxes_Q);
extern void SDD3Dto2DSoftmax_2_2_18(
		short * In,
		short * Out,
		unsigned char Q,
		unsigned short n_classes);
extern void SDD3Dto2D_2_2_24(
		short * In,
		short * Out,
		unsigned char Q,
		unsigned short n_classes);
extern void Predecoder2_2(
		short * Classes,
		short * Boxes,
		void  * Ancor_layer,
		void  * BoundingBoxes,
		int Boxes_Q);
#endif
