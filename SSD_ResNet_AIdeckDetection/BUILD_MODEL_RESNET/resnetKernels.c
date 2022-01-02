#include "resnetKernels.h"
L1_CL_MEM AT_L1_POINTER resnet_L1_Memory;
L2_MEM AT_L2_POINTER resnet_L2_Memory;
AT_HYPERRAM_POINTER resnet_L3_Memory;
extern AT_HYPERRAM_T HyperRam;
static AT_HYPERFLASH_FS_T HyperFlash;
void S4_Conv2d_8x1x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 13472 bytes, L2 buffer: 8416 bytes */
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
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 8, Tiled: 1][Tile0 Dim: 40][D0 Dim: Init: 1, Tiled: 1]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 40 logical tiles, 40 physical tiles
			Total Size: 99856 [D1, [0 x 99856, 99856]][Tile0, 40:[79x2, 38:79x2, 79x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 99856, 99856]][Tile0, 40:[79x2, 38:79x2, 79x1], 2]
		Tile0: [0, 2528, 316], Tile1: [316, 2528, 316], Tile2; [632, 2528, 316]
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
			Total Size: 144 [D1, [0 x 144, 144]][D0, [0 x 18, 18]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 144, 144]][D0, [0 x 18, 18]]
		Tile0: [0, 144, 144], Tile1: [0, 144, 144], Tile2; [0, 144, 144]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 40 logical tiles, 40 physical tiles
			Total Size: 51200 [D0, [0 x 51200, 51200]][Tile0, 40:[160x5, 38:160x5, 160x3], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 40:[160x5], 2][D0, [0 x 51200, 51200]]
		Tile0: [0, 1600, 1600], Tile1: [1280, 1600, 1600], Tile2; [2560, 1600, 1600]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 40 logical tiles, 1 physical tiles
			Total Size: 199712 [D1, [0 x 199712, 199712]][Tile0, 40:[79x2, 38:79x2, 79x1], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 199712, 199712]][Tile0, 40:[79x2, 38:79x2, 79x1], 4]
		Tile0: [0, 5056, 632], Tile1: [0, 5056, 632], Tile2; [0, 5056, 632]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+8416);
	KerArg0->W = (unsigned short int) (79);
	KerArg0->OutFeatures = (unsigned short int) (8);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+3200);
	KerArg0->NormBias = (signed char) (13);
	KerArg1->W = (unsigned short int) (160);
	KerArg1->UsedW = (unsigned short int) (159);
	KerArg1->InFeatures = (unsigned short int) (1);
	KerArg1->OutFeatures = (unsigned short int) (8);
	KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+3216);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+8416);
	KerArg1->Norm = (unsigned char) (14);
	KerArg1->TotalInFeatures = (short int) (1);
	KerArg1->Pad = (v4s) 0;
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+8416);
	KerArg2->W = (unsigned short int) (79);
	KerArg2->Norm = (unsigned char) (14);
	KerArg2->InFeatures = (unsigned short int) (8);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	_C_Out=0; _SC_Out=2528; _LC_Out=316;
	_SPP_Out=0; _SP_Out=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+3200), 16, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+3216), 144, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Filter */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 1600, 0, &DmaR_Evt3);
	_N_In=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<40; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==39), T0Ind_NextLast = ((T0Ind+1)==39);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->H = (unsigned short int) (T0Ind_Last?1:2);
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			{ /* Single iteration on D0 */
				int D0Ind_Last = 1, D0Ind_NextLast = 1;
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(T0Ind_Last)) {
					_N_In = _N_In + (1280); _SN_In = (1*((T0Ind_NextLast)?960:1600)); 
				} else if (!(1)) {
					_N_In = _N_In + (-49920); _SN_In = (1*(1600)); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+1600*((D0Ind_Total+1)%2)),
							_SN_In, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+1600*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (T0Ind_Last?3:5);
				KerArg1->UsedH = (unsigned short int) (T0Ind_Last?3:5);
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride2_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride2_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				/*============================= End Update Arg Pipeline =============================*/
				D0Ind_Total++;
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->H = (unsigned short int) (T0Ind_Last?1:2);
			KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+3360+2528*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+2528*((T0Ind_Total+-1)%2)),
						_SP_Out, 12482, _LP_Out, 1, &UchanHR1);
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+1280+2528*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+3360+2528*((T0Ind_Total)%2)),
					_SC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
			_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (316); _LC_Out = ((T0Ind_NextLast)?158:316); _SC_Out = (8*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+2528*((T0Ind_Total+-1)%2)), _SP_Out, 12482, _LP_Out, 1, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S7_Conv2d_8x8x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 16840 bytes, L2 buffer: 11848 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR2;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	KerSetBias_fpd_fp_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConv_DP_fp_T S_KerArg1, *KerArg1 = &S_KerArg1;
	KerDP_fp_T S_KerArg2, *KerArg2 = &S_KerArg2;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Last;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast, T0Ind_NextNextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast, D0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	unsigned int _LPP_Out, _LP_Out, _LC_Out;
	unsigned int _NN_In;
	unsigned int _SN_In, _SNN_In;
	unsigned int _LN_In, _LNN_In;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 8, Tiled: 1][Tile0 Dim: 10][D0 Dim: Init: 8, Tiled: 4]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 10 logical tiles, 10 physical tiles
			Total Size: 24336 [D1, [0 x 24336, 24336]][Tile0, 10:[39x4, 8:39x4, 39x3], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 24336, 24336]][Tile0, 10:[39x4, 8:39x4, 39x3], 2]
		Tile0: [0, 2496, 312], Tile1: [312, 2496, 312], Tile2; [624, 2496, 312]
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
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 40 logical tiles, 40 physical tiles
			Total Size: 99856 [D0, [3 x 24964, 24964]][Tile0, 10:[79x9, 8:79x9, 79x7], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 10:[79x9, 2:79x9, 79x7], 2][D0, [3 x 24964, 24964]]
		Tile0: [0, 2844, 1422], Tile1: [24964, 2844, 1422], Tile2; [49928, 2844, 1422]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 10 logical tiles, 1 physical tiles
			Total Size: 48672 [D1, [0 x 48672, 48672]][Tile0, 10:[39x4, 8:39x4, 39x3], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 48672, 48672]][Tile0, 10:[39x4, 8:39x4, 39x3], 4]
		Tile0: [0, 4992, 624], Tile1: [0, 4992, 624], Tile2; [0, 4992, 624]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+11848);
	KerArg0->W = (unsigned short int) (39);
	KerArg0->OutFeatures = (unsigned short int) (8);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+5688);
	KerArg0->NormBias = (signed char) (12);
	KerArg1->W = (unsigned short int) (79);
	KerArg1->UsedW = (unsigned short int) (79);
	KerArg1->InFeatures = (unsigned short int) (2);
	KerArg1->OutFeatures = (unsigned short int) (8);
	KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+5704);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+11848);
	KerArg1->Norm = (unsigned char) (14);
	KerArg1->TotalInFeatures = (short int) (8);
	KerArg1->Pad = (v4s) 0;
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+11848);
	KerArg2->W = (unsigned short int) (39);
	KerArg2->Norm = (unsigned char) (14);
	KerArg2->InFeatures = (unsigned short int) (8);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	_C_Out=0; _SC_Out=2496; _LC_Out=312;
	_SPP_Out=0; _SP_Out=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+5688), 16, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+5704), 1152, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Filter */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+0), 2844, 12482, 1422, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+24964), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+2844), 2844, 12482, 1422, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+1280+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 2844, 0, &DmaR_Evt3);
	_NN_In=24964; _SN_In=2844;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<10; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==9), T0Ind_NextLast = ((T0Ind+1)==9), T0Ind_NextNextLast = ((T0Ind+2)==9);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->H = (unsigned short int) (T0Ind_Last?3:4);
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<4; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==3), D0Ind_NextLast = ((D0Ind+1)==3), D0Ind_NextNextLast = ((D0Ind+2)==3);
				/*================================= Prepare Tiles ===================================*/
				_SNN_In = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_In = _NN_In + (24964); _LNN_In = ((T0Ind_Last)?1106:1422); _SNN_In = (2*_LNN_In); 
					} else if (!(T0Ind_Last)) {
						_NN_In = _NN_In + (1264)+(-74892); _LNN_In = ((T0Ind_NextLast)?1106:1422); _SNN_In = (2*_LNN_In); 
					} else if (!(1)) {
						_NN_In = _NN_In + (-11376)+(-74892); _LNN_In = (1422); _SNN_In = (2*_LNN_In); 
					}
				} else if (!(T0Ind_Last)) {
					_NN_In = _NN_In + (24964); _LNN_In = ((T0Ind_NextLast)?1106:1422); _SNN_In = (2*_LNN_In); 
				} else if (!((1))) {
					_NN_In = _NN_In + (24964); _LNN_In = (1422); _SNN_In = (2*_LNN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
				if (_SNN_In) {
					AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+2844*((D0Ind_Total)%2)),
							_SNN_In, 12482, _LNN_In, 0, &UchanHR1);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+1280+2844*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+2844*((D0Ind_Total+1)%2)),
							_SN_In, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+2844*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (T0Ind_Last?7:9);
				KerArg1->UsedH = (unsigned short int) (T0Ind_Last?7:9);
				KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+5704+((D0Ind)*36));
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride2_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride2_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				_SN_In = _SNN_In;_LN_In = _LNN_In;
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->H = (unsigned short int) (T0Ind_Last?3:4);
			KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+6856+2496*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+6968+2496*((T0Ind_Total+-1)%2)),
						_SP_Out, 3042, _LP_Out, 1, &UchanHR2);
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+6968+2496*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+6856+2496*((T0Ind_Total)%2)),
					_SC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
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
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+6968+2496*((T0Ind_Total+-1)%2)), _SP_Out, 3042, _LP_Out, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S10_Conv2d_8x8x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 18640 bytes, L2 buffer: 11152 bytes */
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
		[D1 Dim: Init: 8, Tiled: 1][Tile0 Dim: 7][D0 Dim: Init: 8, Tiled: 4]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 28 logical tiles, 28 physical tiles
			Total Size: 24336 [D0, [3 x 6084, 6084]][Tile0, 7:[39x7, 5:39x8, 39x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 7:[39x7, 2:39x8, 39x4], 2][D0, [3 x 6084, 6084]]
		Tile0: [0, 1092, 546], Tile1: [6084, 1092, 546], Tile2; [12168, 1092, 546]
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
		KerArgItSpace: 7 logical tiles, 7 physical tiles
			Total Size: 24336 [D1, [0 x 24336, 24336]][Tile0, 7:[39x6, 5:39x6, 39x3], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 24336, 24336]][Tile0, 7:[39x6, 5:39x6, 39x3], 2]
		Tile0: [0, 3744, 468], Tile1: [468, 3744, 468], Tile2; [936, 3744, 468]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 7 logical tiles, 1 physical tiles
			Total Size: 48672 [D1, [0 x 48672, 48672]][Tile0, 7:[39x6, 5:39x6, 39x3], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 48672, 48672]][Tile0, 7:[39x6, 5:39x6, 39x3], 4]
		Tile0: [0, 7488, 936], Tile1: [0, 7488, 936], Tile2; [0, 7488, 936]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+11152);
	KerArg0->W = (unsigned short int) (39);
	KerArg0->OutFeatures = (unsigned short int) (8);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+2496);
	KerArg0->NormBias = (signed char) (12);
	KerArg1->W = (unsigned short int) (39);
	KerArg1->UsedW = (unsigned short int) (39);
	KerArg1->InFeatures = (unsigned short int) (2);
	KerArg1->OutFeatures = (unsigned short int) (8);
	KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+2512);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+11152);
	KerArg1->Norm = (unsigned char) (13);
	KerArg1->TotalInFeatures = (short int) (8);
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+11152);
	KerArg2->W = (unsigned short int) (39);
	KerArg2->Norm = (unsigned char) (13);
	KerArg2->InFeatures = (unsigned short int) (8);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+0), 1092, 3042, 546, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+6084), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+1248), 1092, 3042, 546, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+1280+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 1092, 0, &DmaR_Evt1);
	_NN_In=6084; _SN_In=1092;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+2496), 16, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+2512), 1152, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
	_C_Out=0; _SC_Out=3744; _LC_Out=468;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<7; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==6), T0Ind_NextLast = ((T0Ind+1)==6), T0Ind_NextNextLast = ((T0Ind+2)==6);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->H = (unsigned short int) (T0Ind_Last?3:6);
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<4; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==3), D0Ind_NextLast = ((D0Ind+1)==3), D0Ind_NextNextLast = ((D0Ind+2)==3);
				/*================================= Prepare Tiles ===================================*/
				_SNN_In = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_In = _NN_In + (6084); _LNN_In = ((T0Ind_Last)?312:(624-78*(T0Ind==0))); _SNN_In = (2*_LNN_In); 
					} else if (!(T0Ind_Last)) {
						_NN_In = _NN_In + (468-(78*(T0Ind==0)))+(-18252); _LNN_In = ((T0Ind_NextLast)?312:624); _SNN_In = (2*_LNN_In); 
					} else if (!(1)) {
						_NN_In = _NN_In + (-2730)+(-18252); _LNN_In = (546); _SNN_In = (2*_LNN_In); 
					}
				} else if (!(T0Ind_Last)) {
					_NN_In = _NN_In + (6084); _LNN_In = ((T0Ind_NextLast)?312:624); _SNN_In = (2*_LNN_In); 
				} else if (!((1))) {
					_NN_In = _NN_In + (6084); _LNN_In = (546); _SNN_In = (2*_LNN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
				if (_SNN_In) {
					AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+1248*((D0Ind_Total)%2)),
							_SNN_In, 3042, _LNN_In, 0, &UchanHR1);
				}
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+1280+1248*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+1248*((D0Ind_Total+1)%2)),
							_SN_In, 0, &DmaR_Evt1);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+1248*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (((T0Ind_Last)?4:8)-1*(T0Ind==0));
				KerArg1->UsedH = (unsigned short int) (((T0Ind_Last)?4:8)-1*(T0Ind==0));
				KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+2512+((D0Ind)*36));
				KerArg1->Pad = (v4s) ((v4s){1,1,1*(T0Ind==0),1*(T0Ind_Last)});
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				_SN_In = _SNN_In;_LN_In = _LNN_In;
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->H = (unsigned short int) (T0Ind_Last?3:6);
			KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+3664+3744*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+3776+3744*((T0Ind_Total+-1)%2)),
						_SP_Out, 3042, _LP_Out, 1, &UchanHR2);
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+3776+3744*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+3664+3744*((T0Ind_Total)%2)),
					_SC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
			_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (468); _LC_Out = ((T0Ind_NextLast)?234:468); _SC_Out = (8*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+3776+3744*((T0Ind_Total+-1)%2)), _SP_Out, 3042, _LP_Out, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S13_Conv2d_8x8x3x3(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 18640 bytes, L2 buffer: 11152 bytes */
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
		[D1 Dim: Init: 8, Tiled: 1][Tile0 Dim: 7][D0 Dim: Init: 8, Tiled: 4]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 28 logical tiles, 28 physical tiles
			Total Size: 24336 [D0, [3 x 6084, 6084]][Tile0, 7:[39x7, 5:39x8, 39x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 7:[39x7, 2:39x8, 39x4], 2][D0, [3 x 6084, 6084]]
		Tile0: [0, 1092, 546], Tile1: [6084, 1092, 546], Tile2; [12168, 1092, 546]
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
		KerArgItSpace: 7 logical tiles, 7 physical tiles
			Total Size: 24336 [D1, [0 x 24336, 24336]][Tile0, 7:[39x6, 5:39x6, 39x3], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 24336, 24336]][Tile0, 7:[39x6, 5:39x6, 39x3], 2]
		Tile0: [0, 3744, 468], Tile1: [468, 3744, 468], Tile2; [936, 3744, 468]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 7 logical tiles, 1 physical tiles
			Total Size: 48672 [D1, [0 x 48672, 48672]][Tile0, 7:[39x6, 5:39x6, 39x3], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 48672, 48672]][Tile0, 7:[39x6, 5:39x6, 39x3], 4]
		Tile0: [0, 7488, 936], Tile1: [0, 7488, 936], Tile2; [0, 7488, 936]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+11152);
	KerArg0->W = (unsigned short int) (39);
	KerArg0->OutFeatures = (unsigned short int) (8);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+2496);
	KerArg0->NormBias = (signed char) (11);
	KerArg1->W = (unsigned short int) (39);
	KerArg1->UsedW = (unsigned short int) (39);
	KerArg1->InFeatures = (unsigned short int) (2);
	KerArg1->OutFeatures = (unsigned short int) (8);
	KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+2512);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+11152);
	KerArg1->Norm = (unsigned char) (15);
	KerArg1->TotalInFeatures = (short int) (8);
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+11152);
	KerArg2->W = (unsigned short int) (39);
	KerArg2->Norm = (unsigned char) (15);
	KerArg2->InFeatures = (unsigned short int) (8);
	KerArg2->LB = (int) (-32768);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+0), 1092, 3042, 546, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+6084), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+1248), 1092, 3042, 546, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+1280+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 1092, 0, &DmaR_Evt1);
	_NN_In=6084; _SN_In=1092;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+2496), 16, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+2512), 1152, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
	_C_Out=0; _SC_Out=3744; _LC_Out=468;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<7; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==6), T0Ind_NextLast = ((T0Ind+1)==6), T0Ind_NextNextLast = ((T0Ind+2)==6);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->H = (unsigned short int) (T0Ind_Last?3:6);
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<4; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==3), D0Ind_NextLast = ((D0Ind+1)==3), D0Ind_NextNextLast = ((D0Ind+2)==3);
				/*================================= Prepare Tiles ===================================*/
				_SNN_In = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_In = _NN_In + (6084); _LNN_In = ((T0Ind_Last)?312:(624-78*(T0Ind==0))); _SNN_In = (2*_LNN_In); 
					} else if (!(T0Ind_Last)) {
						_NN_In = _NN_In + (468-(78*(T0Ind==0)))+(-18252); _LNN_In = ((T0Ind_NextLast)?312:624); _SNN_In = (2*_LNN_In); 
					} else if (!(1)) {
						_NN_In = _NN_In + (-2730)+(-18252); _LNN_In = (546); _SNN_In = (2*_LNN_In); 
					}
				} else if (!(T0Ind_Last)) {
					_NN_In = _NN_In + (6084); _LNN_In = ((T0Ind_NextLast)?312:624); _SNN_In = (2*_LNN_In); 
				} else if (!((1))) {
					_NN_In = _NN_In + (6084); _LNN_In = (546); _SNN_In = (2*_LNN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
				if (_SNN_In) {
					AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+1248*((D0Ind_Total)%2)),
							_SNN_In, 3042, _LNN_In, 0, &UchanHR1);
				}
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+1280+1248*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+1248*((D0Ind_Total+1)%2)),
							_SN_In, 0, &DmaR_Evt1);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+1248*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (((T0Ind_Last)?4:8)-1*(T0Ind==0));
				KerArg1->UsedH = (unsigned short int) (((T0Ind_Last)?4:8)-1*(T0Ind==0));
				KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+2512+((D0Ind)*36));
				KerArg1->Pad = (v4s) ((v4s){1,1,1*(T0Ind==0),1*(T0Ind_Last)});
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				_SN_In = _SNN_In;_LN_In = _LNN_In;
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->H = (unsigned short int) (T0Ind_Last?3:6);
			KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+3664+3744*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+3776+3744*((T0Ind_Total+-1)%2)),
						_SP_Out, 3042, _LP_Out, 1, &UchanHR2);
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+3776+3744*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+3664+3744*((T0Ind_Total)%2)),
					_SC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
			_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (468); _LC_Out = ((T0Ind_NextLast)?234:468); _SC_Out = (8*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+3776+3744*((T0Ind_Total+-1)%2)), _SP_Out, 3042, _LP_Out, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S14_MatAdd_8x39x39(
		short int * __restrict__ In1,
		short int * __restrict__ In2,
		short int * __restrict__ Out)

{
	/* Shared L1: 18720 bytes, L2 buffer: 18720 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	AT_HYPERRAM_CL_EVENT UchanHR2;
	AT_HYPERRAM_CL_EVENT UchanHR3;
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
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	unsigned int _LPP_Out, _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D0 Dim: Init: 8, Tiled: 1][Tile0 Dim: 8]
	Ker Arg: In1, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 8 logical tiles, 8 physical tiles
			Total Size: 24336 [D0, [0 x 24336, 24336]][Tile0, 8:[39x5, 6:39x5, 39x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 24336, 24336]][Tile0, 8:[39x5, 6:39x5, 39x4], 2]
		Tile0: [0, 3120, 390], Tile1: [390, 3120, 390], Tile2; [780, 3120, 390]
	Ker Arg: In2, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 8 logical tiles, 8 physical tiles
			Total Size: 24336 [D0, [0 x 24336, 24336]][Tile0, 8:[39x5, 6:39x5, 39x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 24336, 24336]][Tile0, 8:[39x5, 6:39x5, 39x4], 2]
		Tile0: [0, 3120, 390], Tile1: [390, 3120, 390], Tile2; [780, 3120, 390]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 8 logical tiles, 8 physical tiles
			Total Size: 24336 [D0, [0 x 24336, 24336]][Tile0, 8:[39x5, 6:39x5, 39x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 24336, 24336]][Tile0, 8:[39x5, 6:39x5, 39x4], 2]
		Tile0: [0, 3120, 390], Tile1: [390, 3120, 390], Tile2; [780, 3120, 390]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->W = (unsigned short int) (39);
	KerArg0->N = (unsigned short int) (8);
	KerArg0->LB = (int) (-32768);
	KerArg0->UB = (int) (32767);
	KerArg0->In1_Q = (unsigned char) (10);
	KerArg0->In2_Q = (unsigned char) (11);
	KerArg0->Out_Q = (unsigned char) (10);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In1+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+13760+0), 3120, 3042, 390, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In1 */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In1+390), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+13760+3120), 3120, 3042, 390, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+13760+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 3120, 0, &DmaR_Evt1);
	_NN_In1=390; _SN_In1=3120;
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+7520+0), 3120, 3042, 390, 0, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read In2 */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+390), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+7520+3120), 3120, 3042, 390, 0, &UchanHR2);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+7520+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+6240+0), 3120, 0, &DmaR_Evt2);
	_NN_In2=390; _SN_In2=3120;
	_C_Out=0; _SC_Out=3120; _LC_Out=390;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D0 */
		int D0Ind_Last = 1, D0Ind_NextLast = 1, D0Ind_NextNextLast = 1;
		for (T0Ind=0; T0Ind<8; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==7), T0Ind_NextLast = ((T0Ind+1)==7), T0Ind_NextNextLast = ((T0Ind+2)==7);
			/*================================= Prepare Tiles ===================================*/
			_SNN_In1 = 0;
			if (!(T0Ind_Last)) {
				if (!(T0Ind_NextLast)) {
					_NN_In1 = _NN_In1 + (390); _LNN_In1 = ((T0Ind_NextNextLast)?312:390); _SNN_In1 = (8*_LNN_In1); 
				}
			}
			_SNN_In2 = 0;
			if (!(T0Ind_Last)) {
				if (!(T0Ind_NextLast)) {
					_NN_In2 = _NN_In2 + (390); _LNN_In2 = ((T0Ind_NextNextLast)?312:390); _SNN_In2 = (8*_LNN_In2); 
				}
			}
			/*============================= End Prepare Tiles ===================================*/
			/*================================= Read Tiles ======================================*/
			AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In1 */
			if (_SNN_In1) {
				AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In1+_NN_In1), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+13760+3120*((T0Ind_Total)%2)),
						_SNN_In1, 3042, _LNN_In1, 0, &UchanHR1);
			}
			AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In1 */
			if (_SN_In1) {
				AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+13760+3120*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+3120*((T0Ind_Total+1)%2)),
						_SN_In1, 0, &DmaR_Evt1);
			}
			AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read In2 */
			if (_SNN_In2) {
				AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+_NN_In2), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+7520+3120*((T0Ind_Total)%2)),
						_SNN_In2, 3042, _LNN_In2, 0, &UchanHR2);
			}
			AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In2 */
			if (_SN_In2) {
				AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+7520+3120*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+6240+3120*((T0Ind_Total+1)%2)),
						_SN_In2, 0, &DmaR_Evt2);
			}
			/*============================= End Read Tiles ======================================*/
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In1 = (short int *__restrict__) (resnet_L1_Memory+0+3120*((T0Ind_Total)%2));
			KerArg0->In2 = (short int *__restrict__) (resnet_L1_Memory+6240+3120*((T0Ind_Total)%2));
			KerArg0->Out = (short int *__restrict__) (resnet_L1_Memory+12480+3120*((T0Ind_Total)%2));
			KerArg0->H = (unsigned short int) (T0Ind_Last?4:5);
			AT_FORK(gap_ncore(), (void *) KerParMatAddDynAdjust_fp, (void *) KerArg0);
			__CALL(KerParMatAddDynAdjust_fp, KerArg0);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+3120*((T0Ind_Total+-1)%2)),
						_SP_Out, 3042, _LP_Out, 1, &UchanHR3);
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+1280+3120*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+12480+3120*((T0Ind_Total)%2)),
					_SC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SN_In1 = _SNN_In1;_LN_In1 = _LNN_In1;
			_SN_In2 = _SNN_In2;_LN_In2 = _LNN_In2;
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
	} /* End iteration on D0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+3120*((T0Ind_Total+-1)%2)), _SP_Out, 3042, _LP_Out, 1, &UchanHR3);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S17_Conv2d_8x8x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 18640 bytes, L2 buffer: 11152 bytes */
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
		[D1 Dim: Init: 8, Tiled: 1][Tile0 Dim: 7][D0 Dim: Init: 8, Tiled: 4]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 28 logical tiles, 28 physical tiles
			Total Size: 24336 [D0, [3 x 6084, 6084]][Tile0, 7:[39x7, 5:39x8, 39x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 7:[39x7, 2:39x8, 39x4], 2][D0, [3 x 6084, 6084]]
		Tile0: [0, 1092, 546], Tile1: [6084, 1092, 546], Tile2; [12168, 1092, 546]
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
		KerArgItSpace: 7 logical tiles, 7 physical tiles
			Total Size: 24336 [D1, [0 x 24336, 24336]][Tile0, 7:[39x6, 5:39x6, 39x3], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 24336, 24336]][Tile0, 7:[39x6, 5:39x6, 39x3], 2]
		Tile0: [0, 3744, 468], Tile1: [468, 3744, 468], Tile2; [936, 3744, 468]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 7 logical tiles, 1 physical tiles
			Total Size: 48672 [D1, [0 x 48672, 48672]][Tile0, 7:[39x6, 5:39x6, 39x3], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 48672, 48672]][Tile0, 7:[39x6, 5:39x6, 39x3], 4]
		Tile0: [0, 7488, 936], Tile1: [0, 7488, 936], Tile2; [0, 7488, 936]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+11152);
	KerArg0->W = (unsigned short int) (39);
	KerArg0->OutFeatures = (unsigned short int) (8);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+2496);
	KerArg0->NormBias = (signed char) (10);
	KerArg1->W = (unsigned short int) (39);
	KerArg1->UsedW = (unsigned short int) (39);
	KerArg1->InFeatures = (unsigned short int) (2);
	KerArg1->OutFeatures = (unsigned short int) (8);
	KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+2512);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+11152);
	KerArg1->Norm = (unsigned char) (13);
	KerArg1->TotalInFeatures = (short int) (8);
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+11152);
	KerArg2->W = (unsigned short int) (39);
	KerArg2->Norm = (unsigned char) (13);
	KerArg2->InFeatures = (unsigned short int) (8);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+0), 1092, 3042, 546, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+6084), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+1248), 1092, 3042, 546, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+1280+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 1092, 0, &DmaR_Evt1);
	_NN_In=6084; _SN_In=1092;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+2496), 16, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+2512), 1152, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
	_C_Out=0; _SC_Out=3744; _LC_Out=468;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<7; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==6), T0Ind_NextLast = ((T0Ind+1)==6), T0Ind_NextNextLast = ((T0Ind+2)==6);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->H = (unsigned short int) (T0Ind_Last?3:6);
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<4; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==3), D0Ind_NextLast = ((D0Ind+1)==3), D0Ind_NextNextLast = ((D0Ind+2)==3);
				/*================================= Prepare Tiles ===================================*/
				_SNN_In = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_In = _NN_In + (6084); _LNN_In = ((T0Ind_Last)?312:(624-78*(T0Ind==0))); _SNN_In = (2*_LNN_In); 
					} else if (!(T0Ind_Last)) {
						_NN_In = _NN_In + (468-(78*(T0Ind==0)))+(-18252); _LNN_In = ((T0Ind_NextLast)?312:624); _SNN_In = (2*_LNN_In); 
					} else if (!(1)) {
						_NN_In = _NN_In + (-2730)+(-18252); _LNN_In = (546); _SNN_In = (2*_LNN_In); 
					}
				} else if (!(T0Ind_Last)) {
					_NN_In = _NN_In + (6084); _LNN_In = ((T0Ind_NextLast)?312:624); _SNN_In = (2*_LNN_In); 
				} else if (!((1))) {
					_NN_In = _NN_In + (6084); _LNN_In = (546); _SNN_In = (2*_LNN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
				if (_SNN_In) {
					AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+1248*((D0Ind_Total)%2)),
							_SNN_In, 3042, _LNN_In, 0, &UchanHR1);
				}
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+1280+1248*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+1248*((D0Ind_Total+1)%2)),
							_SN_In, 0, &DmaR_Evt1);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+1248*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (((T0Ind_Last)?4:8)-1*(T0Ind==0));
				KerArg1->UsedH = (unsigned short int) (((T0Ind_Last)?4:8)-1*(T0Ind==0));
				KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+2512+((D0Ind)*36));
				KerArg1->Pad = (v4s) ((v4s){1,1,1*(T0Ind==0),1*(T0Ind_Last)});
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				_SN_In = _SNN_In;_LN_In = _LNN_In;
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->H = (unsigned short int) (T0Ind_Last?3:6);
			KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+3664+3744*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+3776+3744*((T0Ind_Total+-1)%2)),
						_SP_Out, 3042, _LP_Out, 1, &UchanHR2);
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+3776+3744*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+3664+3744*((T0Ind_Total)%2)),
					_SC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
			_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (468); _LC_Out = ((T0Ind_NextLast)?234:468); _SC_Out = (8*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+3776+3744*((T0Ind_Total+-1)%2)), _SP_Out, 3042, _LP_Out, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S20_Conv2d_8x8x3x3(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 18640 bytes, L2 buffer: 11152 bytes */
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
		[D1 Dim: Init: 8, Tiled: 1][Tile0 Dim: 7][D0 Dim: Init: 8, Tiled: 4]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 28 logical tiles, 28 physical tiles
			Total Size: 24336 [D0, [3 x 6084, 6084]][Tile0, 7:[39x7, 5:39x8, 39x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 7:[39x7, 2:39x8, 39x4], 2][D0, [3 x 6084, 6084]]
		Tile0: [0, 1092, 546], Tile1: [6084, 1092, 546], Tile2; [12168, 1092, 546]
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
		KerArgItSpace: 7 logical tiles, 7 physical tiles
			Total Size: 24336 [D1, [0 x 24336, 24336]][Tile0, 7:[39x6, 5:39x6, 39x3], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 24336, 24336]][Tile0, 7:[39x6, 5:39x6, 39x3], 2]
		Tile0: [0, 3744, 468], Tile1: [468, 3744, 468], Tile2; [936, 3744, 468]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 7 logical tiles, 1 physical tiles
			Total Size: 48672 [D1, [0 x 48672, 48672]][Tile0, 7:[39x6, 5:39x6, 39x3], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 48672, 48672]][Tile0, 7:[39x6, 5:39x6, 39x3], 4]
		Tile0: [0, 7488, 936], Tile1: [0, 7488, 936], Tile2; [0, 7488, 936]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+11152);
	KerArg0->W = (unsigned short int) (39);
	KerArg0->OutFeatures = (unsigned short int) (8);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+2496);
	KerArg0->NormBias = (signed char) (13);
	KerArg1->W = (unsigned short int) (39);
	KerArg1->UsedW = (unsigned short int) (39);
	KerArg1->InFeatures = (unsigned short int) (2);
	KerArg1->OutFeatures = (unsigned short int) (8);
	KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+2512);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+11152);
	KerArg1->Norm = (unsigned char) (15);
	KerArg1->TotalInFeatures = (short int) (8);
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+11152);
	KerArg2->W = (unsigned short int) (39);
	KerArg2->Norm = (unsigned char) (15);
	KerArg2->InFeatures = (unsigned short int) (8);
	KerArg2->LB = (int) (-32768);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+0), 1092, 3042, 546, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+6084), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+1248), 1092, 3042, 546, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+1280+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 1092, 0, &DmaR_Evt1);
	_NN_In=6084; _SN_In=1092;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+2496), 16, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+2512), 1152, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
	_C_Out=0; _SC_Out=3744; _LC_Out=468;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<7; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==6), T0Ind_NextLast = ((T0Ind+1)==6), T0Ind_NextNextLast = ((T0Ind+2)==6);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->H = (unsigned short int) (T0Ind_Last?3:6);
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<4; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==3), D0Ind_NextLast = ((D0Ind+1)==3), D0Ind_NextNextLast = ((D0Ind+2)==3);
				/*================================= Prepare Tiles ===================================*/
				_SNN_In = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_In = _NN_In + (6084); _LNN_In = ((T0Ind_Last)?312:(624-78*(T0Ind==0))); _SNN_In = (2*_LNN_In); 
					} else if (!(T0Ind_Last)) {
						_NN_In = _NN_In + (468-(78*(T0Ind==0)))+(-18252); _LNN_In = ((T0Ind_NextLast)?312:624); _SNN_In = (2*_LNN_In); 
					} else if (!(1)) {
						_NN_In = _NN_In + (-2730)+(-18252); _LNN_In = (546); _SNN_In = (2*_LNN_In); 
					}
				} else if (!(T0Ind_Last)) {
					_NN_In = _NN_In + (6084); _LNN_In = ((T0Ind_NextLast)?312:624); _SNN_In = (2*_LNN_In); 
				} else if (!((1))) {
					_NN_In = _NN_In + (6084); _LNN_In = (546); _SNN_In = (2*_LNN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
				if (_SNN_In) {
					AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+1248*((D0Ind_Total)%2)),
							_SNN_In, 3042, _LNN_In, 0, &UchanHR1);
				}
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+1280+1248*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+1248*((D0Ind_Total+1)%2)),
							_SN_In, 0, &DmaR_Evt1);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+1248*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (((T0Ind_Last)?4:8)-1*(T0Ind==0));
				KerArg1->UsedH = (unsigned short int) (((T0Ind_Last)?4:8)-1*(T0Ind==0));
				KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+2512+((D0Ind)*36));
				KerArg1->Pad = (v4s) ((v4s){1,1,1*(T0Ind==0),1*(T0Ind_Last)});
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				_SN_In = _SNN_In;_LN_In = _LNN_In;
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->H = (unsigned short int) (T0Ind_Last?3:6);
			KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+3664+3744*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+3776+3744*((T0Ind_Total+-1)%2)),
						_SP_Out, 3042, _LP_Out, 1, &UchanHR2);
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+3776+3744*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+3664+3744*((T0Ind_Total)%2)),
					_SC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
			_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (468); _LC_Out = ((T0Ind_NextLast)?234:468); _SC_Out = (8*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+3776+3744*((T0Ind_Total+-1)%2)), _SP_Out, 3042, _LP_Out, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S21_MatAdd_8x39x39(
		short int * __restrict__ In1,
		short int * __restrict__ In2,
		short int * __restrict__ Out)

{
	/* Shared L1: 18720 bytes, L2 buffer: 18720 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	AT_HYPERRAM_CL_EVENT UchanHR2;
	AT_HYPERRAM_CL_EVENT UchanHR3;
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
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	unsigned int _LPP_Out, _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D0 Dim: Init: 8, Tiled: 1][Tile0 Dim: 8]
	Ker Arg: In1, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 8 logical tiles, 8 physical tiles
			Total Size: 24336 [D0, [0 x 24336, 24336]][Tile0, 8:[39x5, 6:39x5, 39x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 24336, 24336]][Tile0, 8:[39x5, 6:39x5, 39x4], 2]
		Tile0: [0, 3120, 390], Tile1: [390, 3120, 390], Tile2; [780, 3120, 390]
	Ker Arg: In2, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 8 logical tiles, 8 physical tiles
			Total Size: 24336 [D0, [0 x 24336, 24336]][Tile0, 8:[39x5, 6:39x5, 39x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 24336, 24336]][Tile0, 8:[39x5, 6:39x5, 39x4], 2]
		Tile0: [0, 3120, 390], Tile1: [390, 3120, 390], Tile2; [780, 3120, 390]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 8 logical tiles, 8 physical tiles
			Total Size: 24336 [D0, [0 x 24336, 24336]][Tile0, 8:[39x5, 6:39x5, 39x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 24336, 24336]][Tile0, 8:[39x5, 6:39x5, 39x4], 2]
		Tile0: [0, 3120, 390], Tile1: [390, 3120, 390], Tile2; [780, 3120, 390]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->W = (unsigned short int) (39);
	KerArg0->N = (unsigned short int) (8);
	KerArg0->LB = (int) (-32768);
	KerArg0->UB = (int) (32767);
	KerArg0->In1_Q = (unsigned char) (11);
	KerArg0->In2_Q = (unsigned char) (10);
	KerArg0->Out_Q = (unsigned char) (10);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In1+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+13760+0), 3120, 3042, 390, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In1 */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In1+390), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+13760+3120), 3120, 3042, 390, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+13760+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 3120, 0, &DmaR_Evt1);
	_NN_In1=390; _SN_In1=3120;
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+0), 3120, 3042, 390, 0, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read In2 */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+390), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+3120), 3120, 3042, 390, 0, &UchanHR2);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+1280+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+6240+0), 3120, 0, &DmaR_Evt2);
	_NN_In2=390; _SN_In2=3120;
	_C_Out=0; _SC_Out=3120; _LC_Out=390;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D0 */
		int D0Ind_Last = 1, D0Ind_NextLast = 1, D0Ind_NextNextLast = 1;
		for (T0Ind=0; T0Ind<8; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==7), T0Ind_NextLast = ((T0Ind+1)==7), T0Ind_NextNextLast = ((T0Ind+2)==7);
			/*================================= Prepare Tiles ===================================*/
			_SNN_In1 = 0;
			if (!(T0Ind_Last)) {
				if (!(T0Ind_NextLast)) {
					_NN_In1 = _NN_In1 + (390); _LNN_In1 = ((T0Ind_NextNextLast)?312:390); _SNN_In1 = (8*_LNN_In1); 
				}
			}
			_SNN_In2 = 0;
			if (!(T0Ind_Last)) {
				if (!(T0Ind_NextLast)) {
					_NN_In2 = _NN_In2 + (390); _LNN_In2 = ((T0Ind_NextNextLast)?312:390); _SNN_In2 = (8*_LNN_In2); 
				}
			}
			/*============================= End Prepare Tiles ===================================*/
			/*================================= Read Tiles ======================================*/
			AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In1 */
			if (_SNN_In1) {
				AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In1+_NN_In1), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+13760+3120*((T0Ind_Total)%2)),
						_SNN_In1, 3042, _LNN_In1, 0, &UchanHR1);
			}
			AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In1 */
			if (_SN_In1) {
				AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+13760+3120*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+3120*((T0Ind_Total+1)%2)),
						_SN_In1, 0, &DmaR_Evt1);
			}
			AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read In2 */
			if (_SNN_In2) {
				AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+_NN_In2), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+3120*((T0Ind_Total)%2)),
						_SNN_In2, 3042, _LNN_In2, 0, &UchanHR2);
			}
			AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In2 */
			if (_SN_In2) {
				AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+1280+3120*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+6240+3120*((T0Ind_Total+1)%2)),
						_SN_In2, 0, &DmaR_Evt2);
			}
			/*============================= End Read Tiles ======================================*/
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In1 = (short int *__restrict__) (resnet_L1_Memory+0+3120*((T0Ind_Total)%2));
			KerArg0->In2 = (short int *__restrict__) (resnet_L1_Memory+6240+3120*((T0Ind_Total)%2));
			KerArg0->Out = (short int *__restrict__) (resnet_L1_Memory+12480+3120*((T0Ind_Total)%2));
			KerArg0->H = (unsigned short int) (T0Ind_Last?4:5);
			AT_FORK(gap_ncore(), (void *) KerParMatAddDynAdjust_fp, (void *) KerArg0);
			__CALL(KerParMatAddDynAdjust_fp, KerArg0);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+7520+3120*((T0Ind_Total+-1)%2)),
						_SP_Out, 3042, _LP_Out, 1, &UchanHR3);
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+7520+3120*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+12480+3120*((T0Ind_Total)%2)),
					_SC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SN_In1 = _SNN_In1;_LN_In1 = _LNN_In1;
			_SN_In2 = _SNN_In2;_LN_In2 = _LNN_In2;
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
	} /* End iteration on D0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+7520+3120*((T0Ind_Total+-1)%2)), _SP_Out, 3042, _LP_Out, 1, &UchanHR3);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S24_Conv2d_16x8x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 18568 bytes, L2 buffer: 12168 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR2;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	KerSetBias_fpd_fp_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConv_DP_fp_T S_KerArg1, *KerArg1 = &S_KerArg1;
	KerDP_fp_T S_KerArg2, *KerArg2 = &S_KerArg2;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Last;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast, T0Ind_NextNextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast, D0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	unsigned int _LPP_Out, _LP_Out, _LC_Out;
	unsigned int _NN_In;
	unsigned int _SN_In, _SNN_In;
	unsigned int _LN_In, _LNN_In;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 16, Tiled: 1][Tile0 Dim: 4][D0 Dim: Init: 8, Tiled: 4]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 4 logical tiles, 4 physical tiles
			Total Size: 12800 [D1, [0 x 12800, 12800]][Tile0, 4:[20x5, 2:20x5, 20x5], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 12800, 12800]][Tile0, 4:[20x5, 2:20x5, 20x5], 2]
		Tile0: [0, 3200, 200], Tile1: [200, 3200, 200], Tile2; [400, 3200, 200]
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
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 16 logical tiles, 16 physical tiles
			Total Size: 24336 [D0, [3 x 6084, 6084]][Tile0, 4:[39x10, 2:39x11, 39x10], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 4:[39x10, 2:39x11, 39x10], 2][D0, [3 x 6084, 6084]]
		Tile0: [0, 1560, 780], Tile1: [6084, 1560, 780], Tile2; [12168, 1560, 780]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 4 logical tiles, 1 physical tiles
			Total Size: 25600 [D1, [0 x 25600, 25600]][Tile0, 4:[20x5, 2:20x5, 20x5], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 25600, 25600]][Tile0, 4:[20x5, 2:20x5, 20x5], 4]
		Tile0: [0, 6400, 400], Tile1: [0, 6400, 400], Tile2; [0, 6400, 400]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+12168);
	KerArg0->W = (unsigned short int) (20);
	KerArg0->H = (unsigned short int) (5);
	KerArg0->OutFeatures = (unsigned short int) (16);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+3432);
	KerArg0->NormBias = (signed char) (11);
	KerArg1->W = (unsigned short int) (39);
	KerArg1->UsedW = (unsigned short int) (39);
	KerArg1->InFeatures = (unsigned short int) (2);
	KerArg1->OutFeatures = (unsigned short int) (16);
	KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+3464);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+12168);
	KerArg1->Norm = (unsigned char) (13);
	KerArg1->TotalInFeatures = (short int) (8);
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+12168);
	KerArg2->W = (unsigned short int) (20);
	KerArg2->H = (unsigned short int) (5);
	KerArg2->Norm = (unsigned char) (13);
	KerArg2->InFeatures = (unsigned short int) (16);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	_C_Out=0; _SC_Out=3200; _LC_Out=200;
	_SPP_Out=0; _SP_Out=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+3432), 32, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+3464), 2304, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Filter */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+0), 1560, 3042, 780, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+6084), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+1716), 1560, 3042, 780, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+1280+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 1560, 0, &DmaR_Evt3);
	_NN_In=6084; _SN_In=1560;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<4; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==3), T0Ind_NextLast = ((T0Ind+1)==3), T0Ind_NextNextLast = ((T0Ind+2)==3);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<4; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==3), D0Ind_NextLast = ((D0Ind+1)==3), D0Ind_NextNextLast = ((D0Ind+2)==3);
				/*================================= Prepare Tiles ===================================*/
				_SNN_In = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_In = _NN_In + (6084); _LNN_In = ((T0Ind_Last)?780:(858-78*(T0Ind==0))); _SNN_In = (2*_LNN_In); 
					} else if (!(T0Ind_Last)) {
						_NN_In = _NN_In + (780-(78*(T0Ind==0)))+(-18252); _LNN_In = ((T0Ind_NextLast)?780:858); _SNN_In = (2*_LNN_In); 
					} else if (!(1)) {
						_NN_In = _NN_In + (-2262)+(-18252); _LNN_In = (780); _SNN_In = (2*_LNN_In); 
					}
				} else if (!(T0Ind_Last)) {
					_NN_In = _NN_In + (6084); _LNN_In = ((T0Ind_NextLast)?780:858); _SNN_In = (2*_LNN_In); 
				} else if (!((1))) {
					_NN_In = _NN_In + (6084); _LNN_In = (780); _SNN_In = (2*_LNN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
				if (_SNN_In) {
					AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+1716*((D0Ind_Total)%2)),
							_SNN_In, 3042, _LNN_In, 0, &UchanHR1);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+1280+1716*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+1716*((D0Ind_Total+1)%2)),
							_SN_In, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+1716*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (11-1*(T0Ind==0)-1*(T0Ind_Last));
				KerArg1->UsedH = (unsigned short int) (11-1*(T0Ind==0)-1*(T0Ind_Last));
				KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+3464+((D0Ind)*36));
				KerArg1->Pad = (v4s) ((v4s){1,1,1*(T0Ind==0),1*(T0Ind_Last)});
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride2_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride2_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				_SN_In = _SNN_In;_LN_In = _LNN_In;
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+5768+3200*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+4712+3200*((T0Ind_Total+-1)%2)),
						_SP_Out, 800, _LP_Out, 1, &UchanHR2);
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+4712+3200*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+5768+3200*((T0Ind_Total)%2)),
					_SC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
			_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (200); _LC_Out = (200); _SC_Out = (16*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+4712+3200*((T0Ind_Total+-1)%2)), _SP_Out, 800, _LP_Out, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S27_Conv2d_16x8x1x1(
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
	AT_HYPERRAM_CL_EVENT UchanHR2;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	KerSetBias_fpd_fp_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConv_DP_fp_T S_KerArg1, *KerArg1 = &S_KerArg1;
	KerDP_fp_T S_KerArg2, *KerArg2 = &S_KerArg2;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Last;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast, T0Ind_NextNextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast, D0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	unsigned int _LPP_Out, _LP_Out, _LC_Out;
	unsigned int _NN_In;
	unsigned int _SN_In, _SNN_In;
	unsigned int _LN_In, _LNN_In;
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
		Min Pipe Depth: 0, Max Pipe Depth: 2
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
	KerArg0->NormBias = (signed char) (11);
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
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+5120+0), 3120, 3042, 390, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+468), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+5120+3120), 3120, 3042, 390, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+5120+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 3120, 0, &DmaR_Evt3);
	_NN_In=468; _SN_In=3120;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<7; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==6), T0Ind_NextLast = ((T0Ind+1)==6), T0Ind_NextNextLast = ((T0Ind+2)==6);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->H = (unsigned short int) (T0Ind_Last?2:3);
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			{ /* Single iteration on D0 */
				int D0Ind_Last = 1, D0Ind_NextLast = 1, D0Ind_NextNextLast = 1;
				/*================================= Prepare Tiles ===================================*/
				_SNN_In = 0;
				if (!(T0Ind_Last)) {
					if (!(T0Ind_NextLast)) {
						_NN_In = _NN_In + (468); _LNN_In = ((T0Ind_NextNextLast)?234:390); _SNN_In = (8*_LNN_In); 
					} else if (!(1)) {
						_NN_In = _NN_In + (-2808); _LNN_In = (390); _SNN_In = (8*_LNN_In); 
					}
				} else if (!((1))) {
					_NN_In = _NN_In + (468); _LNN_In = (390); _SNN_In = (8*_LNN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
				if (_SNN_In) {
					AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+5120+3120*((D0Ind_Total)%2)),
							_SNN_In, 3042, _LNN_In, 0, &UchanHR1);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+5120+3120*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+3120*((D0Ind_Total+1)%2)),
							_SN_In, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+3120*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (T0Ind_Last?3:5);
				KerArg1->UsedH = (unsigned short int) (T0Ind_Last?3:5);
				AT_FORK(gap_ncore(), (void *) KerParConv1x1Stride2_DP_fp, (void *) KerArg1);
				__CALL(KerParConv1x1Stride2_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				_SN_In = _SNN_In;_LN_In = _LNN_In;
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
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+1920*((T0Ind_Total+-1)%2)),
						_SP_Out, 800, _LP_Out, 1, &UchanHR2);
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+1280+1920*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+6528+1920*((T0Ind_Total)%2)),
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
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+1920*((T0Ind_Total+-1)%2)), _SP_Out, 800, _LP_Out, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S30_Conv2d_16x16x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 18560 bytes, L2 buffer: 12160 bytes */
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
		[D1 Dim: Init: 16, Tiled: 1][Tile0 Dim: 4][D0 Dim: Init: 16, Tiled: 8]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 32 logical tiles, 32 physical tiles
			Total Size: 12800 [D0, [7 x 1600, 1600]][Tile0, 4:[20x6, 2:20x7, 20x6], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 4:[20x6, 6:20x7, 20x6], 2][D0, [7 x 1600, 1600]]
		Tile0: [0, 480, 240], Tile1: [1600, 480, 240], Tile2; [3200, 480, 240]
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
		KerArgItSpace: 4 logical tiles, 4 physical tiles
			Total Size: 12800 [D1, [0 x 12800, 12800]][Tile0, 4:[20x5, 2:20x5, 20x5], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 12800, 12800]][Tile0, 4:[20x5, 2:20x5, 20x5], 2]
		Tile0: [0, 3200, 200], Tile1: [200, 3200, 200], Tile2; [400, 3200, 200]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 4 logical tiles, 1 physical tiles
			Total Size: 25600 [D1, [0 x 25600, 25600]][Tile0, 4:[20x5, 2:20x5, 20x5], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 25600, 25600]][Tile0, 4:[20x5, 2:20x5, 20x5], 4]
		Tile0: [0, 6400, 400], Tile1: [0, 6400, 400], Tile2; [0, 6400, 400]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+12160);
	KerArg0->W = (unsigned short int) (20);
	KerArg0->H = (unsigned short int) (5);
	KerArg0->OutFeatures = (unsigned short int) (16);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+1120);
	KerArg0->NormBias = (signed char) (13);
	KerArg1->W = (unsigned short int) (20);
	KerArg1->UsedW = (unsigned short int) (20);
	KerArg1->InFeatures = (unsigned short int) (2);
	KerArg1->OutFeatures = (unsigned short int) (16);
	KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+1152);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+12160);
	KerArg1->Norm = (unsigned char) (14);
	KerArg1->TotalInFeatures = (short int) (16);
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+12160);
	KerArg2->W = (unsigned short int) (20);
	KerArg2->H = (unsigned short int) (5);
	KerArg2->Norm = (unsigned char) (14);
	KerArg2->InFeatures = (unsigned short int) (16);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+0), 480, 800, 240, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+1600), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+560), 480, 800, 240, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+1280+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 480, 0, &DmaR_Evt1);
	_NN_In=1600; _SN_In=480;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+1120), 32, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+1152), 4608, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
	_C_Out=0; _SC_Out=3200; _LC_Out=200;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<4; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==3), T0Ind_NextLast = ((T0Ind+1)==3), T0Ind_NextNextLast = ((T0Ind+2)==3);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<8; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==7), D0Ind_NextLast = ((D0Ind+1)==7), D0Ind_NextNextLast = ((D0Ind+2)==7);
				/*================================= Prepare Tiles ===================================*/
				_SNN_In = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_In = _NN_In + (1600); _LNN_In = ((T0Ind_Last)?240:(280-40*(T0Ind==0))); _SNN_In = (2*_LNN_In); 
					} else if (!(T0Ind_Last)) {
						_NN_In = _NN_In + (200-(40*(T0Ind==0)))+(-11200); _LNN_In = ((T0Ind_NextLast)?240:280); _SNN_In = (2*_LNN_In); 
					} else if (!(1)) {
						_NN_In = _NN_In + (-560)+(-11200); _LNN_In = (240); _SNN_In = (2*_LNN_In); 
					}
				} else if (!(T0Ind_Last)) {
					_NN_In = _NN_In + (1600); _LNN_In = ((T0Ind_NextLast)?240:280); _SNN_In = (2*_LNN_In); 
				} else if (!((1))) {
					_NN_In = _NN_In + (1600); _LNN_In = (240); _SNN_In = (2*_LNN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
				if (_SNN_In) {
					AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+560*((D0Ind_Total)%2)),
							_SNN_In, 800, _LNN_In, 0, &UchanHR1);
				}
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+1280+560*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+560*((D0Ind_Total+1)%2)),
							_SN_In, 0, &DmaR_Evt1);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+560*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (7-1*(T0Ind==0)-1*(T0Ind_Last));
				KerArg1->UsedH = (unsigned short int) (7-1*(T0Ind==0)-1*(T0Ind_Last));
				KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+1152+((D0Ind)*36));
				KerArg1->Pad = (v4s) ((v4s){1,1,1*(T0Ind==0),1*(T0Ind_Last)});
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				_SN_In = _SNN_In;_LN_In = _LNN_In;
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+5760+3200*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+2400+3200*((T0Ind_Total+-1)%2)),
						_SP_Out, 800, _LP_Out, 1, &UchanHR2);
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+2400+3200*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+5760+3200*((T0Ind_Total)%2)),
					_SC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
			_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (200); _LC_Out = (200); _SC_Out = (16*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+2400+3200*((T0Ind_Total+-1)%2)), _SP_Out, 800, _LP_Out, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S31_MatAdd_16x20x20(
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
	AT_HYPERRAM_CL_EVENT UchanHR3;
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
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	unsigned int _LPP_Out, _LP_Out, _LC_Out;
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
		Min Pipe Depth: -2, Max Pipe Depth: 0
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
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In1+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+11520+0), 2560, 800, 160, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In1 */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In1+160), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+11520+2560), 2560, 800, 160, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+11520+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 2560, 0, &DmaR_Evt1);
	_NN_In1=160; _SN_In1=2560;
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+0), 2560, 800, 160, 0, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read In2 */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+160), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+2560), 2560, 800, 160, 0, &UchanHR2);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+1280+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+5120+0), 2560, 0, &DmaR_Evt2);
	_NN_In2=160; _SN_In2=2560;
	_C_Out=0; _SC_Out=2560; _LC_Out=160;
	_SPP_Out=0; _SP_Out=0;
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
				AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In1+_NN_In1), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+11520+2560*((T0Ind_Total)%2)),
						_SNN_In1, 800, _LNN_In1, 0, &UchanHR1);
			}
			AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In1 */
			if (_SN_In1) {
				AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+11520+2560*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+2560*((T0Ind_Total+1)%2)),
						_SN_In1, 0, &DmaR_Evt1);
			}
			AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read In2 */
			if (_SNN_In2) {
				AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+_NN_In2), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+2560*((T0Ind_Total)%2)),
						_SNN_In2, 800, _LNN_In2, 0, &UchanHR2);
			}
			AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In2 */
			if (_SN_In2) {
				AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+1280+2560*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+5120+2560*((T0Ind_Total+1)%2)),
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
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+6400+2560*((T0Ind_Total+-1)%2)),
						_SP_Out, 800, _LP_Out, 1, &UchanHR3);
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+6400+2560*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+10240+2560*((T0Ind_Total)%2)),
					_SC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SN_In1 = _SNN_In1;_LN_In1 = _LNN_In1;
			_SN_In2 = _SNN_In2;_LN_In2 = _LNN_In2;
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
	} /* End iteration on D0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+6400+2560*((T0Ind_Total+-1)%2)), _SP_Out, 800, _LP_Out, 1, &UchanHR3);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S34_Conv2d_16x16x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 18560 bytes, L2 buffer: 12160 bytes */
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
		[D1 Dim: Init: 16, Tiled: 1][Tile0 Dim: 4][D0 Dim: Init: 16, Tiled: 8]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 32 logical tiles, 32 physical tiles
			Total Size: 12800 [D0, [7 x 1600, 1600]][Tile0, 4:[20x6, 2:20x7, 20x6], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 4:[20x6, 6:20x7, 20x6], 2][D0, [7 x 1600, 1600]]
		Tile0: [0, 480, 240], Tile1: [1600, 480, 240], Tile2; [3200, 480, 240]
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
		KerArgItSpace: 4 logical tiles, 4 physical tiles
			Total Size: 12800 [D1, [0 x 12800, 12800]][Tile0, 4:[20x5, 2:20x5, 20x5], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 12800, 12800]][Tile0, 4:[20x5, 2:20x5, 20x5], 2]
		Tile0: [0, 3200, 200], Tile1: [200, 3200, 200], Tile2; [400, 3200, 200]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 4 logical tiles, 1 physical tiles
			Total Size: 25600 [D1, [0 x 25600, 25600]][Tile0, 4:[20x5, 2:20x5, 20x5], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 25600, 25600]][Tile0, 4:[20x5, 2:20x5, 20x5], 4]
		Tile0: [0, 6400, 400], Tile1: [0, 6400, 400], Tile2; [0, 6400, 400]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+12160);
	KerArg0->W = (unsigned short int) (20);
	KerArg0->H = (unsigned short int) (5);
	KerArg0->OutFeatures = (unsigned short int) (16);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+1120);
	KerArg0->NormBias = (signed char) (11);
	KerArg1->W = (unsigned short int) (20);
	KerArg1->UsedW = (unsigned short int) (20);
	KerArg1->InFeatures = (unsigned short int) (2);
	KerArg1->OutFeatures = (unsigned short int) (16);
	KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+1152);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+12160);
	KerArg1->Norm = (unsigned char) (14);
	KerArg1->TotalInFeatures = (short int) (16);
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+12160);
	KerArg2->W = (unsigned short int) (20);
	KerArg2->H = (unsigned short int) (5);
	KerArg2->Norm = (unsigned char) (14);
	KerArg2->InFeatures = (unsigned short int) (16);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+0), 480, 800, 240, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+1600), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+560), 480, 800, 240, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+1280+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 480, 0, &DmaR_Evt1);
	_NN_In=1600; _SN_In=480;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+1120), 32, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+1152), 4608, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
	_C_Out=0; _SC_Out=3200; _LC_Out=200;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<4; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==3), T0Ind_NextLast = ((T0Ind+1)==3), T0Ind_NextNextLast = ((T0Ind+2)==3);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<8; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==7), D0Ind_NextLast = ((D0Ind+1)==7), D0Ind_NextNextLast = ((D0Ind+2)==7);
				/*================================= Prepare Tiles ===================================*/
				_SNN_In = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_In = _NN_In + (1600); _LNN_In = ((T0Ind_Last)?240:(280-40*(T0Ind==0))); _SNN_In = (2*_LNN_In); 
					} else if (!(T0Ind_Last)) {
						_NN_In = _NN_In + (200-(40*(T0Ind==0)))+(-11200); _LNN_In = ((T0Ind_NextLast)?240:280); _SNN_In = (2*_LNN_In); 
					} else if (!(1)) {
						_NN_In = _NN_In + (-560)+(-11200); _LNN_In = (240); _SNN_In = (2*_LNN_In); 
					}
				} else if (!(T0Ind_Last)) {
					_NN_In = _NN_In + (1600); _LNN_In = ((T0Ind_NextLast)?240:280); _SNN_In = (2*_LNN_In); 
				} else if (!((1))) {
					_NN_In = _NN_In + (1600); _LNN_In = (240); _SNN_In = (2*_LNN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
				if (_SNN_In) {
					AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+560*((D0Ind_Total)%2)),
							_SNN_In, 800, _LNN_In, 0, &UchanHR1);
				}
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+1280+560*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+560*((D0Ind_Total+1)%2)),
							_SN_In, 0, &DmaR_Evt1);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+560*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (7-1*(T0Ind==0)-1*(T0Ind_Last));
				KerArg1->UsedH = (unsigned short int) (7-1*(T0Ind==0)-1*(T0Ind_Last));
				KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+1152+((D0Ind)*36));
				KerArg1->Pad = (v4s) ((v4s){1,1,1*(T0Ind==0),1*(T0Ind_Last)});
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				_SN_In = _SNN_In;_LN_In = _LNN_In;
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+5760+3200*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+2400+3200*((T0Ind_Total+-1)%2)),
						_SP_Out, 800, _LP_Out, 1, &UchanHR2);
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+2400+3200*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+5760+3200*((T0Ind_Total)%2)),
					_SC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
			_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (200); _LC_Out = (200); _SC_Out = (16*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+2400+3200*((T0Ind_Total+-1)%2)), _SP_Out, 800, _LP_Out, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S37_Conv2d_16x16x3x3(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 18560 bytes, L2 buffer: 12160 bytes */
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
		[D1 Dim: Init: 16, Tiled: 1][Tile0 Dim: 4][D0 Dim: Init: 16, Tiled: 8]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 32 logical tiles, 32 physical tiles
			Total Size: 12800 [D0, [7 x 1600, 1600]][Tile0, 4:[20x6, 2:20x7, 20x6], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 4:[20x6, 6:20x7, 20x6], 2][D0, [7 x 1600, 1600]]
		Tile0: [0, 480, 240], Tile1: [1600, 480, 240], Tile2; [3200, 480, 240]
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
		KerArgItSpace: 4 logical tiles, 4 physical tiles
			Total Size: 12800 [D1, [0 x 12800, 12800]][Tile0, 4:[20x5, 2:20x5, 20x5], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 12800, 12800]][Tile0, 4:[20x5, 2:20x5, 20x5], 2]
		Tile0: [0, 3200, 200], Tile1: [200, 3200, 200], Tile2; [400, 3200, 200]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 4 logical tiles, 1 physical tiles
			Total Size: 25600 [D1, [0 x 25600, 25600]][Tile0, 4:[20x5, 2:20x5, 20x5], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 25600, 25600]][Tile0, 4:[20x5, 2:20x5, 20x5], 4]
		Tile0: [0, 6400, 400], Tile1: [0, 6400, 400], Tile2; [0, 6400, 400]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+12160);
	KerArg0->W = (unsigned short int) (20);
	KerArg0->H = (unsigned short int) (5);
	KerArg0->OutFeatures = (unsigned short int) (16);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+1120);
	KerArg0->NormBias = (signed char) (13);
	KerArg1->W = (unsigned short int) (20);
	KerArg1->UsedW = (unsigned short int) (20);
	KerArg1->InFeatures = (unsigned short int) (2);
	KerArg1->OutFeatures = (unsigned short int) (16);
	KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+1152);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+12160);
	KerArg1->Norm = (unsigned char) (15);
	KerArg1->TotalInFeatures = (short int) (16);
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+12160);
	KerArg2->W = (unsigned short int) (20);
	KerArg2->H = (unsigned short int) (5);
	KerArg2->Norm = (unsigned char) (15);
	KerArg2->InFeatures = (unsigned short int) (16);
	KerArg2->LB = (int) (-32768);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+0), 480, 800, 240, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+1600), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+560), 480, 800, 240, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+1280+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 480, 0, &DmaR_Evt1);
	_NN_In=1600; _SN_In=480;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+1120), 32, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+1152), 4608, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
	_C_Out=0; _SC_Out=3200; _LC_Out=200;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<4; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==3), T0Ind_NextLast = ((T0Ind+1)==3), T0Ind_NextNextLast = ((T0Ind+2)==3);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<8; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==7), D0Ind_NextLast = ((D0Ind+1)==7), D0Ind_NextNextLast = ((D0Ind+2)==7);
				/*================================= Prepare Tiles ===================================*/
				_SNN_In = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_In = _NN_In + (1600); _LNN_In = ((T0Ind_Last)?240:(280-40*(T0Ind==0))); _SNN_In = (2*_LNN_In); 
					} else if (!(T0Ind_Last)) {
						_NN_In = _NN_In + (200-(40*(T0Ind==0)))+(-11200); _LNN_In = ((T0Ind_NextLast)?240:280); _SNN_In = (2*_LNN_In); 
					} else if (!(1)) {
						_NN_In = _NN_In + (-560)+(-11200); _LNN_In = (240); _SNN_In = (2*_LNN_In); 
					}
				} else if (!(T0Ind_Last)) {
					_NN_In = _NN_In + (1600); _LNN_In = ((T0Ind_NextLast)?240:280); _SNN_In = (2*_LNN_In); 
				} else if (!((1))) {
					_NN_In = _NN_In + (1600); _LNN_In = (240); _SNN_In = (2*_LNN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
				if (_SNN_In) {
					AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+560*((D0Ind_Total)%2)),
							_SNN_In, 800, _LNN_In, 0, &UchanHR1);
				}
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+1280+560*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+560*((D0Ind_Total+1)%2)),
							_SN_In, 0, &DmaR_Evt1);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+560*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (7-1*(T0Ind==0)-1*(T0Ind_Last));
				KerArg1->UsedH = (unsigned short int) (7-1*(T0Ind==0)-1*(T0Ind_Last));
				KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+1152+((D0Ind)*36));
				KerArg1->Pad = (v4s) ((v4s){1,1,1*(T0Ind==0),1*(T0Ind_Last)});
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				_SN_In = _SNN_In;_LN_In = _LNN_In;
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+5760+3200*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+2400+3200*((T0Ind_Total+-1)%2)),
						_SP_Out, 800, _LP_Out, 1, &UchanHR2);
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+2400+3200*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+5760+3200*((T0Ind_Total)%2)),
					_SC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
			_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (200); _LC_Out = (200); _SC_Out = (16*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+2400+3200*((T0Ind_Total+-1)%2)), _SP_Out, 800, _LP_Out, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S38_MatAdd_16x20x20(
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
	AT_HYPERRAM_CL_EVENT UchanHR3;
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
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	unsigned int _LPP_Out, _LP_Out, _LC_Out;
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
		Min Pipe Depth: -2, Max Pipe Depth: 0
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
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In1+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+11520+0), 2560, 800, 160, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In1 */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In1+160), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+11520+2560), 2560, 800, 160, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+11520+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 2560, 0, &DmaR_Evt1);
	_NN_In1=160; _SN_In1=2560;
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+0), 2560, 800, 160, 0, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read In2 */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+160), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+2560), 2560, 800, 160, 0, &UchanHR2);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+1280+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+5120+0), 2560, 0, &DmaR_Evt2);
	_NN_In2=160; _SN_In2=2560;
	_C_Out=0; _SC_Out=2560; _LC_Out=160;
	_SPP_Out=0; _SP_Out=0;
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
				AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In1+_NN_In1), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+11520+2560*((T0Ind_Total)%2)),
						_SNN_In1, 800, _LNN_In1, 0, &UchanHR1);
			}
			AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In1 */
			if (_SN_In1) {
				AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+11520+2560*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+2560*((T0Ind_Total+1)%2)),
						_SN_In1, 0, &DmaR_Evt1);
			}
			AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read In2 */
			if (_SNN_In2) {
				AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+_NN_In2), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+2560*((T0Ind_Total)%2)),
						_SNN_In2, 800, _LNN_In2, 0, &UchanHR2);
			}
			AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In2 */
			if (_SN_In2) {
				AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+1280+2560*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+5120+2560*((T0Ind_Total+1)%2)),
						_SN_In2, 0, &DmaR_Evt2);
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
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+6400+2560*((T0Ind_Total+-1)%2)),
						_SP_Out, 800, _LP_Out, 1, &UchanHR3);
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+6400+2560*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+10240+2560*((T0Ind_Total)%2)),
					_SC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SN_In1 = _SNN_In1;_LN_In1 = _LNN_In1;
			_SN_In2 = _SNN_In2;_LN_In2 = _LNN_In2;
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
	} /* End iteration on D0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+6400+2560*((T0Ind_Total+-1)%2)), _SP_Out, 800, _LP_Out, 1, &UchanHR3);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S41_Conv2d_32x16x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 18080 bytes, L2 buffer: 14240 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR2;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	KerSetBias_fpd_fp_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConv_DP_fp_T S_KerArg1, *KerArg1 = &S_KerArg1;
	KerDP_fp_T S_KerArg2, *KerArg2 = &S_KerArg2;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Last;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast, T0Ind_NextNextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast, D0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	unsigned int _LPP_Out, _LP_Out, _LC_Out;
	unsigned int _NN_In;
	unsigned int _SN_In, _SNN_In;
	unsigned int _LN_In, _LNN_In;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 32, Tiled: 1][Tile0 Dim: 4][D0 Dim: Init: 16, Tiled: 8]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
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
		KerArgItSpace: 8 logical tiles, 1 physical tiles
			Total Size: 9216 [D1, [0 x 9216, 9216]][D0, [7 x 1152, 1152]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 9216, 9216]][D0, [7 x 1152, 1152]]
		Tile0: [0, 9216, 9216], Tile1: [0, 9216, 9216], Tile2; [0, 9216, 9216]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 32 logical tiles, 32 physical tiles
			Total Size: 12800 [D0, [7 x 1600, 1600]][Tile0, 4:[20x7, 2:20x7, 20x2], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 4:[20x7, 6:20x7, 20x2], 2][D0, [7 x 1600, 1600]]
		Tile0: [0, 560, 280], Tile1: [1600, 560, 280], Tile2; [3200, 560, 280]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 4 logical tiles, 1 physical tiles
			Total Size: 12800 [D1, [0 x 12800, 12800]][Tile0, 4:[10x3, 2:10x3, 10x1], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 12800, 12800]][Tile0, 4:[10x3, 2:10x3, 10x1], 4]
		Tile0: [0, 3840, 120], Tile1: [0, 3840, 120], Tile2; [0, 3840, 120]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+14240);
	KerArg0->W = (unsigned short int) (10);
	KerArg0->OutFeatures = (unsigned short int) (32);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+1120);
	KerArg0->NormBias = (signed char) (12);
	KerArg1->W = (unsigned short int) (20);
	KerArg1->UsedW = (unsigned short int) (20);
	KerArg1->InFeatures = (unsigned short int) (2);
	KerArg1->OutFeatures = (unsigned short int) (32);
	KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+1184);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+14240);
	KerArg1->Norm = (unsigned char) (14);
	KerArg1->TotalInFeatures = (short int) (16);
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+14240);
	KerArg2->W = (unsigned short int) (10);
	KerArg2->Norm = (unsigned char) (14);
	KerArg2->InFeatures = (unsigned short int) (32);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	_C_Out=0; _SC_Out=1920; _LC_Out=60;
	_SPP_Out=0; _SP_Out=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+1120), 64, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+1184), 9216, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Filter */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+0), 560, 800, 280, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+1600), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+560), 560, 800, 280, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+1280+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 560, 0, &DmaR_Evt3);
	_NN_In=1600; _SN_In=560;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<4; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==3), T0Ind_NextLast = ((T0Ind+1)==3), T0Ind_NextNextLast = ((T0Ind+2)==3);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->H = (unsigned short int) (T0Ind_Last?1:3);
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<8; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==7), D0Ind_NextLast = ((D0Ind+1)==7), D0Ind_NextNextLast = ((D0Ind+2)==7);
				/*================================= Prepare Tiles ===================================*/
				_SNN_In = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_In = _NN_In + (1600); _LNN_In = ((T0Ind_Last)?80:(280-0*(T0Ind==0))); _SNN_In = (2*_LNN_In); 
					} else if (!(T0Ind_Last)) {
						_NN_In = _NN_In + (240)+(-11200); _LNN_In = ((T0Ind_NextLast)?80:280); _SNN_In = (2*_LNN_In); 
					} else if (!(1)) {
						_NN_In = _NN_In + (-720)+(-11200); _LNN_In = (280); _SNN_In = (2*_LNN_In); 
					}
				} else if (!(T0Ind_Last)) {
					_NN_In = _NN_In + (1600); _LNN_In = ((T0Ind_NextLast)?80:280); _SNN_In = (2*_LNN_In); 
				} else if (!((1))) {
					_NN_In = _NN_In + (1600); _LNN_In = (280); _SNN_In = (2*_LNN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
				if (_SNN_In) {
					AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+560*((D0Ind_Total)%2)),
							_SNN_In, 800, _LNN_In, 0, &UchanHR1);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+1280+560*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+560*((D0Ind_Total+1)%2)),
							_SN_In, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+560*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (((T0Ind_Last)?2:7)-0*(T0Ind==0));
				KerArg1->UsedH = (unsigned short int) (((T0Ind_Last)?2:7)-0*(T0Ind==0));
				KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+1184+((D0Ind)*36));
				KerArg1->Pad = (v4s) ((v4s){0,1,0*(T0Ind==0),1*(T0Ind_Last)});
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride2_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride2_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				_SN_In = _SNN_In;_LN_In = _LNN_In;
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->H = (unsigned short int) (T0Ind_Last?1:3);
			KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+10400+1920*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+2400+1920*((T0Ind_Total+-1)%2)),
						_SP_Out, 200, _LP_Out, 1, &UchanHR2);
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+2400+1920*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+10400+1920*((T0Ind_Total)%2)),
					_SC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
			_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
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
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+2400+1920*((T0Ind_Total+-1)%2)), _SP_Out, 200, _LP_Out, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S44_Conv2d_32x16x1x1(
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
	AT_HYPERRAM_CL_EVENT UchanHR2;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	KerSetBias_fpd_fp_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConv_DP_fp_T S_KerArg1, *KerArg1 = &S_KerArg1;
	KerDP_fp_T S_KerArg2, *KerArg2 = &S_KerArg2;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Last;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast, T0Ind_NextNextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast, D0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	unsigned int _LPP_Out, _LP_Out, _LC_Out;
	unsigned int _NN_In;
	unsigned int _SN_In, _SNN_In;
	unsigned int _LN_In, _LNN_In;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 32, Tiled: 1][Tile0 Dim: 4][D0 Dim: Init: 16, Tiled: 1]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
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
		Min Pipe Depth: 0, Max Pipe Depth: 2
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
	_SPP_Out=0; _SP_Out=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+6400), 64, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+6464), 1024, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Filter */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+5120+0), 3200, 800, 200, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+240), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+5120+3200), 3200, 800, 200, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+5120+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 3200, 0, &DmaR_Evt3);
	_NN_In=240; _SN_In=3200;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<4; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==3), T0Ind_NextLast = ((T0Ind+1)==3), T0Ind_NextNextLast = ((T0Ind+2)==3);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->H = (unsigned short int) (T0Ind_Last?1:3);
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			{ /* Single iteration on D0 */
				int D0Ind_Last = 1, D0Ind_NextLast = 1, D0Ind_NextNextLast = 1;
				/*================================= Prepare Tiles ===================================*/
				_SNN_In = 0;
				if (!(T0Ind_Last)) {
					if (!(T0Ind_NextLast)) {
						_NN_In = _NN_In + (240); _LNN_In = ((T0Ind_NextNextLast)?40:200); _SNN_In = (16*_LNN_In); 
					} else if (!(1)) {
						_NN_In = _NN_In + (-720); _LNN_In = (200); _SNN_In = (16*_LNN_In); 
					}
				} else if (!((1))) {
					_NN_In = _NN_In + (240); _LNN_In = (200); _SNN_In = (16*_LNN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
				if (_SNN_In) {
					AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+5120+3200*((D0Ind_Total)%2)),
							_SNN_In, 800, _LNN_In, 0, &UchanHR1);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+5120+3200*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+3200*((D0Ind_Total+1)%2)),
							_SN_In, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+3200*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (T0Ind_Last?1:5);
				KerArg1->UsedH = (unsigned short int) (T0Ind_Last?1:5);
				AT_FORK(gap_ncore(), (void *) KerParConv1x1Stride2_DP_fp, (void *) KerArg1);
				__CALL(KerParConv1x1Stride2_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				_SN_In = _SNN_In;_LN_In = _LNN_In;
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
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+1920*((T0Ind_Total+-1)%2)),
						_SP_Out, 200, _LP_Out, 1, &UchanHR2);
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+1280+1920*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+7488+1920*((T0Ind_Total)%2)),
					_SC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
			_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
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
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+1920*((T0Ind_Total+-1)%2)), _SP_Out, 200, _LP_Out, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S47_Conv2d_32x32x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 16768 bytes, L2 buffer: 10368 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	AT_HYPERRAM_CL_EVENT UchanHR2;
	AT_HYPERRAM_CL_EVENT UchanHR3;
	KerSetBias_fpd_fp_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConv_DP_fp_T S_KerArg1, *KerArg1 = &S_KerArg1;
	KerDP_fp_T S_KerArg2, *KerArg2 = &S_KerArg2;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Last, D1Ind_NextLast, D1Ind_NextNextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast, T0Ind_NextNextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast, D0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _NN_In;
	unsigned int _SN_In, _SNN_In;
	unsigned int _LN_In, _LNN_In;
	unsigned int _NN_Filter;
	unsigned int _SN_Filter, _SNN_Filter;
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	unsigned int _LPP_Out, _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 32, Tiled: 2][Tile0 Dim: 1][D0 Dim: Init: 32, Tiled: 8]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 8 logical tiles, 8 physical tiles
			Total Size: 6400 [D0, [7 x 800, 800]][Tile0, 1:[10x10], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[10x11, 6:10x12, 10x11], 2][D0, [7 x 800, 800]]
		Tile0: [0, 800, 200], Tile1: [800, 800, 200], Tile2; [1600, 800, 200]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 64 [D1, [1 x 32, 32]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 32, 32]]
		Tile0: [0, 64, 64], Tile1: [0, 64, 64], Tile2; [0, 64, 64]
	Ker Arg: Filter, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 16 logical tiles, 16 physical tiles
			Total Size: 18432 [D1, [1 x 9216, 9216]][D0, [7 x 1152, 1152]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 9216, 9216]][D0, [7 x 1152, 1152]]
		Tile0: [0, 1152, 1152], Tile1: [1152, 1152, 1152], Tile2; [2304, 1152, 1152]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
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
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+10368);
	KerArg0->W = (unsigned short int) (10);
	KerArg0->H = (unsigned short int) (10);
	KerArg0->OutFeatures = (unsigned short int) (16);
	KerArg0->NormBias = (signed char) (14);
	KerArg1->W = (unsigned short int) (10);
	KerArg1->UsedW = (unsigned short int) (10);
	KerArg1->InFeatures = (unsigned short int) (4);
	KerArg1->OutFeatures = (unsigned short int) (16);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+10368);
	KerArg1->Norm = (unsigned char) (14);
	KerArg1->TotalInFeatures = (short int) (4);
	KerArg1->Pad = (v4s) ((v4s){1,1,1,1});
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+10368);
	KerArg2->W = (unsigned short int) (10);
	KerArg2->H = (unsigned short int) (10);
	KerArg2->Norm = (unsigned char) (14);
	KerArg2->InFeatures = (unsigned short int) (16);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+0), 800, 200, 200, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+800), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+800), 800, 200, 200, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+1280+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 800, 0, &DmaR_Evt1);
	_NN_In=800; _SN_In=800;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+1600), 64, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Filter+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+9280+0), 1152, 0, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read Filter */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Filter+1152), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+9280+1152), 1152, 0, &UchanHR2);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+9280+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+1664+0), 1152, 0, &DmaR_Evt3);
	_NN_Filter=1152; _SN_Filter=1152;
	_C_Out=0; _SC_Out=3200; _LC_Out=200;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	for (D1Ind=0; D1Ind<2; D1Ind++) { /* Iteration on D1 */
		int D1Ind_Last = (D1Ind==1), D1Ind_NextLast = ((D1Ind+1)==1), D1Ind_NextNextLast = ((D1Ind+2)==1);
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1, T0Ind_NextLast = 1, T0Ind_NextNextLast = 1;
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+1600+((D1Ind)*32));
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<8; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==7), D0Ind_NextLast = ((D0Ind+1)==7), D0Ind_NextNextLast = ((D0Ind+2)==7);
				/*================================= Prepare Tiles ===================================*/
				_SNN_In = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_In = _NN_In + (800); _LNN_In = (200); _SNN_In = (4*_LNN_In); 
					} else if (!(D1Ind_Last)) {
						_NN_In = _NN_In + (-5600); _LNN_In = (200); _SNN_In = (4*_LNN_In); 
					}
				} else if (!((D1Ind_Last))) {
					_NN_In = _NN_In + (800); _LNN_In = (200); _SNN_In = (4*_LNN_In); 
				}
				_SNN_Filter = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_Filter = _NN_Filter + ((1152)); _SNN_Filter = (((D1Ind_Last)?(1152):(1152))); 
					} else if (!((1))) {
						_NN_Filter = _NN_Filter + ((-8064)); _SNN_Filter = (((D1Ind_Last)?(1152):(1152))); 
					} else if (!(D1Ind_Last)) {
						_NN_Filter = _NN_Filter + (9216)+((-8064)); _SNN_Filter = (((1)?(1152):(1152))); 
					}
				} else if (!((1))) {
					_NN_Filter = _NN_Filter + ((1152)); _SNN_Filter = (((D1Ind_Last)?(1152):(1152))); 
				} else if (!(D1Ind_Last)) {
					_NN_Filter = _NN_Filter + ((1152)); _SNN_Filter = (((1)?(1152):(1152))); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
				if (_SNN_In) {
					AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+800*((D0Ind_Total)%2)),
							_SNN_In, 200, _LNN_In, 0, &UchanHR1);
				}
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+1280+800*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+800*((D0Ind_Total+1)%2)),
							_SN_In, 0, &DmaR_Evt1);
				}
				AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read Filter */
				if (_SNN_Filter) {
					AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Filter+_NN_Filter), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+9280+1152*((D0Ind_Total)%2)),
							_SNN_Filter, 0, &UchanHR2);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
				if (_SN_Filter) {
					AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+9280+1152*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+1664+1152*((D0Ind_Total+1)%2)),
							_SN_Filter, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+800*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (12-1*(1)-1*(1));
				KerArg1->UsedH = (unsigned short int) (12-1*(1)-1*(1));
				KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+1664+1152*((D0Ind_Total)%2));
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				_SN_In = _SNN_In;_LN_In = _LNN_In;
				_SN_Filter = _SNN_Filter;
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+3968+3200*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+2880+3200*((T0Ind_Total+-1)%2)),
						_SP_Out, 200, _LP_Out, 1, &UchanHR3);
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+2880+3200*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+3968+3200*((T0Ind_Total)%2)),
					_SC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
			_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
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
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+2880+3200*((T0Ind_Total+-1)%2)), _SP_Out, 200, _LP_Out, 1, &UchanHR3);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S48_MatAdd_32x10x10(
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
	AT_HYPERRAM_CL_EVENT UchanHR3;
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
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	unsigned int _LPP_Out, _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D0 Dim: Init: 32, Tiled: 1][Tile0 Dim: 3]
	Ker Arg: In1, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 3 logical tiles, 3 physical tiles
			Total Size: 6400 [D0, [0 x 6400, 6400]][Tile0, 3:[10x4, 1:10x4, 10x2], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 6400, 6400]][Tile0, 3:[10x4, 1:10x4, 10x2], 2]
		Tile0: [0, 2560, 80], Tile1: [80, 2560, 80], Tile2; [160, 1280, 40]
	Ker Arg: In2, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 3 logical tiles, 3 physical tiles
			Total Size: 6400 [D0, [0 x 6400, 6400]][Tile0, 3:[10x4, 1:10x4, 10x2], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 6400, 6400]][Tile0, 3:[10x4, 1:10x4, 10x2], 2]
		Tile0: [0, 2560, 80], Tile1: [80, 2560, 80], Tile2; [160, 1280, 40]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
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
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In1+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+11520+0), 2560, 200, 80, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In1 */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In1+80), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+11520+2560), 2560, 200, 80, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+11520+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 2560, 0, &DmaR_Evt1);
	_NN_In1=80; _SN_In1=2560;
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+0), 2560, 200, 80, 0, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read In2 */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+80), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+2560), 2560, 200, 80, 0, &UchanHR2);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+1280+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+5120+0), 2560, 0, &DmaR_Evt2);
	_NN_In2=80; _SN_In2=2560;
	_C_Out=0; _SC_Out=2560; _LC_Out=80;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D0 */
		int D0Ind_Last = 1, D0Ind_NextLast = 1, D0Ind_NextNextLast = 1;
		for (T0Ind=0; T0Ind<3; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==2), T0Ind_NextLast = ((T0Ind+1)==2), T0Ind_NextNextLast = ((T0Ind+2)==2);
			/*================================= Prepare Tiles ===================================*/
			_SNN_In1 = 0;
			if (!(T0Ind_Last)) {
				if (!(T0Ind_NextLast)) {
					_NN_In1 = _NN_In1 + (80); _LNN_In1 = ((1)?40:80); _SNN_In1 = (32*_LNN_In1); 
				}
			}
			_SNN_In2 = 0;
			if (!(T0Ind_Last)) {
				if (!(T0Ind_NextLast)) {
					_NN_In2 = _NN_In2 + (80); _LNN_In2 = ((1)?40:80); _SNN_In2 = (32*_LNN_In2); 
				}
			}
			/*============================= End Prepare Tiles ===================================*/
			/*================================= Read Tiles ======================================*/
			AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In1 */
			if (_SNN_In1) {
				AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In1+_NN_In1), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+11520+2560*((T0Ind_Total)%2)),
						_SNN_In1, 200, _LNN_In1, 0, &UchanHR1);
			}
			AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In1 */
			if (_SN_In1) {
				AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+11520+2560*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+2560*((T0Ind_Total+1)%2)),
						_SN_In1, 0, &DmaR_Evt1);
			}
			AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read In2 */
			if (_SNN_In2) {
				AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+_NN_In2), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+2560*((T0Ind_Total)%2)),
						_SNN_In2, 200, _LNN_In2, 0, &UchanHR2);
			}
			AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In2 */
			if (_SN_In2) {
				AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+1280+2560*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+5120+2560*((T0Ind_Total+1)%2)),
						_SN_In2, 0, &DmaR_Evt2);
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
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+6400+2560*((T0Ind_Total+-1)%2)),
						_SP_Out, 200, _LP_Out, 1, &UchanHR3);
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+6400+2560*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+10240+2560*((T0Ind_Total)%2)),
					_SC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SN_In1 = _SNN_In1;_LN_In1 = _LNN_In1;
			_SN_In2 = _SNN_In2;_LN_In2 = _LNN_In2;
			_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
			_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
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
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+6400+2560*((T0Ind_Total+-1)%2)), _SP_Out, 200, _LP_Out, 1, &UchanHR3);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S51_Conv2d_32x32x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 16768 bytes, L2 buffer: 10368 bytes */
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
	int D1Ind, D1Ind_Last, D1Ind_NextLast, D1Ind_NextNextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast, T0Ind_NextNextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast, D0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _NN_In;
	unsigned int _SN_In, _SNN_In;
	unsigned int _LN_In, _LNN_In;
	unsigned int _NN_Filter;
	unsigned int _SN_Filter, _SNN_Filter;
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	unsigned int _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 32, Tiled: 2][Tile0 Dim: 1][D0 Dim: Init: 32, Tiled: 8]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 8 logical tiles, 8 physical tiles
			Total Size: 6400 [D0, [7 x 800, 800]][Tile0, 1:[10x10], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[10x11, 6:10x12, 10x11], 2][D0, [7 x 800, 800]]
		Tile0: [0, 800, 200], Tile1: [800, 800, 200], Tile2; [1600, 800, 200]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 64 [D1, [1 x 32, 32]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 32, 32]]
		Tile0: [0, 64, 64], Tile1: [0, 64, 64], Tile2; [0, 64, 64]
	Ker Arg: Filter, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 16 logical tiles, 16 physical tiles
			Total Size: 18432 [D1, [1 x 9216, 9216]][D0, [7 x 1152, 1152]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 9216, 9216]][D0, [7 x 1152, 1152]]
		Tile0: [0, 1152, 1152], Tile1: [1152, 1152, 1152], Tile2; [2304, 1152, 1152]
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
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+10368);
	KerArg0->W = (unsigned short int) (10);
	KerArg0->H = (unsigned short int) (10);
	KerArg0->OutFeatures = (unsigned short int) (16);
	KerArg0->NormBias = (signed char) (11);
	KerArg1->W = (unsigned short int) (10);
	KerArg1->UsedW = (unsigned short int) (10);
	KerArg1->InFeatures = (unsigned short int) (4);
	KerArg1->OutFeatures = (unsigned short int) (16);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+10368);
	KerArg1->Norm = (unsigned char) (14);
	KerArg1->TotalInFeatures = (short int) (4);
	KerArg1->Pad = (v4s) ((v4s){1,1,1,1});
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+10368);
	KerArg2->W = (unsigned short int) (10);
	KerArg2->H = (unsigned short int) (10);
	KerArg2->Norm = (unsigned char) (14);
	KerArg2->InFeatures = (unsigned short int) (16);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+0), 800, 200, 200, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+800), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+800), 800, 200, 200, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+1280+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 800, 0, &DmaR_Evt1);
	_NN_In=800; _SN_In=800;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+1600), 64, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Filter+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+9280+0), 1152, 0, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read Filter */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Filter+1152), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+9280+1152), 1152, 0, &UchanHR2);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+9280+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+1664+0), 1152, 0, &DmaR_Evt3);
	_NN_Filter=1152; _SN_Filter=1152;
	_C_Out=0; _SC_Out=3200; _LC_Out=200;
	_SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	for (D1Ind=0; D1Ind<2; D1Ind++) { /* Iteration on D1 */
		int D1Ind_Last = (D1Ind==1), D1Ind_NextLast = ((D1Ind+1)==1), D1Ind_NextNextLast = ((D1Ind+2)==1);
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1, T0Ind_NextLast = 1, T0Ind_NextNextLast = 1;
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+1600+((D1Ind)*32));
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<8; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==7), D0Ind_NextLast = ((D0Ind+1)==7), D0Ind_NextNextLast = ((D0Ind+2)==7);
				/*================================= Prepare Tiles ===================================*/
				_SNN_In = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_In = _NN_In + (800); _LNN_In = (200); _SNN_In = (4*_LNN_In); 
					} else if (!(D1Ind_Last)) {
						_NN_In = _NN_In + (-5600); _LNN_In = (200); _SNN_In = (4*_LNN_In); 
					}
				} else if (!((D1Ind_Last))) {
					_NN_In = _NN_In + (800); _LNN_In = (200); _SNN_In = (4*_LNN_In); 
				}
				_SNN_Filter = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_Filter = _NN_Filter + ((1152)); _SNN_Filter = (((D1Ind_Last)?(1152):(1152))); 
					} else if (!((1))) {
						_NN_Filter = _NN_Filter + ((-8064)); _SNN_Filter = (((D1Ind_Last)?(1152):(1152))); 
					} else if (!(D1Ind_Last)) {
						_NN_Filter = _NN_Filter + (9216)+((-8064)); _SNN_Filter = (((1)?(1152):(1152))); 
					}
				} else if (!((1))) {
					_NN_Filter = _NN_Filter + ((1152)); _SNN_Filter = (((D1Ind_Last)?(1152):(1152))); 
				} else if (!(D1Ind_Last)) {
					_NN_Filter = _NN_Filter + ((1152)); _SNN_Filter = (((1)?(1152):(1152))); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
				if (_SNN_In) {
					AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+800*((D0Ind_Total)%2)),
							_SNN_In, 200, _LNN_In, 0, &UchanHR1);
				}
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+1280+800*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+800*((D0Ind_Total+1)%2)),
							_SN_In, 0, &DmaR_Evt1);
				}
				AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read Filter */
				if (_SNN_Filter) {
					AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Filter+_NN_Filter), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+9280+1152*((D0Ind_Total)%2)),
							_SNN_Filter, 0, &UchanHR2);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
				if (_SN_Filter) {
					AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+9280+1152*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+1664+1152*((D0Ind_Total+1)%2)),
							_SN_Filter, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+800*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (12-1*(1)-1*(1));
				KerArg1->UsedH = (unsigned short int) (12-1*(1)-1*(1));
				KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+1664+1152*((D0Ind_Total)%2));
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				_SN_In = _SNN_In;_LN_In = _LNN_In;
				_SN_Filter = _SNN_Filter;
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+3968+3200*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+3968+3200*((T0Ind_Total)%2)),
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
void S54_Conv2d_32x32x3x3(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 16768 bytes, L2 buffer: 10368 bytes */
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
	int D1Ind, D1Ind_Last, D1Ind_NextLast, D1Ind_NextNextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast, D0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _N_In;
	unsigned int _SN_In;
	unsigned int _LN_In;
	unsigned int _NN_Filter;
	unsigned int _SN_Filter, _SNN_Filter;
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	unsigned int _LPP_Out, _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 32, Tiled: 2][Tile0 Dim: 1][D0 Dim: Init: 32, Tiled: 8]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 8 logical tiles, 8 physical tiles
			Total Size: 6400 [D0, [7 x 800, 800]][Tile0, 1:[10x10], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[10x11, 6:10x12, 10x11], 2][D0, [7 x 800, 800]]
		Tile0: [0, 800, 200], Tile1: [800, 800, 200], Tile2; [1600, 800, 200]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 64 [D1, [1 x 32, 32]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 32, 32]]
		Tile0: [0, 64, 64], Tile1: [0, 64, 64], Tile2; [0, 64, 64]
	Ker Arg: Filter, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 16 logical tiles, 16 physical tiles
			Total Size: 18432 [D1, [1 x 9216, 9216]][D0, [7 x 1152, 1152]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 9216, 9216]][D0, [7 x 1152, 1152]]
		Tile0: [0, 1152, 1152], Tile1: [1152, 1152, 1152], Tile2; [2304, 1152, 1152]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
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
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+10368);
	KerArg0->W = (unsigned short int) (10);
	KerArg0->H = (unsigned short int) (10);
	KerArg0->OutFeatures = (unsigned short int) (16);
	KerArg0->NormBias = (signed char) (13);
	KerArg1->W = (unsigned short int) (10);
	KerArg1->UsedW = (unsigned short int) (10);
	KerArg1->InFeatures = (unsigned short int) (4);
	KerArg1->OutFeatures = (unsigned short int) (16);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+10368);
	KerArg1->Norm = (unsigned char) (15);
	KerArg1->TotalInFeatures = (short int) (4);
	KerArg1->Pad = (v4s) ((v4s){1,1,1,1});
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+10368);
	KerArg2->W = (unsigned short int) (10);
	KerArg2->H = (unsigned short int) (10);
	KerArg2->Norm = (unsigned char) (15);
	KerArg2->InFeatures = (unsigned short int) (16);
	KerArg2->LB = (int) (-32768);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 800, 200, 200, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+1600), 64, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Filter+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+15680+0), 1152, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read Filter */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Filter+1152), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+15680+1152), 1152, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+15680+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+1664+0), 1152, 0, &DmaR_Evt3);
	_NN_Filter=1152; _SN_Filter=1152;
	_C_Out=0; _SC_Out=3200; _LC_Out=200;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	for (D1Ind=0; D1Ind<2; D1Ind++) { /* Iteration on D1 */
		int D1Ind_Last = (D1Ind==1), D1Ind_NextLast = ((D1Ind+1)==1), D1Ind_NextNextLast = ((D1Ind+2)==1);
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1, T0Ind_NextLast = 1;
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+1600+((D1Ind)*32));
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<8; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==7), D0Ind_NextLast = ((D0Ind+1)==7), D0Ind_NextNextLast = ((D0Ind+2)==7);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (800); _LN_In = (200); _SN_In = (4*_LN_In); 
				} else if (!(D1Ind_Last)) {
					_N_In = _N_In + (-5600); _LN_In = (200); _SN_In = (4*_LN_In); 
				}
				_SNN_Filter = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_Filter = _NN_Filter + ((1152)); _SNN_Filter = (((D1Ind_Last)?(1152):(1152))); 
					} else if (!((1))) {
						_NN_Filter = _NN_Filter + ((-8064)); _SNN_Filter = (((D1Ind_Last)?(1152):(1152))); 
					} else if (!(D1Ind_Last)) {
						_NN_Filter = _NN_Filter + (9216)+((-8064)); _SNN_Filter = (((1)?(1152):(1152))); 
					}
				} else if (!((1))) {
					_NN_Filter = _NN_Filter + ((1152)); _SNN_Filter = (((D1Ind_Last)?(1152):(1152))); 
				} else if (!(D1Ind_Last)) {
					_NN_Filter = _NN_Filter + ((1152)); _SNN_Filter = (((1)?(1152):(1152))); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+800*((D0Ind_Total+1)%2)),
							_SN_In, 200, _LN_In, 0, &DmaR_Evt1);
				}
				AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read Filter */
				if (_SNN_Filter) {
					AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Filter+_NN_Filter), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+15680+1152*((D0Ind_Total)%2)),
							_SNN_Filter, 0, &UchanHR1);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
				if (_SN_Filter) {
					AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+15680+1152*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+1664+1152*((D0Ind_Total+1)%2)),
							_SN_Filter, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+800*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (12-1*(1)-1*(1));
				KerArg1->UsedH = (unsigned short int) (12-1*(1)-1*(1));
				KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+1664+1152*((D0Ind_Total)%2));
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				_SN_Filter = _SNN_Filter;
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+3968+3200*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+9280+3200*((T0Ind_Total+-1)%2)),
						_SP_Out, 200, _LP_Out, 1, &UchanHR2);
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+9280+3200*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+3968+3200*((T0Ind_Total)%2)),
					_SC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
			_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
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
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+9280+3200*((T0Ind_Total+-1)%2)), _SP_Out, 200, _LP_Out, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S55_MatAdd_32x10x10(
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
	AT_HYPERRAM_CL_EVENT UchanHR3;
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
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	unsigned int _LPP_Out, _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D0 Dim: Init: 32, Tiled: 1][Tile0 Dim: 3]
	Ker Arg: In1, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 3 logical tiles, 3 physical tiles
			Total Size: 6400 [D0, [0 x 6400, 6400]][Tile0, 3:[10x4, 1:10x4, 10x2], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 6400, 6400]][Tile0, 3:[10x4, 1:10x4, 10x2], 2]
		Tile0: [0, 2560, 80], Tile1: [80, 2560, 80], Tile2; [160, 1280, 40]
	Ker Arg: In2, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 3 logical tiles, 3 physical tiles
			Total Size: 6400 [D0, [0 x 6400, 6400]][Tile0, 3:[10x4, 1:10x4, 10x2], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 6400, 6400]][Tile0, 3:[10x4, 1:10x4, 10x2], 2]
		Tile0: [0, 2560, 80], Tile1: [80, 2560, 80], Tile2; [160, 1280, 40]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
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
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In1+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+11520+0), 2560, 200, 80, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In1 */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In1+80), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+11520+2560), 2560, 200, 80, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+11520+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 2560, 0, &DmaR_Evt1);
	_NN_In1=80; _SN_In1=2560;
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+6400+0), 2560, 200, 80, 0, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read In2 */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+80), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+6400+2560), 2560, 200, 80, 0, &UchanHR2);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+6400+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+5120+0), 2560, 0, &DmaR_Evt2);
	_NN_In2=80; _SN_In2=2560;
	_C_Out=0; _SC_Out=2560; _LC_Out=80;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D0 */
		int D0Ind_Last = 1, D0Ind_NextLast = 1, D0Ind_NextNextLast = 1;
		for (T0Ind=0; T0Ind<3; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==2), T0Ind_NextLast = ((T0Ind+1)==2), T0Ind_NextNextLast = ((T0Ind+2)==2);
			/*================================= Prepare Tiles ===================================*/
			_SNN_In1 = 0;
			if (!(T0Ind_Last)) {
				if (!(T0Ind_NextLast)) {
					_NN_In1 = _NN_In1 + (80); _LNN_In1 = ((1)?40:80); _SNN_In1 = (32*_LNN_In1); 
				}
			}
			_SNN_In2 = 0;
			if (!(T0Ind_Last)) {
				if (!(T0Ind_NextLast)) {
					_NN_In2 = _NN_In2 + (80); _LNN_In2 = ((1)?40:80); _SNN_In2 = (32*_LNN_In2); 
				}
			}
			/*============================= End Prepare Tiles ===================================*/
			/*================================= Read Tiles ======================================*/
			AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In1 */
			if (_SNN_In1) {
				AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In1+_NN_In1), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+11520+2560*((T0Ind_Total)%2)),
						_SNN_In1, 200, _LNN_In1, 0, &UchanHR1);
			}
			AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In1 */
			if (_SN_In1) {
				AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+11520+2560*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+2560*((T0Ind_Total+1)%2)),
						_SN_In1, 0, &DmaR_Evt1);
			}
			AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read In2 */
			if (_SNN_In2) {
				AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+_NN_In2), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+6400+2560*((T0Ind_Total)%2)),
						_SNN_In2, 200, _LNN_In2, 0, &UchanHR2);
			}
			AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In2 */
			if (_SN_In2) {
				AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+6400+2560*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+5120+2560*((T0Ind_Total+1)%2)),
						_SN_In2, 0, &DmaR_Evt2);
			}
			/*============================= End Read Tiles ======================================*/
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In1 = (short int *__restrict__) (resnet_L1_Memory+0+2560*((T0Ind_Total)%2));
			KerArg0->In2 = (short int *__restrict__) (resnet_L1_Memory+5120+2560*((T0Ind_Total)%2));
			KerArg0->Out = (short int *__restrict__) (resnet_L1_Memory+10240+2560*((T0Ind_Total)%2));
			KerArg0->H = (unsigned short int) (T0Ind_Last?2:4);
			AT_FORK(gap_ncore(), (void *) KerParMatAdd_fp, (void *) KerArg0);
			__CALL(KerParMatAdd_fp, KerArg0);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+2560*((T0Ind_Total+-1)%2)),
						_SP_Out, 200, _LP_Out, 1, &UchanHR3);
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+1280+2560*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+10240+2560*((T0Ind_Total)%2)),
					_SC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SN_In1 = _SNN_In1;_LN_In1 = _LNN_In1;
			_SN_In2 = _SNN_In2;_LN_In2 = _LNN_In2;
			_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
			_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
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
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+2560*((T0Ind_Total+-1)%2)), _SP_Out, 200, _LP_Out, 1, &UchanHR3);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S58_Conv2d_64x32x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 15136 bytes, L2 buffer: 8736 bytes */
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
	int D1Ind, D1Ind_Last, D1Ind_NextLast, D1Ind_NextNextLast;
	int T0Ind, T0Ind_Last, T0Ind_NextLast, T0Ind_NextNextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast, D0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _NN_Filter;
	unsigned int _SN_Filter, _SNN_Filter;
	unsigned int _NN_In;
	unsigned int _SN_In, _SNN_In;
	unsigned int _LN_In, _LNN_In;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 64, Tiled: 1][Tile0 Dim: 1][D0 Dim: Init: 32, Tiled: 16]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 6400 [D1, [0 x 6400, 6400]][Tile0, 1:[5x5], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 6400, 6400]][Tile0, 1:[5x5], 4]
		Tile0: [0, 6400, 100], Tile1: [0, 6400, 100], Tile2; [0, 6400, 100]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 128 [D1, [0 x 128, 128]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 128, 128]]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Filter, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 16 logical tiles, 16 physical tiles
			Total Size: 36864 [D1, [0 x 36864, 36864]][D0, [15 x 2304, 2304]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 36864, 36864]][D0, [15 x 2304, 2304]]
		Tile0: [0, 2304, 2304], Tile1: [2304, 2304, 2304], Tile2; [4608, 2304, 2304]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 3200 [D1, [0 x 3200, 3200]][Tile0, 1:[5x5], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 3200, 3200]][Tile0, 1:[5x5], 2]
		Tile0: [0, 3200, 3200], Tile1: [0, 3200, 3200], Tile2; [0, 3200, 3200]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 16 logical tiles, 16 physical tiles
			Total Size: 6400 [D0, [15 x 400, 400]][Tile0, 1:[10x10], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[10x11, 14:10x11, 10x10], 2][D0, [15 x 400, 400]]
		Tile0: [0, 400, 200], Tile1: [400, 400, 200], Tile2; [800, 400, 200]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+8736);
	KerArg0->W = (unsigned short int) (5);
	KerArg0->H = (unsigned short int) (5);
	KerArg0->OutFeatures = (unsigned short int) (64);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+800);
	KerArg0->NormBias = (signed char) (11);
	KerArg1->W = (unsigned short int) (10);
	KerArg1->UsedW = (unsigned short int) (10);
	KerArg1->InFeatures = (unsigned short int) (2);
	KerArg1->OutFeatures = (unsigned short int) (64);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+8736);
	KerArg1->Norm = (unsigned char) (14);
	KerArg1->TotalInFeatures = (short int) (2);
	KerArg1->Pad = (v4s) ((v4s){0,1,0,1});
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+8736);
	KerArg2->W = (unsigned short int) (5);
	KerArg2->H = (unsigned short int) (5);
	KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+5536);
	KerArg2->Norm = (unsigned char) (14);
	KerArg2->InFeatures = (unsigned short int) (64);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+800), 128, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Bias */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Filter+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+5280+0), 2304, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read Filter */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Filter+2304), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+5280+2304), 2304, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+5280+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+928+0), 2304, 0, &DmaR_Evt2);
	_NN_Filter=2304; _SN_Filter=2304;
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+0), 400, 200, 200, 0, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+400), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+400), 400, 200, 200, 0, &UchanHR2);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+1280+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 400, 0, &DmaR_Evt3);
	_NN_In=400; _SN_In=400;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1, D1Ind_NextLast = 1, D1Ind_NextNextLast = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1, T0Ind_NextLast = 1, T0Ind_NextNextLast = 1;
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<16; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==15), D0Ind_NextLast = ((D0Ind+1)==15), D0Ind_NextNextLast = ((D0Ind+2)==15);
				/*================================= Prepare Tiles ===================================*/
				_SNN_Filter = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_Filter = _NN_Filter + ((2304)); _SNN_Filter = (((1)?(2304):(2304))); 
					} else if (!((1))) {
						_NN_Filter = _NN_Filter + ((-34560)); _SNN_Filter = (((1)?(2304):(2304))); 
					}
				} else if (!((1))) {
					_NN_Filter = _NN_Filter + ((2304)); _SNN_Filter = (((1)?(2304):(2304))); 
				}
				_SNN_In = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_In = _NN_In + (400); _LNN_In = (200); _SNN_In = (2*_LNN_In); 
					} else if (!(1)) {
						_NN_In = _NN_In + (-6000); _LNN_In = (200); _SNN_In = (2*_LNN_In); 
					}
				} else if (!((1))) {
					_NN_In = _NN_In + (400); _LNN_In = (200); _SNN_In = (2*_LNN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read Filter */
				if (_SNN_Filter) {
					AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Filter+_NN_Filter), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+5280+2304*((D0Ind_Total)%2)),
							_SNN_Filter, 0, &UchanHR1);
				}
				AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Filter */
				if (_SN_Filter) {
					AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+5280+2304*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+928+2304*((D0Ind_Total+1)%2)),
							_SN_Filter, 0, &DmaR_Evt2);
				}
				AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read In */
				if (_SNN_In) {
					AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+400*((D0Ind_Total)%2)),
							_SNN_In, 200, _LNN_In, 0, &UchanHR2);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+1280+400*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+400*((D0Ind_Total+1)%2)),
							_SN_In, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+400*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (11-0*(1)-1*(1));
				KerArg1->UsedH = (unsigned short int) (11-0*(1)-1*(1));
				KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+928+2304*((D0Ind_Total)%2));
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride2_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride2_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				_SN_Filter = _SNN_Filter;
				_SN_In = _SNN_In;_LN_In = _LNN_In;
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+5536), 3200, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S61_Conv2d_64x32x1x1(
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
	AT_HYPERRAM_CL_EVENT UchanHR1;
	KerSetBias_fpd_fp_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConv_DP_fp_T S_KerArg1, *KerArg1 = &S_KerArg1;
	KerDP_fp_T S_KerArg2, *KerArg2 = &S_KerArg2;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Last;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast, T0Ind_NextNextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast, D0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	unsigned int _LP_Out, _LC_Out;
	unsigned int _NN_In;
	unsigned int _SN_In, _SNN_In;
	unsigned int _LN_In, _LNN_In;
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
		Min Pipe Depth: 0, Max Pipe Depth: 2
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
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+0), 1920, 200, 60, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+80), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+1920), 1920, 200, 60, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+1280+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 1920, 0, &DmaR_Evt3);
	_NN_In=80; _SN_In=1920;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<3; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==2), T0Ind_NextLast = ((T0Ind+1)==2), T0Ind_NextNextLast = ((T0Ind+2)==2);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->H = (unsigned short int) (T0Ind_Last?1:2);
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			{ /* Single iteration on D0 */
				int D0Ind_Last = 1, D0Ind_NextLast = 1, D0Ind_NextNextLast = 1;
				/*================================= Prepare Tiles ===================================*/
				_SNN_In = 0;
				if (!(T0Ind_Last)) {
					if (!(T0Ind_NextLast)) {
						_NN_In = _NN_In + (80); _LNN_In = ((1)?20:60); _SNN_In = (32*_LNN_In); 
					} else if (!(1)) {
						_NN_In = _NN_In + (-160); _LNN_In = (60); _SNN_In = (32*_LNN_In); 
					}
				} else if (!((1))) {
					_NN_In = _NN_In + (80); _LNN_In = (60); _SNN_In = (32*_LNN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
				if (_SNN_In) {
					AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+1920*((D0Ind_Total)%2)),
							_SNN_In, 200, _LNN_In, 0, &UchanHR1);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+1280+1920*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+1920*((D0Ind_Total+1)%2)),
							_SN_In, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+1920*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (T0Ind_Last?1:3);
				KerArg1->UsedH = (unsigned short int) (T0Ind_Last?1:3);
				AT_FORK(gap_ncore(), (void *) KerParConv1x1Stride2_DP_fp, (void *) KerArg1);
				__CALL(KerParConv1x1Stride2_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				_SN_In = _SNN_In;_LN_In = _LNN_In;
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
void S64_Conv2d_64x64x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 14536 bytes, L2 buffer: 8136 bytes */
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
	int D1Ind, D1Ind_Last, D1Ind_NextLast, D1Ind_NextNextLast;
	int T0Ind, T0Ind_Last, T0Ind_NextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast, D0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _N_In;
	unsigned int _SN_In;
	unsigned int _LN_In;
	unsigned int _NN_Filter;
	unsigned int _SN_Filter, _SNN_Filter;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 64, Tiled: 1][Tile0 Dim: 1][D0 Dim: Init: 64, Tiled: 32]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 32 logical tiles, 32 physical tiles
			Total Size: 3200 [D0, [31 x 100, 100]][Tile0, 1:[5x5], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[5x6, 30:5x7, 5x6], 2][D0, [31 x 100, 100]]
		Tile0: [0, 100, 50], Tile1: [100, 100, 50], Tile2; [200, 100, 50]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 128 [D1, [0 x 128, 128]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 128, 128]]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Filter, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 32 logical tiles, 32 physical tiles
			Total Size: 73728 [D1, [0 x 73728, 73728]][D0, [31 x 2304, 2304]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 73728, 73728]][D0, [31 x 2304, 2304]]
		Tile0: [0, 2304, 2304], Tile1: [2304, 2304, 2304], Tile2; [4608, 2304, 2304]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 3200 [D1, [0 x 3200, 3200]][Tile0, 1:[5x5], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 3200, 3200]][Tile0, 1:[5x5], 2]
		Tile0: [0, 3200, 3200], Tile1: [0, 3200, 3200], Tile2; [0, 3200, 3200]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 6400 [D1, [0 x 6400, 6400]][Tile0, 1:[5x5], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 6400, 6400]][Tile0, 1:[5x5], 4]
		Tile0: [0, 6400, 100], Tile1: [0, 6400, 100], Tile2; [0, 6400, 100]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+8136);
	KerArg0->W = (unsigned short int) (5);
	KerArg0->H = (unsigned short int) (5);
	KerArg0->OutFeatures = (unsigned short int) (64);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+200);
	KerArg0->NormBias = (signed char) (13);
	KerArg1->W = (unsigned short int) (5);
	KerArg1->UsedW = (unsigned short int) (5);
	KerArg1->InFeatures = (unsigned short int) (2);
	KerArg1->OutFeatures = (unsigned short int) (64);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+8136);
	KerArg1->Norm = (unsigned char) (13);
	KerArg1->TotalInFeatures = (short int) (2);
	KerArg1->Pad = (v4s) ((v4s){1,1,1,1});
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+8136);
	KerArg2->W = (unsigned short int) (5);
	KerArg2->H = (unsigned short int) (5);
	KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+4936);
	KerArg2->Norm = (unsigned char) (13);
	KerArg2->InFeatures = (unsigned short int) (64);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 100, 50, 50, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+200), 128, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Filter+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+8480+0), 2304, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read Filter */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Filter+2304), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+8480+2304), 2304, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+8480+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+328+0), 2304, 0, &DmaR_Evt3);
	_NN_Filter=2304; _SN_Filter=2304;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1, D1Ind_NextLast = 1, D1Ind_NextNextLast = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1, T0Ind_NextLast = 1;
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<32; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==31), D0Ind_NextLast = ((D0Ind+1)==31), D0Ind_NextNextLast = ((D0Ind+2)==31);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (100); _LN_In = (50); _SN_In = (2*_LN_In); 
				} else if (!(1)) {
					_N_In = _N_In + (-3100); _LN_In = (50); _SN_In = (2*_LN_In); 
				}
				_SNN_Filter = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_Filter = _NN_Filter + ((2304)); _SNN_Filter = (((1)?(2304):(2304))); 
					} else if (!((1))) {
						_NN_Filter = _NN_Filter + ((-71424)); _SNN_Filter = (((1)?(2304):(2304))); 
					}
				} else if (!((1))) {
					_NN_Filter = _NN_Filter + ((2304)); _SNN_Filter = (((1)?(2304):(2304))); 
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
					AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Filter+_NN_Filter), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+8480+2304*((D0Ind_Total)%2)),
							_SNN_Filter, 0, &UchanHR1);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
				if (_SN_Filter) {
					AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+8480+2304*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+328+2304*((D0Ind_Total+1)%2)),
							_SN_Filter, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+100*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (7-1*(1)-1*(1));
				KerArg1->UsedH = (unsigned short int) (7-1*(1)-1*(1));
				KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+328+2304*((D0Ind_Total)%2));
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				_SN_Filter = _SNN_Filter;
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+5280+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+4936), 3200, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+5280+0), 3200, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S65_MatAdd_64x5x5(
		short int * __restrict__ In1,
		short int * __restrict__ In2,
		short int * __restrict__ Out)

{
	/* Shared L1: 9600 bytes, L2 buffer: 9600 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
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
	KerArg0->In2_Q = (unsigned char) (13);
	KerArg0->Out_Q = (unsigned char) (12);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In1+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+1280+0), 3200, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In1 */
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+1280+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0), 3200, 0, &DmaR_Evt1);
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
void S68_Conv2d_64x64x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 14536 bytes, L2 buffer: 8136 bytes */
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
	int T0Ind, T0Ind_Last, T0Ind_NextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast, D0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _N_In;
	unsigned int _SN_In;
	unsigned int _LN_In;
	unsigned int _NN_Filter;
	unsigned int _SN_Filter, _SNN_Filter;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 64, Tiled: 1][Tile0 Dim: 1][D0 Dim: Init: 64, Tiled: 32]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 32 logical tiles, 32 physical tiles
			Total Size: 3200 [D0, [31 x 100, 100]][Tile0, 1:[5x5], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[5x6, 30:5x7, 5x6], 2][D0, [31 x 100, 100]]
		Tile0: [0, 100, 50], Tile1: [100, 100, 50], Tile2; [200, 100, 50]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 128 [D1, [0 x 128, 128]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 128, 128]]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Filter, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 32 logical tiles, 32 physical tiles
			Total Size: 73728 [D1, [0 x 73728, 73728]][D0, [31 x 2304, 2304]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 73728, 73728]][D0, [31 x 2304, 2304]]
		Tile0: [0, 2304, 2304], Tile1: [2304, 2304, 2304], Tile2; [4608, 2304, 2304]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 3200 [D1, [0 x 3200, 3200]][Tile0, 1:[5x5], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 3200, 3200]][Tile0, 1:[5x5], 2]
		Tile0: [0, 3200, 3200], Tile1: [0, 3200, 3200], Tile2; [0, 3200, 3200]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 6400 [D1, [0 x 6400, 6400]][Tile0, 1:[5x5], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 6400, 6400]][Tile0, 1:[5x5], 4]
		Tile0: [0, 6400, 100], Tile1: [0, 6400, 100], Tile2; [0, 6400, 100]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+8136);
	KerArg0->W = (unsigned short int) (5);
	KerArg0->H = (unsigned short int) (5);
	KerArg0->OutFeatures = (unsigned short int) (64);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+200);
	KerArg0->NormBias = (signed char) (12);
	KerArg1->W = (unsigned short int) (5);
	KerArg1->UsedW = (unsigned short int) (5);
	KerArg1->InFeatures = (unsigned short int) (2);
	KerArg1->OutFeatures = (unsigned short int) (64);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+8136);
	KerArg1->Norm = (unsigned char) (14);
	KerArg1->TotalInFeatures = (short int) (2);
	KerArg1->Pad = (v4s) ((v4s){1,1,1,1});
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+8136);
	KerArg2->W = (unsigned short int) (5);
	KerArg2->H = (unsigned short int) (5);
	KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+4936);
	KerArg2->Norm = (unsigned char) (14);
	KerArg2->InFeatures = (unsigned short int) (64);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 100, 50, 50, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+200), 128, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Filter+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+11520+0), 2304, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read Filter */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Filter+2304), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+11520+2304), 2304, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+11520+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+328+0), 2304, 0, &DmaR_Evt3);
	_NN_Filter=2304; _SN_Filter=2304;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1, D1Ind_NextLast = 1, D1Ind_NextNextLast = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1, T0Ind_NextLast = 1;
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<32; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==31), D0Ind_NextLast = ((D0Ind+1)==31), D0Ind_NextNextLast = ((D0Ind+2)==31);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (100); _LN_In = (50); _SN_In = (2*_LN_In); 
				} else if (!(1)) {
					_N_In = _N_In + (-3100); _LN_In = (50); _SN_In = (2*_LN_In); 
				}
				_SNN_Filter = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_Filter = _NN_Filter + ((2304)); _SNN_Filter = (((1)?(2304):(2304))); 
					} else if (!((1))) {
						_NN_Filter = _NN_Filter + ((-71424)); _SNN_Filter = (((1)?(2304):(2304))); 
					}
				} else if (!((1))) {
					_NN_Filter = _NN_Filter + ((2304)); _SNN_Filter = (((1)?(2304):(2304))); 
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
					AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Filter+_NN_Filter), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+11520+2304*((D0Ind_Total)%2)),
							_SNN_Filter, 0, &UchanHR1);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
				if (_SN_Filter) {
					AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+11520+2304*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+328+2304*((D0Ind_Total+1)%2)),
							_SN_Filter, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+100*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (7-1*(1)-1*(1));
				KerArg1->UsedH = (unsigned short int) (7-1*(1)-1*(1));
				KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+328+2304*((D0Ind_Total)%2));
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				_SN_Filter = _SNN_Filter;
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+4936), 3200, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S71_Conv2d_64x64x3x3(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 14536 bytes, L2 buffer: 8136 bytes */
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
	int T0Ind, T0Ind_Last, T0Ind_NextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast, D0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _N_In;
	unsigned int _SN_In;
	unsigned int _LN_In;
	unsigned int _NN_Filter;
	unsigned int _SN_Filter, _SNN_Filter;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 64, Tiled: 1][Tile0 Dim: 1][D0 Dim: Init: 64, Tiled: 32]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 32 logical tiles, 32 physical tiles
			Total Size: 3200 [D0, [31 x 100, 100]][Tile0, 1:[5x5], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[5x6, 30:5x7, 5x6], 2][D0, [31 x 100, 100]]
		Tile0: [0, 100, 50], Tile1: [100, 100, 50], Tile2; [200, 100, 50]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 128 [D1, [0 x 128, 128]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 128, 128]]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Filter, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 32 logical tiles, 32 physical tiles
			Total Size: 73728 [D1, [0 x 73728, 73728]][D0, [31 x 2304, 2304]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 73728, 73728]][D0, [31 x 2304, 2304]]
		Tile0: [0, 2304, 2304], Tile1: [2304, 2304, 2304], Tile2; [4608, 2304, 2304]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 3200 [D1, [0 x 3200, 3200]][Tile0, 1:[5x5], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 3200, 3200]][Tile0, 1:[5x5], 2]
		Tile0: [0, 3200, 3200], Tile1: [0, 3200, 3200], Tile2; [0, 3200, 3200]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 6400 [D1, [0 x 6400, 6400]][Tile0, 1:[5x5], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 6400, 6400]][Tile0, 1:[5x5], 4]
		Tile0: [0, 6400, 100], Tile1: [0, 6400, 100], Tile2; [0, 6400, 100]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+8136);
	KerArg0->W = (unsigned short int) (5);
	KerArg0->H = (unsigned short int) (5);
	KerArg0->OutFeatures = (unsigned short int) (64);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+200);
	KerArg0->NormBias = (signed char) (12);
	KerArg1->W = (unsigned short int) (5);
	KerArg1->UsedW = (unsigned short int) (5);
	KerArg1->InFeatures = (unsigned short int) (2);
	KerArg1->OutFeatures = (unsigned short int) (64);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+8136);
	KerArg1->Norm = (unsigned char) (15);
	KerArg1->TotalInFeatures = (short int) (2);
	KerArg1->Pad = (v4s) ((v4s){1,1,1,1});
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+8136);
	KerArg2->W = (unsigned short int) (5);
	KerArg2->H = (unsigned short int) (5);
	KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+4936);
	KerArg2->Norm = (unsigned char) (15);
	KerArg2->InFeatures = (unsigned short int) (64);
	KerArg2->LB = (int) (-32768);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 100, 50, 50, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+200), 128, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Filter+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+11520+0), 2304, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read Filter */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Filter+2304), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+11520+2304), 2304, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+11520+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+328+0), 2304, 0, &DmaR_Evt3);
	_NN_Filter=2304; _SN_Filter=2304;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1, D1Ind_NextLast = 1, D1Ind_NextNextLast = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1, T0Ind_NextLast = 1;
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<32; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==31), D0Ind_NextLast = ((D0Ind+1)==31), D0Ind_NextNextLast = ((D0Ind+2)==31);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (100); _LN_In = (50); _SN_In = (2*_LN_In); 
				} else if (!(1)) {
					_N_In = _N_In + (-3100); _LN_In = (50); _SN_In = (2*_LN_In); 
				}
				_SNN_Filter = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_Filter = _NN_Filter + ((2304)); _SNN_Filter = (((1)?(2304):(2304))); 
					} else if (!((1))) {
						_NN_Filter = _NN_Filter + ((-71424)); _SNN_Filter = (((1)?(2304):(2304))); 
					}
				} else if (!((1))) {
					_NN_Filter = _NN_Filter + ((2304)); _SNN_Filter = (((1)?(2304):(2304))); 
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
					AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Filter+_NN_Filter), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+11520+2304*((D0Ind_Total)%2)),
							_SNN_Filter, 0, &UchanHR1);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
				if (_SN_Filter) {
					AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+11520+2304*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+328+2304*((D0Ind_Total+1)%2)),
							_SN_Filter, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+100*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (7-1*(1)-1*(1));
				KerArg1->UsedH = (unsigned short int) (7-1*(1)-1*(1));
				KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+328+2304*((D0Ind_Total)%2));
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				_SN_Filter = _SNN_Filter;
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+4936), 3200, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S72_MatAdd_64x5x5(
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
			AT_FORK(gap_ncore(), (void *) KerParMatAdd_fp, (void *) KerArg0);
			__CALL(KerParMatAdd_fp, KerArg0);
		} /* End iteration on Tile0 */
	} /* End iteration on D0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+6400), 3200, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S73_AveragePool_2x2(
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
void S76_Linear_7x256(
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
	KerArg0->Norm = (unsigned char) (15);
	KerArg0->NormBias = (signed char) (12);
	KerArg0->LB = (int) (-32768);
	KerArg0->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0), 512, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Filter+0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory+4992+0), 3584, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read Filter */
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L2_Memory+4992+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+512), 3584, 0, &DmaR_Evt2);
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
void S77_SoftMax(
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
	resnet_L3_Memory = (AT_HYPERRAM_POINTER) AT_HYPERRAM_ALLOC(&HyperRam, 478974);
	if (resnet_L3_Memory == 0) return 2;
	resnet_L2_Memory = (AT_L2_POINTER) AT_L2_ALLOC(0, 20000);
	if (resnet_L2_Memory == 0) return 3;
	resnet_L1_Memory = (AT_L1_POINTER) AT_L1_ALLOC(0, 18720);
	if (resnet_L1_Memory == 0) return 4;
	/* Moving Conv1kernel, size 144 from HyperFlash at 353408 to (size 144) HyperRam at 353408..353551 */
	{
		int Size = 144, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 353408+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 353408+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Model_1conv1conv2d_bias, size 16 from HyperFlash at 354672 to (size 16) HyperRam at 354672..354687 */
	{
		int Size = 16, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 354672+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354672+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Model_1conv2conv2d_bias, size 16 from HyperFlash at 354688 to (size 16) HyperRam at 354688..354703 */
	{
		int Size = 16, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 354688+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354688+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Res2bbranch2akernel, size 1152 from HyperFlash at 347520 to (size 1152) HyperRam at 347520..348671 */
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
	/* Moving Model_1res2bbranch2aconv2d_bia, size 16 from HyperFlash at 354704 to (size 16) HyperRam at 354704..354719 */
	{
		int Size = 16, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 354704+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354704+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Res2bbranch2bkernel, size 1152 from HyperFlash at 348672 to (size 1152) HyperRam at 348672..349823 */
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
	/* Moving Model_1res2bbranch2bconv2d_bia, size 16 from HyperFlash at 354720 to (size 16) HyperRam at 354720..354735 */
	{
		int Size = 16, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 354720+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354720+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Res2cbranch2akernel, size 1152 from HyperFlash at 349824 to (size 1152) HyperRam at 349824..350975 */
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
	/* Moving Model_1res2cbranch2aconv2d_bia, size 16 from HyperFlash at 354736 to (size 16) HyperRam at 354736..354751 */
	{
		int Size = 16, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 354736+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354736+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Res2cbranch2bkernel, size 1152 from HyperFlash at 350976 to (size 1152) HyperRam at 350976..352127 */
	{
		int Size = 1152, Base = 0;
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
	/* Moving Model_1res2cbranch2bconv2d_bia, size 16 from HyperFlash at 354752 to (size 16) HyperRam at 354752..354767 */
	{
		int Size = 16, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 354752+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354752+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
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
	/* Moving Model_1res3a_branch2aconv2d_bi, size 32 from HyperFlash at 354512 to (size 32) HyperRam at 354512..354543 */
	{
		int Size = 32, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 354512+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354512+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Res3a_branch1kernel, size 256 from HyperFlash at 353152 to (size 256) HyperRam at 353152..353407 */
	{
		int Size = 256, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 353152+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 353152+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Model_1res3a_branch1conv2d_bia, size 32 from HyperFlash at 354544 to (size 32) HyperRam at 354544..354575 */
	{
		int Size = 32, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 354544+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354544+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
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
	/* Moving Model_1res3a_branch2bconv2d_bi, size 32 from HyperFlash at 354576 to (size 32) HyperRam at 354576..354607 */
	{
		int Size = 32, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 354576+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354576+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
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
	/* Moving Model_1res3bbranch2aconv2d_bia, size 32 from HyperFlash at 354608 to (size 32) HyperRam at 354608..354639 */
	{
		int Size = 32, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 354608+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354608+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
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
	/* Moving Model_1res3bbranch2bconv2d_bia, size 32 from HyperFlash at 354640 to (size 32) HyperRam at 354640..354671 */
	{
		int Size = 32, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 354640+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354640+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
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
	/* Moving Model_1res4a_branch2aconv2d_bi, size 64 from HyperFlash at 354192 to (size 64) HyperRam at 354192..354255 */
	{
		int Size = 64, Base = 0;
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
	/* Moving Res4a_branch1kernel, size 1024 from HyperFlash at 352128 to (size 1024) HyperRam at 352128..353151 */
	{
		int Size = 1024, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 352128+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 352128+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Model_1res4a_branch1conv2d_bia, size 64 from HyperFlash at 354256 to (size 64) HyperRam at 354256..354319 */
	{
		int Size = 64, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 354256+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354256+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
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
	/* Moving Model_1res4a_branch2bconv2d_bi, size 64 from HyperFlash at 354320 to (size 64) HyperRam at 354320..354383 */
	{
		int Size = 64, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 354320+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354320+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Res4bbranch2akernel, size 18432 from HyperFlash at 18432 to (size 18432) HyperRam at 18432..36863 */
	{
		int Size = 18432, Base = 0;
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
	/* Moving Model_1res4bbranch2aconv2d_bia, size 64 from HyperFlash at 354384 to (size 64) HyperRam at 354384..354447 */
	{
		int Size = 64, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 354384+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354384+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Res4bbranch2bkernel, size 18432 from HyperFlash at 36864 to (size 18432) HyperRam at 36864..55295 */
	{
		int Size = 18432, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 36864+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 36864+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Model_1res4bbranch2bconv2d_bia, size 64 from HyperFlash at 354448 to (size 64) HyperRam at 354448..354511 */
	{
		int Size = 64, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 354448+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354448+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Res5a_branch2akernel, size 36864 from HyperFlash at 55296 to (size 36864) HyperRam at 55296..92159 */
	{
		int Size = 36864, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 55296+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 55296+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
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
	/* Moving Model_1res5a_branch1conv2d_bia, size 128 from HyperFlash at 353680 to (size 128) HyperRam at 353680..353807 */
	{
		int Size = 128, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 353680+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 353680+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Res5a_branch2bkernel, size 73728 from HyperFlash at 92160 to (size 73728) HyperRam at 92160..165887 */
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
	/* Moving Model_1res5a_branch2bconv2d_bi, size 128 from HyperFlash at 353808 to (size 128) HyperRam at 353808..353935 */
	{
		int Size = 128, Base = 0;
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
	/* Moving Res5bbranch2akernel, size 73728 from HyperFlash at 165888 to (size 73728) HyperRam at 165888..239615 */
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
	/* Moving Model_1res5bbranch2aconv2d_bia, size 128 from HyperFlash at 353936 to (size 128) HyperRam at 353936..354063 */
	{
		int Size = 128, Base = 0;
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
	/* Moving Res5bbranch2bkernel, size 73728 from HyperFlash at 239616 to (size 73728) HyperRam at 239616..313343 */
	{
		int Size = 73728, Base = 0;
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
	/* Moving Model_1res5bbranch2bconv2d_bia, size 128 from HyperFlash at 354064 to (size 128) HyperRam at 354064..354191 */
	{
		int Size = 128, Base = 0;
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
	/* Moving M2weightedaveragematmul_bias, size 14 from HyperFlash at 354768 to (size 14) HyperRam at 354768..354781 */
	{
		int Size = 14, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 354768+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354768+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Conv2kernel, size 1152 from HyperFlash at 346368 to (size 1152) L2 at 0..1151 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 346368), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), 1152, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Model_1res5a_branch2aconv2d_bi, size 128 from HyperFlash at 353552 to (size 128) L2 at 1152..1279 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 353552), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 1152), 128, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	return 0;
}
int resnetCNN_Destruct()

{
	AT_HYPERRAM_FREE(&HyperRam, resnet_L3_Memory, 478974);
	AT_L2_FREE(0, resnet_L2_Memory, 20000);
	AT_L1_FREE(0, resnet_L1_Memory, 18720);
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
	/* Moving Conv1kernel, size 144 from HyperRam at 353408 to (size 144) L2 at 6336 using event 0 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 353408), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 6336), 144, 0, &UchanHR0);
	/* Moving Model_1conv1conv2d_bias, size 16 from HyperRam at 354672 to (size 16) L2 at 6480 using event 1 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354672), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 6480), 16, 0, &UchanHR1);
	/* Moving Model_1conv2conv2d_bias, size 16 from HyperRam at 354688 to (size 16) L2 at 14264 using event 2 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354688), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 14264), 16, 0, &UchanHR2);
	/* Moving Res2bbranch2akernel, size 1152 from HyperRam at 347520 to (size 1152) L2 at 13112 using event 3 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 347520), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 13112), 1152, 0, &UchanHR3);
	/* Moving Model_1res2bbranch2aconv2d_bia, size 16 from HyperRam at 354704 to (size 16) L2 at 14280 using event 4 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354704), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 14280), 16, 0, &UchanHR4);
	/* Moving Model_1res2bbranch2bconv2d_bia, size 16 from HyperRam at 354720 to (size 16) L2 at 12416 using event 5 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354720), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 12416), 16, 0, &UchanHR5);
	/* Waiting completion of transfer of Conv1kernel using event 0 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR0);
	/* Waiting completion of transfer of Model_1conv1conv2d_bias using event 1 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1);
	S4_Conv2d_8x1x3x3_Relu(
		((signed short * __restrict__) Input_1), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+6336)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+6480)), /* Bias */
		((signed short * __restrict__) (resnet_L3_Memory+354784)) /* Out */
	);
	/* Waiting completion of transfer of Model_1conv2conv2d_bias using event 2 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2);
	S7_Conv2d_8x8x3x3_Relu(
		((signed short * __restrict__) (resnet_L3_Memory+354784)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+0)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+14264)), /* Bias */
		((signed short * __restrict__) (resnet_L3_Memory+454640)) /* Out */
	);
	/* Moving Res2bbranch2bkernel, size 1152 from HyperRam at 348672 to (size 1152) L2 at 11264 using event 0 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 348672), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 11264), 1152, 0, &UchanHR0);
	/* Waiting completion of transfer of Res2bbranch2akernel using event 3 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3);
	/* Waiting completion of transfer of Model_1res2bbranch2aconv2d_bia using event 4 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR4);
	S10_Conv2d_8x8x3x3_Relu(
		((signed short * __restrict__) (resnet_L3_Memory+454640)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+13112)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+14280)), /* Bias */
		((signed short * __restrict__) (resnet_L3_Memory+354784)) /* Out */
	);
	/* Waiting completion of transfer of Res2bbranch2bkernel using event 0 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR0);
	/* Waiting completion of transfer of Model_1res2bbranch2bconv2d_bia using event 5 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR5);
	S13_Conv2d_8x8x3x3(
		((signed short * __restrict__) (resnet_L3_Memory+354784)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+11264)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+12416)), /* Bias */
		((signed short * __restrict__) (resnet_L3_Memory+379120)) /* Out */
	);
	S14_MatAdd_8x39x39(
		((signed short * __restrict__) (resnet_L3_Memory+379120)), /* In1 */
		((signed short * __restrict__) (resnet_L3_Memory+454640)), /* In2 */
		((signed short * __restrict__) (resnet_L3_Memory+354784)) /* Out */
	);
	/* Moving Res2cbranch2akernel, size 1152 from HyperRam at 349824 to (size 1152) L2 at 11264 using event 0 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 349824), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 11264), 1152, 0, &UchanHR0);
	/* Moving Model_1res2cbranch2aconv2d_bia, size 16 from HyperRam at 354736 to (size 16) L2 at 13568 using event 1 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354736), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 13568), 16, 0, &UchanHR1);
	/* Moving Res2cbranch2bkernel, size 1152 from HyperRam at 350976 to (size 1152) L2 at 12416 using event 2 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 350976), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 12416), 1152, 0, &UchanHR2);
	/* Moving Model_1res2cbranch2bconv2d_bia, size 16 from HyperRam at 354752 to (size 16) L2 at 13584 using event 3 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354752), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 13584), 16, 0, &UchanHR3);
	/* Waiting completion of transfer of Res2cbranch2akernel using event 0 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR0);
	/* Waiting completion of transfer of Model_1res2cbranch2aconv2d_bia using event 1 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1);
	S17_Conv2d_8x8x3x3_Relu(
		((signed short * __restrict__) (resnet_L3_Memory+354784)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+11264)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+13568)), /* Bias */
		((signed short * __restrict__) (resnet_L3_Memory+379120)) /* Out */
	);
	/* Waiting completion of transfer of Res2cbranch2bkernel using event 2 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2);
	/* Waiting completion of transfer of Model_1res2cbranch2bconv2d_bia using event 3 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3);
	S20_Conv2d_8x8x3x3(
		((signed short * __restrict__) (resnet_L3_Memory+379120)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+12416)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+13584)), /* Bias */
		((signed short * __restrict__) (resnet_L3_Memory+403456)) /* Out */
	);
	S21_MatAdd_8x39x39(
		((signed short * __restrict__) (resnet_L3_Memory+403456)), /* In1 */
		((signed short * __restrict__) (resnet_L3_Memory+354784)), /* In2 */
		((signed short * __restrict__) (resnet_L3_Memory+379120)) /* Out */
	);
	/* Moving Res3a_branch2akernel, size 2304 from HyperRam at 344064 to (size 2304) L2 at 15720 using event 0 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 344064), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 15720), 2304, 0, &UchanHR0);
	/* Moving Model_1res3a_branch2aconv2d_bi, size 32 from HyperRam at 354512 to (size 32) L2 at 18024 using event 1 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354512), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 18024), 32, 0, &UchanHR1);
	/* Moving Res3a_branch2bkernel, size 4608 from HyperRam at 322560 to (size 4608) L2 at 11112 using event 2 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 322560), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 11112), 4608, 0, &UchanHR2);
	/* Waiting completion of transfer of Res3a_branch2akernel using event 0 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR0);
	/* Waiting completion of transfer of Model_1res3a_branch2aconv2d_bi using event 1 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1);
	S24_Conv2d_16x8x3x3_Relu(
		((signed short * __restrict__) (resnet_L3_Memory+379120)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+15720)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+18024)), /* Bias */
		((signed short * __restrict__) (resnet_L3_Memory+354784)) /* Out */
	);
	/* Moving Res3a_branch1kernel, size 256 from HyperRam at 353152 to (size 256) L2 at 15720 using event 0 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 353152), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 15720), 256, 0, &UchanHR0);
	/* Moving Model_1res3a_branch1conv2d_bia, size 32 from HyperRam at 354544 to (size 32) L2 at 15976 using event 1 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354544), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 15976), 32, 0, &UchanHR1);
	/* Moving Model_1res3a_branch2bconv2d_bi, size 32 from HyperRam at 354576 to (size 32) L2 at 8800 using event 3 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354576), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 8800), 32, 0, &UchanHR3);
	/* Waiting completion of transfer of Res3a_branch2bkernel using event 2 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2);
	/* Waiting completion of transfer of Model_1res3a_branch2bconv2d_bi using event 3 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3);
	S30_Conv2d_16x16x3x3_Relu(
		((signed short * __restrict__) (resnet_L3_Memory+354784)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+11112)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+8800)), /* Bias */
		((signed short * __restrict__) (resnet_L3_Memory+403456)) /* Out */
	);
	/* Waiting completion of transfer of Res3a_branch1kernel using event 0 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR0);
	/* Waiting completion of transfer of Model_1res3a_branch1conv2d_bia using event 1 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1);
	S27_Conv2d_16x8x1x1(
		((signed short * __restrict__) (resnet_L3_Memory+379120)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+15720)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+15976)), /* Bias */
		((signed short * __restrict__) (resnet_L3_Memory+354784)) /* Out */
	);
	S31_MatAdd_16x20x20(
		((signed short * __restrict__) (resnet_L3_Memory+403456)), /* In1 */
		((signed short * __restrict__) (resnet_L3_Memory+354784)), /* In2 */
		((signed short * __restrict__) (resnet_L3_Memory+367584)) /* Out */
	);
	/* Moving Res3bbranch2akernel, size 4608 from HyperRam at 327168 to (size 4608) L2 at 8800 using event 0 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 327168), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 8800), 4608, 0, &UchanHR0);
	/* Moving Model_1res3bbranch2aconv2d_bia, size 32 from HyperRam at 354608 to (size 32) L2 at 13408 using event 1 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354608), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 13408), 32, 0, &UchanHR1);
	/* Moving Model_1res3bbranch2bconv2d_bia, size 32 from HyperRam at 354640 to (size 32) L2 at 13440 using event 2 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354640), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 13440), 32, 0, &UchanHR2);
	/* Waiting completion of transfer of Res3bbranch2akernel using event 0 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR0);
	/* Waiting completion of transfer of Model_1res3bbranch2aconv2d_bia using event 1 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1);
	S34_Conv2d_16x16x3x3_Relu(
		((signed short * __restrict__) (resnet_L3_Memory+367584)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+8800)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+13408)), /* Bias */
		((signed short * __restrict__) (resnet_L3_Memory+354784)) /* Out */
	);
	/* Moving Res3bbranch2bkernel, size 4608 from HyperRam at 331776 to (size 4608) L2 at 8800 using event 0 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 331776), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 8800), 4608, 0, &UchanHR0);
	/* Waiting completion of transfer of Res3bbranch2bkernel using event 0 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR0);
	/* Waiting completion of transfer of Model_1res3bbranch2bconv2d_bia using event 2 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2);
	S37_Conv2d_16x16x3x3(
		((signed short * __restrict__) (resnet_L3_Memory+354784)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+8800)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+13440)), /* Bias */
		((signed short * __restrict__) (resnet_L3_Memory+393184)) /* Out */
	);
	S38_MatAdd_16x20x20(
		((signed short * __restrict__) (resnet_L3_Memory+393184)), /* In1 */
		((signed short * __restrict__) (resnet_L3_Memory+367584)), /* In2 */
		((signed short * __restrict__) (resnet_L3_Memory+380384)) /* Out */
	);
	/* Moving Res4a_branch2akernel, size 9216 from HyperRam at 313344 to (size 9216) L2 at 6240 using event 0 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 313344), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 6240), 9216, 0, &UchanHR0);
	/* Moving Model_1res4a_branch2aconv2d_bi, size 64 from HyperRam at 354192 to (size 64) L2 at 15456 using event 1 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354192), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 15456), 64, 0, &UchanHR1);
	/* Waiting completion of transfer of Res4a_branch2akernel using event 0 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR0);
	/* Waiting completion of transfer of Model_1res4a_branch2aconv2d_bi using event 1 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1);
	S41_Conv2d_32x16x3x3_Relu(
		((signed short * __restrict__) (resnet_L3_Memory+380384)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+6240)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+15456)), /* Bias */
		((signed short * __restrict__) (resnet_L3_Memory+354784)) /* Out */
	);
	/* Moving Model_1res4a_branch1conv2d_bia, size 64 from HyperRam at 354256 to (size 64) L2 at 12544 using event 0 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354256), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 12544), 64, 0, &UchanHR0);
	/* Moving Model_1res4a_branch2bconv2d_bi, size 64 from HyperRam at 354320 to (size 64) L2 at 11584 using event 1 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354320), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 11584), 64, 0, &UchanHR1);
	/* Waiting completion of transfer of Model_1res4a_branch2bconv2d_bi using event 1 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1);
	S47_Conv2d_32x32x3x3_Relu(
		((signed short * __restrict__) (resnet_L3_Memory+354784)), /* In */
		((signed short * __restrict__) (resnet_L3_Memory+0)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+11584)), /* Bias */
		((signed short * __restrict__) (resnet_L3_Memory+367584)) /* Out */
	);
	/* Moving Res4a_branch1kernel, size 1024 from HyperRam at 352128 to (size 1024) L2 at 11520 using event 1 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 352128), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 11520), 1024, 0, &UchanHR1);
	/* Waiting completion of transfer of Res4a_branch1kernel using event 1 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1);
	/* Waiting completion of transfer of Model_1res4a_branch1conv2d_bia using event 0 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR0);
	S44_Conv2d_32x16x1x1(
		((signed short * __restrict__) (resnet_L3_Memory+380384)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+11520)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+12544)), /* Bias */
		((signed short * __restrict__) (resnet_L3_Memory+354784)) /* Out */
	);
	S48_MatAdd_32x10x10(
		((signed short * __restrict__) (resnet_L3_Memory+367584)), /* In1 */
		((signed short * __restrict__) (resnet_L3_Memory+354784)), /* In2 */
		((signed short * __restrict__) (resnet_L3_Memory+361184)) /* Out */
	);
	/* Moving Model_1res4bbranch2aconv2d_bia, size 64 from HyperRam at 354384 to (size 64) L2 at 11584 using event 0 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354384), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 11584), 64, 0, &UchanHR0);
	/* Waiting completion of transfer of Model_1res4bbranch2aconv2d_bia using event 0 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR0);
	S51_Conv2d_32x32x3x3_Relu(
		((signed short * __restrict__) (resnet_L3_Memory+361184)), /* In */
		((signed short * __restrict__) (resnet_L3_Memory+18432)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+11584)), /* Bias */
		((signed short * __restrict__) (resnet_L2_Memory+2880)) /* Out */
	);
	/* Moving Model_1res4bbranch2bconv2d_bia, size 64 from HyperRam at 354448 to (size 64) L2 at 1280 using event 0 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354448), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 1280), 64, 0, &UchanHR0);
	/* Waiting completion of transfer of Model_1res4bbranch2bconv2d_bia using event 0 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR0);
	S54_Conv2d_32x32x3x3(
		((signed short * __restrict__) (resnet_L2_Memory+2880)), /* In */
		((signed short * __restrict__) (resnet_L3_Memory+36864)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+1280)), /* Bias */
		((signed short * __restrict__) (resnet_L3_Memory+367584)) /* Out */
	);
	S55_MatAdd_32x10x10(
		((signed short * __restrict__) (resnet_L3_Memory+367584)), /* In1 */
		((signed short * __restrict__) (resnet_L3_Memory+361184)), /* In2 */
		((signed short * __restrict__) (resnet_L3_Memory+354784)) /* Out */
	);
	S58_Conv2d_64x32x3x3_Relu(
		((signed short * __restrict__) (resnet_L3_Memory+354784)), /* In */
		((signed short * __restrict__) (resnet_L3_Memory+55296)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+1152)), /* Bias */
		((signed short * __restrict__) (resnet_L2_Memory+2080)) /* Out */
	);
	/* Moving Model_1res5a_branch2bconv2d_bi, size 128 from HyperRam at 353808 to (size 128) L2 at 1280 using event 0 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 353808), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 1280), 128, 0, &UchanHR0);
	/* Waiting completion of transfer of Model_1res5a_branch2bconv2d_bi using event 0 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR0);
	S64_Conv2d_64x64x3x3_Relu(
		((signed short * __restrict__) (resnet_L2_Memory+2080)), /* In */
		((signed short * __restrict__) (resnet_L3_Memory+92160)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+1280)), /* Bias */
		((signed short * __restrict__) (resnet_L3_Memory+361184)) /* Out */
	);
	/* Moving Res5a_branch1kernel, size 4096 from HyperRam at 336384 to (size 4096) L2 at 8320 using event 0 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 336384), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 8320), 4096, 0, &UchanHR0);
	/* Moving Model_1res5a_branch1conv2d_bia, size 128 from HyperRam at 353680 to (size 128) L2 at 12416 using event 1 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 353680), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 12416), 128, 0, &UchanHR1);
	/* Waiting completion of transfer of Res5a_branch1kernel using event 0 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR0);
	/* Waiting completion of transfer of Model_1res5a_branch1conv2d_bia using event 1 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1);
	S61_Conv2d_64x32x1x1(
		((signed short * __restrict__) (resnet_L3_Memory+354784)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+8320)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+12416)), /* Bias */
		((signed short * __restrict__) (resnet_L2_Memory+5120)) /* Out */
	);
	/* Moving Model_1res5bbranch2aconv2d_bia, size 128 from HyperRam at 353936 to (size 128) L2 at 4480 using event 0 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 353936), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 4480), 128, 0, &UchanHR0);
	S65_MatAdd_64x5x5(
		((signed short * __restrict__) (resnet_L3_Memory+361184)), /* In1 */
		((signed short * __restrict__) (resnet_L2_Memory+5120)), /* In2 */
		((signed short * __restrict__) (resnet_L2_Memory+8320)) /* Out */
	);
	/* Moving Model_1res5bbranch2bconv2d_bia, size 128 from HyperRam at 354064 to (size 128) L2 at 7680 using event 1 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354064), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 7680), 128, 0, &UchanHR1);
	/* Waiting completion of transfer of Model_1res5bbranch2aconv2d_bia using event 0 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR0);
	S68_Conv2d_64x64x3x3_Relu(
		((signed short * __restrict__) (resnet_L2_Memory+8320)), /* In */
		((signed short * __restrict__) (resnet_L3_Memory+165888)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+4480)), /* Bias */
		((signed short * __restrict__) (resnet_L2_Memory+1280)) /* Out */
	);
	/* Waiting completion of transfer of Model_1res5bbranch2bconv2d_bia using event 1 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1);
	S71_Conv2d_64x64x3x3(
		((signed short * __restrict__) (resnet_L2_Memory+1280)), /* In */
		((signed short * __restrict__) (resnet_L3_Memory+239616)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+7680)), /* Bias */
		((signed short * __restrict__) (resnet_L2_Memory+4480)) /* Out */
	);
	S72_MatAdd_64x5x5(
		((signed short * __restrict__) (resnet_L2_Memory+4480)), /* In1 */
		((signed short * __restrict__) (resnet_L2_Memory+8320)), /* In2 */
		((signed short * __restrict__) (resnet_L2_Memory+1280)) /* Out */
	);
	/* Moving M2weightedaveragematmul_bias, size 14 from HyperRam at 354768 to (size 14) L2 at 8576 using event 0 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 354768), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 8576), 14, 0, &UchanHR0);
	S73_AveragePool_2x2(
		((signed short * __restrict__) (resnet_L2_Memory+1280)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+4480)) /* Out */
	);
	/* Waiting completion of transfer of M2weightedaveragematmul_bias using event 0 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR0);
	S76_Linear_7x256(
		((signed short * __restrict__) (resnet_L2_Memory+4480)), /* In */
		((signed short * __restrict__) (resnet_L3_Memory+340480)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+8576)), /* Bias */
		((signed short * __restrict__) (resnet_L2_Memory+1280)) /* Out */
	);
	S77_SoftMax(
		((signed short * __restrict__) (resnet_L2_Memory+1280)), /* In */
		((signed short * __restrict__) Output_1) /* Out */
	);
	return 0;
}
