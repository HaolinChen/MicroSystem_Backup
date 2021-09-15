#include "cnn_ssdKernels.h"
L1_CL_MEM AT_L1_POINTER cnn_ssd_L1_Memory;
L2_MEM AT_L2_POINTER cnn_ssd_L2_Memory;
AT_HYPERRAM_POINTER cnn_ssd_L3_Memory;
extern AT_HYPERRAM_T HyperRam;
static AT_HYPERFLASH_FS_T HyperFlash;
void S3_Conv2d_8x1x3x3_MaxPool_2x2_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 43680 bytes, L2 buffer: 12960 bytes */
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
		[D1 Dim: Init: 8, Tiled: 1][Tile0 Dim: 22][D0 Dim: Init: 1, Tiled: 1]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 22 logical tiles, 22 physical tiles
			Total Size: 81920 [D1, [0 x 81920, 81920]][Tile0, 22:[80x3, 20:80x3, 80x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 81920, 81920]][Tile0, 22:[80x3, 20:80x3, 80x1], 2]
		Tile0: [0, 3840, 480], Tile1: [480, 3840, 480], Tile2; [960, 3840, 480]
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
		KerArgItSpace: 22 logical tiles, 22 physical tiles
			Total Size: 40960 [D0, [0 x 40960, 40960]][Tile0, 22:[160x7, 20:160x8, 160x3], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 22:[160x6], 2][D0, [0 x 40960, 40960]]
		Tile0: [0, 2240, 2240], Tile1: [1600, 2560, 2560], Tile2; [3520, 2560, 2560]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 22 logical tiles, 1 physical tiles
			Total Size: 655360 [D1, [0 x 655360, 655360]][Tile0, 22:[160x6, 20:160x6, 160x2], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 655360, 655360]][Tile0, 22:[160x6, 20:160x6, 160x2], 4]
		Tile0: [0, 30720, 3840], Tile1: [0, 30720, 3840], Tile2; [0, 30720, 3840]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (cnn_ssd_L1_Memory+12960);
	KerArg0->W = (unsigned short int) (160);
	KerArg0->OutFeatures = (unsigned short int) (8);
	KerArg0->Bias = (short int * __restrict__) (cnn_ssd_L1_Memory+5120);
	KerArg0->NormBias = (signed char) (12);
	KerArg1->W = (unsigned short int) (160);
	KerArg1->UsedW = (unsigned short int) (160);
	KerArg1->InFeatures = (unsigned short int) (1);
	KerArg1->OutFeatures = (unsigned short int) (8);
	KerArg1->Filter = (short int * __restrict__) (cnn_ssd_L1_Memory+5136);
	KerArg1->Out = (int * __restrict__) (cnn_ssd_L1_Memory+12960);
	KerArg1->Norm = (unsigned char) (15);
	KerArg1->TotalInFeatures = (short int) (1);
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (cnn_ssd_L1_Memory+12960);
	KerArg2->W = (unsigned short int) (160);
	KerArg2->Out = (short int * __restrict__) (cnn_ssd_L1_Memory+12960);
	KerArg2->Norm = (unsigned char) (15);
	KerArg2->InFeatures = (unsigned short int) (8);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	KerArg3->In = (short int * __restrict__) (cnn_ssd_L1_Memory+12960);
	KerArg3->W = (unsigned short int) (160);
	KerArg3->UsedW = (unsigned short int) (160);
	KerArg3->OutFeatures = (unsigned short int) (8);
	KerArg3->Pad = (v4s) 0;
	KerArg3->Orientation = (unsigned char) (1);
	KerArg3->Oper = (unsigned char) (1);
	KerArg3->LB = (int) (0);
	KerArg3->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	_C_Out=0; _SC_Out=3840; _LC_Out=480;
	_SP_Out=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+5120), 16, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+5136), 144, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Filter */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+0), 2240, 0, &DmaR_Evt3);
	_N_In=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<22; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==21), T0Ind_NextLast = ((T0Ind+1)==21);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->H = (unsigned short int) (T0Ind_Last?2:6);
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			{ /* Single iteration on D0 */
				int D0Ind_Last = 1, D0Ind_NextLast = 1;
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(T0Ind_Last)) {
					_N_In = _N_In + (1920-(320*(T0Ind==0))); _SN_In = (1*((T0Ind_NextLast)?960:2560)); 
				} else if (!(1)) {
					_N_In = _N_In + (-40000); _SN_In = (1*(2240)); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+2560*((D0Ind_Total+1)%2)),
							_SN_In, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (cnn_ssd_L1_Memory+0+2560*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (((T0Ind_Last)?3:8)-1*(T0Ind==0));
				KerArg1->UsedH = (unsigned short int) (((T0Ind_Last)?3:8)-1*(T0Ind==0));
				KerArg1->Pad = (v4s) ((v4s){1,1,1*(T0Ind==0),1*(T0Ind_Last)});
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				/*============================= End Update Arg Pipeline =============================*/
				D0Ind_Total++;
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->H = (unsigned short int) (T0Ind_Last?2:6);
			AT_FORK(gap_ncore(), (void *) KerDP_IO_fp, (void *) KerArg2);
			__CALL(KerDP_IO_fp, KerArg2);
			KerArg3->H = (unsigned short int) (T0Ind_Last?2:6);
			KerArg3->UsedH = (unsigned short int) (T0Ind_Last?2:6);
			KerArg3->Out = (short int * __restrict__) (cnn_ssd_L1_Memory+5280+3840*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerParPool2x2Stride2_fp, (void *) KerArg3);
			__CALL(KerParPool2x2Stride2_fp, KerArg3);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+5280+3840*((T0Ind_Total)%2)),
					_SC_Out, 10240, _LC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (480); _LC_Out = ((T0Ind_NextLast)?160:480); _SC_Out = (8*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S6_Conv2d_16x8x3x3_MaxPool_2x2_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 45856 bytes, L2 buffer: 15136 bytes */
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
	unsigned int _LN_In;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 16, Tiled: 1][Tile0 Dim: 11][D0 Dim: Init: 8, Tiled: 4]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 11 logical tiles, 11 physical tiles
			Total Size: 40960 [D1, [0 x 40960, 40960]][Tile0, 11:[40x3, 9:40x3, 40x2], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 40960, 40960]][Tile0, 11:[40x3, 9:40x3, 40x2], 2]
		Tile0: [0, 3840, 240], Tile1: [240, 3840, 240], Tile2; [480, 3840, 240]
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
		KerArgItSpace: 44 logical tiles, 44 physical tiles
			Total Size: 81920 [D0, [3 x 20480, 20480]][Tile0, 11:[80x7, 9:80x8, 80x5], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 11:[80x7, 2:80x8, 80x5], 2][D0, [3 x 20480, 20480]]
		Tile0: [0, 2240, 1120], Tile1: [20480, 2240, 1120], Tile2; [40960, 2240, 1120]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 11 logical tiles, 1 physical tiles
			Total Size: 327680 [D1, [0 x 327680, 327680]][Tile0, 11:[80x6, 9:80x6, 80x4], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 327680, 327680]][Tile0, 11:[80x6, 9:80x6, 80x4], 4]
		Tile0: [0, 30720, 1920], Tile1: [0, 30720, 1920], Tile2; [0, 30720, 1920]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (cnn_ssd_L1_Memory+15136);
	KerArg0->W = (unsigned short int) (80);
	KerArg0->OutFeatures = (unsigned short int) (16);
	KerArg0->Bias = (short int * __restrict__) (cnn_ssd_L1_Memory+5120);
	KerArg0->NormBias = (signed char) (10);
	KerArg1->W = (unsigned short int) (80);
	KerArg1->UsedW = (unsigned short int) (80);
	KerArg1->InFeatures = (unsigned short int) (2);
	KerArg1->OutFeatures = (unsigned short int) (16);
	KerArg1->Filter = (short int * __restrict__) (cnn_ssd_L1_Memory+5152);
	KerArg1->Out = (int * __restrict__) (cnn_ssd_L1_Memory+15136);
	KerArg1->Norm = (unsigned char) (13);
	KerArg1->TotalInFeatures = (short int) (8);
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (cnn_ssd_L1_Memory+15136);
	KerArg2->W = (unsigned short int) (80);
	KerArg2->Out = (short int * __restrict__) (cnn_ssd_L1_Memory+15136);
	KerArg2->Norm = (unsigned char) (13);
	KerArg2->InFeatures = (unsigned short int) (16);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	KerArg3->In = (short int * __restrict__) (cnn_ssd_L1_Memory+15136);
	KerArg3->W = (unsigned short int) (80);
	KerArg3->UsedW = (unsigned short int) (80);
	KerArg3->OutFeatures = (unsigned short int) (16);
	KerArg3->Pad = (v4s) 0;
	KerArg3->Orientation = (unsigned char) (1);
	KerArg3->Oper = (unsigned char) (1);
	KerArg3->LB = (int) (0);
	KerArg3->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	_C_Out=0; _SC_Out=3840; _LC_Out=240;
	_SP_Out=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+5120), 32, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+5152), 2304, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Filter */
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+0), 2240, 10240, 1120, 0, &DmaR_Evt3);
	_N_In=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<11; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==10), T0Ind_NextLast = ((T0Ind+1)==10);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->H = (unsigned short int) (T0Ind_Last?4:6);
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<4; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==3), D0Ind_NextLast = ((D0Ind+1)==3);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (20480); _LN_In = ((T0Ind_Last)?800:(1280-160*(T0Ind==0))); _SN_In = (2*_LN_In); 
				} else if (!(T0Ind_Last)) {
					_N_In = _N_In + (960-(160*(T0Ind==0)))+(-61440); _LN_In = ((T0Ind_NextLast)?800:1280); _SN_In = (2*_LN_In); 
				} else if (!(1)) {
					_N_In = _N_In + (-9440)+(-61440); _LN_In = (1120); _SN_In = (2*_LN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+2560*((D0Ind_Total+1)%2)),
							_SN_In, 10240, _LN_In, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (cnn_ssd_L1_Memory+0+2560*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (((T0Ind_Last)?5:8)-1*(T0Ind==0));
				KerArg1->UsedH = (unsigned short int) (((T0Ind_Last)?5:8)-1*(T0Ind==0));
				KerArg1->Filter = (short int * __restrict__) (cnn_ssd_L1_Memory+5152+((D0Ind)*36));
				KerArg1->Pad = (v4s) ((v4s){1,1,1*(T0Ind==0),1*(T0Ind_Last)});
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->H = (unsigned short int) (T0Ind_Last?4:6);
			AT_FORK(gap_ncore(), (void *) KerDP_IO_fp, (void *) KerArg2);
			__CALL(KerDP_IO_fp, KerArg2);
			KerArg3->H = (unsigned short int) (T0Ind_Last?4:6);
			KerArg3->UsedH = (unsigned short int) (T0Ind_Last?4:6);
			KerArg3->Out = (short int * __restrict__) (cnn_ssd_L1_Memory+7456+3840*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerParPool2x2Stride2_fp, (void *) KerArg3);
			__CALL(KerParPool2x2Stride2_fp, KerArg3);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+7456+3840*((T0Ind_Total)%2)),
					_SC_Out, 2560, _LC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (240); _LC_Out = ((T0Ind_NextLast)?160:240); _SC_Out = (16*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S9_Conv2d_16x16x3x3_MaxPool_2x2_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 47520 bytes, L2 buffer: 16800 bytes */
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
	unsigned int _LN_In;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 16, Tiled: 1][Tile0 Dim: 3][D0 Dim: Init: 16, Tiled: 8]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 3 logical tiles, 3 physical tiles
			Total Size: 10240 [D1, [0 x 10240, 10240]][Tile0, 3:[20x6, 1:20x6, 20x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 10240, 10240]][Tile0, 3:[20x6, 1:20x6, 20x4], 2]
		Tile0: [0, 3840, 240], Tile1: [240, 3840, 240], Tile2; [480, 2560, 160]
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
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 24 logical tiles, 24 physical tiles
			Total Size: 40960 [D0, [7 x 5120, 5120]][Tile0, 3:[40x13, 1:40x14, 40x9], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 3:[40x13, 6:40x14, 40x9], 2][D0, [7 x 5120, 5120]]
		Tile0: [0, 2080, 1040], Tile1: [5120, 2080, 1040], Tile2; [10240, 2080, 1040]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 3 logical tiles, 1 physical tiles
			Total Size: 81920 [D1, [0 x 81920, 81920]][Tile0, 3:[40x12, 1:40x12, 40x8], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 81920, 81920]][Tile0, 3:[40x12, 1:40x12, 40x8], 4]
		Tile0: [0, 30720, 1920], Tile1: [0, 30720, 1920], Tile2; [0, 30720, 1920]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (cnn_ssd_L1_Memory+16800);
	KerArg0->W = (unsigned short int) (40);
	KerArg0->OutFeatures = (unsigned short int) (16);
	KerArg0->Bias = (short int * __restrict__) (cnn_ssd_L1_Memory+4480);
	KerArg0->NormBias = (signed char) (13);
	KerArg1->W = (unsigned short int) (40);
	KerArg1->UsedW = (unsigned short int) (40);
	KerArg1->InFeatures = (unsigned short int) (2);
	KerArg1->OutFeatures = (unsigned short int) (16);
	KerArg1->Filter = (short int * __restrict__) (cnn_ssd_L1_Memory+4512);
	KerArg1->Out = (int * __restrict__) (cnn_ssd_L1_Memory+16800);
	KerArg1->Norm = (unsigned char) (14);
	KerArg1->TotalInFeatures = (short int) (16);
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (cnn_ssd_L1_Memory+16800);
	KerArg2->W = (unsigned short int) (40);
	KerArg2->Out = (short int * __restrict__) (cnn_ssd_L1_Memory+16800);
	KerArg2->Norm = (unsigned char) (14);
	KerArg2->InFeatures = (unsigned short int) (16);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	KerArg3->In = (short int * __restrict__) (cnn_ssd_L1_Memory+16800);
	KerArg3->W = (unsigned short int) (40);
	KerArg3->UsedW = (unsigned short int) (40);
	KerArg3->OutFeatures = (unsigned short int) (16);
	KerArg3->Pad = (v4s) 0;
	KerArg3->Orientation = (unsigned char) (1);
	KerArg3->Oper = (unsigned char) (1);
	KerArg3->LB = (int) (0);
	KerArg3->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	_C_Out=0; _SC_Out=3840; _LC_Out=240;
	_SP_Out=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+4480), 32, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+4512), 4608, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Filter */
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+0), 2080, 2560, 1040, 0, &DmaR_Evt3);
	_N_In=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<3; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==2), T0Ind_NextLast = ((T0Ind+1)==2);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->H = (unsigned short int) (T0Ind_Last?8:12);
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<8; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==7), D0Ind_NextLast = ((D0Ind+1)==7);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (5120); _LN_In = ((T0Ind_Last)?720:(1120-80*(T0Ind==0))); _SN_In = (2*_LN_In); 
				} else if (!(T0Ind_Last)) {
					_N_In = _N_In + (960-(80*(T0Ind==0)))+(-35840); _LN_In = ((T0Ind_NextLast)?720:1120); _SN_In = (2*_LN_In); 
				} else if (!(1)) {
					_N_In = _N_In + (-1840)+(-35840); _LN_In = (1040); _SN_In = (2*_LN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+2240*((D0Ind_Total+1)%2)),
							_SN_In, 2560, _LN_In, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (cnn_ssd_L1_Memory+0+2240*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (((T0Ind_Last)?9:14)-1*(T0Ind==0));
				KerArg1->UsedH = (unsigned short int) (((T0Ind_Last)?9:14)-1*(T0Ind==0));
				KerArg1->Filter = (short int * __restrict__) (cnn_ssd_L1_Memory+4512+((D0Ind)*36));
				KerArg1->Pad = (v4s) ((v4s){1,1,1*(T0Ind==0),1*(T0Ind_Last)});
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->H = (unsigned short int) (T0Ind_Last?8:12);
			AT_FORK(gap_ncore(), (void *) KerDP_IO_fp, (void *) KerArg2);
			__CALL(KerDP_IO_fp, KerArg2);
			KerArg3->H = (unsigned short int) (T0Ind_Last?8:12);
			KerArg3->UsedH = (unsigned short int) (T0Ind_Last?8:12);
			KerArg3->Out = (short int * __restrict__) (cnn_ssd_L1_Memory+9120+3840*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerParPool2x2Stride2_fp, (void *) KerArg3);
			__CALL(KerParPool2x2Stride2_fp, KerArg3);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+9120+3840*((T0Ind_Total)%2)),
					_SC_Out, 640, _LC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (240); _LC_Out = ((T0Ind_NextLast)?160:240); _SC_Out = (16*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S12_Conv2d_32x16x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 47680 bytes, L2 buffer: 32320 bytes */
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
		[D1 Dim: Init: 32, Tiled: 1][Tile0 Dim: 3][D0 Dim: Init: 16, Tiled: 2]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 6 logical tiles, 6 physical tiles
			Total Size: 10240 [D0, [1 x 7680, 2560]][Tile0, 3:[20x7, 1:20x8, 20x5], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 3:[20x7, 20x5], 2][D0, [1 x 7680, 2560]]
		Tile0: [0, 3360, 280], Tile1: [7680, 1120, 280], Tile2; [200, 3840, 320]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 64 [D1, [0 x 64, 64]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 64, 64]]
		Tile0: [0, 64, 64], Tile1: [0, 64, 64], Tile2; [0, 64, 64]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 9216 [D1, [0 x 9216, 9216]][D0, [1 x 6912, 2304]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 9216, 9216]][D0, [1 x 6912, 2304]]
		Tile0: [0, 9216, 9216], Tile1: [0, 9216, 9216], Tile2; [0, 9216, 9216]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 3 logical tiles, 3 physical tiles
			Total Size: 20480 [D1, [0 x 20480, 20480]][Tile0, 3:[20x6, 1:20x6, 20x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 20480, 20480]][Tile0, 3:[20x6, 1:20x6, 20x4], 2]
		Tile0: [0, 7680, 240], Tile1: [240, 7680, 240], Tile2; [480, 5120, 160]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 3 logical tiles, 1 physical tiles
			Total Size: 40960 [D1, [0 x 40960, 40960]][Tile0, 3:[20x6, 1:20x6, 20x4], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 40960, 40960]][Tile0, 3:[20x6, 1:20x6, 20x4], 4]
		Tile0: [0, 15360, 480], Tile1: [0, 15360, 480], Tile2; [0, 15360, 480]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (cnn_ssd_L1_Memory+32320);
	KerArg0->W = (unsigned short int) (20);
	KerArg0->OutFeatures = (unsigned short int) (32);
	KerArg0->Bias = (short int * __restrict__) (cnn_ssd_L1_Memory+7680);
	KerArg0->NormBias = (signed char) (13);
	KerArg1->W = (unsigned short int) (20);
	KerArg1->UsedW = (unsigned short int) (20);
	KerArg1->OutFeatures = (unsigned short int) (32);
	KerArg1->Filter = (short int * __restrict__) (cnn_ssd_L1_Memory+7744);
	KerArg1->Out = (int * __restrict__) (cnn_ssd_L1_Memory+32320);
	KerArg1->Norm = (unsigned char) (14);
	KerArg1->TotalInFeatures = (short int) (16);
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (cnn_ssd_L1_Memory+32320);
	KerArg2->W = (unsigned short int) (20);
	KerArg2->Norm = (unsigned char) (14);
	KerArg2->InFeatures = (unsigned short int) (32);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+0), 3360, 640, 280, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+7680), 64, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+7744), 9216, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
	_C_Out=0; _SC_Out=7680; _LC_Out=240;
	_SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<3; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==2), T0Ind_NextLast = ((T0Ind+1)==2);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->H = (unsigned short int) (T0Ind_Last?4:6);
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<2; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==1), D0Ind_NextLast = ((D0Ind+1)==1);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (7680); _LN_In = ((T0Ind_Last)?200:(320-40*(T0Ind==0))); _SN_In = (((1)?4:12)*_LN_In); 
				} else if (!(T0Ind_Last)) {
					_N_In = _N_In + (240-(40*(T0Ind==0)))+(-7680); _LN_In = ((T0Ind_NextLast)?200:320); _SN_In = (12*_LN_In); 
				} else if (!(1)) {
					_N_In = _N_In + (-440)+(-7680); _LN_In = (280); _SN_In = (12*_LN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+3840*((D0Ind_Total+1)%2)),
							_SN_In, 640, _LN_In, 0, &DmaR_Evt1);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (cnn_ssd_L1_Memory+0+3840*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (((T0Ind_Last)?5:8)-1*(T0Ind==0));
				KerArg1->UsedH = (unsigned short int) (((T0Ind_Last)?5:8)-1*(T0Ind==0));
				KerArg1->InFeatures = (unsigned short int) (D0Ind_Last?4:12);
				KerArg1->Filter = (short int * __restrict__) (cnn_ssd_L1_Memory+7744+((D0Ind)*216));
				KerArg1->Pad = (v4s) ((v4s){1,1,1*(T0Ind==0),1*(T0Ind_Last)});
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->H = (unsigned short int) (T0Ind_Last?4:6);
			KerArg2->Out = (short int * __restrict__) (cnn_ssd_L1_Memory+16960+7680*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+16960+7680*((T0Ind_Total)%2)),
					_SC_Out, 640, _LC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (240); _LC_Out = ((T0Ind_NextLast)?160:240); _SC_Out = (32*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S13_MaxPool_2x2(
		short int * __restrict__ In,
		short int * __restrict__ Out)

{
	/* Shared L1: 25600 bytes, L2 buffer: 25600 bytes */
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
		[D0 Dim: Init: 32, Tiled: 1][Tile0 Dim: 1]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 20480 [D0, [0 x 20480, 20480]][Tile0, 1:[20x16], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 20480, 20480]][Tile0, 1:[20x16], 2]
		Tile0: [0, 20480, 20480], Tile1: [0, 20480, 20480], Tile2; [0, 20480, 20480]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 5120 [D0, [0 x 5120, 5120]][Tile0, 1:[10x8], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 5120, 5120]][Tile0, 1:[10x8], 2]
		Tile0: [0, 5120, 5120], Tile1: [0, 5120, 5120], Tile2; [0, 5120, 5120]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (short int * __restrict__) (cnn_ssd_L1_Memory+0);
	KerArg0->W = (unsigned short int) (20);
	KerArg0->UsedW = (unsigned short int) (20);
	KerArg0->H = (unsigned short int) (16);
	KerArg0->OutFeatures = (unsigned short int) (32);
	KerArg0->Out = (short int * __restrict__) (cnn_ssd_L1_Memory+20480);
	KerArg0->Pad = (v4s) 0;
	KerArg0->Orientation = (unsigned char) (1);
	KerArg0->Oper = (unsigned char) (0);
	KerArg0->LB = (int) (-32768);
	KerArg0->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0), 20480, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D0 */
		int D0Ind_Last = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->UsedH = (unsigned short int) (16);
			AT_FORK(gap_ncore(), (void *) KerParPool2x2Stride2_fp, (void *) KerArg0);
			__CALL(KerParPool2x2Stride2_fp, KerArg0);
		} /* End iteration on Tile0 */
	} /* End iteration on D0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+20480), 5120, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S16_Conv2d_18x32x3x3(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 44708 bytes, L2 buffer: 24228 bytes */
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
	int D1Ind, D1Ind_Last, D1Ind_NextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast;
	/* User kernel arguments related variables */
	unsigned int _N_In;
	unsigned int _SN_In;
	unsigned int _LN_In;
	unsigned int _N_Filter;
	unsigned int _SN_Filter;
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	unsigned int _LPP_Out, _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 18, Tiled: 2][Tile0 Dim: 1][D0 Dim: Init: 32, Tiled: 16]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 16 logical tiles, 16 physical tiles
			Total Size: 20480 [D0, [15 x 1280, 1280]][Tile0, 1:[20x16], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[20x17, 14:20x18, 20x17], 2][D0, [15 x 1280, 1280]]
		Tile0: [0, 1280, 640], Tile1: [1280, 1280, 640], Tile2; [2560, 1280, 640]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 36 [D1, [1 x 32, 4]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 32, 4]]
		Tile0: [0, 36, 36], Tile1: [0, 36, 36], Tile2; [0, 36, 36]
	Ker Arg: Filter, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 32 logical tiles, 32 physical tiles
			Total Size: 10368 [D1, [1 x 9216, 1152]][D0, [15 x 576, 576]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 9216, 1152]][D0, [15 x 576, 576]]
		Tile0: [0, 576, 576], Tile1: [576, 576, 576], Tile2; [1152, 576, 576]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 2 physical tiles
			Total Size: 11520 [D1, [1 x 10240, 1280]][Tile0, 1:[20x16], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 10240, 1280]][Tile0, 1:[20x16], 2]
		Tile0: [0, 10240, 640], Tile1: [10240, 1280, 640], Tile2; [0, 10240, 640]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 23040 [D1, [1 x 20480, 2560]][Tile0, 1:[20x16], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 20480, 2560]][Tile0, 1:[20x16], 4]
		Tile0: [0, 20480, 1280], Tile1: [0, 20480, 1280], Tile2; [0, 20480, 1280]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (cnn_ssd_L1_Memory+24228);
	KerArg0->W = (unsigned short int) (20);
	KerArg0->H = (unsigned short int) (16);
	KerArg0->NormBias = (signed char) (12);
	KerArg1->W = (unsigned short int) (20);
	KerArg1->UsedW = (unsigned short int) (20);
	KerArg1->InFeatures = (unsigned short int) (2);
	KerArg1->Out = (int * __restrict__) (cnn_ssd_L1_Memory+24228);
	KerArg1->Norm = (unsigned char) (16);
	KerArg1->TotalInFeatures = (short int) (2);
	KerArg1->Pad = (v4s) ((v4s){1,1,1,1});
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (cnn_ssd_L1_Memory+24228);
	KerArg2->W = (unsigned short int) (20);
	KerArg2->H = (unsigned short int) (16);
	KerArg2->Norm = (unsigned char) (16);
	KerArg2->LB = (int) (-32768);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+0), 1280, 640, 640, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+2560), 36, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+2596+0), 576, 0, &DmaR_Evt3);
	_N_Filter=0;
	_C_Out=0; _SC_Out=10240; _LC_Out=640;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	for (D1Ind=0; D1Ind<2; D1Ind++) { /* Iteration on D1 */
		int D1Ind_Last = (D1Ind==1), D1Ind_NextLast = ((D1Ind+1)==1);
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1, T0Ind_NextLast = 1;
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->OutFeatures = (unsigned short int) (D1Ind_Last?2:16);
			KerArg0->Bias = (short int * __restrict__) (cnn_ssd_L1_Memory+2560+((D1Ind)*32));
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<16; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==15), D0Ind_NextLast = ((D0Ind+1)==15);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (1280); _LN_In = (640); _SN_In = (2*_LN_In); 
				} else if (!(D1Ind_Last)) {
					_N_In = _N_In + (-19200); _LN_In = (640); _SN_In = (2*_LN_In); 
				}
				_SN_Filter = 0;
				if (!(D0Ind_Last)) {
					_N_Filter = _N_Filter + (((D1Ind_Last)?(72):(576))); _SN_Filter = (((D1Ind_Last)?(72):(576))); 
				} else if (!((1))) {
					_N_Filter = _N_Filter + (((D1Ind_Last)?(-1080):(-8640))); _SN_Filter = (((D1Ind_Last)?(72):(576))); 
				} else if (!(D1Ind_Last)) {
					_N_Filter = _N_Filter + (9216)+(((D1Ind_Last)?(-1080):(-8640))); _SN_Filter = (((1)?(72):(576))); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+1280*((D0Ind_Total+1)%2)),
							_SN_In, 640, _LN_In, 0, &DmaR_Evt1);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
				if (_SN_Filter) {
					AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+_N_Filter), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+2596+576*((D0Ind_Total+1)%2)),
							_SN_Filter, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (cnn_ssd_L1_Memory+0+1280*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (18-1*(1)-1*(1));
				KerArg1->UsedH = (unsigned short int) (18-1*(1)-1*(1));
				KerArg1->OutFeatures = (unsigned short int) (D1Ind_Last?2:16);
				KerArg1->Filter = (short int * __restrict__) (cnn_ssd_L1_Memory+2596+576*((D0Ind_Total)%2));
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->Out = (short int * __restrict__) (cnn_ssd_L1_Memory+3748+10240*((T0Ind_Total)%2));
			KerArg2->InFeatures = (unsigned short int) (D1Ind_Last?2:16);
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) cnn_ssd_L2_Memory+89584+10240*((T0Ind_Total+-1)%2)),
						_SP_Out, 640, _LP_Out, 1, &UchanHR1);
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+89584+10240*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+3748+10240*((T0Ind_Total)%2)),
					_SC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
			_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(D1Ind_Last)) {
				_C_Out = _C_Out + (10240); _LC_Out = (640); _SC_Out = (((1)?2:16)*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
			T0Ind_Total++;
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) cnn_ssd_L2_Memory+89584+10240*((T0Ind_Total+-1)%2)), _SP_Out, 640, _LP_Out, 1, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S20_Conv2d_24x32x3x3(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 47792 bytes, L2 buffer: 32432 bytes */
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
		[D1 Dim: Init: 24, Tiled: 1][Tile0 Dim: 2][D0 Dim: Init: 32, Tiled: 8]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 16 logical tiles, 16 physical tiles
			Total Size: 20480 [D0, [7 x 2560, 2560]][Tile0, 2:[20x9, 20x9], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 2:[20x9, 6:20x10, 20x9], 2][D0, [7 x 2560, 2560]]
		Tile0: [0, 1440, 360], Tile1: [2560, 1440, 360], Tile2; [5120, 1440, 360]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 48 [D1, [0 x 48, 48]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 48, 48]]
		Tile0: [0, 48, 48], Tile1: [0, 48, 48], Tile2; [0, 48, 48]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 8 logical tiles, 1 physical tiles
			Total Size: 13824 [D1, [0 x 13824, 13824]][D0, [7 x 1728, 1728]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 13824, 13824]][D0, [7 x 1728, 1728]]
		Tile0: [0, 13824, 13824], Tile1: [0, 13824, 13824], Tile2; [0, 13824, 13824]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 2 physical tiles
			Total Size: 15360 [D1, [0 x 15360, 15360]][Tile0, 2:[20x8, 20x8], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 15360, 15360]][Tile0, 2:[20x8, 20x8], 2]
		Tile0: [0, 7680, 320], Tile1: [320, 7680, 320], Tile2; [0, 7680, 320]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 30720 [D1, [0 x 30720, 30720]][Tile0, 2:[20x8, 20x8], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 30720, 30720]][Tile0, 2:[20x8, 20x8], 4]
		Tile0: [0, 15360, 640], Tile1: [0, 15360, 640], Tile2; [0, 15360, 640]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (cnn_ssd_L1_Memory+32432);
	KerArg0->W = (unsigned short int) (20);
	KerArg0->H = (unsigned short int) (8);
	KerArg0->OutFeatures = (unsigned short int) (24);
	KerArg0->Bias = (short int * __restrict__) (cnn_ssd_L1_Memory+3200);
	KerArg0->NormBias = (signed char) (12);
	KerArg1->W = (unsigned short int) (20);
	KerArg1->UsedW = (unsigned short int) (20);
	KerArg1->InFeatures = (unsigned short int) (4);
	KerArg1->OutFeatures = (unsigned short int) (24);
	KerArg1->Filter = (short int * __restrict__) (cnn_ssd_L1_Memory+3248);
	KerArg1->Out = (int * __restrict__) (cnn_ssd_L1_Memory+32432);
	KerArg1->Norm = (unsigned char) (16);
	KerArg1->TotalInFeatures = (short int) (32);
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (cnn_ssd_L1_Memory+32432);
	KerArg2->W = (unsigned short int) (20);
	KerArg2->H = (unsigned short int) (8);
	KerArg2->Norm = (unsigned char) (16);
	KerArg2->InFeatures = (unsigned short int) (24);
	KerArg2->LB = (int) (-32768);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+0), 1440, 640, 360, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+3200), 48, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+3248), 13824, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
	_C_Out=0; _SC_Out=7680; _LC_Out=320;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<2; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==1), T0Ind_NextLast = ((T0Ind+1)==1);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<8; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==7), D0Ind_NextLast = ((D0Ind+1)==7);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (2560); _LN_In = ((T0Ind_Last)?360:(400-40*(T0Ind==0))); _SN_In = (4*_LN_In); 
				} else if (!(T0Ind_Last)) {
					_N_In = _N_In + (320-(40*(T0Ind==0)))+(-17920); _LN_In = ((1)?360:400); _SN_In = (4*_LN_In); 
				} else if (!(1)) {
					_N_In = _N_In + (-280)+(-17920); _LN_In = (360); _SN_In = (4*_LN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+1600*((D0Ind_Total+1)%2)),
							_SN_In, 640, _LN_In, 0, &DmaR_Evt1);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (cnn_ssd_L1_Memory+0+1600*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (10-1*(T0Ind==0)-1*(T0Ind_Last));
				KerArg1->UsedH = (unsigned short int) (10-1*(T0Ind==0)-1*(T0Ind_Last));
				KerArg1->Filter = (short int * __restrict__) (cnn_ssd_L1_Memory+3248+((D0Ind)*72));
				KerArg1->Pad = (v4s) ((v4s){1,1,1*(T0Ind==0),1*(T0Ind_Last)});
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->Out = (short int * __restrict__) (cnn_ssd_L1_Memory+17072+7680*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) cnn_ssd_L2_Memory+89584+7680*((T0Ind_Total+-1)%2)),
						_SP_Out, 640, _LP_Out, 1, &UchanHR1);
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+89584+7680*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+17072+7680*((T0Ind_Total)%2)),
					_SC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
			_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (320); _LC_Out = (320); _SC_Out = (24*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) cnn_ssd_L2_Memory+89584+7680*((T0Ind_Total+-1)%2)), _SP_Out, 640, _LP_Out, 1, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S24_Conv2d_64x32x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 36096 bytes, L2 buffer: 15616 bytes */
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
		[D1 Dim: Init: 64, Tiled: 1][Tile0 Dim: 1][D0 Dim: Init: 32, Tiled: 16]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 16 logical tiles, 16 physical tiles
			Total Size: 5120 [D0, [15 x 320, 320]][Tile0, 1:[10x8], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[10x9, 14:10x10, 10x9], 2][D0, [15 x 320, 320]]
		Tile0: [0, 320, 160], Tile1: [320, 320, 160], Tile2; [640, 320, 160]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 128 [D1, [0 x 128, 128]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 128, 128]]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Filter, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 16 logical tiles, 16 physical tiles
			Total Size: 36864 [D1, [0 x 36864, 36864]][D0, [15 x 2304, 2304]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 36864, 36864]][D0, [15 x 2304, 2304]]
		Tile0: [0, 2304, 2304], Tile1: [2304, 2304, 2304], Tile2; [4608, 2304, 2304]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 10240 [D1, [0 x 10240, 10240]][Tile0, 1:[10x8], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 10240, 10240]][Tile0, 1:[10x8], 2]
		Tile0: [0, 10240, 10240], Tile1: [0, 10240, 10240], Tile2; [0, 10240, 10240]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 20480 [D1, [0 x 20480, 20480]][Tile0, 1:[10x8], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 20480, 20480]][Tile0, 1:[10x8], 4]
		Tile0: [0, 20480, 320], Tile1: [0, 20480, 320], Tile2; [0, 20480, 320]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (cnn_ssd_L1_Memory+15616);
	KerArg0->W = (unsigned short int) (10);
	KerArg0->H = (unsigned short int) (8);
	KerArg0->OutFeatures = (unsigned short int) (64);
	KerArg0->Bias = (short int * __restrict__) (cnn_ssd_L1_Memory+640);
	KerArg0->NormBias = (signed char) (14);
	KerArg1->W = (unsigned short int) (10);
	KerArg1->UsedW = (unsigned short int) (10);
	KerArg1->InFeatures = (unsigned short int) (2);
	KerArg1->OutFeatures = (unsigned short int) (64);
	KerArg1->Out = (int * __restrict__) (cnn_ssd_L1_Memory+15616);
	KerArg1->Norm = (unsigned char) (14);
	KerArg1->TotalInFeatures = (short int) (2);
	KerArg1->Pad = (v4s) ((v4s){1,1,1,1});
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (cnn_ssd_L1_Memory+15616);
	KerArg2->W = (unsigned short int) (10);
	KerArg2->H = (unsigned short int) (8);
	KerArg2->Out = (short int * __restrict__) (cnn_ssd_L1_Memory+5376);
	KerArg2->Norm = (unsigned char) (14);
	KerArg2->InFeatures = (unsigned short int) (64);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+0), 320, 160, 160, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+640), 128, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+768+0), 2304, 0, &DmaR_Evt3);
	_N_Filter=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1, D1Ind_NextLast = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1, T0Ind_NextLast = 1;
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<16; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==15), D0Ind_NextLast = ((D0Ind+1)==15);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (320); _LN_In = (160); _SN_In = (2*_LN_In); 
				} else if (!(1)) {
					_N_In = _N_In + (-4800); _LN_In = (160); _SN_In = (2*_LN_In); 
				}
				_SN_Filter = 0;
				if (!(D0Ind_Last)) {
					_N_Filter = _N_Filter + ((2304)); _SN_Filter = (((1)?(2304):(2304))); 
				} else if (!((1))) {
					_N_Filter = _N_Filter + ((-34560)); _SN_Filter = (((1)?(2304):(2304))); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+320*((D0Ind_Total+1)%2)),
							_SN_In, 160, _LN_In, 0, &DmaR_Evt1);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
				if (_SN_Filter) {
					AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+_N_Filter), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+768+2304*((D0Ind_Total+1)%2)),
							_SN_Filter, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (cnn_ssd_L1_Memory+0+320*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (10-1*(1)-1*(1));
				KerArg1->UsedH = (unsigned short int) (10-1*(1)-1*(1));
				KerArg1->Filter = (short int * __restrict__) (cnn_ssd_L1_Memory+768+2304*((D0Ind_Total)%2));
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
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+5376), 10240, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S25_MaxPool_2x2(
		short int * __restrict__ In,
		short int * __restrict__ Out)

{
	/* Shared L1: 12800 bytes, L2 buffer: 12800 bytes */
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
			Total Size: 10240 [D0, [0 x 10240, 10240]][Tile0, 1:[10x8], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 10240, 10240]][Tile0, 1:[10x8], 2]
		Tile0: [0, 10240, 10240], Tile1: [0, 10240, 10240], Tile2; [0, 10240, 10240]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 2560 [D0, [0 x 2560, 2560]][Tile0, 1:[5x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 2560, 2560]][Tile0, 1:[5x4], 2]
		Tile0: [0, 2560, 2560], Tile1: [0, 2560, 2560], Tile2; [0, 2560, 2560]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (short int * __restrict__) (cnn_ssd_L1_Memory+0);
	KerArg0->W = (unsigned short int) (10);
	KerArg0->UsedW = (unsigned short int) (10);
	KerArg0->H = (unsigned short int) (8);
	KerArg0->OutFeatures = (unsigned short int) (64);
	KerArg0->Out = (short int * __restrict__) (cnn_ssd_L1_Memory+10240);
	KerArg0->Pad = (v4s) 0;
	KerArg0->Orientation = (unsigned char) (1);
	KerArg0->Oper = (unsigned char) (0);
	KerArg0->LB = (int) (-32768);
	KerArg0->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0), 10240, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D0 */
		int D0Ind_Last = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->UsedH = (unsigned short int) (8);
			AT_FORK(gap_ncore(), (void *) KerParPool2x2Stride2_fp, (void *) KerArg0);
			__CALL(KerParPool2x2Stride2_fp, KerArg0);
		} /* End iteration on Tile0 */
	} /* End iteration on D0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+10240), 2560, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S28_Conv2d_18x64x3x3(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 39652 bytes, L2 buffer: 33892 bytes */
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
	int T0Ind, T0Ind_Last;
	int D0Ind, D0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 18, Tiled: 1][Tile0 Dim: 1][D0 Dim: Init: 64, Tiled: 1]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 5760 [D1, [0 x 5760, 5760]][Tile0, 1:[10x8], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 5760, 5760]][Tile0, 1:[10x8], 4]
		Tile0: [0, 5760, 320], Tile1: [0, 5760, 320], Tile2; [0, 5760, 320]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 36 [D1, [0 x 36, 36]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 36, 36]]
		Tile0: [0, 36, 36], Tile1: [0, 36, 36], Tile2; [0, 36, 36]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 20736 [D1, [0 x 20736, 20736]][D0, [0 x 20736, 20736]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 20736, 20736]][D0, [0 x 20736, 20736]]
		Tile0: [0, 20736, 20736], Tile1: [0, 20736, 20736], Tile2; [0, 20736, 20736]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 2880 [D1, [0 x 2880, 2880]][Tile0, 1:[10x8], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 2880, 2880]][Tile0, 1:[10x8], 2]
		Tile0: [0, 2880, 2880], Tile1: [0, 2880, 2880], Tile2; [0, 2880, 2880]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 10240 [D0, [0 x 10240, 10240]][Tile0, 1:[10x8], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[10x8], 2][D0, [0 x 10240, 10240]]
		Tile0: [0, 10240, 10240], Tile1: [0, 10240, 10240], Tile2; [0, 10240, 10240]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (cnn_ssd_L1_Memory+33892);
	KerArg0->W = (unsigned short int) (10);
	KerArg0->H = (unsigned short int) (8);
	KerArg0->OutFeatures = (unsigned short int) (18);
	KerArg0->Bias = (short int * __restrict__) (cnn_ssd_L1_Memory+10240);
	KerArg0->NormBias = (signed char) (12);
	KerArg1->In = (short int * __restrict__) (cnn_ssd_L1_Memory+0);
	KerArg1->W = (unsigned short int) (10);
	KerArg1->UsedW = (unsigned short int) (10);
	KerArg1->H = (unsigned short int) (8);
	KerArg1->InFeatures = (unsigned short int) (64);
	KerArg1->OutFeatures = (unsigned short int) (18);
	KerArg1->Filter = (short int * __restrict__) (cnn_ssd_L1_Memory+10276);
	KerArg1->Out = (int * __restrict__) (cnn_ssd_L1_Memory+33892);
	KerArg1->Norm = (unsigned char) (16);
	KerArg1->TotalInFeatures = (short int) (64);
	KerArg1->Pad = (v4s) ((v4s){1,1,1,1});
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (cnn_ssd_L1_Memory+33892);
	KerArg2->W = (unsigned short int) (10);
	KerArg2->H = (unsigned short int) (8);
	KerArg2->Out = (short int * __restrict__) (cnn_ssd_L1_Memory+31012);
	KerArg2->Norm = (unsigned char) (16);
	KerArg2->InFeatures = (unsigned short int) (18);
	KerArg2->LB = (int) (-32768);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+10240), 36, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+10276), 20736, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Filter */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0), 10240, 0, &DmaR_Evt3);
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
				KerArg1->UsedH = (unsigned short int) (8);
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+58864+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+31012), 2880, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+0), ((AT_HYPERRAM_INT_ADDR_TYPE) cnn_ssd_L2_Memory+58864+0), 2880, 1, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S32_Conv2d_24x64x3x3(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 42352 bytes, L2 buffer: 34672 bytes */
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
		[D1 Dim: Init: 24, Tiled: 1][Tile0 Dim: 1][D0 Dim: Init: 64, Tiled: 3]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 3 logical tiles, 3 physical tiles
			Total Size: 10240 [D0, [2 x 4160, 1920]][Tile0, 1:[10x8], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[10x9, 1:10x10, 10x9], 2][D0, [2 x 4160, 1920]]
		Tile0: [0, 4160, 160], Tile1: [4160, 4160, 160], Tile2; [8320, 1920, 160]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 48 [D1, [0 x 48, 48]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 48, 48]]
		Tile0: [0, 48, 48], Tile1: [0, 48, 48], Tile2; [0, 48, 48]
	Ker Arg: Filter, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 3 logical tiles, 3 physical tiles
			Total Size: 27648 [D1, [0 x 27648, 27648]][D0, [2 x 11232, 5184]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 27648, 27648]][D0, [2 x 11232, 5184]]
		Tile0: [0, 11232, 11232], Tile1: [11232, 11232, 11232], Tile2; [22464, 5184, 5184]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 3840 [D1, [0 x 3840, 3840]][Tile0, 1:[10x8], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 3840, 3840]][Tile0, 1:[10x8], 2]
		Tile0: [0, 3840, 3840], Tile1: [0, 3840, 3840], Tile2; [0, 3840, 3840]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 7680 [D1, [0 x 7680, 7680]][Tile0, 1:[10x8], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 7680, 7680]][Tile0, 1:[10x8], 4]
		Tile0: [0, 7680, 320], Tile1: [0, 7680, 320], Tile2; [0, 7680, 320]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (cnn_ssd_L1_Memory+34672);
	KerArg0->W = (unsigned short int) (10);
	KerArg0->H = (unsigned short int) (8);
	KerArg0->OutFeatures = (unsigned short int) (24);
	KerArg0->Bias = (short int * __restrict__) (cnn_ssd_L1_Memory+8320);
	KerArg0->NormBias = (signed char) (13);
	KerArg1->W = (unsigned short int) (10);
	KerArg1->UsedW = (unsigned short int) (10);
	KerArg1->OutFeatures = (unsigned short int) (24);
	KerArg1->Out = (int * __restrict__) (cnn_ssd_L1_Memory+34672);
	KerArg1->Norm = (unsigned char) (16);
	KerArg1->Pad = (v4s) ((v4s){1,1,1,1});
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (cnn_ssd_L1_Memory+34672);
	KerArg2->W = (unsigned short int) (10);
	KerArg2->H = (unsigned short int) (8);
	KerArg2->Out = (short int * __restrict__) (cnn_ssd_L1_Memory+30832);
	KerArg2->Norm = (unsigned char) (16);
	KerArg2->InFeatures = (unsigned short int) (24);
	KerArg2->LB = (int) (-32768);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+0), 4160, 160, 160, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+8320), 48, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+8368+0), 11232, 0, &DmaR_Evt3);
	_N_Filter=0;
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
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (4160); _LN_In = (160); _SN_In = (((D0Ind_NextLast)?12:26)*_LN_In); 
				} else if (!(1)) {
					_N_In = _N_In + (-8320); _LN_In = (160); _SN_In = (26*_LN_In); 
				}
				_SN_Filter = 0;
				if (!(D0Ind_Last)) {
					_N_Filter = _N_Filter + ((11232)); _SN_Filter = (((1)?(((D0Ind_NextLast)?5184:11232)):(((D0Ind_NextLast)?5184:11232)))); 
				} else if (!((1))) {
					_N_Filter = _N_Filter + ((-22464)); _SN_Filter = (((1)?(11232):(11232))); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+4160*((D0Ind_Total+1)%2)),
							_SN_In, 160, _LN_In, 0, &DmaR_Evt1);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
				if (_SN_Filter) {
					AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+_N_Filter), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+8368+11232*((D0Ind_Total+1)%2)),
							_SN_Filter, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (cnn_ssd_L1_Memory+0+4160*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (10-1*(1)-1*(1));
				KerArg1->UsedH = (unsigned short int) (10-1*(1)-1*(1));
				KerArg1->InFeatures = (unsigned short int) (D0Ind_Last?12:26);
				KerArg1->Filter = (short int * __restrict__) (cnn_ssd_L1_Memory+8368+11232*((D0Ind_Total)%2));
				KerArg1->TotalInFeatures = (short int) (D0Ind_Last?12:26);
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
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+58864+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+30832), 3840, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+0), ((AT_HYPERRAM_INT_ADDR_TYPE) cnn_ssd_L2_Memory+58864+0), 3840, 1, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S36_Conv2d_128x64x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 34368 bytes, L2 buffer: 24128 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF1;
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
		[D1 Dim: Init: 128, Tiled: 1][Tile0 Dim: 1][D0 Dim: Init: 64, Tiled: 16]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 16 logical tiles, 16 physical tiles
			Total Size: 2560 [D0, [15 x 160, 160]][Tile0, 1:[5x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[5x5, 14:5x6, 5x5], 2][D0, [15 x 160, 160]]
		Tile0: [0, 160, 40], Tile1: [160, 160, 40], Tile2; [320, 160, 40]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 256 [D1, [0 x 256, 256]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 256, 256]]
		Tile0: [0, 256, 256], Tile1: [0, 256, 256], Tile2; [0, 256, 256]
	Ker Arg: Filter, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 16 logical tiles, 16 physical tiles
			Total Size: 147456 [D1, [0 x 147456, 147456]][D0, [15 x 9216, 9216]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 147456, 147456]][D0, [15 x 9216, 9216]]
		Tile0: [0, 9216, 9216], Tile1: [9216, 9216, 9216], Tile2; [18432, 9216, 9216]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 5120 [D1, [0 x 5120, 5120]][Tile0, 1:[5x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 5120, 5120]][Tile0, 1:[5x4], 2]
		Tile0: [0, 5120, 5120], Tile1: [0, 5120, 5120], Tile2; [0, 5120, 5120]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 10240 [D1, [0 x 10240, 10240]][Tile0, 1:[5x4], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 10240, 10240]][Tile0, 1:[5x4], 4]
		Tile0: [0, 10240, 80], Tile1: [0, 10240, 80], Tile2; [0, 10240, 80]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (cnn_ssd_L1_Memory+24128);
	KerArg0->W = (unsigned short int) (5);
	KerArg0->H = (unsigned short int) (4);
	KerArg0->OutFeatures = (unsigned short int) (128);
	KerArg0->Bias = (short int * __restrict__) (cnn_ssd_L1_Memory+320);
	KerArg0->NormBias = (signed char) (15);
	KerArg1->W = (unsigned short int) (5);
	KerArg1->UsedW = (unsigned short int) (5);
	KerArg1->InFeatures = (unsigned short int) (4);
	KerArg1->OutFeatures = (unsigned short int) (128);
	KerArg1->Out = (int * __restrict__) (cnn_ssd_L1_Memory+24128);
	KerArg1->Norm = (unsigned char) (15);
	KerArg1->TotalInFeatures = (short int) (4);
	KerArg1->Pad = (v4s) ((v4s){1,1,1,1});
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (cnn_ssd_L1_Memory+24128);
	KerArg2->W = (unsigned short int) (5);
	KerArg2->H = (unsigned short int) (4);
	KerArg2->Out = (short int * __restrict__) (cnn_ssd_L1_Memory+19008);
	KerArg2->Norm = (unsigned char) (15);
	KerArg2->InFeatures = (unsigned short int) (128);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+0), 160, 40, 40, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+320), 256, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory+99824+0), 9216, 0, &UchanHF1);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read Filter */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+9216), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory+99824+9216), 9216, 0, &UchanHF1);
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+99824+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+576+0), 9216, 0, &DmaR_Evt3);
	_NN_Filter=9216; _SN_Filter=9216;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1, D1Ind_NextLast = 1, D1Ind_NextNextLast = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1, T0Ind_NextLast = 1;
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<16; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==15), D0Ind_NextLast = ((D0Ind+1)==15), D0Ind_NextNextLast = ((D0Ind+2)==15);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (160); _LN_In = (40); _SN_In = (4*_LN_In); 
				} else if (!(1)) {
					_N_In = _N_In + (-2400); _LN_In = (40); _SN_In = (4*_LN_In); 
				}
				_SNN_Filter = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_Filter = _NN_Filter + ((9216)); _SNN_Filter = (((1)?(9216):(9216))); 
					} else if (!((1))) {
						_NN_Filter = _NN_Filter + ((-138240)); _SNN_Filter = (((1)?(9216):(9216))); 
					}
				} else if (!((1))) {
					_NN_Filter = _NN_Filter + ((9216)); _SNN_Filter = (((1)?(9216):(9216))); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+160*((D0Ind_Total+1)%2)),
							_SN_In, 40, _LN_In, 0, &DmaR_Evt1);
				}
				AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read Filter */
				if (_SNN_Filter) {
					AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+_NN_Filter), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory+99824+9216*((D0Ind_Total)%2)),
							_SNN_Filter, 0, &UchanHF1);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
				if (_SN_Filter) {
					AT_L2_COPY(0, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+99824+9216*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+576+9216*((D0Ind_Total+1)%2)),
							_SN_Filter, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (cnn_ssd_L1_Memory+0+160*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (6-1*(1)-1*(1));
				KerArg1->UsedH = (unsigned short int) (6-1*(1)-1*(1));
				KerArg1->Filter = (short int * __restrict__) (cnn_ssd_L1_Memory+576+9216*((D0Ind_Total)%2));
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
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+19008), 5120, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S37_MaxPool_2x2(
		short int * __restrict__ In,
		short int * __restrict__ Out)

{
	/* Shared L1: 6144 bytes, L2 buffer: 6144 bytes */
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
		[D0 Dim: Init: 128, Tiled: 1][Tile0 Dim: 1]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 5120 [D0, [0 x 5120, 5120]][Tile0, 1:[5x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 5120, 5120]][Tile0, 1:[5x4], 2]
		Tile0: [0, 5120, 5120], Tile1: [0, 5120, 5120], Tile2; [0, 5120, 5120]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 1024 [D0, [0 x 1024, 1024]][Tile0, 1:[2x2], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 1024, 1024]][Tile0, 1:[2x2], 2]
		Tile0: [0, 1024, 1024], Tile1: [0, 1024, 1024], Tile2; [0, 1024, 1024]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (short int * __restrict__) (cnn_ssd_L1_Memory+0);
	KerArg0->W = (unsigned short int) (5);
	KerArg0->UsedW = (unsigned short int) (4);
	KerArg0->H = (unsigned short int) (4);
	KerArg0->OutFeatures = (unsigned short int) (128);
	KerArg0->Out = (short int * __restrict__) (cnn_ssd_L1_Memory+5120);
	KerArg0->Pad = (v4s) 0;
	KerArg0->Orientation = (unsigned char) (1);
	KerArg0->Oper = (unsigned char) (0);
	KerArg0->LB = (int) (-32768);
	KerArg0->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0), 5120, 0, &DmaR_Evt1);
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
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+5120), 1024, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S40_Conv2d_18x128x3x3(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 45892 bytes, L2 buffer: 44612 bytes */
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
	int D1Ind, D1Ind_Last, D1Ind_NextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast;
	/* User kernel arguments related variables */
	unsigned int _N_In;
	unsigned int _SN_In;
	unsigned int _LN_In;
	unsigned int _N_Filter;
	unsigned int _SN_Filter;
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	unsigned int _LPP_Out, _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 18, Tiled: 2][Tile0 Dim: 1][D0 Dim: Init: 128, Tiled: 2]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 2 logical tiles, 2 physical tiles
			Total Size: 5120 [D0, [1 x 2640, 2480]][Tile0, 1:[5x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[5x5, 5x5], 2][D0, [1 x 2640, 2480]]
		Tile0: [0, 2640, 40], Tile1: [2640, 2480, 40], Tile2; [0, 2640, 40]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 36 [D1, [1 x 32, 4]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 32, 4]]
		Tile0: [0, 36, 36], Tile1: [0, 36, 36], Tile2; [0, 36, 36]
	Ker Arg: Filter, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 4 logical tiles, 4 physical tiles
			Total Size: 41472 [D1, [1 x 36864, 4608]][D0, [1 x 19008, 17856]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 36864, 4608]][D0, [1 x 19008, 17856]]
		Tile0: [0, 19008, 19008], Tile1: [19008, 17856, 17856], Tile2; [36864, 2376, 2376]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 2 physical tiles
			Total Size: 720 [D1, [1 x 640, 80]][Tile0, 1:[5x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 640, 80]][Tile0, 1:[5x4], 2]
		Tile0: [0, 640, 40], Tile1: [640, 80, 40], Tile2; [0, 640, 40]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 1440 [D1, [1 x 1280, 160]][Tile0, 1:[5x4], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 1280, 160]][Tile0, 1:[5x4], 4]
		Tile0: [0, 1280, 80], Tile1: [0, 1280, 80], Tile2; [0, 1280, 80]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (cnn_ssd_L1_Memory+44612);
	KerArg0->W = (unsigned short int) (5);
	KerArg0->H = (unsigned short int) (4);
	KerArg0->NormBias = (signed char) (12);
	KerArg1->W = (unsigned short int) (5);
	KerArg1->UsedW = (unsigned short int) (5);
	KerArg1->Out = (int * __restrict__) (cnn_ssd_L1_Memory+44612);
	KerArg1->Norm = (unsigned char) (16);
	KerArg1->Pad = (v4s) ((v4s){1,1,1,1});
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (cnn_ssd_L1_Memory+44612);
	KerArg2->W = (unsigned short int) (5);
	KerArg2->H = (unsigned short int) (4);
	KerArg2->Norm = (unsigned char) (16);
	KerArg2->LB = (int) (-32768);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+0), 2640, 40, 40, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+5280), 36, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+5316+0), 19008, 0, &DmaR_Evt3);
	_N_Filter=0;
	_C_Out=0; _SC_Out=640; _LC_Out=40;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	for (D1Ind=0; D1Ind<2; D1Ind++) { /* Iteration on D1 */
		int D1Ind_Last = (D1Ind==1), D1Ind_NextLast = ((D1Ind+1)==1);
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1, T0Ind_NextLast = 1;
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->OutFeatures = (unsigned short int) (D1Ind_Last?2:16);
			KerArg0->Bias = (short int * __restrict__) (cnn_ssd_L1_Memory+5280+((D1Ind)*32));
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<2; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==1), D0Ind_NextLast = ((D0Ind+1)==1);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (2640); _LN_In = (40); _SN_In = (((1)?62:66)*_LN_In); 
				} else if (!(D1Ind_Last)) {
					_N_In = _N_In + (-2640); _LN_In = (40); _SN_In = (66*_LN_In); 
				}
				_SN_Filter = 0;
				if (!(D0Ind_Last)) {
					_N_Filter = _N_Filter + (((D1Ind_Last)?(2376):(19008))); _SN_Filter = (((D1Ind_Last)?(((1)?2232:2376)):(((1)?17856:19008)))); 
				} else if (!((1))) {
					_N_Filter = _N_Filter + (((D1Ind_Last)?(-2376):(-19008))); _SN_Filter = (((D1Ind_Last)?(2376):(19008))); 
				} else if (!(D1Ind_Last)) {
					_N_Filter = _N_Filter + (36864)+(((D1Ind_Last)?(-2376):(-19008))); _SN_Filter = (((1)?(2376):(19008))); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+2640*((D0Ind_Total+1)%2)),
							_SN_In, 40, _LN_In, 0, &DmaR_Evt1);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
				if (_SN_Filter) {
					AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+_N_Filter), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+5316+19008*((D0Ind_Total+1)%2)),
							_SN_Filter, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (cnn_ssd_L1_Memory+0+2640*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (6-1*(1)-1*(1));
				KerArg1->UsedH = (unsigned short int) (6-1*(1)-1*(1));
				KerArg1->InFeatures = (unsigned short int) (D0Ind_Last?62:66);
				KerArg1->OutFeatures = (unsigned short int) (D1Ind_Last?2:16);
				KerArg1->Filter = (short int * __restrict__) (cnn_ssd_L1_Memory+5316+19008*((D0Ind_Total)%2));
				KerArg1->TotalInFeatures = (short int) (D0Ind_Last?62:66);
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->Out = (short int * __restrict__) (cnn_ssd_L1_Memory+43332+640*((T0Ind_Total)%2));
			KerArg2->InFeatures = (unsigned short int) (D1Ind_Last?2:16);
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) cnn_ssd_L2_Memory+58864+640*((T0Ind_Total+-1)%2)),
						_SP_Out, 40, _LP_Out, 1, &UchanHR1);
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+58864+640*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+43332+640*((T0Ind_Total)%2)),
					_SC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
			_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(D1Ind_Last)) {
				_C_Out = _C_Out + (640); _LC_Out = (40); _SC_Out = (((1)?2:16)*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
			T0Ind_Total++;
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) cnn_ssd_L2_Memory+58864+640*((T0Ind_Total+-1)%2)), _SP_Out, 40, _LP_Out, 1, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S44_Conv2d_24x128x3x3(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 44464 bytes, L2 buffer: 42544 bytes */
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
		[D1 Dim: Init: 24, Tiled: 1][Tile0 Dim: 1][D0 Dim: Init: 128, Tiled: 3]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 3 logical tiles, 3 physical tiles
			Total Size: 5120 [D0, [2 x 1760, 1600]][Tile0, 1:[5x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[5x5, 1:5x6, 5x5], 2][D0, [2 x 1760, 1600]]
		Tile0: [0, 1760, 40], Tile1: [1760, 1760, 40], Tile2; [3520, 1600, 40]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 48 [D1, [0 x 48, 48]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 48, 48]]
		Tile0: [0, 48, 48], Tile1: [0, 48, 48], Tile2; [0, 48, 48]
	Ker Arg: Filter, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 3 logical tiles, 3 physical tiles
			Total Size: 55296 [D1, [0 x 55296, 55296]][D0, [2 x 19008, 17280]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 55296, 55296]][D0, [2 x 19008, 17280]]
		Tile0: [0, 19008, 19008], Tile1: [19008, 19008, 19008], Tile2; [38016, 17280, 17280]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 960 [D1, [0 x 960, 960]][Tile0, 1:[5x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 960, 960]][Tile0, 1:[5x4], 2]
		Tile0: [0, 960, 960], Tile1: [0, 960, 960], Tile2; [0, 960, 960]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 1920 [D1, [0 x 1920, 1920]][Tile0, 1:[5x4], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 1920, 1920]][Tile0, 1:[5x4], 4]
		Tile0: [0, 1920, 80], Tile1: [0, 1920, 80], Tile2; [0, 1920, 80]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (cnn_ssd_L1_Memory+42544);
	KerArg0->W = (unsigned short int) (5);
	KerArg0->H = (unsigned short int) (4);
	KerArg0->OutFeatures = (unsigned short int) (24);
	KerArg0->Bias = (short int * __restrict__) (cnn_ssd_L1_Memory+3520);
	KerArg0->NormBias = (signed char) (13);
	KerArg1->W = (unsigned short int) (5);
	KerArg1->UsedW = (unsigned short int) (5);
	KerArg1->OutFeatures = (unsigned short int) (24);
	KerArg1->Out = (int * __restrict__) (cnn_ssd_L1_Memory+42544);
	KerArg1->Norm = (unsigned char) (16);
	KerArg1->Pad = (v4s) ((v4s){1,1,1,1});
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (cnn_ssd_L1_Memory+42544);
	KerArg2->W = (unsigned short int) (5);
	KerArg2->H = (unsigned short int) (4);
	KerArg2->Out = (short int * __restrict__) (cnn_ssd_L1_Memory+41584);
	KerArg2->Norm = (unsigned char) (16);
	KerArg2->InFeatures = (unsigned short int) (24);
	KerArg2->LB = (int) (-32768);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+0), 1760, 40, 40, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+3520), 48, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+3568+0), 19008, 0, &DmaR_Evt3);
	_N_Filter=0;
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
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (1760); _LN_In = (40); _SN_In = (((D0Ind_NextLast)?40:44)*_LN_In); 
				} else if (!(1)) {
					_N_In = _N_In + (-3520); _LN_In = (40); _SN_In = (44*_LN_In); 
				}
				_SN_Filter = 0;
				if (!(D0Ind_Last)) {
					_N_Filter = _N_Filter + ((19008)); _SN_Filter = (((1)?(((D0Ind_NextLast)?17280:19008)):(((D0Ind_NextLast)?17280:19008)))); 
				} else if (!((1))) {
					_N_Filter = _N_Filter + ((-38016)); _SN_Filter = (((1)?(19008):(19008))); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+1760*((D0Ind_Total+1)%2)),
							_SN_In, 40, _LN_In, 0, &DmaR_Evt1);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
				if (_SN_Filter) {
					AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+_N_Filter), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+3568+19008*((D0Ind_Total+1)%2)),
							_SN_Filter, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (cnn_ssd_L1_Memory+0+1760*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (6-1*(1)-1*(1));
				KerArg1->UsedH = (unsigned short int) (6-1*(1)-1*(1));
				KerArg1->InFeatures = (unsigned short int) (D0Ind_Last?40:44);
				KerArg1->Filter = (short int * __restrict__) (cnn_ssd_L1_Memory+3568+19008*((D0Ind_Total)%2));
				KerArg1->TotalInFeatures = (short int) (D0Ind_Last?40:44);
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
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+58864+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+41584), 960, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+0), ((AT_HYPERRAM_INT_ADDR_TYPE) cnn_ssd_L2_Memory+58864+0), 960, 1, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S48_Conv2d_128x128x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 40320 bytes, L2 buffer: 38272 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF1;
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
		[D1 Dim: Init: 128, Tiled: 1][Tile0 Dim: 1][D0 Dim: Init: 128, Tiled: 16]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 16 logical tiles, 16 physical tiles
			Total Size: 1024 [D0, [15 x 64, 64]][Tile0, 1:[2x2], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[2x3, 14:2x4, 2x3], 2][D0, [15 x 64, 64]]
		Tile0: [0, 64, 8], Tile1: [64, 64, 8], Tile2; [128, 64, 8]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 256 [D1, [0 x 256, 256]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 256, 256]]
		Tile0: [0, 256, 256], Tile1: [0, 256, 256], Tile2; [0, 256, 256]
	Ker Arg: Filter, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 16 logical tiles, 16 physical tiles
			Total Size: 294912 [D1, [0 x 294912, 294912]][D0, [15 x 18432, 18432]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 294912, 294912]][D0, [15 x 18432, 18432]]
		Tile0: [0, 18432, 18432], Tile1: [18432, 18432, 18432], Tile2; [36864, 18432, 18432]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 1024 [D1, [0 x 1024, 1024]][Tile0, 1:[2x2], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 1024, 1024]][Tile0, 1:[2x2], 2]
		Tile0: [0, 1024, 1024], Tile1: [0, 1024, 1024], Tile2; [0, 1024, 1024]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 2048 [D1, [0 x 2048, 2048]][Tile0, 1:[2x2], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 2048, 2048]][Tile0, 1:[2x2], 4]
		Tile0: [0, 2048, 16], Tile1: [0, 2048, 16], Tile2; [0, 2048, 16]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (cnn_ssd_L1_Memory+38272);
	KerArg0->W = (unsigned short int) (2);
	KerArg0->H = (unsigned short int) (2);
	KerArg0->OutFeatures = (unsigned short int) (128);
	KerArg0->Bias = (short int * __restrict__) (cnn_ssd_L1_Memory+128);
	KerArg0->NormBias = (signed char) (13);
	KerArg1->W = (unsigned short int) (2);
	KerArg1->UsedW = (unsigned short int) (2);
	KerArg1->InFeatures = (unsigned short int) (8);
	KerArg1->OutFeatures = (unsigned short int) (128);
	KerArg1->Out = (int * __restrict__) (cnn_ssd_L1_Memory+38272);
	KerArg1->Norm = (unsigned char) (14);
	KerArg1->TotalInFeatures = (short int) (8);
	KerArg1->Pad = (v4s) ((v4s){1,1,1,1});
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (cnn_ssd_L1_Memory+38272);
	KerArg2->W = (unsigned short int) (2);
	KerArg2->H = (unsigned short int) (2);
	KerArg2->Out = (short int * __restrict__) (cnn_ssd_L1_Memory+37248);
	KerArg2->Norm = (unsigned char) (14);
	KerArg2->InFeatures = (unsigned short int) (128);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+0), 64, 8, 8, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+128), 256, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory+99824+0), 18432, 0, &UchanHF1);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read Filter */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+18432), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory+99824+18432), 18432, 0, &UchanHF1);
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+99824+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+384+0), 18432, 0, &DmaR_Evt3);
	_NN_Filter=18432; _SN_Filter=18432;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1, D1Ind_NextLast = 1, D1Ind_NextNextLast = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1, T0Ind_NextLast = 1;
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<16; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==15), D0Ind_NextLast = ((D0Ind+1)==15), D0Ind_NextNextLast = ((D0Ind+2)==15);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (64); _LN_In = (8); _SN_In = (8*_LN_In); 
				} else if (!(1)) {
					_N_In = _N_In + (-960); _LN_In = (8); _SN_In = (8*_LN_In); 
				}
				_SNN_Filter = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_Filter = _NN_Filter + ((18432)); _SNN_Filter = (((1)?(18432):(18432))); 
					} else if (!((1))) {
						_NN_Filter = _NN_Filter + ((-276480)); _SNN_Filter = (((1)?(18432):(18432))); 
					}
				} else if (!((1))) {
					_NN_Filter = _NN_Filter + ((18432)); _SNN_Filter = (((1)?(18432):(18432))); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+64*((D0Ind_Total+1)%2)),
							_SN_In, 8, _LN_In, 0, &DmaR_Evt1);
				}
				AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read Filter */
				if (_SNN_Filter) {
					AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+_NN_Filter), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory+99824+18432*((D0Ind_Total)%2)),
							_SNN_Filter, 0, &UchanHF1);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
				if (_SN_Filter) {
					AT_L2_COPY(0, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+99824+18432*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+384+18432*((D0Ind_Total+1)%2)),
							_SN_Filter, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (cnn_ssd_L1_Memory+0+64*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (4-1*(1)-1*(1));
				KerArg1->UsedH = (unsigned short int) (4-1*(1)-1*(1));
				KerArg1->Filter = (short int * __restrict__) (cnn_ssd_L1_Memory+384+18432*((D0Ind_Total)%2));
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
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+37248), 1024, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S51_Conv2d_18x128x3x3(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 42964 bytes, L2 buffer: 42676 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF1;
	AT_HYPERRAM_CL_EVENT UchanHR2;
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
		[D1 Dim: Init: 18, Tiled: 1][Tile0 Dim: 1][D0 Dim: Init: 128, Tiled: 1]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 288 [D1, [0 x 288, 288]][Tile0, 1:[2x2], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 288, 288]][Tile0, 1:[2x2], 4]
		Tile0: [0, 288, 16], Tile1: [0, 288, 16], Tile2; [0, 288, 16]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 36 [D1, [0 x 36, 36]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 36, 36]]
		Tile0: [0, 36, 36], Tile1: [0, 36, 36], Tile2; [0, 36, 36]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 41472 [D1, [0 x 41472, 41472]][D0, [0 x 41472, 41472]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 41472, 41472]][D0, [0 x 41472, 41472]]
		Tile0: [0, 41472, 41472], Tile1: [0, 41472, 41472], Tile2; [0, 41472, 41472]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 144 [D1, [0 x 144, 144]][Tile0, 1:[2x2], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 144, 144]][Tile0, 1:[2x2], 2]
		Tile0: [0, 144, 144], Tile1: [0, 144, 144], Tile2; [0, 144, 144]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 1024 [D0, [0 x 1024, 1024]][Tile0, 1:[2x2], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[2x2], 2][D0, [0 x 1024, 1024]]
		Tile0: [0, 1024, 1024], Tile1: [0, 1024, 1024], Tile2; [0, 1024, 1024]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (cnn_ssd_L1_Memory+42676);
	KerArg0->W = (unsigned short int) (2);
	KerArg0->H = (unsigned short int) (2);
	KerArg0->OutFeatures = (unsigned short int) (18);
	KerArg0->Bias = (short int * __restrict__) (cnn_ssd_L1_Memory+1024);
	KerArg0->NormBias = (signed char) (13);
	KerArg1->In = (short int * __restrict__) (cnn_ssd_L1_Memory+0);
	KerArg1->W = (unsigned short int) (2);
	KerArg1->UsedW = (unsigned short int) (2);
	KerArg1->H = (unsigned short int) (2);
	KerArg1->InFeatures = (unsigned short int) (128);
	KerArg1->OutFeatures = (unsigned short int) (18);
	KerArg1->Filter = (short int * __restrict__) (cnn_ssd_L1_Memory+1060);
	KerArg1->Out = (int * __restrict__) (cnn_ssd_L1_Memory+42676);
	KerArg1->Norm = (unsigned char) (16);
	KerArg1->TotalInFeatures = (short int) (128);
	KerArg1->Pad = (v4s) ((v4s){1,1,1,1});
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (cnn_ssd_L1_Memory+42676);
	KerArg2->W = (unsigned short int) (2);
	KerArg2->H = (unsigned short int) (2);
	KerArg2->Out = (short int * __restrict__) (cnn_ssd_L1_Memory+42532);
	KerArg2->Norm = (unsigned char) (16);
	KerArg2->InFeatures = (unsigned short int) (18);
	KerArg2->LB = (int) (-32768);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+1024), 36, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Bias */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory+99824+0), 41472, 0, &UchanHF1);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read Filter */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+99824+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+1060), 41472, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Filter */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0), 1024, 0, &DmaR_Evt3);
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
				KerArg1->UsedH = (unsigned short int) (2);
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+58864+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+42532), 144, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+0), ((AT_HYPERRAM_INT_ADDR_TYPE) cnn_ssd_L2_Memory+58864+0), 144, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S55_Conv2d_24x128x3x3(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 46384 bytes, L2 buffer: 46000 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF1;
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
		[D1 Dim: Init: 24, Tiled: 1][Tile0 Dim: 1][D0 Dim: Init: 128, Tiled: 3]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 3 logical tiles, 3 physical tiles
			Total Size: 1024 [D0, [2 x 416, 192]][Tile0, 1:[2x2], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[2x3, 1:2x4, 2x3], 2][D0, [2 x 416, 192]]
		Tile0: [0, 416, 8], Tile1: [416, 416, 8], Tile2; [832, 192, 8]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 48 [D1, [0 x 48, 48]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 48, 48]]
		Tile0: [0, 48, 48], Tile1: [0, 48, 48], Tile2; [0, 48, 48]
	Ker Arg: Filter, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 3 logical tiles, 3 physical tiles
			Total Size: 55296 [D1, [0 x 55296, 55296]][D0, [2 x 22464, 10368]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 55296, 55296]][D0, [2 x 22464, 10368]]
		Tile0: [0, 22464, 22464], Tile1: [22464, 22464, 22464], Tile2; [44928, 10368, 10368]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 192 [D1, [0 x 192, 192]][Tile0, 1:[2x2], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 192, 192]][Tile0, 1:[2x2], 2]
		Tile0: [0, 192, 192], Tile1: [0, 192, 192], Tile2; [0, 192, 192]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 384 [D1, [0 x 384, 384]][Tile0, 1:[2x2], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 384, 384]][Tile0, 1:[2x2], 4]
		Tile0: [0, 384, 16], Tile1: [0, 384, 16], Tile2; [0, 384, 16]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (cnn_ssd_L1_Memory+46000);
	KerArg0->W = (unsigned short int) (2);
	KerArg0->H = (unsigned short int) (2);
	KerArg0->OutFeatures = (unsigned short int) (24);
	KerArg0->Bias = (short int * __restrict__) (cnn_ssd_L1_Memory+832);
	KerArg0->NormBias = (signed char) (14);
	KerArg1->W = (unsigned short int) (2);
	KerArg1->UsedW = (unsigned short int) (2);
	KerArg1->OutFeatures = (unsigned short int) (24);
	KerArg1->Out = (int * __restrict__) (cnn_ssd_L1_Memory+46000);
	KerArg1->Norm = (unsigned char) (16);
	KerArg1->Pad = (v4s) ((v4s){1,1,1,1});
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (cnn_ssd_L1_Memory+46000);
	KerArg2->W = (unsigned short int) (2);
	KerArg2->H = (unsigned short int) (2);
	KerArg2->Out = (short int * __restrict__) (cnn_ssd_L1_Memory+45808);
	KerArg2->Norm = (unsigned char) (16);
	KerArg2->InFeatures = (unsigned short int) (24);
	KerArg2->LB = (int) (-32768);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+0), 416, 8, 8, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+832), 48, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory+99824+0), 22464, 0, &UchanHF1);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read Filter */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+22464), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory+99824+22464), 22464, 0, &UchanHF1);
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+99824+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+880+0), 22464, 0, &DmaR_Evt3);
	_NN_Filter=22464; _SN_Filter=22464;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1, D1Ind_NextLast = 1, D1Ind_NextNextLast = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1, T0Ind_NextLast = 1;
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<3; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==2), D0Ind_NextLast = ((D0Ind+1)==2), D0Ind_NextNextLast = ((D0Ind+2)==2);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (416); _LN_In = (8); _SN_In = (((D0Ind_NextLast)?24:52)*_LN_In); 
				} else if (!(1)) {
					_N_In = _N_In + (-832); _LN_In = (8); _SN_In = (52*_LN_In); 
				}
				_SNN_Filter = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_Filter = _NN_Filter + ((22464)); _SNN_Filter = (((1)?(((1)?10368:22464)):(((1)?10368:22464)))); 
					} else if (!((1))) {
						_NN_Filter = _NN_Filter + ((-44928)); _SNN_Filter = (((1)?(22464):(22464))); 
					}
				} else if (!((1))) {
					_NN_Filter = _NN_Filter + ((22464)); _SNN_Filter = (((1)?(22464):(22464))); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+416*((D0Ind_Total+1)%2)),
							_SN_In, 8, _LN_In, 0, &DmaR_Evt1);
				}
				AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read Filter */
				if (_SNN_Filter) {
					AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+_NN_Filter), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory+99824+22464*((D0Ind_Total)%2)),
							_SNN_Filter, 0, &UchanHF1);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
				if (_SN_Filter) {
					AT_L2_COPY(0, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+99824+22464*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+880+22464*((D0Ind_Total+1)%2)),
							_SN_Filter, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (cnn_ssd_L1_Memory+0+416*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (4-1*(1)-1*(1));
				KerArg1->UsedH = (unsigned short int) (4-1*(1)-1*(1));
				KerArg1->InFeatures = (unsigned short int) (D0Ind_Last?24:52);
				KerArg1->Filter = (short int * __restrict__) (cnn_ssd_L1_Memory+880+22464*((D0Ind_Total)%2));
				KerArg1->TotalInFeatures = (short int) (D0Ind_Last?24:52);
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
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+58864+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+45808), 192, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+0), ((AT_HYPERRAM_INT_ADDR_TYPE) cnn_ssd_L2_Memory+58864+0), 192, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
int cnn_ssdCNN_Construct()

{
	AT_HYPERFLASH_FS_FC_EVENT UchanHF1;
	AT_HYPERFLASH_FS_CONF_T HyperFlashConf;
	int Error;
	AT_HYPERFLASH_FS_CONF_INIT(&HyperFlashConf, AT_MEM_L3_HFLASH, 0);
	AT_HYPERFLASH_FS_OPEN(&HyperFlash, &HyperFlashConf, "cnn_ssd_L3_Flash_Const.dat", &Error);
	if (Error) return 1;
	cnn_ssd_L2_Memory = (AT_L2_POINTER) AT_L2_ALLOC(0, 196592);
	if (cnn_ssd_L2_Memory == 0) return 3;
	cnn_ssd_L1_Memory = (AT_L1_POINTER) AT_L1_ALLOC(0, 47792);
	if (cnn_ssd_L1_Memory == 0) return 4;
	/* Moving Conv_0_weights, size 144 from HyperFlash at 761984 to (size 144) L2 at 29952..30095 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L3_Flash + 761984), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory + 29952), 144, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Constant_103, size 16 from HyperFlash at 762720 to (size 16) L2 at 30160..30175 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L3_Flash + 762720), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory + 30160), 16, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Conv_3_weights, size 2304 from HyperFlash at 759168 to (size 2304) L2 at 27648..29951 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L3_Flash + 759168), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory + 27648), 2304, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Constant_106, size 32 from HyperFlash at 762656 to (size 32) L2 at 30096..30127 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L3_Flash + 762656), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory + 30096), 32, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Conv_6_weights, size 4608 from HyperFlash at 754560 to (size 4608) L2 at 23040..27647 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L3_Flash + 754560), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory + 23040), 4608, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Constant_109, size 32 from HyperFlash at 762688 to (size 32) L2 at 30128..30159 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L3_Flash + 762688), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory + 30128), 32, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Conv_9_weights, size 9216 from HyperFlash at 745344 to (size 9216) L2 at 13824..23039 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L3_Flash + 745344), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory + 13824), 9216, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Constant_112, size 64 from HyperFlash at 762256 to (size 64) L2 at 58464..58527 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L3_Flash + 762256), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory + 58464), 64, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Constant_classification_headers.0.bias, size 36 from HyperFlash at 762512 to (size 36) L2 at 58720..58755 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L3_Flash + 762512), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory + 58720), 36, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Conv_12_weights, size 13824 from HyperFlash at 721152 to (size 13824) L2 at 0..13823 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L3_Flash + 721152), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory + 0), 13824, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Constant_regression_headers.0.bias, size 48 from HyperFlash at 762320 to (size 48) L2 at 58528..58575 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L3_Flash + 762320), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory + 58528), 48, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Constant_115, size 128 from HyperFlash at 762128 to (size 128) L2 at 58336..58463 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L3_Flash + 762128), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory + 58336), 128, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Constant_classification_headers.1.bias, size 36 from HyperFlash at 762548 to (size 36) L2 at 58756..58791 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L3_Flash + 762548), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory + 58756), 36, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Conv_17_weights, size 27648 from HyperFlash at 672768 to (size 27648) L2 at 30176..57823 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L3_Flash + 672768), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory + 30176), 27648, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Constant_regression_headers.1.bias, size 48 from HyperFlash at 762368 to (size 48) L2 at 58576..58623 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L3_Flash + 762368), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory + 58576), 48, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Constant_118, size 256 from HyperFlash at 761472 to (size 256) L2 at 57824..58079 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L3_Flash + 761472), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory + 57824), 256, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Constant_classification_headers.2.bias, size 36 from HyperFlash at 762584 to (size 36) L2 at 58792..58827 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L3_Flash + 762584), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory + 58792), 36, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Constant_regression_headers.2.bias, size 48 from HyperFlash at 762416 to (size 48) L2 at 58624..58671 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L3_Flash + 762416), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory + 58624), 48, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Constant_121, size 256 from HyperFlash at 761728 to (size 256) L2 at 58080..58335 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L3_Flash + 761728), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory + 58080), 256, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Constant_classification_headers.3.bias, size 36 from HyperFlash at 762620 to (size 36) L2 at 58828..58863 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L3_Flash + 762620), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory + 58828), 36, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Constant_regression_headers.3.bias, size 48 from HyperFlash at 762464 to (size 48) L2 at 58672..58719 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L3_Flash + 762464), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory + 58672), 48, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	return 0;
}
int cnn_ssdCNN_Destruct()

{
	AT_L2_FREE(0, cnn_ssd_L2_Memory, 196592);
	AT_L1_FREE(0, cnn_ssd_L1_Memory, 47792);
	AT_HYPERFLASH_FS_CLOSE(&HyperFlash);
	return 0;
}
unsigned int AT_GraphPerf[18];
unsigned int AT_GraphOperInfosNames[18] = {
	1679360,
	6000640,
	2974720,
	1484800,
	10240,
	1479680,
	5120,
	1477120,
	414720,
	552960,
	2048,
	590336,
	82944,
	110592,
	829440,
	1105920,
	1658880,
	2211840,
};
char *AT_GraphNodeNames[18] = {
	"S3_Conv2d_8x1x3x3_MaxPool_2x2_Relu",
	"S6_Conv2d_16x8x3x3_MaxPool_2x2_Relu",
	"S9_Conv2d_16x16x3x3_MaxPool_2x2_Relu",
	"S12_Conv2d_32x16x3x3_Relu",
	"S13_MaxPool_2x2",
	"S24_Conv2d_64x32x3x3_Relu",
	"S25_MaxPool_2x2",
	"S36_Conv2d_128x64x3x3_Relu",
	"S40_Conv2d_18x128x3x3",
	"S44_Conv2d_24x128x3x3",
	"S37_MaxPool_2x2",
	"S48_Conv2d_128x128x3x3_Relu",
	"S51_Conv2d_18x128x3x3",
	"S55_Conv2d_24x128x3x3",
	"S28_Conv2d_18x64x3x3",
	"S32_Conv2d_24x64x3x3",
	"S16_Conv2d_18x32x3x3",
	"S20_Conv2d_24x32x3x3",
};
int cnn_ssdCNN(
		signed short * __restrict__ Input_1,
		signed short * __restrict__ Output_1,
		signed short * __restrict__ Output_2,
		signed short * __restrict__ Output_3,
		signed short * __restrict__ Output_4,
		signed short * __restrict__ Output_5,
		signed short * __restrict__ Output_6,
		signed short * __restrict__ Output_7,
		signed short * __restrict__ Output_8)

{
	AT_HYPERFLASH_FS_CL_EVENT UchanHF0;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF1;
	AT_GraphPerf[0] = gap_cl_readhwtimer();
	S3_Conv2d_8x1x3x3_MaxPool_2x2_Relu(
		((signed short * __restrict__) Input_1), /* In */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+29952)), /* Filter */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+30160)), /* Bias */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+58864)) /* Out */
	);
	AT_GraphPerf[0] = gap_cl_readhwtimer() - AT_GraphPerf[0];
	AT_GraphPerf[1] = gap_cl_readhwtimer();
	S6_Conv2d_16x8x3x3_MaxPool_2x2_Relu(
		((signed short * __restrict__) (cnn_ssd_L2_Memory+58864)), /* In */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+27648)), /* Filter */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+30096)), /* Bias */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+140784)) /* Out */
	);
	AT_GraphPerf[1] = gap_cl_readhwtimer() - AT_GraphPerf[1];
	/* Moving Conv_14_weights, size 36864 from HyperFlash at 635904 to (size 36864) L2 at 99824 using event 0 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L3_Flash + 635904), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory + 99824), 36864, 0, &UchanHF0);
	AT_GraphPerf[2] = gap_cl_readhwtimer();
	S9_Conv2d_16x16x3x3_MaxPool_2x2_Relu(
		((signed short * __restrict__) (cnn_ssd_L2_Memory+140784)), /* In */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+23040)), /* Filter */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+30128)), /* Bias */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+58864)) /* Out */
	);
	AT_GraphPerf[2] = gap_cl_readhwtimer() - AT_GraphPerf[2];
	/* Moving Conv_21_weights, size 41472 from HyperFlash at 552960 to (size 41472) L2 at 155120 using event 1 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L3_Flash + 552960), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory + 155120), 41472, 0, &UchanHF1);
	AT_GraphPerf[3] = gap_cl_readhwtimer();
	S12_Conv2d_32x16x3x3_Relu(
		((signed short * __restrict__) (cnn_ssd_L2_Memory+58864)), /* In */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+13824)), /* Filter */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+58464)), /* Bias */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+69104)) /* Out */
	);
	AT_GraphPerf[3] = gap_cl_readhwtimer() - AT_GraphPerf[3];
	AT_GraphPerf[4] = gap_cl_readhwtimer();
	S13_MaxPool_2x2(
		((signed short * __restrict__) (cnn_ssd_L2_Memory+69104)), /* In */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+58864)) /* Out */
	);
	AT_GraphPerf[4] = gap_cl_readhwtimer() - AT_GraphPerf[4];
	/* Waiting completion of transfer of Conv_14_weights using event 0 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF0);
	AT_GraphPerf[5] = gap_cl_readhwtimer();
	S24_Conv2d_64x32x3x3_Relu(
		((signed short * __restrict__) (cnn_ssd_L2_Memory+58864)), /* In */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+99824)), /* Filter */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+58336)), /* Bias */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+89584)) /* Out */
	);
	AT_GraphPerf[5] = gap_cl_readhwtimer() - AT_GraphPerf[5];
	AT_GraphPerf[6] = gap_cl_readhwtimer();
	S25_MaxPool_2x2(
		((signed short * __restrict__) (cnn_ssd_L2_Memory+89584)), /* In */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+58864)) /* Out */
	);
	AT_GraphPerf[6] = gap_cl_readhwtimer() - AT_GraphPerf[6];
	AT_GraphPerf[7] = gap_cl_readhwtimer();
	S36_Conv2d_128x64x3x3_Relu(
		((signed short * __restrict__) (cnn_ssd_L2_Memory+58864)), /* In */
		((signed short * __restrict__) (cnn_ssd_L3_Flash+294912)), /* Filter */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+57824)), /* Bias */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+61424)) /* Out */
	);
	AT_GraphPerf[7] = gap_cl_readhwtimer() - AT_GraphPerf[7];
	/* Moving Conv_22_weights, size 55296 from HyperFlash at 442368 to (size 55296) L2 at 99824 using event 0 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L3_Flash + 442368), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory + 99824), 55296, 0, &UchanHF0);
	/* Waiting completion of transfer of Conv_21_weights using event 1 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1);
	AT_GraphPerf[8] = gap_cl_readhwtimer();
	S40_Conv2d_18x128x3x3(
		((signed short * __restrict__) (cnn_ssd_L2_Memory+61424)), /* In */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+155120)), /* Filter */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+58792)), /* Bias */
		((signed short * __restrict__) Output_5) /* Out */
	);
	AT_GraphPerf[8] = gap_cl_readhwtimer() - AT_GraphPerf[8];
	/* Waiting completion of transfer of Conv_22_weights using event 0 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF0);
	AT_GraphPerf[9] = gap_cl_readhwtimer();
	S44_Conv2d_24x128x3x3(
		((signed short * __restrict__) (cnn_ssd_L2_Memory+61424)), /* In */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+99824)), /* Filter */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+58624)), /* Bias */
		((signed short * __restrict__) Output_6) /* Out */
	);
	AT_GraphPerf[9] = gap_cl_readhwtimer() - AT_GraphPerf[9];
	/* Moving Conv_16_weights, size 20736 from HyperFlash at 700416 to (size 20736) L2 at 144752 using event 0 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L3_Flash + 700416), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory + 144752), 20736, 0, &UchanHF0);
	AT_GraphPerf[10] = gap_cl_readhwtimer();
	S37_MaxPool_2x2(
		((signed short * __restrict__) (cnn_ssd_L2_Memory+61424)), /* In */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+58864)) /* Out */
	);
	AT_GraphPerf[10] = gap_cl_readhwtimer() - AT_GraphPerf[10];
	AT_GraphPerf[11] = gap_cl_readhwtimer();
	S48_Conv2d_128x128x3x3_Relu(
		((signed short * __restrict__) (cnn_ssd_L2_Memory+58864)), /* In */
		((signed short * __restrict__) (cnn_ssd_L3_Flash+0)), /* Filter */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+58080)), /* Bias */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+59888)) /* Out */
	);
	AT_GraphPerf[11] = gap_cl_readhwtimer() - AT_GraphPerf[11];
	AT_GraphPerf[12] = gap_cl_readhwtimer();
	S51_Conv2d_18x128x3x3(
		((signed short * __restrict__) (cnn_ssd_L2_Memory+59888)), /* In */
		((signed short * __restrict__) (cnn_ssd_L3_Flash+594432)), /* Filter */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+58828)), /* Bias */
		((signed short * __restrict__) Output_7) /* Out */
	);
	AT_GraphPerf[12] = gap_cl_readhwtimer() - AT_GraphPerf[12];
	AT_GraphPerf[13] = gap_cl_readhwtimer();
	S55_Conv2d_24x128x3x3(
		((signed short * __restrict__) (cnn_ssd_L2_Memory+59888)), /* In */
		((signed short * __restrict__) (cnn_ssd_L3_Flash+497664)), /* Filter */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+58672)), /* Bias */
		((signed short * __restrict__) Output_8) /* Out */
	);
	AT_GraphPerf[13] = gap_cl_readhwtimer() - AT_GraphPerf[13];
	/* Moving Conv_11_weights, size 10368 from HyperFlash at 734976 to (size 10368) L2 at 127472 using event 1 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L3_Flash + 734976), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory + 127472), 10368, 0, &UchanHF1);
	/* Waiting completion of transfer of Conv_16_weights using event 0 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF0);
	AT_GraphPerf[14] = gap_cl_readhwtimer();
	S28_Conv2d_18x64x3x3(
		((signed short * __restrict__) (cnn_ssd_L2_Memory+89584)), /* In */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+144752)), /* Filter */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+58756)), /* Bias */
		((signed short * __restrict__) Output_3) /* Out */
	);
	AT_GraphPerf[14] = gap_cl_readhwtimer() - AT_GraphPerf[14];
	AT_GraphPerf[15] = gap_cl_readhwtimer();
	S32_Conv2d_24x64x3x3(
		((signed short * __restrict__) (cnn_ssd_L2_Memory+89584)), /* In */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+30176)), /* Filter */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+58576)), /* Bias */
		((signed short * __restrict__) Output_4) /* Out */
	);
	AT_GraphPerf[15] = gap_cl_readhwtimer() - AT_GraphPerf[15];
	/* Waiting completion of transfer of Conv_11_weights using event 1 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1);
	AT_GraphPerf[16] = gap_cl_readhwtimer();
	S16_Conv2d_18x32x3x3(
		((signed short * __restrict__) (cnn_ssd_L2_Memory+69104)), /* In */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+127472)), /* Filter */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+58720)), /* Bias */
		((signed short * __restrict__) Output_1) /* Out */
	);
	AT_GraphPerf[16] = gap_cl_readhwtimer() - AT_GraphPerf[16];
	AT_GraphPerf[17] = gap_cl_readhwtimer();
	S20_Conv2d_24x32x3x3(
		((signed short * __restrict__) (cnn_ssd_L2_Memory+69104)), /* In */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+0)), /* Filter */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+58528)), /* Bias */
		((signed short * __restrict__) Output_2) /* Out */
	);
	AT_GraphPerf[17] = gap_cl_readhwtimer() - AT_GraphPerf[17];
	return 0;
}
