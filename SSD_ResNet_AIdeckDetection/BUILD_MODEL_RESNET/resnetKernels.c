#include "resnetKernels.h"
L1_CL_MEM AT_L1_POINTER resnet_L1_Memory;
L2_MEM AT_L2_POINTER resnet_L2_Memory;
AT_HYPERRAM_POINTER resnet_L3_Memory;
extern AT_HYPERRAM_T HyperRam;
static AT_HYPERFLASH_FS_T HyperFlash;
void S4_Conv2d_8x1x7x7_MaxPool_3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 16672 bytes, L2 buffer: 9088 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaW_Evt1;
	KerSetBias_fpd_fp_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConv_DP_fp_T S_KerArg1, *KerArg1 = &S_KerArg1;
	KerDP_fp_T S_KerArg2, *KerArg2 = &S_KerArg2;
	KerReLUPool_fp_T S_KerArg3, *KerArg3 = &S_KerArg3;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Last;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast;
	/* User kernel arguments related variables */
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	unsigned int _LP_Out, _LC_Out;
	unsigned int _N_In;
	unsigned int _SN_In;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 8, Tiled: 1][Tile0 Dim: 39][D0 Dim: Init: 1, Tiled: 1]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 39 logical tiles, 39 physical tiles
			Total Size: 24336 [D1, [0 x 24336, 24336]][Tile0, 39:[39x1, 37:39x1, 39x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 24336, 24336]][Tile0, 39:[39x1, 37:39x1, 39x1], 2]
		Tile0: [0, 624, 78], Tile1: [78, 624, 78], Tile2; [156, 624, 78]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 16 [D1, [0 x 16, 16]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 16, 16]]
		Tile0: [0, 16, 16], Tile1: [0, 16, 16], Tile2; [0, 16, 16]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 784 [D1, [0 x 784, 784]][D0, [0 x 98, 98]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 784, 784]][D0, [0 x 98, 98]]
		Tile0: [0, 784, 784], Tile1: [0, 784, 784], Tile2; [0, 784, 784]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 39 logical tiles, 39 physical tiles
			Total Size: 51200 [D0, [0 x 51200, 51200]][Tile0, 39:[160x8, 37:160x11, 160x11], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 39:[160x8], 2][D0, [0 x 51200, 51200]]
		Tile0: [0, 2560, 2560], Tile1: [320, 3520, 3520], Tile2; [1600, 3520, 3520]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 39 logical tiles, 1 physical tiles
			Total Size: 199712 [D1, [0 x 199712, 199712]][Tile0, 39:[79x3, 37:79x3, 79x3], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 199712, 199712]][Tile0, 39:[79x3, 37:79x3, 79x3], 4]
		Tile0: [0, 7584, 948], Tile1: [0, 7584, 948], Tile2; [0, 7584, 948]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+9088);
	KerArg0->W = (unsigned short int) (79);
	KerArg0->H = (unsigned short int) (3);
	KerArg0->OutFeatures = (unsigned short int) (8);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+7040);
	KerArg0->NormBias = (signed char) (13);
	KerArg1->W = (unsigned short int) (160);
	KerArg1->UsedW = (unsigned short int) (160);
	KerArg1->InFeatures = (unsigned short int) (1);
	KerArg1->OutFeatures = (unsigned short int) (8);
	KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+7056);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+9088);
	KerArg1->Norm = (unsigned char) (14);
	KerArg1->TotalInFeatures = (short int) (1);
	KerArg1->Orientation = (unsigned char) (1);
	KerArg1->S = (unsigned char) (2);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+9088);
	KerArg2->W = (unsigned short int) (79);
	KerArg2->H = (unsigned short int) (3);
	KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+9088);
	KerArg2->Norm = (unsigned char) (14);
	KerArg2->InFeatures = (unsigned short int) (8);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	KerArg3->In = (short int * __restrict__) (resnet_L1_Memory+9088);
	KerArg3->W = (unsigned short int) (79);
	KerArg3->UsedW = (unsigned short int) (79);
	KerArg3->H = (unsigned short int) (3);
	KerArg3->UsedH = (unsigned short int) (3);
	KerArg3->OutFeatures = (unsigned short int) (8);
	KerArg3->Pad = (v4s) 0;
	KerArg3->M = (unsigned char) (3);
	KerArg3->S = (unsigned char) (2);
	KerArg3->Orientation = (unsigned char) (1);
	KerArg3->Oper = (unsigned char) (1);
	KerArg3->LB = (int) (0);
	KerArg3->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	_C_Out=0; _SC_Out=624; _LC_Out=78;
	_SP_Out=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+7040), 16, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+7056), 784, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Filter */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 2560, 0, &DmaR_Evt3);
	_N_In=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<39; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==38), T0Ind_NextLast = ((T0Ind+1)==38);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			{ /* Single iteration on D0 */
				int D0Ind_Last = 1, D0Ind_NextLast = 1;
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(T0Ind_Last)) {
					_N_In = _N_In + (1280-(960*(T0Ind==0))); _SN_In = (1*((T0Ind_NextLast)?3520:3520)); 
				} else if (!(1)) {
					_N_In = _N_In + (-47680); _SN_In = (1*(2560)); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+3520*((D0Ind_Total+1)%2)),
							_SN_In, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+3520*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (11-3*(T0Ind==0)-0*(T0Ind_Last));
				KerArg1->UsedH = (unsigned short int) (11-3*(T0Ind==0)-0*(T0Ind_Last));
				KerArg1->Pad = (v4s) ((v4s){3,0,3*(T0Ind==0),0*(T0Ind_Last)});
				AT_FORK(gap_ncore(), (void *) KerParConv7x7StrideS_DP_fp, (void *) KerArg1);
				__CALL(KerParConv7x7StrideS_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				/*============================= End Update Arg Pipeline =============================*/
				D0Ind_Total++;
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerDP_IO_fp, (void *) KerArg2);
			__CALL(KerDP_IO_fp, KerArg2);
			KerArg3->Out = (short int * __restrict__) (resnet_L1_Memory+7840+624*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerParPoolNxNStrideS_fp, (void *) KerArg3);
			__CALL(KerParPoolNxNStrideS_fp, KerArg3);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+7840+624*((T0Ind_Total)%2)),
					_SC_Out, 3042, _LC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (78); _LC_Out = (78); _SC_Out = (8*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S7_Conv2d_8x8x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 15832 bytes, L2 buffer: 9592 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	KerSetBias_fpd_fp_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConv_DP_fp_T S_KerArg1, *KerArg1 = &S_KerArg1;
	KerDP_fp_T S_KerArg2, *KerArg2 = &S_KerArg2;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Last;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast;
	/* User kernel arguments related variables */
	unsigned int _N_In;
	unsigned int _SN_In;
	unsigned int _LN_In;
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	unsigned int _LPP_Out, _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 8, Tiled: 1][Tile0 Dim: 8][D0 Dim: Init: 8, Tiled: 4]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 32 logical tiles, 32 physical tiles
			Total Size: 24336 [D0, [3 x 6084, 6084]][Tile0, 8:[39x6, 6:39x7, 39x5], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 8:[39x6, 2:39x7, 39x5], 2][D0, [3 x 6084, 6084]]
		Tile0: [0, 936, 468], Tile1: [6084, 936, 468], Tile2; [12168, 936, 468]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 16 [D1, [0 x 16, 16]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 16, 16]]
		Tile0: [0, 16, 16], Tile1: [0, 16, 16], Tile2; [0, 16, 16]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 4 logical tiles, 1 physical tiles
			Total Size: 1152 [D1, [0 x 1152, 1152]][D0, [3 x 36, 36]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 1152, 1152]][D0, [3 x 36, 36]]
		Tile0: [0, 1152, 1152], Tile1: [0, 1152, 1152], Tile2; [0, 1152, 1152]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 8 logical tiles, 8 physical tiles
			Total Size: 24336 [D1, [0 x 24336, 24336]][Tile0, 8:[39x5, 6:39x5, 39x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 24336, 24336]][Tile0, 8:[39x5, 6:39x5, 39x4], 2]
		Tile0: [0, 3120, 390], Tile1: [390, 3120, 390], Tile2; [780, 3120, 390]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 8 logical tiles, 1 physical tiles
			Total Size: 48672 [D1, [0 x 48672, 48672]][Tile0, 8:[39x5, 6:39x5, 39x4], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 48672, 48672]][Tile0, 8:[39x5, 6:39x5, 39x4], 4]
		Tile0: [0, 6240, 780], Tile1: [0, 6240, 780], Tile2; [0, 6240, 780]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+9592);
	KerArg0->W = (unsigned short int) (39);
	KerArg0->OutFeatures = (unsigned short int) (8);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+2184);
	KerArg0->NormBias = (signed char) (15);
	KerArg1->W = (unsigned short int) (39);
	KerArg1->UsedW = (unsigned short int) (39);
	KerArg1->InFeatures = (unsigned short int) (2);
	KerArg1->OutFeatures = (unsigned short int) (8);
	KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+2200);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+9592);
	KerArg1->Norm = (unsigned char) (14);
	KerArg1->TotalInFeatures = (short int) (8);
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+9592);
	KerArg2->W = (unsigned short int) (39);
	KerArg2->Norm = (unsigned char) (14);
	KerArg2->InFeatures = (unsigned short int) (8);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 936, 3042, 468, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+2184), 16, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+2200), 1152, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
	_C_Out=0; _SC_Out=3120; _LC_Out=390;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<8; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==7), T0Ind_NextLast = ((T0Ind+1)==7);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->H = (unsigned short int) (T0Ind_Last?4:5);
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<4; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==3), D0Ind_NextLast = ((D0Ind+1)==3);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (6084); _LN_In = ((T0Ind_Last)?390:(546-78*(T0Ind==0))); _SN_In = (2*_LN_In); 
				} else if (!(T0Ind_Last)) {
					_N_In = _N_In + (390-(78*(T0Ind==0)))+(-18252); _LN_In = ((T0Ind_NextLast)?390:546); _SN_In = (2*_LN_In); 
				} else if (!(1)) {
					_N_In = _N_In + (-2652)+(-18252); _LN_In = (468); _SN_In = (2*_LN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+1092*((D0Ind_Total+1)%2)),
							_SN_In, 3042, _LN_In, 0, &DmaR_Evt1);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+1092*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (((T0Ind_Last)?5:7)-1*(T0Ind==0));
				KerArg1->UsedH = (unsigned short int) (((T0Ind_Last)?5:7)-1*(T0Ind==0));
				KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+2200+((D0Ind)*36));
				KerArg1->Pad = (v4s) ((v4s){1,1,1*(T0Ind==0),1*(T0Ind_Last)});
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->H = (unsigned short int) (T0Ind_Last?4:5);
			KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+3352+3120*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+24672+3120*((T0Ind_Total+-1)%2)),
						_SP_Out, 3042, _LP_Out, 1, &UchanHR1);
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+24672+3120*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+3352+3120*((T0Ind_Total)%2)),
					_SC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
			_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (390); _LC_Out = ((T0Ind_NextLast)?312:390); _SC_Out = (8*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+24672+3120*((T0Ind_Total+-1)%2)), _SP_Out, 3042, _LP_Out, 1, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S10_Conv2d_8x8x3x3(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 15832 bytes, L2 buffer: 9592 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	AT_HYPERRAM_CL_EVENT UchanHR2;
	KerSetBias_fpd_fp_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConv_DP_fp_T S_KerArg1, *KerArg1 = &S_KerArg1;
	KerDP_fp_T S_KerArg2, *KerArg2 = &S_KerArg2;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Last;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast, T0Ind_NextNextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast, D0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _NN_In;
	unsigned int _SN_In, _SNN_In;
	unsigned int _LN_In, _LNN_In;
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	unsigned int _LPP_Out, _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 8, Tiled: 1][Tile0 Dim: 8][D0 Dim: Init: 8, Tiled: 4]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 32 logical tiles, 32 physical tiles
			Total Size: 24336 [D0, [3 x 6084, 6084]][Tile0, 8:[39x6, 6:39x7, 39x5], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 8:[39x6, 2:39x7, 39x5], 2][D0, [3 x 6084, 6084]]
		Tile0: [0, 936, 468], Tile1: [6084, 936, 468], Tile2; [12168, 936, 468]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 16 [D1, [0 x 16, 16]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 16, 16]]
		Tile0: [0, 16, 16], Tile1: [0, 16, 16], Tile2; [0, 16, 16]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 4 logical tiles, 1 physical tiles
			Total Size: 1152 [D1, [0 x 1152, 1152]][D0, [3 x 36, 36]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 1152, 1152]][D0, [3 x 36, 36]]
		Tile0: [0, 1152, 1152], Tile1: [0, 1152, 1152], Tile2; [0, 1152, 1152]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 8 logical tiles, 8 physical tiles
			Total Size: 24336 [D1, [0 x 24336, 24336]][Tile0, 8:[39x5, 6:39x5, 39x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 24336, 24336]][Tile0, 8:[39x5, 6:39x5, 39x4], 2]
		Tile0: [0, 3120, 390], Tile1: [390, 3120, 390], Tile2; [780, 3120, 390]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 8 logical tiles, 1 physical tiles
			Total Size: 48672 [D1, [0 x 48672, 48672]][Tile0, 8:[39x5, 6:39x5, 39x4], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 48672, 48672]][Tile0, 8:[39x5, 6:39x5, 39x4], 4]
		Tile0: [0, 6240, 780], Tile1: [0, 6240, 780], Tile2; [0, 6240, 780]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+9592);
	KerArg0->W = (unsigned short int) (39);
	KerArg0->OutFeatures = (unsigned short int) (8);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+2184);
	KerArg0->NormBias = (signed char) (15);
	KerArg1->W = (unsigned short int) (39);
	KerArg1->UsedW = (unsigned short int) (39);
	KerArg1->InFeatures = (unsigned short int) (2);
	KerArg1->OutFeatures = (unsigned short int) (8);
	KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+2200);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+9592);
	KerArg1->Norm = (unsigned char) (16);
	KerArg1->TotalInFeatures = (short int) (8);
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+9592);
	KerArg2->W = (unsigned short int) (39);
	KerArg2->Norm = (unsigned char) (16);
	KerArg2->InFeatures = (unsigned short int) (8);
	KerArg2->LB = (int) (-32768);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+24672+0), 936, 3042, 468, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+6084), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+24672+1092), 936, 3042, 468, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+24672+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 936, 0, &DmaR_Evt1);
	_NN_In=6084; _SN_In=936;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+2184), 16, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+2200), 1152, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
	_C_Out=0; _SC_Out=3120; _LC_Out=390;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<8; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==7), T0Ind_NextLast = ((T0Ind+1)==7), T0Ind_NextNextLast = ((T0Ind+2)==7);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->H = (unsigned short int) (T0Ind_Last?4:5);
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<4; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==3), D0Ind_NextLast = ((D0Ind+1)==3), D0Ind_NextNextLast = ((D0Ind+2)==3);
				/*================================= Prepare Tiles ===================================*/
				_SNN_In = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_In = _NN_In + (6084); _LNN_In = ((T0Ind_Last)?390:(546-78*(T0Ind==0))); _SNN_In = (2*_LNN_In); 
					} else if (!(T0Ind_Last)) {
						_NN_In = _NN_In + (390-(78*(T0Ind==0)))+(-18252); _LNN_In = ((T0Ind_NextLast)?390:546); _SNN_In = (2*_LNN_In); 
					} else if (!(1)) {
						_NN_In = _NN_In + (-2652)+(-18252); _LNN_In = (468); _SNN_In = (2*_LNN_In); 
					}
				} else if (!(T0Ind_Last)) {
					_NN_In = _NN_In + (6084); _LNN_In = ((T0Ind_NextLast)?390:546); _SNN_In = (2*_LNN_In); 
				} else if (!((1))) {
					_NN_In = _NN_In + (6084); _LNN_In = (468); _SNN_In = (2*_LNN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
				if (_SNN_In) {
					AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+24672+1092*((D0Ind_Total)%2)),
							_SNN_In, 3042, _LNN_In, 0, &UchanHR1);
				}
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+24672+1092*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+1092*((D0Ind_Total+1)%2)),
							_SN_In, 0, &DmaR_Evt1);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+1092*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (((T0Ind_Last)?5:7)-1*(T0Ind==0));
				KerArg1->UsedH = (unsigned short int) (((T0Ind_Last)?5:7)-1*(T0Ind==0));
				KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+2200+((D0Ind)*36));
				KerArg1->Pad = (v4s) ((v4s){1,1,1*(T0Ind==0),1*(T0Ind_Last)});
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				_SN_In = _SNN_In;_LN_In = _LNN_In;
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->H = (unsigned short int) (T0Ind_Last?4:5);
			KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+3352+3120*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+26856+3120*((T0Ind_Total+-1)%2)),
						_SP_Out, 3042, _LP_Out, 1, &UchanHR2);
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+26856+3120*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+3352+3120*((T0Ind_Total)%2)),
					_SC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
			_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (390); _LC_Out = ((T0Ind_NextLast)?312:390); _SC_Out = (8*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+26856+3120*((T0Ind_Total+-1)%2)), _SP_Out, 3042, _LP_Out, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S11_MatAdd_8x39x39(
		short int * __restrict__ In1,
		short int * __restrict__ In2,
		short int * __restrict__ Out)

{
	/* Shared L1: 14976 bytes, L2 buffer: 14976 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	AT_HYPERRAM_CL_EVENT UchanHR2;
	KerMat3_fp_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int D0Ind, D0Ind_Last, D0Ind_NextLast, D0Ind_NextNextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast, T0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _NN_In1;
	unsigned int _SN_In1, _SNN_In1;
	unsigned int _LN_In1, _LNN_In1;
	unsigned int _N_In2;
	unsigned int _SN_In2;
	unsigned int _LN_In2;
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	unsigned int _LPP_Out, _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D0 Dim: Init: 8, Tiled: 1][Tile0 Dim: 10]
	Ker Arg: In1, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 10 logical tiles, 10 physical tiles
			Total Size: 24336 [D0, [0 x 24336, 24336]][Tile0, 10:[39x4, 8:39x4, 39x3], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 24336, 24336]][Tile0, 10:[39x4, 8:39x4, 39x3], 2]
		Tile0: [0, 2496, 312], Tile1: [312, 2496, 312], Tile2; [624, 2496, 312]
	Ker Arg: In2, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 10 logical tiles, 10 physical tiles
			Total Size: 24336 [D0, [0 x 24336, 24336]][Tile0, 10:[39x4, 8:39x4, 39x3], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 24336, 24336]][Tile0, 10:[39x4, 8:39x4, 39x3], 2]
		Tile0: [0, 2496, 312], Tile1: [312, 2496, 312], Tile2; [624, 2496, 312]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 10 logical tiles, 10 physical tiles
			Total Size: 24336 [D0, [0 x 24336, 24336]][Tile0, 10:[39x4, 8:39x4, 39x3], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 24336, 24336]][Tile0, 10:[39x4, 8:39x4, 39x3], 2]
		Tile0: [0, 2496, 312], Tile1: [312, 2496, 312], Tile2; [624, 2496, 312]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->W = (unsigned short int) (39);
	KerArg0->N = (unsigned short int) (8);
	KerArg0->LB = (int) (-32768);
	KerArg0->UB = (int) (32767);
	KerArg0->In1_Q = (unsigned char) (12);
	KerArg0->In2_Q = (unsigned char) (12);
	KerArg0->Out_Q = (unsigned char) (11);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In1+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+29664+0), 2496, 3042, 312, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In1 */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In1+312), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+29664+2496), 2496, 3042, 312, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+29664+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 2496, 0, &DmaR_Evt1);
	_NN_In1=312; _SN_In1=2496;
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In2+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+4992+0), 2496, 3042, 312, 0, &DmaR_Evt2);
	_N_In2=0;
	_C_Out=0; _SC_Out=2496; _LC_Out=312;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D0 */
		int D0Ind_Last = 1, D0Ind_NextLast = 1, D0Ind_NextNextLast = 1;
		for (T0Ind=0; T0Ind<10; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==9), T0Ind_NextLast = ((T0Ind+1)==9), T0Ind_NextNextLast = ((T0Ind+2)==9);
			/*================================= Prepare Tiles ===================================*/
			_SNN_In1 = 0;
			if (!(T0Ind_Last)) {
				if (!(T0Ind_NextLast)) {
					_NN_In1 = _NN_In1 + (312); _LNN_In1 = ((T0Ind_NextNextLast)?234:312); _SNN_In1 = (8*_LNN_In1); 
				}
			}
			_SN_In2 = 0;
			if (!(T0Ind_Last)) {
				_N_In2 = _N_In2 + (312); _LN_In2 = ((T0Ind_NextLast)?234:312); _SN_In2 = (8*_LN_In2); 
			}
			/*============================= End Prepare Tiles ===================================*/
			/*================================= Read Tiles ======================================*/
			AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In1 */
			if (_SNN_In1) {
				AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In1+_NN_In1), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+29664+2496*((T0Ind_Total)%2)),
						_SNN_In1, 3042, _LNN_In1, 0, &UchanHR1);
			}
			AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In1 */
			if (_SN_In1) {
				AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+29664+2496*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+2496*((T0Ind_Total+1)%2)),
						_SN_In1, 0, &DmaR_Evt1);
			}
			AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In2 */
			if (_SN_In2) {
				AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In2+_N_In2), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+4992+2496*((T0Ind_Total+1)%2)),
						_SN_In2, 3042, _LN_In2, 0, &DmaR_Evt2);
			}
			/*============================= End Read Tiles ======================================*/
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In1 = (short int *__restrict__) (resnet_L1_Memory+0+2496*((T0Ind_Total)%2));
			KerArg0->In2 = (short int *__restrict__) (resnet_L1_Memory+4992+2496*((T0Ind_Total)%2));
			KerArg0->Out = (short int *__restrict__) (resnet_L1_Memory+9984+2496*((T0Ind_Total)%2));
			KerArg0->H = (unsigned short int) (T0Ind_Last?3:4);
			AT_FORK(gap_ncore(), (void *) KerParMatAddDynAdjust_fp, (void *) KerArg0);
			__CALL(KerParMatAddDynAdjust_fp, KerArg0);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+24672+2496*((T0Ind_Total+-1)%2)),
						_SP_Out, 3042, _LP_Out, 1, &UchanHR2);
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+24672+2496*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+9984+2496*((T0Ind_Total)%2)),
					_SC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SN_In1 = _SNN_In1;_LN_In1 = _LNN_In1;
			_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
			_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (312); _LC_Out = ((T0Ind_NextLast)?234:312); _SC_Out = (8*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+24672+2496*((T0Ind_Total+-1)%2)), _SP_Out, 3042, _LP_Out, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S14_Conv2d_8x8x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 15832 bytes, L2 buffer: 9592 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	KerSetBias_fpd_fp_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConv_DP_fp_T S_KerArg1, *KerArg1 = &S_KerArg1;
	KerDP_fp_T S_KerArg2, *KerArg2 = &S_KerArg2;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Last;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast, T0Ind_NextNextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast, D0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _NN_In;
	unsigned int _SN_In, _SNN_In;
	unsigned int _LN_In, _LNN_In;
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	unsigned int _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 8, Tiled: 1][Tile0 Dim: 8][D0 Dim: Init: 8, Tiled: 4]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 32 logical tiles, 32 physical tiles
			Total Size: 24336 [D0, [3 x 6084, 6084]][Tile0, 8:[39x6, 6:39x7, 39x5], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 8:[39x6, 2:39x7, 39x5], 2][D0, [3 x 6084, 6084]]
		Tile0: [0, 936, 468], Tile1: [6084, 936, 468], Tile2; [12168, 936, 468]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 16 [D1, [0 x 16, 16]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 16, 16]]
		Tile0: [0, 16, 16], Tile1: [0, 16, 16], Tile2; [0, 16, 16]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 4 logical tiles, 1 physical tiles
			Total Size: 1152 [D1, [0 x 1152, 1152]][D0, [3 x 36, 36]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 1152, 1152]][D0, [3 x 36, 36]]
		Tile0: [0, 1152, 1152], Tile1: [0, 1152, 1152], Tile2; [0, 1152, 1152]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 8 logical tiles, 8 physical tiles
			Total Size: 24336 [D1, [0 x 24336, 24336]][Tile0, 8:[39x5, 6:39x5, 39x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 24336, 24336]][Tile0, 8:[39x5, 6:39x5, 39x4], 2]
		Tile0: [0, 3120, 390], Tile1: [390, 3120, 390], Tile2; [780, 3120, 390]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 8 logical tiles, 1 physical tiles
			Total Size: 48672 [D1, [0 x 48672, 48672]][Tile0, 8:[39x5, 6:39x5, 39x4], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 48672, 48672]][Tile0, 8:[39x5, 6:39x5, 39x4], 4]
		Tile0: [0, 6240, 780], Tile1: [0, 6240, 780], Tile2; [0, 6240, 780]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+9592);
	KerArg0->W = (unsigned short int) (39);
	KerArg0->OutFeatures = (unsigned short int) (8);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+2184);
	KerArg0->NormBias = (signed char) (12);
	KerArg1->W = (unsigned short int) (39);
	KerArg1->UsedW = (unsigned short int) (39);
	KerArg1->InFeatures = (unsigned short int) (2);
	KerArg1->OutFeatures = (unsigned short int) (8);
	KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+2200);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+9592);
	KerArg1->Norm = (unsigned char) (14);
	KerArg1->TotalInFeatures = (short int) (8);
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+9592);
	KerArg2->W = (unsigned short int) (39);
	KerArg2->Norm = (unsigned char) (14);
	KerArg2->InFeatures = (unsigned short int) (8);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+336+0), 936, 3042, 468, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+6084), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+336+1092), 936, 3042, 468, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+336+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 936, 0, &DmaR_Evt1);
	_NN_In=6084; _SN_In=936;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+2184), 16, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+2200), 1152, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
	_C_Out=0; _SC_Out=3120; _LC_Out=390;
	_SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<8; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==7), T0Ind_NextLast = ((T0Ind+1)==7), T0Ind_NextNextLast = ((T0Ind+2)==7);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->H = (unsigned short int) (T0Ind_Last?4:5);
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<4; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==3), D0Ind_NextLast = ((D0Ind+1)==3), D0Ind_NextNextLast = ((D0Ind+2)==3);
				/*================================= Prepare Tiles ===================================*/
				_SNN_In = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_In = _NN_In + (6084); _LNN_In = ((T0Ind_Last)?390:(546-78*(T0Ind==0))); _SNN_In = (2*_LNN_In); 
					} else if (!(T0Ind_Last)) {
						_NN_In = _NN_In + (390-(78*(T0Ind==0)))+(-18252); _LNN_In = ((T0Ind_NextLast)?390:546); _SNN_In = (2*_LNN_In); 
					} else if (!(1)) {
						_NN_In = _NN_In + (-2652)+(-18252); _LNN_In = (468); _SNN_In = (2*_LNN_In); 
					}
				} else if (!(T0Ind_Last)) {
					_NN_In = _NN_In + (6084); _LNN_In = ((T0Ind_NextLast)?390:546); _SNN_In = (2*_LNN_In); 
				} else if (!((1))) {
					_NN_In = _NN_In + (6084); _LNN_In = (468); _SNN_In = (2*_LNN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
				if (_SNN_In) {
					AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+336+1092*((D0Ind_Total)%2)),
							_SNN_In, 3042, _LNN_In, 0, &UchanHR1);
				}
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+336+1092*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+1092*((D0Ind_Total+1)%2)),
							_SN_In, 0, &DmaR_Evt1);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+1092*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (((T0Ind_Last)?5:7)-1*(T0Ind==0));
				KerArg1->UsedH = (unsigned short int) (((T0Ind_Last)?5:7)-1*(T0Ind==0));
				KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+2200+((D0Ind)*36));
				KerArg1->Pad = (v4s) ((v4s){1,1,1*(T0Ind==0),1*(T0Ind_Last)});
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				_SN_In = _SNN_In;_LN_In = _LNN_In;
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->H = (unsigned short int) (T0Ind_Last?4:5);
			KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+3352+3120*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+3352+3120*((T0Ind_Total)%2)),
					_SC_Out, 3042, _LC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (390); _LC_Out = ((T0Ind_NextLast)?312:390); _SC_Out = (8*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S17_Conv2d_8x8x3x3(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 15832 bytes, L2 buffer: 9592 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	KerSetBias_fpd_fp_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConv_DP_fp_T S_KerArg1, *KerArg1 = &S_KerArg1;
	KerDP_fp_T S_KerArg2, *KerArg2 = &S_KerArg2;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Last;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast;
	/* User kernel arguments related variables */
	unsigned int _N_In;
	unsigned int _SN_In;
	unsigned int _LN_In;
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	unsigned int _LPP_Out, _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 8, Tiled: 1][Tile0 Dim: 8][D0 Dim: Init: 8, Tiled: 4]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 32 logical tiles, 32 physical tiles
			Total Size: 24336 [D0, [3 x 6084, 6084]][Tile0, 8:[39x6, 6:39x7, 39x5], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 8:[39x6, 2:39x7, 39x5], 2][D0, [3 x 6084, 6084]]
		Tile0: [0, 936, 468], Tile1: [6084, 936, 468], Tile2; [12168, 936, 468]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 16 [D1, [0 x 16, 16]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 16, 16]]
		Tile0: [0, 16, 16], Tile1: [0, 16, 16], Tile2; [0, 16, 16]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 4 logical tiles, 1 physical tiles
			Total Size: 1152 [D1, [0 x 1152, 1152]][D0, [3 x 36, 36]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 1152, 1152]][D0, [3 x 36, 36]]
		Tile0: [0, 1152, 1152], Tile1: [0, 1152, 1152], Tile2; [0, 1152, 1152]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 8 logical tiles, 8 physical tiles
			Total Size: 24336 [D1, [0 x 24336, 24336]][Tile0, 8:[39x5, 6:39x5, 39x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 24336, 24336]][Tile0, 8:[39x5, 6:39x5, 39x4], 2]
		Tile0: [0, 3120, 390], Tile1: [390, 3120, 390], Tile2; [780, 3120, 390]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 8 logical tiles, 1 physical tiles
			Total Size: 48672 [D1, [0 x 48672, 48672]][Tile0, 8:[39x5, 6:39x5, 39x4], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 48672, 48672]][Tile0, 8:[39x5, 6:39x5, 39x4], 4]
		Tile0: [0, 6240, 780], Tile1: [0, 6240, 780], Tile2; [0, 6240, 780]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+9592);
	KerArg0->W = (unsigned short int) (39);
	KerArg0->OutFeatures = (unsigned short int) (8);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+2184);
	KerArg0->NormBias = (signed char) (13);
	KerArg1->W = (unsigned short int) (39);
	KerArg1->UsedW = (unsigned short int) (39);
	KerArg1->InFeatures = (unsigned short int) (2);
	KerArg1->OutFeatures = (unsigned short int) (8);
	KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+2200);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+9592);
	KerArg1->Norm = (unsigned char) (15);
	KerArg1->TotalInFeatures = (short int) (8);
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+9592);
	KerArg2->W = (unsigned short int) (39);
	KerArg2->Norm = (unsigned char) (15);
	KerArg2->InFeatures = (unsigned short int) (8);
	KerArg2->LB = (int) (-32768);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 936, 3042, 468, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+2184), 16, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+2200), 1152, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
	_C_Out=0; _SC_Out=3120; _LC_Out=390;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<8; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==7), T0Ind_NextLast = ((T0Ind+1)==7);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->H = (unsigned short int) (T0Ind_Last?4:5);
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<4; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==3), D0Ind_NextLast = ((D0Ind+1)==3);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (6084); _LN_In = ((T0Ind_Last)?390:(546-78*(T0Ind==0))); _SN_In = (2*_LN_In); 
				} else if (!(T0Ind_Last)) {
					_N_In = _N_In + (390-(78*(T0Ind==0)))+(-18252); _LN_In = ((T0Ind_NextLast)?390:546); _SN_In = (2*_LN_In); 
				} else if (!(1)) {
					_N_In = _N_In + (-2652)+(-18252); _LN_In = (468); _SN_In = (2*_LN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+1092*((D0Ind_Total+1)%2)),
							_SN_In, 3042, _LN_In, 0, &DmaR_Evt1);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+1092*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (((T0Ind_Last)?5:7)-1*(T0Ind==0));
				KerArg1->UsedH = (unsigned short int) (((T0Ind_Last)?5:7)-1*(T0Ind==0));
				KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+2200+((D0Ind)*36));
				KerArg1->Pad = (v4s) ((v4s){1,1,1*(T0Ind==0),1*(T0Ind_Last)});
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->H = (unsigned short int) (T0Ind_Last?4:5);
			KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+3352+3120*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+26856+3120*((T0Ind_Total+-1)%2)),
						_SP_Out, 3042, _LP_Out, 1, &UchanHR1);
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+26856+3120*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+3352+3120*((T0Ind_Total)%2)),
					_SC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
			_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (390); _LC_Out = ((T0Ind_NextLast)?312:390); _SC_Out = (8*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+26856+3120*((T0Ind_Total+-1)%2)), _SP_Out, 3042, _LP_Out, 1, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S18_MatAdd_8x39x39(
		short int * __restrict__ In1,
		short int * __restrict__ In2,
		short int * __restrict__ Out)

{
	/* Shared L1: 14976 bytes, L2 buffer: 14976 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	AT_HYPERRAM_CL_EVENT UchanHR2;
	KerMat3_fp_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int D0Ind, D0Ind_Last, D0Ind_NextLast, D0Ind_NextNextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast, T0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _NN_In1;
	unsigned int _SN_In1, _SNN_In1;
	unsigned int _LN_In1, _LNN_In1;
	unsigned int _NN_In2;
	unsigned int _SN_In2, _SNN_In2;
	unsigned int _LN_In2, _LNN_In2;
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	unsigned int _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D0 Dim: Init: 8, Tiled: 1][Tile0 Dim: 10]
	Ker Arg: In1, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 10 logical tiles, 10 physical tiles
			Total Size: 24336 [D0, [0 x 24336, 24336]][Tile0, 10:[39x4, 8:39x4, 39x3], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 24336, 24336]][Tile0, 10:[39x4, 8:39x4, 39x3], 2]
		Tile0: [0, 2496, 312], Tile1: [312, 2496, 312], Tile2; [624, 2496, 312]
	Ker Arg: In2, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 10 logical tiles, 10 physical tiles
			Total Size: 24336 [D0, [0 x 24336, 24336]][Tile0, 10:[39x4, 8:39x4, 39x3], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 24336, 24336]][Tile0, 10:[39x4, 8:39x4, 39x3], 2]
		Tile0: [0, 2496, 312], Tile1: [312, 2496, 312], Tile2; [624, 2496, 312]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 10 logical tiles, 10 physical tiles
			Total Size: 24336 [D0, [0 x 24336, 24336]][Tile0, 10:[39x4, 8:39x4, 39x3], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 24336, 24336]][Tile0, 10:[39x4, 8:39x4, 39x3], 2]
		Tile0: [0, 2496, 312], Tile1: [312, 2496, 312], Tile2; [624, 2496, 312]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->W = (unsigned short int) (39);
	KerArg0->N = (unsigned short int) (8);
	KerArg0->LB = (int) (-32768);
	KerArg0->UB = (int) (32767);
	KerArg0->In1_Q = (unsigned char) (12);
	KerArg0->In2_Q = (unsigned char) (11);
	KerArg0->Out_Q = (unsigned char) (11);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In1+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+29664+0), 2496, 3042, 312, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In1 */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In1+312), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+29664+2496), 2496, 3042, 312, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+29664+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 2496, 0, &DmaR_Evt1);
	_NN_In1=312; _SN_In1=2496;
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+24672+0), 2496, 3042, 312, 0, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read In2 */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+312), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+24672+2496), 2496, 3042, 312, 0, &UchanHR2);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+24672+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+4992+0), 2496, 0, &DmaR_Evt2);
	_NN_In2=312; _SN_In2=2496;
	_C_Out=0; _SC_Out=2496; _LC_Out=312;
	_SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D0 */
		int D0Ind_Last = 1, D0Ind_NextLast = 1, D0Ind_NextNextLast = 1;
		for (T0Ind=0; T0Ind<10; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==9), T0Ind_NextLast = ((T0Ind+1)==9), T0Ind_NextNextLast = ((T0Ind+2)==9);
			/*================================= Prepare Tiles ===================================*/
			_SNN_In1 = 0;
			if (!(T0Ind_Last)) {
				if (!(T0Ind_NextLast)) {
					_NN_In1 = _NN_In1 + (312); _LNN_In1 = ((T0Ind_NextNextLast)?234:312); _SNN_In1 = (8*_LNN_In1); 
				}
			}
			_SNN_In2 = 0;
			if (!(T0Ind_Last)) {
				if (!(T0Ind_NextLast)) {
					_NN_In2 = _NN_In2 + (312); _LNN_In2 = ((T0Ind_NextNextLast)?234:312); _SNN_In2 = (8*_LNN_In2); 
				}
			}
			/*============================= End Prepare Tiles ===================================*/
			/*================================= Read Tiles ======================================*/
			AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In1 */
			if (_SNN_In1) {
				AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In1+_NN_In1), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+29664+2496*((T0Ind_Total)%2)),
						_SNN_In1, 3042, _LNN_In1, 0, &UchanHR1);
			}
			AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In1 */
			if (_SN_In1) {
				AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+29664+2496*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+2496*((T0Ind_Total+1)%2)),
						_SN_In1, 0, &DmaR_Evt1);
			}
			AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read In2 */
			if (_SNN_In2) {
				AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+_NN_In2), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+24672+2496*((T0Ind_Total)%2)),
						_SNN_In2, 3042, _LNN_In2, 0, &UchanHR2);
			}
			AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In2 */
			if (_SN_In2) {
				AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+24672+2496*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+4992+2496*((T0Ind_Total+1)%2)),
						_SN_In2, 0, &DmaR_Evt2);
			}
			/*============================= End Read Tiles ======================================*/
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In1 = (short int *__restrict__) (resnet_L1_Memory+0+2496*((T0Ind_Total)%2));
			KerArg0->In2 = (short int *__restrict__) (resnet_L1_Memory+4992+2496*((T0Ind_Total)%2));
			KerArg0->Out = (short int *__restrict__) (resnet_L1_Memory+9984+2496*((T0Ind_Total)%2));
			KerArg0->H = (unsigned short int) (T0Ind_Last?3:4);
			AT_FORK(gap_ncore(), (void *) KerParMatAddDynAdjust_fp, (void *) KerArg0);
			__CALL(KerParMatAddDynAdjust_fp, KerArg0);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+9984+2496*((T0Ind_Total)%2)),
					_SC_Out, 3042, _LC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SN_In1 = _SNN_In1;_LN_In1 = _LNN_In1;
			_SN_In2 = _SNN_In2;_LN_In2 = _LNN_In2;
			_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (312); _LC_Out = ((T0Ind_NextLast)?234:312); _SC_Out = (8*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S21_Conv2d_16x8x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 15384 bytes, L2 buffer: 10264 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaW_Evt1;
	KerSetBias_fpd_fp_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConv_DP_fp_T S_KerArg1, *KerArg1 = &S_KerArg1;
	KerDP_fp_T S_KerArg2, *KerArg2 = &S_KerArg2;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Last;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast;
	/* User kernel arguments related variables */
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	unsigned int _LP_Out, _LC_Out;
	unsigned int _N_In;
	unsigned int _SN_In;
	unsigned int _LN_In;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 16, Tiled: 1][Tile0 Dim: 5][D0 Dim: Init: 8, Tiled: 4]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 5 logical tiles, 5 physical tiles
			Total Size: 12800 [D1, [0 x 12800, 12800]][Tile0, 5:[20x4, 3:20x4, 20x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 12800, 12800]][Tile0, 5:[20x4, 3:20x4, 20x4], 2]
		Tile0: [0, 2560, 160], Tile1: [160, 2560, 160], Tile2; [320, 2560, 160]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 32 [D1, [0 x 32, 32]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 32, 32]]
		Tile0: [0, 32, 32], Tile1: [0, 32, 32], Tile2; [0, 32, 32]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 4 logical tiles, 1 physical tiles
			Total Size: 2304 [D1, [0 x 2304, 2304]][D0, [3 x 576, 576]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 2304, 2304]][D0, [3 x 576, 576]]
		Tile0: [0, 2304, 2304], Tile1: [0, 2304, 2304], Tile2; [0, 2304, 2304]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 20 logical tiles, 20 physical tiles
			Total Size: 24336 [D0, [3 x 6084, 6084]][Tile0, 5:[39x8, 3:39x9, 39x8], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 5:[39x8, 2:39x9, 39x8], 2][D0, [3 x 6084, 6084]]
		Tile0: [0, 1248, 624], Tile1: [6084, 1248, 624], Tile2; [12168, 1248, 624]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 5 logical tiles, 1 physical tiles
			Total Size: 25600 [D1, [0 x 25600, 25600]][Tile0, 5:[20x4, 3:20x4, 20x4], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 25600, 25600]][Tile0, 5:[20x4, 3:20x4, 20x4], 4]
		Tile0: [0, 5120, 320], Tile1: [0, 5120, 320], Tile2; [0, 5120, 320]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+10264);
	KerArg0->W = (unsigned short int) (20);
	KerArg0->H = (unsigned short int) (4);
	KerArg0->OutFeatures = (unsigned short int) (16);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+2808);
	KerArg0->NormBias = (signed char) (12);
	KerArg1->W = (unsigned short int) (39);
	KerArg1->UsedW = (unsigned short int) (39);
	KerArg1->InFeatures = (unsigned short int) (2);
	KerArg1->OutFeatures = (unsigned short int) (16);
	KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+2840);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+10264);
	KerArg1->Norm = (unsigned char) (14);
	KerArg1->TotalInFeatures = (short int) (8);
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+10264);
	KerArg2->W = (unsigned short int) (20);
	KerArg2->H = (unsigned short int) (4);
	KerArg2->Norm = (unsigned char) (14);
	KerArg2->InFeatures = (unsigned short int) (16);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	_C_Out=0; _SC_Out=2560; _LC_Out=160;
	_SP_Out=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+2808), 32, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+2840), 2304, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Filter */
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 1248, 3042, 624, 0, &DmaR_Evt3);
	_N_In=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<5; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==4), T0Ind_NextLast = ((T0Ind+1)==4);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<4; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==3), D0Ind_NextLast = ((D0Ind+1)==3);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (6084); _LN_In = ((T0Ind_Last)?624:(702-78*(T0Ind==0))); _SN_In = (2*_LN_In); 
				} else if (!(T0Ind_Last)) {
					_N_In = _N_In + (624-(78*(T0Ind==0)))+(-18252); _LN_In = ((T0Ind_NextLast)?624:702); _SN_In = (2*_LN_In); 
				} else if (!(1)) {
					_N_In = _N_In + (-2418)+(-18252); _LN_In = (624); _SN_In = (2*_LN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+1404*((D0Ind_Total+1)%2)),
							_SN_In, 3042, _LN_In, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+1404*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (9-1*(T0Ind==0)-1*(T0Ind_Last));
				KerArg1->UsedH = (unsigned short int) (9-1*(T0Ind==0)-1*(T0Ind_Last));
				KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+2840+((D0Ind)*36));
				KerArg1->Pad = (v4s) ((v4s){1,1,1*(T0Ind==0),1*(T0Ind_Last)});
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride2_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride2_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+5144+2560*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+5144+2560*((T0Ind_Total)%2)),
					_SC_Out, 800, _LC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (160); _LC_Out = (160); _SC_Out = (16*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S24_Conv2d_16x8x1x1(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 14208 bytes, L2 buffer: 10368 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	KerSetBias_fpd_fp_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConv_DP_fp_T S_KerArg1, *KerArg1 = &S_KerArg1;
	KerDP_fp_T S_KerArg2, *KerArg2 = &S_KerArg2;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Last;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast;
	/* User kernel arguments related variables */
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	unsigned int _LPP_Out, _LP_Out, _LC_Out;
	unsigned int _N_In;
	unsigned int _SN_In;
	unsigned int _LN_In;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 16, Tiled: 1][Tile0 Dim: 7][D0 Dim: Init: 8, Tiled: 1]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 7 logical tiles, 7 physical tiles
			Total Size: 12800 [D1, [0 x 12800, 12800]][Tile0, 7:[20x3, 5:20x3, 20x2], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 12800, 12800]][Tile0, 7:[20x3, 5:20x3, 20x2], 2]
		Tile0: [0, 1920, 120], Tile1: [120, 1920, 120], Tile2; [240, 1920, 120]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 32 [D1, [0 x 32, 32]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 32, 32]]
		Tile0: [0, 32, 32], Tile1: [0, 32, 32], Tile2; [0, 32, 32]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 256 [D1, [0 x 256, 256]][D0, [0 x 256, 256]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 256, 256]][D0, [0 x 256, 256]]
		Tile0: [0, 256, 256], Tile1: [0, 256, 256], Tile2; [0, 256, 256]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 7 logical tiles, 7 physical tiles
			Total Size: 24336 [D0, [0 x 24336, 24336]][Tile0, 7:[39x5, 5:39x5, 39x3], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 7:[39x5], 2][D0, [0 x 24336, 24336]]
		Tile0: [0, 3120, 390], Tile1: [468, 3120, 390], Tile2; [936, 3120, 390]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 7 logical tiles, 1 physical tiles
			Total Size: 25600 [D1, [0 x 25600, 25600]][Tile0, 7:[20x3, 5:20x3, 20x2], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 25600, 25600]][Tile0, 7:[20x3, 5:20x3, 20x2], 4]
		Tile0: [0, 3840, 240], Tile1: [0, 3840, 240], Tile2; [0, 3840, 240]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+10368);
	KerArg0->W = (unsigned short int) (20);
	KerArg0->OutFeatures = (unsigned short int) (16);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+6240);
	KerArg0->NormBias = (signed char) (12);
	KerArg1->W = (unsigned short int) (39);
	KerArg1->UsedW = (unsigned short int) (39);
	KerArg1->InFeatures = (unsigned short int) (8);
	KerArg1->OutFeatures = (unsigned short int) (16);
	KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+6272);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+10368);
	KerArg1->Norm = (unsigned char) (14);
	KerArg1->TotalInFeatures = (short int) (8);
	KerArg1->Pad = (v4s) 0;
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+10368);
	KerArg2->W = (unsigned short int) (20);
	KerArg2->Norm = (unsigned char) (14);
	KerArg2->InFeatures = (unsigned short int) (16);
	KerArg2->LB = (int) (-32768);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	_C_Out=0; _SC_Out=1920; _LC_Out=120;
	_SPP_Out=0; _SP_Out=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+6240), 32, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+6272), 256, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Filter */
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 3120, 3042, 390, 0, &DmaR_Evt3);
	_N_In=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<7; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==6), T0Ind_NextLast = ((T0Ind+1)==6);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->H = (unsigned short int) (T0Ind_Last?2:3);
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			{ /* Single iteration on D0 */
				int D0Ind_Last = 1, D0Ind_NextLast = 1;
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(T0Ind_Last)) {
					_N_In = _N_In + (468); _LN_In = ((T0Ind_NextLast)?234:390); _SN_In = (8*_LN_In); 
				} else if (!(1)) {
					_N_In = _N_In + (-2808); _LN_In = (390); _SN_In = (8*_LN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+3120*((D0Ind_Total+1)%2)),
							_SN_In, 3042, _LN_In, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+3120*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (T0Ind_Last?3:5);
				KerArg1->UsedH = (unsigned short int) (T0Ind_Last?3:5);
				AT_FORK(gap_ncore(), (void *) KerParConv1x1Stride2_DP_fp, (void *) KerArg1);
				__CALL(KerParConv1x1Stride2_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				/*============================= End Update Arg Pipeline =============================*/
				D0Ind_Total++;
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->H = (unsigned short int) (T0Ind_Last?2:3);
			KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+6528+1920*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+24672+1920*((T0Ind_Total+-1)%2)),
						_SP_Out, 800, _LP_Out, 1, &UchanHR1);
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+24672+1920*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+6528+1920*((T0Ind_Total)%2)),
					_SC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
			_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (120); _LC_Out = ((T0Ind_NextLast)?80:120); _SC_Out = (16*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+24672+1920*((T0Ind_Total+-1)%2)), _SP_Out, 800, _LP_Out, 1, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S27_Conv2d_16x16x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 15840 bytes, L2 buffer: 10720 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	KerSetBias_fpd_fp_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConv_DP_fp_T S_KerArg1, *KerArg1 = &S_KerArg1;
	KerDP_fp_T S_KerArg2, *KerArg2 = &S_KerArg2;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Last;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast;
	/* User kernel arguments related variables */
	unsigned int _N_In;
	unsigned int _SN_In;
	unsigned int _LN_In;
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	unsigned int _LPP_Out, _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 16, Tiled: 1][Tile0 Dim: 5][D0 Dim: Init: 16, Tiled: 8]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 40 logical tiles, 40 physical tiles
			Total Size: 12800 [D0, [7 x 1600, 1600]][Tile0, 5:[20x5, 3:20x6, 20x5], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 5:[20x5, 6:20x6, 20x5], 2][D0, [7 x 1600, 1600]]
		Tile0: [0, 400, 200], Tile1: [1600, 400, 200], Tile2; [3200, 400, 200]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 32 [D1, [0 x 32, 32]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 32, 32]]
		Tile0: [0, 32, 32], Tile1: [0, 32, 32], Tile2; [0, 32, 32]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 8 logical tiles, 1 physical tiles
			Total Size: 4608 [D1, [0 x 4608, 4608]][D0, [7 x 576, 576]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 4608, 4608]][D0, [7 x 576, 576]]
		Tile0: [0, 4608, 4608], Tile1: [0, 4608, 4608], Tile2; [0, 4608, 4608]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 5 logical tiles, 5 physical tiles
			Total Size: 12800 [D1, [0 x 12800, 12800]][Tile0, 5:[20x4, 3:20x4, 20x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 12800, 12800]][Tile0, 5:[20x4, 3:20x4, 20x4], 2]
		Tile0: [0, 2560, 160], Tile1: [160, 2560, 160], Tile2; [320, 2560, 160]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 5 logical tiles, 1 physical tiles
			Total Size: 25600 [D1, [0 x 25600, 25600]][Tile0, 5:[20x4, 3:20x4, 20x4], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 25600, 25600]][Tile0, 5:[20x4, 3:20x4, 20x4], 4]
		Tile0: [0, 5120, 320], Tile1: [0, 5120, 320], Tile2; [0, 5120, 320]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+10720);
	KerArg0->W = (unsigned short int) (20);
	KerArg0->H = (unsigned short int) (4);
	KerArg0->OutFeatures = (unsigned short int) (16);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+960);
	KerArg0->NormBias = (signed char) (15);
	KerArg1->W = (unsigned short int) (20);
	KerArg1->UsedW = (unsigned short int) (20);
	KerArg1->InFeatures = (unsigned short int) (2);
	KerArg1->OutFeatures = (unsigned short int) (16);
	KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+992);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+10720);
	KerArg1->Norm = (unsigned char) (15);
	KerArg1->TotalInFeatures = (short int) (16);
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+10720);
	KerArg2->W = (unsigned short int) (20);
	KerArg2->H = (unsigned short int) (4);
	KerArg2->Norm = (unsigned char) (15);
	KerArg2->InFeatures = (unsigned short int) (16);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 400, 800, 200, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+960), 32, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+992), 4608, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
	_C_Out=0; _SC_Out=2560; _LC_Out=160;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<5; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==4), T0Ind_NextLast = ((T0Ind+1)==4);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<8; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==7), D0Ind_NextLast = ((D0Ind+1)==7);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (1600); _LN_In = ((T0Ind_Last)?200:(240-40*(T0Ind==0))); _SN_In = (2*_LN_In); 
				} else if (!(T0Ind_Last)) {
					_N_In = _N_In + (160-(40*(T0Ind==0)))+(-11200); _LN_In = ((T0Ind_NextLast)?200:240); _SN_In = (2*_LN_In); 
				} else if (!(1)) {
					_N_In = _N_In + (-600)+(-11200); _LN_In = (200); _SN_In = (2*_LN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+480*((D0Ind_Total+1)%2)),
							_SN_In, 800, _LN_In, 0, &DmaR_Evt1);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+480*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (6-1*(T0Ind==0)-1*(T0Ind_Last));
				KerArg1->UsedH = (unsigned short int) (6-1*(T0Ind==0)-1*(T0Ind_Last));
				KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+992+((D0Ind)*36));
				KerArg1->Pad = (v4s) ((v4s){1,1,1*(T0Ind==0),1*(T0Ind_Last)});
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+5600+2560*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+37472+2560*((T0Ind_Total+-1)%2)),
						_SP_Out, 800, _LP_Out, 1, &UchanHR1);
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+37472+2560*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+5600+2560*((T0Ind_Total)%2)),
					_SC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
			_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (160); _LC_Out = (160); _SC_Out = (16*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+37472+2560*((T0Ind_Total+-1)%2)), _SP_Out, 800, _LP_Out, 1, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S28_MatAdd_16x20x20(
		short int * __restrict__ In1,
		short int * __restrict__ In2,
		short int * __restrict__ Out)

{
	/* Shared L1: 15360 bytes, L2 buffer: 15360 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	AT_HYPERRAM_CL_EVENT UchanHR2;
	KerMat3_fp_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int D0Ind, D0Ind_Last, D0Ind_NextLast, D0Ind_NextNextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast, T0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _NN_In1;
	unsigned int _SN_In1, _SNN_In1;
	unsigned int _LN_In1, _LNN_In1;
	unsigned int _NN_In2;
	unsigned int _SN_In2, _SNN_In2;
	unsigned int _LN_In2, _LNN_In2;
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	unsigned int _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D0 Dim: Init: 16, Tiled: 1][Tile0 Dim: 5]
	Ker Arg: In1, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 5 logical tiles, 5 physical tiles
			Total Size: 12800 [D0, [0 x 12800, 12800]][Tile0, 5:[20x4, 3:20x4, 20x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 12800, 12800]][Tile0, 5:[20x4, 3:20x4, 20x4], 2]
		Tile0: [0, 2560, 160], Tile1: [160, 2560, 160], Tile2; [320, 2560, 160]
	Ker Arg: In2, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 5 logical tiles, 5 physical tiles
			Total Size: 12800 [D0, [0 x 12800, 12800]][Tile0, 5:[20x4, 3:20x4, 20x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 12800, 12800]][Tile0, 5:[20x4, 3:20x4, 20x4], 2]
		Tile0: [0, 2560, 160], Tile1: [160, 2560, 160], Tile2; [320, 2560, 160]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 5 logical tiles, 5 physical tiles
			Total Size: 12800 [D0, [0 x 12800, 12800]][Tile0, 5:[20x4, 3:20x4, 20x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 12800, 12800]][Tile0, 5:[20x4, 3:20x4, 20x4], 2]
		Tile0: [0, 2560, 160], Tile1: [160, 2560, 160], Tile2; [320, 2560, 160]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->W = (unsigned short int) (20);
	KerArg0->H = (unsigned short int) (4);
	KerArg0->N = (unsigned short int) (16);
	KerArg0->LB = (int) (-32768);
	KerArg0->UB = (int) (32767);
	KerArg0->In1_Q = (unsigned char) (12);
	KerArg0->In2_Q = (unsigned char) (11);
	KerArg0->Out_Q = (unsigned char) (11);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In1+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+18256+0), 2560, 800, 160, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In1 */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In1+160), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+18256+2560), 2560, 800, 160, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+18256+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 2560, 0, &DmaR_Evt1);
	_NN_In1=160; _SN_In1=2560;
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+13136+0), 2560, 800, 160, 0, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read In2 */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+160), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+13136+2560), 2560, 800, 160, 0, &UchanHR2);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+13136+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+5120+0), 2560, 0, &DmaR_Evt2);
	_NN_In2=160; _SN_In2=2560;
	_C_Out=0; _SC_Out=2560; _LC_Out=160;
	_SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D0 */
		int D0Ind_Last = 1, D0Ind_NextLast = 1, D0Ind_NextNextLast = 1;
		for (T0Ind=0; T0Ind<5; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==4), T0Ind_NextLast = ((T0Ind+1)==4), T0Ind_NextNextLast = ((T0Ind+2)==4);
			/*================================= Prepare Tiles ===================================*/
			_SNN_In1 = 0;
			if (!(T0Ind_Last)) {
				if (!(T0Ind_NextLast)) {
					_NN_In1 = _NN_In1 + (160); _LNN_In1 = (160); _SNN_In1 = (16*_LNN_In1); 
				}
			}
			_SNN_In2 = 0;
			if (!(T0Ind_Last)) {
				if (!(T0Ind_NextLast)) {
					_NN_In2 = _NN_In2 + (160); _LNN_In2 = (160); _SNN_In2 = (16*_LNN_In2); 
				}
			}
			/*============================= End Prepare Tiles ===================================*/
			/*================================= Read Tiles ======================================*/
			AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In1 */
			if (_SNN_In1) {
				AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In1+_NN_In1), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+18256+2560*((T0Ind_Total)%2)),
						_SNN_In1, 800, _LNN_In1, 0, &UchanHR1);
			}
			AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In1 */
			if (_SN_In1) {
				AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+18256+2560*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+2560*((T0Ind_Total+1)%2)),
						_SN_In1, 0, &DmaR_Evt1);
			}
			AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read In2 */
			if (_SNN_In2) {
				AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+_NN_In2), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+13136+2560*((T0Ind_Total)%2)),
						_SNN_In2, 800, _LNN_In2, 0, &UchanHR2);
			}
			AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In2 */
			if (_SN_In2) {
				AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+13136+2560*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+5120+2560*((T0Ind_Total+1)%2)),
						_SN_In2, 0, &DmaR_Evt2);
			}
			/*============================= End Read Tiles ======================================*/
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In1 = (short int *__restrict__) (resnet_L1_Memory+0+2560*((T0Ind_Total)%2));
			KerArg0->In2 = (short int *__restrict__) (resnet_L1_Memory+5120+2560*((T0Ind_Total)%2));
			KerArg0->Out = (short int *__restrict__) (resnet_L1_Memory+10240+2560*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerParMatAddDynAdjust_fp, (void *) KerArg0);
			__CALL(KerParMatAddDynAdjust_fp, KerArg0);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+10240+2560*((T0Ind_Total)%2)),
					_SC_Out, 800, _LC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SN_In1 = _SNN_In1;_LN_In1 = _LNN_In1;
			_SN_In2 = _SNN_In2;_LN_In2 = _LNN_In2;
			_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (160); _LC_Out = (160); _SC_Out = (16*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S31_Conv2d_16x16x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 15840 bytes, L2 buffer: 10720 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaW_Evt1;
	KerSetBias_fpd_fp_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConv_DP_fp_T S_KerArg1, *KerArg1 = &S_KerArg1;
	KerDP_fp_T S_KerArg2, *KerArg2 = &S_KerArg2;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Last;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast;
	/* User kernel arguments related variables */
	unsigned int _N_In;
	unsigned int _SN_In;
	unsigned int _LN_In;
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	unsigned int _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 16, Tiled: 1][Tile0 Dim: 5][D0 Dim: Init: 16, Tiled: 8]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 40 logical tiles, 40 physical tiles
			Total Size: 12800 [D0, [7 x 1600, 1600]][Tile0, 5:[20x5, 3:20x6, 20x5], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 5:[20x5, 6:20x6, 20x5], 2][D0, [7 x 1600, 1600]]
		Tile0: [0, 400, 200], Tile1: [1600, 400, 200], Tile2; [3200, 400, 200]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 32 [D1, [0 x 32, 32]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 32, 32]]
		Tile0: [0, 32, 32], Tile1: [0, 32, 32], Tile2; [0, 32, 32]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 8 logical tiles, 1 physical tiles
			Total Size: 4608 [D1, [0 x 4608, 4608]][D0, [7 x 576, 576]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 4608, 4608]][D0, [7 x 576, 576]]
		Tile0: [0, 4608, 4608], Tile1: [0, 4608, 4608], Tile2; [0, 4608, 4608]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 5 logical tiles, 5 physical tiles
			Total Size: 12800 [D1, [0 x 12800, 12800]][Tile0, 5:[20x4, 3:20x4, 20x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 12800, 12800]][Tile0, 5:[20x4, 3:20x4, 20x4], 2]
		Tile0: [0, 2560, 160], Tile1: [160, 2560, 160], Tile2; [320, 2560, 160]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 5 logical tiles, 1 physical tiles
			Total Size: 25600 [D1, [0 x 25600, 25600]][Tile0, 5:[20x4, 3:20x4, 20x4], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 25600, 25600]][Tile0, 5:[20x4, 3:20x4, 20x4], 4]
		Tile0: [0, 5120, 320], Tile1: [0, 5120, 320], Tile2; [0, 5120, 320]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+10720);
	KerArg0->W = (unsigned short int) (20);
	KerArg0->H = (unsigned short int) (4);
	KerArg0->OutFeatures = (unsigned short int) (16);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+960);
	KerArg0->NormBias = (signed char) (12);
	KerArg1->W = (unsigned short int) (20);
	KerArg1->UsedW = (unsigned short int) (20);
	KerArg1->InFeatures = (unsigned short int) (2);
	KerArg1->OutFeatures = (unsigned short int) (16);
	KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+992);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+10720);
	KerArg1->Norm = (unsigned char) (13);
	KerArg1->TotalInFeatures = (short int) (16);
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+10720);
	KerArg2->W = (unsigned short int) (20);
	KerArg2->H = (unsigned short int) (4);
	KerArg2->Norm = (unsigned char) (13);
	KerArg2->InFeatures = (unsigned short int) (16);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 400, 800, 200, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+960), 32, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+992), 4608, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
	_C_Out=0; _SC_Out=2560; _LC_Out=160;
	_SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<5; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==4), T0Ind_NextLast = ((T0Ind+1)==4);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<8; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==7), D0Ind_NextLast = ((D0Ind+1)==7);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (1600); _LN_In = ((T0Ind_Last)?200:(240-40*(T0Ind==0))); _SN_In = (2*_LN_In); 
				} else if (!(T0Ind_Last)) {
					_N_In = _N_In + (160-(40*(T0Ind==0)))+(-11200); _LN_In = ((T0Ind_NextLast)?200:240); _SN_In = (2*_LN_In); 
				} else if (!(1)) {
					_N_In = _N_In + (-600)+(-11200); _LN_In = (200); _SN_In = (2*_LN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+480*((D0Ind_Total+1)%2)),
							_SN_In, 800, _LN_In, 0, &DmaR_Evt1);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+480*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (6-1*(T0Ind==0)-1*(T0Ind_Last));
				KerArg1->UsedH = (unsigned short int) (6-1*(T0Ind==0)-1*(T0Ind_Last));
				KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+992+((D0Ind)*36));
				KerArg1->Pad = (v4s) ((v4s){1,1,1*(T0Ind==0),1*(T0Ind_Last)});
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+5600+2560*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+5600+2560*((T0Ind_Total)%2)),
					_SC_Out, 800, _LC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (160); _LC_Out = (160); _SC_Out = (16*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S34_Conv2d_16x16x3x3(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 15840 bytes, L2 buffer: 10720 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	KerSetBias_fpd_fp_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConv_DP_fp_T S_KerArg1, *KerArg1 = &S_KerArg1;
	KerDP_fp_T S_KerArg2, *KerArg2 = &S_KerArg2;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Last;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast;
	/* User kernel arguments related variables */
	unsigned int _N_In;
	unsigned int _SN_In;
	unsigned int _LN_In;
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	unsigned int _LPP_Out, _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 16, Tiled: 1][Tile0 Dim: 5][D0 Dim: Init: 16, Tiled: 8]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 40 logical tiles, 40 physical tiles
			Total Size: 12800 [D0, [7 x 1600, 1600]][Tile0, 5:[20x5, 3:20x6, 20x5], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 5:[20x5, 6:20x6, 20x5], 2][D0, [7 x 1600, 1600]]
		Tile0: [0, 400, 200], Tile1: [1600, 400, 200], Tile2; [3200, 400, 200]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 32 [D1, [0 x 32, 32]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 32, 32]]
		Tile0: [0, 32, 32], Tile1: [0, 32, 32], Tile2; [0, 32, 32]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 8 logical tiles, 1 physical tiles
			Total Size: 4608 [D1, [0 x 4608, 4608]][D0, [7 x 576, 576]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 4608, 4608]][D0, [7 x 576, 576]]
		Tile0: [0, 4608, 4608], Tile1: [0, 4608, 4608], Tile2; [0, 4608, 4608]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 5 logical tiles, 5 physical tiles
			Total Size: 12800 [D1, [0 x 12800, 12800]][Tile0, 5:[20x4, 3:20x4, 20x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 12800, 12800]][Tile0, 5:[20x4, 3:20x4, 20x4], 2]
		Tile0: [0, 2560, 160], Tile1: [160, 2560, 160], Tile2; [320, 2560, 160]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 5 logical tiles, 1 physical tiles
			Total Size: 25600 [D1, [0 x 25600, 25600]][Tile0, 5:[20x4, 3:20x4, 20x4], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 25600, 25600]][Tile0, 5:[20x4, 3:20x4, 20x4], 4]
		Tile0: [0, 5120, 320], Tile1: [0, 5120, 320], Tile2; [0, 5120, 320]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+10720);
	KerArg0->W = (unsigned short int) (20);
	KerArg0->H = (unsigned short int) (4);
	KerArg0->OutFeatures = (unsigned short int) (16);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+960);
	KerArg0->NormBias = (signed char) (14);
	KerArg1->W = (unsigned short int) (20);
	KerArg1->UsedW = (unsigned short int) (20);
	KerArg1->InFeatures = (unsigned short int) (2);
	KerArg1->OutFeatures = (unsigned short int) (16);
	KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+992);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+10720);
	KerArg1->Norm = (unsigned char) (16);
	KerArg1->TotalInFeatures = (short int) (16);
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+10720);
	KerArg2->W = (unsigned short int) (20);
	KerArg2->H = (unsigned short int) (4);
	KerArg2->Norm = (unsigned char) (16);
	KerArg2->InFeatures = (unsigned short int) (16);
	KerArg2->LB = (int) (-32768);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 400, 800, 200, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+960), 32, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+992), 4608, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
	_C_Out=0; _SC_Out=2560; _LC_Out=160;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<5; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==4), T0Ind_NextLast = ((T0Ind+1)==4);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<8; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==7), D0Ind_NextLast = ((D0Ind+1)==7);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (1600); _LN_In = ((T0Ind_Last)?200:(240-40*(T0Ind==0))); _SN_In = (2*_LN_In); 
				} else if (!(T0Ind_Last)) {
					_N_In = _N_In + (160-(40*(T0Ind==0)))+(-11200); _LN_In = ((T0Ind_NextLast)?200:240); _SN_In = (2*_LN_In); 
				} else if (!(1)) {
					_N_In = _N_In + (-600)+(-11200); _LN_In = (200); _SN_In = (2*_LN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+480*((D0Ind_Total+1)%2)),
							_SN_In, 800, _LN_In, 0, &DmaR_Evt1);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+480*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (6-1*(T0Ind==0)-1*(T0Ind_Last));
				KerArg1->UsedH = (unsigned short int) (6-1*(T0Ind==0)-1*(T0Ind_Last));
				KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+992+((D0Ind)*36));
				KerArg1->Pad = (v4s) ((v4s){1,1,1*(T0Ind==0),1*(T0Ind_Last)});
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+5600+2560*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+25936+2560*((T0Ind_Total+-1)%2)),
						_SP_Out, 800, _LP_Out, 1, &UchanHR1);
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+25936+2560*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+5600+2560*((T0Ind_Total)%2)),
					_SC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
			_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (160); _LC_Out = (160); _SC_Out = (16*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+25936+2560*((T0Ind_Total+-1)%2)), _SP_Out, 800, _LP_Out, 1, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S35_MatAdd_16x20x20(
		short int * __restrict__ In1,
		short int * __restrict__ In2,
		short int * __restrict__ Out)

{
	/* Shared L1: 15360 bytes, L2 buffer: 15360 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	KerMat3_fp_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int D0Ind, D0Ind_Last, D0Ind_NextLast, D0Ind_NextNextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast, T0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _NN_In1;
	unsigned int _SN_In1, _SNN_In1;
	unsigned int _LN_In1, _LNN_In1;
	unsigned int _N_In2;
	unsigned int _SN_In2;
	unsigned int _LN_In2;
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	unsigned int _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D0 Dim: Init: 16, Tiled: 1][Tile0 Dim: 5]
	Ker Arg: In1, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 5 logical tiles, 5 physical tiles
			Total Size: 12800 [D0, [0 x 12800, 12800]][Tile0, 5:[20x4, 3:20x4, 20x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 12800, 12800]][Tile0, 5:[20x4, 3:20x4, 20x4], 2]
		Tile0: [0, 2560, 160], Tile1: [160, 2560, 160], Tile2; [320, 2560, 160]
	Ker Arg: In2, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 5 logical tiles, 5 physical tiles
			Total Size: 12800 [D0, [0 x 12800, 12800]][Tile0, 5:[20x4, 3:20x4, 20x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 12800, 12800]][Tile0, 5:[20x4, 3:20x4, 20x4], 2]
		Tile0: [0, 2560, 160], Tile1: [160, 2560, 160], Tile2; [320, 2560, 160]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 5 logical tiles, 5 physical tiles
			Total Size: 12800 [D0, [0 x 12800, 12800]][Tile0, 5:[20x4, 3:20x4, 20x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 12800, 12800]][Tile0, 5:[20x4, 3:20x4, 20x4], 2]
		Tile0: [0, 2560, 160], Tile1: [160, 2560, 160], Tile2; [320, 2560, 160]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->W = (unsigned short int) (20);
	KerArg0->H = (unsigned short int) (4);
	KerArg0->N = (unsigned short int) (16);
	KerArg0->LB = (int) (-32768);
	KerArg0->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In1+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+25936+0), 2560, 800, 160, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In1 */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In1+160), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+25936+2560), 2560, 800, 160, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+25936+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 2560, 0, &DmaR_Evt1);
	_NN_In1=160; _SN_In1=2560;
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In2+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+5120+0), 2560, 800, 160, 0, &DmaR_Evt2);
	_N_In2=0;
	_C_Out=0; _SC_Out=2560; _LC_Out=160;
	_SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D0 */
		int D0Ind_Last = 1, D0Ind_NextLast = 1, D0Ind_NextNextLast = 1;
		for (T0Ind=0; T0Ind<5; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==4), T0Ind_NextLast = ((T0Ind+1)==4), T0Ind_NextNextLast = ((T0Ind+2)==4);
			/*================================= Prepare Tiles ===================================*/
			_SNN_In1 = 0;
			if (!(T0Ind_Last)) {
				if (!(T0Ind_NextLast)) {
					_NN_In1 = _NN_In1 + (160); _LNN_In1 = (160); _SNN_In1 = (16*_LNN_In1); 
				}
			}
			_SN_In2 = 0;
			if (!(T0Ind_Last)) {
				_N_In2 = _N_In2 + (160); _LN_In2 = (160); _SN_In2 = (16*_LN_In2); 
			}
			/*============================= End Prepare Tiles ===================================*/
			/*================================= Read Tiles ======================================*/
			AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In1 */
			if (_SNN_In1) {
				AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In1+_NN_In1), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+25936+2560*((T0Ind_Total)%2)),
						_SNN_In1, 800, _LNN_In1, 0, &UchanHR1);
			}
			AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In1 */
			if (_SN_In1) {
				AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+25936+2560*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+2560*((T0Ind_Total+1)%2)),
						_SN_In1, 0, &DmaR_Evt1);
			}
			AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In2 */
			if (_SN_In2) {
				AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In2+_N_In2), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+5120+2560*((T0Ind_Total+1)%2)),
						_SN_In2, 800, _LN_In2, 0, &DmaR_Evt2);
			}
			/*============================= End Read Tiles ======================================*/
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In1 = (short int *__restrict__) (resnet_L1_Memory+0+2560*((T0Ind_Total)%2));
			KerArg0->In2 = (short int *__restrict__) (resnet_L1_Memory+5120+2560*((T0Ind_Total)%2));
			KerArg0->Out = (short int *__restrict__) (resnet_L1_Memory+10240+2560*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerParMatAdd_fp, (void *) KerArg0);
			__CALL(KerParMatAdd_fp, KerArg0);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+10240+2560*((T0Ind_Total)%2)),
					_SC_Out, 800, _LC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SN_In1 = _SNN_In1;_LN_In1 = _LNN_In1;
			_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (160); _LC_Out = (160); _SC_Out = (16*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S38_Conv2d_32x16x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 16000 bytes, L2 buffer: 13440 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaW_Evt1;
	KerSetBias_fpd_fp_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConv_DP_fp_T S_KerArg1, *KerArg1 = &S_KerArg1;
	KerDP_fp_T S_KerArg2, *KerArg2 = &S_KerArg2;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Last;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast;
	/* User kernel arguments related variables */
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	unsigned int _LP_Out, _LC_Out;
	unsigned int _N_In;
	unsigned int _SN_In;
	unsigned int _LN_In;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 32, Tiled: 1][Tile0 Dim: 5][D0 Dim: Init: 16, Tiled: 4]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 5 logical tiles, 5 physical tiles
			Total Size: 6400 [D1, [0 x 6400, 6400]][Tile0, 5:[10x2, 3:10x2, 10x2], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 6400, 6400]][Tile0, 5:[10x2, 3:10x2, 10x2], 2]
		Tile0: [0, 1280, 40], Tile1: [40, 1280, 40], Tile2; [80, 1280, 40]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 64 [D1, [0 x 64, 64]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 64, 64]]
		Tile0: [0, 64, 64], Tile1: [0, 64, 64], Tile2; [0, 64, 64]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 4 logical tiles, 1 physical tiles
			Total Size: 9216 [D1, [0 x 9216, 9216]][D0, [3 x 2304, 2304]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 9216, 9216]][D0, [3 x 2304, 2304]]
		Tile0: [0, 9216, 9216], Tile1: [0, 9216, 9216], Tile2; [0, 9216, 9216]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 20 logical tiles, 20 physical tiles
			Total Size: 12800 [D0, [3 x 3200, 3200]][Tile0, 5:[20x5, 3:20x5, 20x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 5:[20x5, 2:20x5, 20x4], 2][D0, [3 x 3200, 3200]]
		Tile0: [0, 800, 200], Tile1: [3200, 800, 200], Tile2; [6400, 800, 200]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 5 logical tiles, 1 physical tiles
			Total Size: 12800 [D1, [0 x 12800, 12800]][Tile0, 5:[10x2, 3:10x2, 10x2], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 12800, 12800]][Tile0, 5:[10x2, 3:10x2, 10x2], 4]
		Tile0: [0, 2560, 80], Tile1: [0, 2560, 80], Tile2; [0, 2560, 80]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+13440);
	KerArg0->W = (unsigned short int) (10);
	KerArg0->H = (unsigned short int) (2);
	KerArg0->OutFeatures = (unsigned short int) (32);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+1600);
	KerArg0->NormBias = (signed char) (12);
	KerArg1->W = (unsigned short int) (20);
	KerArg1->UsedW = (unsigned short int) (20);
	KerArg1->InFeatures = (unsigned short int) (4);
	KerArg1->OutFeatures = (unsigned short int) (32);
	KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+1664);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+13440);
	KerArg1->Norm = (unsigned char) (14);
	KerArg1->TotalInFeatures = (short int) (16);
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+13440);
	KerArg2->W = (unsigned short int) (10);
	KerArg2->H = (unsigned short int) (2);
	KerArg2->Norm = (unsigned char) (14);
	KerArg2->InFeatures = (unsigned short int) (32);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	_C_Out=0; _SC_Out=1280; _LC_Out=40;
	_SP_Out=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+1600), 64, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+1664), 9216, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Filter */
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 800, 800, 200, 0, &DmaR_Evt3);
	_N_In=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<5; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==4), T0Ind_NextLast = ((T0Ind+1)==4);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<4; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==3), D0Ind_NextLast = ((D0Ind+1)==3);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (3200); _LN_In = ((T0Ind_Last)?160:(200-0*(T0Ind==0))); _SN_In = (4*_LN_In); 
				} else if (!(T0Ind_Last)) {
					_N_In = _N_In + (160)+(-9600); _LN_In = ((T0Ind_NextLast)?160:200); _SN_In = (4*_LN_In); 
				} else if (!(1)) {
					_N_In = _N_In + (-640)+(-9600); _LN_In = (200); _SN_In = (4*_LN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+800*((D0Ind_Total+1)%2)),
							_SN_In, 800, _LN_In, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+800*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (5-0*(T0Ind==0)-1*(T0Ind_Last));
				KerArg1->UsedH = (unsigned short int) (5-0*(T0Ind==0)-1*(T0Ind_Last));
				KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+1664+((D0Ind)*72));
				KerArg1->Pad = (v4s) ((v4s){0,1,0*(T0Ind==0),1*(T0Ind_Last)});
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride2_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride2_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+10880+1280*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+10880+1280*((T0Ind_Total)%2)),
					_SC_Out, 200, _LC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (40); _LC_Out = (40); _SC_Out = (32*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S41_Conv2d_32x16x1x1(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 15168 bytes, L2 buffer: 11328 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaW_Evt1;
	KerSetBias_fpd_fp_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConv_DP_fp_T S_KerArg1, *KerArg1 = &S_KerArg1;
	KerDP_fp_T S_KerArg2, *KerArg2 = &S_KerArg2;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Last;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast;
	/* User kernel arguments related variables */
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	unsigned int _LP_Out, _LC_Out;
	unsigned int _N_In;
	unsigned int _SN_In;
	unsigned int _LN_In;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 32, Tiled: 1][Tile0 Dim: 4][D0 Dim: Init: 16, Tiled: 1]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 4 logical tiles, 4 physical tiles
			Total Size: 6400 [D1, [0 x 6400, 6400]][Tile0, 4:[10x3, 2:10x3, 10x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 6400, 6400]][Tile0, 4:[10x3, 2:10x3, 10x1], 2]
		Tile0: [0, 1920, 60], Tile1: [60, 1920, 60], Tile2; [120, 1920, 60]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 64 [D1, [0 x 64, 64]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 64, 64]]
		Tile0: [0, 64, 64], Tile1: [0, 64, 64], Tile2; [0, 64, 64]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 1024 [D1, [0 x 1024, 1024]][D0, [0 x 1024, 1024]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 1024, 1024]][D0, [0 x 1024, 1024]]
		Tile0: [0, 1024, 1024], Tile1: [0, 1024, 1024], Tile2; [0, 1024, 1024]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 4 logical tiles, 4 physical tiles
			Total Size: 12800 [D0, [0 x 12800, 12800]][Tile0, 4:[20x5, 2:20x5, 20x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 4:[20x5], 2][D0, [0 x 12800, 12800]]
		Tile0: [0, 3200, 200], Tile1: [240, 3200, 200], Tile2; [480, 3200, 200]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 4 logical tiles, 1 physical tiles
			Total Size: 12800 [D1, [0 x 12800, 12800]][Tile0, 4:[10x3, 2:10x3, 10x1], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 12800, 12800]][Tile0, 4:[10x3, 2:10x3, 10x1], 4]
		Tile0: [0, 3840, 120], Tile1: [0, 3840, 120], Tile2; [0, 3840, 120]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+11328);
	KerArg0->W = (unsigned short int) (10);
	KerArg0->OutFeatures = (unsigned short int) (32);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+6400);
	KerArg0->NormBias = (signed char) (12);
	KerArg1->W = (unsigned short int) (20);
	KerArg1->UsedW = (unsigned short int) (19);
	KerArg1->InFeatures = (unsigned short int) (16);
	KerArg1->OutFeatures = (unsigned short int) (32);
	KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+6464);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+11328);
	KerArg1->Norm = (unsigned char) (15);
	KerArg1->TotalInFeatures = (short int) (16);
	KerArg1->Pad = (v4s) 0;
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+11328);
	KerArg2->W = (unsigned short int) (10);
	KerArg2->Norm = (unsigned char) (15);
	KerArg2->InFeatures = (unsigned short int) (32);
	KerArg2->LB = (int) (-32768);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	_C_Out=0; _SC_Out=1920; _LC_Out=60;
	_SP_Out=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+6400), 64, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+6464), 1024, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Filter */
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 3200, 800, 200, 0, &DmaR_Evt3);
	_N_In=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<4; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==3), T0Ind_NextLast = ((T0Ind+1)==3);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->H = (unsigned short int) (T0Ind_Last?1:3);
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			{ /* Single iteration on D0 */
				int D0Ind_Last = 1, D0Ind_NextLast = 1;
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(T0Ind_Last)) {
					_N_In = _N_In + (240); _LN_In = ((T0Ind_NextLast)?40:200); _SN_In = (16*_LN_In); 
				} else if (!(1)) {
					_N_In = _N_In + (-720); _LN_In = (200); _SN_In = (16*_LN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+3200*((D0Ind_Total+1)%2)),
							_SN_In, 800, _LN_In, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+3200*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (T0Ind_Last?1:5);
				KerArg1->UsedH = (unsigned short int) (T0Ind_Last?1:5);
				AT_FORK(gap_ncore(), (void *) KerParConv1x1Stride2_DP_fp, (void *) KerArg1);
				__CALL(KerParConv1x1Stride2_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				/*============================= End Update Arg Pipeline =============================*/
				D0Ind_Total++;
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->H = (unsigned short int) (T0Ind_Last?1:3);
			KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+7488+1920*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+7488+1920*((T0Ind_Total)%2)),
					_SC_Out, 200, _LC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (60); _LC_Out = ((T0Ind_NextLast)?20:60); _SC_Out = (32*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S44_Conv2d_32x32x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 14816 bytes, L2 buffer: 8416 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	KerSetBias_fpd_fp_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConv_DP_fp_T S_KerArg1, *KerArg1 = &S_KerArg1;
	KerDP_fp_T S_KerArg2, *KerArg2 = &S_KerArg2;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Last, D1Ind_NextLast, D1Ind_NextNextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast, D0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _N_In;
	unsigned int _SN_In;
	unsigned int _LN_In;
	unsigned int _NN_Filter;
	unsigned int _SN_Filter, _SNN_Filter;
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	unsigned int _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 32, Tiled: 2][Tile0 Dim: 1][D0 Dim: Init: 32, Tiled: 16]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 16 logical tiles, 16 physical tiles
			Total Size: 6400 [D0, [15 x 400, 400]][Tile0, 1:[10x10], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[10x11, 14:10x12, 10x11], 2][D0, [15 x 400, 400]]
		Tile0: [0, 400, 200], Tile1: [400, 400, 200], Tile2; [800, 400, 200]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 64 [D1, [1 x 32, 32]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 32, 32]]
		Tile0: [0, 64, 64], Tile1: [0, 64, 64], Tile2; [0, 64, 64]
	Ker Arg: Filter, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 32 logical tiles, 32 physical tiles
			Total Size: 18432 [D1, [1 x 9216, 9216]][D0, [15 x 576, 576]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 9216, 9216]][D0, [15 x 576, 576]]
		Tile0: [0, 576, 576], Tile1: [576, 576, 576], Tile2; [1152, 576, 576]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 2 physical tiles
			Total Size: 6400 [D1, [1 x 3200, 3200]][Tile0, 1:[10x10], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 3200, 3200]][Tile0, 1:[10x10], 2]
		Tile0: [0, 3200, 200], Tile1: [3200, 3200, 200], Tile2; [0, 3200, 200]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 12800 [D1, [1 x 6400, 6400]][Tile0, 1:[10x10], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 6400, 6400]][Tile0, 1:[10x10], 4]
		Tile0: [0, 6400, 400], Tile1: [0, 6400, 400], Tile2; [0, 6400, 400]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+8416);
	KerArg0->W = (unsigned short int) (10);
	KerArg0->H = (unsigned short int) (10);
	KerArg0->OutFeatures = (unsigned short int) (16);
	KerArg0->NormBias = (signed char) (15);
	KerArg1->W = (unsigned short int) (10);
	KerArg1->UsedW = (unsigned short int) (10);
	KerArg1->InFeatures = (unsigned short int) (2);
	KerArg1->OutFeatures = (unsigned short int) (16);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+8416);
	KerArg1->Norm = (unsigned char) (15);
	KerArg1->TotalInFeatures = (short int) (2);
	KerArg1->Pad = (v4s) ((v4s){1,1,1,1});
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+8416);
	KerArg2->W = (unsigned short int) (10);
	KerArg2->H = (unsigned short int) (10);
	KerArg2->Norm = (unsigned char) (15);
	KerArg2->InFeatures = (unsigned short int) (16);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 400, 200, 200, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+800), 64, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Filter+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+6736+0), 576, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read Filter */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Filter+576), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+6736+576), 576, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+6736+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+864+0), 576, 0, &DmaR_Evt3);
	_NN_Filter=576; _SN_Filter=576;
	_C_Out=0; _SC_Out=3200; _LC_Out=200;
	_SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	for (D1Ind=0; D1Ind<2; D1Ind++) { /* Iteration on D1 */
		int D1Ind_Last = (D1Ind==1), D1Ind_NextLast = ((D1Ind+1)==1), D1Ind_NextNextLast = ((D1Ind+2)==1);
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1, T0Ind_NextLast = 1;
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+800+((D1Ind)*32));
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<16; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==15), D0Ind_NextLast = ((D0Ind+1)==15), D0Ind_NextNextLast = ((D0Ind+2)==15);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (400); _LN_In = (200); _SN_In = (2*_LN_In); 
				} else if (!(D1Ind_Last)) {
					_N_In = _N_In + (-6000); _LN_In = (200); _SN_In = (2*_LN_In); 
				}
				_SNN_Filter = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_Filter = _NN_Filter + ((576)); _SNN_Filter = (((D1Ind_Last)?(576):(576))); 
					} else if (!((1))) {
						_NN_Filter = _NN_Filter + ((-8640)); _SNN_Filter = (((D1Ind_Last)?(576):(576))); 
					} else if (!(D1Ind_Last)) {
						_NN_Filter = _NN_Filter + (9216)+((-8640)); _SNN_Filter = (((1)?(576):(576))); 
					}
				} else if (!((1))) {
					_NN_Filter = _NN_Filter + ((576)); _SNN_Filter = (((D1Ind_Last)?(576):(576))); 
				} else if (!(D1Ind_Last)) {
					_NN_Filter = _NN_Filter + ((576)); _SNN_Filter = (((1)?(576):(576))); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+400*((D0Ind_Total+1)%2)),
							_SN_In, 200, _LN_In, 0, &DmaR_Evt1);
				}
				AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read Filter */
				if (_SNN_Filter) {
					AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Filter+_NN_Filter), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+6736+576*((D0Ind_Total)%2)),
							_SNN_Filter, 0, &UchanHR1);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
				if (_SN_Filter) {
					AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+6736+576*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+864+576*((D0Ind_Total+1)%2)),
							_SN_Filter, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+400*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (12-1*(1)-1*(1));
				KerArg1->UsedH = (unsigned short int) (12-1*(1)-1*(1));
				KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+864+576*((D0Ind_Total)%2));
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				_SN_Filter = _SNN_Filter;
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+2016+3200*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+2016+3200*((T0Ind_Total)%2)),
					_SC_Out, 200, _LC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(D1Ind_Last)) {
				_C_Out = _C_Out + (3200); _LC_Out = (200); _SC_Out = (16*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
			T0Ind_Total++;
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S45_MatAdd_32x10x10(
		short int * __restrict__ In1,
		short int * __restrict__ In2,
		short int * __restrict__ Out)

{
	/* Shared L1: 15360 bytes, L2 buffer: 15360 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaW_Evt1;
	KerMat3_fp_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int D0Ind, D0Ind_Last, D0Ind_NextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast;
	/* User kernel arguments related variables */
	unsigned int _N_In1;
	unsigned int _SN_In1;
	unsigned int _LN_In1;
	unsigned int _N_In2;
	unsigned int _SN_In2;
	unsigned int _LN_In2;
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	unsigned int _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D0 Dim: Init: 32, Tiled: 1][Tile0 Dim: 3]
	Ker Arg: In1, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 3 logical tiles, 3 physical tiles
			Total Size: 6400 [D0, [0 x 6400, 6400]][Tile0, 3:[10x4, 1:10x4, 10x2], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 6400, 6400]][Tile0, 3:[10x4, 1:10x4, 10x2], 2]
		Tile0: [0, 2560, 80], Tile1: [80, 2560, 80], Tile2; [160, 1280, 40]
	Ker Arg: In2, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 3 logical tiles, 3 physical tiles
			Total Size: 6400 [D0, [0 x 6400, 6400]][Tile0, 3:[10x4, 1:10x4, 10x2], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 6400, 6400]][Tile0, 3:[10x4, 1:10x4, 10x2], 2]
		Tile0: [0, 2560, 80], Tile1: [80, 2560, 80], Tile2; [160, 1280, 40]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 3 logical tiles, 3 physical tiles
			Total Size: 6400 [D0, [0 x 6400, 6400]][Tile0, 3:[10x4, 1:10x4, 10x2], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 6400, 6400]][Tile0, 3:[10x4, 1:10x4, 10x2], 2]
		Tile0: [0, 2560, 80], Tile1: [80, 2560, 80], Tile2; [160, 1280, 40]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->W = (unsigned short int) (10);
	KerArg0->N = (unsigned short int) (32);
	KerArg0->LB = (int) (-32768);
	KerArg0->UB = (int) (32767);
	KerArg0->In1_Q = (unsigned char) (12);
	KerArg0->In2_Q = (unsigned char) (11);
	KerArg0->Out_Q = (unsigned char) (11);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In1+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 2560, 200, 80, 0, &DmaR_Evt1);
	_N_In1=0;
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In2+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+5120+0), 2560, 200, 80, 0, &DmaR_Evt2);
	_N_In2=0;
	_C_Out=0; _SC_Out=2560; _LC_Out=80;
	_SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D0 */
		int D0Ind_Last = 1, D0Ind_NextLast = 1;
		for (T0Ind=0; T0Ind<3; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==2), T0Ind_NextLast = ((T0Ind+1)==2);
			/*================================= Prepare Tiles ===================================*/
			_SN_In1 = 0;
			if (!(T0Ind_Last)) {
				_N_In1 = _N_In1 + (80); _LN_In1 = ((T0Ind_NextLast)?40:80); _SN_In1 = (32*_LN_In1); 
			}
			_SN_In2 = 0;
			if (!(T0Ind_Last)) {
				_N_In2 = _N_In2 + (80); _LN_In2 = ((T0Ind_NextLast)?40:80); _SN_In2 = (32*_LN_In2); 
			}
			/*============================= End Prepare Tiles ===================================*/
			/*================================= Read Tiles ======================================*/
			AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In1 */
			if (_SN_In1) {
				AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In1+_N_In1), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+2560*((T0Ind_Total+1)%2)),
						_SN_In1, 200, _LN_In1, 0, &DmaR_Evt1);
			}
			AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In2 */
			if (_SN_In2) {
				AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In2+_N_In2), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+5120+2560*((T0Ind_Total+1)%2)),
						_SN_In2, 200, _LN_In2, 0, &DmaR_Evt2);
			}
			/*============================= End Read Tiles ======================================*/
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In1 = (short int *__restrict__) (resnet_L1_Memory+0+2560*((T0Ind_Total)%2));
			KerArg0->In2 = (short int *__restrict__) (resnet_L1_Memory+5120+2560*((T0Ind_Total)%2));
			KerArg0->Out = (short int *__restrict__) (resnet_L1_Memory+10240+2560*((T0Ind_Total)%2));
			KerArg0->H = (unsigned short int) (T0Ind_Last?2:4);
			AT_FORK(gap_ncore(), (void *) KerParMatAddDynAdjust_fp, (void *) KerArg0);
			__CALL(KerParMatAddDynAdjust_fp, KerArg0);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+10240+2560*((T0Ind_Total)%2)),
					_SC_Out, 200, _LC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (80); _LC_Out = ((T0Ind_NextLast)?40:80); _SC_Out = (32*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S48_Conv2d_32x32x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 14816 bytes, L2 buffer: 8416 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaW_Evt1;
	KerSetBias_fpd_fp_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConv_DP_fp_T S_KerArg1, *KerArg1 = &S_KerArg1;
	KerDP_fp_T S_KerArg2, *KerArg2 = &S_KerArg2;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Last, D1Ind_NextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast;
	/* User kernel arguments related variables */
	unsigned int _N_In;
	unsigned int _SN_In;
	unsigned int _LN_In;
	unsigned int _N_Filter;
	unsigned int _SN_Filter;
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	unsigned int _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 32, Tiled: 2][Tile0 Dim: 1][D0 Dim: Init: 32, Tiled: 16]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 16 logical tiles, 16 physical tiles
			Total Size: 6400 [D0, [15 x 400, 400]][Tile0, 1:[10x10], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[10x11, 14:10x12, 10x11], 2][D0, [15 x 400, 400]]
		Tile0: [0, 400, 200], Tile1: [400, 400, 200], Tile2; [800, 400, 200]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 64 [D1, [1 x 32, 32]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 32, 32]]
		Tile0: [0, 64, 64], Tile1: [0, 64, 64], Tile2; [0, 64, 64]
	Ker Arg: Filter, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 32 logical tiles, 32 physical tiles
			Total Size: 18432 [D1, [1 x 9216, 9216]][D0, [15 x 576, 576]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 9216, 9216]][D0, [15 x 576, 576]]
		Tile0: [0, 576, 576], Tile1: [576, 576, 576], Tile2; [1152, 576, 576]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 2 physical tiles
			Total Size: 6400 [D1, [1 x 3200, 3200]][Tile0, 1:[10x10], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 3200, 3200]][Tile0, 1:[10x10], 2]
		Tile0: [0, 3200, 200], Tile1: [3200, 3200, 200], Tile2; [0, 3200, 200]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 12800 [D1, [1 x 6400, 6400]][Tile0, 1:[10x10], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 6400, 6400]][Tile0, 1:[10x10], 4]
		Tile0: [0, 6400, 400], Tile1: [0, 6400, 400], Tile2; [0, 6400, 400]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+8416);
	KerArg0->W = (unsigned short int) (10);
	KerArg0->H = (unsigned short int) (10);
	KerArg0->OutFeatures = (unsigned short int) (16);
	KerArg0->NormBias = (signed char) (12);
	KerArg1->W = (unsigned short int) (10);
	KerArg1->UsedW = (unsigned short int) (10);
	KerArg1->InFeatures = (unsigned short int) (2);
	KerArg1->OutFeatures = (unsigned short int) (16);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+8416);
	KerArg1->Norm = (unsigned char) (13);
	KerArg1->TotalInFeatures = (short int) (2);
	KerArg1->Pad = (v4s) ((v4s){1,1,1,1});
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+8416);
	KerArg2->W = (unsigned short int) (10);
	KerArg2->H = (unsigned short int) (10);
	KerArg2->Norm = (unsigned char) (13);
	KerArg2->InFeatures = (unsigned short int) (16);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 400, 200, 200, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+800), 64, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+864+0), 576, 0, &DmaR_Evt3);
	_N_Filter=0;
	_C_Out=0; _SC_Out=3200; _LC_Out=200;
	_SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	for (D1Ind=0; D1Ind<2; D1Ind++) { /* Iteration on D1 */
		int D1Ind_Last = (D1Ind==1), D1Ind_NextLast = ((D1Ind+1)==1);
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1, T0Ind_NextLast = 1;
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+800+((D1Ind)*32));
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<16; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==15), D0Ind_NextLast = ((D0Ind+1)==15);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (400); _LN_In = (200); _SN_In = (2*_LN_In); 
				} else if (!(D1Ind_Last)) {
					_N_In = _N_In + (-6000); _LN_In = (200); _SN_In = (2*_LN_In); 
				}
				_SN_Filter = 0;
				if (!(D0Ind_Last)) {
					_N_Filter = _N_Filter + ((576)); _SN_Filter = (((D1Ind_Last)?(576):(576))); 
				} else if (!((1))) {
					_N_Filter = _N_Filter + ((-8640)); _SN_Filter = (((D1Ind_Last)?(576):(576))); 
				} else if (!(D1Ind_Last)) {
					_N_Filter = _N_Filter + (9216)+((-8640)); _SN_Filter = (((1)?(576):(576))); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+400*((D0Ind_Total+1)%2)),
							_SN_In, 200, _LN_In, 0, &DmaR_Evt1);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
				if (_SN_Filter) {
					AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+_N_Filter), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+864+576*((D0Ind_Total+1)%2)),
							_SN_Filter, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+400*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (12-1*(1)-1*(1));
				KerArg1->UsedH = (unsigned short int) (12-1*(1)-1*(1));
				KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+864+576*((D0Ind_Total)%2));
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+2016+3200*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+2016+3200*((T0Ind_Total)%2)),
					_SC_Out, 200, _LC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(D1Ind_Last)) {
				_C_Out = _C_Out + (3200); _LC_Out = (200); _SC_Out = (16*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
			T0Ind_Total++;
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S51_Conv2d_32x32x3x3(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 14816 bytes, L2 buffer: 8416 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaW_Evt1;
	KerSetBias_fpd_fp_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConv_DP_fp_T S_KerArg1, *KerArg1 = &S_KerArg1;
	KerDP_fp_T S_KerArg2, *KerArg2 = &S_KerArg2;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Last, D1Ind_NextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast;
	/* User kernel arguments related variables */
	unsigned int _N_In;
	unsigned int _SN_In;
	unsigned int _LN_In;
	unsigned int _N_Filter;
	unsigned int _SN_Filter;
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	unsigned int _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 32, Tiled: 2][Tile0 Dim: 1][D0 Dim: Init: 32, Tiled: 16]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 16 logical tiles, 16 physical tiles
			Total Size: 6400 [D0, [15 x 400, 400]][Tile0, 1:[10x10], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[10x11, 14:10x12, 10x11], 2][D0, [15 x 400, 400]]
		Tile0: [0, 400, 200], Tile1: [400, 400, 200], Tile2; [800, 400, 200]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 64 [D1, [1 x 32, 32]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 32, 32]]
		Tile0: [0, 64, 64], Tile1: [0, 64, 64], Tile2; [0, 64, 64]
	Ker Arg: Filter, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 32 logical tiles, 32 physical tiles
			Total Size: 18432 [D1, [1 x 9216, 9216]][D0, [15 x 576, 576]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 9216, 9216]][D0, [15 x 576, 576]]
		Tile0: [0, 576, 576], Tile1: [576, 576, 576], Tile2; [1152, 576, 576]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 2 physical tiles
			Total Size: 6400 [D1, [1 x 3200, 3200]][Tile0, 1:[10x10], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 3200, 3200]][Tile0, 1:[10x10], 2]
		Tile0: [0, 3200, 200], Tile1: [3200, 3200, 200], Tile2; [0, 3200, 200]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 12800 [D1, [1 x 6400, 6400]][Tile0, 1:[10x10], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 6400, 6400]][Tile0, 1:[10x10], 4]
		Tile0: [0, 6400, 400], Tile1: [0, 6400, 400], Tile2; [0, 6400, 400]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+8416);
	KerArg0->W = (unsigned short int) (10);
	KerArg0->H = (unsigned short int) (10);
	KerArg0->OutFeatures = (unsigned short int) (16);
	KerArg0->NormBias = (signed char) (14);
	KerArg1->W = (unsigned short int) (10);
	KerArg1->UsedW = (unsigned short int) (10);
	KerArg1->InFeatures = (unsigned short int) (2);
	KerArg1->OutFeatures = (unsigned short int) (16);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+8416);
	KerArg1->Norm = (unsigned char) (16);
	KerArg1->TotalInFeatures = (short int) (2);
	KerArg1->Pad = (v4s) ((v4s){1,1,1,1});
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+8416);
	KerArg2->W = (unsigned short int) (10);
	KerArg2->H = (unsigned short int) (10);
	KerArg2->Norm = (unsigned char) (16);
	KerArg2->InFeatures = (unsigned short int) (16);
	KerArg2->LB = (int) (-32768);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 400, 200, 200, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+800), 64, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+864+0), 576, 0, &DmaR_Evt3);
	_N_Filter=0;
	_C_Out=0; _SC_Out=3200; _LC_Out=200;
	_SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	for (D1Ind=0; D1Ind<2; D1Ind++) { /* Iteration on D1 */
		int D1Ind_Last = (D1Ind==1), D1Ind_NextLast = ((D1Ind+1)==1);
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1, T0Ind_NextLast = 1;
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+800+((D1Ind)*32));
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<16; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==15), D0Ind_NextLast = ((D0Ind+1)==15);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (400); _LN_In = (200); _SN_In = (2*_LN_In); 
				} else if (!(D1Ind_Last)) {
					_N_In = _N_In + (-6000); _LN_In = (200); _SN_In = (2*_LN_In); 
				}
				_SN_Filter = 0;
				if (!(D0Ind_Last)) {
					_N_Filter = _N_Filter + ((576)); _SN_Filter = (((D1Ind_Last)?(576):(576))); 
				} else if (!((1))) {
					_N_Filter = _N_Filter + ((-8640)); _SN_Filter = (((D1Ind_Last)?(576):(576))); 
				} else if (!(D1Ind_Last)) {
					_N_Filter = _N_Filter + (9216)+((-8640)); _SN_Filter = (((1)?(576):(576))); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+400*((D0Ind_Total+1)%2)),
							_SN_In, 200, _LN_In, 0, &DmaR_Evt1);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
				if (_SN_Filter) {
					AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+_N_Filter), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+864+576*((D0Ind_Total+1)%2)),
							_SN_Filter, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+400*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (12-1*(1)-1*(1));
				KerArg1->UsedH = (unsigned short int) (12-1*(1)-1*(1));
				KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+864+576*((D0Ind_Total)%2));
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+2016+3200*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+2016+3200*((T0Ind_Total)%2)),
					_SC_Out, 200, _LC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(D1Ind_Last)) {
				_C_Out = _C_Out + (3200); _LC_Out = (200); _SC_Out = (16*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
			T0Ind_Total++;
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S52_MatAdd_32x10x10(
		short int * __restrict__ In1,
		short int * __restrict__ In2,
		short int * __restrict__ Out)

{
	/* Shared L1: 15360 bytes, L2 buffer: 15360 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaW_Evt1;
	KerMat3_fp_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int D0Ind, D0Ind_Last, D0Ind_NextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast;
	/* User kernel arguments related variables */
	unsigned int _N_In1;
	unsigned int _SN_In1;
	unsigned int _LN_In1;
	unsigned int _N_In2;
	unsigned int _SN_In2;
	unsigned int _LN_In2;
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	unsigned int _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D0 Dim: Init: 32, Tiled: 1][Tile0 Dim: 3]
	Ker Arg: In1, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 3 logical tiles, 3 physical tiles
			Total Size: 6400 [D0, [0 x 6400, 6400]][Tile0, 3:[10x4, 1:10x4, 10x2], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 6400, 6400]][Tile0, 3:[10x4, 1:10x4, 10x2], 2]
		Tile0: [0, 2560, 80], Tile1: [80, 2560, 80], Tile2; [160, 1280, 40]
	Ker Arg: In2, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 3 logical tiles, 3 physical tiles
			Total Size: 6400 [D0, [0 x 6400, 6400]][Tile0, 3:[10x4, 1:10x4, 10x2], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 6400, 6400]][Tile0, 3:[10x4, 1:10x4, 10x2], 2]
		Tile0: [0, 2560, 80], Tile1: [80, 2560, 80], Tile2; [160, 1280, 40]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 3 logical tiles, 3 physical tiles
			Total Size: 6400 [D0, [0 x 6400, 6400]][Tile0, 3:[10x4, 1:10x4, 10x2], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 6400, 6400]][Tile0, 3:[10x4, 1:10x4, 10x2], 2]
		Tile0: [0, 2560, 80], Tile1: [80, 2560, 80], Tile2; [160, 1280, 40]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->W = (unsigned short int) (10);
	KerArg0->N = (unsigned short int) (32);
	KerArg0->LB = (int) (-32768);
	KerArg0->UB = (int) (32767);
	KerArg0->In1_Q = (unsigned char) (12);
	KerArg0->In2_Q = (unsigned char) (11);
	KerArg0->Out_Q = (unsigned char) (11);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In1+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 2560, 200, 80, 0, &DmaR_Evt1);
	_N_In1=0;
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In2+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+5120+0), 2560, 200, 80, 0, &DmaR_Evt2);
	_N_In2=0;
	_C_Out=0; _SC_Out=2560; _LC_Out=80;
	_SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D0 */
		int D0Ind_Last = 1, D0Ind_NextLast = 1;
		for (T0Ind=0; T0Ind<3; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==2), T0Ind_NextLast = ((T0Ind+1)==2);
			/*================================= Prepare Tiles ===================================*/
			_SN_In1 = 0;
			if (!(T0Ind_Last)) {
				_N_In1 = _N_In1 + (80); _LN_In1 = ((T0Ind_NextLast)?40:80); _SN_In1 = (32*_LN_In1); 
			}
			_SN_In2 = 0;
			if (!(T0Ind_Last)) {
				_N_In2 = _N_In2 + (80); _LN_In2 = ((T0Ind_NextLast)?40:80); _SN_In2 = (32*_LN_In2); 
			}
			/*============================= End Prepare Tiles ===================================*/
			/*================================= Read Tiles ======================================*/
			AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In1 */
			if (_SN_In1) {
				AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In1+_N_In1), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+2560*((T0Ind_Total+1)%2)),
						_SN_In1, 200, _LN_In1, 0, &DmaR_Evt1);
			}
			AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In2 */
			if (_SN_In2) {
				AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In2+_N_In2), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+5120+2560*((T0Ind_Total+1)%2)),
						_SN_In2, 200, _LN_In2, 0, &DmaR_Evt2);
			}
			/*============================= End Read Tiles ======================================*/
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In1 = (short int *__restrict__) (resnet_L1_Memory+0+2560*((T0Ind_Total)%2));
			KerArg0->In2 = (short int *__restrict__) (resnet_L1_Memory+5120+2560*((T0Ind_Total)%2));
			KerArg0->Out = (short int *__restrict__) (resnet_L1_Memory+10240+2560*((T0Ind_Total)%2));
			KerArg0->H = (unsigned short int) (T0Ind_Last?2:4);
			AT_FORK(gap_ncore(), (void *) KerParMatAddDynAdjust_fp, (void *) KerArg0);
			__CALL(KerParMatAddDynAdjust_fp, KerArg0);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+10240+2560*((T0Ind_Total)%2)),
					_SC_Out, 200, _LC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (80); _LC_Out = ((T0Ind_NextLast)?40:80); _SC_Out = (32*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S55_Conv2d_64x32x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 16160 bytes, L2 buffer: 10560 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaW_Evt1;
	KerSetBias_fpd_fp_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConv_DP_fp_T S_KerArg1, *KerArg1 = &S_KerArg1;
	KerDP_fp_T S_KerArg2, *KerArg2 = &S_KerArg2;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Last, D1Ind_NextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast;
	/* User kernel arguments related variables */
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	unsigned int _LP_Out, _LC_Out;
	unsigned int _N_Filter;
	unsigned int _SN_Filter;
	unsigned int _N_In;
	unsigned int _SN_In;
	unsigned int _LN_In;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 64, Tiled: 2][Tile0 Dim: 1][D0 Dim: Init: 32, Tiled: 16]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 2 physical tiles
			Total Size: 3200 [D1, [1 x 2800, 400]][Tile0, 1:[5x5], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 2800, 400]][Tile0, 1:[5x5], 2]
		Tile0: [0, 2800, 50], Tile1: [2800, 400, 50], Tile2; [0, 2800, 50]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 128 [D1, [1 x 112, 16]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 112, 16]]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Filter, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 32 logical tiles, 32 physical tiles
			Total Size: 36864 [D1, [1 x 32256, 4608]][D0, [15 x 2016, 2016]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 32256, 4608]][D0, [15 x 2016, 2016]]
		Tile0: [0, 2016, 2016], Tile1: [2016, 2016, 2016], Tile2; [4032, 2016, 2016]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 16 logical tiles, 16 physical tiles
			Total Size: 6400 [D0, [15 x 400, 400]][Tile0, 1:[10x10], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[10x11, 14:10x11, 10x10], 2][D0, [15 x 400, 400]]
		Tile0: [0, 400, 200], Tile1: [400, 400, 200], Tile2; [800, 400, 200]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 6400 [D1, [1 x 5600, 800]][Tile0, 1:[5x5], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 5600, 800]][Tile0, 1:[5x5], 4]
		Tile0: [0, 5600, 100], Tile1: [0, 5600, 100], Tile2; [0, 5600, 100]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+10560);
	KerArg0->W = (unsigned short int) (5);
	KerArg0->H = (unsigned short int) (5);
	KerArg0->NormBias = (signed char) (12);
	KerArg1->W = (unsigned short int) (10);
	KerArg1->UsedW = (unsigned short int) (10);
	KerArg1->InFeatures = (unsigned short int) (2);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+10560);
	KerArg1->Norm = (unsigned char) (13);
	KerArg1->TotalInFeatures = (short int) (2);
	KerArg1->Pad = (v4s) ((v4s){0,1,0,1});
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+10560);
	KerArg2->W = (unsigned short int) (5);
	KerArg2->H = (unsigned short int) (5);
	KerArg2->Norm = (unsigned char) (13);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	_C_Out=0; _SC_Out=2800; _LC_Out=50;
	_SP_Out=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+800), 128, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+928+0), 2016, 0, &DmaR_Evt2);
	_N_Filter=0;
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 400, 200, 200, 0, &DmaR_Evt3);
	_N_In=0;
	/*============================= End Read Tiles Prolog ===============================*/
	for (D1Ind=0; D1Ind<2; D1Ind++) { /* Iteration on D1 */
		int D1Ind_Last = (D1Ind==1), D1Ind_NextLast = ((D1Ind+1)==1);
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1, T0Ind_NextLast = 1;
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->OutFeatures = (unsigned short int) (D1Ind_Last?8:56);
			KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+800+((D1Ind)*112));
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<16; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==15), D0Ind_NextLast = ((D0Ind+1)==15);
				/*================================= Prepare Tiles ===================================*/
				_SN_Filter = 0;
				if (!(D0Ind_Last)) {
					_N_Filter = _N_Filter + (((D1Ind_Last)?(288):(2016))); _SN_Filter = (((D1Ind_Last)?(288):(2016))); 
				} else if (!((1))) {
					_N_Filter = _N_Filter + (((D1Ind_Last)?(-4320):(-30240))); _SN_Filter = (((D1Ind_Last)?(288):(2016))); 
				} else if (!(D1Ind_Last)) {
					_N_Filter = _N_Filter + (32256)+(((D1Ind_Last)?(-4320):(-30240))); _SN_Filter = (((1)?(288):(2016))); 
				}
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (400); _LN_In = (200); _SN_In = (2*_LN_In); 
				} else if (!(D1Ind_Last)) {
					_N_In = _N_In + (-6000); _LN_In = (200); _SN_In = (2*_LN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Filter */
				if (_SN_Filter) {
					AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+_N_Filter), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+928+2016*((D0Ind_Total+1)%2)),
							_SN_Filter, 0, &DmaR_Evt2);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+400*((D0Ind_Total+1)%2)),
							_SN_In, 200, _LN_In, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+400*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (11-0*(1)-1*(1));
				KerArg1->UsedH = (unsigned short int) (11-0*(1)-1*(1));
				KerArg1->OutFeatures = (unsigned short int) (D1Ind_Last?8:56);
				KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+928+2016*((D0Ind_Total)%2));
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride2_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride2_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+4960+2800*((T0Ind_Total)%2));
			KerArg2->InFeatures = (unsigned short int) (D1Ind_Last?8:56);
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+4960+2800*((T0Ind_Total)%2)),
					_SC_Out, 50, _LC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(D1Ind_Last)) {
				_C_Out = _C_Out + (2800); _LC_Out = (50); _SC_Out = (((1)?8:56)*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
			T0Ind_Total++;
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S58_Conv2d_64x32x1x1(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 13184 bytes, L2 buffer: 10624 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaW_Evt1;
	KerSetBias_fpd_fp_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConv_DP_fp_T S_KerArg1, *KerArg1 = &S_KerArg1;
	KerDP_fp_T S_KerArg2, *KerArg2 = &S_KerArg2;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Last;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast;
	/* User kernel arguments related variables */
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	unsigned int _LP_Out, _LC_Out;
	unsigned int _N_In;
	unsigned int _SN_In;
	unsigned int _LN_In;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 64, Tiled: 1][Tile0 Dim: 3][D0 Dim: Init: 32, Tiled: 1]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 3 logical tiles, 3 physical tiles
			Total Size: 3200 [D1, [0 x 3200, 3200]][Tile0, 3:[5x2, 1:5x2, 5x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 3200, 3200]][Tile0, 3:[5x2, 1:5x2, 5x1], 2]
		Tile0: [0, 1280, 20], Tile1: [20, 1280, 20], Tile2; [40, 640, 10]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 128 [D1, [0 x 128, 128]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 128, 128]]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 4096 [D1, [0 x 4096, 4096]][D0, [0 x 4096, 4096]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 4096, 4096]][D0, [0 x 4096, 4096]]
		Tile0: [0, 4096, 4096], Tile1: [0, 4096, 4096], Tile2; [0, 4096, 4096]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 3 logical tiles, 3 physical tiles
			Total Size: 6400 [D0, [0 x 6400, 6400]][Tile0, 3:[10x3, 1:10x3, 10x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 3:[10x3], 2][D0, [0 x 6400, 6400]]
		Tile0: [0, 1920, 60], Tile1: [80, 1920, 60], Tile2; [160, 640, 20]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 3 logical tiles, 1 physical tiles
			Total Size: 6400 [D1, [0 x 6400, 6400]][Tile0, 3:[5x2, 1:5x2, 5x1], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 6400, 6400]][Tile0, 3:[5x2, 1:5x2, 5x1], 4]
		Tile0: [0, 2560, 40], Tile1: [0, 2560, 40], Tile2; [0, 2560, 40]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+10624);
	KerArg0->W = (unsigned short int) (5);
	KerArg0->OutFeatures = (unsigned short int) (64);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+3840);
	KerArg0->NormBias = (signed char) (11);
	KerArg1->W = (unsigned short int) (10);
	KerArg1->UsedW = (unsigned short int) (9);
	KerArg1->InFeatures = (unsigned short int) (32);
	KerArg1->OutFeatures = (unsigned short int) (64);
	KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+3968);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+10624);
	KerArg1->Norm = (unsigned char) (13);
	KerArg1->TotalInFeatures = (short int) (32);
	KerArg1->Pad = (v4s) 0;
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+10624);
	KerArg2->W = (unsigned short int) (5);
	KerArg2->Norm = (unsigned char) (13);
	KerArg2->InFeatures = (unsigned short int) (64);
	KerArg2->LB = (int) (-32768);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	_C_Out=0; _SC_Out=1280; _LC_Out=20;
	_SP_Out=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+3840), 128, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+3968), 4096, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Filter */
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 1920, 200, 60, 0, &DmaR_Evt3);
	_N_In=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<3; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==2), T0Ind_NextLast = ((T0Ind+1)==2);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->H = (unsigned short int) (T0Ind_Last?1:2);
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			{ /* Single iteration on D0 */
				int D0Ind_Last = 1, D0Ind_NextLast = 1;
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(T0Ind_Last)) {
					_N_In = _N_In + (80); _LN_In = ((T0Ind_NextLast)?20:60); _SN_In = (32*_LN_In); 
				} else if (!(1)) {
					_N_In = _N_In + (-160); _LN_In = (60); _SN_In = (32*_LN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+1920*((D0Ind_Total+1)%2)),
							_SN_In, 200, _LN_In, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+1920*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (T0Ind_Last?1:3);
				KerArg1->UsedH = (unsigned short int) (T0Ind_Last?1:3);
				AT_FORK(gap_ncore(), (void *) KerParConv1x1Stride2_DP_fp, (void *) KerArg1);
				__CALL(KerParConv1x1Stride2_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				/*============================= End Update Arg Pipeline =============================*/
				D0Ind_Total++;
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->H = (unsigned short int) (T0Ind_Last?1:2);
			KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+8064+1280*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+8064+1280*((T0Ind_Total)%2)),
					_SC_Out, 50, _LC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (20); _LC_Out = ((T0Ind_NextLast)?10:20); _SC_Out = (64*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S61_Conv2d_64x64x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 15560 bytes, L2 buffer: 9960 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	KerSetBias_fpd_fp_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConv_DP_fp_T S_KerArg1, *KerArg1 = &S_KerArg1;
	KerDP_fp_T S_KerArg2, *KerArg2 = &S_KerArg2;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Last, D1Ind_NextLast, D1Ind_NextNextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast, D0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _N_In;
	unsigned int _SN_In;
	unsigned int _LN_In;
	unsigned int _NN_Filter;
	unsigned int _SN_Filter, _SNN_Filter;
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	unsigned int _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 64, Tiled: 2][Tile0 Dim: 1][D0 Dim: Init: 64, Tiled: 32]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 32 logical tiles, 32 physical tiles
			Total Size: 3200 [D0, [31 x 100, 100]][Tile0, 1:[5x5], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[5x6, 30:5x7, 5x6], 2][D0, [31 x 100, 100]]
		Tile0: [0, 100, 50], Tile1: [100, 100, 50], Tile2; [200, 100, 50]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 128 [D1, [1 x 112, 16]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 112, 16]]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Filter, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 64 logical tiles, 64 physical tiles
			Total Size: 73728 [D1, [1 x 64512, 9216]][D0, [31 x 2016, 2016]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 64512, 9216]][D0, [31 x 2016, 2016]]
		Tile0: [0, 2016, 2016], Tile1: [2016, 2016, 2016], Tile2; [4032, 2016, 2016]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 2 physical tiles
			Total Size: 3200 [D1, [1 x 2800, 400]][Tile0, 1:[5x5], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 2800, 400]][Tile0, 1:[5x5], 2]
		Tile0: [0, 2800, 50], Tile1: [2800, 400, 50], Tile2; [0, 2800, 50]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 6400 [D1, [1 x 5600, 800]][Tile0, 1:[5x5], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 5600, 800]][Tile0, 1:[5x5], 4]
		Tile0: [0, 5600, 100], Tile1: [0, 5600, 100], Tile2; [0, 5600, 100]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+9960);
	KerArg0->W = (unsigned short int) (5);
	KerArg0->H = (unsigned short int) (5);
	KerArg0->NormBias = (signed char) (14);
	KerArg1->W = (unsigned short int) (5);
	KerArg1->UsedW = (unsigned short int) (5);
	KerArg1->InFeatures = (unsigned short int) (2);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+9960);
	KerArg1->Norm = (unsigned char) (15);
	KerArg1->TotalInFeatures = (short int) (2);
	KerArg1->Pad = (v4s) ((v4s){1,1,1,1});
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+9960);
	KerArg2->W = (unsigned short int) (5);
	KerArg2->H = (unsigned short int) (5);
	KerArg2->Norm = (unsigned char) (15);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 100, 50, 50, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+200), 128, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Filter+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+16336+0), 2016, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read Filter */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Filter+2016), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+16336+2016), 2016, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+16336+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+328+0), 2016, 0, &DmaR_Evt3);
	_NN_Filter=2016; _SN_Filter=2016;
	_C_Out=0; _SC_Out=2800; _LC_Out=50;
	_SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	for (D1Ind=0; D1Ind<2; D1Ind++) { /* Iteration on D1 */
		int D1Ind_Last = (D1Ind==1), D1Ind_NextLast = ((D1Ind+1)==1), D1Ind_NextNextLast = ((D1Ind+2)==1);
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1, T0Ind_NextLast = 1;
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->OutFeatures = (unsigned short int) (D1Ind_Last?8:56);
			KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+200+((D1Ind)*112));
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<32; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==31), D0Ind_NextLast = ((D0Ind+1)==31), D0Ind_NextNextLast = ((D0Ind+2)==31);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (100); _LN_In = (50); _SN_In = (2*_LN_In); 
				} else if (!(D1Ind_Last)) {
					_N_In = _N_In + (-3100); _LN_In = (50); _SN_In = (2*_LN_In); 
				}
				_SNN_Filter = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_Filter = _NN_Filter + (((D1Ind_Last)?(288):(2016))); _SNN_Filter = (((D1Ind_Last)?(288):(2016))); 
					} else if (!((1))) {
						_NN_Filter = _NN_Filter + (((D1Ind_Last)?(-8928):(-62496))); _SNN_Filter = (((D1Ind_Last)?(288):(2016))); 
					} else if (!(D1Ind_Last)) {
						_NN_Filter = _NN_Filter + (64512)+(((D1Ind_Last)?(-8928):(-62496))); _SNN_Filter = (((1)?(288):(2016))); 
					}
				} else if (!((1))) {
					_NN_Filter = _NN_Filter + (((D1Ind_Last)?(288):(2016))); _SNN_Filter = (((D1Ind_Last)?(288):(2016))); 
				} else if (!(D1Ind_Last)) {
					_NN_Filter = _NN_Filter + (((1)?(288):(2016))); _SNN_Filter = (((1)?(288):(2016))); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+100*((D0Ind_Total+1)%2)),
							_SN_In, 50, _LN_In, 0, &DmaR_Evt1);
				}
				AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read Filter */
				if (_SNN_Filter) {
					AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Filter+_NN_Filter), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+16336+2016*((D0Ind_Total)%2)),
							_SNN_Filter, 0, &UchanHR1);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
				if (_SN_Filter) {
					AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+16336+2016*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+328+2016*((D0Ind_Total+1)%2)),
							_SN_Filter, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+100*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (7-1*(1)-1*(1));
				KerArg1->UsedH = (unsigned short int) (7-1*(1)-1*(1));
				KerArg1->OutFeatures = (unsigned short int) (D1Ind_Last?8:56);
				KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+328+2016*((D0Ind_Total)%2));
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				_SN_Filter = _SNN_Filter;
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+4360+2800*((T0Ind_Total)%2));
			KerArg2->InFeatures = (unsigned short int) (D1Ind_Last?8:56);
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+4360+2800*((T0Ind_Total)%2)),
					_SC_Out, 50, _LC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(D1Ind_Last)) {
				_C_Out = _C_Out + (2800); _LC_Out = (50); _SC_Out = (((1)?8:56)*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
			T0Ind_Total++;
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S62_MatAdd_64x5x5(
		short int * __restrict__ In1,
		short int * __restrict__ In2,
		short int * __restrict__ Out)

{
	/* Shared L1: 9600 bytes, L2 buffer: 9600 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaW_Evt1;
	KerMat3_fp_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int D0Ind, D0Ind_Last;
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D0 Dim: Init: 64, Tiled: 1][Tile0 Dim: 1]
	Ker Arg: In1, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 3200 [D0, [0 x 3200, 3200]][Tile0, 1:[5x5], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 3200, 3200]][Tile0, 1:[5x5], 2]
		Tile0: [0, 3200, 3200], Tile1: [0, 3200, 3200], Tile2; [0, 3200, 3200]
	Ker Arg: In2, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 3200 [D0, [0 x 3200, 3200]][Tile0, 1:[5x5], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 3200, 3200]][Tile0, 1:[5x5], 2]
		Tile0: [0, 3200, 3200], Tile1: [0, 3200, 3200], Tile2; [0, 3200, 3200]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 3200 [D0, [0 x 3200, 3200]][Tile0, 1:[5x5], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 3200, 3200]][Tile0, 1:[5x5], 2]
		Tile0: [0, 3200, 3200], Tile1: [0, 3200, 3200], Tile2; [0, 3200, 3200]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In1 = (short int *__restrict__) (resnet_L1_Memory+0);
	KerArg0->In2 = (short int *__restrict__) (resnet_L1_Memory+3200);
	KerArg0->Out = (short int *__restrict__) (resnet_L1_Memory+6400);
	KerArg0->W = (unsigned short int) (5);
	KerArg0->H = (unsigned short int) (5);
	KerArg0->N = (unsigned short int) (64);
	KerArg0->LB = (int) (-32768);
	KerArg0->UB = (int) (32767);
	KerArg0->In1_Q = (unsigned char) (12);
	KerArg0->In2_Q = (unsigned char) (13);
	KerArg0->Out_Q = (unsigned char) (12);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In1+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0), 3200, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In1 */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In2+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+3200), 3200, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In2 */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D0 */
		int D0Ind_Last = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			/*====================== Call Kernel LOC_LOOP =========================*/
			AT_FORK(gap_ncore(), (void *) KerParMatAddDynAdjust_fp, (void *) KerArg0);
			__CALL(KerParMatAddDynAdjust_fp, KerArg0);
		} /* End iteration on Tile0 */
	} /* End iteration on D0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+6400), 3200, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S65_Conv2d_64x64x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 15560 bytes, L2 buffer: 9960 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	KerSetBias_fpd_fp_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConv_DP_fp_T S_KerArg1, *KerArg1 = &S_KerArg1;
	KerDP_fp_T S_KerArg2, *KerArg2 = &S_KerArg2;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Last, D1Ind_NextLast, D1Ind_NextNextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast, D0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _N_In;
	unsigned int _SN_In;
	unsigned int _LN_In;
	unsigned int _NN_Filter;
	unsigned int _SN_Filter, _SNN_Filter;
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	unsigned int _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 64, Tiled: 2][Tile0 Dim: 1][D0 Dim: Init: 64, Tiled: 32]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 32 logical tiles, 32 physical tiles
			Total Size: 3200 [D0, [31 x 100, 100]][Tile0, 1:[5x5], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[5x6, 30:5x7, 5x6], 2][D0, [31 x 100, 100]]
		Tile0: [0, 100, 50], Tile1: [100, 100, 50], Tile2; [200, 100, 50]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 128 [D1, [1 x 112, 16]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 112, 16]]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Filter, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 64 logical tiles, 64 physical tiles
			Total Size: 73728 [D1, [1 x 64512, 9216]][D0, [31 x 2016, 2016]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 64512, 9216]][D0, [31 x 2016, 2016]]
		Tile0: [0, 2016, 2016], Tile1: [2016, 2016, 2016], Tile2; [4032, 2016, 2016]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 2 physical tiles
			Total Size: 3200 [D1, [1 x 2800, 400]][Tile0, 1:[5x5], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 2800, 400]][Tile0, 1:[5x5], 2]
		Tile0: [0, 2800, 50], Tile1: [2800, 400, 50], Tile2; [0, 2800, 50]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 6400 [D1, [1 x 5600, 800]][Tile0, 1:[5x5], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 5600, 800]][Tile0, 1:[5x5], 4]
		Tile0: [0, 5600, 100], Tile1: [0, 5600, 100], Tile2; [0, 5600, 100]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+9960);
	KerArg0->W = (unsigned short int) (5);
	KerArg0->H = (unsigned short int) (5);
	KerArg0->NormBias = (signed char) (13);
	KerArg1->W = (unsigned short int) (5);
	KerArg1->UsedW = (unsigned short int) (5);
	KerArg1->InFeatures = (unsigned short int) (2);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+9960);
	KerArg1->Norm = (unsigned char) (14);
	KerArg1->TotalInFeatures = (short int) (2);
	KerArg1->Pad = (v4s) ((v4s){1,1,1,1});
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+9960);
	KerArg2->W = (unsigned short int) (5);
	KerArg2->H = (unsigned short int) (5);
	KerArg2->Norm = (unsigned char) (14);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 100, 50, 50, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+200), 128, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Filter+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+6736+0), 2016, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read Filter */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Filter+2016), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+6736+2016), 2016, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+6736+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+328+0), 2016, 0, &DmaR_Evt3);
	_NN_Filter=2016; _SN_Filter=2016;
	_C_Out=0; _SC_Out=2800; _LC_Out=50;
	_SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	for (D1Ind=0; D1Ind<2; D1Ind++) { /* Iteration on D1 */
		int D1Ind_Last = (D1Ind==1), D1Ind_NextLast = ((D1Ind+1)==1), D1Ind_NextNextLast = ((D1Ind+2)==1);
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1, T0Ind_NextLast = 1;
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->OutFeatures = (unsigned short int) (D1Ind_Last?8:56);
			KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+200+((D1Ind)*112));
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<32; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==31), D0Ind_NextLast = ((D0Ind+1)==31), D0Ind_NextNextLast = ((D0Ind+2)==31);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (100); _LN_In = (50); _SN_In = (2*_LN_In); 
				} else if (!(D1Ind_Last)) {
					_N_In = _N_In + (-3100); _LN_In = (50); _SN_In = (2*_LN_In); 
				}
				_SNN_Filter = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_Filter = _NN_Filter + (((D1Ind_Last)?(288):(2016))); _SNN_Filter = (((D1Ind_Last)?(288):(2016))); 
					} else if (!((1))) {
						_NN_Filter = _NN_Filter + (((D1Ind_Last)?(-8928):(-62496))); _SNN_Filter = (((D1Ind_Last)?(288):(2016))); 
					} else if (!(D1Ind_Last)) {
						_NN_Filter = _NN_Filter + (64512)+(((D1Ind_Last)?(-8928):(-62496))); _SNN_Filter = (((1)?(288):(2016))); 
					}
				} else if (!((1))) {
					_NN_Filter = _NN_Filter + (((D1Ind_Last)?(288):(2016))); _SNN_Filter = (((D1Ind_Last)?(288):(2016))); 
				} else if (!(D1Ind_Last)) {
					_NN_Filter = _NN_Filter + (((1)?(288):(2016))); _SNN_Filter = (((1)?(288):(2016))); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+100*((D0Ind_Total+1)%2)),
							_SN_In, 50, _LN_In, 0, &DmaR_Evt1);
				}
				AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read Filter */
				if (_SNN_Filter) {
					AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Filter+_NN_Filter), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+6736+2016*((D0Ind_Total)%2)),
							_SNN_Filter, 0, &UchanHR1);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
				if (_SN_Filter) {
					AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+6736+2016*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+328+2016*((D0Ind_Total+1)%2)),
							_SN_Filter, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+100*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (7-1*(1)-1*(1));
				KerArg1->UsedH = (unsigned short int) (7-1*(1)-1*(1));
				KerArg1->OutFeatures = (unsigned short int) (D1Ind_Last?8:56);
				KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+328+2016*((D0Ind_Total)%2));
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				_SN_Filter = _SNN_Filter;
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+4360+2800*((T0Ind_Total)%2));
			KerArg2->InFeatures = (unsigned short int) (D1Ind_Last?8:56);
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+4360+2800*((T0Ind_Total)%2)),
					_SC_Out, 50, _LC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(D1Ind_Last)) {
				_C_Out = _C_Out + (2800); _LC_Out = (50); _SC_Out = (((1)?8:56)*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
			T0Ind_Total++;
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S68_Conv2d_64x64x3x3(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 15560 bytes, L2 buffer: 9960 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	KerSetBias_fpd_fp_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConv_DP_fp_T S_KerArg1, *KerArg1 = &S_KerArg1;
	KerDP_fp_T S_KerArg2, *KerArg2 = &S_KerArg2;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Last, D1Ind_NextLast, D1Ind_NextNextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast, D0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _N_In;
	unsigned int _SN_In;
	unsigned int _LN_In;
	unsigned int _NN_Filter;
	unsigned int _SN_Filter, _SNN_Filter;
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	unsigned int _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 64, Tiled: 2][Tile0 Dim: 1][D0 Dim: Init: 64, Tiled: 32]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 32 logical tiles, 32 physical tiles
			Total Size: 3200 [D0, [31 x 100, 100]][Tile0, 1:[5x5], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[5x6, 30:5x7, 5x6], 2][D0, [31 x 100, 100]]
		Tile0: [0, 100, 50], Tile1: [100, 100, 50], Tile2; [200, 100, 50]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 128 [D1, [1 x 112, 16]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 112, 16]]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Filter, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 64 logical tiles, 64 physical tiles
			Total Size: 73728 [D1, [1 x 64512, 9216]][D0, [31 x 2016, 2016]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 64512, 9216]][D0, [31 x 2016, 2016]]
		Tile0: [0, 2016, 2016], Tile1: [2016, 2016, 2016], Tile2; [4032, 2016, 2016]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 2 physical tiles
			Total Size: 3200 [D1, [1 x 2800, 400]][Tile0, 1:[5x5], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 2800, 400]][Tile0, 1:[5x5], 2]
		Tile0: [0, 2800, 50], Tile1: [2800, 400, 50], Tile2; [0, 2800, 50]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 6400 [D1, [1 x 5600, 800]][Tile0, 1:[5x5], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 5600, 800]][Tile0, 1:[5x5], 4]
		Tile0: [0, 5600, 100], Tile1: [0, 5600, 100], Tile2; [0, 5600, 100]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+9960);
	KerArg0->W = (unsigned short int) (5);
	KerArg0->H = (unsigned short int) (5);
	KerArg0->NormBias = (signed char) (14);
	KerArg1->W = (unsigned short int) (5);
	KerArg1->UsedW = (unsigned short int) (5);
	KerArg1->InFeatures = (unsigned short int) (2);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+9960);
	KerArg1->Norm = (unsigned char) (15);
	KerArg1->TotalInFeatures = (short int) (2);
	KerArg1->Pad = (v4s) ((v4s){1,1,1,1});
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+9960);
	KerArg2->W = (unsigned short int) (5);
	KerArg2->H = (unsigned short int) (5);
	KerArg2->Norm = (unsigned char) (15);
	KerArg2->LB = (int) (-32768);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 100, 50, 50, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+200), 128, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Filter+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+13136+0), 2016, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read Filter */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Filter+2016), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+13136+2016), 2016, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+13136+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+328+0), 2016, 0, &DmaR_Evt3);
	_NN_Filter=2016; _SN_Filter=2016;
	_C_Out=0; _SC_Out=2800; _LC_Out=50;
	_SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	for (D1Ind=0; D1Ind<2; D1Ind++) { /* Iteration on D1 */
		int D1Ind_Last = (D1Ind==1), D1Ind_NextLast = ((D1Ind+1)==1), D1Ind_NextNextLast = ((D1Ind+2)==1);
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1, T0Ind_NextLast = 1;
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->OutFeatures = (unsigned short int) (D1Ind_Last?8:56);
			KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+200+((D1Ind)*112));
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<32; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==31), D0Ind_NextLast = ((D0Ind+1)==31), D0Ind_NextNextLast = ((D0Ind+2)==31);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (100); _LN_In = (50); _SN_In = (2*_LN_In); 
				} else if (!(D1Ind_Last)) {
					_N_In = _N_In + (-3100); _LN_In = (50); _SN_In = (2*_LN_In); 
				}
				_SNN_Filter = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_Filter = _NN_Filter + (((D1Ind_Last)?(288):(2016))); _SNN_Filter = (((D1Ind_Last)?(288):(2016))); 
					} else if (!((1))) {
						_NN_Filter = _NN_Filter + (((D1Ind_Last)?(-8928):(-62496))); _SNN_Filter = (((D1Ind_Last)?(288):(2016))); 
					} else if (!(D1Ind_Last)) {
						_NN_Filter = _NN_Filter + (64512)+(((D1Ind_Last)?(-8928):(-62496))); _SNN_Filter = (((1)?(288):(2016))); 
					}
				} else if (!((1))) {
					_NN_Filter = _NN_Filter + (((D1Ind_Last)?(288):(2016))); _SNN_Filter = (((D1Ind_Last)?(288):(2016))); 
				} else if (!(D1Ind_Last)) {
					_NN_Filter = _NN_Filter + (((1)?(288):(2016))); _SNN_Filter = (((1)?(288):(2016))); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+100*((D0Ind_Total+1)%2)),
							_SN_In, 50, _LN_In, 0, &DmaR_Evt1);
				}
				AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read Filter */
				if (_SNN_Filter) {
					AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Filter+_NN_Filter), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+13136+2016*((D0Ind_Total)%2)),
							_SNN_Filter, 0, &UchanHR1);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
				if (_SN_Filter) {
					AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+13136+2016*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+328+2016*((D0Ind_Total+1)%2)),
							_SN_Filter, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+100*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (7-1*(1)-1*(1));
				KerArg1->UsedH = (unsigned short int) (7-1*(1)-1*(1));
				KerArg1->OutFeatures = (unsigned short int) (D1Ind_Last?8:56);
				KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+328+2016*((D0Ind_Total)%2));
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				_SN_Filter = _SNN_Filter;
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+4360+2800*((T0Ind_Total)%2));
			KerArg2->InFeatures = (unsigned short int) (D1Ind_Last?8:56);
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+4360+2800*((T0Ind_Total)%2)),
					_SC_Out, 50, _LC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(D1Ind_Last)) {
				_C_Out = _C_Out + (2800); _LC_Out = (50); _SC_Out = (((1)?8:56)*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
			T0Ind_Total++;
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S69_MatAdd_64x5x5(
		short int * __restrict__ In1,
		short int * __restrict__ In2,
		short int * __restrict__ Out)

{
	/* Shared L1: 9600 bytes, L2 buffer: 9600 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaW_Evt1;
	KerMat3_fp_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int D0Ind, D0Ind_Last;
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D0 Dim: Init: 64, Tiled: 1][Tile0 Dim: 1]
	Ker Arg: In1, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 3200 [D0, [0 x 3200, 3200]][Tile0, 1:[5x5], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 3200, 3200]][Tile0, 1:[5x5], 2]
		Tile0: [0, 3200, 3200], Tile1: [0, 3200, 3200], Tile2; [0, 3200, 3200]
	Ker Arg: In2, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 3200 [D0, [0 x 3200, 3200]][Tile0, 1:[5x5], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 3200, 3200]][Tile0, 1:[5x5], 2]
		Tile0: [0, 3200, 3200], Tile1: [0, 3200, 3200], Tile2; [0, 3200, 3200]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 3200 [D0, [0 x 3200, 3200]][Tile0, 1:[5x5], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 3200, 3200]][Tile0, 1:[5x5], 2]
		Tile0: [0, 3200, 3200], Tile1: [0, 3200, 3200], Tile2; [0, 3200, 3200]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In1 = (short int *__restrict__) (resnet_L1_Memory+0);
	KerArg0->In2 = (short int *__restrict__) (resnet_L1_Memory+3200);
	KerArg0->Out = (short int *__restrict__) (resnet_L1_Memory+6400);
	KerArg0->W = (unsigned short int) (5);
	KerArg0->H = (unsigned short int) (5);
	KerArg0->N = (unsigned short int) (64);
	KerArg0->LB = (int) (-32768);
	KerArg0->UB = (int) (32767);
	KerArg0->In1_Q = (unsigned char) (13);
	KerArg0->In2_Q = (unsigned char) (12);
	KerArg0->Out_Q = (unsigned char) (11);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In1+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0), 3200, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In1 */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In2+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+3200), 3200, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In2 */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D0 */
		int D0Ind_Last = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			/*====================== Call Kernel LOC_LOOP =========================*/
			AT_FORK(gap_ncore(), (void *) KerParMatAddDynAdjust_fp, (void *) KerArg0);
			__CALL(KerParMatAddDynAdjust_fp, KerArg0);
		} /* End iteration on Tile0 */
	} /* End iteration on D0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+6400), 3200, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S70_AveragePool_2x2(
		short int * __restrict__ In,
		short int * __restrict__ Out)

{
	/* Shared L1: 3712 bytes, L2 buffer: 3712 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaW_Evt1;
	KerReLUPool_fp_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int D0Ind, D0Ind_Last;
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D0 Dim: Init: 64, Tiled: 1][Tile0 Dim: 1]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 3200 [D0, [0 x 3200, 3200]][Tile0, 1:[5x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 3200, 3200]][Tile0, 1:[5x4], 2]
		Tile0: [0, 3200, 3200], Tile1: [0, 3200, 3200], Tile2; [0, 3200, 3200]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 512 [D0, [0 x 512, 512]][Tile0, 1:[2x2], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 512, 512]][Tile0, 1:[2x2], 2]
		Tile0: [0, 512, 512], Tile1: [0, 512, 512], Tile2; [0, 512, 512]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (short int * __restrict__) (resnet_L1_Memory+0);
	KerArg0->W = (unsigned short int) (5);
	KerArg0->UsedW = (unsigned short int) (4);
	KerArg0->H = (unsigned short int) (5);
	KerArg0->OutFeatures = (unsigned short int) (64);
	KerArg0->Out = (short int * __restrict__) (resnet_L1_Memory+3200);
	KerArg0->Pad = (v4s) 0;
	KerArg0->Orientation = (unsigned char) (1);
	KerArg0->Oper = (unsigned char) (2);
	KerArg0->LB = (int) (-32768);
	KerArg0->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0), 3200, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D0 */
		int D0Ind_Last = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->UsedH = (unsigned short int) (4);
			AT_FORK(gap_ncore(), (void *) KerParPool2x2Stride2_fp, (void *) KerArg0);
			__CALL(KerParPool2x2Stride2_fp, KerArg0);
		} /* End iteration on Tile0 */
	} /* End iteration on D0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+3200), 512, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S73_Linear_7x64x2x2(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 4128 bytes, L2 buffer: 4128 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	KerLinearLayerReLU_fp_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int D0Ind, D0Ind_Last;
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D0 Dim: Init: 7, Tiled: 1][Tile0 Dim: 1]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 512 [Tile0, 1:[1x1], 512]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x1], 512]
		Tile0: [0, 512, 512], Tile1: [0, 512, 512], Tile2; [0, 512, 512]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 3584 [D0, [0 x 3584, 3584]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 3584, 3584]]
		Tile0: [0, 3584, 3584], Tile1: [0, 3584, 3584], Tile2; [0, 3584, 3584]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 14 [D0, [0 x 14, 14]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 14, 14]]
		Tile0: [0, 14, 14], Tile1: [0, 14, 14], Tile2; [0, 14, 14]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 14 [D0, [0 x 14, 14]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 14, 14]]
		Tile0: [0, 14, 14], Tile1: [0, 14, 14], Tile2; [0, 14, 14]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (short int * __restrict__) (resnet_L1_Memory+0);
	KerArg0->InSize = (unsigned short int) (256);
	KerArg0->TotalInSize = (unsigned short int) (256);
	KerArg0->OutSize = (unsigned short int) (7);
	KerArg0->Filter = (short int * __restrict__) (resnet_L1_Memory+512);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+4096);
	KerArg0->Out = (short int * __restrict__) (resnet_L1_Memory+4112);
	KerArg0->Norm = (unsigned char) (14);
	KerArg0->NormBias = (signed char) (11);
	KerArg0->LB = (int) (-32768);
	KerArg0->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0), 512, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Filter+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+864+0), 3584, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read Filter */
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+864+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+512), 3584, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Filter */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+4096), 14, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Bias */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D0 */
		int D0Ind_Last = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			/*====================== Call Kernel LOC_LOOP =========================*/
			AT_FORK(gap_ncore(), (void *) KerParLinearLayerReLU_fp, (void *) KerArg0);
			__CALL(KerParLinearLayerReLU_fp, KerArg0);
		} /* End iteration on Tile0 */
	} /* End iteration on D0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+4112), 14, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S74_SoftMax(
		short int * __restrict__ In,
		short int * __restrict__ Out)

{
	/* Shared L1: 32 bytes, L2 buffer: 32 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaW_Evt1;
	KerSoftMax_fp_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile0 Dim: 1]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 14 [Tile0, 1:[1x7], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x7], 2]
		Tile0: [0, 14, 14], Tile1: [0, 14, 14], Tile2; [0, 14, 14]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 14 [Tile0, 1:[1x7], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x7], 2]
		Tile0: [0, 14, 14], Tile1: [0, 14, 14], Tile2; [0, 14, 14]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (short int *__restrict__) (resnet_L1_Memory+0);
	KerArg0->N = (unsigned short int) (7);
	KerArg0->Norm = (unsigned short int) (12);
	KerArg0->Out = (short int *__restrict__) (resnet_L1_Memory+16);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0), 14, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile0 */
		int T0Ind_Last = 1;
		/*====================== Call Kernel LOC_LOOP =========================*/
		AT_FORK(gap_ncore(), (void *) KerParSoftMax_fp, (void *) KerArg0);
		__CALL(KerParSoftMax_fp, KerArg0);
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+16), 14, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
int resnetCNN_Construct()

{
	AT_HYPERFLASH_FS_FC_EVENT UchanHF1;
	AT_HYPERRAM_FC_EVENT UchanHR2;
	AT_HYPERFLASH_FS_CONF_T HyperFlashConf;
	int Error;
	AT_HYPERFLASH_FS_CONF_INIT(&HyperFlashConf, AT_MEM_L3_HFLASH, 0);
	AT_HYPERFLASH_FS_OPEN(&HyperFlash, &HyperFlashConf, "resnet_L3_Flash_Const.dat", &Error);
	if (Error) return 1;
	resnet_L3_Memory = (AT_HYPERRAM_POINTER) AT_HYPERRAM_ALLOC(&HyperRam, 402926);
	if (resnet_L3_Memory == 0) return 2;
	resnet_L2_Memory = (AT_L2_POINTER) AT_L2_ALLOC(0, 50000);
	if (resnet_L2_Memory == 0) return 3;
	resnet_L1_Memory = (AT_L1_POINTER) AT_L1_ALLOC(0, 16672);
	if (resnet_L1_Memory == 0) return 4;
	/* Moving Conv1kernel, size 784 from HyperFlash at 352000 to (size 784) HyperRam at 352000..352783 */
	{
		int Size = 784, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 352000+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 352000+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Res2bbranch2akernel, size 1152 from HyperFlash at 346368 to (size 1152) HyperRam at 346368..347519 */
	{
		int Size = 1152, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 346368+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 346368+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Model_1res2bbranch2aconv2d_bia, size 16 from HyperFlash at 354176 to (size 16) HyperRam at 354176..354191 */
	{
		int Size = 16, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 354176+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354176+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Res2bbranch2bkernel, size 1152 from HyperFlash at 347520 to (size 1152) HyperRam at 347520..348671 */
	{
		int Size = 1152, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 347520+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 347520+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Model_1res2bbranch2bconv2d_bia, size 16 from HyperFlash at 354192 to (size 16) HyperRam at 354192..354207 */
	{
		int Size = 16, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 354192+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354192+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Res2cbranch2akernel, size 1152 from HyperFlash at 348672 to (size 1152) HyperRam at 348672..349823 */
	{
		int Size = 1152, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 348672+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 348672+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Model_1res2cbranch2aconv2d_bia, size 16 from HyperFlash at 354208 to (size 16) HyperRam at 354208..354223 */
	{
		int Size = 16, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 354208+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354208+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Res2cbranch2bkernel, size 1152 from HyperFlash at 349824 to (size 1152) HyperRam at 349824..350975 */
	{
		int Size = 1152, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 349824+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 349824+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Model_1res2cbranch2bconv2d_bia, size 16 from HyperFlash at 354224 to (size 16) HyperRam at 354224..354239 */
	{
		int Size = 16, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 354224+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354224+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Res3a_branch2akernel, size 2304 from HyperFlash at 344064 to (size 2304) HyperRam at 344064..346367 */
	{
		int Size = 2304, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 344064+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 344064+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Model_1res3a_branch2aconv2d_bi, size 32 from HyperFlash at 354000 to (size 32) HyperRam at 354000..354031 */
	{
		int Size = 32, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 354000+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354000+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Model_1res3a_branch1conv2d_bia, size 32 from HyperFlash at 354032 to (size 32) HyperRam at 354032..354063 */
	{
		int Size = 32, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 354032+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354032+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Res3a_branch2bkernel, size 4608 from HyperFlash at 322560 to (size 4608) HyperRam at 322560..327167 */
	{
		int Size = 4608, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 322560+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 322560+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Model_1res3a_branch2bconv2d_bi, size 32 from HyperFlash at 354064 to (size 32) HyperRam at 354064..354095 */
	{
		int Size = 32, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 354064+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354064+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Res3bbranch2akernel, size 4608 from HyperFlash at 327168 to (size 4608) HyperRam at 327168..331775 */
	{
		int Size = 4608, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 327168+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 327168+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Model_1res3bbranch2aconv2d_bia, size 32 from HyperFlash at 354096 to (size 32) HyperRam at 354096..354127 */
	{
		int Size = 32, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 354096+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354096+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Res3bbranch2bkernel, size 4608 from HyperFlash at 331776 to (size 4608) HyperRam at 331776..336383 */
	{
		int Size = 4608, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 331776+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 331776+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Model_1res3bbranch2bconv2d_bia, size 32 from HyperFlash at 354128 to (size 32) HyperRam at 354128..354159 */
	{
		int Size = 32, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 354128+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354128+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Res4a_branch2akernel, size 9216 from HyperFlash at 313344 to (size 9216) HyperRam at 313344..322559 */
	{
		int Size = 9216, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 313344+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 313344+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Res4a_branch1kernel, size 1024 from HyperFlash at 350976 to (size 1024) HyperRam at 350976..351999 */
	{
		int Size = 1024, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 350976+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 350976+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Model_1res4a_branch1conv2d_bia, size 64 from HyperFlash at 353744 to (size 64) HyperRam at 353744..353807 */
	{
		int Size = 64, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 353744+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 353744+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Res4a_branch2bkernel, size 18432 from HyperFlash at 0 to (size 18432) HyperRam at 0..18431 */
	{
		int Size = 18432, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 0+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 0+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Model_1res4a_branch2bconv2d_bi, size 64 from HyperFlash at 353808 to (size 64) HyperRam at 353808..353871 */
	{
		int Size = 64, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 353808+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 353808+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Res4bbranch2akernel, size 18432 from HyperFlash at 276480 to (size 18432) HyperRam at 276480..294911 */
	{
		int Size = 18432, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 276480+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 276480+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Model_1res4bbranch2aconv2d_bia, size 64 from HyperFlash at 353872 to (size 64) HyperRam at 353872..353935 */
	{
		int Size = 64, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 353872+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 353872+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Res4bbranch2bkernel, size 18432 from HyperFlash at 294912 to (size 18432) HyperRam at 294912..313343 */
	{
		int Size = 18432, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 294912+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 294912+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Model_1res4bbranch2bconv2d_bia, size 64 from HyperFlash at 353936 to (size 64) HyperRam at 353936..353999 */
	{
		int Size = 64, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 353936+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 353936+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Res5a_branch2akernel, size 36864 from HyperFlash at 239616 to (size 36864) HyperRam at 239616..276479 */
	{
		int Size = 36864, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 239616+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 239616+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Model_1res5a_branch2aconv2d_bi, size 128 from HyperFlash at 353040 to (size 128) HyperRam at 353040..353167 */
	{
		int Size = 128, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 353040+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 353040+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Res5a_branch1kernel, size 4096 from HyperFlash at 336384 to (size 4096) HyperRam at 336384..340479 */
	{
		int Size = 4096, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 336384+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 336384+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Model_1res5a_branch1conv2d_bia, size 128 from HyperFlash at 353168 to (size 128) HyperRam at 353168..353295 */
	{
		int Size = 128, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 353168+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 353168+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Res5a_branch2bkernel, size 73728 from HyperFlash at 18432 to (size 73728) HyperRam at 18432..92159 */
	{
		int Size = 73728, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 18432+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 18432+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Model_1res5a_branch2bconv2d_bi, size 128 from HyperFlash at 353296 to (size 128) HyperRam at 353296..353423 */
	{
		int Size = 128, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 353296+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 353296+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Res5bbranch2akernel, size 73728 from HyperFlash at 92160 to (size 73728) HyperRam at 92160..165887 */
	{
		int Size = 73728, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 92160+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 92160+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Model_1res5bbranch2aconv2d_bia, size 128 from HyperFlash at 353424 to (size 128) HyperRam at 353424..353551 */
	{
		int Size = 128, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 353424+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 353424+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Res5bbranch2bkernel, size 73728 from HyperFlash at 165888 to (size 73728) HyperRam at 165888..239615 */
	{
		int Size = 73728, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 165888+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 165888+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Model_1res5bbranch2bconv2d_bia, size 128 from HyperFlash at 353552 to (size 128) HyperRam at 353552..353679 */
	{
		int Size = 128, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 353552+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 353552+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Weightedaveragekerneltranspose, size 3584 from HyperFlash at 340480 to (size 3584) HyperRam at 340480..344063 */
	{
		int Size = 3584, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 340480+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 340480+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving M2weightedaveragematmul_bias, size 14 from HyperFlash at 354240 to (size 14) HyperRam at 354240..354253 */
	{
		int Size = 14, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 354240+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354240+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Model_1conv1conv2d_bias, size 16 from HyperFlash at 354160 to (size 16) L2 at 320..335 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 354160), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 320), 16, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Res3a_branch1kernel, size 256 from HyperFlash at 352784 to (size 256) L2 at 0..255 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 352784), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), 256, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Model_1res4a_branch2aconv2d_bi, size 64 from HyperFlash at 353680 to (size 64) L2 at 256..319 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 353680), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 256), 64, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	return 0;
}
int resnetCNN_Destruct()

{
	AT_HYPERRAM_FREE(&HyperRam, resnet_L3_Memory, 402926);
	AT_L2_FREE(0, resnet_L2_Memory, 50000);
	AT_L1_FREE(0, resnet_L1_Memory, 16672);
	AT_HYPERFLASH_FS_CLOSE(&HyperFlash);
	return 0;
}
int resnetCNN(
		signed short * __restrict__ Input_1,
		signed short * __restrict__ Output_1)

{
	AT_HYPERRAM_CL_EVENT UchanHR0;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	AT_HYPERRAM_CL_EVENT UchanHR2;
	AT_HYPERRAM_CL_EVENT UchanHR3;
	AT_HYPERRAM_CL_EVENT UchanHR4;
	AT_HYPERRAM_CL_EVENT UchanHR5;
	AT_HYPERRAM_CL_EVENT UchanHR6;
	AT_HYPERRAM_CL_EVENT UchanHR7;
	/* Moving Conv1kernel, size 784 from HyperRam at 352000 to (size 784) L2 at 24672 using event 0 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 352000), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 24672), 784, 0, &UchanHR0);
	/* Moving Res2bbranch2akernel, size 1152 from HyperRam at 346368 to (size 1152) L2 at 30912 using event 1 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 346368), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 30912), 1152, 0, &UchanHR1);
	/* Moving Model_1res2bbranch2aconv2d_bia, size 16 from HyperRam at 354176 to (size 16) L2 at 32064 using event 2 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354176), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 32064), 16, 0, &UchanHR2);
	/* Moving Res2bbranch2bkernel, size 1152 from HyperRam at 347520 to (size 1152) L2 at 33096 using event 3 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 347520), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 33096), 1152, 0, &UchanHR3);
	/* Moving Model_1res2bbranch2bconv2d_bia, size 16 from HyperRam at 354192 to (size 16) L2 at 34248 using event 4 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354192), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 34248), 16, 0, &UchanHR4);
	/* Moving Res2cbranch2akernel, size 1152 from HyperRam at 348672 to (size 1152) L2 at 34656 using event 5 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 348672), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 34656), 1152, 0, &UchanHR5);
	/* Moving Model_1res2cbranch2aconv2d_bia, size 16 from HyperRam at 354208 to (size 16) L2 at 35808 using event 6 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354208), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 35808), 16, 0, &UchanHR6);
	/* Waiting completion of transfer of Conv1kernel using event 0 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR0);
	S4_Conv2d_8x1x7x7_MaxPool_3x3_Relu(
		((signed short * __restrict__) Input_1), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+24672)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+320)), /* Bias */
		((signed short * __restrict__) (resnet_L2_Memory+336)) /* Out */
	);
	/* Waiting completion of transfer of Res2bbranch2akernel using event 1 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1);
	/* Waiting completion of transfer of Model_1res2bbranch2aconv2d_bia using event 2 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2);
	S7_Conv2d_8x8x3x3_Relu(
		((signed short * __restrict__) (resnet_L2_Memory+336)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+30912)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+32064)), /* Bias */
		((signed short * __restrict__) (resnet_L3_Memory+354256)) /* Out */
	);
	/* Moving Res3a_branch2akernel, size 2304 from HyperRam at 344064 to (size 2304) L2 at 37472 using event 0 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 344064), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 37472), 2304, 0, &UchanHR0);
	/* Moving Model_1res3a_branch2aconv2d_bi, size 32 from HyperRam at 354000 to (size 32) L2 at 39776 using event 1 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354000), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 39776), 32, 0, &UchanHR1);
	/* Waiting completion of transfer of Res2bbranch2bkernel using event 3 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3);
	/* Waiting completion of transfer of Model_1res2bbranch2bconv2d_bia using event 4 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR4);
	S10_Conv2d_8x8x3x3(
		((signed short * __restrict__) (resnet_L3_Memory+354256)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+33096)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+34248)), /* Bias */
		((signed short * __restrict__) (resnet_L3_Memory+378592)) /* Out */
	);
	/* Moving Res3a_branch2bkernel, size 4608 from HyperRam at 322560 to (size 4608) L2 at 42592 using event 2 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 322560), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 42592), 4608, 0, &UchanHR2);
	/* Moving Model_1res3a_branch2bconv2d_bi, size 32 from HyperRam at 354064 to (size 32) L2 at 47200 using event 3 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354064), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 47200), 32, 0, &UchanHR3);
	S11_MatAdd_8x39x39(
		((signed short * __restrict__) (resnet_L3_Memory+378592)), /* In1 */
		((signed short * __restrict__) (resnet_L2_Memory+336)), /* In2 */
		((signed short * __restrict__) (resnet_L3_Memory+354256)) /* Out */
	);
	/* Moving Res2cbranch2bkernel, size 1152 from HyperRam at 349824 to (size 1152) L2 at 33096 using event 4 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 349824), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 33096), 1152, 0, &UchanHR4);
	/* Moving Model_1res2cbranch2bconv2d_bia, size 16 from HyperRam at 354224 to (size 16) L2 at 34248 using event 7 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354224), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 34248), 16, 0, &UchanHR7);
	/* Waiting completion of transfer of Res2cbranch2akernel using event 5 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR5);
	/* Waiting completion of transfer of Model_1res2cbranch2aconv2d_bia using event 6 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR6);
	S14_Conv2d_8x8x3x3_Relu(
		((signed short * __restrict__) (resnet_L3_Memory+354256)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+34656)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+35808)), /* Bias */
		((signed short * __restrict__) (resnet_L2_Memory+2520)) /* Out */
	);
	/* Waiting completion of transfer of Res2cbranch2bkernel using event 4 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR4);
	/* Waiting completion of transfer of Model_1res2cbranch2bconv2d_bia using event 7 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR7);
	S17_Conv2d_8x8x3x3(
		((signed short * __restrict__) (resnet_L2_Memory+2520)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+33096)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+34248)), /* Bias */
		((signed short * __restrict__) (resnet_L3_Memory+378592)) /* Out */
	);
	S18_MatAdd_8x39x39(
		((signed short * __restrict__) (resnet_L3_Memory+378592)), /* In1 */
		((signed short * __restrict__) (resnet_L3_Memory+354256)), /* In2 */
		((signed short * __restrict__) (resnet_L2_Memory+336)) /* Out */
	);
	/* Waiting completion of transfer of Res3a_branch2akernel using event 0 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR0);
	/* Waiting completion of transfer of Model_1res3a_branch2aconv2d_bi using event 1 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1);
	S21_Conv2d_16x8x3x3_Relu(
		((signed short * __restrict__) (resnet_L2_Memory+336)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+37472)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+39776)), /* Bias */
		((signed short * __restrict__) (resnet_L2_Memory+24672)) /* Out */
	);
	/* Waiting completion of transfer of Res3a_branch2bkernel using event 2 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2);
	/* Waiting completion of transfer of Model_1res3a_branch2bconv2d_bi using event 3 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3);
	S27_Conv2d_16x16x3x3_Relu(
		((signed short * __restrict__) (resnet_L2_Memory+24672)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+42592)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+47200)), /* Bias */
		((signed short * __restrict__) (resnet_L3_Memory+367056)) /* Out */
	);
	/* Moving Model_1res3a_branch1conv2d_bia, size 32 from HyperRam at 354032 to (size 32) L2 at 28768 using event 0 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354032), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 28768), 32, 0, &UchanHR0);
	/* Moving Model_1res3bbranch2aconv2d_bia, size 32 from HyperRam at 354096 to (size 32) L2 at 30544 using event 1 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354096), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 30544), 32, 0, &UchanHR1);
	/* Moving Res3bbranch2bkernel, size 4608 from HyperRam at 331776 to (size 4608) L2 at 31056 using event 2 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 331776), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 31056), 4608, 0, &UchanHR2);
	/* Moving Model_1res3bbranch2bconv2d_bia, size 32 from HyperRam at 354128 to (size 32) L2 at 35664 using event 3 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354128), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 35664), 32, 0, &UchanHR3);
	/* Waiting completion of transfer of Model_1res3a_branch1conv2d_bia using event 0 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR0);
	S24_Conv2d_16x8x1x1(
		((signed short * __restrict__) (resnet_L2_Memory+336)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+0)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+28768)), /* Bias */
		((signed short * __restrict__) (resnet_L3_Memory+354256)) /* Out */
	);
	/* Moving Res3bbranch2akernel, size 4608 from HyperRam at 327168 to (size 4608) L2 at 25936 using event 0 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 327168), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 25936), 4608, 0, &UchanHR0);
	S28_MatAdd_16x20x20(
		((signed short * __restrict__) (resnet_L3_Memory+367056)), /* In1 */
		((signed short * __restrict__) (resnet_L3_Memory+354256)), /* In2 */
		((signed short * __restrict__) (resnet_L2_Memory+336)) /* Out */
	);
	/* Waiting completion of transfer of Res3bbranch2akernel using event 0 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR0);
	/* Waiting completion of transfer of Model_1res3bbranch2aconv2d_bia using event 1 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1);
	S31_Conv2d_16x16x3x3_Relu(
		((signed short * __restrict__) (resnet_L2_Memory+336)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+25936)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+30544)), /* Bias */
		((signed short * __restrict__) (resnet_L2_Memory+13136)) /* Out */
	);
	/* Waiting completion of transfer of Res3bbranch2bkernel using event 2 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2);
	/* Waiting completion of transfer of Model_1res3bbranch2bconv2d_bia using event 3 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3);
	S34_Conv2d_16x16x3x3(
		((signed short * __restrict__) (resnet_L2_Memory+13136)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+31056)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+35664)), /* Bias */
		((signed short * __restrict__) (resnet_L3_Memory+354256)) /* Out */
	);
	S35_MatAdd_16x20x20(
		((signed short * __restrict__) (resnet_L3_Memory+354256)), /* In1 */
		((signed short * __restrict__) (resnet_L2_Memory+336)), /* In2 */
		((signed short * __restrict__) (resnet_L2_Memory+13136)) /* Out */
	);
	/* Moving Res4a_branch2akernel, size 9216 from HyperRam at 313344 to (size 9216) L2 at 25936 using event 0 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 313344), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 25936), 9216, 0, &UchanHR0);
	/* Moving Model_1res4a_branch2bconv2d_bi, size 64 from HyperRam at 353808 to (size 64) L2 at 7888 using event 1 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 353808), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 7888), 64, 0, &UchanHR1);
	/* Moving Model_1res4bbranch2bconv2d_bia, size 64 from HyperRam at 353936 to (size 64) L2 at 37968 using event 2 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 353936), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 37968), 64, 0, &UchanHR2);
	/* Waiting completion of transfer of Res4a_branch2akernel using event 0 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR0);
	S38_Conv2d_32x16x3x3_Relu(
		((signed short * __restrict__) (resnet_L2_Memory+13136)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+25936)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+256)), /* Bias */
		((signed short * __restrict__) (resnet_L2_Memory+336)) /* Out */
	);
	/* Moving Res4a_branch1kernel, size 1024 from HyperRam at 350976 to (size 1024) L2 at 32336 using event 0 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 350976), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 32336), 1024, 0, &UchanHR0);
	/* Moving Model_1res4a_branch1conv2d_bia, size 64 from HyperRam at 353744 to (size 64) L2 at 33360 using event 3 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 353744), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 33360), 64, 0, &UchanHR3);
	/* Waiting completion of transfer of Model_1res4a_branch2bconv2d_bi using event 1 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1);
	S44_Conv2d_32x32x3x3_Relu(
		((signed short * __restrict__) (resnet_L2_Memory+336)), /* In */
		((signed short * __restrict__) (resnet_L3_Memory+0)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+7888)), /* Bias */
		((signed short * __restrict__) (resnet_L2_Memory+25936)) /* Out */
	);
	/* Waiting completion of transfer of Res4a_branch1kernel using event 0 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR0);
	/* Waiting completion of transfer of Model_1res4a_branch1conv2d_bia using event 3 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3);
	S41_Conv2d_32x16x1x1(
		((signed short * __restrict__) (resnet_L2_Memory+13136)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+32336)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+33360)), /* Bias */
		((signed short * __restrict__) (resnet_L2_Memory+6736)) /* Out */
	);
	/* Moving Model_1res4bbranch2aconv2d_bia, size 64 from HyperRam at 353872 to (size 64) L2 at 32336 using event 0 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 353872), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 32336), 64, 0, &UchanHR0);
	S45_MatAdd_32x10x10(
		((signed short * __restrict__) (resnet_L2_Memory+25936)), /* In1 */
		((signed short * __restrict__) (resnet_L2_Memory+6736)), /* In2 */
		((signed short * __restrict__) (resnet_L2_Memory+336)) /* Out */
	);
	/* Moving Res4bbranch2akernel, size 18432 from HyperRam at 276480 to (size 18432) L2 at 13136 using event 1 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 276480), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 13136), 18432, 0, &UchanHR1);
	/* Waiting completion of transfer of Res4bbranch2akernel using event 1 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1);
	/* Waiting completion of transfer of Model_1res4bbranch2aconv2d_bia using event 0 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR0);
	S48_Conv2d_32x32x3x3_Relu(
		((signed short * __restrict__) (resnet_L2_Memory+336)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+13136)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+32336)), /* Bias */
		((signed short * __restrict__) (resnet_L2_Memory+6736)) /* Out */
	);
	/* Moving Res4bbranch2bkernel, size 18432 from HyperRam at 294912 to (size 18432) L2 at 19536 using event 0 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 294912), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 19536), 18432, 0, &UchanHR0);
	/* Waiting completion of transfer of Res4bbranch2bkernel using event 0 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR0);
	/* Waiting completion of transfer of Model_1res4bbranch2bconv2d_bia using event 2 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2);
	S51_Conv2d_32x32x3x3(
		((signed short * __restrict__) (resnet_L2_Memory+6736)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+19536)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+37968)), /* Bias */
		((signed short * __restrict__) (resnet_L2_Memory+13136)) /* Out */
	);
	S52_MatAdd_32x10x10(
		((signed short * __restrict__) (resnet_L2_Memory+13136)), /* In1 */
		((signed short * __restrict__) (resnet_L2_Memory+336)), /* In2 */
		((signed short * __restrict__) (resnet_L2_Memory+6736)) /* Out */
	);
	/* Moving Res5a_branch2akernel, size 36864 from HyperRam at 239616 to (size 36864) L2 at 13136 using event 0 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 239616), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 13136), 36864, 0, &UchanHR0);
	/* Moving Model_1res5a_branch2aconv2d_bi, size 128 from HyperRam at 353040 to (size 128) L2 at 3536 using event 1 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 353040), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 3536), 128, 0, &UchanHR1);
	/* Moving Model_1res5a_branch2bconv2d_bi, size 128 from HyperRam at 353296 to (size 128) L2 at 3664 using event 2 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 353296), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 3664), 128, 0, &UchanHR2);
	/* Waiting completion of transfer of Res5a_branch2akernel using event 0 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR0);
	/* Waiting completion of transfer of Model_1res5a_branch2aconv2d_bi using event 1 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1);
	S55_Conv2d_64x32x3x3_Relu(
		((signed short * __restrict__) (resnet_L2_Memory+6736)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+13136)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+3536)), /* Bias */
		((signed short * __restrict__) (resnet_L2_Memory+336)) /* Out */
	);
	/* Moving Res5a_branch1kernel, size 4096 from HyperRam at 336384 to (size 4096) L2 at 20368 using event 0 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 336384), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 20368), 4096, 0, &UchanHR0);
	/* Moving Model_1res5a_branch1conv2d_bia, size 128 from HyperRam at 353168 to (size 128) L2 at 3536 using event 1 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 353168), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 3536), 128, 0, &UchanHR1);
	/* Waiting completion of transfer of Model_1res5a_branch2bconv2d_bi using event 2 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2);
	S61_Conv2d_64x64x3x3_Relu(
		((signed short * __restrict__) (resnet_L2_Memory+336)), /* In */
		((signed short * __restrict__) (resnet_L3_Memory+18432)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+3664)), /* Bias */
		((signed short * __restrict__) (resnet_L2_Memory+13136)) /* Out */
	);
	/* Moving Model_1res5bbranch2bconv2d_bia, size 128 from HyperRam at 353552 to (size 128) L2 at 17168 using event 2 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 353552), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 17168), 128, 0, &UchanHR2);
	/* Waiting completion of transfer of Res5a_branch1kernel using event 0 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR0);
	/* Waiting completion of transfer of Model_1res5a_branch1conv2d_bia using event 1 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1);
	S58_Conv2d_64x32x1x1(
		((signed short * __restrict__) (resnet_L2_Memory+6736)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+20368)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+3536)), /* Bias */
		((signed short * __restrict__) (resnet_L2_Memory+336)) /* Out */
	);
	/* Moving Model_1res5bbranch2aconv2d_bia, size 128 from HyperRam at 353424 to (size 128) L2 at 10768 using event 0 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 353424), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 10768), 128, 0, &UchanHR0);
	S62_MatAdd_64x5x5(
		((signed short * __restrict__) (resnet_L2_Memory+13136)), /* In1 */
		((signed short * __restrict__) (resnet_L2_Memory+336)), /* In2 */
		((signed short * __restrict__) (resnet_L2_Memory+3536)) /* Out */
	);
	/* Waiting completion of transfer of Model_1res5bbranch2aconv2d_bia using event 0 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR0);
	S65_Conv2d_64x64x3x3_Relu(
		((signed short * __restrict__) (resnet_L2_Memory+3536)), /* In */
		((signed short * __restrict__) (resnet_L3_Memory+92160)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+10768)), /* Bias */
		((signed short * __restrict__) (resnet_L2_Memory+336)) /* Out */
	);
	/* Waiting completion of transfer of Model_1res5bbranch2bconv2d_bia using event 2 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2);
	S68_Conv2d_64x64x3x3(
		((signed short * __restrict__) (resnet_L2_Memory+336)), /* In */
		((signed short * __restrict__) (resnet_L3_Memory+165888)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+17168)), /* Bias */
		((signed short * __restrict__) (resnet_L2_Memory+9936)) /* Out */
	);
	S69_MatAdd_64x5x5(
		((signed short * __restrict__) (resnet_L2_Memory+9936)), /* In1 */
		((signed short * __restrict__) (resnet_L2_Memory+3536)), /* In2 */
		((signed short * __restrict__) (resnet_L2_Memory+6736)) /* Out */
	);
	/* Moving M2weightedaveragematmul_bias, size 14 from HyperRam at 354240 to (size 14) L2 at 4448 using event 0 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354240), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 4448), 14, 0, &UchanHR0);
	S70_AveragePool_2x2(
		((signed short * __restrict__) (resnet_L2_Memory+6736)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+336)) /* Out */
	);
	/* Waiting completion of transfer of M2weightedaveragematmul_bias using event 0 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR0);
	S73_Linear_7x64x2x2(
		((signed short * __restrict__) (resnet_L2_Memory+336)), /* In */
		((signed short * __restrict__) (resnet_L3_Memory+340480)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+4448)), /* Bias */
		((signed short * __restrict__) (resnet_L2_Memory+848)) /* Out */
	);
	S74_SoftMax(
		((signed short * __restrict__) (resnet_L2_Memory+848)), /* In */
		((signed short * __restrict__) Output_1) /* Out */
	);
	return 0;
}
