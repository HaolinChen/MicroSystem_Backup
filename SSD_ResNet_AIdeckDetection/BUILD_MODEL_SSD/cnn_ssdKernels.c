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
	/* Shared L1: 15520 bytes, L2 buffer: 5280 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	KerSetBias_fpd_fp_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConv_DP_fp_T S_KerArg1, *KerArg1 = &S_KerArg1;
	KerDP_fp_T S_KerArg2, *KerArg2 = &S_KerArg2;
	KerReLUPool_fp_T S_KerArg3, *KerArg3 = &S_KerArg3;

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
		[D1 Dim: Init: 8, Tiled: 1][Tile0 Dim: 64][D0 Dim: Init: 1, Tiled: 1]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 64 logical tiles, 64 physical tiles
			Total Size: 81920 [D1, [0 x 81920, 81920]][Tile0, 64:[80x1, 62:80x1, 80x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 81920, 81920]][Tile0, 64:[80x1, 62:80x1, 80x1], 2]
		Tile0: [0, 1280, 160], Tile1: [160, 1280, 160], Tile2; [320, 1280, 160]
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
		KerArgItSpace: 64 logical tiles, 64 physical tiles
			Total Size: 40960 [D0, [0 x 40960, 40960]][Tile0, 64:[160x3, 62:160x4, 160x3], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 64:[160x2], 2][D0, [0 x 40960, 40960]]
		Tile0: [0, 960, 960], Tile1: [320, 1280, 1280], Tile2; [960, 1280, 1280]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 64 logical tiles, 1 physical tiles
			Total Size: 655360 [D1, [0 x 655360, 655360]][Tile0, 64:[160x2, 62:160x2, 160x2], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 655360, 655360]][Tile0, 64:[160x2, 62:160x2, 160x2], 4]
		Tile0: [0, 10240, 1280], Tile1: [0, 10240, 1280], Tile2; [0, 10240, 1280]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (cnn_ssd_L1_Memory+5280);
	KerArg0->W = (unsigned short int) (160);
	KerArg0->H = (unsigned short int) (2);
	KerArg0->OutFeatures = (unsigned short int) (8);
	KerArg0->Bias = (short int * __restrict__) (cnn_ssd_L1_Memory+2560);
	KerArg0->NormBias = (signed char) (13);
	KerArg1->W = (unsigned short int) (160);
	KerArg1->UsedW = (unsigned short int) (160);
	KerArg1->InFeatures = (unsigned short int) (1);
	KerArg1->OutFeatures = (unsigned short int) (8);
	KerArg1->Filter = (short int * __restrict__) (cnn_ssd_L1_Memory+2576);
	KerArg1->Out = (int * __restrict__) (cnn_ssd_L1_Memory+5280);
	KerArg1->Norm = (unsigned char) (15);
	KerArg1->TotalInFeatures = (short int) (1);
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (cnn_ssd_L1_Memory+5280);
	KerArg2->W = (unsigned short int) (160);
	KerArg2->H = (unsigned short int) (2);
	KerArg2->Out = (short int * __restrict__) (cnn_ssd_L1_Memory+5280);
	KerArg2->Norm = (unsigned char) (15);
	KerArg2->InFeatures = (unsigned short int) (8);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	KerArg3->In = (short int * __restrict__) (cnn_ssd_L1_Memory+5280);
	KerArg3->W = (unsigned short int) (160);
	KerArg3->UsedW = (unsigned short int) (160);
	KerArg3->H = (unsigned short int) (2);
	KerArg3->UsedH = (unsigned short int) (2);
	KerArg3->OutFeatures = (unsigned short int) (8);
	KerArg3->Pad = (v4s) 0;
	KerArg3->Orientation = (unsigned char) (1);
	KerArg3->Oper = (unsigned char) (1);
	KerArg3->LB = (int) (0);
	KerArg3->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	_C_Out=0; _SC_Out=1280; _LC_Out=160;
	_SPP_Out=0; _SP_Out=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+2560), 16, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+2576), 144, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Filter */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+0), 960, 0, &DmaR_Evt3);
	_N_In=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<64; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==63), T0Ind_NextLast = ((T0Ind+1)==63);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			{ /* Single iteration on D0 */
				int D0Ind_Last = 1, D0Ind_NextLast = 1;
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(T0Ind_Last)) {
					_N_In = _N_In + (640-(320*(T0Ind==0))); _SN_In = (1*((T0Ind_NextLast)?960:1280)); 
				} else if (!(1)) {
					_N_In = _N_In + (-40000); _SN_In = (1*(960)); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+1280*((D0Ind_Total+1)%2)),
							_SN_In, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (cnn_ssd_L1_Memory+0+1280*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (4-1*(T0Ind==0)-1*(T0Ind_Last));
				KerArg1->UsedH = (unsigned short int) (4-1*(T0Ind==0)-1*(T0Ind_Last));
				KerArg1->Pad = (v4s) ((v4s){1,1,1*(T0Ind==0),1*(T0Ind_Last)});
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				/*============================= End Update Arg Pipeline =============================*/
				D0Ind_Total++;
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerDP_IO_fp, (void *) KerArg2);
			__CALL(KerDP_IO_fp, KerArg2);
			KerArg3->Out = (short int * __restrict__) (cnn_ssd_L1_Memory+2720+1280*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerParPool2x2Stride2_fp, (void *) KerArg3);
			__CALL(KerParPool2x2Stride2_fp, KerArg3);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) cnn_ssd_L2_Memory+3568+1280*((T0Ind_Total+-1)%2)),
						_SP_Out, 10240, _LP_Out, 1, &UchanHR1);
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+3568+1280*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+2720+1280*((T0Ind_Total)%2)),
					_SC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
			_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (160); _LC_Out = (160); _SC_Out = (8*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) cnn_ssd_L2_Memory+3568+1280*((T0Ind_Total+-1)%2)), _SP_Out, 10240, _LP_Out, 1, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S6_Conv2d_16x8x3x3_MaxPool_2x2_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 16544 bytes, L2 buffer: 6304 bytes */
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
	KerReLUPool_fp_T S_KerArg3, *KerArg3 = &S_KerArg3;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Last, D1Ind_NextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast, T0Ind_NextNextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast, D0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	unsigned int _LPP_Out, _LP_Out, _LC_Out;
	unsigned int _N_Filter;
	unsigned int _SN_Filter;
	unsigned int _NN_In;
	unsigned int _SN_In, _SNN_In;
	unsigned int _LN_In, _LNN_In;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 16, Tiled: 1][Tile0 Dim: 32][D0 Dim: Init: 8, Tiled: 4]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 32 logical tiles, 32 physical tiles
			Total Size: 40960 [D1, [0 x 40960, 40960]][Tile0, 32:[40x1, 30:40x1, 40x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 40960, 40960]][Tile0, 32:[40x1, 30:40x1, 40x1], 2]
		Tile0: [0, 1280, 80], Tile1: [80, 1280, 80], Tile2; [160, 1280, 80]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 32 [D1, [0 x 32, 32]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 32, 32]]
		Tile0: [0, 32, 32], Tile1: [0, 32, 32], Tile2; [0, 32, 32]
	Ker Arg: Filter, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 4 logical tiles, 4 physical tiles
			Total Size: 2304 [D1, [0 x 2304, 2304]][D0, [3 x 576, 576]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 2304, 2304]][D0, [3 x 576, 576]]
		Tile0: [0, 576, 576], Tile1: [576, 576, 576], Tile2; [1152, 576, 576]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 128 logical tiles, 128 physical tiles
			Total Size: 81920 [D0, [3 x 20480, 20480]][Tile0, 32:[80x3, 30:80x4, 80x3], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 32:[80x3, 2:80x4, 80x3], 2][D0, [3 x 20480, 20480]]
		Tile0: [0, 960, 480], Tile1: [20480, 960, 480], Tile2; [40960, 960, 480]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 32 logical tiles, 1 physical tiles
			Total Size: 327680 [D1, [0 x 327680, 327680]][Tile0, 32:[80x2, 30:80x2, 80x2], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 327680, 327680]][Tile0, 32:[80x2, 30:80x2, 80x2], 4]
		Tile0: [0, 10240, 640], Tile1: [0, 10240, 640], Tile2; [0, 10240, 640]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (cnn_ssd_L1_Memory+6304);
	KerArg0->W = (unsigned short int) (80);
	KerArg0->H = (unsigned short int) (2);
	KerArg0->OutFeatures = (unsigned short int) (16);
	KerArg0->Bias = (short int * __restrict__) (cnn_ssd_L1_Memory+2560);
	KerArg0->NormBias = (signed char) (13);
	KerArg1->W = (unsigned short int) (80);
	KerArg1->UsedW = (unsigned short int) (80);
	KerArg1->InFeatures = (unsigned short int) (2);
	KerArg1->OutFeatures = (unsigned short int) (16);
	KerArg1->Out = (int * __restrict__) (cnn_ssd_L1_Memory+6304);
	KerArg1->Norm = (unsigned char) (14);
	KerArg1->TotalInFeatures = (short int) (2);
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (cnn_ssd_L1_Memory+6304);
	KerArg2->W = (unsigned short int) (80);
	KerArg2->H = (unsigned short int) (2);
	KerArg2->Out = (short int * __restrict__) (cnn_ssd_L1_Memory+6304);
	KerArg2->Norm = (unsigned char) (14);
	KerArg2->InFeatures = (unsigned short int) (16);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	KerArg3->In = (short int * __restrict__) (cnn_ssd_L1_Memory+6304);
	KerArg3->W = (unsigned short int) (80);
	KerArg3->UsedW = (unsigned short int) (80);
	KerArg3->H = (unsigned short int) (2);
	KerArg3->UsedH = (unsigned short int) (2);
	KerArg3->OutFeatures = (unsigned short int) (16);
	KerArg3->Pad = (v4s) 0;
	KerArg3->Orientation = (unsigned char) (1);
	KerArg3->Oper = (unsigned char) (1);
	KerArg3->LB = (int) (0);
	KerArg3->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	_C_Out=0; _SC_Out=1280; _LC_Out=80;
	_SPP_Out=0; _SP_Out=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+2560), 32, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+2592+0), 576, 0, &DmaR_Evt2);
	_N_Filter=0;
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) cnn_ssd_L2_Memory+3568+0), 960, 10240, 480, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+20480), ((AT_HYPERRAM_INT_ADDR_TYPE) cnn_ssd_L2_Memory+3568+1280), 960, 10240, 480, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+3568+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+0), 960, 0, &DmaR_Evt3);
	_NN_In=20480; _SN_In=960;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1, D1Ind_NextLast = 1;
		for (T0Ind=0; T0Ind<32; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==31), T0Ind_NextLast = ((T0Ind+1)==31), T0Ind_NextNextLast = ((T0Ind+2)==31);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<4; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==3), D0Ind_NextLast = ((D0Ind+1)==3), D0Ind_NextNextLast = ((D0Ind+2)==3);
				/*================================= Prepare Tiles ===================================*/
				_SN_Filter = 0;
				if (!(D0Ind_Last)) {
					_N_Filter = _N_Filter + ((576)); _SN_Filter = (((1)?(576):(576))); 
				} else if (!((T0Ind_Last))) {
					_N_Filter = _N_Filter + ((-1728)); _SN_Filter = (((1)?(576):(576))); 
				}
				_SNN_In = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_In = _NN_In + (20480); _LNN_In = ((T0Ind_Last)?480:(640-160*(T0Ind==0))); _SNN_In = (2*_LNN_In); 
					} else if (!(T0Ind_Last)) {
						_NN_In = _NN_In + (320-(160*(T0Ind==0)))+(-61440); _LNN_In = ((T0Ind_NextLast)?480:640); _SNN_In = (2*_LNN_In); 
					} else if (!(1)) {
						_NN_In = _NN_In + (-9760)+(-61440); _LNN_In = (480); _SNN_In = (2*_LNN_In); 
					}
				} else if (!(T0Ind_Last)) {
					_NN_In = _NN_In + (20480); _LNN_In = ((T0Ind_NextLast)?480:640); _SNN_In = (2*_LNN_In); 
				} else if (!((1))) {
					_NN_In = _NN_In + (20480); _LNN_In = (480); _SNN_In = (2*_LNN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Filter */
				if (_SN_Filter) {
					AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+_N_Filter), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+2592+576*((D0Ind_Total+1)%2)),
							_SN_Filter, 0, &DmaR_Evt2);
				}
				AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
				if (_SNN_In) {
					AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) cnn_ssd_L2_Memory+3568+1280*((D0Ind_Total)%2)),
							_SNN_In, 10240, _LNN_In, 0, &UchanHR1);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+3568+1280*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+1280*((D0Ind_Total+1)%2)),
							_SN_In, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (cnn_ssd_L1_Memory+0+1280*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (4-1*(T0Ind==0)-1*(T0Ind_Last));
				KerArg1->UsedH = (unsigned short int) (4-1*(T0Ind==0)-1*(T0Ind_Last));
				KerArg1->Filter = (short int * __restrict__) (cnn_ssd_L1_Memory+2592+576*((D0Ind_Total)%2));
				KerArg1->Pad = (v4s) ((v4s){1,1,1*(T0Ind==0),1*(T0Ind_Last)});
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				_SN_In = _SNN_In;_LN_In = _LNN_In;
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerDP_IO_fp, (void *) KerArg2);
			__CALL(KerDP_IO_fp, KerArg2);
			KerArg3->Out = (short int * __restrict__) (cnn_ssd_L1_Memory+3744+1280*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerParPool2x2Stride2_fp, (void *) KerArg3);
			__CALL(KerParPool2x2Stride2_fp, KerArg3);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) cnn_ssd_L2_Memory+6128+1280*((T0Ind_Total+-1)%2)),
						_SP_Out, 2560, _LP_Out, 1, &UchanHR2);
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+6128+1280*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+3744+1280*((T0Ind_Total)%2)),
					_SC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
			_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (80); _LC_Out = (80); _SC_Out = (16*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) cnn_ssd_L2_Memory+6128+1280*((T0Ind_Total+-1)%2)), _SP_Out, 2560, _LP_Out, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S9_Conv2d_16x16x3x3_MaxPool_2x2_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 16160 bytes, L2 buffer: 11040 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	KerSetBias_fpd_fp_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConv_DP_fp_T S_KerArg1, *KerArg1 = &S_KerArg1;
	KerDP_fp_T S_KerArg2, *KerArg2 = &S_KerArg2;
	KerReLUPool_fp_T S_KerArg3, *KerArg3 = &S_KerArg3;

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
		[D1 Dim: Init: 16, Tiled: 1][Tile0 Dim: 16][D0 Dim: Init: 16, Tiled: 2]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 16 logical tiles, 16 physical tiles
			Total Size: 10240 [D1, [0 x 10240, 10240]][Tile0, 16:[20x1, 14:20x1, 20x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 10240, 10240]][Tile0, 16:[20x1, 14:20x1, 20x1], 2]
		Tile0: [0, 640, 40], Tile1: [40, 640, 40], Tile2; [80, 640, 40]
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
			Total Size: 4608 [D1, [0 x 4608, 4608]][D0, [1 x 2304, 2304]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 4608, 4608]][D0, [1 x 2304, 2304]]
		Tile0: [0, 4608, 4608], Tile1: [0, 4608, 4608], Tile2; [0, 4608, 4608]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 32 logical tiles, 32 physical tiles
			Total Size: 40960 [D0, [1 x 20480, 20480]][Tile0, 16:[40x3, 14:40x4, 40x3], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 16:[40x3, 40x3], 2][D0, [1 x 20480, 20480]]
		Tile0: [0, 1920, 240], Tile1: [20480, 1920, 240], Tile2; [80, 2560, 320]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 16 logical tiles, 1 physical tiles
			Total Size: 81920 [D1, [0 x 81920, 81920]][Tile0, 16:[40x2, 14:40x2, 40x2], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 81920, 81920]][Tile0, 16:[40x2, 14:40x2, 40x2], 4]
		Tile0: [0, 5120, 320], Tile1: [0, 5120, 320], Tile2; [0, 5120, 320]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (cnn_ssd_L1_Memory+11040);
	KerArg0->W = (unsigned short int) (40);
	KerArg0->H = (unsigned short int) (2);
	KerArg0->OutFeatures = (unsigned short int) (16);
	KerArg0->Bias = (short int * __restrict__) (cnn_ssd_L1_Memory+5120);
	KerArg0->NormBias = (signed char) (13);
	KerArg1->W = (unsigned short int) (40);
	KerArg1->UsedW = (unsigned short int) (40);
	KerArg1->InFeatures = (unsigned short int) (8);
	KerArg1->OutFeatures = (unsigned short int) (16);
	KerArg1->Filter = (short int * __restrict__) (cnn_ssd_L1_Memory+5152);
	KerArg1->Out = (int * __restrict__) (cnn_ssd_L1_Memory+11040);
	KerArg1->Norm = (unsigned char) (14);
	KerArg1->TotalInFeatures = (short int) (16);
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (cnn_ssd_L1_Memory+11040);
	KerArg2->W = (unsigned short int) (40);
	KerArg2->H = (unsigned short int) (2);
	KerArg2->Out = (short int * __restrict__) (cnn_ssd_L1_Memory+11040);
	KerArg2->Norm = (unsigned char) (14);
	KerArg2->InFeatures = (unsigned short int) (16);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	KerArg3->In = (short int * __restrict__) (cnn_ssd_L1_Memory+11040);
	KerArg3->W = (unsigned short int) (40);
	KerArg3->UsedW = (unsigned short int) (40);
	KerArg3->H = (unsigned short int) (2);
	KerArg3->UsedH = (unsigned short int) (2);
	KerArg3->OutFeatures = (unsigned short int) (16);
	KerArg3->Pad = (v4s) 0;
	KerArg3->Orientation = (unsigned char) (1);
	KerArg3->Oper = (unsigned char) (1);
	KerArg3->LB = (int) (0);
	KerArg3->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	_C_Out=0; _SC_Out=640; _LC_Out=40;
	_SP_Out=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+5120), 32, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+5152), 4608, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Filter */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) cnn_ssd_L2_Memory+13808+0), 1920, 2560, 240, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+20480), ((AT_HYPERRAM_INT_ADDR_TYPE) cnn_ssd_L2_Memory+13808+2560), 1920, 2560, 240, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+13808+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+0), 1920, 0, &DmaR_Evt3);
	_NN_In=20480; _SN_In=1920;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<16; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==15), T0Ind_NextLast = ((T0Ind+1)==15), T0Ind_NextNextLast = ((T0Ind+2)==15);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<2; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==1), D0Ind_NextLast = ((D0Ind+1)==1), D0Ind_NextNextLast = ((D0Ind+2)==1);
				/*================================= Prepare Tiles ===================================*/
				_SNN_In = 0;
				if (!(D0Ind_Last)) {
					if (!(1)) {
						_NN_In = _NN_In + (20480); _LNN_In = ((T0Ind_Last)?240:(320-80*(T0Ind==0))); _SNN_In = (8*_LNN_In); 
					} else if (!(T0Ind_Last)) {
						_NN_In = _NN_In + (160-(80*(T0Ind==0)))+(-20480); _LNN_In = ((T0Ind_NextLast)?240:320); _SNN_In = (8*_LNN_In); 
					} else if (!(1)) {
						_NN_In = _NN_In + (-2320)+(-20480); _LNN_In = (240); _SNN_In = (8*_LNN_In); 
					}
				} else if (!(T0Ind_Last)) {
					_NN_In = _NN_In + (20480); _LNN_In = ((T0Ind_NextLast)?240:320); _SNN_In = (8*_LNN_In); 
				} else if (!((1))) {
					_NN_In = _NN_In + (20480); _LNN_In = (240); _SNN_In = (8*_LNN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
				if (_SNN_In) {
					AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) cnn_ssd_L2_Memory+13808+2560*((D0Ind_Total)%2)),
							_SNN_In, 2560, _LNN_In, 0, &UchanHR1);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+13808+2560*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+2560*((D0Ind_Total+1)%2)),
							_SN_In, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (cnn_ssd_L1_Memory+0+2560*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (4-1*(T0Ind==0)-1*(T0Ind_Last));
				KerArg1->UsedH = (unsigned short int) (4-1*(T0Ind==0)-1*(T0Ind_Last));
				KerArg1->Filter = (short int * __restrict__) (cnn_ssd_L1_Memory+5152+((D0Ind)*144));
				KerArg1->Pad = (v4s) ((v4s){1,1,1*(T0Ind==0),1*(T0Ind_Last)});
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				_SN_In = _SNN_In;_LN_In = _LNN_In;
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerDP_IO_fp, (void *) KerArg2);
			__CALL(KerDP_IO_fp, KerArg2);
			KerArg3->Out = (short int * __restrict__) (cnn_ssd_L1_Memory+9760+640*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerParPool2x2Stride2_fp, (void *) KerArg3);
			__CALL(KerParPool2x2Stride2_fp, KerArg3);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+9760+640*((T0Ind_Total)%2)),
					_SC_Out, 640, _LC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (40); _LC_Out = (40); _SC_Out = (16*_LC_Out); 
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
	/* Shared L1: 16320 bytes, L2 buffer: 13760 bytes */
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
		[D1 Dim: Init: 32, Tiled: 1][Tile0 Dim: 16][D0 Dim: Init: 16, Tiled: 2]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 32 logical tiles, 32 physical tiles
			Total Size: 10240 [D0, [1 x 5120, 5120]][Tile0, 16:[20x2, 14:20x3, 20x2], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 16:[20x2, 20x2], 2][D0, [1 x 5120, 5120]]
		Tile0: [0, 640, 80], Tile1: [5120, 640, 80], Tile2; [0, 960, 120]
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
			Total Size: 9216 [D1, [0 x 9216, 9216]][D0, [1 x 4608, 4608]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 9216, 9216]][D0, [1 x 4608, 4608]]
		Tile0: [0, 9216, 9216], Tile1: [0, 9216, 9216], Tile2; [0, 9216, 9216]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 16 logical tiles, 16 physical tiles
			Total Size: 20480 [D1, [0 x 20480, 20480]][Tile0, 16:[20x1, 14:20x1, 20x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 20480, 20480]][Tile0, 16:[20x1, 14:20x1, 20x1], 2]
		Tile0: [0, 1280, 40], Tile1: [40, 1280, 40], Tile2; [80, 1280, 40]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 16 logical tiles, 1 physical tiles
			Total Size: 40960 [D1, [0 x 40960, 40960]][Tile0, 16:[20x1, 14:20x1, 20x1], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 40960, 40960]][Tile0, 16:[20x1, 14:20x1, 20x1], 4]
		Tile0: [0, 2560, 80], Tile1: [0, 2560, 80], Tile2; [0, 2560, 80]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (cnn_ssd_L1_Memory+13760);
	KerArg0->W = (unsigned short int) (20);
	KerArg0->H = (unsigned short int) (1);
	KerArg0->OutFeatures = (unsigned short int) (32);
	KerArg0->Bias = (short int * __restrict__) (cnn_ssd_L1_Memory+1920);
	KerArg0->NormBias = (signed char) (14);
	KerArg1->W = (unsigned short int) (20);
	KerArg1->UsedW = (unsigned short int) (20);
	KerArg1->InFeatures = (unsigned short int) (8);
	KerArg1->OutFeatures = (unsigned short int) (32);
	KerArg1->Filter = (short int * __restrict__) (cnn_ssd_L1_Memory+1984);
	KerArg1->Out = (int * __restrict__) (cnn_ssd_L1_Memory+13760);
	KerArg1->Norm = (unsigned char) (14);
	KerArg1->TotalInFeatures = (short int) (16);
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (cnn_ssd_L1_Memory+13760);
	KerArg2->W = (unsigned short int) (20);
	KerArg2->H = (unsigned short int) (1);
	KerArg2->Norm = (unsigned char) (14);
	KerArg2->InFeatures = (unsigned short int) (32);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+0), 640, 640, 80, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+1920), 64, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory+34288+0), 9216, 0, &UchanHF1);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read Filter */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+34288+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+1984), 9216, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
	_C_Out=0; _SC_Out=1280; _LC_Out=40;
	_SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<16; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==15), T0Ind_NextLast = ((T0Ind+1)==15);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<2; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==1), D0Ind_NextLast = ((D0Ind+1)==1);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (5120); _LN_In = ((T0Ind_Last)?80:(120-40*(T0Ind==0))); _SN_In = (8*_LN_In); 
				} else if (!(T0Ind_Last)) {
					_N_In = _N_In + (40-(40*(T0Ind==0)))+(-5120); _LN_In = ((T0Ind_NextLast)?80:120); _SN_In = (8*_LN_In); 
				} else if (!(1)) {
					_N_In = _N_In + (-560)+(-5120); _LN_In = (80); _SN_In = (8*_LN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+960*((D0Ind_Total+1)%2)),
							_SN_In, 640, _LN_In, 0, &DmaR_Evt1);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (cnn_ssd_L1_Memory+0+960*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (3-1*(T0Ind==0)-1*(T0Ind_Last));
				KerArg1->UsedH = (unsigned short int) (3-1*(T0Ind==0)-1*(T0Ind_Last));
				KerArg1->Filter = (short int * __restrict__) (cnn_ssd_L1_Memory+1984+((D0Ind)*144));
				KerArg1->Pad = (v4s) ((v4s){1,1,1*(T0Ind==0),1*(T0Ind_Last)});
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->Out = (short int * __restrict__) (cnn_ssd_L1_Memory+11200+1280*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+11200+1280*((T0Ind_Total)%2)),
					_SC_Out, 640, _LC_Out, 1, &DmaW_Evt1);
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
void S13_MaxPool_2x2(
		short int * __restrict__ In,
		short int * __restrict__ Out)

{
	/* Shared L1: 12800 bytes, L2 buffer: 12800 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaW_Evt1;
	KerReLUPool_fp_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int D0Ind, D0Ind_Last, D0Ind_NextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast;
	/* User kernel arguments related variables */
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	unsigned int _LP_Out, _LC_Out;
	unsigned int _N_In;
	unsigned int _SN_In;
	unsigned int _LN_In;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D0 Dim: Init: 32, Tiled: 1][Tile0 Dim: 4]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 4 logical tiles, 4 physical tiles
			Total Size: 5120 [D0, [0 x 5120, 5120]][Tile0, 4:[10x2, 2:10x2, 10x2], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 5120, 5120]][Tile0, 4:[10x2, 2:10x2, 10x2], 2]
		Tile0: [0, 1280, 40], Tile1: [40, 1280, 40], Tile2; [80, 1280, 40]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 4 logical tiles, 4 physical tiles
			Total Size: 20480 [D0, [0 x 20480, 20480]][Tile0, 4:[20x4, 2:20x4, 20x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 20480, 20480]][Tile0, 4:[20x4, 2:20x4, 20x4], 2]
		Tile0: [0, 5120, 160], Tile1: [160, 5120, 160], Tile2; [320, 5120, 160]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->W = (unsigned short int) (20);
	KerArg0->UsedW = (unsigned short int) (20);
	KerArg0->H = (unsigned short int) (4);
	KerArg0->UsedH = (unsigned short int) (4);
	KerArg0->OutFeatures = (unsigned short int) (32);
	KerArg0->Pad = (v4s) 0;
	KerArg0->Orientation = (unsigned char) (1);
	KerArg0->Oper = (unsigned char) (0);
	KerArg0->LB = (int) (-32768);
	KerArg0->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	_C_Out=0; _SC_Out=1280; _LC_Out=40;
	_SP_Out=0;
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+0), 5120, 640, 160, 0, &DmaR_Evt1);
	_N_In=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D0 */
		int D0Ind_Last = 1, D0Ind_NextLast = 1;
		for (T0Ind=0; T0Ind<4; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==3), T0Ind_NextLast = ((T0Ind+1)==3);
			/*================================= Prepare Tiles ===================================*/
			_SN_In = 0;
			if (!(T0Ind_Last)) {
				_N_In = _N_In + (160); _LN_In = (160); _SN_In = (32*_LN_In); 
			}
			/*============================= End Prepare Tiles ===================================*/
			/*================================= Read Tiles ======================================*/
			AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
			if (_SN_In) {
				AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+5120*((T0Ind_Total+1)%2)),
						_SN_In, 640, _LN_In, 0, &DmaR_Evt1);
			}
			/*============================= End Read Tiles ======================================*/
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In = (short int * __restrict__) (cnn_ssd_L1_Memory+0+5120*((T0Ind_Total)%2));
			KerArg0->Out = (short int * __restrict__) (cnn_ssd_L1_Memory+10240+1280*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerParPool2x2Stride2_fp, (void *) KerArg0);
			__CALL(KerParPool2x2Stride2_fp, KerArg0);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+10240+1280*((T0Ind_Total)%2)),
					_SC_Out, 160, _LC_Out, 1, &DmaW_Evt1);
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
	} /* End iteration on D0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S16_Conv2d_18x32x3x3(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 16228 bytes, L2 buffer: 10468 bytes */
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
		[D1 Dim: Init: 18, Tiled: 3][Tile0 Dim: 2][D0 Dim: Init: 32, Tiled: 8]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 16 logical tiles, 16 physical tiles
			Total Size: 20480 [D0, [7 x 2560, 2560]][Tile0, 2:[20x10, 20x8], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 2:[20x10, 6:20x11, 20x8], 2][D0, [7 x 2560, 2560]]
		Tile0: [0, 1600, 400], Tile1: [2560, 1600, 400], Tile2; [5120, 1600, 400]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 3 logical tiles, 1 physical tiles
			Total Size: 36 [D1, [2 x 16, 4]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [2 x 16, 4]]
		Tile0: [0, 36, 36], Tile1: [0, 36, 36], Tile2; [0, 36, 36]
	Ker Arg: Filter, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 24 logical tiles, 24 physical tiles
			Total Size: 10368 [D1, [2 x 4608, 1152]][D0, [7 x 576, 576]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [2 x 4608, 1152]][D0, [7 x 576, 576]]
		Tile0: [0, 576, 576], Tile1: [576, 576, 576], Tile2; [1152, 576, 576]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 6 logical tiles, 6 physical tiles
			Total Size: 11520 [D1, [2 x 5120, 1280]][Tile0, 2:[20x9, 20x7], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [2 x 5120, 1280]][Tile0, 2:[20x9, 20x7], 2]
		Tile0: [0, 2880, 360], Tile1: [360, 2240, 280], Tile2; [5120, 2880, 360]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 6 logical tiles, 1 physical tiles
			Total Size: 23040 [D1, [2 x 10240, 2560]][Tile0, 2:[20x9, 20x7], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [2 x 10240, 2560]][Tile0, 2:[20x9, 20x7], 4]
		Tile0: [0, 5760, 720], Tile1: [0, 5760, 720], Tile2; [0, 5760, 720]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (cnn_ssd_L1_Memory+10468);
	KerArg0->W = (unsigned short int) (20);
	KerArg0->NormBias = (signed char) (13);
	KerArg1->W = (unsigned short int) (20);
	KerArg1->UsedW = (unsigned short int) (20);
	KerArg1->InFeatures = (unsigned short int) (4);
	KerArg1->Out = (int * __restrict__) (cnn_ssd_L1_Memory+10468);
	KerArg1->Norm = (unsigned char) (16);
	KerArg1->TotalInFeatures = (short int) (4);
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (cnn_ssd_L1_Memory+10468);
	KerArg2->W = (unsigned short int) (20);
	KerArg2->Norm = (unsigned char) (16);
	KerArg2->LB = (int) (-32768);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+0), 1600, 640, 400, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+3520), 36, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory+9328+0), 576, 0, &UchanHF1);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read Filter */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+576), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory+9328+576), 576, 0, &UchanHF1);
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+9328+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+3556+0), 576, 0, &DmaR_Evt3);
	_NN_Filter=576; _SN_Filter=576;
	_C_Out=0; _SC_Out=2880; _LC_Out=360;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	for (D1Ind=0; D1Ind<3; D1Ind++) { /* Iteration on D1 */
		int D1Ind_Last = (D1Ind==2), D1Ind_NextLast = ((D1Ind+1)==2), D1Ind_NextNextLast = ((D1Ind+2)==2);
		for (T0Ind=0; T0Ind<2; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==1), T0Ind_NextLast = ((T0Ind+1)==1);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->H = (unsigned short int) (T0Ind_Last?7:9);
			KerArg0->OutFeatures = (unsigned short int) (D1Ind_Last?2:8);
			KerArg0->Bias = (short int * __restrict__) (cnn_ssd_L1_Memory+3520+((D1Ind)*16));
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<8; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==7), D0Ind_NextLast = ((D0Ind+1)==7), D0Ind_NextNextLast = ((D0Ind+2)==7);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (2560); _LN_In = ((T0Ind_Last)?320:(440-40*(T0Ind==0))); _SN_In = (4*_LN_In); 
				} else if (!(T0Ind_Last)) {
					_N_In = _N_In + (360-(40*(T0Ind==0)))+(-17920); _LN_In = ((1)?320:440); _SN_In = (4*_LN_In); 
				} else if (!(D1Ind_Last)) {
					_N_In = _N_In + (-320)+(-17920); _LN_In = (400); _SN_In = (4*_LN_In); 
				}
				_SNN_Filter = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_Filter = _NN_Filter + (((D1Ind_Last)?(144):(576))); _SNN_Filter = (((D1Ind_Last)?(144):(576))); 
					} else if (!((T0Ind_Last))) {
						_NN_Filter = _NN_Filter + (((D1Ind_Last)?(-1008):(-4032))); _SNN_Filter = (((D1Ind_Last)?(144):(576))); 
					} else if (!(D1Ind_Last)) {
						_NN_Filter = _NN_Filter + (4608)+(((D1Ind_Last)?(-1008):(-4032))); _SNN_Filter = (((D1Ind_NextLast)?(144):(576))); 
					}
				} else if (!((T0Ind_Last))) {
					_NN_Filter = _NN_Filter + (((D1Ind_Last)?(144):(576))); _SNN_Filter = (((D1Ind_Last)?(144):(576))); 
				} else if (!(D1Ind_Last)) {
					_NN_Filter = _NN_Filter + (((D1Ind_NextLast)?(144):(576))); _SNN_Filter = (((D1Ind_NextLast)?(144):(576))); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+1760*((D0Ind_Total+1)%2)),
							_SN_In, 640, _LN_In, 0, &DmaR_Evt1);
				}
				AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read Filter */
				if (_SNN_Filter) {
					AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+_NN_Filter), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory+9328+576*((D0Ind_Total)%2)),
							_SNN_Filter, 0, &UchanHF1);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
				if (_SN_Filter) {
					AT_L2_COPY(0, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+9328+576*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+3556+576*((D0Ind_Total+1)%2)),
							_SN_Filter, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (cnn_ssd_L1_Memory+0+1760*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (((T0Ind_Last)?8:11)-1*(T0Ind==0));
				KerArg1->UsedH = (unsigned short int) (((T0Ind_Last)?8:11)-1*(T0Ind==0));
				KerArg1->OutFeatures = (unsigned short int) (D1Ind_Last?2:8);
				KerArg1->Filter = (short int * __restrict__) (cnn_ssd_L1_Memory+3556+576*((D0Ind_Total)%2));
				KerArg1->Pad = (v4s) ((v4s){1,1,1*(T0Ind==0),1*(T0Ind_Last)});
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				_SN_Filter = _SNN_Filter;
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->H = (unsigned short int) (T0Ind_Last?7:9);
			KerArg2->Out = (short int * __restrict__) (cnn_ssd_L1_Memory+4708+2880*((T0Ind_Total)%2));
			KerArg2->InFeatures = (unsigned short int) (D1Ind_Last?2:8);
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) cnn_ssd_L2_Memory+3568+2880*((T0Ind_Total+-1)%2)),
						_SP_Out, 640, _LP_Out, 1, &UchanHR2);
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+3568+2880*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+4708+2880*((T0Ind_Total)%2)),
					_SC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
			_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (360); _LC_Out = ((1)?280:360); _SC_Out = (((D1Ind_Last)?2:8)*_LC_Out); 
			} else if (!(D1Ind_Last)) {
				_C_Out = _C_Out + (5120)+(-360); _LC_Out = (360); _SC_Out = (((D1Ind_NextLast)?2:8)*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) cnn_ssd_L2_Memory+3568+2880*((T0Ind_Total+-1)%2)), _SP_Out, 640, _LP_Out, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S20_Conv2d_24x32x3x3(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 16240 bytes, L2 buffer: 10480 bytes */
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
		[D1 Dim: Init: 24, Tiled: 3][Tile0 Dim: 2][D0 Dim: Init: 32, Tiled: 8]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 16 logical tiles, 16 physical tiles
			Total Size: 20480 [D0, [7 x 2560, 2560]][Tile0, 2:[20x10, 20x8], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 2:[20x10, 6:20x11, 20x8], 2][D0, [7 x 2560, 2560]]
		Tile0: [0, 1600, 400], Tile1: [2560, 1600, 400], Tile2; [5120, 1600, 400]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 3 logical tiles, 1 physical tiles
			Total Size: 48 [D1, [2 x 16, 16]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [2 x 16, 16]]
		Tile0: [0, 48, 48], Tile1: [0, 48, 48], Tile2; [0, 48, 48]
	Ker Arg: Filter, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 24 logical tiles, 24 physical tiles
			Total Size: 13824 [D1, [2 x 4608, 4608]][D0, [7 x 576, 576]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [2 x 4608, 4608]][D0, [7 x 576, 576]]
		Tile0: [0, 576, 576], Tile1: [576, 576, 576], Tile2; [1152, 576, 576]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 6 logical tiles, 6 physical tiles
			Total Size: 15360 [D1, [2 x 5120, 5120]][Tile0, 2:[20x9, 20x7], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [2 x 5120, 5120]][Tile0, 2:[20x9, 20x7], 2]
		Tile0: [0, 2880, 360], Tile1: [360, 2240, 280], Tile2; [5120, 2880, 360]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 6 logical tiles, 1 physical tiles
			Total Size: 30720 [D1, [2 x 10240, 10240]][Tile0, 2:[20x9, 20x7], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [2 x 10240, 10240]][Tile0, 2:[20x9, 20x7], 4]
		Tile0: [0, 5760, 720], Tile1: [0, 5760, 720], Tile2; [0, 5760, 720]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (cnn_ssd_L1_Memory+10480);
	KerArg0->W = (unsigned short int) (20);
	KerArg0->OutFeatures = (unsigned short int) (8);
	KerArg0->NormBias = (signed char) (13);
	KerArg1->W = (unsigned short int) (20);
	KerArg1->UsedW = (unsigned short int) (20);
	KerArg1->InFeatures = (unsigned short int) (4);
	KerArg1->OutFeatures = (unsigned short int) (8);
	KerArg1->Out = (int * __restrict__) (cnn_ssd_L1_Memory+10480);
	KerArg1->Norm = (unsigned char) (16);
	KerArg1->TotalInFeatures = (short int) (4);
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (cnn_ssd_L1_Memory+10480);
	KerArg2->W = (unsigned short int) (20);
	KerArg2->Norm = (unsigned char) (16);
	KerArg2->InFeatures = (unsigned short int) (8);
	KerArg2->LB = (int) (-32768);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+0), 1600, 640, 400, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+3520), 48, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory+9328+0), 576, 0, &UchanHF1);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read Filter */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+576), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory+9328+576), 576, 0, &UchanHF1);
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+9328+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+3568+0), 576, 0, &DmaR_Evt3);
	_NN_Filter=576; _SN_Filter=576;
	_C_Out=0; _SC_Out=2880; _LC_Out=360;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	for (D1Ind=0; D1Ind<3; D1Ind++) { /* Iteration on D1 */
		int D1Ind_Last = (D1Ind==2), D1Ind_NextLast = ((D1Ind+1)==2), D1Ind_NextNextLast = ((D1Ind+2)==2);
		for (T0Ind=0; T0Ind<2; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==1), T0Ind_NextLast = ((T0Ind+1)==1);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->H = (unsigned short int) (T0Ind_Last?7:9);
			KerArg0->Bias = (short int * __restrict__) (cnn_ssd_L1_Memory+3520+((D1Ind)*16));
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<8; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==7), D0Ind_NextLast = ((D0Ind+1)==7), D0Ind_NextNextLast = ((D0Ind+2)==7);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (2560); _LN_In = ((T0Ind_Last)?320:(440-40*(T0Ind==0))); _SN_In = (4*_LN_In); 
				} else if (!(T0Ind_Last)) {
					_N_In = _N_In + (360-(40*(T0Ind==0)))+(-17920); _LN_In = ((1)?320:440); _SN_In = (4*_LN_In); 
				} else if (!(D1Ind_Last)) {
					_N_In = _N_In + (-320)+(-17920); _LN_In = (400); _SN_In = (4*_LN_In); 
				}
				_SNN_Filter = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_Filter = _NN_Filter + ((576)); _SNN_Filter = (((D1Ind_Last)?(576):(576))); 
					} else if (!((T0Ind_Last))) {
						_NN_Filter = _NN_Filter + ((-4032)); _SNN_Filter = (((D1Ind_Last)?(576):(576))); 
					} else if (!(D1Ind_Last)) {
						_NN_Filter = _NN_Filter + (4608)+((-4032)); _SNN_Filter = (((D1Ind_NextLast)?(576):(576))); 
					}
				} else if (!((T0Ind_Last))) {
					_NN_Filter = _NN_Filter + ((576)); _SNN_Filter = (((D1Ind_Last)?(576):(576))); 
				} else if (!(D1Ind_Last)) {
					_NN_Filter = _NN_Filter + ((576)); _SNN_Filter = (((D1Ind_NextLast)?(576):(576))); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+1760*((D0Ind_Total+1)%2)),
							_SN_In, 640, _LN_In, 0, &DmaR_Evt1);
				}
				AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read Filter */
				if (_SNN_Filter) {
					AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+_NN_Filter), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory+9328+576*((D0Ind_Total)%2)),
							_SNN_Filter, 0, &UchanHF1);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
				if (_SN_Filter) {
					AT_L2_COPY(0, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+9328+576*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+3568+576*((D0Ind_Total+1)%2)),
							_SN_Filter, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (cnn_ssd_L1_Memory+0+1760*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (((T0Ind_Last)?8:11)-1*(T0Ind==0));
				KerArg1->UsedH = (unsigned short int) (((T0Ind_Last)?8:11)-1*(T0Ind==0));
				KerArg1->Filter = (short int * __restrict__) (cnn_ssd_L1_Memory+3568+576*((D0Ind_Total)%2));
				KerArg1->Pad = (v4s) ((v4s){1,1,1*(T0Ind==0),1*(T0Ind_Last)});
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				_SN_Filter = _SNN_Filter;
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->H = (unsigned short int) (T0Ind_Last?7:9);
			KerArg2->Out = (short int * __restrict__) (cnn_ssd_L1_Memory+4720+2880*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) cnn_ssd_L2_Memory+3568+2880*((T0Ind_Total+-1)%2)),
						_SP_Out, 640, _LP_Out, 1, &UchanHR2);
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+3568+2880*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+4720+2880*((T0Ind_Total)%2)),
					_SC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
			_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (360); _LC_Out = ((1)?280:360); _SC_Out = (8*_LC_Out); 
			} else if (!(D1Ind_Last)) {
				_C_Out = _C_Out + (5120)+(-360); _LC_Out = (360); _SC_Out = (8*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) cnn_ssd_L2_Memory+3568+2880*((T0Ind_Total+-1)%2)), _SP_Out, 640, _LP_Out, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S24_Conv2d_64x32x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 15744 bytes, L2 buffer: 10624 bytes */
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
		[D1 Dim: Init: 64, Tiled: 4][Tile0 Dim: 1][D0 Dim: Init: 32, Tiled: 6]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 6 logical tiles, 6 physical tiles
			Total Size: 5120 [D0, [5 x 960, 320]][Tile0, 1:[10x8], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[10x9, 4:10x10, 10x9], 2][D0, [5 x 960, 320]]
		Tile0: [0, 960, 160], Tile1: [960, 960, 160], Tile2; [1920, 960, 160]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 4 logical tiles, 1 physical tiles
			Total Size: 128 [D1, [3 x 32, 32]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [3 x 32, 32]]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Filter, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 24 logical tiles, 24 physical tiles
			Total Size: 36864 [D1, [3 x 9216, 9216]][D0, [5 x 1728, 576]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [3 x 9216, 9216]][D0, [5 x 1728, 576]]
		Tile0: [0, 1728, 1728], Tile1: [1728, 1728, 1728], Tile2; [3456, 1728, 1728]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 4 logical tiles, 4 physical tiles
			Total Size: 10240 [D1, [3 x 2560, 2560]][Tile0, 1:[10x8], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [3 x 2560, 2560]][Tile0, 1:[10x8], 2]
		Tile0: [0, 2560, 160], Tile1: [2560, 2560, 160], Tile2; [5120, 2560, 160]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 4 logical tiles, 1 physical tiles
			Total Size: 20480 [D1, [3 x 5120, 5120]][Tile0, 1:[10x8], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [3 x 5120, 5120]][Tile0, 1:[10x8], 4]
		Tile0: [0, 5120, 320], Tile1: [0, 5120, 320], Tile2; [0, 5120, 320]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (cnn_ssd_L1_Memory+10624);
	KerArg0->W = (unsigned short int) (10);
	KerArg0->H = (unsigned short int) (8);
	KerArg0->OutFeatures = (unsigned short int) (16);
	KerArg0->NormBias = (signed char) (15);
	KerArg1->W = (unsigned short int) (10);
	KerArg1->UsedW = (unsigned short int) (10);
	KerArg1->OutFeatures = (unsigned short int) (16);
	KerArg1->Out = (int * __restrict__) (cnn_ssd_L1_Memory+10624);
	KerArg1->Norm = (unsigned char) (15);
	KerArg1->Pad = (v4s) ((v4s){1,1,1,1});
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (cnn_ssd_L1_Memory+10624);
	KerArg2->W = (unsigned short int) (10);
	KerArg2->H = (unsigned short int) (8);
	KerArg2->Norm = (unsigned char) (15);
	KerArg2->InFeatures = (unsigned short int) (16);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+0), 960, 160, 160, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+1920), 128, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory+34288+0), 1728, 0, &UchanHF1);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read Filter */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+1728), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory+34288+1728), 1728, 0, &UchanHF1);
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+34288+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+2048+0), 1728, 0, &DmaR_Evt3);
	_NN_Filter=1728; _SN_Filter=1728;
	_C_Out=0; _SC_Out=2560; _LC_Out=160;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	for (D1Ind=0; D1Ind<4; D1Ind++) { /* Iteration on D1 */
		int D1Ind_Last = (D1Ind==3), D1Ind_NextLast = ((D1Ind+1)==3), D1Ind_NextNextLast = ((D1Ind+2)==3);
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1, T0Ind_NextLast = 1;
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->Bias = (short int * __restrict__) (cnn_ssd_L1_Memory+1920+((D1Ind)*32));
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<6; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==5), D0Ind_NextLast = ((D0Ind+1)==5), D0Ind_NextNextLast = ((D0Ind+2)==5);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (960); _LN_In = (160); _SN_In = (((D0Ind_NextLast)?2:6)*_LN_In); 
				} else if (!(D1Ind_Last)) {
					_N_In = _N_In + (-4800); _LN_In = (160); _SN_In = (6*_LN_In); 
				}
				_SNN_Filter = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_Filter = _NN_Filter + ((1728)); _SNN_Filter = (((D1Ind_Last)?(((D0Ind_NextNextLast)?576:1728)):(((D0Ind_NextNextLast)?576:1728)))); 
					} else if (!((1))) {
						_NN_Filter = _NN_Filter + ((-8640)); _SNN_Filter = (((D1Ind_Last)?(1728):(1728))); 
					} else if (!(D1Ind_Last)) {
						_NN_Filter = _NN_Filter + (9216)+((-8640)); _SNN_Filter = (((D1Ind_NextLast)?(1728):(1728))); 
					}
				} else if (!((1))) {
					_NN_Filter = _NN_Filter + ((1728)); _SNN_Filter = (((D1Ind_Last)?(1728):(1728))); 
				} else if (!(D1Ind_Last)) {
					_NN_Filter = _NN_Filter + ((1728)); _SNN_Filter = (((D1Ind_NextLast)?(1728):(1728))); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+960*((D0Ind_Total+1)%2)),
							_SN_In, 160, _LN_In, 0, &DmaR_Evt1);
				}
				AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read Filter */
				if (_SNN_Filter) {
					AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+_NN_Filter), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory+34288+1728*((D0Ind_Total)%2)),
							_SNN_Filter, 0, &UchanHF1);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
				if (_SN_Filter) {
					AT_L2_COPY(0, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+34288+1728*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+2048+1728*((D0Ind_Total+1)%2)),
							_SN_Filter, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (cnn_ssd_L1_Memory+0+960*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (10-1*(1)-1*(1));
				KerArg1->UsedH = (unsigned short int) (10-1*(1)-1*(1));
				KerArg1->InFeatures = (unsigned short int) (D0Ind_Last?2:6);
				KerArg1->Filter = (short int * __restrict__) (cnn_ssd_L1_Memory+2048+1728*((D0Ind_Total)%2));
				KerArg1->TotalInFeatures = (short int) (D0Ind_Last?2:6);
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				_SN_Filter = _SNN_Filter;
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->Out = (short int * __restrict__) (cnn_ssd_L1_Memory+5504+2560*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) cnn_ssd_L2_Memory+8688+2560*((T0Ind_Total+-1)%2)),
						_SP_Out, 160, _LP_Out, 1, &UchanHR2);
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+8688+2560*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+5504+2560*((T0Ind_Total)%2)),
					_SC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
			_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(D1Ind_Last)) {
				_C_Out = _C_Out + (2560); _LC_Out = (160); _SC_Out = (16*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
			T0Ind_Total++;
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) cnn_ssd_L2_Memory+8688+2560*((T0Ind_Total+-1)%2)), _SP_Out, 160, _LP_Out, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait current uDMA write Out */
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
	AT_HYPERRAM_CL_EVENT UchanHR1;
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
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) cnn_ssd_L2_Memory+3568+0), 10240, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+3568+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0), 10240, 0, &DmaR_Evt1);
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
	/* Shared L1: 15652 bytes, L2 buffer: 10532 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF2;
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
		[D1 Dim: Init: 18, Tiled: 2][Tile0 Dim: 1][D0 Dim: Init: 64, Tiled: 11]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 11 logical tiles, 11 physical tiles
			Total Size: 10240 [D0, [10 x 960, 640]][Tile0, 1:[10x8], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[10x9, 9:10x10, 10x9], 2][D0, [10 x 960, 640]]
		Tile0: [0, 960, 160], Tile1: [960, 960, 160], Tile2; [1920, 960, 160]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 36 [D1, [1 x 32, 4]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 32, 4]]
		Tile0: [0, 36, 36], Tile1: [0, 36, 36], Tile2; [0, 36, 36]
	Ker Arg: Filter, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 22 logical tiles, 22 physical tiles
			Total Size: 20736 [D1, [1 x 18432, 2304]][D0, [10 x 1728, 1152]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 18432, 2304]][D0, [10 x 1728, 1152]]
		Tile0: [0, 1728, 1728], Tile1: [1728, 1728, 1728], Tile2; [3456, 1728, 1728]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 2 physical tiles
			Total Size: 2880 [D1, [1 x 2560, 320]][Tile0, 1:[10x8], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 2560, 320]][Tile0, 1:[10x8], 2]
		Tile0: [0, 2560, 160], Tile1: [2560, 320, 160], Tile2; [0, 2560, 160]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 5760 [D1, [1 x 5120, 640]][Tile0, 1:[10x8], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 5120, 640]][Tile0, 1:[10x8], 4]
		Tile0: [0, 5120, 320], Tile1: [0, 5120, 320], Tile2; [0, 5120, 320]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (cnn_ssd_L1_Memory+10532);
	KerArg0->W = (unsigned short int) (10);
	KerArg0->H = (unsigned short int) (8);
	KerArg0->NormBias = (signed char) (12);
	KerArg1->W = (unsigned short int) (10);
	KerArg1->UsedW = (unsigned short int) (10);
	KerArg1->Out = (int * __restrict__) (cnn_ssd_L1_Memory+10532);
	KerArg1->Norm = (unsigned char) (16);
	KerArg1->Pad = (v4s) ((v4s){1,1,1,1});
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (cnn_ssd_L1_Memory+10532);
	KerArg2->W = (unsigned short int) (10);
	KerArg2->H = (unsigned short int) (8);
	KerArg2->Norm = (unsigned char) (16);
	KerArg2->LB = (int) (-32768);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) cnn_ssd_L2_Memory+3568+0), 960, 160, 160, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+960), ((AT_HYPERRAM_INT_ADDR_TYPE) cnn_ssd_L2_Memory+3568+960), 960, 160, 160, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+3568+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+0), 960, 0, &DmaR_Evt1);
	_NN_In=960; _SN_In=960;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+1920), 36, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory+34288+0), 1728, 0, &UchanHF2);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF2); /* Wait previous uDMA read Filter */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+1728), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory+34288+1728), 1728, 0, &UchanHF2);
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+34288+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+1956+0), 1728, 0, &DmaR_Evt3);
	_NN_Filter=1728; _SN_Filter=1728;
	_C_Out=0; _SC_Out=2560; _LC_Out=160;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	for (D1Ind=0; D1Ind<2; D1Ind++) { /* Iteration on D1 */
		int D1Ind_Last = (D1Ind==1), D1Ind_NextLast = ((D1Ind+1)==1), D1Ind_NextNextLast = ((D1Ind+2)==1);
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1, T0Ind_NextLast = 1, T0Ind_NextNextLast = 1;
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->OutFeatures = (unsigned short int) (D1Ind_Last?2:16);
			KerArg0->Bias = (short int * __restrict__) (cnn_ssd_L1_Memory+1920+((D1Ind)*32));
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<11; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==10), D0Ind_NextLast = ((D0Ind+1)==10), D0Ind_NextNextLast = ((D0Ind+2)==10);
				/*================================= Prepare Tiles ===================================*/
				_SNN_In = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_In = _NN_In + (960); _LNN_In = (160); _SNN_In = (((D0Ind_NextNextLast)?4:6)*_LNN_In); 
					} else if (!(D1Ind_Last)) {
						_NN_In = _NN_In + (-9600); _LNN_In = (160); _SNN_In = (6*_LNN_In); 
					}
				} else if (!((D1Ind_Last))) {
					_NN_In = _NN_In + (960); _LNN_In = (160); _SNN_In = (6*_LNN_In); 
				}
				_SNN_Filter = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_Filter = _NN_Filter + (((D1Ind_Last)?(216):(1728))); _SNN_Filter = (((D1Ind_Last)?(((D0Ind_NextNextLast)?144:216)):(((D0Ind_NextNextLast)?1152:1728)))); 
					} else if (!((1))) {
						_NN_Filter = _NN_Filter + (((D1Ind_Last)?(-2160):(-17280))); _SNN_Filter = (((D1Ind_Last)?(216):(1728))); 
					} else if (!(D1Ind_Last)) {
						_NN_Filter = _NN_Filter + (18432)+(((D1Ind_Last)?(-2160):(-17280))); _SNN_Filter = (((1)?(216):(1728))); 
					}
				} else if (!((1))) {
					_NN_Filter = _NN_Filter + (((D1Ind_Last)?(216):(1728))); _SNN_Filter = (((D1Ind_Last)?(216):(1728))); 
				} else if (!(D1Ind_Last)) {
					_NN_Filter = _NN_Filter + (((1)?(216):(1728))); _SNN_Filter = (((1)?(216):(1728))); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
				if (_SNN_In) {
					AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) cnn_ssd_L2_Memory+3568+960*((D0Ind_Total)%2)),
							_SNN_In, 160, _LNN_In, 0, &UchanHR1);
				}
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+3568+960*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+960*((D0Ind_Total+1)%2)),
							_SN_In, 0, &DmaR_Evt1);
				}
				AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF2); /* Wait previous uDMA read Filter */
				if (_SNN_Filter) {
					AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+_NN_Filter), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory+34288+1728*((D0Ind_Total)%2)),
							_SNN_Filter, 0, &UchanHF2);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
				if (_SN_Filter) {
					AT_L2_COPY(0, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+34288+1728*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+1956+1728*((D0Ind_Total+1)%2)),
							_SN_Filter, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (cnn_ssd_L1_Memory+0+960*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (10-1*(1)-1*(1));
				KerArg1->UsedH = (unsigned short int) (10-1*(1)-1*(1));
				KerArg1->InFeatures = (unsigned short int) (D0Ind_Last?4:6);
				KerArg1->OutFeatures = (unsigned short int) (D1Ind_Last?2:16);
				KerArg1->Filter = (short int * __restrict__) (cnn_ssd_L1_Memory+1956+1728*((D0Ind_Total)%2));
				KerArg1->TotalInFeatures = (short int) (D0Ind_Last?4:6);
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				_SN_In = _SNN_In;_LN_In = _LNN_In;
				_SN_Filter = _SNN_Filter;
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->Out = (short int * __restrict__) (cnn_ssd_L1_Memory+5412+2560*((T0Ind_Total)%2));
			KerArg2->InFeatures = (unsigned short int) (D1Ind_Last?2:16);
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) cnn_ssd_L2_Memory+5488+2560*((T0Ind_Total+-1)%2)),
						_SP_Out, 160, _LP_Out, 1, &UchanHR3);
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+5488+2560*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+5412+2560*((T0Ind_Total)%2)),
					_SC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
			_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(D1Ind_Last)) {
				_C_Out = _C_Out + (2560); _LC_Out = (160); _SC_Out = (((1)?2:16)*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
			T0Ind_Total++;
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) cnn_ssd_L2_Memory+5488+2560*((T0Ind_Total+-1)%2)), _SP_Out, 160, _LP_Out, 1, &UchanHR3);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S32_Conv2d_24x64x3x3(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 15664 bytes, L2 buffer: 10544 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF2;
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
		[D1 Dim: Init: 24, Tiled: 2][Tile0 Dim: 1][D0 Dim: Init: 64, Tiled: 11]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 11 logical tiles, 11 physical tiles
			Total Size: 10240 [D0, [10 x 960, 640]][Tile0, 1:[10x8], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[10x9, 9:10x10, 10x9], 2][D0, [10 x 960, 640]]
		Tile0: [0, 960, 160], Tile1: [960, 960, 160], Tile2; [1920, 960, 160]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 48 [D1, [1 x 32, 16]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 32, 16]]
		Tile0: [0, 48, 48], Tile1: [0, 48, 48], Tile2; [0, 48, 48]
	Ker Arg: Filter, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 22 logical tiles, 22 physical tiles
			Total Size: 27648 [D1, [1 x 18432, 9216]][D0, [10 x 1728, 1152]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 18432, 9216]][D0, [10 x 1728, 1152]]
		Tile0: [0, 1728, 1728], Tile1: [1728, 1728, 1728], Tile2; [3456, 1728, 1728]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 2 physical tiles
			Total Size: 3840 [D1, [1 x 2560, 1280]][Tile0, 1:[10x8], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 2560, 1280]][Tile0, 1:[10x8], 2]
		Tile0: [0, 2560, 160], Tile1: [2560, 1280, 160], Tile2; [0, 2560, 160]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 7680 [D1, [1 x 5120, 2560]][Tile0, 1:[10x8], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 5120, 2560]][Tile0, 1:[10x8], 4]
		Tile0: [0, 5120, 320], Tile1: [0, 5120, 320], Tile2; [0, 5120, 320]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (cnn_ssd_L1_Memory+10544);
	KerArg0->W = (unsigned short int) (10);
	KerArg0->H = (unsigned short int) (8);
	KerArg0->NormBias = (signed char) (13);
	KerArg1->W = (unsigned short int) (10);
	KerArg1->UsedW = (unsigned short int) (10);
	KerArg1->Out = (int * __restrict__) (cnn_ssd_L1_Memory+10544);
	KerArg1->Norm = (unsigned char) (16);
	KerArg1->Pad = (v4s) ((v4s){1,1,1,1});
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (cnn_ssd_L1_Memory+10544);
	KerArg2->W = (unsigned short int) (10);
	KerArg2->H = (unsigned short int) (8);
	KerArg2->Norm = (unsigned char) (16);
	KerArg2->LB = (int) (-32768);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) cnn_ssd_L2_Memory+3568+0), 960, 160, 160, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+960), ((AT_HYPERRAM_INT_ADDR_TYPE) cnn_ssd_L2_Memory+3568+960), 960, 160, 160, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+3568+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+0), 960, 0, &DmaR_Evt1);
	_NN_In=960; _SN_In=960;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+1920), 48, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory+34288+0), 1728, 0, &UchanHF2);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF2); /* Wait previous uDMA read Filter */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+1728), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory+34288+1728), 1728, 0, &UchanHF2);
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+34288+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+1968+0), 1728, 0, &DmaR_Evt3);
	_NN_Filter=1728; _SN_Filter=1728;
	_C_Out=0; _SC_Out=2560; _LC_Out=160;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	for (D1Ind=0; D1Ind<2; D1Ind++) { /* Iteration on D1 */
		int D1Ind_Last = (D1Ind==1), D1Ind_NextLast = ((D1Ind+1)==1), D1Ind_NextNextLast = ((D1Ind+2)==1);
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1, T0Ind_NextLast = 1, T0Ind_NextNextLast = 1;
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->OutFeatures = (unsigned short int) (D1Ind_Last?8:16);
			KerArg0->Bias = (short int * __restrict__) (cnn_ssd_L1_Memory+1920+((D1Ind)*32));
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<11; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==10), D0Ind_NextLast = ((D0Ind+1)==10), D0Ind_NextNextLast = ((D0Ind+2)==10);
				/*================================= Prepare Tiles ===================================*/
				_SNN_In = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_In = _NN_In + (960); _LNN_In = (160); _SNN_In = (((D0Ind_NextNextLast)?4:6)*_LNN_In); 
					} else if (!(D1Ind_Last)) {
						_NN_In = _NN_In + (-9600); _LNN_In = (160); _SNN_In = (6*_LNN_In); 
					}
				} else if (!((D1Ind_Last))) {
					_NN_In = _NN_In + (960); _LNN_In = (160); _SNN_In = (6*_LNN_In); 
				}
				_SNN_Filter = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_Filter = _NN_Filter + (((D1Ind_Last)?(864):(1728))); _SNN_Filter = (((D1Ind_Last)?(((D0Ind_NextNextLast)?576:864)):(((D0Ind_NextNextLast)?1152:1728)))); 
					} else if (!((1))) {
						_NN_Filter = _NN_Filter + (((D1Ind_Last)?(-8640):(-17280))); _SNN_Filter = (((D1Ind_Last)?(864):(1728))); 
					} else if (!(D1Ind_Last)) {
						_NN_Filter = _NN_Filter + (18432)+(((D1Ind_Last)?(-8640):(-17280))); _SNN_Filter = (((1)?(864):(1728))); 
					}
				} else if (!((1))) {
					_NN_Filter = _NN_Filter + (((D1Ind_Last)?(864):(1728))); _SNN_Filter = (((D1Ind_Last)?(864):(1728))); 
				} else if (!(D1Ind_Last)) {
					_NN_Filter = _NN_Filter + (((1)?(864):(1728))); _SNN_Filter = (((1)?(864):(1728))); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
				if (_SNN_In) {
					AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) cnn_ssd_L2_Memory+3568+960*((D0Ind_Total)%2)),
							_SNN_In, 160, _LNN_In, 0, &UchanHR1);
				}
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+3568+960*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+960*((D0Ind_Total+1)%2)),
							_SN_In, 0, &DmaR_Evt1);
				}
				AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF2); /* Wait previous uDMA read Filter */
				if (_SNN_Filter) {
					AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+_NN_Filter), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory+34288+1728*((D0Ind_Total)%2)),
							_SNN_Filter, 0, &UchanHF2);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
				if (_SN_Filter) {
					AT_L2_COPY(0, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+34288+1728*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+1968+1728*((D0Ind_Total+1)%2)),
							_SN_Filter, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (cnn_ssd_L1_Memory+0+960*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (10-1*(1)-1*(1));
				KerArg1->UsedH = (unsigned short int) (10-1*(1)-1*(1));
				KerArg1->InFeatures = (unsigned short int) (D0Ind_Last?4:6);
				KerArg1->OutFeatures = (unsigned short int) (D1Ind_Last?8:16);
				KerArg1->Filter = (short int * __restrict__) (cnn_ssd_L1_Memory+1968+1728*((D0Ind_Total)%2));
				KerArg1->TotalInFeatures = (short int) (D0Ind_Last?4:6);
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				_SN_In = _SNN_In;_LN_In = _LNN_In;
				_SN_Filter = _SNN_Filter;
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->Out = (short int * __restrict__) (cnn_ssd_L1_Memory+5424+2560*((T0Ind_Total)%2));
			KerArg2->InFeatures = (unsigned short int) (D1Ind_Last?8:16);
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) cnn_ssd_L2_Memory+5488+2560*((T0Ind_Total+-1)%2)),
						_SP_Out, 160, _LP_Out, 1, &UchanHR3);
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+5488+2560*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+5424+2560*((T0Ind_Total)%2)),
					_SC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
			_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(D1Ind_Last)) {
				_C_Out = _C_Out + (2560); _LC_Out = (160); _SC_Out = (((1)?8:16)*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
			T0Ind_Total++;
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) cnn_ssd_L2_Memory+5488+2560*((T0Ind_Total+-1)%2)), _SP_Out, 160, _LP_Out, 1, &UchanHR3);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S36_Conv2d_128x64x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 15264 bytes, L2 buffer: 10144 bytes */
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
		[D1 Dim: Init: 128, Tiled: 2][Tile0 Dim: 1][D0 Dim: Init: 64, Tiled: 32]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 32 logical tiles, 32 physical tiles
			Total Size: 2560 [D0, [31 x 80, 80]][Tile0, 1:[5x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[5x5, 30:5x6, 5x5], 2][D0, [31 x 80, 80]]
		Tile0: [0, 80, 40], Tile1: [80, 80, 40], Tile2; [160, 80, 40]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 256 [D1, [1 x 128, 128]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 128, 128]]
		Tile0: [0, 256, 256], Tile1: [0, 256, 256], Tile2; [0, 256, 256]
	Ker Arg: Filter, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 64 logical tiles, 64 physical tiles
			Total Size: 147456 [D1, [1 x 73728, 73728]][D0, [31 x 2304, 2304]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 73728, 73728]][D0, [31 x 2304, 2304]]
		Tile0: [0, 2304, 2304], Tile1: [2304, 2304, 2304], Tile2; [4608, 2304, 2304]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 2 physical tiles
			Total Size: 5120 [D1, [1 x 2560, 2560]][Tile0, 1:[5x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 2560, 2560]][Tile0, 1:[5x4], 2]
		Tile0: [0, 2560, 40], Tile1: [2560, 2560, 40], Tile2; [0, 2560, 40]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 10240 [D1, [1 x 5120, 5120]][Tile0, 1:[5x4], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 5120, 5120]][Tile0, 1:[5x4], 4]
		Tile0: [0, 5120, 80], Tile1: [0, 5120, 80], Tile2; [0, 5120, 80]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (cnn_ssd_L1_Memory+10144);
	KerArg0->W = (unsigned short int) (5);
	KerArg0->H = (unsigned short int) (4);
	KerArg0->OutFeatures = (unsigned short int) (64);
	KerArg0->NormBias = (signed char) (15);
	KerArg1->W = (unsigned short int) (5);
	KerArg1->UsedW = (unsigned short int) (5);
	KerArg1->InFeatures = (unsigned short int) (2);
	KerArg1->OutFeatures = (unsigned short int) (64);
	KerArg1->Out = (int * __restrict__) (cnn_ssd_L1_Memory+10144);
	KerArg1->Norm = (unsigned char) (15);
	KerArg1->TotalInFeatures = (short int) (2);
	KerArg1->Pad = (v4s) ((v4s){1,1,1,1});
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (cnn_ssd_L1_Memory+10144);
	KerArg2->W = (unsigned short int) (5);
	KerArg2->H = (unsigned short int) (4);
	KerArg2->Norm = (unsigned char) (15);
	KerArg2->InFeatures = (unsigned short int) (64);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+0), 80, 40, 40, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+160), 256, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory+36848+0), 2304, 0, &UchanHF1);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read Filter */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+2304), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory+36848+2304), 2304, 0, &UchanHF1);
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+36848+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+416+0), 2304, 0, &DmaR_Evt3);
	_NN_Filter=2304; _SN_Filter=2304;
	_C_Out=0; _SC_Out=2560; _LC_Out=40;
	_SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	for (D1Ind=0; D1Ind<2; D1Ind++) { /* Iteration on D1 */
		int D1Ind_Last = (D1Ind==1), D1Ind_NextLast = ((D1Ind+1)==1), D1Ind_NextNextLast = ((D1Ind+2)==1);
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1, T0Ind_NextLast = 1;
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->Bias = (short int * __restrict__) (cnn_ssd_L1_Memory+160+((D1Ind)*128));
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<32; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==31), D0Ind_NextLast = ((D0Ind+1)==31), D0Ind_NextNextLast = ((D0Ind+2)==31);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (80); _LN_In = (40); _SN_In = (2*_LN_In); 
				} else if (!(D1Ind_Last)) {
					_N_In = _N_In + (-2480); _LN_In = (40); _SN_In = (2*_LN_In); 
				}
				_SNN_Filter = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_Filter = _NN_Filter + ((2304)); _SNN_Filter = (((D1Ind_Last)?(2304):(2304))); 
					} else if (!((1))) {
						_NN_Filter = _NN_Filter + ((-71424)); _SNN_Filter = (((D1Ind_Last)?(2304):(2304))); 
					} else if (!(D1Ind_Last)) {
						_NN_Filter = _NN_Filter + (73728)+((-71424)); _SNN_Filter = (((1)?(2304):(2304))); 
					}
				} else if (!((1))) {
					_NN_Filter = _NN_Filter + ((2304)); _SNN_Filter = (((D1Ind_Last)?(2304):(2304))); 
				} else if (!(D1Ind_Last)) {
					_NN_Filter = _NN_Filter + ((2304)); _SNN_Filter = (((1)?(2304):(2304))); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+80*((D0Ind_Total+1)%2)),
							_SN_In, 40, _LN_In, 0, &DmaR_Evt1);
				}
				AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read Filter */
				if (_SNN_Filter) {
					AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+_NN_Filter), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory+36848+2304*((D0Ind_Total)%2)),
							_SNN_Filter, 0, &UchanHF1);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
				if (_SN_Filter) {
					AT_L2_COPY(0, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+36848+2304*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+416+2304*((D0Ind_Total+1)%2)),
							_SN_Filter, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (cnn_ssd_L1_Memory+0+80*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (6-1*(1)-1*(1));
				KerArg1->UsedH = (unsigned short int) (6-1*(1)-1*(1));
				KerArg1->Filter = (short int * __restrict__) (cnn_ssd_L1_Memory+416+2304*((D0Ind_Total)%2));
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				_SN_Filter = _SNN_Filter;
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->Out = (short int * __restrict__) (cnn_ssd_L1_Memory+5024+2560*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+5024+2560*((T0Ind_Total)%2)),
					_SC_Out, 40, _LC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(D1Ind_Last)) {
				_C_Out = _C_Out + (2560); _LC_Out = (40); _SC_Out = (64*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
			T0Ind_Total++;
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
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
	/* Shared L1: 15716 bytes, L2 buffer: 14436 bytes */
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
		[D1 Dim: Init: 18, Tiled: 2][Tile0 Dim: 1][D0 Dim: Init: 128, Tiled: 7]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 7 logical tiles, 7 physical tiles
			Total Size: 5120 [D0, [6 x 800, 320]][Tile0, 1:[5x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[5x5, 5:5x6, 5x5], 2][D0, [6 x 800, 320]]
		Tile0: [0, 800, 40], Tile1: [800, 800, 40], Tile2; [1600, 800, 40]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 36 [D1, [1 x 32, 4]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 32, 4]]
		Tile0: [0, 36, 36], Tile1: [0, 36, 36], Tile2; [0, 36, 36]
	Ker Arg: Filter, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 14 logical tiles, 14 physical tiles
			Total Size: 41472 [D1, [1 x 36864, 4608]][D0, [6 x 5760, 2304]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 36864, 4608]][D0, [6 x 5760, 2304]]
		Tile0: [0, 5760, 5760], Tile1: [5760, 5760, 5760], Tile2; [11520, 5760, 5760]
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
	KerArg0->Out = (int * __restrict__) (cnn_ssd_L1_Memory+14436);
	KerArg0->W = (unsigned short int) (5);
	KerArg0->H = (unsigned short int) (4);
	KerArg0->NormBias = (signed char) (13);
	KerArg1->W = (unsigned short int) (5);
	KerArg1->UsedW = (unsigned short int) (5);
	KerArg1->Out = (int * __restrict__) (cnn_ssd_L1_Memory+14436);
	KerArg1->Norm = (unsigned char) (16);
	KerArg1->Pad = (v4s) ((v4s){1,1,1,1});
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (cnn_ssd_L1_Memory+14436);
	KerArg2->W = (unsigned short int) (5);
	KerArg2->H = (unsigned short int) (4);
	KerArg2->Norm = (unsigned char) (16);
	KerArg2->LB = (int) (-32768);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+0), 800, 40, 40, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+1600), 36, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory+34288+0), 5760, 0, &UchanHF1);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read Filter */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+5760), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory+34288+5760), 5760, 0, &UchanHF1);
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+34288+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+1636+0), 5760, 0, &DmaR_Evt3);
	_NN_Filter=5760; _SN_Filter=5760;
	_C_Out=0; _SC_Out=640; _LC_Out=40;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	for (D1Ind=0; D1Ind<2; D1Ind++) { /* Iteration on D1 */
		int D1Ind_Last = (D1Ind==1), D1Ind_NextLast = ((D1Ind+1)==1), D1Ind_NextNextLast = ((D1Ind+2)==1);
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1, T0Ind_NextLast = 1;
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->OutFeatures = (unsigned short int) (D1Ind_Last?2:16);
			KerArg0->Bias = (short int * __restrict__) (cnn_ssd_L1_Memory+1600+((D1Ind)*32));
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<7; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==6), D0Ind_NextLast = ((D0Ind+1)==6), D0Ind_NextNextLast = ((D0Ind+2)==6);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (800); _LN_In = (40); _SN_In = (((D0Ind_NextLast)?8:20)*_LN_In); 
				} else if (!(D1Ind_Last)) {
					_N_In = _N_In + (-4800); _LN_In = (40); _SN_In = (20*_LN_In); 
				}
				_SNN_Filter = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_Filter = _NN_Filter + (((D1Ind_Last)?(720):(5760))); _SNN_Filter = (((D1Ind_Last)?(((D0Ind_NextNextLast)?288:720)):(((D0Ind_NextNextLast)?2304:5760)))); 
					} else if (!((1))) {
						_NN_Filter = _NN_Filter + (((D1Ind_Last)?(-4320):(-34560))); _SNN_Filter = (((D1Ind_Last)?(720):(5760))); 
					} else if (!(D1Ind_Last)) {
						_NN_Filter = _NN_Filter + (36864)+(((D1Ind_Last)?(-4320):(-34560))); _SNN_Filter = (((1)?(720):(5760))); 
					}
				} else if (!((1))) {
					_NN_Filter = _NN_Filter + (((D1Ind_Last)?(720):(5760))); _SNN_Filter = (((D1Ind_Last)?(720):(5760))); 
				} else if (!(D1Ind_Last)) {
					_NN_Filter = _NN_Filter + (((1)?(720):(5760))); _SNN_Filter = (((1)?(720):(5760))); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+800*((D0Ind_Total+1)%2)),
							_SN_In, 40, _LN_In, 0, &DmaR_Evt1);
				}
				AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read Filter */
				if (_SNN_Filter) {
					AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+_NN_Filter), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory+34288+5760*((D0Ind_Total)%2)),
							_SNN_Filter, 0, &UchanHF1);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
				if (_SN_Filter) {
					AT_L2_COPY(0, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+34288+5760*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+1636+5760*((D0Ind_Total+1)%2)),
							_SN_Filter, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (cnn_ssd_L1_Memory+0+800*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (6-1*(1)-1*(1));
				KerArg1->UsedH = (unsigned short int) (6-1*(1)-1*(1));
				KerArg1->InFeatures = (unsigned short int) (D0Ind_Last?8:20);
				KerArg1->OutFeatures = (unsigned short int) (D1Ind_Last?2:16);
				KerArg1->Filter = (short int * __restrict__) (cnn_ssd_L1_Memory+1636+5760*((D0Ind_Total)%2));
				KerArg1->TotalInFeatures = (short int) (D0Ind_Last?8:20);
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				_SN_Filter = _SNN_Filter;
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->Out = (short int * __restrict__) (cnn_ssd_L1_Memory+13156+640*((T0Ind_Total)%2));
			KerArg2->InFeatures = (unsigned short int) (D1Ind_Last?2:16);
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) cnn_ssd_L2_Memory+9712+640*((T0Ind_Total+-1)%2)),
						_SP_Out, 40, _LP_Out, 1, &UchanHR2);
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+9712+640*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+13156+640*((T0Ind_Total)%2)),
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
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) cnn_ssd_L2_Memory+9712+640*((T0Ind_Total+-1)%2)), _SP_Out, 40, _LP_Out, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S44_Conv2d_24x128x3x3(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 14256 bytes, L2 buffer: 12336 bytes */
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
		[D1 Dim: Init: 24, Tiled: 1][Tile0 Dim: 1][D0 Dim: Init: 128, Tiled: 11]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 11 logical tiles, 11 physical tiles
			Total Size: 5120 [D0, [10 x 480, 320]][Tile0, 1:[5x4], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[5x5, 9:5x6, 5x5], 2][D0, [10 x 480, 320]]
		Tile0: [0, 480, 40], Tile1: [480, 480, 40], Tile2; [960, 480, 40]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 48 [D1, [0 x 48, 48]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 48, 48]]
		Tile0: [0, 48, 48], Tile1: [0, 48, 48], Tile2; [0, 48, 48]
	Ker Arg: Filter, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 11 logical tiles, 11 physical tiles
			Total Size: 55296 [D1, [0 x 55296, 55296]][D0, [10 x 5184, 3456]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 55296, 55296]][D0, [10 x 5184, 3456]]
		Tile0: [0, 5184, 5184], Tile1: [5184, 5184, 5184], Tile2; [10368, 5184, 5184]
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
	KerArg0->Out = (int * __restrict__) (cnn_ssd_L1_Memory+12336);
	KerArg0->W = (unsigned short int) (5);
	KerArg0->H = (unsigned short int) (4);
	KerArg0->OutFeatures = (unsigned short int) (24);
	KerArg0->Bias = (short int * __restrict__) (cnn_ssd_L1_Memory+960);
	KerArg0->NormBias = (signed char) (13);
	KerArg1->W = (unsigned short int) (5);
	KerArg1->UsedW = (unsigned short int) (5);
	KerArg1->OutFeatures = (unsigned short int) (24);
	KerArg1->Out = (int * __restrict__) (cnn_ssd_L1_Memory+12336);
	KerArg1->Norm = (unsigned char) (16);
	KerArg1->Pad = (v4s) ((v4s){1,1,1,1});
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (cnn_ssd_L1_Memory+12336);
	KerArg2->W = (unsigned short int) (5);
	KerArg2->H = (unsigned short int) (4);
	KerArg2->Out = (short int * __restrict__) (cnn_ssd_L1_Memory+11376);
	KerArg2->Norm = (unsigned char) (16);
	KerArg2->InFeatures = (unsigned short int) (24);
	KerArg2->LB = (int) (-32768);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+0), 480, 40, 40, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+960), 48, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory+34288+0), 5184, 0, &UchanHF1);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read Filter */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+5184), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory+34288+5184), 5184, 0, &UchanHF1);
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+34288+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+1008+0), 5184, 0, &DmaR_Evt3);
	_NN_Filter=5184; _SN_Filter=5184;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1, D1Ind_NextLast = 1, D1Ind_NextNextLast = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1, T0Ind_NextLast = 1;
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<11; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==10), D0Ind_NextLast = ((D0Ind+1)==10), D0Ind_NextNextLast = ((D0Ind+2)==10);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (480); _LN_In = (40); _SN_In = (((D0Ind_NextLast)?8:12)*_LN_In); 
				} else if (!(1)) {
					_N_In = _N_In + (-4800); _LN_In = (40); _SN_In = (12*_LN_In); 
				}
				_SNN_Filter = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_Filter = _NN_Filter + ((5184)); _SNN_Filter = (((1)?(((D0Ind_NextNextLast)?3456:5184)):(((D0Ind_NextNextLast)?3456:5184)))); 
					} else if (!((1))) {
						_NN_Filter = _NN_Filter + ((-51840)); _SNN_Filter = (((1)?(5184):(5184))); 
					}
				} else if (!((1))) {
					_NN_Filter = _NN_Filter + ((5184)); _SNN_Filter = (((1)?(5184):(5184))); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+480*((D0Ind_Total+1)%2)),
							_SN_In, 40, _LN_In, 0, &DmaR_Evt1);
				}
				AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read Filter */
				if (_SNN_Filter) {
					AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+_NN_Filter), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory+34288+5184*((D0Ind_Total)%2)),
							_SNN_Filter, 0, &UchanHF1);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
				if (_SN_Filter) {
					AT_L2_COPY(0, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+34288+5184*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+1008+5184*((D0Ind_Total+1)%2)),
							_SN_Filter, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (cnn_ssd_L1_Memory+0+480*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (6-1*(1)-1*(1));
				KerArg1->UsedH = (unsigned short int) (6-1*(1)-1*(1));
				KerArg1->InFeatures = (unsigned short int) (D0Ind_Last?8:12);
				KerArg1->Filter = (short int * __restrict__) (cnn_ssd_L1_Memory+1008+5184*((D0Ind_Total)%2));
				KerArg1->TotalInFeatures = (short int) (D0Ind_Last?8:12);
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
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+3568+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+11376), 960, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+0), ((AT_HYPERRAM_INT_ADDR_TYPE) cnn_ssd_L2_Memory+3568+0), 960, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S48_Conv2d_128x128x3x3_Relu(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 12576 bytes, L2 buffer: 10528 bytes */
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
		[D1 Dim: Init: 128, Tiled: 1][Tile0 Dim: 1][D0 Dim: Init: 128, Tiled: 64]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 64 logical tiles, 64 physical tiles
			Total Size: 1024 [D0, [63 x 16, 16]][Tile0, 1:[2x2], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[2x3, 62:2x4, 2x3], 2][D0, [63 x 16, 16]]
		Tile0: [0, 16, 8], Tile1: [16, 16, 8], Tile2; [32, 16, 8]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 256 [D1, [0 x 256, 256]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 256, 256]]
		Tile0: [0, 256, 256], Tile1: [0, 256, 256], Tile2; [0, 256, 256]
	Ker Arg: Filter, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 64 logical tiles, 64 physical tiles
			Total Size: 294912 [D1, [0 x 294912, 294912]][D0, [63 x 4608, 4608]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 294912, 294912]][D0, [63 x 4608, 4608]]
		Tile0: [0, 4608, 4608], Tile1: [4608, 4608, 4608], Tile2; [9216, 4608, 4608]
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
	KerArg0->Out = (int * __restrict__) (cnn_ssd_L1_Memory+10528);
	KerArg0->W = (unsigned short int) (2);
	KerArg0->H = (unsigned short int) (2);
	KerArg0->OutFeatures = (unsigned short int) (128);
	KerArg0->Bias = (short int * __restrict__) (cnn_ssd_L1_Memory+32);
	KerArg0->NormBias = (signed char) (15);
	KerArg1->W = (unsigned short int) (2);
	KerArg1->UsedW = (unsigned short int) (2);
	KerArg1->InFeatures = (unsigned short int) (2);
	KerArg1->OutFeatures = (unsigned short int) (128);
	KerArg1->Out = (int * __restrict__) (cnn_ssd_L1_Memory+10528);
	KerArg1->Norm = (unsigned char) (15);
	KerArg1->TotalInFeatures = (short int) (2);
	KerArg1->Pad = (v4s) ((v4s){1,1,1,1});
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (cnn_ssd_L1_Memory+10528);
	KerArg2->W = (unsigned short int) (2);
	KerArg2->H = (unsigned short int) (2);
	KerArg2->Out = (short int * __restrict__) (cnn_ssd_L1_Memory+9504);
	KerArg2->Norm = (unsigned char) (15);
	KerArg2->InFeatures = (unsigned short int) (128);
	KerArg2->LB = (int) (0);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+0), 16, 8, 8, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+32), 256, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory+34288+0), 4608, 0, &UchanHF1);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read Filter */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+4608), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory+34288+4608), 4608, 0, &UchanHF1);
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+34288+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+288+0), 4608, 0, &DmaR_Evt3);
	_NN_Filter=4608; _SN_Filter=4608;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1, D1Ind_NextLast = 1, D1Ind_NextNextLast = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1, T0Ind_NextLast = 1;
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<64; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==63), D0Ind_NextLast = ((D0Ind+1)==63), D0Ind_NextNextLast = ((D0Ind+2)==63);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (16); _LN_In = (8); _SN_In = (2*_LN_In); 
				} else if (!(1)) {
					_N_In = _N_In + (-1008); _LN_In = (8); _SN_In = (2*_LN_In); 
				}
				_SNN_Filter = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_Filter = _NN_Filter + ((4608)); _SNN_Filter = (((1)?(4608):(4608))); 
					} else if (!((1))) {
						_NN_Filter = _NN_Filter + ((-290304)); _SNN_Filter = (((1)?(4608):(4608))); 
					}
				} else if (!((1))) {
					_NN_Filter = _NN_Filter + ((4608)); _SNN_Filter = (((1)?(4608):(4608))); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+16*((D0Ind_Total+1)%2)),
							_SN_In, 8, _LN_In, 0, &DmaR_Evt1);
				}
				AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read Filter */
				if (_SNN_Filter) {
					AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+_NN_Filter), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory+34288+4608*((D0Ind_Total)%2)),
							_SNN_Filter, 0, &UchanHF1);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
				if (_SN_Filter) {
					AT_L2_COPY(0, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+34288+4608*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+288+4608*((D0Ind_Total+1)%2)),
							_SN_Filter, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (cnn_ssd_L1_Memory+0+16*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (4-1*(1)-1*(1));
				KerArg1->UsedH = (unsigned short int) (4-1*(1)-1*(1));
				KerArg1->Filter = (short int * __restrict__) (cnn_ssd_L1_Memory+288+4608*((D0Ind_Total)%2));
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
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+9504), 1024, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S51_Conv2d_18x128x3x3(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 15940 bytes, L2 buffer: 15684 bytes */
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
		[D1 Dim: Init: 18, Tiled: 2][Tile0 Dim: 1][D0 Dim: Init: 128, Tiled: 5]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 5 logical tiles, 5 physical tiles
			Total Size: 1024 [D0, [4 x 208, 192]][Tile0, 1:[2x2], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[2x3, 3:2x4, 2x3], 2][D0, [4 x 208, 192]]
		Tile0: [0, 208, 8], Tile1: [208, 208, 8], Tile2; [416, 208, 8]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 36 [D1, [1 x 32, 4]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 32, 4]]
		Tile0: [0, 36, 36], Tile1: [0, 36, 36], Tile2; [0, 36, 36]
	Ker Arg: Filter, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 10 logical tiles, 10 physical tiles
			Total Size: 41472 [D1, [1 x 36864, 4608]][D0, [4 x 7488, 6912]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 36864, 4608]][D0, [4 x 7488, 6912]]
		Tile0: [0, 7488, 7488], Tile1: [7488, 7488, 7488], Tile2; [14976, 7488, 7488]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 2 physical tiles
			Total Size: 144 [D1, [1 x 128, 16]][Tile0, 1:[2x2], 2]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 128, 16]][Tile0, 1:[2x2], 2]
		Tile0: [0, 128, 8], Tile1: [128, 16, 8], Tile2; [0, 128, 8]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 288 [D1, [1 x 256, 32]][Tile0, 1:[2x2], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 256, 32]][Tile0, 1:[2x2], 4]
		Tile0: [0, 256, 16], Tile1: [0, 256, 16], Tile2; [0, 256, 16]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (cnn_ssd_L1_Memory+15684);
	KerArg0->W = (unsigned short int) (2);
	KerArg0->H = (unsigned short int) (2);
	KerArg0->NormBias = (signed char) (13);
	KerArg1->W = (unsigned short int) (2);
	KerArg1->UsedW = (unsigned short int) (2);
	KerArg1->Out = (int * __restrict__) (cnn_ssd_L1_Memory+15684);
	KerArg1->Norm = (unsigned char) (16);
	KerArg1->Pad = (v4s) ((v4s){1,1,1,1});
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (cnn_ssd_L1_Memory+15684);
	KerArg2->W = (unsigned short int) (2);
	KerArg2->H = (unsigned short int) (2);
	KerArg2->Norm = (unsigned char) (16);
	KerArg2->LB = (int) (-32768);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+0), 208, 8, 8, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+416), 36, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory+34288+0), 7488, 0, &UchanHF1);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read Filter */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+7488), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory+34288+7488), 7488, 0, &UchanHF1);
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+34288+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+452+0), 7488, 0, &DmaR_Evt3);
	_NN_Filter=7488; _SN_Filter=7488;
	_C_Out=0; _SC_Out=128; _LC_Out=8;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	for (D1Ind=0; D1Ind<2; D1Ind++) { /* Iteration on D1 */
		int D1Ind_Last = (D1Ind==1), D1Ind_NextLast = ((D1Ind+1)==1), D1Ind_NextNextLast = ((D1Ind+2)==1);
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1, T0Ind_NextLast = 1;
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->OutFeatures = (unsigned short int) (D1Ind_Last?2:16);
			KerArg0->Bias = (short int * __restrict__) (cnn_ssd_L1_Memory+416+((D1Ind)*32));
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<5; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==4), D0Ind_NextLast = ((D0Ind+1)==4), D0Ind_NextNextLast = ((D0Ind+2)==4);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (208); _LN_In = (8); _SN_In = (((D0Ind_NextLast)?24:26)*_LN_In); 
				} else if (!(D1Ind_Last)) {
					_N_In = _N_In + (-832); _LN_In = (8); _SN_In = (26*_LN_In); 
				}
				_SNN_Filter = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_Filter = _NN_Filter + (((D1Ind_Last)?(936):(7488))); _SNN_Filter = (((D1Ind_Last)?(((D0Ind_NextNextLast)?864:936)):(((D0Ind_NextNextLast)?6912:7488)))); 
					} else if (!((1))) {
						_NN_Filter = _NN_Filter + (((D1Ind_Last)?(-3744):(-29952))); _SNN_Filter = (((D1Ind_Last)?(936):(7488))); 
					} else if (!(D1Ind_Last)) {
						_NN_Filter = _NN_Filter + (36864)+(((D1Ind_Last)?(-3744):(-29952))); _SNN_Filter = (((1)?(936):(7488))); 
					}
				} else if (!((1))) {
					_NN_Filter = _NN_Filter + (((D1Ind_Last)?(936):(7488))); _SNN_Filter = (((D1Ind_Last)?(936):(7488))); 
				} else if (!(D1Ind_Last)) {
					_NN_Filter = _NN_Filter + (((1)?(936):(7488))); _SNN_Filter = (((1)?(936):(7488))); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+208*((D0Ind_Total+1)%2)),
							_SN_In, 8, _LN_In, 0, &DmaR_Evt1);
				}
				AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read Filter */
				if (_SNN_Filter) {
					AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+_NN_Filter), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory+34288+7488*((D0Ind_Total)%2)),
							_SNN_Filter, 0, &UchanHF1);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
				if (_SN_Filter) {
					AT_L2_COPY(0, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+34288+7488*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+452+7488*((D0Ind_Total+1)%2)),
							_SN_Filter, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (cnn_ssd_L1_Memory+0+208*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (4-1*(1)-1*(1));
				KerArg1->UsedH = (unsigned short int) (4-1*(1)-1*(1));
				KerArg1->InFeatures = (unsigned short int) (D0Ind_Last?24:26);
				KerArg1->OutFeatures = (unsigned short int) (D1Ind_Last?2:16);
				KerArg1->Filter = (short int * __restrict__) (cnn_ssd_L1_Memory+452+7488*((D0Ind_Total)%2));
				KerArg1->TotalInFeatures = (short int) (D0Ind_Last?24:26);
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_DP_fp, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_DP_fp, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				_SN_Filter = _SNN_Filter;
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->Out = (short int * __restrict__) (cnn_ssd_L1_Memory+15428+128*((T0Ind_Total)%2));
			KerArg2->InFeatures = (unsigned short int) (D1Ind_Last?2:16);
			AT_FORK(gap_ncore(), (void *) KerDP_fp, (void *) KerArg2);
			__CALL(KerDP_fp, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) cnn_ssd_L2_Memory+3568+128*((T0Ind_Total+-1)%2)),
						_SP_Out, 8, _LP_Out, 1, &UchanHR2);
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+3568+128*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+15428+128*((T0Ind_Total)%2)),
					_SC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
			_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(D1Ind_Last)) {
				_C_Out = _C_Out + (128); _LC_Out = (8); _SC_Out = (((1)?2:16)*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
			T0Ind_Total++;
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) cnn_ssd_L2_Memory+3568+128*((T0Ind_Total+-1)%2)), _SP_Out, 8, _LP_Out, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S55_Conv2d_24x128x3x3(
		short int * __restrict__ In,
		short int * __restrict__ Filter,
		short int * __restrict__ Bias,
		short int * __restrict__ Out)

{
	/* Shared L1: 14704 bytes, L2 buffer: 14320 bytes */
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
		[D1 Dim: Init: 24, Tiled: 1][Tile0 Dim: 1][D0 Dim: Init: 128, Tiled: 8]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 8 logical tiles, 8 physical tiles
			Total Size: 1024 [D0, [7 x 128, 128]][Tile0, 1:[2x2], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[2x3, 6:2x4, 2x3], 2][D0, [7 x 128, 128]]
		Tile0: [0, 128, 8], Tile1: [128, 128, 8], Tile2; [256, 128, 8]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 48 [D1, [0 x 48, 48]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 48, 48]]
		Tile0: [0, 48, 48], Tile1: [0, 48, 48], Tile2; [0, 48, 48]
	Ker Arg: Filter, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 8 logical tiles, 8 physical tiles
			Total Size: 55296 [D1, [0 x 55296, 55296]][D0, [7 x 6912, 6912]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 55296, 55296]][D0, [7 x 6912, 6912]]
		Tile0: [0, 6912, 6912], Tile1: [6912, 6912, 6912], Tile2; [13824, 6912, 6912]
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
	KerArg0->Out = (int * __restrict__) (cnn_ssd_L1_Memory+14320);
	KerArg0->W = (unsigned short int) (2);
	KerArg0->H = (unsigned short int) (2);
	KerArg0->OutFeatures = (unsigned short int) (24);
	KerArg0->Bias = (short int * __restrict__) (cnn_ssd_L1_Memory+256);
	KerArg0->NormBias = (signed char) (13);
	KerArg1->W = (unsigned short int) (2);
	KerArg1->UsedW = (unsigned short int) (2);
	KerArg1->InFeatures = (unsigned short int) (16);
	KerArg1->OutFeatures = (unsigned short int) (24);
	KerArg1->Out = (int * __restrict__) (cnn_ssd_L1_Memory+14320);
	KerArg1->Norm = (unsigned char) (16);
	KerArg1->TotalInFeatures = (short int) (16);
	KerArg1->Pad = (v4s) ((v4s){1,1,1,1});
	KerArg1->Orientation = (unsigned char) (1);
	KerArg2->In = (int * __restrict__) (cnn_ssd_L1_Memory+14320);
	KerArg2->W = (unsigned short int) (2);
	KerArg2->H = (unsigned short int) (2);
	KerArg2->Out = (short int * __restrict__) (cnn_ssd_L1_Memory+14128);
	KerArg2->Norm = (unsigned char) (16);
	KerArg2->InFeatures = (unsigned short int) (24);
	KerArg2->LB = (int) (-32768);
	KerArg2->UB = (int) (32767);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+0), 128, 8, 8, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+256), 48, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory+34288+0), 6912, 0, &UchanHF1);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read Filter */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+6912), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory+34288+6912), 6912, 0, &UchanHF1);
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+34288+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+304+0), 6912, 0, &DmaR_Evt3);
	_NN_Filter=6912; _SN_Filter=6912;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1, D1Ind_NextLast = 1, D1Ind_NextNextLast = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1, T0Ind_NextLast = 1;
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			AT_FORK(gap_ncore(), (void *) KerParSetBias_DP_fp, (void *) KerArg0);
			__CALL(KerParSetBias_DP_fp, KerArg0);
			for (D0Ind=0; D0Ind<8; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==7), D0Ind_NextLast = ((D0Ind+1)==7), D0Ind_NextNextLast = ((D0Ind+2)==7);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (128); _LN_In = (8); _SN_In = (16*_LN_In); 
				} else if (!(1)) {
					_N_In = _N_In + (-896); _LN_In = (8); _SN_In = (16*_LN_In); 
				}
				_SNN_Filter = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_Filter = _NN_Filter + ((6912)); _SNN_Filter = (((1)?(6912):(6912))); 
					} else if (!((1))) {
						_NN_Filter = _NN_Filter + ((-48384)); _SNN_Filter = (((1)?(6912):(6912))); 
					}
				} else if (!((1))) {
					_NN_Filter = _NN_Filter + ((6912)); _SNN_Filter = (((1)?(6912):(6912))); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+0+128*((D0Ind_Total+1)%2)),
							_SN_In, 8, _LN_In, 0, &DmaR_Evt1);
				}
				AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read Filter */
				if (_SNN_Filter) {
					AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+_NN_Filter), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory+34288+6912*((D0Ind_Total)%2)),
							_SNN_Filter, 0, &UchanHF1);
				}
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Filter */
				if (_SN_Filter) {
					AT_L2_COPY(0, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+34288+6912*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+304+6912*((D0Ind_Total+1)%2)),
							_SN_Filter, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (short int * __restrict__) (cnn_ssd_L1_Memory+0+128*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (4-1*(1)-1*(1));
				KerArg1->UsedH = (unsigned short int) (4-1*(1)-1*(1));
				KerArg1->Filter = (short int * __restrict__) (cnn_ssd_L1_Memory+304+6912*((D0Ind_Total)%2));
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
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) cnn_ssd_L2_Memory+3568+0), ((AT_L2_INT_ADDR_TYPE) cnn_ssd_L1_Memory+14128), 192, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+0), ((AT_HYPERRAM_INT_ADDR_TYPE) cnn_ssd_L2_Memory+3568+0), 192, 1, &UchanHR2);
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
	cnn_ssd_L3_Memory = (AT_HYPERRAM_POINTER) AT_HYPERRAM_ALLOC(&HyperRam, 122880);
	if (cnn_ssd_L3_Memory == 0) return 2;
	cnn_ssd_L2_Memory = (AT_L2_POINTER) AT_L2_ALLOC(0, 49264);
	if (cnn_ssd_L2_Memory == 0) return 3;
	cnn_ssd_L1_Memory = (AT_L1_POINTER) AT_L1_ALLOC(0, 16544);
	if (cnn_ssd_L1_Memory == 0) return 4;
	/* Moving Conv_0_weights, size 144 from HyperFlash at 761984 to (size 144) L2 at 0..143 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L3_Flash + 761984), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory + 0), 144, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Constant_103, size 16 from HyperFlash at 762720 to (size 16) L2 at 176..191 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L3_Flash + 762720), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory + 176), 16, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Conv_3_weights, size 2304 from HyperFlash at 759168 to (size 2304) L2 at 192..2495 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L3_Flash + 759168), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory + 192), 2304, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Constant_106, size 32 from HyperFlash at 762656 to (size 32) L2 at 144..175 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L3_Flash + 762656), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory + 144), 32, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Constant_109, size 32 from HyperFlash at 762688 to (size 32) L2 at 3536..3567 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L3_Flash + 762688), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory + 3536), 32, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Constant_112, size 64 from HyperFlash at 762256 to (size 64) L2 at 3136..3199 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L3_Flash + 762256), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory + 3136), 64, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Constant_classification_headers.0.bias, size 36 from HyperFlash at 762512 to (size 36) L2 at 3392..3427 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L3_Flash + 762512), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory + 3392), 36, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Constant_regression_headers.0.bias, size 48 from HyperFlash at 762320 to (size 48) L2 at 3200..3247 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L3_Flash + 762320), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory + 3200), 48, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Constant_115, size 128 from HyperFlash at 762128 to (size 128) L2 at 3008..3135 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L3_Flash + 762128), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory + 3008), 128, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Constant_classification_headers.1.bias, size 36 from HyperFlash at 762548 to (size 36) L2 at 3428..3463 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L3_Flash + 762548), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory + 3428), 36, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Constant_regression_headers.1.bias, size 48 from HyperFlash at 762368 to (size 48) L2 at 3248..3295 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L3_Flash + 762368), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory + 3248), 48, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Constant_118, size 256 from HyperFlash at 761472 to (size 256) L2 at 2496..2751 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L3_Flash + 761472), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory + 2496), 256, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Constant_classification_headers.2.bias, size 36 from HyperFlash at 762584 to (size 36) L2 at 3464..3499 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L3_Flash + 762584), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory + 3464), 36, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Constant_regression_headers.2.bias, size 48 from HyperFlash at 762416 to (size 48) L2 at 3296..3343 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L3_Flash + 762416), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory + 3296), 48, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Constant_121, size 256 from HyperFlash at 761728 to (size 256) L2 at 2752..3007 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L3_Flash + 761728), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory + 2752), 256, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Constant_classification_headers.3.bias, size 36 from HyperFlash at 762620 to (size 36) L2 at 3500..3535 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L3_Flash + 762620), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory + 3500), 36, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Constant_regression_headers.3.bias, size 48 from HyperFlash at 762464 to (size 48) L2 at 3344..3391 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L3_Flash + 762464), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory + 3344), 48, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	return 0;
}
int cnn_ssdCNN_Destruct()

{
	AT_HYPERRAM_FREE(&HyperRam, cnn_ssd_L3_Memory, 122880);
	AT_L2_FREE(0, cnn_ssd_L2_Memory, 49264);
	AT_L1_FREE(0, cnn_ssd_L1_Memory, 16544);
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
	/* Moving Conv_6_weights, size 4608 from HyperFlash at 754560 to (size 4608) L2 at 18928 using event 0 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) cnn_ssd_L3_Flash + 754560), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) cnn_ssd_L2_Memory + 18928), 4608, 0, &UchanHF0);
	AT_GraphPerf[0] = gap_cl_readhwtimer();
	S3_Conv2d_8x1x3x3_MaxPool_2x2_Relu(
		((signed short * __restrict__) Input_1), /* In */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+0)), /* Filter */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+176)), /* Bias */
		((signed short * __restrict__) (cnn_ssd_L3_Memory+0)) /* Out */
	);
	AT_GraphPerf[0] = gap_cl_readhwtimer() - AT_GraphPerf[0];
	AT_GraphPerf[1] = gap_cl_readhwtimer();
	S6_Conv2d_16x8x3x3_MaxPool_2x2_Relu(
		((signed short * __restrict__) (cnn_ssd_L3_Memory+0)), /* In */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+192)), /* Filter */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+144)), /* Bias */
		((signed short * __restrict__) (cnn_ssd_L3_Memory+81920)) /* Out */
	);
	AT_GraphPerf[1] = gap_cl_readhwtimer() - AT_GraphPerf[1];
	/* Waiting completion of transfer of Conv_6_weights using event 0 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF0);
	AT_GraphPerf[2] = gap_cl_readhwtimer();
	S9_Conv2d_16x16x3x3_MaxPool_2x2_Relu(
		((signed short * __restrict__) (cnn_ssd_L3_Memory+81920)), /* In */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+18928)), /* Filter */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+3536)), /* Bias */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+3568)) /* Out */
	);
	AT_GraphPerf[2] = gap_cl_readhwtimer() - AT_GraphPerf[2];
	AT_GraphPerf[3] = gap_cl_readhwtimer();
	S12_Conv2d_32x16x3x3_Relu(
		((signed short * __restrict__) (cnn_ssd_L2_Memory+3568)), /* In */
		((signed short * __restrict__) (cnn_ssd_L3_Flash+745344)), /* Filter */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+3136)), /* Bias */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+13808)) /* Out */
	);
	AT_GraphPerf[3] = gap_cl_readhwtimer() - AT_GraphPerf[3];
	AT_GraphPerf[4] = gap_cl_readhwtimer();
	S13_MaxPool_2x2(
		((signed short * __restrict__) (cnn_ssd_L2_Memory+13808)), /* In */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+3568)) /* Out */
	);
	AT_GraphPerf[4] = gap_cl_readhwtimer() - AT_GraphPerf[4];
	AT_GraphPerf[5] = gap_cl_readhwtimer();
	S24_Conv2d_64x32x3x3_Relu(
		((signed short * __restrict__) (cnn_ssd_L2_Memory+3568)), /* In */
		((signed short * __restrict__) (cnn_ssd_L3_Flash+0)), /* Filter */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+3008)), /* Bias */
		((signed short * __restrict__) (cnn_ssd_L3_Memory+0)) /* Out */
	);
	AT_GraphPerf[5] = gap_cl_readhwtimer() - AT_GraphPerf[5];
	AT_GraphPerf[6] = gap_cl_readhwtimer();
	S25_MaxPool_2x2(
		((signed short * __restrict__) (cnn_ssd_L3_Memory+0)), /* In */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+34288)) /* Out */
	);
	AT_GraphPerf[6] = gap_cl_readhwtimer() - AT_GraphPerf[6];
	AT_GraphPerf[7] = gap_cl_readhwtimer();
	S36_Conv2d_128x64x3x3_Relu(
		((signed short * __restrict__) (cnn_ssd_L2_Memory+34288)), /* In */
		((signed short * __restrict__) (cnn_ssd_L3_Flash+85248)), /* Filter */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+2496)), /* Bias */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+4592)) /* Out */
	);
	AT_GraphPerf[7] = gap_cl_readhwtimer() - AT_GraphPerf[7];
	AT_GraphPerf[8] = gap_cl_readhwtimer();
	S40_Conv2d_18x128x3x3(
		((signed short * __restrict__) (cnn_ssd_L2_Memory+4592)), /* In */
		((signed short * __restrict__) (cnn_ssd_L3_Flash+232704)), /* Filter */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+3464)), /* Bias */
		((signed short * __restrict__) Output_5) /* Out */
	);
	AT_GraphPerf[8] = gap_cl_readhwtimer() - AT_GraphPerf[8];
	AT_GraphPerf[9] = gap_cl_readhwtimer();
	S44_Conv2d_24x128x3x3(
		((signed short * __restrict__) (cnn_ssd_L2_Memory+4592)), /* In */
		((signed short * __restrict__) (cnn_ssd_L3_Flash+274176)), /* Filter */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+3296)), /* Bias */
		((signed short * __restrict__) Output_6) /* Out */
	);
	AT_GraphPerf[9] = gap_cl_readhwtimer() - AT_GraphPerf[9];
	AT_GraphPerf[10] = gap_cl_readhwtimer();
	S37_MaxPool_2x2(
		((signed short * __restrict__) (cnn_ssd_L2_Memory+4592)), /* In */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+3568)) /* Out */
	);
	AT_GraphPerf[10] = gap_cl_readhwtimer() - AT_GraphPerf[10];
	AT_GraphPerf[11] = gap_cl_readhwtimer();
	S48_Conv2d_128x128x3x3_Relu(
		((signed short * __restrict__) (cnn_ssd_L2_Memory+3568)), /* In */
		((signed short * __restrict__) (cnn_ssd_L3_Flash+329472)), /* Filter */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+2752)), /* Bias */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+4592)) /* Out */
	);
	AT_GraphPerf[11] = gap_cl_readhwtimer() - AT_GraphPerf[11];
	AT_GraphPerf[12] = gap_cl_readhwtimer();
	S51_Conv2d_18x128x3x3(
		((signed short * __restrict__) (cnn_ssd_L2_Memory+4592)), /* In */
		((signed short * __restrict__) (cnn_ssd_L3_Flash+624384)), /* Filter */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+3500)), /* Bias */
		((signed short * __restrict__) Output_7) /* Out */
	);
	AT_GraphPerf[12] = gap_cl_readhwtimer() - AT_GraphPerf[12];
	AT_GraphPerf[13] = gap_cl_readhwtimer();
	S55_Conv2d_24x128x3x3(
		((signed short * __restrict__) (cnn_ssd_L2_Memory+4592)), /* In */
		((signed short * __restrict__) (cnn_ssd_L3_Flash+665856)), /* Filter */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+3344)), /* Bias */
		((signed short * __restrict__) Output_8) /* Out */
	);
	AT_GraphPerf[13] = gap_cl_readhwtimer() - AT_GraphPerf[13];
	AT_GraphPerf[14] = gap_cl_readhwtimer();
	S28_Conv2d_18x64x3x3(
		((signed short * __restrict__) (cnn_ssd_L3_Memory+0)), /* In */
		((signed short * __restrict__) (cnn_ssd_L3_Flash+36864)), /* Filter */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+3428)), /* Bias */
		((signed short * __restrict__) Output_3) /* Out */
	);
	AT_GraphPerf[14] = gap_cl_readhwtimer() - AT_GraphPerf[14];
	AT_GraphPerf[15] = gap_cl_readhwtimer();
	S32_Conv2d_24x64x3x3(
		((signed short * __restrict__) (cnn_ssd_L3_Memory+0)), /* In */
		((signed short * __restrict__) (cnn_ssd_L3_Flash+57600)), /* Filter */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+3248)), /* Bias */
		((signed short * __restrict__) Output_4) /* Out */
	);
	AT_GraphPerf[15] = gap_cl_readhwtimer() - AT_GraphPerf[15];
	AT_GraphPerf[16] = gap_cl_readhwtimer();
	S16_Conv2d_18x32x3x3(
		((signed short * __restrict__) (cnn_ssd_L2_Memory+13808)), /* In */
		((signed short * __restrict__) (cnn_ssd_L3_Flash+734976)), /* Filter */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+3392)), /* Bias */
		((signed short * __restrict__) Output_1) /* Out */
	);
	AT_GraphPerf[16] = gap_cl_readhwtimer() - AT_GraphPerf[16];
	AT_GraphPerf[17] = gap_cl_readhwtimer();
	S20_Conv2d_24x32x3x3(
		((signed short * __restrict__) (cnn_ssd_L2_Memory+13808)), /* In */
		((signed short * __restrict__) (cnn_ssd_L3_Flash+721152)), /* Filter */
		((signed short * __restrict__) (cnn_ssd_L2_Memory+3200)), /* Bias */
		((signed short * __restrict__) Output_2) /* Out */
	);
	AT_GraphPerf[17] = gap_cl_readhwtimer() - AT_GraphPerf[17];
	return 0;
}
