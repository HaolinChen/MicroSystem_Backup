#include "SSDKernels.h"
L1_CL_MEM AT_L1_POINTER SSDKernels_L1_Memory;
L2_MEM AT_L2_POINTER SSDKernels_L2_Memory;
AT_HYPERRAM_POINTER SSDKernels_L3_Memory;
extern AT_HYPERRAM_T HyperRam;
void SDD3Dto2DSoftmax_20_16_12(
		short * In,
		short * Out,
		unsigned char Q,
		unsigned short n_classes)

{
	/* Shared L1: 15360 bytes, L2 buffer: 15360 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	AT_HYPERRAM_CL_EVENT UchanHR2;
	KerSDD3Dto2DShort_ArgT S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile0 Dim: 1]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 7680 [Tile0, 1:[12x320], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[12x320], 2]
		Tile0: [0, 7680, 7680], Tile1: [0, 7680, 7680], Tile2; [0, 7680, 7680]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 7680 [Tile0, 1:[12x320], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[12x320], 2]
		Tile0: [0, 7680, 7680], Tile1: [0, 7680, 7680], Tile2; [0, 7680, 7680]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (short * __restrict__) (SSDKernels_L1_Memory+0);
	KerArg0->Win = (unsigned int ) (320);
	KerArg0->Hin = (unsigned int ) (12);
	KerArg0->Out = (short * __restrict__) (SSDKernels_L1_Memory+7680);
	KerArg0->Wout = (unsigned int ) (12);
	KerArg0->Hout = (unsigned int ) (320);
	KerArg0->Q = (unsigned char) (Q);
	KerArg0->n_classes = (unsigned short) (n_classes);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), 7680, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0), 7680, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile0 */
		int T0Ind_Last = 1;
		/*====================== Call Kernel LOC_LOOP =========================*/
		AT_FORK(gap_ncore(), (void *) KerSDD3Dto2DShort, (void *) KerArg0);
		__CALL(KerSDD3Dto2DShort, KerArg0);
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+7680+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+7680), 7680, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+7680+0), 7680, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void SDD3Dto2D_20_16_24(
		short * In,
		short * Out,
		unsigned char Q,
		unsigned short n_classes)

{
	/* Shared L1: 37824 bytes, L2 buffer: 37824 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	AT_HYPERRAM_CL_EVENT UchanHR2;
	KerSDD3Dto2DShort_ArgT S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast, T0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _NN_In;
	unsigned int _SN_In, _SNN_In;
	unsigned int _LN_In, _LNN_In;
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile0 Dim: 2]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 2 logical tiles, 2 physical tiles
			Total Size: 15360 [Tile0, 2:[24x197, 24x123], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 2:[24x197, 24x123], 2]
		Tile0: [0, 9456, 394], Tile1: [394, 5904, 246], Tile2; [0, 9456, 394]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 2 physical tiles
			Total Size: 15360 [Tile0, 2:[24x197, 24x123], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 2:[24x197, 24x123], 2]
		Tile0: [0, 9456, 9456], Tile1: [9456, 5904, 5904], Tile2; [0, 9456, 9456]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Hin = (unsigned int ) (24);
	KerArg0->Wout = (unsigned int ) (24);
	KerArg0->Q = (unsigned char) (Q);
	KerArg0->n_classes = (unsigned short) (n_classes);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), 9456, 640, 394, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+394), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+9456), 5904, 640, 246, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0+0), 9456, 0, &DmaR_Evt1);
	_NN_In=394; _SN_In=5904;
	_C_Out=0; _SC_Out=9456;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	for (T0Ind=0; T0Ind<2; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
		int T0Ind_Last = (T0Ind==1), T0Ind_NextLast = ((T0Ind+1)==1), T0Ind_NextNextLast = ((T0Ind+2)==1);
		/*================================= Prepare Tiles ===================================*/
		_SNN_In = 0;
		if (!(T0Ind_Last)) {
			if (!(1)) {
				_NN_In = _NN_In + (394); _LNN_In = ((1)?246:394); _SNN_In = (24*_LNN_In); 
			}
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
		if (_SNN_In) {
			AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+9456*((T0Ind_Total)%2)),
					_SNN_In, 640, _LNN_In, 0, &UchanHR1);
		}
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
		if (_SN_In) {
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+9456*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0+9456*((T0Ind_Total+1)%2)),
					_SN_In, 0, &DmaR_Evt1);
		}
		/*============================= End Read Tiles ======================================*/
		/*====================== Call Kernel LOC_LOOP =========================*/
		KerArg0->In = (short * __restrict__) (SSDKernels_L1_Memory+0+9456*((T0Ind_Total)%2));
		KerArg0->Win = (unsigned int ) ((T0Ind_Last)?123:197);
		KerArg0->Out = (short * __restrict__) (SSDKernels_L1_Memory+18912+9456*((T0Ind_Total)%2));
		KerArg0->Hout = (unsigned int ) (T0Ind_Last?123:197);
		AT_FORK(gap_ncore(), (void *) KerSDD3Dto2DShort, (void *) KerArg0);
		__CALL(KerSDD3Dto2DShort, KerArg0);
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
		if (_SP_Out) AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+18912+9456*((T0Ind_Total+-1)%2)),
					_SP_Out, 1, &UchanHR2);
		AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+18912+9456*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+18912+9456*((T0Ind_Total)%2)),
				_SC_Out, 1, &DmaW_Evt1);
		/*============================= End Write Tiles =====================================*/
		/*================================= Update Arg Pipeline =============================*/
		_SN_In = _SNN_In;_LN_In = _LNN_In;
		_SPP_Out = _SP_Out;
		_P_Out = _C_Out;_SP_Out = _SC_Out;
		/*============================= End Update Arg Pipeline =============================*/
		/*================================= Prepare Tiles ===================================*/
		_SC_Out = 0;
		if (!(T0Ind_Last)) {
			_C_Out = _C_Out + (9456); _SC_Out = ((1)?5904:9456); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+18912+9456*((T0Ind_Total+-1)%2)), _SP_Out, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void Predecoder20_16(
		short * Classes,
		short * Boxes,
		void  * Ancor_layer,
		void  * BoundingBoxes,
		int Boxes_Q)

{
	/* Shared L1: 37992 bytes, L2 buffer: 37992 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	AT_HYPERRAM_CL_EVENT UchanHR2;
	KerPredecoderShort_ArgT S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast, T0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _NN_Classes;
	unsigned int _SN_Classes, _SNN_Classes;
	unsigned int _NN_Boxes;
	unsigned int _SN_Boxes, _SNN_Boxes;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile0 Dim: 2]
	Ker Arg: Classes, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 2 logical tiles, 2 physical tiles
			Total Size: 7680 [Tile0, 2:[2x1583, 2x337], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 2:[2x1583, 2x337], 2]
		Tile0: [0, 6332, 6332], Tile1: [6332, 1348, 1348], Tile2; [0, 6332, 6332]
	Ker Arg: Boxes, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 2 logical tiles, 2 physical tiles
			Total Size: 15360 [Tile0, 2:[4x1583, 4x337], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 2:[4x1583, 4x337], 2]
		Tile0: [0, 12664, 12664], Tile1: [12664, 2696, 2696], Tile2; [0, 12664, 12664]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Classes_W = (unsigned int ) (2);
	KerArg0->Classes_Std_H = (unsigned int ) (1583);
	KerArg0->Ancor_layer = (void  * __restrict__) (Ancor_layer);
	KerArg0->BoundingBoxes = (void  * __restrict__) (BoundingBoxes);
	KerArg0->Boxes_Q = (int) (Boxes_Q);
	KerArg0->n_classes = (unsigned int ) (2);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Classes+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), 6332, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read Classes */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Classes+6332), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+6332), 1348, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0+0), 6332, 0, &DmaR_Evt1);
	_NN_Classes=6332; _SN_Classes=1348;
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Boxes+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+12664+0), 12664, 0, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read Boxes */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Boxes+12664), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+12664+12664), 2696, 0, &UchanHR2);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+12664+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+12664+0), 12664, 0, &DmaR_Evt2);
	_NN_Boxes=12664; _SN_Boxes=2696;
	/*============================= End Read Tiles Prolog ===============================*/
	for (T0Ind=0; T0Ind<2; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
		int T0Ind_Last = (T0Ind==1), T0Ind_NextLast = ((T0Ind+1)==1), T0Ind_NextNextLast = ((T0Ind+2)==1);
		/*================================= Prepare Tiles ===================================*/
		_SNN_Classes = 0;
		if (!(T0Ind_Last)) {
			if (!(1)) {
				_NN_Classes = _NN_Classes + (6332); _SNN_Classes = ((1)?1348:6332); 
			}
		}
		_SNN_Boxes = 0;
		if (!(T0Ind_Last)) {
			if (!(1)) {
				_NN_Boxes = _NN_Boxes + (12664); _SNN_Boxes = ((1)?2696:12664); 
			}
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read Classes */
		if (_SNN_Classes) {
			AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Classes+_NN_Classes), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+6332*((T0Ind_Total)%2)),
					_SNN_Classes, 0, &UchanHR1);
		}
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Classes */
		if (_SN_Classes) {
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+6332*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0+6332*((T0Ind_Total+1)%2)),
					_SN_Classes, 0, &DmaR_Evt1);
		}
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read Boxes */
		if (_SNN_Boxes) {
			AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Boxes+_NN_Boxes), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+12664+12664*((T0Ind_Total)%2)),
					_SNN_Boxes, 0, &UchanHR2);
		}
		AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Boxes */
		if (_SN_Boxes) {
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+12664+12664*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+12664+12664*((T0Ind_Total+1)%2)),
					_SN_Boxes, 0, &DmaR_Evt2);
		}
		/*============================= End Read Tiles ======================================*/
		/*====================== Call Kernel LOC_LOOP =========================*/
		KerArg0->Classes = (short * __restrict__) (SSDKernels_L1_Memory+0+6332*((T0Ind_Total)%2));
		KerArg0->Boxes = (short * __restrict__) (SSDKernels_L1_Memory+12664+12664*((T0Ind_Total)%2));
		KerArg0->Classes_H = (unsigned int ) (T0Ind_Last?337:1583);
		KerArg0->Classes_TileIndex = (unsigned int ) ((T0Ind));
		AT_FORK(gap_ncore(), (void *) KerPredecoderShort, (void *) KerArg0);
		__CALL(KerPredecoderShort, KerArg0);
		/*================================= Update Arg Pipeline =============================*/
		_SN_Classes = _SNN_Classes;
		_SN_Boxes = _SNN_Boxes;
		/*============================= End Update Arg Pipeline =============================*/
	} /* End iteration on Tile0 */
}
void SDD3Dto2DSoftmax_10_8_12(
		short * In,
		short * Out,
		unsigned char Q,
		unsigned short n_classes)

{
	/* Shared L1: 3840 bytes, L2 buffer: 3840 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	AT_HYPERRAM_CL_EVENT UchanHR2;
	KerSDD3Dto2DShort_ArgT S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile0 Dim: 1]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 1920 [Tile0, 1:[12x80], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[12x80], 2]
		Tile0: [0, 1920, 1920], Tile1: [0, 1920, 1920], Tile2; [0, 1920, 1920]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 1920 [Tile0, 1:[12x80], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[12x80], 2]
		Tile0: [0, 1920, 1920], Tile1: [0, 1920, 1920], Tile2; [0, 1920, 1920]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (short * __restrict__) (SSDKernels_L1_Memory+0);
	KerArg0->Win = (unsigned int ) (80);
	KerArg0->Hin = (unsigned int ) (12);
	KerArg0->Out = (short * __restrict__) (SSDKernels_L1_Memory+1920);
	KerArg0->Wout = (unsigned int ) (12);
	KerArg0->Hout = (unsigned int ) (80);
	KerArg0->Q = (unsigned char) (Q);
	KerArg0->n_classes = (unsigned short) (n_classes);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), 1920, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0), 1920, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile0 */
		int T0Ind_Last = 1;
		/*====================== Call Kernel LOC_LOOP =========================*/
		AT_FORK(gap_ncore(), (void *) KerSDD3Dto2DShort, (void *) KerArg0);
		__CALL(KerSDD3Dto2DShort, KerArg0);
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+1920+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+1920), 1920, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+1920+0), 1920, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void SDD3Dto2D_10_8_24(
		short * In,
		short * Out,
		unsigned char Q,
		unsigned short n_classes)

{
	/* Shared L1: 7680 bytes, L2 buffer: 7680 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	AT_HYPERRAM_CL_EVENT UchanHR2;
	KerSDD3Dto2DShort_ArgT S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile0 Dim: 1]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 3840 [Tile0, 1:[24x80], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[24x80], 2]
		Tile0: [0, 3840, 3840], Tile1: [0, 3840, 3840], Tile2; [0, 3840, 3840]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 3840 [Tile0, 1:[24x80], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[24x80], 2]
		Tile0: [0, 3840, 3840], Tile1: [0, 3840, 3840], Tile2; [0, 3840, 3840]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (short * __restrict__) (SSDKernels_L1_Memory+0);
	KerArg0->Win = (unsigned int ) (80);
	KerArg0->Hin = (unsigned int ) (24);
	KerArg0->Out = (short * __restrict__) (SSDKernels_L1_Memory+3840);
	KerArg0->Wout = (unsigned int ) (24);
	KerArg0->Hout = (unsigned int ) (80);
	KerArg0->Q = (unsigned char) (Q);
	KerArg0->n_classes = (unsigned short) (n_classes);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), 3840, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0), 3840, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile0 */
		int T0Ind_Last = 1;
		/*====================== Call Kernel LOC_LOOP =========================*/
		AT_FORK(gap_ncore(), (void *) KerSDD3Dto2DShort, (void *) KerArg0);
		__CALL(KerSDD3Dto2DShort, KerArg0);
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+3840+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+3840), 3840, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+3840+0), 3840, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void Predecoder10_8(
		short * Classes,
		short * Boxes,
		void  * Ancor_layer,
		void  * BoundingBoxes,
		int Boxes_Q)

{
	/* Shared L1: 5760 bytes, L2 buffer: 5760 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	AT_HYPERRAM_CL_EVENT UchanHR2;
	KerPredecoderShort_ArgT S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile0 Dim: 1]
	Ker Arg: Classes, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 1920 [Tile0, 1:[2x480], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[2x480], 2]
		Tile0: [0, 1920, 1920], Tile1: [0, 1920, 1920], Tile2; [0, 1920, 1920]
	Ker Arg: Boxes, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 3840 [Tile0, 1:[4x480], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[4x480], 2]
		Tile0: [0, 3840, 3840], Tile1: [0, 3840, 3840], Tile2; [0, 3840, 3840]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Classes = (short * __restrict__) (SSDKernels_L1_Memory+0);
	KerArg0->Boxes = (short * __restrict__) (SSDKernels_L1_Memory+1920);
	KerArg0->Classes_W = (unsigned int ) (2);
	KerArg0->Classes_H = (unsigned int ) (480);
	KerArg0->Classes_TileIndex = (unsigned int ) ((0));
	KerArg0->Classes_Std_H = (unsigned int ) (480);
	KerArg0->Ancor_layer = (void  * __restrict__) (Ancor_layer);
	KerArg0->BoundingBoxes = (void  * __restrict__) (BoundingBoxes);
	KerArg0->Boxes_Q = (int) (Boxes_Q);
	KerArg0->n_classes = (unsigned int ) (2);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Classes+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), 1920, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read Classes */
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0), 1920, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Classes */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Boxes+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+1920+0), 3840, 0, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read Boxes */
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+1920+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+1920), 3840, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Boxes */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile0 */
		int T0Ind_Last = 1;
		/*====================== Call Kernel LOC_LOOP =========================*/
		AT_FORK(gap_ncore(), (void *) KerPredecoderShort, (void *) KerArg0);
		__CALL(KerPredecoderShort, KerArg0);
	} /* End iteration on Tile0 */
}
void SDD3Dto2DSoftmax_5_4_12(
		short * In,
		short * Out,
		unsigned char Q,
		unsigned short n_classes)

{
	/* Shared L1: 960 bytes, L2 buffer: 960 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	AT_HYPERRAM_CL_EVENT UchanHR2;
	KerSDD3Dto2DShort_ArgT S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile0 Dim: 1]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 480 [Tile0, 1:[12x20], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[12x20], 2]
		Tile0: [0, 480, 480], Tile1: [0, 480, 480], Tile2; [0, 480, 480]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 480 [Tile0, 1:[12x20], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[12x20], 2]
		Tile0: [0, 480, 480], Tile1: [0, 480, 480], Tile2; [0, 480, 480]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (short * __restrict__) (SSDKernels_L1_Memory+0);
	KerArg0->Win = (unsigned int ) (20);
	KerArg0->Hin = (unsigned int ) (12);
	KerArg0->Out = (short * __restrict__) (SSDKernels_L1_Memory+480);
	KerArg0->Wout = (unsigned int ) (12);
	KerArg0->Hout = (unsigned int ) (20);
	KerArg0->Q = (unsigned char) (Q);
	KerArg0->n_classes = (unsigned short) (n_classes);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), 480, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0), 480, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile0 */
		int T0Ind_Last = 1;
		/*====================== Call Kernel LOC_LOOP =========================*/
		AT_FORK(gap_ncore(), (void *) KerSDD3Dto2DShort, (void *) KerArg0);
		__CALL(KerSDD3Dto2DShort, KerArg0);
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+480+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+480), 480, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+480+0), 480, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void SDD3Dto2D_5_4_24(
		short * In,
		short * Out,
		unsigned char Q,
		unsigned short n_classes)

{
	/* Shared L1: 1920 bytes, L2 buffer: 1920 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	AT_HYPERRAM_CL_EVENT UchanHR2;
	KerSDD3Dto2DShort_ArgT S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile0 Dim: 1]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 960 [Tile0, 1:[24x20], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[24x20], 2]
		Tile0: [0, 960, 960], Tile1: [0, 960, 960], Tile2; [0, 960, 960]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 960 [Tile0, 1:[24x20], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[24x20], 2]
		Tile0: [0, 960, 960], Tile1: [0, 960, 960], Tile2; [0, 960, 960]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (short * __restrict__) (SSDKernels_L1_Memory+0);
	KerArg0->Win = (unsigned int ) (20);
	KerArg0->Hin = (unsigned int ) (24);
	KerArg0->Out = (short * __restrict__) (SSDKernels_L1_Memory+960);
	KerArg0->Wout = (unsigned int ) (24);
	KerArg0->Hout = (unsigned int ) (20);
	KerArg0->Q = (unsigned char) (Q);
	KerArg0->n_classes = (unsigned short) (n_classes);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), 960, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0), 960, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile0 */
		int T0Ind_Last = 1;
		/*====================== Call Kernel LOC_LOOP =========================*/
		AT_FORK(gap_ncore(), (void *) KerSDD3Dto2DShort, (void *) KerArg0);
		__CALL(KerSDD3Dto2DShort, KerArg0);
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+960+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+960), 960, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+960+0), 960, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void Predecoder5_4(
		short * Classes,
		short * Boxes,
		void  * Ancor_layer,
		void  * BoundingBoxes,
		int Boxes_Q)

{
	/* Shared L1: 1440 bytes, L2 buffer: 1440 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	AT_HYPERRAM_CL_EVENT UchanHR2;
	KerPredecoderShort_ArgT S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile0 Dim: 1]
	Ker Arg: Classes, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 480 [Tile0, 1:[2x120], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[2x120], 2]
		Tile0: [0, 480, 480], Tile1: [0, 480, 480], Tile2; [0, 480, 480]
	Ker Arg: Boxes, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 960 [Tile0, 1:[4x120], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[4x120], 2]
		Tile0: [0, 960, 960], Tile1: [0, 960, 960], Tile2; [0, 960, 960]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Classes = (short * __restrict__) (SSDKernels_L1_Memory+0);
	KerArg0->Boxes = (short * __restrict__) (SSDKernels_L1_Memory+480);
	KerArg0->Classes_W = (unsigned int ) (2);
	KerArg0->Classes_H = (unsigned int ) (120);
	KerArg0->Classes_TileIndex = (unsigned int ) ((0));
	KerArg0->Classes_Std_H = (unsigned int ) (120);
	KerArg0->Ancor_layer = (void  * __restrict__) (Ancor_layer);
	KerArg0->BoundingBoxes = (void  * __restrict__) (BoundingBoxes);
	KerArg0->Boxes_Q = (int) (Boxes_Q);
	KerArg0->n_classes = (unsigned int ) (2);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Classes+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), 480, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read Classes */
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0), 480, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Classes */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Boxes+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+480+0), 960, 0, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read Boxes */
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+480+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+480), 960, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Boxes */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile0 */
		int T0Ind_Last = 1;
		/*====================== Call Kernel LOC_LOOP =========================*/
		AT_FORK(gap_ncore(), (void *) KerPredecoderShort, (void *) KerArg0);
		__CALL(KerPredecoderShort, KerArg0);
	} /* End iteration on Tile0 */
}
void SDD3Dto2DSoftmax_2_2_12(
		short * In,
		short * Out,
		unsigned char Q,
		unsigned short n_classes)

{
	/* Shared L1: 192 bytes, L2 buffer: 192 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	AT_HYPERRAM_CL_EVENT UchanHR2;
	KerSDD3Dto2DShort_ArgT S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile0 Dim: 1]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 96 [Tile0, 1:[12x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[12x4], 2]
		Tile0: [0, 96, 96], Tile1: [0, 96, 96], Tile2; [0, 96, 96]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 96 [Tile0, 1:[12x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[12x4], 2]
		Tile0: [0, 96, 96], Tile1: [0, 96, 96], Tile2; [0, 96, 96]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (short * __restrict__) (SSDKernels_L1_Memory+0);
	KerArg0->Win = (unsigned int ) (4);
	KerArg0->Hin = (unsigned int ) (12);
	KerArg0->Out = (short * __restrict__) (SSDKernels_L1_Memory+96);
	KerArg0->Wout = (unsigned int ) (12);
	KerArg0->Hout = (unsigned int ) (4);
	KerArg0->Q = (unsigned char) (Q);
	KerArg0->n_classes = (unsigned short) (n_classes);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), 96, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0), 96, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile0 */
		int T0Ind_Last = 1;
		/*====================== Call Kernel LOC_LOOP =========================*/
		AT_FORK(gap_ncore(), (void *) KerSDD3Dto2DShort, (void *) KerArg0);
		__CALL(KerSDD3Dto2DShort, KerArg0);
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+96+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+96), 96, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+96+0), 96, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void SDD3Dto2D_2_2_24(
		short * In,
		short * Out,
		unsigned char Q,
		unsigned short n_classes)

{
	/* Shared L1: 384 bytes, L2 buffer: 384 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	AT_HYPERRAM_CL_EVENT UchanHR2;
	KerSDD3Dto2DShort_ArgT S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile0 Dim: 1]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 192 [Tile0, 1:[24x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[24x4], 2]
		Tile0: [0, 192, 192], Tile1: [0, 192, 192], Tile2; [0, 192, 192]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 192 [Tile0, 1:[24x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[24x4], 2]
		Tile0: [0, 192, 192], Tile1: [0, 192, 192], Tile2; [0, 192, 192]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (short * __restrict__) (SSDKernels_L1_Memory+0);
	KerArg0->Win = (unsigned int ) (4);
	KerArg0->Hin = (unsigned int ) (24);
	KerArg0->Out = (short * __restrict__) (SSDKernels_L1_Memory+192);
	KerArg0->Wout = (unsigned int ) (24);
	KerArg0->Hout = (unsigned int ) (4);
	KerArg0->Q = (unsigned char) (Q);
	KerArg0->n_classes = (unsigned short) (n_classes);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), 192, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0), 192, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile0 */
		int T0Ind_Last = 1;
		/*====================== Call Kernel LOC_LOOP =========================*/
		AT_FORK(gap_ncore(), (void *) KerSDD3Dto2DShort, (void *) KerArg0);
		__CALL(KerSDD3Dto2DShort, KerArg0);
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+192+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+192), 192, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+192+0), 192, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void Predecoder2_2(
		short * Classes,
		short * Boxes,
		void  * Ancor_layer,
		void  * BoundingBoxes,
		int Boxes_Q)

{
	/* Shared L1: 288 bytes, L2 buffer: 288 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	AT_HYPERRAM_CL_EVENT UchanHR2;
	KerPredecoderShort_ArgT S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile0 Dim: 1]
	Ker Arg: Classes, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 96 [Tile0, 1:[2x24], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[2x24], 2]
		Tile0: [0, 96, 96], Tile1: [0, 96, 96], Tile2; [0, 96, 96]
	Ker Arg: Boxes, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 192 [Tile0, 1:[4x24], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[4x24], 2]
		Tile0: [0, 192, 192], Tile1: [0, 192, 192], Tile2; [0, 192, 192]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Classes = (short * __restrict__) (SSDKernels_L1_Memory+0);
	KerArg0->Boxes = (short * __restrict__) (SSDKernels_L1_Memory+96);
	KerArg0->Classes_W = (unsigned int ) (2);
	KerArg0->Classes_H = (unsigned int ) (24);
	KerArg0->Classes_TileIndex = (unsigned int ) ((0));
	KerArg0->Classes_Std_H = (unsigned int ) (24);
	KerArg0->Ancor_layer = (void  * __restrict__) (Ancor_layer);
	KerArg0->BoundingBoxes = (void  * __restrict__) (BoundingBoxes);
	KerArg0->Boxes_Q = (int) (Boxes_Q);
	KerArg0->n_classes = (unsigned int ) (2);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Classes+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), 96, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read Classes */
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0), 96, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Classes */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Boxes+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+96+0), 192, 0, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read Boxes */
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+96+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+96), 192, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Boxes */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile0 */
		int T0Ind_Last = 1;
		/*====================== Call Kernel LOC_LOOP =========================*/
		AT_FORK(gap_ncore(), (void *) KerPredecoderShort, (void *) KerArg0);
		__CALL(KerPredecoderShort, KerArg0);
	} /* End iteration on Tile0 */
}
