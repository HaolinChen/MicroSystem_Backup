#include "SSDKernels.h"
L1_CL_MEM AT_L1_POINTER SSDKernels_L1_Memory;
L2_MEM AT_L2_POINTER SSDKernels_L2_Memory;
AT_HYPERRAM_POINTER SSDKernels_L3_Memory;
extern AT_HYPERRAM_T HyperRam;
void SDD3Dto2DSoftmax_20_16_18(
		short * In,
		short * Out,
		unsigned char Q,
		unsigned short n_classes)

{
	/* Shared L1: 9936 bytes, L2 buffer: 9936 bytes */
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
		[Tile0 Dim: 5]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 5 logical tiles, 5 physical tiles
			Total Size: 11520 [Tile0, 5:[18x69, 3:18x69, 18x44], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 5:[18x69, 3:18x69, 18x44], 2]
		Tile0: [0, 2484, 138], Tile1: [138, 2484, 138], Tile2; [276, 2484, 138]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 5 logical tiles, 5 physical tiles
			Total Size: 11520 [Tile0, 5:[18x69, 3:18x69, 18x44], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 5:[18x69, 3:18x69, 18x44], 2]
		Tile0: [0, 2484, 2484], Tile1: [2484, 2484, 2484], Tile2; [4968, 2484, 2484]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Hin = (unsigned int ) (18);
	KerArg0->Wout = (unsigned int ) (18);
	KerArg0->Q = (unsigned char) (Q);
	KerArg0->n_classes = (unsigned short) (n_classes);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), 2484, 640, 138, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+138), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+2484), 2484, 640, 138, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0+0), 2484, 0, &DmaR_Evt1);
	_NN_In=138; _SN_In=2484;
	_C_Out=0; _SC_Out=2484;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	for (T0Ind=0; T0Ind<5; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
		int T0Ind_Last = (T0Ind==4), T0Ind_NextLast = ((T0Ind+1)==4), T0Ind_NextNextLast = ((T0Ind+2)==4);
		/*================================= Prepare Tiles ===================================*/
		_SNN_In = 0;
		if (!(T0Ind_Last)) {
			if (!(T0Ind_NextLast)) {
				_NN_In = _NN_In + (138); _LNN_In = ((T0Ind_NextNextLast)?88:138); _SNN_In = (18*_LNN_In); 
			}
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
		if (_SNN_In) {
			AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+2484*((T0Ind_Total)%2)),
					_SNN_In, 640, _LNN_In, 0, &UchanHR1);
		}
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
		if (_SN_In) {
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+2484*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0+2484*((T0Ind_Total+1)%2)),
					_SN_In, 0, &DmaR_Evt1);
		}
		/*============================= End Read Tiles ======================================*/
		/*====================== Call Kernel LOC_LOOP =========================*/
		KerArg0->In = (short * __restrict__) (SSDKernels_L1_Memory+0+2484*((T0Ind_Total)%2));
		KerArg0->Win = (unsigned int ) ((T0Ind_Last)?44:69);
		KerArg0->Out = (short * __restrict__) (SSDKernels_L1_Memory+4968+2484*((T0Ind_Total)%2));
		KerArg0->Hout = (unsigned int ) (T0Ind_Last?44:69);
		AT_FORK(gap_ncore(), (void *) KerSDD3Dto2DShort, (void *) KerArg0);
		__CALL(KerSDD3Dto2DShort, KerArg0);
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
		if (_SP_Out) AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+4968+2484*((T0Ind_Total+-1)%2)),
					_SP_Out, 1, &UchanHR2);
		AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+4968+2484*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+4968+2484*((T0Ind_Total)%2)),
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
			_C_Out = _C_Out + (2484); _SC_Out = ((T0Ind_NextLast)?1584:2484); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+4968+2484*((T0Ind_Total+-1)%2)), _SP_Out, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void SDD3Dto2D_20_16_24(
		short * In,
		short * Out,
		unsigned char Q,
		unsigned short n_classes)

{
	/* Shared L1: 9984 bytes, L2 buffer: 9984 bytes */
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
		[Tile0 Dim: 7]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 7 logical tiles, 7 physical tiles
			Total Size: 15360 [Tile0, 7:[24x52, 5:24x52, 24x8], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 7:[24x52, 5:24x52, 24x8], 2]
		Tile0: [0, 2496, 104], Tile1: [104, 2496, 104], Tile2; [208, 2496, 104]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 7 logical tiles, 7 physical tiles
			Total Size: 15360 [Tile0, 7:[24x52, 5:24x52, 24x8], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 7:[24x52, 5:24x52, 24x8], 2]
		Tile0: [0, 2496, 2496], Tile1: [2496, 2496, 2496], Tile2; [4992, 2496, 2496]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Hin = (unsigned int ) (24);
	KerArg0->Wout = (unsigned int ) (24);
	KerArg0->Q = (unsigned char) (Q);
	KerArg0->n_classes = (unsigned short) (n_classes);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), 2496, 640, 104, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+104), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+2496), 2496, 640, 104, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0+0), 2496, 0, &DmaR_Evt1);
	_NN_In=104; _SN_In=2496;
	_C_Out=0; _SC_Out=2496;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	for (T0Ind=0; T0Ind<7; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
		int T0Ind_Last = (T0Ind==6), T0Ind_NextLast = ((T0Ind+1)==6), T0Ind_NextNextLast = ((T0Ind+2)==6);
		/*================================= Prepare Tiles ===================================*/
		_SNN_In = 0;
		if (!(T0Ind_Last)) {
			if (!(T0Ind_NextLast)) {
				_NN_In = _NN_In + (104); _LNN_In = ((T0Ind_NextNextLast)?16:104); _SNN_In = (24*_LNN_In); 
			}
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
		if (_SNN_In) {
			AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+2496*((T0Ind_Total)%2)),
					_SNN_In, 640, _LNN_In, 0, &UchanHR1);
		}
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
		if (_SN_In) {
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+2496*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0+2496*((T0Ind_Total+1)%2)),
					_SN_In, 0, &DmaR_Evt1);
		}
		/*============================= End Read Tiles ======================================*/
		/*====================== Call Kernel LOC_LOOP =========================*/
		KerArg0->In = (short * __restrict__) (SSDKernels_L1_Memory+0+2496*((T0Ind_Total)%2));
		KerArg0->Win = (unsigned int ) ((T0Ind_Last)?8:52);
		KerArg0->Out = (short * __restrict__) (SSDKernels_L1_Memory+4992+2496*((T0Ind_Total)%2));
		KerArg0->Hout = (unsigned int ) (T0Ind_Last?8:52);
		AT_FORK(gap_ncore(), (void *) KerSDD3Dto2DShort, (void *) KerArg0);
		__CALL(KerSDD3Dto2DShort, KerArg0);
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
		if (_SP_Out) AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+4992+2496*((T0Ind_Total+-1)%2)),
					_SP_Out, 1, &UchanHR2);
		AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+4992+2496*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+4992+2496*((T0Ind_Total)%2)),
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
			_C_Out = _C_Out + (2496); _SC_Out = ((T0Ind_NextLast)?384:2496); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+4992+2496*((T0Ind_Total+-1)%2)), _SP_Out, 1, &UchanHR2);
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
	/* Shared L1: 10000 bytes, L2 buffer: 10000 bytes */
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
			Total Size: 11520 [Tile0, 6:[3x357, 4:3x357, 3x135], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 6:[3x357, 4:3x357, 3x135], 2]
		Tile0: [0, 2142, 2142], Tile1: [2142, 2142, 2142], Tile2; [4284, 2142, 2142]
	Ker Arg: Boxes, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 6 logical tiles, 6 physical tiles
			Total Size: 15360 [Tile0, 6:[4x357, 4:4x357, 4x135], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 6:[4x357, 4:4x357, 4x135], 2]
		Tile0: [0, 2856, 2856], Tile1: [2856, 2856, 2856], Tile2; [5712, 2856, 2856]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Classes_W = (unsigned int ) (3);
	KerArg0->Classes_Std_H = (unsigned int ) (357);
	KerArg0->Ancor_layer = (void  * __restrict__) (Ancor_layer);
	KerArg0->BoundingBoxes = (void  * __restrict__) (BoundingBoxes);
	KerArg0->Boxes_Q = (int) (Boxes_Q);
	KerArg0->n_classes = (unsigned int ) (3);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Classes+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), 2142, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read Classes */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Classes+2142), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+2144), 2142, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0+0), 2142, 0, &DmaR_Evt1);
	_NN_Classes=2142; _SN_Classes=2142;
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Boxes+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+4288+0), 2856, 0, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read Boxes */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Boxes+2856), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+4288+2856), 2856, 0, &UchanHR2);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+4288+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+4288+0), 2856, 0, &DmaR_Evt2);
	_NN_Boxes=2856; _SN_Boxes=2856;
	/*============================= End Read Tiles Prolog ===============================*/
	for (T0Ind=0; T0Ind<6; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
		int T0Ind_Last = (T0Ind==5), T0Ind_NextLast = ((T0Ind+1)==5), T0Ind_NextNextLast = ((T0Ind+2)==5);
		/*================================= Prepare Tiles ===================================*/
		_SNN_Classes = 0;
		if (!(T0Ind_Last)) {
			if (!(T0Ind_NextLast)) {
				_NN_Classes = _NN_Classes + (2142); _SNN_Classes = ((T0Ind_NextNextLast)?810:2142); 
			}
		}
		_SNN_Boxes = 0;
		if (!(T0Ind_Last)) {
			if (!(T0Ind_NextLast)) {
				_NN_Boxes = _NN_Boxes + (2856); _SNN_Boxes = ((T0Ind_NextNextLast)?1080:2856); 
			}
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read Classes */
		if (_SNN_Classes) {
			AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Classes+_NN_Classes), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+2144*((T0Ind_Total)%2)),
					_SNN_Classes, 0, &UchanHR1);
		}
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Classes */
		if (_SN_Classes) {
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+2144*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0+2144*((T0Ind_Total+1)%2)),
					_SN_Classes, 0, &DmaR_Evt1);
		}
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read Boxes */
		if (_SNN_Boxes) {
			AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Boxes+_NN_Boxes), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+4288+2856*((T0Ind_Total)%2)),
					_SNN_Boxes, 0, &UchanHR2);
		}
		AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Boxes */
		if (_SN_Boxes) {
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+4288+2856*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+4288+2856*((T0Ind_Total+1)%2)),
					_SN_Boxes, 0, &DmaR_Evt2);
		}
		/*============================= End Read Tiles ======================================*/
		/*====================== Call Kernel LOC_LOOP =========================*/
		KerArg0->Classes = (short * __restrict__) (SSDKernels_L1_Memory+0+2144*((T0Ind_Total)%2));
		KerArg0->Boxes = (short * __restrict__) (SSDKernels_L1_Memory+4288+2856*((T0Ind_Total)%2));
		KerArg0->Classes_H = (unsigned int ) (T0Ind_Last?135:357);
		KerArg0->Classes_TileIndex = (unsigned int ) ((T0Ind));
		AT_FORK(gap_ncore(), (void *) KerPredecoderShort, (void *) KerArg0);
		__CALL(KerPredecoderShort, KerArg0);
		/*================================= Update Arg Pipeline =============================*/
		_SN_Classes = _SNN_Classes;
		_SN_Boxes = _SNN_Boxes;
		/*============================= End Update Arg Pipeline =============================*/
	} /* End iteration on Tile0 */
}
void SDD3Dto2DSoftmax_10_8_18(
		short * In,
		short * Out,
		unsigned char Q,
		unsigned short n_classes)

{
	/* Shared L1: 9936 bytes, L2 buffer: 9936 bytes */
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
			Total Size: 2880 [Tile0, 2:[18x69, 18x11], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 2:[18x69, 18x11], 2]
		Tile0: [0, 2484, 138], Tile1: [138, 396, 22], Tile2; [0, 2484, 138]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 2 physical tiles
			Total Size: 2880 [Tile0, 2:[18x69, 18x11], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 2:[18x69, 18x11], 2]
		Tile0: [0, 2484, 2484], Tile1: [2484, 396, 396], Tile2; [0, 2484, 2484]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Hin = (unsigned int ) (18);
	KerArg0->Wout = (unsigned int ) (18);
	KerArg0->Q = (unsigned char) (Q);
	KerArg0->n_classes = (unsigned short) (n_classes);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), 2484, 160, 138, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+138), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+2484), 396, 160, 22, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0+0), 2484, 0, &DmaR_Evt1);
	_NN_In=138; _SN_In=396;
	_C_Out=0; _SC_Out=2484;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	for (T0Ind=0; T0Ind<2; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
		int T0Ind_Last = (T0Ind==1), T0Ind_NextLast = ((T0Ind+1)==1), T0Ind_NextNextLast = ((T0Ind+2)==1);
		/*================================= Prepare Tiles ===================================*/
		_SNN_In = 0;
		if (!(T0Ind_Last)) {
			if (!(1)) {
				_NN_In = _NN_In + (138); _LNN_In = ((1)?22:138); _SNN_In = (18*_LNN_In); 
			}
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
		if (_SNN_In) {
			AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+2484*((T0Ind_Total)%2)),
					_SNN_In, 160, _LNN_In, 0, &UchanHR1);
		}
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
		if (_SN_In) {
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+2484*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0+2484*((T0Ind_Total+1)%2)),
					_SN_In, 0, &DmaR_Evt1);
		}
		/*============================= End Read Tiles ======================================*/
		/*====================== Call Kernel LOC_LOOP =========================*/
		KerArg0->In = (short * __restrict__) (SSDKernels_L1_Memory+0+2484*((T0Ind_Total)%2));
		KerArg0->Win = (unsigned int ) ((T0Ind_Last)?11:69);
		KerArg0->Out = (short * __restrict__) (SSDKernels_L1_Memory+4968+2484*((T0Ind_Total)%2));
		KerArg0->Hout = (unsigned int ) (T0Ind_Last?11:69);
		AT_FORK(gap_ncore(), (void *) KerSDD3Dto2DShort, (void *) KerArg0);
		__CALL(KerSDD3Dto2DShort, KerArg0);
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
		if (_SP_Out) AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+4968+2484*((T0Ind_Total+-1)%2)),
					_SP_Out, 1, &UchanHR2);
		AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+4968+2484*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+4968+2484*((T0Ind_Total)%2)),
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
			_C_Out = _C_Out + (2484); _SC_Out = ((1)?396:2484); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+4968+2484*((T0Ind_Total+-1)%2)), _SP_Out, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void SDD3Dto2D_10_8_24(
		short * In,
		short * Out,
		unsigned char Q,
		unsigned short n_classes)

{
	/* Shared L1: 9984 bytes, L2 buffer: 9984 bytes */
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
			Total Size: 3840 [Tile0, 2:[24x52, 24x28], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 2:[24x52, 24x28], 2]
		Tile0: [0, 2496, 104], Tile1: [104, 1344, 56], Tile2; [0, 2496, 104]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 2 physical tiles
			Total Size: 3840 [Tile0, 2:[24x52, 24x28], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 2:[24x52, 24x28], 2]
		Tile0: [0, 2496, 2496], Tile1: [2496, 1344, 1344], Tile2; [0, 2496, 2496]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Hin = (unsigned int ) (24);
	KerArg0->Wout = (unsigned int ) (24);
	KerArg0->Q = (unsigned char) (Q);
	KerArg0->n_classes = (unsigned short) (n_classes);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), 2496, 160, 104, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+104), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+2496), 1344, 160, 56, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0+0), 2496, 0, &DmaR_Evt1);
	_NN_In=104; _SN_In=1344;
	_C_Out=0; _SC_Out=2496;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	for (T0Ind=0; T0Ind<2; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
		int T0Ind_Last = (T0Ind==1), T0Ind_NextLast = ((T0Ind+1)==1), T0Ind_NextNextLast = ((T0Ind+2)==1);
		/*================================= Prepare Tiles ===================================*/
		_SNN_In = 0;
		if (!(T0Ind_Last)) {
			if (!(1)) {
				_NN_In = _NN_In + (104); _LNN_In = ((1)?56:104); _SNN_In = (24*_LNN_In); 
			}
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
		if (_SNN_In) {
			AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+2496*((T0Ind_Total)%2)),
					_SNN_In, 160, _LNN_In, 0, &UchanHR1);
		}
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
		if (_SN_In) {
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+2496*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0+2496*((T0Ind_Total+1)%2)),
					_SN_In, 0, &DmaR_Evt1);
		}
		/*============================= End Read Tiles ======================================*/
		/*====================== Call Kernel LOC_LOOP =========================*/
		KerArg0->In = (short * __restrict__) (SSDKernels_L1_Memory+0+2496*((T0Ind_Total)%2));
		KerArg0->Win = (unsigned int ) ((T0Ind_Last)?28:52);
		KerArg0->Out = (short * __restrict__) (SSDKernels_L1_Memory+4992+2496*((T0Ind_Total)%2));
		KerArg0->Hout = (unsigned int ) (T0Ind_Last?28:52);
		AT_FORK(gap_ncore(), (void *) KerSDD3Dto2DShort, (void *) KerArg0);
		__CALL(KerSDD3Dto2DShort, KerArg0);
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
		if (_SP_Out) AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+4992+2496*((T0Ind_Total+-1)%2)),
					_SP_Out, 1, &UchanHR2);
		AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+4992+2496*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+4992+2496*((T0Ind_Total)%2)),
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
			_C_Out = _C_Out + (2496); _SC_Out = ((1)?1344:2496); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+4992+2496*((T0Ind_Total+-1)%2)), _SP_Out, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void Predecoder10_8(
		short * Classes,
		short * Boxes,
		void  * Ancor_layer,
		void  * BoundingBoxes,
		int Boxes_Q)

{
	/* Shared L1: 10000 bytes, L2 buffer: 10000 bytes */
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
			Total Size: 2880 [Tile0, 2:[3x357, 3x123], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 2:[3x357, 3x123], 2]
		Tile0: [0, 2142, 2142], Tile1: [2142, 738, 738], Tile2; [0, 2142, 2142]
	Ker Arg: Boxes, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 2 logical tiles, 2 physical tiles
			Total Size: 3840 [Tile0, 2:[4x357, 4x123], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 2:[4x357, 4x123], 2]
		Tile0: [0, 2856, 2856], Tile1: [2856, 984, 984], Tile2; [0, 2856, 2856]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Classes_W = (unsigned int ) (3);
	KerArg0->Classes_Std_H = (unsigned int ) (357);
	KerArg0->Ancor_layer = (void  * __restrict__) (Ancor_layer);
	KerArg0->BoundingBoxes = (void  * __restrict__) (BoundingBoxes);
	KerArg0->Boxes_Q = (int) (Boxes_Q);
	KerArg0->n_classes = (unsigned int ) (3);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Classes+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), 2142, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read Classes */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Classes+2142), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+2144), 738, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0+0), 2142, 0, &DmaR_Evt1);
	_NN_Classes=2142; _SN_Classes=738;
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Boxes+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+4288+0), 2856, 0, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read Boxes */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Boxes+2856), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+4288+2856), 984, 0, &UchanHR2);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+4288+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+4288+0), 2856, 0, &DmaR_Evt2);
	_NN_Boxes=2856; _SN_Boxes=984;
	/*============================= End Read Tiles Prolog ===============================*/
	for (T0Ind=0; T0Ind<2; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
		int T0Ind_Last = (T0Ind==1), T0Ind_NextLast = ((T0Ind+1)==1), T0Ind_NextNextLast = ((T0Ind+2)==1);
		/*================================= Prepare Tiles ===================================*/
		_SNN_Classes = 0;
		if (!(T0Ind_Last)) {
			if (!(1)) {
				_NN_Classes = _NN_Classes + (2142); _SNN_Classes = ((1)?738:2142); 
			}
		}
		_SNN_Boxes = 0;
		if (!(T0Ind_Last)) {
			if (!(1)) {
				_NN_Boxes = _NN_Boxes + (2856); _SNN_Boxes = ((1)?984:2856); 
			}
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read Classes */
		if (_SNN_Classes) {
			AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Classes+_NN_Classes), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+2144*((T0Ind_Total)%2)),
					_SNN_Classes, 0, &UchanHR1);
		}
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Classes */
		if (_SN_Classes) {
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+2144*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0+2144*((T0Ind_Total+1)%2)),
					_SN_Classes, 0, &DmaR_Evt1);
		}
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read Boxes */
		if (_SNN_Boxes) {
			AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Boxes+_NN_Boxes), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+4288+2856*((T0Ind_Total)%2)),
					_SNN_Boxes, 0, &UchanHR2);
		}
		AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Boxes */
		if (_SN_Boxes) {
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+4288+2856*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+4288+2856*((T0Ind_Total+1)%2)),
					_SN_Boxes, 0, &DmaR_Evt2);
		}
		/*============================= End Read Tiles ======================================*/
		/*====================== Call Kernel LOC_LOOP =========================*/
		KerArg0->Classes = (short * __restrict__) (SSDKernels_L1_Memory+0+2144*((T0Ind_Total)%2));
		KerArg0->Boxes = (short * __restrict__) (SSDKernels_L1_Memory+4288+2856*((T0Ind_Total)%2));
		KerArg0->Classes_H = (unsigned int ) (T0Ind_Last?123:357);
		KerArg0->Classes_TileIndex = (unsigned int ) ((T0Ind));
		AT_FORK(gap_ncore(), (void *) KerPredecoderShort, (void *) KerArg0);
		__CALL(KerPredecoderShort, KerArg0);
		/*================================= Update Arg Pipeline =============================*/
		_SN_Classes = _SNN_Classes;
		_SN_Boxes = _SNN_Boxes;
		/*============================= End Update Arg Pipeline =============================*/
	} /* End iteration on Tile0 */
}
void SDD3Dto2DSoftmax_5_4_18(
		short * In,
		short * Out,
		unsigned char Q,
		unsigned short n_classes)

{
	/* Shared L1: 1440 bytes, L2 buffer: 1440 bytes */
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
			Total Size: 720 [Tile0, 1:[18x20], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[18x20], 2]
		Tile0: [0, 720, 720], Tile1: [0, 720, 720], Tile2; [0, 720, 720]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 720 [Tile0, 1:[18x20], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[18x20], 2]
		Tile0: [0, 720, 720], Tile1: [0, 720, 720], Tile2; [0, 720, 720]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (short * __restrict__) (SSDKernels_L1_Memory+0);
	KerArg0->Win = (unsigned int ) (20);
	KerArg0->Hin = (unsigned int ) (18);
	KerArg0->Out = (short * __restrict__) (SSDKernels_L1_Memory+720);
	KerArg0->Wout = (unsigned int ) (18);
	KerArg0->Hout = (unsigned int ) (20);
	KerArg0->Q = (unsigned char) (Q);
	KerArg0->n_classes = (unsigned short) (n_classes);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), 720, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0), 720, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile0 */
		int T0Ind_Last = 1;
		/*====================== Call Kernel LOC_LOOP =========================*/
		AT_FORK(gap_ncore(), (void *) KerSDD3Dto2DShort, (void *) KerArg0);
		__CALL(KerSDD3Dto2DShort, KerArg0);
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+720+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+720), 720, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+720+0), 720, 1, &UchanHR2);
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
	/* Shared L1: 1680 bytes, L2 buffer: 1680 bytes */
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
			Total Size: 720 [Tile0, 1:[3x120], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[3x120], 2]
		Tile0: [0, 720, 720], Tile1: [0, 720, 720], Tile2; [0, 720, 720]
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
	KerArg0->Boxes = (short * __restrict__) (SSDKernels_L1_Memory+720);
	KerArg0->Classes_W = (unsigned int ) (3);
	KerArg0->Classes_H = (unsigned int ) (120);
	KerArg0->Classes_TileIndex = (unsigned int ) ((0));
	KerArg0->Classes_Std_H = (unsigned int ) (120);
	KerArg0->Ancor_layer = (void  * __restrict__) (Ancor_layer);
	KerArg0->BoundingBoxes = (void  * __restrict__) (BoundingBoxes);
	KerArg0->Boxes_Q = (int) (Boxes_Q);
	KerArg0->n_classes = (unsigned int ) (3);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Classes+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), 720, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read Classes */
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0), 720, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Classes */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Boxes+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+720+0), 960, 0, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read Boxes */
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+720+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+720), 960, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Boxes */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile0 */
		int T0Ind_Last = 1;
		/*====================== Call Kernel LOC_LOOP =========================*/
		AT_FORK(gap_ncore(), (void *) KerPredecoderShort, (void *) KerArg0);
		__CALL(KerPredecoderShort, KerArg0);
	} /* End iteration on Tile0 */
}
void SDD3Dto2DSoftmax_2_2_18(
		short * In,
		short * Out,
		unsigned char Q,
		unsigned short n_classes)

{
	/* Shared L1: 288 bytes, L2 buffer: 288 bytes */
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
			Total Size: 144 [Tile0, 1:[18x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[18x4], 2]
		Tile0: [0, 144, 144], Tile1: [0, 144, 144], Tile2; [0, 144, 144]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 144 [Tile0, 1:[18x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[18x4], 2]
		Tile0: [0, 144, 144], Tile1: [0, 144, 144], Tile2; [0, 144, 144]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (short * __restrict__) (SSDKernels_L1_Memory+0);
	KerArg0->Win = (unsigned int ) (4);
	KerArg0->Hin = (unsigned int ) (18);
	KerArg0->Out = (short * __restrict__) (SSDKernels_L1_Memory+144);
	KerArg0->Wout = (unsigned int ) (18);
	KerArg0->Hout = (unsigned int ) (4);
	KerArg0->Q = (unsigned char) (Q);
	KerArg0->n_classes = (unsigned short) (n_classes);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), 144, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0), 144, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile0 */
		int T0Ind_Last = 1;
		/*====================== Call Kernel LOC_LOOP =========================*/
		AT_FORK(gap_ncore(), (void *) KerSDD3Dto2DShort, (void *) KerArg0);
		__CALL(KerSDD3Dto2DShort, KerArg0);
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+144+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+144), 144, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+144+0), 144, 1, &UchanHR2);
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
	/* Shared L1: 336 bytes, L2 buffer: 336 bytes */
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
			Total Size: 144 [Tile0, 1:[3x24], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[3x24], 2]
		Tile0: [0, 144, 144], Tile1: [0, 144, 144], Tile2; [0, 144, 144]
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
	KerArg0->Boxes = (short * __restrict__) (SSDKernels_L1_Memory+144);
	KerArg0->Classes_W = (unsigned int ) (3);
	KerArg0->Classes_H = (unsigned int ) (24);
	KerArg0->Classes_TileIndex = (unsigned int ) ((0));
	KerArg0->Classes_Std_H = (unsigned int ) (24);
	KerArg0->Ancor_layer = (void  * __restrict__) (Ancor_layer);
	KerArg0->BoundingBoxes = (void  * __restrict__) (BoundingBoxes);
	KerArg0->Boxes_Q = (int) (Boxes_Q);
	KerArg0->n_classes = (unsigned int ) (3);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Classes+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), 144, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read Classes */
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0), 144, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Classes */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Boxes+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+144+0), 192, 0, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read Boxes */
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+144+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+144), 192, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Boxes */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile0 */
		int T0Ind_Last = 1;
		/*====================== Call Kernel LOC_LOOP =========================*/
		AT_FORK(gap_ncore(), (void *) KerPredecoderShort, (void *) KerArg0);
		__CALL(KerPredecoderShort, KerArg0);
	} /* End iteration on Tile0 */
}
