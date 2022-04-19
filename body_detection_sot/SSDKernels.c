#include "SSDKernels.h"
L1_CL_MEM AT_L1_POINTER SSDKernels_L1_Memory;
L2_MEM AT_L2_POINTER SSDKernels_L2_Memory;
AT_HYPERRAM_POINTER SSDKernels_L3_Memory;
extern AT_HYPERRAM_T HyperRam;
void SDD3Dto2DSoftmax_80_60_12(
		short * In,
		short * Out,
		unsigned char Q,
		unsigned short n_classes)

{
	/* Shared L1: 37920 bytes, L2 buffer: 37920 bytes */
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
		[Tile0 Dim: 13]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 13 logical tiles, 13 physical tiles
			Total Size: 115200 [Tile0, 13:[12x395, 11:12x395, 12x60], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 13:[12x395, 11:12x395, 12x60], 2]
		Tile0: [0, 9480, 790], Tile1: [790, 9480, 790], Tile2; [1580, 9480, 790]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 13 logical tiles, 13 physical tiles
			Total Size: 115200 [Tile0, 13:[12x395, 11:12x395, 12x60], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 13:[12x395, 11:12x395, 12x60], 2]
		Tile0: [0, 9480, 9480], Tile1: [9480, 9480, 9480], Tile2; [18960, 9480, 9480]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Hin = (unsigned int ) (12);
	KerArg0->Wout = (unsigned int ) (12);
	KerArg0->Q = (unsigned char) (Q);
	KerArg0->n_classes = (unsigned short) (n_classes);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), 9480, 9600, 790, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+790), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+9480), 9480, 9600, 790, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0+0), 9480, 0, &DmaR_Evt1);
	_NN_In=790; _SN_In=9480;
	_C_Out=0; _SC_Out=9480;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	for (T0Ind=0; T0Ind<13; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
		int T0Ind_Last = (T0Ind==12), T0Ind_NextLast = ((T0Ind+1)==12), T0Ind_NextNextLast = ((T0Ind+2)==12);
		/*================================= Prepare Tiles ===================================*/
		_SNN_In = 0;
		if (!(T0Ind_Last)) {
			if (!(T0Ind_NextLast)) {
				_NN_In = _NN_In + (790); _LNN_In = ((T0Ind_NextNextLast)?120:790); _SNN_In = (12*_LNN_In); 
			}
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
		if (_SNN_In) {
			AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+9480*((T0Ind_Total)%2)),
					_SNN_In, 9600, _LNN_In, 0, &UchanHR1);
		}
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
		if (_SN_In) {
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+9480*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0+9480*((T0Ind_Total+1)%2)),
					_SN_In, 0, &DmaR_Evt1);
		}
		/*============================= End Read Tiles ======================================*/
		/*====================== Call Kernel LOC_LOOP =========================*/
		KerArg0->In = (short * __restrict__) (SSDKernels_L1_Memory+0+9480*((T0Ind_Total)%2));
		KerArg0->Win = (unsigned int ) ((T0Ind_Last)?60:395);
		KerArg0->Out = (short * __restrict__) (SSDKernels_L1_Memory+18960+9480*((T0Ind_Total)%2));
		KerArg0->Hout = (unsigned int ) (T0Ind_Last?60:395);
		AT_FORK(gap_ncore(), (void *) KerSDD3Dto2DShort, (void *) KerArg0);
		__CALL(KerSDD3Dto2DShort, KerArg0);
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
		if (_SP_Out) AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+18960+9480*((T0Ind_Total+-1)%2)),
					_SP_Out, 1, &UchanHR2);
		AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+18960+9480*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+18960+9480*((T0Ind_Total)%2)),
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
			_C_Out = _C_Out + (9480); _SC_Out = ((T0Ind_NextLast)?1440:9480); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+18960+9480*((T0Ind_Total+-1)%2)), _SP_Out, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void SDD3Dto2D_80_60_24(
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
		[Tile0 Dim: 25]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 25 logical tiles, 25 physical tiles
			Total Size: 230400 [Tile0, 25:[24x197, 23:24x197, 24x72], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 25:[24x197, 23:24x197, 24x72], 2]
		Tile0: [0, 9456, 394], Tile1: [394, 9456, 394], Tile2; [788, 9456, 394]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 25 logical tiles, 25 physical tiles
			Total Size: 230400 [Tile0, 25:[24x197, 23:24x197, 24x72], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 25:[24x197, 23:24x197, 24x72], 2]
		Tile0: [0, 9456, 9456], Tile1: [9456, 9456, 9456], Tile2; [18912, 9456, 9456]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Hin = (unsigned int ) (24);
	KerArg0->Wout = (unsigned int ) (24);
	KerArg0->Q = (unsigned char) (Q);
	KerArg0->n_classes = (unsigned short) (n_classes);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), 9456, 9600, 394, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+394), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+9456), 9456, 9600, 394, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0+0), 9456, 0, &DmaR_Evt1);
	_NN_In=394; _SN_In=9456;
	_C_Out=0; _SC_Out=9456;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	for (T0Ind=0; T0Ind<25; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
		int T0Ind_Last = (T0Ind==24), T0Ind_NextLast = ((T0Ind+1)==24), T0Ind_NextNextLast = ((T0Ind+2)==24);
		/*================================= Prepare Tiles ===================================*/
		_SNN_In = 0;
		if (!(T0Ind_Last)) {
			if (!(T0Ind_NextLast)) {
				_NN_In = _NN_In + (394); _LNN_In = ((T0Ind_NextNextLast)?144:394); _SNN_In = (24*_LNN_In); 
			}
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
		if (_SNN_In) {
			AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+9456*((T0Ind_Total)%2)),
					_SNN_In, 9600, _LNN_In, 0, &UchanHR1);
		}
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
		if (_SN_In) {
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+9456*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0+9456*((T0Ind_Total+1)%2)),
					_SN_In, 0, &DmaR_Evt1);
		}
		/*============================= End Read Tiles ======================================*/
		/*====================== Call Kernel LOC_LOOP =========================*/
		KerArg0->In = (short * __restrict__) (SSDKernels_L1_Memory+0+9456*((T0Ind_Total)%2));
		KerArg0->Win = (unsigned int ) ((T0Ind_Last)?72:197);
		KerArg0->Out = (short * __restrict__) (SSDKernels_L1_Memory+18912+9456*((T0Ind_Total)%2));
		KerArg0->Hout = (unsigned int ) (T0Ind_Last?72:197);
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
			_C_Out = _C_Out + (9456); _SC_Out = ((T0Ind_NextLast)?3456:9456); 
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
void Predecoder80_60(
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
		[Tile0 Dim: 19]
	Ker Arg: Classes, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 19 logical tiles, 19 physical tiles
			Total Size: 115200 [Tile0, 19:[2x1583, 17:2x1583, 2x306], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 19:[2x1583, 17:2x1583, 2x306], 2]
		Tile0: [0, 6332, 6332], Tile1: [6332, 6332, 6332], Tile2; [12664, 6332, 6332]
	Ker Arg: Boxes, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 19 logical tiles, 19 physical tiles
			Total Size: 230400 [Tile0, 19:[4x1583, 17:4x1583, 4x306], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 19:[4x1583, 17:4x1583, 4x306], 2]
		Tile0: [0, 12664, 12664], Tile1: [12664, 12664, 12664], Tile2; [25328, 12664, 12664]
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
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Classes+6332), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+6332), 6332, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0+0), 6332, 0, &DmaR_Evt1);
	_NN_Classes=6332; _SN_Classes=6332;
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Boxes+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+12664+0), 12664, 0, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read Boxes */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Boxes+12664), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+12664+12664), 12664, 0, &UchanHR2);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+12664+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+12664+0), 12664, 0, &DmaR_Evt2);
	_NN_Boxes=12664; _SN_Boxes=12664;
	/*============================= End Read Tiles Prolog ===============================*/
	for (T0Ind=0; T0Ind<19; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
		int T0Ind_Last = (T0Ind==18), T0Ind_NextLast = ((T0Ind+1)==18), T0Ind_NextNextLast = ((T0Ind+2)==18);
		/*================================= Prepare Tiles ===================================*/
		_SNN_Classes = 0;
		if (!(T0Ind_Last)) {
			if (!(T0Ind_NextLast)) {
				_NN_Classes = _NN_Classes + (6332); _SNN_Classes = ((T0Ind_NextNextLast)?1224:6332); 
			}
		}
		_SNN_Boxes = 0;
		if (!(T0Ind_Last)) {
			if (!(T0Ind_NextLast)) {
				_NN_Boxes = _NN_Boxes + (12664); _SNN_Boxes = ((T0Ind_NextNextLast)?2448:12664); 
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
		KerArg0->Classes_H = (unsigned int ) (T0Ind_Last?306:1583);
		KerArg0->Classes_TileIndex = (unsigned int ) ((T0Ind));
		AT_FORK(gap_ncore(), (void *) KerPredecoderShort, (void *) KerArg0);
		__CALL(KerPredecoderShort, KerArg0);
		/*================================= Update Arg Pipeline =============================*/
		_SN_Classes = _SNN_Classes;
		_SN_Boxes = _SNN_Boxes;
		/*============================= End Update Arg Pipeline =============================*/
	} /* End iteration on Tile0 */
}
void SDD3Dto2DSoftmax_40_30_14(
		short * In,
		short * Out,
		unsigned char Q,
		unsigned short n_classes)

{
	/* Shared L1: 37968 bytes, L2 buffer: 37968 bytes */
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
		[Tile0 Dim: 4]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 4 logical tiles, 4 physical tiles
			Total Size: 33600 [Tile0, 4:[14x339, 2:14x339, 14x183], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 4:[14x339, 2:14x339, 14x183], 2]
		Tile0: [0, 9492, 678], Tile1: [678, 9492, 678], Tile2; [1356, 9492, 678]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 4 logical tiles, 4 physical tiles
			Total Size: 33600 [Tile0, 4:[14x339, 2:14x339, 14x183], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 4:[14x339, 2:14x339, 14x183], 2]
		Tile0: [0, 9492, 9492], Tile1: [9492, 9492, 9492], Tile2; [18984, 9492, 9492]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Hin = (unsigned int ) (14);
	KerArg0->Wout = (unsigned int ) (14);
	KerArg0->Q = (unsigned char) (Q);
	KerArg0->n_classes = (unsigned short) (n_classes);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), 9492, 2400, 678, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+678), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+9492), 9492, 2400, 678, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0+0), 9492, 0, &DmaR_Evt1);
	_NN_In=678; _SN_In=9492;
	_C_Out=0; _SC_Out=9492;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	for (T0Ind=0; T0Ind<4; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
		int T0Ind_Last = (T0Ind==3), T0Ind_NextLast = ((T0Ind+1)==3), T0Ind_NextNextLast = ((T0Ind+2)==3);
		/*================================= Prepare Tiles ===================================*/
		_SNN_In = 0;
		if (!(T0Ind_Last)) {
			if (!(T0Ind_NextLast)) {
				_NN_In = _NN_In + (678); _LNN_In = ((T0Ind_NextNextLast)?366:678); _SNN_In = (14*_LNN_In); 
			}
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
		if (_SNN_In) {
			AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+9492*((T0Ind_Total)%2)),
					_SNN_In, 2400, _LNN_In, 0, &UchanHR1);
		}
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
		if (_SN_In) {
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+9492*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0+9492*((T0Ind_Total+1)%2)),
					_SN_In, 0, &DmaR_Evt1);
		}
		/*============================= End Read Tiles ======================================*/
		/*====================== Call Kernel LOC_LOOP =========================*/
		KerArg0->In = (short * __restrict__) (SSDKernels_L1_Memory+0+9492*((T0Ind_Total)%2));
		KerArg0->Win = (unsigned int ) ((T0Ind_Last)?183:339);
		KerArg0->Out = (short * __restrict__) (SSDKernels_L1_Memory+18984+9492*((T0Ind_Total)%2));
		KerArg0->Hout = (unsigned int ) (T0Ind_Last?183:339);
		AT_FORK(gap_ncore(), (void *) KerSDD3Dto2DShort, (void *) KerArg0);
		__CALL(KerSDD3Dto2DShort, KerArg0);
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
		if (_SP_Out) AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+18984+9492*((T0Ind_Total+-1)%2)),
					_SP_Out, 1, &UchanHR2);
		AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+18984+9492*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+18984+9492*((T0Ind_Total)%2)),
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
			_C_Out = _C_Out + (9492); _SC_Out = ((T0Ind_NextLast)?5124:9492); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+18984+9492*((T0Ind_Total+-1)%2)), _SP_Out, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void SDD3Dto2D_40_30_28(
		short * In,
		short * Out,
		unsigned char Q,
		unsigned short n_classes)

{
	/* Shared L1: 37856 bytes, L2 buffer: 37856 bytes */
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
		[Tile0 Dim: 8]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 8 logical tiles, 8 physical tiles
			Total Size: 67200 [Tile0, 8:[28x169, 6:28x169, 28x17], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 8:[28x169, 6:28x169, 28x17], 2]
		Tile0: [0, 9464, 338], Tile1: [338, 9464, 338], Tile2; [676, 9464, 338]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 8 logical tiles, 8 physical tiles
			Total Size: 67200 [Tile0, 8:[28x169, 6:28x169, 28x17], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 8:[28x169, 6:28x169, 28x17], 2]
		Tile0: [0, 9464, 9464], Tile1: [9464, 9464, 9464], Tile2; [18928, 9464, 9464]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Hin = (unsigned int ) (28);
	KerArg0->Wout = (unsigned int ) (28);
	KerArg0->Q = (unsigned char) (Q);
	KerArg0->n_classes = (unsigned short) (n_classes);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), 9464, 2400, 338, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+338), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+9464), 9464, 2400, 338, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0+0), 9464, 0, &DmaR_Evt1);
	_NN_In=338; _SN_In=9464;
	_C_Out=0; _SC_Out=9464;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	for (T0Ind=0; T0Ind<8; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
		int T0Ind_Last = (T0Ind==7), T0Ind_NextLast = ((T0Ind+1)==7), T0Ind_NextNextLast = ((T0Ind+2)==7);
		/*================================= Prepare Tiles ===================================*/
		_SNN_In = 0;
		if (!(T0Ind_Last)) {
			if (!(T0Ind_NextLast)) {
				_NN_In = _NN_In + (338); _LNN_In = ((T0Ind_NextNextLast)?34:338); _SNN_In = (28*_LNN_In); 
			}
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
		if (_SNN_In) {
			AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+9464*((T0Ind_Total)%2)),
					_SNN_In, 2400, _LNN_In, 0, &UchanHR1);
		}
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
		if (_SN_In) {
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+9464*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0+9464*((T0Ind_Total+1)%2)),
					_SN_In, 0, &DmaR_Evt1);
		}
		/*============================= End Read Tiles ======================================*/
		/*====================== Call Kernel LOC_LOOP =========================*/
		KerArg0->In = (short * __restrict__) (SSDKernels_L1_Memory+0+9464*((T0Ind_Total)%2));
		KerArg0->Win = (unsigned int ) ((T0Ind_Last)?17:169);
		KerArg0->Out = (short * __restrict__) (SSDKernels_L1_Memory+18928+9464*((T0Ind_Total)%2));
		KerArg0->Hout = (unsigned int ) (T0Ind_Last?17:169);
		AT_FORK(gap_ncore(), (void *) KerSDD3Dto2DShort, (void *) KerArg0);
		__CALL(KerSDD3Dto2DShort, KerArg0);
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
		if (_SP_Out) AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+18928+9464*((T0Ind_Total+-1)%2)),
					_SP_Out, 1, &UchanHR2);
		AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+18928+9464*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+18928+9464*((T0Ind_Total)%2)),
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
			_C_Out = _C_Out + (9464); _SC_Out = ((T0Ind_NextLast)?952:9464); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+18928+9464*((T0Ind_Total+-1)%2)), _SP_Out, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void Predecoder40_30(
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
		[Tile0 Dim: 6]
	Ker Arg: Classes, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 6 logical tiles, 6 physical tiles
			Total Size: 33600 [Tile0, 6:[2x1583, 4:2x1583, 2x485], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 6:[2x1583, 4:2x1583, 2x485], 2]
		Tile0: [0, 6332, 6332], Tile1: [6332, 6332, 6332], Tile2; [12664, 6332, 6332]
	Ker Arg: Boxes, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 6 logical tiles, 6 physical tiles
			Total Size: 67200 [Tile0, 6:[4x1583, 4:4x1583, 4x485], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 6:[4x1583, 4:4x1583, 4x485], 2]
		Tile0: [0, 12664, 12664], Tile1: [12664, 12664, 12664], Tile2; [25328, 12664, 12664]
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
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Classes+6332), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+6332), 6332, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0+0), 6332, 0, &DmaR_Evt1);
	_NN_Classes=6332; _SN_Classes=6332;
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Boxes+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+12664+0), 12664, 0, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read Boxes */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Boxes+12664), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+12664+12664), 12664, 0, &UchanHR2);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+12664+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+12664+0), 12664, 0, &DmaR_Evt2);
	_NN_Boxes=12664; _SN_Boxes=12664;
	/*============================= End Read Tiles Prolog ===============================*/
	for (T0Ind=0; T0Ind<6; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
		int T0Ind_Last = (T0Ind==5), T0Ind_NextLast = ((T0Ind+1)==5), T0Ind_NextNextLast = ((T0Ind+2)==5);
		/*================================= Prepare Tiles ===================================*/
		_SNN_Classes = 0;
		if (!(T0Ind_Last)) {
			if (!(T0Ind_NextLast)) {
				_NN_Classes = _NN_Classes + (6332); _SNN_Classes = ((T0Ind_NextNextLast)?1940:6332); 
			}
		}
		_SNN_Boxes = 0;
		if (!(T0Ind_Last)) {
			if (!(T0Ind_NextLast)) {
				_NN_Boxes = _NN_Boxes + (12664); _SNN_Boxes = ((T0Ind_NextNextLast)?3880:12664); 
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
		KerArg0->Classes_H = (unsigned int ) (T0Ind_Last?485:1583);
		KerArg0->Classes_TileIndex = (unsigned int ) ((T0Ind));
		AT_FORK(gap_ncore(), (void *) KerPredecoderShort, (void *) KerArg0);
		__CALL(KerPredecoderShort, KerArg0);
		/*================================= Update Arg Pipeline =============================*/
		_SN_Classes = _SNN_Classes;
		_SN_Boxes = _SNN_Boxes;
		/*============================= End Update Arg Pipeline =============================*/
	} /* End iteration on Tile0 */
}
void SDD3Dto2DSoftmax_20_15_16(
		short * In,
		short * Out,
		unsigned char Q,
		unsigned short n_classes)

{
	/* Shared L1: 37888 bytes, L2 buffer: 37888 bytes */
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
			Total Size: 9600 [Tile0, 2:[16x296, 16x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 2:[16x296, 16x4], 2]
		Tile0: [0, 9472, 592], Tile1: [592, 128, 8], Tile2; [0, 9472, 592]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 2 physical tiles
			Total Size: 9600 [Tile0, 2:[16x296, 16x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 2:[16x296, 16x4], 2]
		Tile0: [0, 9472, 9472], Tile1: [9472, 128, 128], Tile2; [0, 9472, 9472]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Hin = (unsigned int ) (16);
	KerArg0->Wout = (unsigned int ) (16);
	KerArg0->Q = (unsigned char) (Q);
	KerArg0->n_classes = (unsigned short) (n_classes);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), 9472, 600, 592, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+592), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+9472), 128, 600, 8, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0+0), 9472, 0, &DmaR_Evt1);
	_NN_In=592; _SN_In=128;
	_C_Out=0; _SC_Out=9472;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	for (T0Ind=0; T0Ind<2; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
		int T0Ind_Last = (T0Ind==1), T0Ind_NextLast = ((T0Ind+1)==1), T0Ind_NextNextLast = ((T0Ind+2)==1);
		/*================================= Prepare Tiles ===================================*/
		_SNN_In = 0;
		if (!(T0Ind_Last)) {
			if (!(1)) {
				_NN_In = _NN_In + (592); _LNN_In = ((1)?8:592); _SNN_In = (16*_LNN_In); 
			}
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
		if (_SNN_In) {
			AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+9472*((T0Ind_Total)%2)),
					_SNN_In, 600, _LNN_In, 0, &UchanHR1);
		}
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
		if (_SN_In) {
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+9472*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0+9472*((T0Ind_Total+1)%2)),
					_SN_In, 0, &DmaR_Evt1);
		}
		/*============================= End Read Tiles ======================================*/
		/*====================== Call Kernel LOC_LOOP =========================*/
		KerArg0->In = (short * __restrict__) (SSDKernels_L1_Memory+0+9472*((T0Ind_Total)%2));
		KerArg0->Win = (unsigned int ) ((T0Ind_Last)?4:296);
		KerArg0->Out = (short * __restrict__) (SSDKernels_L1_Memory+18944+9472*((T0Ind_Total)%2));
		KerArg0->Hout = (unsigned int ) (T0Ind_Last?4:296);
		AT_FORK(gap_ncore(), (void *) KerSDD3Dto2DShort, (void *) KerArg0);
		__CALL(KerSDD3Dto2DShort, KerArg0);
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
		if (_SP_Out) AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+18944+9472*((T0Ind_Total+-1)%2)),
					_SP_Out, 1, &UchanHR2);
		AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+18944+9472*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+18944+9472*((T0Ind_Total)%2)),
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
			_C_Out = _C_Out + (9472); _SC_Out = ((1)?128:9472); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+18944+9472*((T0Ind_Total+-1)%2)), _SP_Out, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void SDD3Dto2D_20_15_32(
		short * In,
		short * Out,
		unsigned char Q,
		unsigned short n_classes)

{
	/* Shared L1: 37888 bytes, L2 buffer: 37888 bytes */
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
		[Tile0 Dim: 3]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 3 logical tiles, 3 physical tiles
			Total Size: 19200 [Tile0, 3:[32x148, 1:32x148, 32x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 3:[32x148, 1:32x148, 32x4], 2]
		Tile0: [0, 9472, 296], Tile1: [296, 9472, 296], Tile2; [592, 256, 8]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 3 logical tiles, 3 physical tiles
			Total Size: 19200 [Tile0, 3:[32x148, 1:32x148, 32x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 3:[32x148, 1:32x148, 32x4], 2]
		Tile0: [0, 9472, 9472], Tile1: [9472, 9472, 9472], Tile2; [18944, 256, 256]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Hin = (unsigned int ) (32);
	KerArg0->Wout = (unsigned int ) (32);
	KerArg0->Q = (unsigned char) (Q);
	KerArg0->n_classes = (unsigned short) (n_classes);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), 9472, 600, 296, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+296), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+9472), 9472, 600, 296, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0+0), 9472, 0, &DmaR_Evt1);
	_NN_In=296; _SN_In=9472;
	_C_Out=0; _SC_Out=9472;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	for (T0Ind=0; T0Ind<3; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
		int T0Ind_Last = (T0Ind==2), T0Ind_NextLast = ((T0Ind+1)==2), T0Ind_NextNextLast = ((T0Ind+2)==2);
		/*================================= Prepare Tiles ===================================*/
		_SNN_In = 0;
		if (!(T0Ind_Last)) {
			if (!(T0Ind_NextLast)) {
				_NN_In = _NN_In + (296); _LNN_In = ((1)?8:296); _SNN_In = (32*_LNN_In); 
			}
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
		if (_SNN_In) {
			AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+9472*((T0Ind_Total)%2)),
					_SNN_In, 600, _LNN_In, 0, &UchanHR1);
		}
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
		if (_SN_In) {
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+9472*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0+9472*((T0Ind_Total+1)%2)),
					_SN_In, 0, &DmaR_Evt1);
		}
		/*============================= End Read Tiles ======================================*/
		/*====================== Call Kernel LOC_LOOP =========================*/
		KerArg0->In = (short * __restrict__) (SSDKernels_L1_Memory+0+9472*((T0Ind_Total)%2));
		KerArg0->Win = (unsigned int ) ((T0Ind_Last)?4:148);
		KerArg0->Out = (short * __restrict__) (SSDKernels_L1_Memory+18944+9472*((T0Ind_Total)%2));
		KerArg0->Hout = (unsigned int ) (T0Ind_Last?4:148);
		AT_FORK(gap_ncore(), (void *) KerSDD3Dto2DShort, (void *) KerArg0);
		__CALL(KerSDD3Dto2DShort, KerArg0);
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
		if (_SP_Out) AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+18944+9472*((T0Ind_Total+-1)%2)),
					_SP_Out, 1, &UchanHR2);
		AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+18944+9472*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+18944+9472*((T0Ind_Total)%2)),
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
			_C_Out = _C_Out + (9472); _SC_Out = ((T0Ind_NextLast)?256:9472); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+18944+9472*((T0Ind_Total+-1)%2)), _SP_Out, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void Predecoder20_15(
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
			Total Size: 9600 [Tile0, 2:[2x1583, 2x817], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 2:[2x1583, 2x817], 2]
		Tile0: [0, 6332, 6332], Tile1: [6332, 3268, 3268], Tile2; [0, 6332, 6332]
	Ker Arg: Boxes, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 2 logical tiles, 2 physical tiles
			Total Size: 19200 [Tile0, 2:[4x1583, 4x817], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 2:[4x1583, 4x817], 2]
		Tile0: [0, 12664, 12664], Tile1: [12664, 6536, 6536], Tile2; [0, 12664, 12664]
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
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Classes+6332), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+6332), 3268, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0+0), 6332, 0, &DmaR_Evt1);
	_NN_Classes=6332; _SN_Classes=3268;
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Boxes+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+12664+0), 12664, 0, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read Boxes */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Boxes+12664), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+12664+12664), 6536, 0, &UchanHR2);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+12664+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+12664+0), 12664, 0, &DmaR_Evt2);
	_NN_Boxes=12664; _SN_Boxes=6536;
	/*============================= End Read Tiles Prolog ===============================*/
	for (T0Ind=0; T0Ind<2; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
		int T0Ind_Last = (T0Ind==1), T0Ind_NextLast = ((T0Ind+1)==1), T0Ind_NextNextLast = ((T0Ind+2)==1);
		/*================================= Prepare Tiles ===================================*/
		_SNN_Classes = 0;
		if (!(T0Ind_Last)) {
			if (!(1)) {
				_NN_Classes = _NN_Classes + (6332); _SNN_Classes = ((1)?3268:6332); 
			}
		}
		_SNN_Boxes = 0;
		if (!(T0Ind_Last)) {
			if (!(1)) {
				_NN_Boxes = _NN_Boxes + (12664); _SNN_Boxes = ((1)?6536:12664); 
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
		KerArg0->Classes_H = (unsigned int ) (T0Ind_Last?817:1583);
		KerArg0->Classes_TileIndex = (unsigned int ) ((T0Ind));
		AT_FORK(gap_ncore(), (void *) KerPredecoderShort, (void *) KerArg0);
		__CALL(KerPredecoderShort, KerArg0);
		/*================================= Update Arg Pipeline =============================*/
		_SN_Classes = _SNN_Classes;
		_SN_Boxes = _SNN_Boxes;
		/*============================= End Update Arg Pipeline =============================*/
	} /* End iteration on Tile0 */
}
void SDD3Dto2DSoftmax_10_7_14(
		short * In,
		short * Out,
		unsigned char Q,
		unsigned short n_classes)

{
	/* Shared L1: 3920 bytes, L2 buffer: 3920 bytes */
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
			Total Size: 1960 [Tile0, 1:[14x70], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[14x70], 2]
		Tile0: [0, 1960, 1960], Tile1: [0, 1960, 1960], Tile2; [0, 1960, 1960]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 1960 [Tile0, 1:[14x70], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[14x70], 2]
		Tile0: [0, 1960, 1960], Tile1: [0, 1960, 1960], Tile2; [0, 1960, 1960]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (short * __restrict__) (SSDKernels_L1_Memory+0);
	KerArg0->Win = (unsigned int ) (70);
	KerArg0->Hin = (unsigned int ) (14);
	KerArg0->Out = (short * __restrict__) (SSDKernels_L1_Memory+1960);
	KerArg0->Wout = (unsigned int ) (14);
	KerArg0->Hout = (unsigned int ) (70);
	KerArg0->Q = (unsigned char) (Q);
	KerArg0->n_classes = (unsigned short) (n_classes);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), 1960, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0), 1960, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile0 */
		int T0Ind_Last = 1;
		/*====================== Call Kernel LOC_LOOP =========================*/
		AT_FORK(gap_ncore(), (void *) KerSDD3Dto2DShort, (void *) KerArg0);
		__CALL(KerSDD3Dto2DShort, KerArg0);
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+1960+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+1960), 1960, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+1960+0), 1960, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void SDD3Dto2D_10_7_28(
		short * In,
		short * Out,
		unsigned char Q,
		unsigned short n_classes)

{
	/* Shared L1: 7840 bytes, L2 buffer: 7840 bytes */
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
			Total Size: 3920 [Tile0, 1:[28x70], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[28x70], 2]
		Tile0: [0, 3920, 3920], Tile1: [0, 3920, 3920], Tile2; [0, 3920, 3920]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 3920 [Tile0, 1:[28x70], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[28x70], 2]
		Tile0: [0, 3920, 3920], Tile1: [0, 3920, 3920], Tile2; [0, 3920, 3920]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (short * __restrict__) (SSDKernels_L1_Memory+0);
	KerArg0->Win = (unsigned int ) (70);
	KerArg0->Hin = (unsigned int ) (28);
	KerArg0->Out = (short * __restrict__) (SSDKernels_L1_Memory+3920);
	KerArg0->Wout = (unsigned int ) (28);
	KerArg0->Hout = (unsigned int ) (70);
	KerArg0->Q = (unsigned char) (Q);
	KerArg0->n_classes = (unsigned short) (n_classes);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), 3920, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0), 3920, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile0 */
		int T0Ind_Last = 1;
		/*====================== Call Kernel LOC_LOOP =========================*/
		AT_FORK(gap_ncore(), (void *) KerSDD3Dto2DShort, (void *) KerArg0);
		__CALL(KerSDD3Dto2DShort, KerArg0);
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+3920+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+3920), 3920, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+3920+0), 3920, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void Predecoder10_7(
		short * Classes,
		short * Boxes,
		void  * Ancor_layer,
		void  * BoundingBoxes,
		int Boxes_Q)

{
	/* Shared L1: 5880 bytes, L2 buffer: 5880 bytes */
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
			Total Size: 1960 [Tile0, 1:[2x490], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[2x490], 2]
		Tile0: [0, 1960, 1960], Tile1: [0, 1960, 1960], Tile2; [0, 1960, 1960]
	Ker Arg: Boxes, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 3920 [Tile0, 1:[4x490], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[4x490], 2]
		Tile0: [0, 3920, 3920], Tile1: [0, 3920, 3920], Tile2; [0, 3920, 3920]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Classes = (short * __restrict__) (SSDKernels_L1_Memory+0);
	KerArg0->Boxes = (short * __restrict__) (SSDKernels_L1_Memory+1960);
	KerArg0->Classes_W = (unsigned int ) (2);
	KerArg0->Classes_H = (unsigned int ) (490);
	KerArg0->Classes_TileIndex = (unsigned int ) ((0));
	KerArg0->Classes_Std_H = (unsigned int ) (490);
	KerArg0->Ancor_layer = (void  * __restrict__) (Ancor_layer);
	KerArg0->BoundingBoxes = (void  * __restrict__) (BoundingBoxes);
	KerArg0->Boxes_Q = (int) (Boxes_Q);
	KerArg0->n_classes = (unsigned int ) (2);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Classes+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), 1960, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read Classes */
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0), 1960, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Classes */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Boxes+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+1960+0), 3920, 0, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read Boxes */
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+1960+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+1960), 3920, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Boxes */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile0 */
		int T0Ind_Last = 1;
		/*====================== Call Kernel LOC_LOOP =========================*/
		AT_FORK(gap_ncore(), (void *) KerPredecoderShort, (void *) KerArg0);
		__CALL(KerPredecoderShort, KerArg0);
	} /* End iteration on Tile0 */
}
