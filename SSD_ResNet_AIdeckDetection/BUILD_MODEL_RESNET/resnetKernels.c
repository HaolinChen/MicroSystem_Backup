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
	/* Shared L1: 43264 bytes, L2 buffer: 20512 bytes */
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
		[D1 Dim: Init: 8, Tiled: 1][Tile0 Dim: 10][D0 Dim: Init: 1, Tiled: 1]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
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
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 784 [D1, [0 x 784, 784]][D0, [0 x 98, 98]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 784, 784]][D0, [0 x 98, 98]]
		Tile0: [0, 784, 784], Tile1: [0, 784, 784], Tile2; [0, 784, 784]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 10 logical tiles, 10 physical tiles
			Total Size: 51200 [D0, [0 x 51200, 51200]][Tile0, 10:[160x20, 8:160x23, 160x19], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 10:[160x20], 2][D0, [0 x 51200, 51200]]
		Tile0: [0, 6400, 6400], Tile1: [4160, 7360, 7360], Tile2; [9280, 7360, 7360]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 10 logical tiles, 1 physical tiles
			Total Size: 199712 [D1, [0 x 199712, 199712]][Tile0, 10:[79x9, 8:79x9, 79x7], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 199712, 199712]][Tile0, 10:[79x9, 8:79x9, 79x7], 4]
		Tile0: [0, 22752, 2844], Tile1: [0, 22752, 2844], Tile2; [0, 22752, 2844]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+20512);
	KerArg0->W = (unsigned short int) (79);
	KerArg0->OutFeatures = (unsigned short int) (8);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+14720);
	KerArg0->NormBias = (signed char) (14);
	KerArg1->W = (unsigned short int) (160);
	KerArg1->UsedW = (unsigned short int) (160);
	KerArg1->InFeatures = (unsigned short int) (1);
	KerArg1->OutFeatures = (unsigned short int) (8);
	KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+14736);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+20512);
	KerArg1->Norm = (unsigned char) (15);
	KerArg1->TotalInFeatures = (short int) (1);
	KerArg1->Orientation = (unsigned char) (1);
	KerArg1->S = (unsigned char) (2);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+20512);
	KerArg2->W = (unsigned short int) (79);
	KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+20512);
	KerArg2->Norm = (unsigned char) (15);
	KerArg2->InFeatures = (unsigned short int) (8);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	KerArg3->In = (short int * __restrict__) (resnet_L1_Memory+20512);
	KerArg3->W = (unsigned short int) (79);
	KerArg3->UsedW = (unsigned short int) (79);
	KerArg3->OutFeatures = (unsigned short int) (8);
	KerArg3->Pad = (v4s) 0;
	KerArg3->M = (unsigned char) (3);
	KerArg3->S = (unsigned char) (2);
	KerArg3->Orientation = (unsigned char) (1);
	KerArg3->Oper = (unsigned char) (1);
	KerArg3->LB = (int) (0);
	KerArg3->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	_C_Out=0; _SC_Out=2496; _LC_Out=312;
	_SP_Out=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+14720), 16, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+14736), 784, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Filter */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 6400, 0, &DmaR_Evt3);
	_N_In=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<10; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==9), T0Ind_NextLast = ((T0Ind+1)==9);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->H = (unsigned short int) (T0Ind_Last?7:9);
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			{ /* Single iteration on D0 */
				int D0Ind_Last = 1, D0Ind_NextLast = 1;
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(T0Ind_Last)) {
					_N_In = _N_In + (5120-(960*(T0Ind==0))); _SN_In = (1*((T0Ind_NextLast)?6080:7360)); 
				} else if (!(1)) {
					_N_In = _N_In + (-45120); _SN_In = (1*(6400)); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+7360*((D0Ind_Total+1)%2)),
							_SN_In, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+7360*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (((T0Ind_Last)?19:23)-3*(T0Ind==0));
				KerArg1->UsedH = (unsigned short int) (((T0Ind_Last)?19:23)-3*(T0Ind==0));
				KerArg1->Pad = (v4s) ((v4s){3,0,3*(T0Ind==0),0*(T0Ind_Last)});
				AT_FORK(gap_ncore(), (void *) KerParConv7x7StrideS_DP_fp, (void *) KerArg1);
				__CALL(KerParConv7x7StrideS_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				/*============================= End Update Arg Pipeline =============================*/
				D0Ind_Total++;
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->H = (unsigned short int) (T0Ind_Last?7:9);
			AT_FORK(gap_ncore(), (void *) KerDP_IO_fp, (void *) KerArg2);
			__CALL(KerDP_IO_fp, KerArg2);
			KerArg3->H = (unsigned short int) (T0Ind_Last?7:9);
			KerArg3->UsedH = (unsigned short int) (T0Ind_Last?7:9);
			KerArg3->Out = (short int * __restrict__) (resnet_L1_Memory+15520+2496*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerParPoolNxNStrideS_fp, (void *) KerArg3);
			__CALL(KerParPoolNxNStrideS_fp, KerArg3);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+15520+2496*((T0Ind_Total)%2)),
					_SC_Out, 3042, _LC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SP_Out = _SC_Out;_LP_Out = _LC_Out;
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
	/*============================ End Write Tiles Epilog ===============================*/
}
void S7_Conv2d_8x8x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 46096 bytes, L2 buffer: 28624 bytes */
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
		[D1 Dim: Init: 8, Tiled: 1][Tile0 Dim: 3][D0 Dim: Init: 8, Tiled: 2]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 6 logical tiles, 6 physical tiles
			Total Size: 24336 [D0, [1 x 12168, 12168]][Tile0, 3:[39x15, 1:39x16, 39x12], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 3:[39x15, 39x12], 2][D0, [1 x 12168, 12168]]
		Tile0: [0, 4680, 1170], Tile1: [12168, 4680, 1170], Tile2; [1014, 4992, 1248]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 16 [D1, [0 x 16, 16]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 16, 16]]
		Tile0: [0, 16, 16], Tile1: [0, 16, 16], Tile2; [0, 16, 16]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 1152 [D1, [0 x 1152, 1152]][D0, [1 x 72, 72]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 1152, 1152]][D0, [1 x 72, 72]]
		Tile0: [0, 1152, 1152], Tile1: [0, 1152, 1152], Tile2; [0, 1152, 1152]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 3 logical tiles, 3 physical tiles
			Total Size: 24336 [D1, [0 x 24336, 24336]][Tile0, 3:[39x14, 1:39x14, 39x11], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 24336, 24336]][Tile0, 3:[39x14, 1:39x14, 39x11], 2]
		Tile0: [0, 8736, 1092], Tile1: [1092, 8736, 1092], Tile2; [2184, 6864, 858]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 3 logical tiles, 1 physical tiles
			Total Size: 48672 [D1, [0 x 48672, 48672]][Tile0, 3:[39x14, 1:39x14, 39x11], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 48672, 48672]][Tile0, 3:[39x14, 1:39x14, 39x11], 4]
		Tile0: [0, 17472, 2184], Tile1: [0, 17472, 2184], Tile2; [0, 17472, 2184]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+28624);
	KerArg0->W = (unsigned short int) (39);
	KerArg0->OutFeatures = (unsigned short int) (8);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+9984);
	KerArg0->NormBias = (signed char) (13);
	KerArg1->W = (unsigned short int) (39);
	KerArg1->UsedW = (unsigned short int) (39);
	KerArg1->InFeatures = (unsigned short int) (4);
	KerArg1->OutFeatures = (unsigned short int) (8);
	KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+10000);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+28624);
	KerArg1->Norm = (unsigned char) (14);
	KerArg1->TotalInFeatures = (short int) (8);
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+28624);
	KerArg2->W = (unsigned short int) (39);
	KerArg2->Norm = (unsigned char) (14);
	KerArg2->InFeatures = (unsigned short int) (8);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 4680, 3042, 1170, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+9984), 16, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+10000), 1152, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
	_C_Out=0; _SC_Out=8736; _LC_Out=1092;
	_SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<3; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==2), T0Ind_NextLast = ((T0Ind+1)==2);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->H = (unsigned short int) (T0Ind_Last?11:14);
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<2; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==1), D0Ind_NextLast = ((D0Ind+1)==1);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (12168); _LN_In = ((T0Ind_Last)?936:(1248-78*(T0Ind==0))); _SN_In = (4*_LN_In); 
				} else if (!(T0Ind_Last)) {
					_N_In = _N_In + (1092-(78*(T0Ind==0)))+(-12168); _LN_In = ((T0Ind_NextLast)?936:1248); _SN_In = (4*_LN_In); 
				} else if (!(1)) {
					_N_In = _N_In + (-2106)+(-12168); _LN_In = (1170); _SN_In = (4*_LN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+4992*((D0Ind_Total+1)%2)),
							_SN_In, 3042, _LN_In, 0, &DmaR_Evt1);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+4992*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (((T0Ind_Last)?12:16)-1*(T0Ind==0));
				KerArg1->UsedH = (unsigned short int) (((T0Ind_Last)?12:16)-1*(T0Ind==0));
				KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+10000+((D0Ind)*72));
				KerArg1->Pad = (v4s) ((v4s){1,1,1*(T0Ind==0),1*(T0Ind_Last)});
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->H = (unsigned short int) (T0Ind_Last?11:14);
			KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+11152+8736*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+11152+8736*((T0Ind_Total)%2)),
					_SC_Out, 3042, _LC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (1092); _LC_Out = ((T0Ind_NextLast)?858:1092); _SC_Out = (8*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S10_Conv2d_8x8x3x3(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 46096 bytes, L2 buffer: 28624 bytes */
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
		[D1 Dim: Init: 8, Tiled: 1][Tile0 Dim: 3][D0 Dim: Init: 8, Tiled: 2]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 6 logical tiles, 6 physical tiles
			Total Size: 24336 [D0, [1 x 12168, 12168]][Tile0, 3:[39x15, 1:39x16, 39x12], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 3:[39x15, 39x12], 2][D0, [1 x 12168, 12168]]
		Tile0: [0, 4680, 1170], Tile1: [12168, 4680, 1170], Tile2; [1014, 4992, 1248]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 16 [D1, [0 x 16, 16]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 16, 16]]
		Tile0: [0, 16, 16], Tile1: [0, 16, 16], Tile2; [0, 16, 16]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 1152 [D1, [0 x 1152, 1152]][D0, [1 x 72, 72]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 1152, 1152]][D0, [1 x 72, 72]]
		Tile0: [0, 1152, 1152], Tile1: [0, 1152, 1152], Tile2; [0, 1152, 1152]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 3 logical tiles, 3 physical tiles
			Total Size: 24336 [D1, [0 x 24336, 24336]][Tile0, 3:[39x14, 1:39x14, 39x11], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 24336, 24336]][Tile0, 3:[39x14, 1:39x14, 39x11], 2]
		Tile0: [0, 8736, 1092], Tile1: [1092, 8736, 1092], Tile2; [2184, 6864, 858]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 3 logical tiles, 1 physical tiles
			Total Size: 48672 [D1, [0 x 48672, 48672]][Tile0, 3:[39x14, 1:39x14, 39x11], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 48672, 48672]][Tile0, 3:[39x14, 1:39x14, 39x11], 4]
		Tile0: [0, 17472, 2184], Tile1: [0, 17472, 2184], Tile2; [0, 17472, 2184]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+28624);
	KerArg0->W = (unsigned short int) (39);
	KerArg0->OutFeatures = (unsigned short int) (8);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+9984);
	KerArg0->NormBias = (signed char) (14);
	KerArg1->W = (unsigned short int) (39);
	KerArg1->UsedW = (unsigned short int) (39);
	KerArg1->InFeatures = (unsigned short int) (4);
	KerArg1->OutFeatures = (unsigned short int) (8);
	KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+10000);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+28624);
	KerArg1->Norm = (unsigned char) (15);
	KerArg1->TotalInFeatures = (short int) (8);
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+28624);
	KerArg2->W = (unsigned short int) (39);
	KerArg2->Norm = (unsigned char) (15);
	KerArg2->InFeatures = (unsigned short int) (8);
	KerArg2->LB = (int) (-32768);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 4680, 3042, 1170, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+9984), 16, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+10000), 1152, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
	_C_Out=0; _SC_Out=8736; _LC_Out=1092;
	_SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<3; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==2), T0Ind_NextLast = ((T0Ind+1)==2);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->H = (unsigned short int) (T0Ind_Last?11:14);
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<2; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==1), D0Ind_NextLast = ((D0Ind+1)==1);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (12168); _LN_In = ((T0Ind_Last)?936:(1248-78*(T0Ind==0))); _SN_In = (4*_LN_In); 
				} else if (!(T0Ind_Last)) {
					_N_In = _N_In + (1092-(78*(T0Ind==0)))+(-12168); _LN_In = ((T0Ind_NextLast)?936:1248); _SN_In = (4*_LN_In); 
				} else if (!(1)) {
					_N_In = _N_In + (-2106)+(-12168); _LN_In = (1170); _SN_In = (4*_LN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+4992*((D0Ind_Total+1)%2)),
							_SN_In, 3042, _LN_In, 0, &DmaR_Evt1);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+4992*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (((T0Ind_Last)?12:16)-1*(T0Ind==0));
				KerArg1->UsedH = (unsigned short int) (((T0Ind_Last)?12:16)-1*(T0Ind==0));
				KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+10000+((D0Ind)*72));
				KerArg1->Pad = (v4s) ((v4s){1,1,1*(T0Ind==0),1*(T0Ind_Last)});
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->H = (unsigned short int) (T0Ind_Last?11:14);
			KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+11152+8736*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+11152+8736*((T0Ind_Total)%2)),
					_SC_Out, 3042, _LC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (1092); _LC_Out = ((T0Ind_NextLast)?858:1092); _SC_Out = (8*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S11_MatAdd_8x39x39(
		short int * __restrict__ In1,
		short int * __restrict__ In2,
		short int * __restrict__ Out)

{
	/* Shared L1: 44928 bytes, L2 buffer: 44928 bytes */
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
		[D0 Dim: Init: 8, Tiled: 1][Tile0 Dim: 4]
	Ker Arg: In1, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 4 logical tiles, 4 physical tiles
			Total Size: 24336 [D0, [0 x 24336, 24336]][Tile0, 4:[39x12, 2:39x12, 39x3], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 24336, 24336]][Tile0, 4:[39x12, 2:39x12, 39x3], 2]
		Tile0: [0, 7488, 936], Tile1: [936, 7488, 936], Tile2; [1872, 7488, 936]
	Ker Arg: In2, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 4 logical tiles, 4 physical tiles
			Total Size: 24336 [D0, [0 x 24336, 24336]][Tile0, 4:[39x12, 2:39x12, 39x3], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 24336, 24336]][Tile0, 4:[39x12, 2:39x12, 39x3], 2]
		Tile0: [0, 7488, 936], Tile1: [936, 7488, 936], Tile2; [1872, 7488, 936]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 4 logical tiles, 4 physical tiles
			Total Size: 24336 [D0, [0 x 24336, 24336]][Tile0, 4:[39x12, 2:39x12, 39x3], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 24336, 24336]][Tile0, 4:[39x12, 2:39x12, 39x3], 2]
		Tile0: [0, 7488, 936], Tile1: [936, 7488, 936], Tile2; [1872, 7488, 936]
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
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In1+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 7488, 3042, 936, 0, &DmaR_Evt1);
	_N_In1=0;
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In2+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+14976+0), 7488, 3042, 936, 0, &DmaR_Evt2);
	_N_In2=0;
	_C_Out=0; _SC_Out=7488; _LC_Out=936;
	_SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D0 */
		int D0Ind_Last = 1, D0Ind_NextLast = 1;
		for (T0Ind=0; T0Ind<4; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==3), T0Ind_NextLast = ((T0Ind+1)==3);
			/*================================= Prepare Tiles ===================================*/
			_SN_In1 = 0;
			if (!(T0Ind_Last)) {
				_N_In1 = _N_In1 + (936); _LN_In1 = ((T0Ind_NextLast)?234:936); _SN_In1 = (8*_LN_In1); 
			}
			_SN_In2 = 0;
			if (!(T0Ind_Last)) {
				_N_In2 = _N_In2 + (936); _LN_In2 = ((T0Ind_NextLast)?234:936); _SN_In2 = (8*_LN_In2); 
			}
			/*============================= End Prepare Tiles ===================================*/
			/*================================= Read Tiles ======================================*/
			AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In1 */
			if (_SN_In1) {
				AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In1+_N_In1), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+7488*((T0Ind_Total+1)%2)),
						_SN_In1, 3042, _LN_In1, 0, &DmaR_Evt1);
			}
			AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In2 */
			if (_SN_In2) {
				AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In2+_N_In2), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+14976+7488*((T0Ind_Total+1)%2)),
						_SN_In2, 3042, _LN_In2, 0, &DmaR_Evt2);
			}
			/*============================= End Read Tiles ======================================*/
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In1 = (short int *__restrict__) (resnet_L1_Memory+0+7488*((T0Ind_Total)%2));
			KerArg0->In2 = (short int *__restrict__) (resnet_L1_Memory+14976+7488*((T0Ind_Total)%2));
			KerArg0->Out = (short int *__restrict__) (resnet_L1_Memory+29952+7488*((T0Ind_Total)%2));
			KerArg0->H = (unsigned short int) (T0Ind_Last?3:12);
			AT_FORK(gap_ncore(), (void *) KerParMatAddDynAdjust_fp, (void *) KerArg0);
			__CALL(KerParMatAddDynAdjust_fp, KerArg0);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+29952+7488*((T0Ind_Total)%2)),
					_SC_Out, 3042, _LC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (936); _LC_Out = ((T0Ind_NextLast)?234:936); _SC_Out = (8*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S14_Conv2d_8x8x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 46096 bytes, L2 buffer: 28624 bytes */
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
		[D1 Dim: Init: 8, Tiled: 1][Tile0 Dim: 3][D0 Dim: Init: 8, Tiled: 2]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 6 logical tiles, 6 physical tiles
			Total Size: 24336 [D0, [1 x 12168, 12168]][Tile0, 3:[39x15, 1:39x16, 39x12], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 3:[39x15, 39x12], 2][D0, [1 x 12168, 12168]]
		Tile0: [0, 4680, 1170], Tile1: [12168, 4680, 1170], Tile2; [1014, 4992, 1248]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 16 [D1, [0 x 16, 16]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 16, 16]]
		Tile0: [0, 16, 16], Tile1: [0, 16, 16], Tile2; [0, 16, 16]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 1152 [D1, [0 x 1152, 1152]][D0, [1 x 72, 72]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 1152, 1152]][D0, [1 x 72, 72]]
		Tile0: [0, 1152, 1152], Tile1: [0, 1152, 1152], Tile2; [0, 1152, 1152]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 3 logical tiles, 3 physical tiles
			Total Size: 24336 [D1, [0 x 24336, 24336]][Tile0, 3:[39x14, 1:39x14, 39x11], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 24336, 24336]][Tile0, 3:[39x14, 1:39x14, 39x11], 2]
		Tile0: [0, 8736, 1092], Tile1: [1092, 8736, 1092], Tile2; [2184, 6864, 858]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 3 logical tiles, 1 physical tiles
			Total Size: 48672 [D1, [0 x 48672, 48672]][Tile0, 3:[39x14, 1:39x14, 39x11], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 48672, 48672]][Tile0, 3:[39x14, 1:39x14, 39x11], 4]
		Tile0: [0, 17472, 2184], Tile1: [0, 17472, 2184], Tile2; [0, 17472, 2184]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+28624);
	KerArg0->W = (unsigned short int) (39);
	KerArg0->OutFeatures = (unsigned short int) (8);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+9984);
	KerArg0->NormBias = (signed char) (12);
	KerArg1->W = (unsigned short int) (39);
	KerArg1->UsedW = (unsigned short int) (39);
	KerArg1->InFeatures = (unsigned short int) (4);
	KerArg1->OutFeatures = (unsigned short int) (8);
	KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+10000);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+28624);
	KerArg1->Norm = (unsigned char) (14);
	KerArg1->TotalInFeatures = (short int) (8);
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+28624);
	KerArg2->W = (unsigned short int) (39);
	KerArg2->Norm = (unsigned char) (14);
	KerArg2->InFeatures = (unsigned short int) (8);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 4680, 3042, 1170, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+9984), 16, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+10000), 1152, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
	_C_Out=0; _SC_Out=8736; _LC_Out=1092;
	_SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<3; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==2), T0Ind_NextLast = ((T0Ind+1)==2);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->H = (unsigned short int) (T0Ind_Last?11:14);
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<2; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==1), D0Ind_NextLast = ((D0Ind+1)==1);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (12168); _LN_In = ((T0Ind_Last)?936:(1248-78*(T0Ind==0))); _SN_In = (4*_LN_In); 
				} else if (!(T0Ind_Last)) {
					_N_In = _N_In + (1092-(78*(T0Ind==0)))+(-12168); _LN_In = ((T0Ind_NextLast)?936:1248); _SN_In = (4*_LN_In); 
				} else if (!(1)) {
					_N_In = _N_In + (-2106)+(-12168); _LN_In = (1170); _SN_In = (4*_LN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+4992*((D0Ind_Total+1)%2)),
							_SN_In, 3042, _LN_In, 0, &DmaR_Evt1);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+4992*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (((T0Ind_Last)?12:16)-1*(T0Ind==0));
				KerArg1->UsedH = (unsigned short int) (((T0Ind_Last)?12:16)-1*(T0Ind==0));
				KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+10000+((D0Ind)*72));
				KerArg1->Pad = (v4s) ((v4s){1,1,1*(T0Ind==0),1*(T0Ind_Last)});
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->H = (unsigned short int) (T0Ind_Last?11:14);
			KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+11152+8736*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+11152+8736*((T0Ind_Total)%2)),
					_SC_Out, 3042, _LC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (1092); _LC_Out = ((T0Ind_NextLast)?858:1092); _SC_Out = (8*_LC_Out); 
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
	/* Shared L1: 46096 bytes, L2 buffer: 28624 bytes */
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
		[D1 Dim: Init: 8, Tiled: 1][Tile0 Dim: 3][D0 Dim: Init: 8, Tiled: 2]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 6 logical tiles, 6 physical tiles
			Total Size: 24336 [D0, [1 x 12168, 12168]][Tile0, 3:[39x15, 1:39x16, 39x12], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 3:[39x15, 39x12], 2][D0, [1 x 12168, 12168]]
		Tile0: [0, 4680, 1170], Tile1: [12168, 4680, 1170], Tile2; [1014, 4992, 1248]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 16 [D1, [0 x 16, 16]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 16, 16]]
		Tile0: [0, 16, 16], Tile1: [0, 16, 16], Tile2; [0, 16, 16]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 1152 [D1, [0 x 1152, 1152]][D0, [1 x 72, 72]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 1152, 1152]][D0, [1 x 72, 72]]
		Tile0: [0, 1152, 1152], Tile1: [0, 1152, 1152], Tile2; [0, 1152, 1152]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 3 logical tiles, 3 physical tiles
			Total Size: 24336 [D1, [0 x 24336, 24336]][Tile0, 3:[39x14, 1:39x14, 39x11], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 24336, 24336]][Tile0, 3:[39x14, 1:39x14, 39x11], 2]
		Tile0: [0, 8736, 1092], Tile1: [1092, 8736, 1092], Tile2; [2184, 6864, 858]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 3 logical tiles, 1 physical tiles
			Total Size: 48672 [D1, [0 x 48672, 48672]][Tile0, 3:[39x14, 1:39x14, 39x11], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 48672, 48672]][Tile0, 3:[39x14, 1:39x14, 39x11], 4]
		Tile0: [0, 17472, 2184], Tile1: [0, 17472, 2184], Tile2; [0, 17472, 2184]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+28624);
	KerArg0->W = (unsigned short int) (39);
	KerArg0->OutFeatures = (unsigned short int) (8);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+9984);
	KerArg0->NormBias = (signed char) (13);
	KerArg1->W = (unsigned short int) (39);
	KerArg1->UsedW = (unsigned short int) (39);
	KerArg1->InFeatures = (unsigned short int) (4);
	KerArg1->OutFeatures = (unsigned short int) (8);
	KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+10000);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+28624);
	KerArg1->Norm = (unsigned char) (16);
	KerArg1->TotalInFeatures = (short int) (8);
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+28624);
	KerArg2->W = (unsigned short int) (39);
	KerArg2->Norm = (unsigned char) (16);
	KerArg2->InFeatures = (unsigned short int) (8);
	KerArg2->LB = (int) (-32768);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 4680, 3042, 1170, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+9984), 16, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+10000), 1152, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
	_C_Out=0; _SC_Out=8736; _LC_Out=1092;
	_SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<3; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==2), T0Ind_NextLast = ((T0Ind+1)==2);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->H = (unsigned short int) (T0Ind_Last?11:14);
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<2; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==1), D0Ind_NextLast = ((D0Ind+1)==1);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (12168); _LN_In = ((T0Ind_Last)?936:(1248-78*(T0Ind==0))); _SN_In = (4*_LN_In); 
				} else if (!(T0Ind_Last)) {
					_N_In = _N_In + (1092-(78*(T0Ind==0)))+(-12168); _LN_In = ((T0Ind_NextLast)?936:1248); _SN_In = (4*_LN_In); 
				} else if (!(1)) {
					_N_In = _N_In + (-2106)+(-12168); _LN_In = (1170); _SN_In = (4*_LN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+4992*((D0Ind_Total+1)%2)),
							_SN_In, 3042, _LN_In, 0, &DmaR_Evt1);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+4992*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (((T0Ind_Last)?12:16)-1*(T0Ind==0));
				KerArg1->UsedH = (unsigned short int) (((T0Ind_Last)?12:16)-1*(T0Ind==0));
				KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+10000+((D0Ind)*72));
				KerArg1->Pad = (v4s) ((v4s){1,1,1*(T0Ind==0),1*(T0Ind_Last)});
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->H = (unsigned short int) (T0Ind_Last?11:14);
			KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+11152+8736*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+11152+8736*((T0Ind_Total)%2)),
					_SC_Out, 3042, _LC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (1092); _LC_Out = ((T0Ind_NextLast)?858:1092); _SC_Out = (8*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S18_MatAdd_8x39x39(
		short int * __restrict__ In1,
		short int * __restrict__ In2,
		short int * __restrict__ Out)

{
	/* Shared L1: 44928 bytes, L2 buffer: 44928 bytes */
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
		[D0 Dim: Init: 8, Tiled: 1][Tile0 Dim: 4]
	Ker Arg: In1, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 4 logical tiles, 4 physical tiles
			Total Size: 24336 [D0, [0 x 24336, 24336]][Tile0, 4:[39x12, 2:39x12, 39x3], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 24336, 24336]][Tile0, 4:[39x12, 2:39x12, 39x3], 2]
		Tile0: [0, 7488, 936], Tile1: [936, 7488, 936], Tile2; [1872, 7488, 936]
	Ker Arg: In2, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 4 logical tiles, 4 physical tiles
			Total Size: 24336 [D0, [0 x 24336, 24336]][Tile0, 4:[39x12, 2:39x12, 39x3], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 24336, 24336]][Tile0, 4:[39x12, 2:39x12, 39x3], 2]
		Tile0: [0, 7488, 936], Tile1: [936, 7488, 936], Tile2; [1872, 7488, 936]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 4 logical tiles, 4 physical tiles
			Total Size: 24336 [D0, [0 x 24336, 24336]][Tile0, 4:[39x12, 2:39x12, 39x3], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 24336, 24336]][Tile0, 4:[39x12, 2:39x12, 39x3], 2]
		Tile0: [0, 7488, 936], Tile1: [936, 7488, 936], Tile2; [1872, 7488, 936]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->W = (unsigned short int) (39);
	KerArg0->N = (unsigned short int) (8);
	KerArg0->LB = (int) (-32768);
	KerArg0->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In1+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 7488, 3042, 936, 0, &DmaR_Evt1);
	_N_In1=0;
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In2+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+14976+0), 7488, 3042, 936, 0, &DmaR_Evt2);
	_N_In2=0;
	_C_Out=0; _SC_Out=7488; _LC_Out=936;
	_SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D0 */
		int D0Ind_Last = 1, D0Ind_NextLast = 1;
		for (T0Ind=0; T0Ind<4; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==3), T0Ind_NextLast = ((T0Ind+1)==3);
			/*================================= Prepare Tiles ===================================*/
			_SN_In1 = 0;
			if (!(T0Ind_Last)) {
				_N_In1 = _N_In1 + (936); _LN_In1 = ((T0Ind_NextLast)?234:936); _SN_In1 = (8*_LN_In1); 
			}
			_SN_In2 = 0;
			if (!(T0Ind_Last)) {
				_N_In2 = _N_In2 + (936); _LN_In2 = ((T0Ind_NextLast)?234:936); _SN_In2 = (8*_LN_In2); 
			}
			/*============================= End Prepare Tiles ===================================*/
			/*================================= Read Tiles ======================================*/
			AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In1 */
			if (_SN_In1) {
				AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In1+_N_In1), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+7488*((T0Ind_Total+1)%2)),
						_SN_In1, 3042, _LN_In1, 0, &DmaR_Evt1);
			}
			AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In2 */
			if (_SN_In2) {
				AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In2+_N_In2), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+14976+7488*((T0Ind_Total+1)%2)),
						_SN_In2, 3042, _LN_In2, 0, &DmaR_Evt2);
			}
			/*============================= End Read Tiles ======================================*/
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In1 = (short int *__restrict__) (resnet_L1_Memory+0+7488*((T0Ind_Total)%2));
			KerArg0->In2 = (short int *__restrict__) (resnet_L1_Memory+14976+7488*((T0Ind_Total)%2));
			KerArg0->Out = (short int *__restrict__) (resnet_L1_Memory+29952+7488*((T0Ind_Total)%2));
			KerArg0->H = (unsigned short int) (T0Ind_Last?3:12);
			AT_FORK(gap_ncore(), (void *) KerParMatAdd_fp, (void *) KerArg0);
			__CALL(KerParMatAdd_fp, KerArg0);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+29952+7488*((T0Ind_Total)%2)),
					_SC_Out, 3042, _LC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (936); _LC_Out = ((T0Ind_NextLast)?234:936); _SC_Out = (8*_LC_Out); 
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
	/* Shared L1: 44848 bytes, L2 buffer: 30768 bytes */
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
		[D1 Dim: Init: 16, Tiled: 1][Tile0 Dim: 2][D0 Dim: Init: 8, Tiled: 2]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 2 physical tiles
			Total Size: 12800 [D1, [0 x 12800, 12800]][Tile0, 2:[20x11, 20x9], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 12800, 12800]][Tile0, 2:[20x11, 20x9], 2]
		Tile0: [0, 7040, 440], Tile1: [440, 5760, 360], Tile2; [0, 7040, 440]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 32 [D1, [0 x 32, 32]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 32, 32]]
		Tile0: [0, 32, 32], Tile1: [0, 32, 32], Tile2; [0, 32, 32]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 2304 [D1, [0 x 2304, 2304]][D0, [1 x 1152, 1152]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 2304, 2304]][D0, [1 x 1152, 1152]]
		Tile0: [0, 2304, 2304], Tile1: [0, 2304, 2304], Tile2; [0, 2304, 2304]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 4 logical tiles, 4 physical tiles
			Total Size: 24336 [D0, [1 x 12168, 12168]][Tile0, 2:[39x22, 39x18], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 2:[39x22, 39x18], 2][D0, [1 x 12168, 12168]]
		Tile0: [0, 6864, 1716], Tile1: [12168, 6864, 1716], Tile2; [1638, 5616, 1404]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 25600 [D1, [0 x 25600, 25600]][Tile0, 2:[20x11, 20x9], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 25600, 25600]][Tile0, 2:[20x11, 20x9], 4]
		Tile0: [0, 14080, 880], Tile1: [0, 14080, 880], Tile2; [0, 14080, 880]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+30768);
	KerArg0->W = (unsigned short int) (20);
	KerArg0->OutFeatures = (unsigned short int) (16);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+14352);
	KerArg0->NormBias = (signed char) (12);
	KerArg1->W = (unsigned short int) (39);
	KerArg1->UsedW = (unsigned short int) (39);
	KerArg1->InFeatures = (unsigned short int) (4);
	KerArg1->OutFeatures = (unsigned short int) (16);
	KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+14384);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+30768);
	KerArg1->Norm = (unsigned char) (14);
	KerArg1->TotalInFeatures = (short int) (8);
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+30768);
	KerArg2->W = (unsigned short int) (20);
	KerArg2->Norm = (unsigned char) (14);
	KerArg2->InFeatures = (unsigned short int) (16);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	_C_Out=0; _SC_Out=7040; _LC_Out=440;
	_SP_Out=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+14352), 32, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+14384), 2304, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Filter */
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 6864, 3042, 1716, 0, &DmaR_Evt3);
	_N_In=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<2; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==1), T0Ind_NextLast = ((T0Ind+1)==1);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->H = (unsigned short int) (T0Ind_Last?9:11);
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<2; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==1), D0Ind_NextLast = ((D0Ind+1)==1);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (12168); _LN_In = ((T0Ind_Last)?1404:(1794-78*(T0Ind==0))); _SN_In = (4*_LN_In); 
				} else if (!(T0Ind_Last)) {
					_N_In = _N_In + (1716-(78*(T0Ind==0)))+(-12168); _LN_In = ((1)?1404:1794); _SN_In = (4*_LN_In); 
				} else if (!(1)) {
					_N_In = _N_In + (-1638)+(-12168); _LN_In = (1716); _SN_In = (4*_LN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+7176*((D0Ind_Total+1)%2)),
							_SN_In, 3042, _LN_In, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+7176*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (((T0Ind_Last)?18:23)-1*(T0Ind==0));
				KerArg1->UsedH = (unsigned short int) (((T0Ind_Last)?18:23)-1*(T0Ind==0));
				KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+14384+((D0Ind)*72));
				KerArg1->Pad = (v4s) ((v4s){1,1,1*(T0Ind==0),1*(T0Ind_Last)});
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride2_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride2_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->H = (unsigned short int) (T0Ind_Last?9:11);
			KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+16688+7040*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+16688+7040*((T0Ind_Total)%2)),
					_SC_Out, 800, _LC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (440); _LC_Out = ((1)?360:440); _SC_Out = (16*_LC_Out); 
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
	/* Shared L1: 44544 bytes, L2 buffer: 33024 bytes */
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
		[D1 Dim: Init: 16, Tiled: 1][Tile0 Dim: 3][D0 Dim: Init: 8, Tiled: 1]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 3 logical tiles, 3 physical tiles
			Total Size: 12800 [D1, [0 x 12800, 12800]][Tile0, 3:[20x9, 1:20x9, 20x2], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 12800, 12800]][Tile0, 3:[20x9, 1:20x9, 20x2], 2]
		Tile0: [0, 5760, 360], Tile1: [360, 5760, 360], Tile2; [720, 1280, 80]
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
		KerArgItSpace: 3 logical tiles, 3 physical tiles
			Total Size: 24336 [D0, [0 x 24336, 24336]][Tile0, 3:[39x17, 1:39x17, 39x3], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 3:[39x17], 2][D0, [0 x 24336, 24336]]
		Tile0: [0, 10608, 1326], Tile1: [1404, 10608, 1326], Tile2; [2808, 1872, 234]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 3 logical tiles, 1 physical tiles
			Total Size: 25600 [D1, [0 x 25600, 25600]][Tile0, 3:[20x9, 1:20x9, 20x2], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 25600, 25600]][Tile0, 3:[20x9, 1:20x9, 20x2], 4]
		Tile0: [0, 11520, 720], Tile1: [0, 11520, 720], Tile2; [0, 11520, 720]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+33024);
	KerArg0->W = (unsigned short int) (20);
	KerArg0->OutFeatures = (unsigned short int) (16);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+21216);
	KerArg0->NormBias = (signed char) (12);
	KerArg1->W = (unsigned short int) (39);
	KerArg1->UsedW = (unsigned short int) (39);
	KerArg1->InFeatures = (unsigned short int) (8);
	KerArg1->OutFeatures = (unsigned short int) (16);
	KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+21248);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+33024);
	KerArg1->Norm = (unsigned char) (14);
	KerArg1->TotalInFeatures = (short int) (8);
	KerArg1->Pad = (v4s) 0;
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+33024);
	KerArg2->W = (unsigned short int) (20);
	KerArg2->Norm = (unsigned char) (14);
	KerArg2->InFeatures = (unsigned short int) (16);
	KerArg2->LB = (int) (-32768);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	_C_Out=0; _SC_Out=5760; _LC_Out=360;
	_SP_Out=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+21216), 32, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+21248), 256, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Filter */
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 10608, 3042, 1326, 0, &DmaR_Evt3);
	_N_In=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<3; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==2), T0Ind_NextLast = ((T0Ind+1)==2);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->H = (unsigned short int) (T0Ind_Last?2:9);
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			{ /* Single iteration on D0 */
				int D0Ind_Last = 1, D0Ind_NextLast = 1;
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(T0Ind_Last)) {
					_N_In = _N_In + (1404); _LN_In = ((T0Ind_NextLast)?234:1326); _SN_In = (8*_LN_In); 
				} else if (!(1)) {
					_N_In = _N_In + (-2808); _LN_In = (1326); _SN_In = (8*_LN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+10608*((D0Ind_Total+1)%2)),
							_SN_In, 3042, _LN_In, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+10608*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (T0Ind_Last?3:17);
				KerArg1->UsedH = (unsigned short int) (T0Ind_Last?3:17);
				AT_FORK(gap_ncore(), (void *) KerParConv1x1Stride2_DP_fp, (void *) KerArg1);
				__CALL(KerParConv1x1Stride2_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				/*============================= End Update Arg Pipeline =============================*/
				D0Ind_Total++;
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->H = (unsigned short int) (T0Ind_Last?2:9);
			KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+21504+5760*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+21504+5760*((T0Ind_Total)%2)),
					_SC_Out, 800, _LC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (360); _LC_Out = ((T0Ind_NextLast)?80:360); _SC_Out = (16*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S27_Conv2d_16x16x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 45600 bytes, L2 buffer: 32800 bytes */
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
		[D1 Dim: Init: 16, Tiled: 1][Tile0 Dim: 2][D0 Dim: Init: 16, Tiled: 1]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 2 logical tiles, 2 physical tiles
			Total Size: 12800 [D0, [0 x 12800, 12800]][Tile0, 2:[20x11, 20x11], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 2:[20x10], 2][D0, [0 x 12800, 12800]]
		Tile0: [0, 7040, 440], Tile1: [360, 7040, 440], Tile2; [0, 7040, 440]
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
			Total Size: 4608 [D1, [0 x 4608, 4608]][D0, [0 x 4608, 4608]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 4608, 4608]][D0, [0 x 4608, 4608]]
		Tile0: [0, 4608, 4608], Tile1: [0, 4608, 4608], Tile2; [0, 4608, 4608]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 2 physical tiles
			Total Size: 12800 [D1, [0 x 12800, 12800]][Tile0, 2:[20x10, 20x10], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 12800, 12800]][Tile0, 2:[20x10, 20x10], 2]
		Tile0: [0, 6400, 400], Tile1: [400, 6400, 400], Tile2; [0, 6400, 400]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 25600 [D1, [0 x 25600, 25600]][Tile0, 2:[20x10, 20x10], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 25600, 25600]][Tile0, 2:[20x10, 20x10], 4]
		Tile0: [0, 12800, 800], Tile1: [0, 12800, 800], Tile2; [0, 12800, 800]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+32800);
	KerArg0->W = (unsigned short int) (20);
	KerArg0->H = (unsigned short int) (10);
	KerArg0->OutFeatures = (unsigned short int) (16);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+15360);
	KerArg0->NormBias = (signed char) (15);
	KerArg1->W = (unsigned short int) (20);
	KerArg1->UsedW = (unsigned short int) (20);
	KerArg1->InFeatures = (unsigned short int) (16);
	KerArg1->OutFeatures = (unsigned short int) (16);
	KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+15392);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+32800);
	KerArg1->Norm = (unsigned char) (15);
	KerArg1->TotalInFeatures = (short int) (16);
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+32800);
	KerArg2->W = (unsigned short int) (20);
	KerArg2->H = (unsigned short int) (10);
	KerArg2->Norm = (unsigned char) (15);
	KerArg2->InFeatures = (unsigned short int) (16);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 7040, 800, 440, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+15360), 32, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+15392), 4608, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
	_C_Out=0; _SC_Out=6400; _LC_Out=400;
	_SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<2; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==1), T0Ind_NextLast = ((T0Ind+1)==1);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			{ /* Single iteration on D0 */
				int D0Ind_Last = 1, D0Ind_NextLast = 1;
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(T0Ind_Last)) {
					_N_In = _N_In + (400-(40*(T0Ind==0))); _LN_In = ((1)?440:480); _SN_In = (16*_LN_In); 
				} else if (!(1)) {
					_N_In = _N_In + (-360); _LN_In = (440); _SN_In = (16*_LN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+7680*((D0Ind_Total+1)%2)),
							_SN_In, 800, _LN_In, 0, &DmaR_Evt1);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+7680*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (12-1*(T0Ind==0)-1*(T0Ind_Last));
				KerArg1->UsedH = (unsigned short int) (12-1*(T0Ind==0)-1*(T0Ind_Last));
				KerArg1->Pad = (v4s) ((v4s){1,1,1*(T0Ind==0),1*(T0Ind_Last)});
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				/*============================= End Update Arg Pipeline =============================*/
				D0Ind_Total++;
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+20000+6400*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+20000+6400*((T0Ind_Total)%2)),
					_SC_Out, 800, _LC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (400); _LC_Out = (400); _SC_Out = (16*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S28_MatAdd_16x20x20(
		short int * __restrict__ In1,
		short int * __restrict__ In2,
		short int * __restrict__ Out)

{
	/* Shared L1: 38400 bytes, L2 buffer: 38400 bytes */
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
		[D0 Dim: Init: 16, Tiled: 1][Tile0 Dim: 1]
	Ker Arg: In1, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 12800 [D0, [0 x 12800, 12800]][Tile0, 1:[20x20], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 12800, 12800]][Tile0, 1:[20x20], 2]
		Tile0: [0, 12800, 12800], Tile1: [0, 12800, 12800], Tile2; [0, 12800, 12800]
	Ker Arg: In2, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 12800 [D0, [0 x 12800, 12800]][Tile0, 1:[20x20], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 12800, 12800]][Tile0, 1:[20x20], 2]
		Tile0: [0, 12800, 12800], Tile1: [0, 12800, 12800], Tile2; [0, 12800, 12800]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 12800 [D0, [0 x 12800, 12800]][Tile0, 1:[20x20], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 12800, 12800]][Tile0, 1:[20x20], 2]
		Tile0: [0, 12800, 12800], Tile1: [0, 12800, 12800], Tile2; [0, 12800, 12800]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In1 = (short int *__restrict__) (resnet_L1_Memory+0);
	KerArg0->In2 = (short int *__restrict__) (resnet_L1_Memory+12800);
	KerArg0->Out = (short int *__restrict__) (resnet_L1_Memory+25600);
	KerArg0->W = (unsigned short int) (20);
	KerArg0->H = (unsigned short int) (20);
	KerArg0->N = (unsigned short int) (16);
	KerArg0->LB = (int) (-32768);
	KerArg0->UB = (int) (32767);
	KerArg0->In1_Q = (unsigned char) (12);
	KerArg0->In2_Q = (unsigned char) (11);
	KerArg0->Out_Q = (unsigned char) (11);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In1+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0), 12800, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In1 */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In2+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+12800), 12800, 0, &DmaR_Evt2);
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
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+25600), 12800, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S31_Conv2d_16x16x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 45600 bytes, L2 buffer: 32800 bytes */
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
		[D1 Dim: Init: 16, Tiled: 1][Tile0 Dim: 2][D0 Dim: Init: 16, Tiled: 1]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 2 logical tiles, 2 physical tiles
			Total Size: 12800 [D0, [0 x 12800, 12800]][Tile0, 2:[20x11, 20x11], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 2:[20x10], 2][D0, [0 x 12800, 12800]]
		Tile0: [0, 7040, 440], Tile1: [360, 7040, 440], Tile2; [0, 7040, 440]
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
			Total Size: 4608 [D1, [0 x 4608, 4608]][D0, [0 x 4608, 4608]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 4608, 4608]][D0, [0 x 4608, 4608]]
		Tile0: [0, 4608, 4608], Tile1: [0, 4608, 4608], Tile2; [0, 4608, 4608]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 2 physical tiles
			Total Size: 12800 [D1, [0 x 12800, 12800]][Tile0, 2:[20x10, 20x10], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 12800, 12800]][Tile0, 2:[20x10, 20x10], 2]
		Tile0: [0, 6400, 400], Tile1: [400, 6400, 400], Tile2; [0, 6400, 400]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 25600 [D1, [0 x 25600, 25600]][Tile0, 2:[20x10, 20x10], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 25600, 25600]][Tile0, 2:[20x10, 20x10], 4]
		Tile0: [0, 12800, 800], Tile1: [0, 12800, 800], Tile2; [0, 12800, 800]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+32800);
	KerArg0->W = (unsigned short int) (20);
	KerArg0->H = (unsigned short int) (10);
	KerArg0->OutFeatures = (unsigned short int) (16);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+15360);
	KerArg0->NormBias = (signed char) (12);
	KerArg1->W = (unsigned short int) (20);
	KerArg1->UsedW = (unsigned short int) (20);
	KerArg1->InFeatures = (unsigned short int) (16);
	KerArg1->OutFeatures = (unsigned short int) (16);
	KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+15392);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+32800);
	KerArg1->Norm = (unsigned char) (14);
	KerArg1->TotalInFeatures = (short int) (16);
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+32800);
	KerArg2->W = (unsigned short int) (20);
	KerArg2->H = (unsigned short int) (10);
	KerArg2->Norm = (unsigned char) (14);
	KerArg2->InFeatures = (unsigned short int) (16);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 7040, 800, 440, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+15360), 32, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+15392), 4608, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
	_C_Out=0; _SC_Out=6400; _LC_Out=400;
	_SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<2; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==1), T0Ind_NextLast = ((T0Ind+1)==1);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			{ /* Single iteration on D0 */
				int D0Ind_Last = 1, D0Ind_NextLast = 1;
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(T0Ind_Last)) {
					_N_In = _N_In + (400-(40*(T0Ind==0))); _LN_In = ((1)?440:480); _SN_In = (16*_LN_In); 
				} else if (!(1)) {
					_N_In = _N_In + (-360); _LN_In = (440); _SN_In = (16*_LN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+7680*((D0Ind_Total+1)%2)),
							_SN_In, 800, _LN_In, 0, &DmaR_Evt1);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+7680*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (12-1*(T0Ind==0)-1*(T0Ind_Last));
				KerArg1->UsedH = (unsigned short int) (12-1*(T0Ind==0)-1*(T0Ind_Last));
				KerArg1->Pad = (v4s) ((v4s){1,1,1*(T0Ind==0),1*(T0Ind_Last)});
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				/*============================= End Update Arg Pipeline =============================*/
				D0Ind_Total++;
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+20000+6400*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+20000+6400*((T0Ind_Total)%2)),
					_SC_Out, 800, _LC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (400); _LC_Out = (400); _SC_Out = (16*_LC_Out); 
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
	/* Shared L1: 45600 bytes, L2 buffer: 32800 bytes */
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
		[D1 Dim: Init: 16, Tiled: 1][Tile0 Dim: 2][D0 Dim: Init: 16, Tiled: 1]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 2 logical tiles, 2 physical tiles
			Total Size: 12800 [D0, [0 x 12800, 12800]][Tile0, 2:[20x11, 20x11], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 2:[20x10], 2][D0, [0 x 12800, 12800]]
		Tile0: [0, 7040, 440], Tile1: [360, 7040, 440], Tile2; [0, 7040, 440]
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
			Total Size: 4608 [D1, [0 x 4608, 4608]][D0, [0 x 4608, 4608]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 4608, 4608]][D0, [0 x 4608, 4608]]
		Tile0: [0, 4608, 4608], Tile1: [0, 4608, 4608], Tile2; [0, 4608, 4608]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 2 physical tiles
			Total Size: 12800 [D1, [0 x 12800, 12800]][Tile0, 2:[20x10, 20x10], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 12800, 12800]][Tile0, 2:[20x10, 20x10], 2]
		Tile0: [0, 6400, 400], Tile1: [400, 6400, 400], Tile2; [0, 6400, 400]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 25600 [D1, [0 x 25600, 25600]][Tile0, 2:[20x10, 20x10], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 25600, 25600]][Tile0, 2:[20x10, 20x10], 4]
		Tile0: [0, 12800, 800], Tile1: [0, 12800, 800], Tile2; [0, 12800, 800]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+32800);
	KerArg0->W = (unsigned short int) (20);
	KerArg0->H = (unsigned short int) (10);
	KerArg0->OutFeatures = (unsigned short int) (16);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+15360);
	KerArg0->NormBias = (signed char) (14);
	KerArg1->W = (unsigned short int) (20);
	KerArg1->UsedW = (unsigned short int) (20);
	KerArg1->InFeatures = (unsigned short int) (16);
	KerArg1->OutFeatures = (unsigned short int) (16);
	KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+15392);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+32800);
	KerArg1->Norm = (unsigned char) (16);
	KerArg1->TotalInFeatures = (short int) (16);
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+32800);
	KerArg2->W = (unsigned short int) (20);
	KerArg2->H = (unsigned short int) (10);
	KerArg2->Norm = (unsigned char) (16);
	KerArg2->InFeatures = (unsigned short int) (16);
	KerArg2->LB = (int) (-32768);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 7040, 800, 440, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+15360), 32, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+15392), 4608, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
	_C_Out=0; _SC_Out=6400; _LC_Out=400;
	_SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<2; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==1), T0Ind_NextLast = ((T0Ind+1)==1);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			{ /* Single iteration on D0 */
				int D0Ind_Last = 1, D0Ind_NextLast = 1;
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(T0Ind_Last)) {
					_N_In = _N_In + (400-(40*(T0Ind==0))); _LN_In = ((1)?440:480); _SN_In = (16*_LN_In); 
				} else if (!(1)) {
					_N_In = _N_In + (-360); _LN_In = (440); _SN_In = (16*_LN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+7680*((D0Ind_Total+1)%2)),
							_SN_In, 800, _LN_In, 0, &DmaR_Evt1);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+7680*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (12-1*(T0Ind==0)-1*(T0Ind_Last));
				KerArg1->UsedH = (unsigned short int) (12-1*(T0Ind==0)-1*(T0Ind_Last));
				KerArg1->Pad = (v4s) ((v4s){1,1,1*(T0Ind==0),1*(T0Ind_Last)});
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				/*============================= End Update Arg Pipeline =============================*/
				D0Ind_Total++;
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+20000+6400*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+20000+6400*((T0Ind_Total)%2)),
					_SC_Out, 800, _LC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (400); _LC_Out = (400); _SC_Out = (16*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S35_MatAdd_16x20x20(
		short int * __restrict__ In1,
		short int * __restrict__ In2,
		short int * __restrict__ Out)

{
	/* Shared L1: 38400 bytes, L2 buffer: 38400 bytes */
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
		[D0 Dim: Init: 16, Tiled: 1][Tile0 Dim: 1]
	Ker Arg: In1, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 12800 [D0, [0 x 12800, 12800]][Tile0, 1:[20x20], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 12800, 12800]][Tile0, 1:[20x20], 2]
		Tile0: [0, 12800, 12800], Tile1: [0, 12800, 12800], Tile2; [0, 12800, 12800]
	Ker Arg: In2, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 12800 [D0, [0 x 12800, 12800]][Tile0, 1:[20x20], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 12800, 12800]][Tile0, 1:[20x20], 2]
		Tile0: [0, 12800, 12800], Tile1: [0, 12800, 12800], Tile2; [0, 12800, 12800]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 12800 [D0, [0 x 12800, 12800]][Tile0, 1:[20x20], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 12800, 12800]][Tile0, 1:[20x20], 2]
		Tile0: [0, 12800, 12800], Tile1: [0, 12800, 12800], Tile2; [0, 12800, 12800]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In1 = (short int *__restrict__) (resnet_L1_Memory+0);
	KerArg0->In2 = (short int *__restrict__) (resnet_L1_Memory+12800);
	KerArg0->Out = (short int *__restrict__) (resnet_L1_Memory+25600);
	KerArg0->W = (unsigned short int) (20);
	KerArg0->H = (unsigned short int) (20);
	KerArg0->N = (unsigned short int) (16);
	KerArg0->LB = (int) (-32768);
	KerArg0->UB = (int) (32767);
	KerArg0->In1_Q = (unsigned char) (11);
	KerArg0->In2_Q = (unsigned char) (11);
	KerArg0->Out_Q = (unsigned char) (10);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In1+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0), 12800, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In1 */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In2+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+12800), 12800, 0, &DmaR_Evt2);
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
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+25600), 12800, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S38_Conv2d_32x16x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 41280 bytes, L2 buffer: 28480 bytes */
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
	int T0Ind, T0Ind_Last;
	int D0Ind, D0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 32, Tiled: 1][Tile0 Dim: 1][D0 Dim: Init: 16, Tiled: 1]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 12800 [D1, [0 x 12800, 12800]][Tile0, 1:[10x10], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 12800, 12800]][Tile0, 1:[10x10], 4]
		Tile0: [0, 12800, 400], Tile1: [0, 12800, 400], Tile2; [0, 12800, 400]
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
			Total Size: 9216 [D1, [0 x 9216, 9216]][D0, [0 x 9216, 9216]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 9216, 9216]][D0, [0 x 9216, 9216]]
		Tile0: [0, 9216, 9216], Tile1: [0, 9216, 9216], Tile2; [0, 9216, 9216]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 6400 [D1, [0 x 6400, 6400]][Tile0, 1:[10x10], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 6400, 6400]][Tile0, 1:[10x10], 2]
		Tile0: [0, 6400, 6400], Tile1: [0, 6400, 6400], Tile2; [0, 6400, 6400]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 12800 [D0, [0 x 12800, 12800]][Tile0, 1:[20x20], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[20x20], 2][D0, [0 x 12800, 12800]]
		Tile0: [0, 12800, 12800], Tile1: [0, 12800, 12800], Tile2; [0, 12800, 12800]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+28480);
	KerArg0->W = (unsigned short int) (10);
	KerArg0->H = (unsigned short int) (10);
	KerArg0->OutFeatures = (unsigned short int) (32);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+12800);
	KerArg0->NormBias = (signed char) (11);
	KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0);
	KerArg1->W = (unsigned short int) (20);
	KerArg1->UsedW = (unsigned short int) (20);
	KerArg1->H = (unsigned short int) (20);
	KerArg1->InFeatures = (unsigned short int) (16);
	KerArg1->OutFeatures = (unsigned short int) (32);
	KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+12864);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+28480);
	KerArg1->Norm = (unsigned char) (13);
	KerArg1->TotalInFeatures = (short int) (16);
	KerArg1->Pad = (v4s) ((v4s){0,1,0,1});
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+28480);
	KerArg2->W = (unsigned short int) (10);
	KerArg2->H = (unsigned short int) (10);
	KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+22080);
	KerArg2->Norm = (unsigned char) (13);
	KerArg2->InFeatures = (unsigned short int) (32);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+12800), 64, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+12864), 9216, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Filter */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0), 12800, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read In */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			{ /* Single iteration on D0 */
				int D0Ind_Last = 1;
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->UsedH = (unsigned short int) (20);
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride2_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride2_DP_fp, KerArg1);
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+22080), 6400, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S41_Conv2d_32x16x1x1(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 33088 bytes, L2 buffer: 20288 bytes */
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
	int T0Ind, T0Ind_Last;
	int D0Ind, D0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 32, Tiled: 1][Tile0 Dim: 1][D0 Dim: Init: 16, Tiled: 1]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 12800 [D1, [0 x 12800, 12800]][Tile0, 1:[10x10], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 12800, 12800]][Tile0, 1:[10x10], 4]
		Tile0: [0, 12800, 400], Tile1: [0, 12800, 400], Tile2; [0, 12800, 400]
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
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 6400 [D1, [0 x 6400, 6400]][Tile0, 1:[10x10], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 6400, 6400]][Tile0, 1:[10x10], 2]
		Tile0: [0, 6400, 6400], Tile1: [0, 6400, 6400], Tile2; [0, 6400, 6400]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 12800 [D0, [0 x 12800, 12800]][Tile0, 1:[20x19], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[20x19], 2][D0, [0 x 12800, 12800]]
		Tile0: [0, 12800, 12800], Tile1: [0, 12800, 12800], Tile2; [0, 12800, 12800]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+20288);
	KerArg0->W = (unsigned short int) (10);
	KerArg0->H = (unsigned short int) (10);
	KerArg0->OutFeatures = (unsigned short int) (32);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+12800);
	KerArg0->NormBias = (signed char) (11);
	KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0);
	KerArg1->W = (unsigned short int) (20);
	KerArg1->UsedW = (unsigned short int) (19);
	KerArg1->H = (unsigned short int) (20);
	KerArg1->InFeatures = (unsigned short int) (16);
	KerArg1->OutFeatures = (unsigned short int) (32);
	KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+12864);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+20288);
	KerArg1->Norm = (unsigned char) (14);
	KerArg1->TotalInFeatures = (short int) (16);
	KerArg1->Pad = (v4s) 0;
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+20288);
	KerArg2->W = (unsigned short int) (10);
	KerArg2->H = (unsigned short int) (10);
	KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+13888);
	KerArg2->Norm = (unsigned char) (14);
	KerArg2->InFeatures = (unsigned short int) (32);
	KerArg2->LB = (int) (-32768);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+12800), 64, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+12864), 1024, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Filter */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0), 12800, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read In */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			{ /* Single iteration on D0 */
				int D0Ind_Last = 1;
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->UsedH = (unsigned short int) (19);
				AT_FORK(gap_ncore(), (void *) KerParConv1x1Stride2_DP_fp, (void *) KerArg1);
				__CALL(KerParConv1x1Stride2_DP_fp, KerArg1);
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+13888), 6400, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S44_Conv2d_32x32x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 44096 bytes, L2 buffer: 31296 bytes */
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
	int T0Ind, T0Ind_Last;
	int D0Ind, D0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 32, Tiled: 1][Tile0 Dim: 1][D0 Dim: Init: 32, Tiled: 1]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 12800 [D1, [0 x 12800, 12800]][Tile0, 1:[10x10], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 12800, 12800]][Tile0, 1:[10x10], 4]
		Tile0: [0, 12800, 400], Tile1: [0, 12800, 400], Tile2; [0, 12800, 400]
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
			Total Size: 18432 [D1, [0 x 18432, 18432]][D0, [0 x 18432, 18432]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 18432, 18432]][D0, [0 x 18432, 18432]]
		Tile0: [0, 18432, 18432], Tile1: [0, 18432, 18432], Tile2; [0, 18432, 18432]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 6400 [D1, [0 x 6400, 6400]][Tile0, 1:[10x10], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 6400, 6400]][Tile0, 1:[10x10], 2]
		Tile0: [0, 6400, 6400], Tile1: [0, 6400, 6400], Tile2; [0, 6400, 6400]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 6400 [D0, [0 x 6400, 6400]][Tile0, 1:[10x10], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[10x10], 2][D0, [0 x 6400, 6400]]
		Tile0: [0, 6400, 6400], Tile1: [0, 6400, 6400], Tile2; [0, 6400, 6400]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+31296);
	KerArg0->W = (unsigned short int) (10);
	KerArg0->H = (unsigned short int) (10);
	KerArg0->OutFeatures = (unsigned short int) (32);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+6400);
	KerArg0->NormBias = (signed char) (14);
	KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0);
	KerArg1->W = (unsigned short int) (10);
	KerArg1->UsedW = (unsigned short int) (10);
	KerArg1->H = (unsigned short int) (10);
	KerArg1->InFeatures = (unsigned short int) (32);
	KerArg1->OutFeatures = (unsigned short int) (32);
	KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+6464);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+31296);
	KerArg1->Norm = (unsigned char) (14);
	KerArg1->TotalInFeatures = (short int) (32);
	KerArg1->Pad = (v4s) ((v4s){1,1,1,1});
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+31296);
	KerArg2->W = (unsigned short int) (10);
	KerArg2->H = (unsigned short int) (10);
	KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+24896);
	KerArg2->Norm = (unsigned char) (14);
	KerArg2->InFeatures = (unsigned short int) (32);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+6400), 64, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+6464), 18432, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Filter */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0), 6400, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read In */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			{ /* Single iteration on D0 */
				int D0Ind_Last = 1;
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->UsedH = (unsigned short int) (10);
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+24896), 6400, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S45_MatAdd_32x10x10(
		short int * __restrict__ In1,
		short int * __restrict__ In2,
		short int * __restrict__ Out)

{
	/* Shared L1: 19200 bytes, L2 buffer: 19200 bytes */
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
		[D0 Dim: Init: 32, Tiled: 1][Tile0 Dim: 1]
	Ker Arg: In1, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 6400 [D0, [0 x 6400, 6400]][Tile0, 1:[10x10], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 6400, 6400]][Tile0, 1:[10x10], 2]
		Tile0: [0, 6400, 6400], Tile1: [0, 6400, 6400], Tile2; [0, 6400, 6400]
	Ker Arg: In2, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 6400 [D0, [0 x 6400, 6400]][Tile0, 1:[10x10], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 6400, 6400]][Tile0, 1:[10x10], 2]
		Tile0: [0, 6400, 6400], Tile1: [0, 6400, 6400], Tile2; [0, 6400, 6400]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 6400 [D0, [0 x 6400, 6400]][Tile0, 1:[10x10], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 6400, 6400]][Tile0, 1:[10x10], 2]
		Tile0: [0, 6400, 6400], Tile1: [0, 6400, 6400], Tile2; [0, 6400, 6400]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In1 = (short int *__restrict__) (resnet_L1_Memory+0);
	KerArg0->In2 = (short int *__restrict__) (resnet_L1_Memory+6400);
	KerArg0->Out = (short int *__restrict__) (resnet_L1_Memory+12800);
	KerArg0->W = (unsigned short int) (10);
	KerArg0->H = (unsigned short int) (10);
	KerArg0->N = (unsigned short int) (32);
	KerArg0->LB = (int) (-32768);
	KerArg0->UB = (int) (32767);
	KerArg0->In1_Q = (unsigned char) (12);
	KerArg0->In2_Q = (unsigned char) (11);
	KerArg0->Out_Q = (unsigned char) (11);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In1+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0), 6400, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In1 */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In2+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+6400), 6400, 0, &DmaR_Evt2);
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
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+12800), 6400, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S48_Conv2d_32x32x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 44096 bytes, L2 buffer: 31296 bytes */
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
	int T0Ind, T0Ind_Last;
	int D0Ind, D0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 32, Tiled: 1][Tile0 Dim: 1][D0 Dim: Init: 32, Tiled: 1]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 12800 [D1, [0 x 12800, 12800]][Tile0, 1:[10x10], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 12800, 12800]][Tile0, 1:[10x10], 4]
		Tile0: [0, 12800, 400], Tile1: [0, 12800, 400], Tile2; [0, 12800, 400]
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
			Total Size: 18432 [D1, [0 x 18432, 18432]][D0, [0 x 18432, 18432]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 18432, 18432]][D0, [0 x 18432, 18432]]
		Tile0: [0, 18432, 18432], Tile1: [0, 18432, 18432], Tile2; [0, 18432, 18432]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 6400 [D1, [0 x 6400, 6400]][Tile0, 1:[10x10], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 6400, 6400]][Tile0, 1:[10x10], 2]
		Tile0: [0, 6400, 6400], Tile1: [0, 6400, 6400], Tile2; [0, 6400, 6400]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 6400 [D0, [0 x 6400, 6400]][Tile0, 1:[10x10], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[10x10], 2][D0, [0 x 6400, 6400]]
		Tile0: [0, 6400, 6400], Tile1: [0, 6400, 6400], Tile2; [0, 6400, 6400]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+31296);
	KerArg0->W = (unsigned short int) (10);
	KerArg0->H = (unsigned short int) (10);
	KerArg0->OutFeatures = (unsigned short int) (32);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+6400);
	KerArg0->NormBias = (signed char) (12);
	KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0);
	KerArg1->W = (unsigned short int) (10);
	KerArg1->UsedW = (unsigned short int) (10);
	KerArg1->H = (unsigned short int) (10);
	KerArg1->InFeatures = (unsigned short int) (32);
	KerArg1->OutFeatures = (unsigned short int) (32);
	KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+6464);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+31296);
	KerArg1->Norm = (unsigned char) (13);
	KerArg1->TotalInFeatures = (short int) (32);
	KerArg1->Pad = (v4s) ((v4s){1,1,1,1});
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+31296);
	KerArg2->W = (unsigned short int) (10);
	KerArg2->H = (unsigned short int) (10);
	KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+24896);
	KerArg2->Norm = (unsigned char) (13);
	KerArg2->InFeatures = (unsigned short int) (32);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+6400), 64, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+6464), 18432, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Filter */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0), 6400, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read In */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			{ /* Single iteration on D0 */
				int D0Ind_Last = 1;
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->UsedH = (unsigned short int) (10);
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+24896), 6400, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S51_Conv2d_32x32x3x3(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 44096 bytes, L2 buffer: 31296 bytes */
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
	int T0Ind, T0Ind_Last;
	int D0Ind, D0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 32, Tiled: 1][Tile0 Dim: 1][D0 Dim: Init: 32, Tiled: 1]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 12800 [D1, [0 x 12800, 12800]][Tile0, 1:[10x10], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 12800, 12800]][Tile0, 1:[10x10], 4]
		Tile0: [0, 12800, 400], Tile1: [0, 12800, 400], Tile2; [0, 12800, 400]
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
			Total Size: 18432 [D1, [0 x 18432, 18432]][D0, [0 x 18432, 18432]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 18432, 18432]][D0, [0 x 18432, 18432]]
		Tile0: [0, 18432, 18432], Tile1: [0, 18432, 18432], Tile2; [0, 18432, 18432]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 6400 [D1, [0 x 6400, 6400]][Tile0, 1:[10x10], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 6400, 6400]][Tile0, 1:[10x10], 2]
		Tile0: [0, 6400, 6400], Tile1: [0, 6400, 6400], Tile2; [0, 6400, 6400]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 6400 [D0, [0 x 6400, 6400]][Tile0, 1:[10x10], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[10x10], 2][D0, [0 x 6400, 6400]]
		Tile0: [0, 6400, 6400], Tile1: [0, 6400, 6400], Tile2; [0, 6400, 6400]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+31296);
	KerArg0->W = (unsigned short int) (10);
	KerArg0->H = (unsigned short int) (10);
	KerArg0->OutFeatures = (unsigned short int) (32);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+6400);
	KerArg0->NormBias = (signed char) (14);
	KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0);
	KerArg1->W = (unsigned short int) (10);
	KerArg1->UsedW = (unsigned short int) (10);
	KerArg1->H = (unsigned short int) (10);
	KerArg1->InFeatures = (unsigned short int) (32);
	KerArg1->OutFeatures = (unsigned short int) (32);
	KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+6464);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+31296);
	KerArg1->Norm = (unsigned char) (16);
	KerArg1->TotalInFeatures = (short int) (32);
	KerArg1->Pad = (v4s) ((v4s){1,1,1,1});
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+31296);
	KerArg2->W = (unsigned short int) (10);
	KerArg2->H = (unsigned short int) (10);
	KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+24896);
	KerArg2->Norm = (unsigned char) (16);
	KerArg2->InFeatures = (unsigned short int) (32);
	KerArg2->LB = (int) (-32768);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+6400), 64, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+6464), 18432, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Filter */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0), 6400, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read In */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			{ /* Single iteration on D0 */
				int D0Ind_Last = 1;
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->UsedH = (unsigned short int) (10);
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+24896), 6400, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S52_MatAdd_32x10x10(
		short int * __restrict__ In1,
		short int * __restrict__ In2,
		short int * __restrict__ Out)

{
	/* Shared L1: 19200 bytes, L2 buffer: 19200 bytes */
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
		[D0 Dim: Init: 32, Tiled: 1][Tile0 Dim: 1]
	Ker Arg: In1, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 6400 [D0, [0 x 6400, 6400]][Tile0, 1:[10x10], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 6400, 6400]][Tile0, 1:[10x10], 2]
		Tile0: [0, 6400, 6400], Tile1: [0, 6400, 6400], Tile2; [0, 6400, 6400]
	Ker Arg: In2, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 6400 [D0, [0 x 6400, 6400]][Tile0, 1:[10x10], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 6400, 6400]][Tile0, 1:[10x10], 2]
		Tile0: [0, 6400, 6400], Tile1: [0, 6400, 6400], Tile2; [0, 6400, 6400]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 6400 [D0, [0 x 6400, 6400]][Tile0, 1:[10x10], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 6400, 6400]][Tile0, 1:[10x10], 2]
		Tile0: [0, 6400, 6400], Tile1: [0, 6400, 6400], Tile2; [0, 6400, 6400]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In1 = (short int *__restrict__) (resnet_L1_Memory+0);
	KerArg0->In2 = (short int *__restrict__) (resnet_L1_Memory+6400);
	KerArg0->Out = (short int *__restrict__) (resnet_L1_Memory+12800);
	KerArg0->W = (unsigned short int) (10);
	KerArg0->H = (unsigned short int) (10);
	KerArg0->N = (unsigned short int) (32);
	KerArg0->LB = (int) (-32768);
	KerArg0->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In1+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0), 6400, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In1 */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In2+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+6400), 6400, 0, &DmaR_Evt2);
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
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+12800), 6400, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S55_Conv2d_64x32x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 42176 bytes, L2 buffer: 35776 bytes */
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
	int T0Ind, T0Ind_Last, T0Ind_NextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast;
	/* User kernel arguments related variables */
	unsigned int _N_Filter;
	unsigned int _SN_Filter;
	unsigned int _N_In;
	unsigned int _SN_In;
	unsigned int _LN_In;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 64, Tiled: 1][Tile0 Dim: 1][D0 Dim: Init: 32, Tiled: 3]
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
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 3 logical tiles, 3 physical tiles
			Total Size: 36864 [D1, [0 x 36864, 36864]][D0, [2 x 13824, 9216]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 36864, 36864]][D0, [2 x 13824, 9216]]
		Tile0: [0, 13824, 13824], Tile1: [13824, 13824, 13824], Tile2; [27648, 9216, 9216]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 3200 [D1, [0 x 3200, 3200]][Tile0, 1:[5x5], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 3200, 3200]][Tile0, 1:[5x5], 2]
		Tile0: [0, 3200, 3200], Tile1: [0, 3200, 3200], Tile2; [0, 3200, 3200]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 3 logical tiles, 3 physical tiles
			Total Size: 6400 [D0, [2 x 2400, 1600]][Tile0, 1:[10x10], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[10x11, 1:10x11, 10x10], 2][D0, [2 x 2400, 1600]]
		Tile0: [0, 2400, 200], Tile1: [2400, 2400, 200], Tile2; [4800, 1600, 200]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+35776);
	KerArg0->W = (unsigned short int) (5);
	KerArg0->H = (unsigned short int) (5);
	KerArg0->OutFeatures = (unsigned short int) (64);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+4800);
	KerArg0->NormBias = (signed char) (12);
	KerArg1->W = (unsigned short int) (10);
	KerArg1->UsedW = (unsigned short int) (10);
	KerArg1->OutFeatures = (unsigned short int) (64);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+35776);
	KerArg1->Norm = (unsigned char) (14);
	KerArg1->Pad = (v4s) ((v4s){0,1,0,1});
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+35776);
	KerArg2->W = (unsigned short int) (5);
	KerArg2->H = (unsigned short int) (5);
	KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+32576);
	KerArg2->Norm = (unsigned char) (14);
	KerArg2->InFeatures = (unsigned short int) (64);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+4800), 128, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+4928+0), 13824, 0, &DmaR_Evt2);
	_N_Filter=0;
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 2400, 200, 200, 0, &DmaR_Evt3);
	_N_In=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1, D1Ind_NextLast = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1, T0Ind_NextLast = 1;
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<3; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==2), D0Ind_NextLast = ((D0Ind+1)==2);
				/*================================= Prepare Tiles ===================================*/
				_SN_Filter = 0;
				if (!(D0Ind_Last)) {
					_N_Filter = _N_Filter + ((13824)); _SN_Filter = (((1)?(((D0Ind_NextLast)?9216:13824)):(((D0Ind_NextLast)?9216:13824)))); 
				} else if (!((1))) {
					_N_Filter = _N_Filter + ((-27648)); _SN_Filter = (((1)?(13824):(13824))); 
				}
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (2400); _LN_In = (200); _SN_In = (((D0Ind_NextLast)?8:12)*_LN_In); 
				} else if (!(1)) {
					_N_In = _N_In + (-4800); _LN_In = (200); _SN_In = (12*_LN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Filter */
				if (_SN_Filter) {
					AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+_N_Filter), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+4928+13824*((D0Ind_Total+1)%2)),
							_SN_Filter, 0, &DmaR_Evt2);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+2400*((D0Ind_Total+1)%2)),
							_SN_In, 200, _LN_In, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+2400*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (11-0*(1)-1*(1));
				KerArg1->UsedH = (unsigned short int) (11-0*(1)-1*(1));
				KerArg1->InFeatures = (unsigned short int) (D0Ind_Last?8:12);
				KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+4928+13824*((D0Ind_Total)%2));
				KerArg1->TotalInFeatures = (short int) (D0Ind_Last?8:12);
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride2_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride2_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+32576), 3200, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S58_Conv2d_64x32x1x1(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 20224 bytes, L2 buffer: 13824 bytes */
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
	int T0Ind, T0Ind_Last;
	int D0Ind, D0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 64, Tiled: 1][Tile0 Dim: 1][D0 Dim: Init: 32, Tiled: 1]
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
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 4096 [D1, [0 x 4096, 4096]][D0, [0 x 4096, 4096]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 4096, 4096]][D0, [0 x 4096, 4096]]
		Tile0: [0, 4096, 4096], Tile1: [0, 4096, 4096], Tile2; [0, 4096, 4096]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 3200 [D1, [0 x 3200, 3200]][Tile0, 1:[5x5], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 3200, 3200]][Tile0, 1:[5x5], 2]
		Tile0: [0, 3200, 3200], Tile1: [0, 3200, 3200], Tile2; [0, 3200, 3200]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 6400 [D0, [0 x 6400, 6400]][Tile0, 1:[10x9], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[10x9], 2][D0, [0 x 6400, 6400]]
		Tile0: [0, 6400, 6400], Tile1: [0, 6400, 6400], Tile2; [0, 6400, 6400]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+13824);
	KerArg0->W = (unsigned short int) (5);
	KerArg0->H = (unsigned short int) (5);
	KerArg0->OutFeatures = (unsigned short int) (64);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+6400);
	KerArg0->NormBias = (signed char) (11);
	KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0);
	KerArg1->W = (unsigned short int) (10);
	KerArg1->UsedW = (unsigned short int) (9);
	KerArg1->H = (unsigned short int) (10);
	KerArg1->InFeatures = (unsigned short int) (32);
	KerArg1->OutFeatures = (unsigned short int) (64);
	KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+6528);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+13824);
	KerArg1->Norm = (unsigned char) (14);
	KerArg1->TotalInFeatures = (short int) (32);
	KerArg1->Pad = (v4s) 0;
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+13824);
	KerArg2->W = (unsigned short int) (5);
	KerArg2->H = (unsigned short int) (5);
	KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+10624);
	KerArg2->Norm = (unsigned char) (14);
	KerArg2->InFeatures = (unsigned short int) (64);
	KerArg2->LB = (int) (-32768);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+6400), 128, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+6528), 4096, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Filter */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0), 6400, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read In */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			{ /* Single iteration on D0 */
				int D0Ind_Last = 1;
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->UsedH = (unsigned short int) (9);
				AT_FORK(gap_ncore(), (void *) KerParConv1x1Stride2_DP_fp, (void *) KerArg1);
				__CALL(KerParConv1x1Stride2_DP_fp, KerArg1);
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+10624), 3200, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S61_Conv2d_64x64x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 38576 bytes, L2 buffer: 32176 bytes */
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
	int T0Ind, T0Ind_Last, T0Ind_NextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast;
	/* User kernel arguments related variables */
	unsigned int _N_In;
	unsigned int _SN_In;
	unsigned int _LN_In;
	unsigned int _N_Filter;
	unsigned int _SN_Filter;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 64, Tiled: 1][Tile0 Dim: 1][D0 Dim: Init: 64, Tiled: 6]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 6 logical tiles, 6 physical tiles
			Total Size: 3200 [D0, [5 x 600, 200]][Tile0, 1:[5x5], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[5x6, 4:5x7, 5x6], 2][D0, [5 x 600, 200]]
		Tile0: [0, 600, 50], Tile1: [600, 600, 50], Tile2; [1200, 600, 50]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 128 [D1, [0 x 128, 128]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 128, 128]]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Filter, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 6 logical tiles, 6 physical tiles
			Total Size: 73728 [D1, [0 x 73728, 73728]][D0, [5 x 13824, 4608]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 73728, 73728]][D0, [5 x 13824, 4608]]
		Tile0: [0, 13824, 13824], Tile1: [13824, 13824, 13824], Tile2; [27648, 13824, 13824]
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
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+32176);
	KerArg0->W = (unsigned short int) (5);
	KerArg0->H = (unsigned short int) (5);
	KerArg0->OutFeatures = (unsigned short int) (64);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+1200);
	KerArg0->NormBias = (signed char) (13);
	KerArg1->W = (unsigned short int) (5);
	KerArg1->UsedW = (unsigned short int) (5);
	KerArg1->OutFeatures = (unsigned short int) (64);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+32176);
	KerArg1->Norm = (unsigned char) (14);
	KerArg1->Pad = (v4s) ((v4s){1,1,1,1});
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+32176);
	KerArg2->W = (unsigned short int) (5);
	KerArg2->H = (unsigned short int) (5);
	KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+28976);
	KerArg2->Norm = (unsigned char) (14);
	KerArg2->InFeatures = (unsigned short int) (64);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 600, 50, 50, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+1200), 128, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+1328+0), 13824, 0, &DmaR_Evt3);
	_N_Filter=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1, D1Ind_NextLast = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1, T0Ind_NextLast = 1;
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<6; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==5), D0Ind_NextLast = ((D0Ind+1)==5);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (600); _LN_In = (50); _SN_In = (((D0Ind_NextLast)?4:12)*_LN_In); 
				} else if (!(1)) {
					_N_In = _N_In + (-3000); _LN_In = (50); _SN_In = (12*_LN_In); 
				}
				_SN_Filter = 0;
				if (!(D0Ind_Last)) {
					_N_Filter = _N_Filter + ((13824)); _SN_Filter = (((1)?(((D0Ind_NextLast)?4608:13824)):(((D0Ind_NextLast)?4608:13824)))); 
				} else if (!((1))) {
					_N_Filter = _N_Filter + ((-69120)); _SN_Filter = (((1)?(13824):(13824))); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+600*((D0Ind_Total+1)%2)),
							_SN_In, 50, _LN_In, 0, &DmaR_Evt1);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
				if (_SN_Filter) {
					AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+_N_Filter), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+1328+13824*((D0Ind_Total+1)%2)),
							_SN_Filter, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+600*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (7-1*(1)-1*(1));
				KerArg1->UsedH = (unsigned short int) (7-1*(1)-1*(1));
				KerArg1->InFeatures = (unsigned short int) (D0Ind_Last?4:12);
				KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+1328+13824*((D0Ind_Total)%2));
				KerArg1->TotalInFeatures = (short int) (D0Ind_Last?4:12);
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+28976), 3200, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
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
void S65_Conv2d_64x64x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 38576 bytes, L2 buffer: 32176 bytes */
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
	int T0Ind, T0Ind_Last, T0Ind_NextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast;
	/* User kernel arguments related variables */
	unsigned int _N_In;
	unsigned int _SN_In;
	unsigned int _LN_In;
	unsigned int _N_Filter;
	unsigned int _SN_Filter;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 64, Tiled: 1][Tile0 Dim: 1][D0 Dim: Init: 64, Tiled: 6]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 6 logical tiles, 6 physical tiles
			Total Size: 3200 [D0, [5 x 600, 200]][Tile0, 1:[5x5], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[5x6, 4:5x7, 5x6], 2][D0, [5 x 600, 200]]
		Tile0: [0, 600, 50], Tile1: [600, 600, 50], Tile2; [1200, 600, 50]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 128 [D1, [0 x 128, 128]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 128, 128]]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Filter, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 6 logical tiles, 6 physical tiles
			Total Size: 73728 [D1, [0 x 73728, 73728]][D0, [5 x 13824, 4608]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 73728, 73728]][D0, [5 x 13824, 4608]]
		Tile0: [0, 13824, 13824], Tile1: [13824, 13824, 13824], Tile2; [27648, 13824, 13824]
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
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+32176);
	KerArg0->W = (unsigned short int) (5);
	KerArg0->H = (unsigned short int) (5);
	KerArg0->OutFeatures = (unsigned short int) (64);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+1200);
	KerArg0->NormBias = (signed char) (12);
	KerArg1->W = (unsigned short int) (5);
	KerArg1->UsedW = (unsigned short int) (5);
	KerArg1->OutFeatures = (unsigned short int) (64);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+32176);
	KerArg1->Norm = (unsigned char) (13);
	KerArg1->Pad = (v4s) ((v4s){1,1,1,1});
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+32176);
	KerArg2->W = (unsigned short int) (5);
	KerArg2->H = (unsigned short int) (5);
	KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+28976);
	KerArg2->Norm = (unsigned char) (13);
	KerArg2->InFeatures = (unsigned short int) (64);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 600, 50, 50, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+1200), 128, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+1328+0), 13824, 0, &DmaR_Evt3);
	_N_Filter=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1, D1Ind_NextLast = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1, T0Ind_NextLast = 1;
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<6; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==5), D0Ind_NextLast = ((D0Ind+1)==5);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (600); _LN_In = (50); _SN_In = (((D0Ind_NextLast)?4:12)*_LN_In); 
				} else if (!(1)) {
					_N_In = _N_In + (-3000); _LN_In = (50); _SN_In = (12*_LN_In); 
				}
				_SN_Filter = 0;
				if (!(D0Ind_Last)) {
					_N_Filter = _N_Filter + ((13824)); _SN_Filter = (((1)?(((D0Ind_NextLast)?4608:13824)):(((D0Ind_NextLast)?4608:13824)))); 
				} else if (!((1))) {
					_N_Filter = _N_Filter + ((-69120)); _SN_Filter = (((1)?(13824):(13824))); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+600*((D0Ind_Total+1)%2)),
							_SN_In, 50, _LN_In, 0, &DmaR_Evt1);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
				if (_SN_Filter) {
					AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+_N_Filter), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+1328+13824*((D0Ind_Total+1)%2)),
							_SN_Filter, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+600*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (7-1*(1)-1*(1));
				KerArg1->UsedH = (unsigned short int) (7-1*(1)-1*(1));
				KerArg1->InFeatures = (unsigned short int) (D0Ind_Last?4:12);
				KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+1328+13824*((D0Ind_Total)%2));
				KerArg1->TotalInFeatures = (short int) (D0Ind_Last?4:12);
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+28976), 3200, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S68_Conv2d_64x64x3x3(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 38576 bytes, L2 buffer: 32176 bytes */
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
	int T0Ind, T0Ind_Last, T0Ind_NextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast;
	/* User kernel arguments related variables */
	unsigned int _N_In;
	unsigned int _SN_In;
	unsigned int _LN_In;
	unsigned int _N_Filter;
	unsigned int _SN_Filter;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 64, Tiled: 1][Tile0 Dim: 1][D0 Dim: Init: 64, Tiled: 6]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 6 logical tiles, 6 physical tiles
			Total Size: 3200 [D0, [5 x 600, 200]][Tile0, 1:[5x5], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[5x6, 4:5x7, 5x6], 2][D0, [5 x 600, 200]]
		Tile0: [0, 600, 50], Tile1: [600, 600, 50], Tile2; [1200, 600, 50]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 128 [D1, [0 x 128, 128]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 128, 128]]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Filter, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 6 logical tiles, 6 physical tiles
			Total Size: 73728 [D1, [0 x 73728, 73728]][D0, [5 x 13824, 4608]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 73728, 73728]][D0, [5 x 13824, 4608]]
		Tile0: [0, 13824, 13824], Tile1: [13824, 13824, 13824], Tile2; [27648, 13824, 13824]
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
	KerArg0->Out = (int * __restrict__) (resnet_L1_Memory+32176);
	KerArg0->W = (unsigned short int) (5);
	KerArg0->H = (unsigned short int) (5);
	KerArg0->OutFeatures = (unsigned short int) (64);
	KerArg0->Bias = (short int * __restrict__) (resnet_L1_Memory+1200);
	KerArg0->NormBias = (signed char) (14);
	KerArg1->W = (unsigned short int) (5);
	KerArg1->UsedW = (unsigned short int) (5);
	KerArg1->OutFeatures = (unsigned short int) (64);
	KerArg1->Out = (int * __restrict__) (resnet_L1_Memory+32176);
	KerArg1->Norm = (unsigned char) (16);
	KerArg1->Pad = (v4s) ((v4s){1,1,1,1});
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (resnet_L1_Memory+32176);
	KerArg2->W = (unsigned short int) (5);
	KerArg2->H = (unsigned short int) (5);
	KerArg2->Out = (short int * __restrict__) (resnet_L1_Memory+28976);
	KerArg2->Norm = (unsigned char) (16);
	KerArg2->InFeatures = (unsigned short int) (64);
	KerArg2->LB = (int) (-32768);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+0), 600, 50, 50, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+1200), 128, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+1328+0), 13824, 0, &DmaR_Evt3);
	_N_Filter=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1, D1Ind_NextLast = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1, T0Ind_NextLast = 1;
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<6; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==5), D0Ind_NextLast = ((D0Ind+1)==5);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (600); _LN_In = (50); _SN_In = (((D0Ind_NextLast)?4:12)*_LN_In); 
				} else if (!(1)) {
					_N_In = _N_In + (-3000); _LN_In = (50); _SN_In = (12*_LN_In); 
				}
				_SN_Filter = 0;
				if (!(D0Ind_Last)) {
					_N_Filter = _N_Filter + ((13824)); _SN_Filter = (((1)?(((D0Ind_NextLast)?4608:13824)):(((D0Ind_NextLast)?4608:13824)))); 
				} else if (!((1))) {
					_N_Filter = _N_Filter + ((-69120)); _SN_Filter = (((1)?(13824):(13824))); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0+600*((D0Ind_Total+1)%2)),
							_SN_In, 50, _LN_In, 0, &DmaR_Evt1);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
				if (_SN_Filter) {
					AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+_N_Filter), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+1328+13824*((D0Ind_Total+1)%2)),
							_SN_Filter, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (resnet_L1_Memory+0+600*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (7-1*(1)-1*(1));
				KerArg1->UsedH = (unsigned short int) (7-1*(1)-1*(1));
				KerArg1->InFeatures = (unsigned short int) (D0Ind_Last?4:12);
				KerArg1->Filter = (short int * __restrict__) (resnet_L1_Memory+1328+13824*((D0Ind_Total)%2));
				KerArg1->TotalInFeatures = (short int) (D0Ind_Last?4:12);
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+28976), 3200, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
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
	KerArg0->In1_Q = (unsigned char) (12);
	KerArg0->In2_Q = (unsigned char) (11);
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
	KerArg0->Norm = (unsigned char) (16);
	KerArg0->NormBias = (signed char) (11);
	KerArg0->LB = (int) (-32768);
	KerArg0->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+0), 512, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) resnet_L1_Memory+512), 3584, 0, &DmaR_Evt2);
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
	KerArg0->Norm = (unsigned short int) (10);
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
	resnet_L3_Memory = (AT_HYPERRAM_POINTER) AT_HYPERRAM_ALLOC(&HyperRam, 323470);
	if (resnet_L3_Memory == 0) return 2;
	resnet_L2_Memory = (AT_L2_POINTER) AT_L2_ALLOC(0, 200000);
	if (resnet_L2_Memory == 0) return 3;
	resnet_L1_Memory = (AT_L1_POINTER) AT_L1_ALLOC(0, 46096);
	if (resnet_L1_Memory == 0) return 4;
	/* Moving Model_1res2cbranch2aconv2d_bia, size 16 from HyperFlash at 354208 to (size 16) HyperRam at 323424..323439 */
	{
		int Size = 16, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 354208+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 323424+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Res2cbranch2bkernel, size 1152 from HyperFlash at 349824 to (size 1152) HyperRam at 319872..321023 */
	{
		int Size = 1152, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 349824+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 319872+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Model_1res2cbranch2bconv2d_bia, size 16 from HyperFlash at 354224 to (size 16) HyperRam at 323440..323455 */
	{
		int Size = 16, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 354224+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 323440+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Res3a_branch2akernel, size 2304 from HyperFlash at 344064 to (size 2304) HyperRam at 316416..318719 */
	{
		int Size = 2304, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 344064+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 316416+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Model_1res3a_branch2aconv2d_bi, size 32 from HyperFlash at 354000 to (size 32) HyperRam at 323264..323295 */
	{
		int Size = 32, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 354000+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 323264+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Model_1res3a_branch1conv2d_bia, size 32 from HyperFlash at 354032 to (size 32) HyperRam at 323296..323327 */
	{
		int Size = 32, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 354032+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 323296+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Model_1res3a_branch2bconv2d_bi, size 32 from HyperFlash at 354064 to (size 32) HyperRam at 323328..323359 */
	{
		int Size = 32, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 354064+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 323328+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Model_1res3bbranch2aconv2d_bia, size 32 from HyperFlash at 354096 to (size 32) HyperRam at 323360..323391 */
	{
		int Size = 32, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 354096+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 323360+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Model_1res3bbranch2bconv2d_bia, size 32 from HyperFlash at 354128 to (size 32) HyperRam at 323392..323423 */
	{
		int Size = 32, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 354128+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 323392+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Model_1res4a_branch2aconv2d_bi, size 64 from HyperFlash at 353680 to (size 64) HyperRam at 322944..323007 */
	{
		int Size = 64, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 353680+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 322944+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Model_1res4a_branch1conv2d_bia, size 64 from HyperFlash at 353744 to (size 64) HyperRam at 323008..323071 */
	{
		int Size = 64, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 353744+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 323008+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Model_1res4a_branch2bconv2d_bi, size 64 from HyperFlash at 353808 to (size 64) HyperRam at 323072..323135 */
	{
		int Size = 64, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 353808+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 323072+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
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
	/* Moving Model_1res4bbranch2aconv2d_bia, size 64 from HyperFlash at 353872 to (size 64) HyperRam at 323136..323199 */
	{
		int Size = 64, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 353872+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 323136+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Model_1res4bbranch2bconv2d_bia, size 64 from HyperFlash at 353936 to (size 64) HyperRam at 323200..323263 */
	{
		int Size = 64, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 353936+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 323200+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Res5a_branch2bkernel, size 73728 from HyperFlash at 0 to (size 73728) HyperRam at 0..73727 */
	{
		int Size = 73728, Base = 0;
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
	/* Moving Model_1res5a_branch2bconv2d_bi, size 128 from HyperFlash at 353296 to (size 128) HyperRam at 322560..322687 */
	{
		int Size = 128, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 353296+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 322560+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Res5bbranch2akernel, size 73728 from HyperFlash at 73728 to (size 73728) HyperRam at 73728..147455 */
	{
		int Size = 73728, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 73728+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 73728+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Model_1res5bbranch2aconv2d_bia, size 128 from HyperFlash at 353424 to (size 128) HyperRam at 322688..322815 */
	{
		int Size = 128, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 353424+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 322688+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Res5bbranch2bkernel, size 73728 from HyperFlash at 147456 to (size 73728) HyperRam at 147456..221183 */
	{
		int Size = 73728, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 147456+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 147456+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Model_1res5bbranch2bconv2d_bia, size 128 from HyperFlash at 353552 to (size 128) HyperRam at 322816..322943 */
	{
		int Size = 128, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 353552+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 322816+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving M2weightedaveragematmul_bias, size 14 from HyperFlash at 354240 to (size 14) HyperRam at 323456..323469 */
	{
		int Size = 14, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 354240+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 323456+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving Conv1kernel, size 784 from HyperFlash at 352000 to (size 784) L2 at 66816..67599 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 352000), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 66816), 784, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Model_1conv1conv2d_bias, size 16 from HyperFlash at 354160 to (size 16) L2 at 67600..67615 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 354160), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 67600), 16, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Res2bbranch2akernel, size 1152 from HyperFlash at 346368 to (size 1152) L2 at 64512..65663 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 346368), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 64512), 1152, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Model_1res2bbranch2aconv2d_bia, size 16 from HyperFlash at 354176 to (size 16) L2 at 67616..67631 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 354176), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 67616), 16, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Res2bbranch2bkernel, size 1152 from HyperFlash at 347520 to (size 1152) L2 at 65664..66815 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 347520), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 65664), 1152, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Model_1res2bbranch2bconv2d_bia, size 16 from HyperFlash at 354192 to (size 16) L2 at 67632..67647 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 354192), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 67632), 16, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Res2cbranch2akernel, size 1152 from HyperFlash at 348672 to (size 1152) L2 at 109120..110271 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 348672), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 109120), 1152, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Res3a_branch1kernel, size 256 from HyperFlash at 352784 to (size 256) L2 at 3584..3839 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 352784), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 3584), 256, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Res3a_branch2bkernel, size 4608 from HyperFlash at 322560 to (size 4608) L2 at 104512..109119 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 322560), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 104512), 4608, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Res3bbranch2akernel, size 4608 from HyperFlash at 327168 to (size 4608) L2 at 22528..27135 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 327168), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 22528), 4608, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Res3bbranch2bkernel, size 4608 from HyperFlash at 331776 to (size 4608) L2 at 27136..31743 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 331776), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 27136), 4608, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Res4a_branch2akernel, size 9216 from HyperFlash at 313344 to (size 9216) L2 at 55296..64511 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 313344), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 55296), 9216, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Res4a_branch1kernel, size 1024 from HyperFlash at 350976 to (size 1024) L2 at 35840..36863 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 350976), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 35840), 1024, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Res4a_branch2bkernel, size 18432 from HyperFlash at 258048 to (size 18432) L2 at 4096..22527 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 258048), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 4096), 18432, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Res4bbranch2bkernel, size 18432 from HyperFlash at 294912 to (size 18432) L2 at 36864..55295 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 294912), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 36864), 18432, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Res5a_branch2akernel, size 36864 from HyperFlash at 221184 to (size 36864) L2 at 67648..104511 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 221184), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 67648), 36864, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Model_1res5a_branch2aconv2d_bi, size 128 from HyperFlash at 353040 to (size 128) L2 at 3840..3967 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 353040), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 3840), 128, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Res5a_branch1kernel, size 4096 from HyperFlash at 336384 to (size 4096) L2 at 31744..35839 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 336384), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 31744), 4096, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Model_1res5a_branch1conv2d_bia, size 128 from HyperFlash at 353168 to (size 128) L2 at 3968..4095 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 353168), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 3968), 128, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Weightedaveragekerneltranspose, size 3584 from HyperFlash at 340480 to (size 3584) L2 at 0..3583 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) resnet_L3_Flash + 340480), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) resnet_L2_Memory + 0), 3584, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	return 0;
}
int resnetCNN_Destruct()

{
	AT_HYPERRAM_FREE(&HyperRam, resnet_L3_Memory, 323470);
	AT_L2_FREE(0, resnet_L2_Memory, 200000);
	AT_L1_FREE(0, resnet_L1_Memory, 46096);
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
	/* Moving Model_1res2cbranch2aconv2d_bia, size 16 from HyperRam at 323424 to (size 16) L2 at 185584 using event 0 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 323424), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 185584), 16, 0, &UchanHR0);
	/* Moving Res2cbranch2bkernel, size 1152 from HyperRam at 319872 to (size 1152) L2 at 184432 using event 1 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 319872), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 184432), 1152, 0, &UchanHR1);
	/* Moving Model_1res2cbranch2bconv2d_bia, size 16 from HyperRam at 323440 to (size 16) L2 at 185600 using event 2 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 323440), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 185600), 16, 0, &UchanHR2);
	S4_Conv2d_8x1x7x7_MaxPool_3x3_Relu(
		((signed short * __restrict__) Input_1), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+66816)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+67600)), /* Bias */
		((signed short * __restrict__) (resnet_L2_Memory+110272)) /* Out */
	);
	S7_Conv2d_8x8x3x3_Relu(
		((signed short * __restrict__) (resnet_L2_Memory+110272)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+64512)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+67616)), /* Bias */
		((signed short * __restrict__) (resnet_L2_Memory+134608)) /* Out */
	);
	S10_Conv2d_8x8x3x3(
		((signed short * __restrict__) (resnet_L2_Memory+134608)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+65664)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+67632)), /* Bias */
		((signed short * __restrict__) (resnet_L2_Memory+158944)) /* Out */
	);
	S11_MatAdd_8x39x39(
		((signed short * __restrict__) (resnet_L2_Memory+158944)), /* In1 */
		((signed short * __restrict__) (resnet_L2_Memory+110272)), /* In2 */
		((signed short * __restrict__) (resnet_L2_Memory+134608)) /* Out */
	);
	/* Waiting completion of transfer of Model_1res2cbranch2aconv2d_bia using event 0 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR0);
	S14_Conv2d_8x8x3x3_Relu(
		((signed short * __restrict__) (resnet_L2_Memory+134608)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+109120)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+185584)), /* Bias */
		((signed short * __restrict__) (resnet_L2_Memory+110272)) /* Out */
	);
	/* Waiting completion of transfer of Res2cbranch2bkernel using event 1 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1);
	/* Waiting completion of transfer of Model_1res2cbranch2bconv2d_bia using event 2 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2);
	S17_Conv2d_8x8x3x3(
		((signed short * __restrict__) (resnet_L2_Memory+110272)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+184432)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+185600)), /* Bias */
		((signed short * __restrict__) (resnet_L2_Memory+158944)) /* Out */
	);
	/* Moving Res3a_branch2akernel, size 2304 from HyperRam at 316416 to (size 2304) L2 at 183280 using event 0 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 316416), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 183280), 2304, 0, &UchanHR0);
	/* Moving Model_1res3a_branch2aconv2d_bi, size 32 from HyperRam at 323264 to (size 32) L2 at 185584 using event 1 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 323264), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 185584), 32, 0, &UchanHR1);
	S18_MatAdd_8x39x39(
		((signed short * __restrict__) (resnet_L2_Memory+158944)), /* In1 */
		((signed short * __restrict__) (resnet_L2_Memory+134608)), /* In2 */
		((signed short * __restrict__) (resnet_L2_Memory+110272)) /* Out */
	);
	/* Moving Model_1res3a_branch1conv2d_bia, size 32 from HyperRam at 323296 to (size 32) L2 at 165072 using event 2 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 323296), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 165072), 32, 0, &UchanHR2);
	/* Moving Model_1res3a_branch2bconv2d_bi, size 32 from HyperRam at 323328 to (size 32) L2 at 165104 using event 3 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 323328), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 165104), 32, 0, &UchanHR3);
	/* Moving Model_1res3bbranch2aconv2d_bia, size 32 from HyperRam at 323360 to (size 32) L2 at 164816 using event 4 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 323360), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 164816), 32, 0, &UchanHR4);
	/* Waiting completion of transfer of Res3a_branch2akernel using event 0 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR0);
	/* Waiting completion of transfer of Model_1res3a_branch2aconv2d_bi using event 1 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1);
	S21_Conv2d_16x8x3x3_Relu(
		((signed short * __restrict__) (resnet_L2_Memory+110272)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+183280)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+185584)), /* Bias */
		((signed short * __restrict__) (resnet_L2_Memory+134608)) /* Out */
	);
	/* Waiting completion of transfer of Model_1res3a_branch2bconv2d_bi using event 3 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3);
	S27_Conv2d_16x16x3x3_Relu(
		((signed short * __restrict__) (resnet_L2_Memory+134608)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+104512)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+165104)), /* Bias */
		((signed short * __restrict__) (resnet_L2_Memory+147408)) /* Out */
	);
	/* Moving Model_1res4a_branch2aconv2d_bi, size 64 from HyperRam at 322944 to (size 64) L2 at 160704 using event 0 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 322944), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 160704), 64, 0, &UchanHR0);
	/* Waiting completion of transfer of Model_1res3a_branch1conv2d_bia using event 2 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2);
	S24_Conv2d_16x8x1x1(
		((signed short * __restrict__) (resnet_L2_Memory+110272)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+3584)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+165072)), /* Bias */
		((signed short * __restrict__) (resnet_L2_Memory+134608)) /* Out */
	);
	S28_MatAdd_16x20x20(
		((signed short * __restrict__) (resnet_L2_Memory+147408)), /* In1 */
		((signed short * __restrict__) (resnet_L2_Memory+134608)), /* In2 */
		((signed short * __restrict__) (resnet_L2_Memory+110272)) /* Out */
	);
	/* Moving Model_1res3bbranch2bconv2d_bia, size 32 from HyperRam at 323392 to (size 32) L2 at 153280 using event 1 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 323392), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 153280), 32, 0, &UchanHR1);
	/* Moving Model_1res4a_branch1conv2d_bia, size 64 from HyperRam at 323008 to (size 64) L2 at 161728 using event 2 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 323008), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 161728), 64, 0, &UchanHR2);
	/* Waiting completion of transfer of Model_1res3bbranch2aconv2d_bia using event 4 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR4);
	S31_Conv2d_16x16x3x3_Relu(
		((signed short * __restrict__) (resnet_L2_Memory+110272)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+22528)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+164816)), /* Bias */
		((signed short * __restrict__) (resnet_L2_Memory+123072)) /* Out */
	);
	/* Waiting completion of transfer of Model_1res3bbranch2bconv2d_bia using event 1 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1);
	S34_Conv2d_16x16x3x3(
		((signed short * __restrict__) (resnet_L2_Memory+123072)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+27136)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+153280)), /* Bias */
		((signed short * __restrict__) (resnet_L2_Memory+135872)) /* Out */
	);
	S35_MatAdd_16x20x20(
		((signed short * __restrict__) (resnet_L2_Memory+135872)), /* In1 */
		((signed short * __restrict__) (resnet_L2_Memory+110272)), /* In2 */
		((signed short * __restrict__) (resnet_L2_Memory+123072)) /* Out */
	);
	/* Moving Model_1res4a_branch2bconv2d_bi, size 64 from HyperRam at 323072 to (size 64) L2 at 116672 using event 1 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 323072), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 116672), 64, 0, &UchanHR1);
	/* Moving Res4bbranch2akernel, size 18432 from HyperRam at 276480 to (size 18432) L2 at 142272 using event 3 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 276480), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 142272), 18432, 0, &UchanHR3);
	/* Waiting completion of transfer of Model_1res4a_branch2aconv2d_bi using event 0 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR0);
	S38_Conv2d_32x16x3x3_Relu(
		((signed short * __restrict__) (resnet_L2_Memory+123072)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+55296)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+160704)), /* Bias */
		((signed short * __restrict__) (resnet_L2_Memory+110272)) /* Out */
	);
	/* Waiting completion of transfer of Model_1res4a_branch2bconv2d_bi using event 1 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1);
	S44_Conv2d_32x32x3x3_Relu(
		((signed short * __restrict__) (resnet_L2_Memory+110272)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+4096)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+116672)), /* Bias */
		((signed short * __restrict__) (resnet_L2_Memory+135872)) /* Out */
	);
	/* Waiting completion of transfer of Model_1res4a_branch1conv2d_bia using event 2 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2);
	S41_Conv2d_32x16x1x1(
		((signed short * __restrict__) (resnet_L2_Memory+123072)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+35840)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+161728)), /* Bias */
		((signed short * __restrict__) (resnet_L2_Memory+116672)) /* Out */
	);
	/* Moving Model_1res4bbranch2aconv2d_bia, size 64 from HyperRam at 323136 to (size 64) L2 at 123072 using event 0 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 323136), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 123072), 64, 0, &UchanHR0);
	/* Moving Model_1res4bbranch2bconv2d_bia, size 64 from HyperRam at 323200 to (size 64) L2 at 129472 using event 1 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 323200), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 129472), 64, 0, &UchanHR1);
	S45_MatAdd_32x10x10(
		((signed short * __restrict__) (resnet_L2_Memory+135872)), /* In1 */
		((signed short * __restrict__) (resnet_L2_Memory+116672)), /* In2 */
		((signed short * __restrict__) (resnet_L2_Memory+110272)) /* Out */
	);
	/* Waiting completion of transfer of Res4bbranch2akernel using event 3 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3);
	/* Waiting completion of transfer of Model_1res4bbranch2aconv2d_bia using event 0 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR0);
	S48_Conv2d_32x32x3x3_Relu(
		((signed short * __restrict__) (resnet_L2_Memory+110272)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+142272)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+123072)), /* Bias */
		((signed short * __restrict__) (resnet_L2_Memory+116672)) /* Out */
	);
	/* Waiting completion of transfer of Model_1res4bbranch2bconv2d_bia using event 1 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1);
	S51_Conv2d_32x32x3x3(
		((signed short * __restrict__) (resnet_L2_Memory+116672)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+36864)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+129472)), /* Bias */
		((signed short * __restrict__) (resnet_L2_Memory+123072)) /* Out */
	);
	S52_MatAdd_32x10x10(
		((signed short * __restrict__) (resnet_L2_Memory+123072)), /* In1 */
		((signed short * __restrict__) (resnet_L2_Memory+110272)), /* In2 */
		((signed short * __restrict__) (resnet_L2_Memory+116672)) /* Out */
	);
	/* Moving Res5a_branch2bkernel, size 73728 from HyperRam at 0 to (size 73728) L2 at 126272 using event 0 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 0), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 126272), 73728, 0, &UchanHR0);
	/* Moving Model_1res5a_branch2bconv2d_bi, size 128 from HyperRam at 322560 to (size 128) L2 at 113472 using event 1 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 322560), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 113472), 128, 0, &UchanHR1);
	S55_Conv2d_64x32x3x3_Relu(
		((signed short * __restrict__) (resnet_L2_Memory+116672)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+67648)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+3840)), /* Bias */
		((signed short * __restrict__) (resnet_L2_Memory+110272)) /* Out */
	);
	/* Waiting completion of transfer of Res5a_branch2bkernel using event 0 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR0);
	/* Waiting completion of transfer of Model_1res5a_branch2bconv2d_bi using event 1 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1);
	S61_Conv2d_64x64x3x3_Relu(
		((signed short * __restrict__) (resnet_L2_Memory+110272)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+126272)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+113472)), /* Bias */
		((signed short * __restrict__) (resnet_L2_Memory+123072)) /* Out */
	);
	/* Moving Res5bbranch2akernel, size 73728 from HyperRam at 73728 to (size 73728) L2 at 126272 using event 0 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 73728), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 126272), 73728, 0, &UchanHR0);
	S58_Conv2d_64x32x1x1(
		((signed short * __restrict__) (resnet_L2_Memory+116672)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+31744)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+3968)), /* Bias */
		((signed short * __restrict__) (resnet_L2_Memory+110272)) /* Out */
	);
	/* Moving Model_1res5bbranch2aconv2d_bia, size 128 from HyperRam at 322688 to (size 128) L2 at 116672 using event 1 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 322688), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 116672), 128, 0, &UchanHR1);
	S62_MatAdd_64x5x5(
		((signed short * __restrict__) (resnet_L2_Memory+123072)), /* In1 */
		((signed short * __restrict__) (resnet_L2_Memory+110272)), /* In2 */
		((signed short * __restrict__) (resnet_L2_Memory+113472)) /* Out */
	);
	/* Waiting completion of transfer of Res5bbranch2akernel using event 0 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR0);
	/* Waiting completion of transfer of Model_1res5bbranch2aconv2d_bia using event 1 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1);
	S65_Conv2d_64x64x3x3_Relu(
		((signed short * __restrict__) (resnet_L2_Memory+113472)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+126272)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+116672)), /* Bias */
		((signed short * __restrict__) (resnet_L2_Memory+110272)) /* Out */
	);
	/* Moving Res5bbranch2bkernel, size 73728 from HyperRam at 147456 to (size 73728) L2 at 123072 using event 0 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 147456), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 123072), 73728, 0, &UchanHR0);
	/* Moving Model_1res5bbranch2bconv2d_bia, size 128 from HyperRam at 322816 to (size 128) L2 at 116672 using event 1 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 322816), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 116672), 128, 0, &UchanHR1);
	/* Waiting completion of transfer of Res5bbranch2bkernel using event 0 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR0);
	/* Waiting completion of transfer of Model_1res5bbranch2bconv2d_bia using event 1 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1);
	S68_Conv2d_64x64x3x3(
		((signed short * __restrict__) (resnet_L2_Memory+110272)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+123072)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+116672)), /* Bias */
		((signed short * __restrict__) (resnet_L2_Memory+119872)) /* Out */
	);
	S69_MatAdd_64x5x5(
		((signed short * __restrict__) (resnet_L2_Memory+119872)), /* In1 */
		((signed short * __restrict__) (resnet_L2_Memory+113472)), /* In2 */
		((signed short * __restrict__) (resnet_L2_Memory+116672)) /* Out */
	);
	/* Moving M2weightedaveragematmul_bias, size 14 from HyperRam at 323456 to (size 14) L2 at 114384 using event 0 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) resnet_L3_Memory + 323456), ((AT_HYPERRAM_INT_ADDR_TYPE) resnet_L2_Memory + 114384), 14, 0, &UchanHR0);
	S70_AveragePool_2x2(
		((signed short * __restrict__) (resnet_L2_Memory+116672)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+110272)) /* Out */
	);
	/* Waiting completion of transfer of M2weightedaveragematmul_bias using event 0 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR0);
	S73_Linear_7x64x2x2(
		((signed short * __restrict__) (resnet_L2_Memory+110272)), /* In */
		((signed short * __restrict__) (resnet_L2_Memory+0)), /* Filter */
		((signed short * __restrict__) (resnet_L2_Memory+114384)), /* Bias */
		((signed short * __restrict__) (resnet_L2_Memory+110784)) /* Out */
	);
	S74_SoftMax(
		((signed short * __restrict__) (resnet_L2_Memory+110784)), /* In */
		((signed short * __restrict__) Output_1) /* Out */
	);
	return 0;
}
