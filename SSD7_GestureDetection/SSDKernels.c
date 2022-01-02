#include "SSDKernels.h"
L1_CL_MEM AT_L1_POINTER SSDKernels_L1_Memory;
L2_MEM AT_L2_POINTER SSDKernels_L2_Memory;
AT_HYPERRAM_POINTER SSDKernels_L3_Memory;
extern AT_HYPERRAM_T HyperRam;
void SDD3Dto2DSoftmax_20_16_48(
		short * In,
		short * Out,
		unsigned char Q,
		unsigned short n_classes)

{
	/* Shared L1: 14976 bytes, L2 buffer: 14976 bytes */
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
		[Tile0 Dim: 9]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 9 logical tiles, 9 physical tiles
			Total Size: 30720 [Tile0, 9:[48x39, 7:48x39, 48x8], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 9:[48x39, 7:48x39, 48x8], 2]
		Tile0: [0, 3744, 78], Tile1: [78, 3744, 78], Tile2; [156, 3744, 78]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 9 logical tiles, 9 physical tiles
			Total Size: 30720 [Tile0, 9:[48x39, 7:48x39, 48x8], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 9:[48x39, 7:48x39, 48x8], 2]
		Tile0: [0, 3744, 3744], Tile1: [3744, 3744, 3744], Tile2; [7488, 3744, 3744]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Hin = (unsigned int ) (48);
	KerArg0->Wout = (unsigned int ) (48);
	KerArg0->Q = (unsigned char) (Q);
	KerArg0->n_classes = (unsigned short) (n_classes);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), 3744, 640, 78, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+78), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+3744), 3744, 640, 78, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0+0), 3744, 0, &DmaR_Evt1);
	_NN_In=78; _SN_In=3744;
	_C_Out=0; _SC_Out=3744;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	for (T0Ind=0; T0Ind<9; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
		int T0Ind_Last = (T0Ind==8), T0Ind_NextLast = ((T0Ind+1)==8), T0Ind_NextNextLast = ((T0Ind+2)==8);
		/*================================= Prepare Tiles ===================================*/
		_SNN_In = 0;
		if (!(T0Ind_Last)) {
			if (!(T0Ind_NextLast)) {
				_NN_In = _NN_In + (78); _LNN_In = ((T0Ind_NextNextLast)?16:78); _SNN_In = (48*_LNN_In); 
			}
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
		if (_SNN_In) {
			AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+3744*((T0Ind_Total)%2)),
					_SNN_In, 640, _LNN_In, 0, &UchanHR1);
		}
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
		if (_SN_In) {
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+3744*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0+3744*((T0Ind_Total+1)%2)),
					_SN_In, 0, &DmaR_Evt1);
		}
		/*============================= End Read Tiles ======================================*/
		/*====================== Call Kernel LOC_LOOP =========================*/
		KerArg0->In = (short * __restrict__) (SSDKernels_L1_Memory+0+3744*((T0Ind_Total)%2));
		KerArg0->Win = (unsigned int ) ((T0Ind_Last)?8:39);
		KerArg0->Out = (short * __restrict__) (SSDKernels_L1_Memory+7488+3744*((T0Ind_Total)%2));
		KerArg0->Hout = (unsigned int ) (T0Ind_Last?8:39);
		AT_FORK(gap_ncore(), (void *) KerSDD3Dto2DShort, (void *) KerArg0);
		__CALL(KerSDD3Dto2DShort, KerArg0);
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
		if (_SP_Out) AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+7488+3744*((T0Ind_Total+-1)%2)),
					_SP_Out, 1, &UchanHR2);
		AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+7488+3744*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+7488+3744*((T0Ind_Total)%2)),
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
			_C_Out = _C_Out + (3744); _SC_Out = ((T0Ind_NextLast)?768:3744); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+7488+3744*((T0Ind_Total+-1)%2)), _SP_Out, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void SDD3Dto2D_20_16_24(
		short * In,
		short * Out,
		unsigned char Q,
		unsigned short n_classes)

{
	/* Shared L1: 14976 bytes, L2 buffer: 14976 bytes */
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
			Total Size: 15360 [Tile0, 5:[24x78, 3:24x78, 24x8], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 5:[24x78, 3:24x78, 24x8], 2]
		Tile0: [0, 3744, 156], Tile1: [156, 3744, 156], Tile2; [312, 3744, 156]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 5 logical tiles, 5 physical tiles
			Total Size: 15360 [Tile0, 5:[24x78, 3:24x78, 24x8], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 5:[24x78, 3:24x78, 24x8], 2]
		Tile0: [0, 3744, 3744], Tile1: [3744, 3744, 3744], Tile2; [7488, 3744, 3744]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Hin = (unsigned int ) (24);
	KerArg0->Wout = (unsigned int ) (24);
	KerArg0->Q = (unsigned char) (Q);
	KerArg0->n_classes = (unsigned short) (n_classes);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), 3744, 640, 156, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+156), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+3744), 3744, 640, 156, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0+0), 3744, 0, &DmaR_Evt1);
	_NN_In=156; _SN_In=3744;
	_C_Out=0; _SC_Out=3744;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	for (T0Ind=0; T0Ind<5; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
		int T0Ind_Last = (T0Ind==4), T0Ind_NextLast = ((T0Ind+1)==4), T0Ind_NextNextLast = ((T0Ind+2)==4);
		/*================================= Prepare Tiles ===================================*/
		_SNN_In = 0;
		if (!(T0Ind_Last)) {
			if (!(T0Ind_NextLast)) {
				_NN_In = _NN_In + (156); _LNN_In = ((T0Ind_NextNextLast)?16:156); _SNN_In = (24*_LNN_In); 
			}
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
		if (_SNN_In) {
			AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+3744*((T0Ind_Total)%2)),
					_SNN_In, 640, _LNN_In, 0, &UchanHR1);
		}
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
		if (_SN_In) {
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+3744*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0+3744*((T0Ind_Total+1)%2)),
					_SN_In, 0, &DmaR_Evt1);
		}
		/*============================= End Read Tiles ======================================*/
		/*====================== Call Kernel LOC_LOOP =========================*/
		KerArg0->In = (short * __restrict__) (SSDKernels_L1_Memory+0+3744*((T0Ind_Total)%2));
		KerArg0->Win = (unsigned int ) ((T0Ind_Last)?8:78);
		KerArg0->Out = (short * __restrict__) (SSDKernels_L1_Memory+7488+3744*((T0Ind_Total)%2));
		KerArg0->Hout = (unsigned int ) (T0Ind_Last?8:78);
		AT_FORK(gap_ncore(), (void *) KerSDD3Dto2DShort, (void *) KerArg0);
		__CALL(KerSDD3Dto2DShort, KerArg0);
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
		if (_SP_Out) AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+7488+3744*((T0Ind_Total+-1)%2)),
					_SP_Out, 1, &UchanHR2);
		AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+7488+3744*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+7488+3744*((T0Ind_Total)%2)),
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
			_C_Out = _C_Out + (3744); _SC_Out = ((T0Ind_NextLast)?384:3744); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+7488+3744*((T0Ind_Total+-1)%2)), _SP_Out, 1, &UchanHR2);
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
	/* Shared L1: 14976 bytes, L2 buffer: 14976 bytes */
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
		[Tile0 Dim: 7]
	Ker Arg: Classes, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 7 logical tiles, 7 physical tiles
			Total Size: 30720 [Tile0, 7:[8x312, 5:8x312, 8x48], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 7:[8x312, 5:8x312, 8x48], 2]
		Tile0: [0, 4992, 4992], Tile1: [4992, 4992, 4992], Tile2; [9984, 4992, 4992]
	Ker Arg: Boxes, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 7 logical tiles, 7 physical tiles
			Total Size: 15360 [Tile0, 7:[4x312, 5:4x312, 4x48], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 7:[4x312, 5:4x312, 4x48], 2]
		Tile0: [0, 2496, 2496], Tile1: [2496, 2496, 2496], Tile2; [4992, 2496, 2496]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Classes_W = (unsigned int ) (8);
	KerArg0->Classes_Std_H = (unsigned int ) (312);
	KerArg0->Ancor_layer = (void  * __restrict__) (Ancor_layer);
	KerArg0->BoundingBoxes = (void  * __restrict__) (BoundingBoxes);
	KerArg0->Boxes_Q = (int) (Boxes_Q);
	KerArg0->n_classes = (unsigned int ) (8);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Classes+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), 4992, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read Classes */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Classes+4992), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+4992), 4992, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0+0), 4992, 0, &DmaR_Evt1);
	_NN_Classes=4992; _SN_Classes=4992;
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Boxes+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+9984+0), 2496, 0, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read Boxes */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Boxes+2496), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+9984+2496), 2496, 0, &UchanHR2);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+9984+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+9984+0), 2496, 0, &DmaR_Evt2);
	_NN_Boxes=2496; _SN_Boxes=2496;
	/*============================= End Read Tiles Prolog ===============================*/
	for (T0Ind=0; T0Ind<7; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
		int T0Ind_Last = (T0Ind==6), T0Ind_NextLast = ((T0Ind+1)==6), T0Ind_NextNextLast = ((T0Ind+2)==6);
		/*================================= Prepare Tiles ===================================*/
		_SNN_Classes = 0;
		if (!(T0Ind_Last)) {
			if (!(T0Ind_NextLast)) {
				_NN_Classes = _NN_Classes + (4992); _SNN_Classes = ((T0Ind_NextNextLast)?768:4992); 
			}
		}
		_SNN_Boxes = 0;
		if (!(T0Ind_Last)) {
			if (!(T0Ind_NextLast)) {
				_NN_Boxes = _NN_Boxes + (2496); _SNN_Boxes = ((T0Ind_NextNextLast)?384:2496); 
			}
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read Classes */
		if (_SNN_Classes) {
			AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Classes+_NN_Classes), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+4992*((T0Ind_Total)%2)),
					_SNN_Classes, 0, &UchanHR1);
		}
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Classes */
		if (_SN_Classes) {
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+4992*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0+4992*((T0Ind_Total+1)%2)),
					_SN_Classes, 0, &DmaR_Evt1);
		}
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read Boxes */
		if (_SNN_Boxes) {
			AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Boxes+_NN_Boxes), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+9984+2496*((T0Ind_Total)%2)),
					_SNN_Boxes, 0, &UchanHR2);
		}
		AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Boxes */
		if (_SN_Boxes) {
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+9984+2496*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+9984+2496*((T0Ind_Total+1)%2)),
					_SN_Boxes, 0, &DmaR_Evt2);
		}
		/*============================= End Read Tiles ======================================*/
		/*====================== Call Kernel LOC_LOOP =========================*/
		KerArg0->Classes = (short * __restrict__) (SSDKernels_L1_Memory+0+4992*((T0Ind_Total)%2));
		KerArg0->Boxes = (short * __restrict__) (SSDKernels_L1_Memory+9984+2496*((T0Ind_Total)%2));
		KerArg0->Classes_H = (unsigned int ) (T0Ind_Last?48:312);
		KerArg0->Classes_TileIndex = (unsigned int ) ((T0Ind));
		AT_FORK(gap_ncore(), (void *) KerPredecoderShort, (void *) KerArg0);
		__CALL(KerPredecoderShort, KerArg0);
		/*================================= Update Arg Pipeline =============================*/
		_SN_Classes = _SNN_Classes;
		_SN_Boxes = _SNN_Boxes;
		/*============================= End Update Arg Pipeline =============================*/
	} /* End iteration on Tile0 */
}
void SDD3Dto2DSoftmax_10_8_48(
		short * In,
		short * Out,
		unsigned char Q,
		unsigned short n_classes)

{
	/* Shared L1: 14976 bytes, L2 buffer: 14976 bytes */
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
			Total Size: 7680 [Tile0, 3:[48x39, 1:48x39, 48x2], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 3:[48x39, 1:48x39, 48x2], 2]
		Tile0: [0, 3744, 78], Tile1: [78, 3744, 78], Tile2; [156, 192, 4]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 3 logical tiles, 3 physical tiles
			Total Size: 7680 [Tile0, 3:[48x39, 1:48x39, 48x2], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 3:[48x39, 1:48x39, 48x2], 2]
		Tile0: [0, 3744, 3744], Tile1: [3744, 3744, 3744], Tile2; [7488, 192, 192]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Hin = (unsigned int ) (48);
	KerArg0->Wout = (unsigned int ) (48);
	KerArg0->Q = (unsigned char) (Q);
	KerArg0->n_classes = (unsigned short) (n_classes);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), 3744, 160, 78, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+78), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+3744), 3744, 160, 78, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0+0), 3744, 0, &DmaR_Evt1);
	_NN_In=78; _SN_In=3744;
	_C_Out=0; _SC_Out=3744;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	for (T0Ind=0; T0Ind<3; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
		int T0Ind_Last = (T0Ind==2), T0Ind_NextLast = ((T0Ind+1)==2), T0Ind_NextNextLast = ((T0Ind+2)==2);
		/*================================= Prepare Tiles ===================================*/
		_SNN_In = 0;
		if (!(T0Ind_Last)) {
			if (!(T0Ind_NextLast)) {
				_NN_In = _NN_In + (78); _LNN_In = ((1)?4:78); _SNN_In = (48*_LNN_In); 
			}
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
		if (_SNN_In) {
			AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+3744*((T0Ind_Total)%2)),
					_SNN_In, 160, _LNN_In, 0, &UchanHR1);
		}
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
		if (_SN_In) {
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+3744*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0+3744*((T0Ind_Total+1)%2)),
					_SN_In, 0, &DmaR_Evt1);
		}
		/*============================= End Read Tiles ======================================*/
		/*====================== Call Kernel LOC_LOOP =========================*/
		KerArg0->In = (short * __restrict__) (SSDKernels_L1_Memory+0+3744*((T0Ind_Total)%2));
		KerArg0->Win = (unsigned int ) ((T0Ind_Last)?2:39);
		KerArg0->Out = (short * __restrict__) (SSDKernels_L1_Memory+7488+3744*((T0Ind_Total)%2));
		KerArg0->Hout = (unsigned int ) (T0Ind_Last?2:39);
		AT_FORK(gap_ncore(), (void *) KerSDD3Dto2DShort, (void *) KerArg0);
		__CALL(KerSDD3Dto2DShort, KerArg0);
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
		if (_SP_Out) AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+7488+3744*((T0Ind_Total+-1)%2)),
					_SP_Out, 1, &UchanHR2);
		AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+7488+3744*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+7488+3744*((T0Ind_Total)%2)),
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
			_C_Out = _C_Out + (3744); _SC_Out = ((T0Ind_NextLast)?192:3744); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+7488+3744*((T0Ind_Total+-1)%2)), _SP_Out, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void SDD3Dto2D_10_8_24(
		short * In,
		short * Out,
		unsigned char Q,
		unsigned short n_classes)

{
	/* Shared L1: 14976 bytes, L2 buffer: 14976 bytes */
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
			Total Size: 3840 [Tile0, 2:[24x78, 24x2], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 2:[24x78, 24x2], 2]
		Tile0: [0, 3744, 156], Tile1: [156, 96, 4], Tile2; [0, 3744, 156]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 2 physical tiles
			Total Size: 3840 [Tile0, 2:[24x78, 24x2], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 2:[24x78, 24x2], 2]
		Tile0: [0, 3744, 3744], Tile1: [3744, 96, 96], Tile2; [0, 3744, 3744]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Hin = (unsigned int ) (24);
	KerArg0->Wout = (unsigned int ) (24);
	KerArg0->Q = (unsigned char) (Q);
	KerArg0->n_classes = (unsigned short) (n_classes);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), 3744, 160, 156, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+156), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+3744), 96, 160, 4, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0+0), 3744, 0, &DmaR_Evt1);
	_NN_In=156; _SN_In=96;
	_C_Out=0; _SC_Out=3744;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	for (T0Ind=0; T0Ind<2; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
		int T0Ind_Last = (T0Ind==1), T0Ind_NextLast = ((T0Ind+1)==1), T0Ind_NextNextLast = ((T0Ind+2)==1);
		/*================================= Prepare Tiles ===================================*/
		_SNN_In = 0;
		if (!(T0Ind_Last)) {
			if (!(1)) {
				_NN_In = _NN_In + (156); _LNN_In = ((1)?4:156); _SNN_In = (24*_LNN_In); 
			}
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
		if (_SNN_In) {
			AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+3744*((T0Ind_Total)%2)),
					_SNN_In, 160, _LNN_In, 0, &UchanHR1);
		}
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
		if (_SN_In) {
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+3744*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0+3744*((T0Ind_Total+1)%2)),
					_SN_In, 0, &DmaR_Evt1);
		}
		/*============================= End Read Tiles ======================================*/
		/*====================== Call Kernel LOC_LOOP =========================*/
		KerArg0->In = (short * __restrict__) (SSDKernels_L1_Memory+0+3744*((T0Ind_Total)%2));
		KerArg0->Win = (unsigned int ) ((T0Ind_Last)?2:78);
		KerArg0->Out = (short * __restrict__) (SSDKernels_L1_Memory+7488+3744*((T0Ind_Total)%2));
		KerArg0->Hout = (unsigned int ) (T0Ind_Last?2:78);
		AT_FORK(gap_ncore(), (void *) KerSDD3Dto2DShort, (void *) KerArg0);
		__CALL(KerSDD3Dto2DShort, KerArg0);
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
		if (_SP_Out) AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+7488+3744*((T0Ind_Total+-1)%2)),
					_SP_Out, 1, &UchanHR2);
		AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+7488+3744*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+7488+3744*((T0Ind_Total)%2)),
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
			_C_Out = _C_Out + (3744); _SC_Out = ((1)?96:3744); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+7488+3744*((T0Ind_Total+-1)%2)), _SP_Out, 1, &UchanHR2);
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
	/* Shared L1: 14976 bytes, L2 buffer: 14976 bytes */
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
			Total Size: 7680 [Tile0, 2:[8x312, 8x168], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 2:[8x312, 8x168], 2]
		Tile0: [0, 4992, 4992], Tile1: [4992, 2688, 2688], Tile2; [0, 4992, 4992]
	Ker Arg: Boxes, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 2 logical tiles, 2 physical tiles
			Total Size: 3840 [Tile0, 2:[4x312, 4x168], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 2:[4x312, 4x168], 2]
		Tile0: [0, 2496, 2496], Tile1: [2496, 1344, 1344], Tile2; [0, 2496, 2496]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Classes_W = (unsigned int ) (8);
	KerArg0->Classes_Std_H = (unsigned int ) (312);
	KerArg0->Ancor_layer = (void  * __restrict__) (Ancor_layer);
	KerArg0->BoundingBoxes = (void  * __restrict__) (BoundingBoxes);
	KerArg0->Boxes_Q = (int) (Boxes_Q);
	KerArg0->n_classes = (unsigned int ) (8);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Classes+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), 4992, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read Classes */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Classes+4992), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+4992), 2688, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0+0), 4992, 0, &DmaR_Evt1);
	_NN_Classes=4992; _SN_Classes=2688;
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Boxes+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+9984+0), 2496, 0, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read Boxes */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Boxes+2496), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+9984+2496), 1344, 0, &UchanHR2);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+9984+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+9984+0), 2496, 0, &DmaR_Evt2);
	_NN_Boxes=2496; _SN_Boxes=1344;
	/*============================= End Read Tiles Prolog ===============================*/
	for (T0Ind=0; T0Ind<2; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
		int T0Ind_Last = (T0Ind==1), T0Ind_NextLast = ((T0Ind+1)==1), T0Ind_NextNextLast = ((T0Ind+2)==1);
		/*================================= Prepare Tiles ===================================*/
		_SNN_Classes = 0;
		if (!(T0Ind_Last)) {
			if (!(1)) {
				_NN_Classes = _NN_Classes + (4992); _SNN_Classes = ((1)?2688:4992); 
			}
		}
		_SNN_Boxes = 0;
		if (!(T0Ind_Last)) {
			if (!(1)) {
				_NN_Boxes = _NN_Boxes + (2496); _SNN_Boxes = ((1)?1344:2496); 
			}
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read Classes */
		if (_SNN_Classes) {
			AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Classes+_NN_Classes), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+4992*((T0Ind_Total)%2)),
					_SNN_Classes, 0, &UchanHR1);
		}
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Classes */
		if (_SN_Classes) {
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+4992*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0+4992*((T0Ind_Total+1)%2)),
					_SN_Classes, 0, &DmaR_Evt1);
		}
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read Boxes */
		if (_SNN_Boxes) {
			AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Boxes+_NN_Boxes), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+9984+2496*((T0Ind_Total)%2)),
					_SNN_Boxes, 0, &UchanHR2);
		}
		AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Boxes */
		if (_SN_Boxes) {
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+9984+2496*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+9984+2496*((T0Ind_Total+1)%2)),
					_SN_Boxes, 0, &DmaR_Evt2);
		}
		/*============================= End Read Tiles ======================================*/
		/*====================== Call Kernel LOC_LOOP =========================*/
		KerArg0->Classes = (short * __restrict__) (SSDKernels_L1_Memory+0+4992*((T0Ind_Total)%2));
		KerArg0->Boxes = (short * __restrict__) (SSDKernels_L1_Memory+9984+2496*((T0Ind_Total)%2));
		KerArg0->Classes_H = (unsigned int ) (T0Ind_Last?168:312);
		KerArg0->Classes_TileIndex = (unsigned int ) ((T0Ind));
		AT_FORK(gap_ncore(), (void *) KerPredecoderShort, (void *) KerArg0);
		__CALL(KerPredecoderShort, KerArg0);
		/*================================= Update Arg Pipeline =============================*/
		_SN_Classes = _SNN_Classes;
		_SN_Boxes = _SNN_Boxes;
		/*============================= End Update Arg Pipeline =============================*/
	} /* End iteration on Tile0 */
}
void SDD3Dto2DSoftmax_5_4_48(
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
			Total Size: 1920 [Tile0, 1:[48x20], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[48x20], 2]
		Tile0: [0, 1920, 1920], Tile1: [0, 1920, 1920], Tile2; [0, 1920, 1920]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 1920 [Tile0, 1:[48x20], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[48x20], 2]
		Tile0: [0, 1920, 1920], Tile1: [0, 1920, 1920], Tile2; [0, 1920, 1920]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (short * __restrict__) (SSDKernels_L1_Memory+0);
	KerArg0->Win = (unsigned int ) (20);
	KerArg0->Hin = (unsigned int ) (48);
	KerArg0->Out = (short * __restrict__) (SSDKernels_L1_Memory+1920);
	KerArg0->Wout = (unsigned int ) (48);
	KerArg0->Hout = (unsigned int ) (20);
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
	/* Shared L1: 2880 bytes, L2 buffer: 2880 bytes */
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
			Total Size: 1920 [Tile0, 1:[8x120], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[8x120], 2]
		Tile0: [0, 1920, 1920], Tile1: [0, 1920, 1920], Tile2; [0, 1920, 1920]
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
	KerArg0->Boxes = (short * __restrict__) (SSDKernels_L1_Memory+1920);
	KerArg0->Classes_W = (unsigned int ) (8);
	KerArg0->Classes_H = (unsigned int ) (120);
	KerArg0->Classes_TileIndex = (unsigned int ) ((0));
	KerArg0->Classes_Std_H = (unsigned int ) (120);
	KerArg0->Ancor_layer = (void  * __restrict__) (Ancor_layer);
	KerArg0->BoundingBoxes = (void  * __restrict__) (BoundingBoxes);
	KerArg0->Boxes_Q = (int) (Boxes_Q);
	KerArg0->n_classes = (unsigned int ) (8);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Classes+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), 1920, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read Classes */
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+0+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+0), 1920, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Classes */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Boxes+0), ((AT_HYPERRAM_INT_ADDR_TYPE) SSDKernels_L2_Memory+1920+0), 960, 0, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read Boxes */
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) SSDKernels_L2_Memory+1920+0), ((AT_L2_INT_ADDR_TYPE) SSDKernels_L1_Memory+1920), 960, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Boxes */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile0 */
		int T0Ind_Last = 1;
		/*====================== Call Kernel LOC_LOOP =========================*/
		AT_FORK(gap_ncore(), (void *) KerPredecoderShort, (void *) KerArg0);
		__CALL(KerPredecoderShort, KerArg0);
	} /* End iteration on Tile0 */
}
