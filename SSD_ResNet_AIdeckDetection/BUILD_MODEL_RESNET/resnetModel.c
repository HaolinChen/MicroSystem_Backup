#include <stdint.h>
#include <stdio.h>
#include "AutoTilerLib.h"
#include "CNN_Generators.h"

#include "CNN_Copy_Generators.h"





void resnetModel(unsigned int L1Memory, unsigned int L2Memory, unsigned int L3Memory, unsigned int L3Flash)
{
    KernelOper_T Cop = KOP_CONV;

    // SetKernelOpts(KER_OPT_NONE, KER_OPT_BUFFER_PROMOTE);
    SetSymbolDynamics();

    SetUsedFilesNames(0, 2, "CNN_BasicKernels.h", "resnet.h");
    SetGeneratedFilesNames("resnetKernels.c", "resnetKernels.h");


    SetMemoryDeviceInfos(4,
        AT_MEM_L1, L1Memory, "resnet_L1_Memory", 0, 0,
        AT_MEM_L2, L2Memory, "resnet_L2_Memory", 0, 1,
        AT_MEM_L3_HRAM, L3Memory, "resnet_L3_Memory", 0, 1,
        AT_MEM_L3_HFLASH, L3Flash, "resnet_L3_Flash", "resnet_L3_Flash_Const.dat", 0
    );

    LoadCNNLibrary();


    
    // generator for DEPTHWISE_CONV_2D_0_0_fusion
    CNN_ConvolutionPoolReLU("S4_Conv2d_8x1x3x3_Relu", 0,
                            2, 2, 2, 2,
                            15, 11, 13, 12,
                            1, 1, 1, 1, 1, 8, 160, 160,
                            KOP_CONV_DP, 3, 3, 1, 1, 2, 2, 0,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_RELU);
    
    
    // generator for CONV_2D_0_1_fusion
    CNN_ConvolutionPoolReLU("S7_Conv2d_8x8x3x3_Relu", 0,
                            2, 2, 2, 2,
                            12, 13, 13, 11,
                            1, 1, 1, 1, 8, 8, 79, 79,
                            KOP_CONV_DP, 3, 3, 1, 1, 2, 2, 0,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_RELU);
    
    
    // generator for CONV_2D_0_2_fusion
    CNN_ConvolutionPoolReLU("S10_Conv2d_8x8x3x3_Relu", 0,
                            2, 2, 2, 2,
                            11, 14, 13, 12,
                            1, 1, 1, 1, 8, 8, 39, 39,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_RELU);
    
    
    // generator for CONV_2D_0_3
    CNN_ConvolutionPoolReLU("S13_Conv2d_8x8x3x3", 0,
                            2, 2, 2, 2,
                            12, 13, 14, 10,
                            1, 1, 1, 1, 8, 8, 39, 39,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_NONE);
    
    
    // generator for ADD_0_4
    CNN_MatAddDynAdjust("S14_MatAdd_8x39x39", 0, 2, 2, 2,
                        10, 11, 10, 1, 1, 1, 
                        8, 8, 
                        39, 39, KOP_MATADD_DYNADJUST);
    
    
    // generator for CONV_2D_0_5_fusion
    CNN_ConvolutionPoolReLU("S17_Conv2d_8x8x3x3_Relu", 0,
                            2, 2, 2, 2,
                            10, 15, 15, 12,
                            1, 1, 1, 1, 8, 8, 39, 39,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_RELU);
    
    
    // generator for CONV_2D_0_6
    CNN_ConvolutionPoolReLU("S20_Conv2d_8x8x3x3", 0,
                            2, 2, 2, 2,
                            12, 14, 13, 11,
                            1, 1, 1, 1, 8, 8, 39, 39,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_NONE);
    
    
    // generator for ADD_0_7
    CNN_MatAddDynAdjust("S21_MatAdd_8x39x39", 0, 2, 2, 2,
                        11, 10, 10, 1, 1, 1, 
                        8, 8, 
                        39, 39, KOP_MATADD_DYNADJUST);
    
    
    // generator for CONV_2D_0_8_fusion
    CNN_ConvolutionPoolReLU("S24_Conv2d_16x8x3x3_Relu", 0,
                            2, 2, 2, 2,
                            10, 15, 14, 12,
                            1, 1, 1, 1, 8, 16, 39, 39,
                            KOP_CONV_DP, 3, 3, 1, 1, 2, 2, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_RELU);
    
    
    // generator for CONV_2D_0_9
    CNN_ConvolutionPoolReLU("S27_Conv2d_16x8x1x1", 0,
                            2, 2, 2, 2,
                            10, 15, 14, 11,
                            1, 1, 1, 1, 8, 16, 39, 39,
                            KOP_CONV_DP, 1, 1, 1, 1, 2, 2, 0,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_NONE);
    
    
    // generator for CONV_2D_0_10_fusion
    CNN_ConvolutionPoolReLU("S30_Conv2d_16x16x3x3_Relu", 0,
                            2, 2, 2, 2,
                            12, 14, 13, 12,
                            1, 1, 1, 1, 16, 16, 20, 20,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_RELU);
    
    
    // generator for ADD_0_11
    CNN_MatAddDynAdjust("S31_MatAdd_16x20x20", 0, 2, 2, 2,
                        12, 11, 11, 1, 1, 1, 
                        16, 16, 
                        20, 20, KOP_MATADD_DYNADJUST);
    
    
    // generator for CONV_2D_0_12_fusion
    CNN_ConvolutionPoolReLU("S34_Conv2d_16x16x3x3_Relu", 0,
                            2, 2, 2, 2,
                            11, 15, 15, 12,
                            1, 1, 1, 1, 16, 16, 20, 20,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_RELU);
    
    
    // generator for CONV_2D_0_13
    CNN_ConvolutionPoolReLU("S37_Conv2d_16x16x3x3", 0,
                            2, 2, 2, 2,
                            12, 14, 13, 11,
                            1, 1, 1, 1, 16, 16, 20, 20,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_NONE);
    
    // generator for ADD_0_14
    CNN_MatAdd("S38_MatAdd_16x20x20", 0, 2, 2, 2, 11, 11, 11, 1, 1, 1, 16, 16, 20, 20, KOP_MATADD);
    CNN_GenControl_T gen_ctrl_S41_Conv2d_32x16x3x3_Relu;
    CNN_InitGenCtrl(&gen_ctrl_S41_Conv2d_32x16x3x3_Relu);
    CNN_SetGenCtrl(&gen_ctrl_S41_Conv2d_32x16x3x3_Relu, "PADTYPE", AT_OPT_VAL(1));
    
    // generator for CONV_2D_0_15_fusion
    CNN_ConvolutionPoolReLU("S41_Conv2d_32x16x3x3_Relu", &gen_ctrl_S41_Conv2d_32x16x3x3_Relu,
                            2, 2, 2, 2,
                            11, 15, 14, 12,
                            1, 1, 1, 1, 16, 32, 20, 20,
                            KOP_CONV_DP, 3, 3, 1, 1, 2, 2, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_RELU);
    
    
    // generator for CONV_2D_0_16
    CNN_ConvolutionPoolReLU("S44_Conv2d_32x16x1x1", 0,
                            2, 2, 2, 2,
                            11, 15, 14, 11,
                            1, 1, 1, 1, 16, 32, 20, 20,
                            KOP_CONV_DP, 1, 1, 1, 1, 2, 2, 0,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_NONE);
    
    
    // generator for CONV_2D_0_17_fusion
    CNN_ConvolutionPoolReLU("S47_Conv2d_32x32x3x3_Relu", 0,
                            2, 2, 2, 2,
                            12, 14, 12, 12,
                            1, 1, 1, 1, 32, 32, 10, 10,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_RELU);
    
    
    // generator for ADD_0_18
    CNN_MatAddDynAdjust("S48_MatAdd_32x10x10", 0, 2, 2, 2,
                        12, 11, 11, 1, 1, 1, 
                        32, 32, 
                        10, 10, KOP_MATADD_DYNADJUST);
    
    
    // generator for CONV_2D_0_19_fusion
    CNN_ConvolutionPoolReLU("S51_Conv2d_32x32x3x3_Relu", 0,
                            2, 2, 2, 2,
                            11, 15, 15, 12,
                            1, 1, 1, 1, 32, 32, 10, 10,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_RELU);
    
    
    // generator for CONV_2D_0_20
    CNN_ConvolutionPoolReLU("S54_Conv2d_32x32x3x3", 0,
                            2, 2, 2, 2,
                            12, 14, 13, 11,
                            1, 1, 1, 1, 32, 32, 10, 10,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_NONE);
    
    // generator for ADD_0_21
    CNN_MatAdd("S55_MatAdd_32x10x10", 0, 2, 2, 2, 11, 11, 11, 1, 1, 1, 32, 32, 10, 10, KOP_MATADD);
    CNN_GenControl_T gen_ctrl_S58_Conv2d_64x32x3x3_Relu;
    CNN_InitGenCtrl(&gen_ctrl_S58_Conv2d_64x32x3x3_Relu);
    CNN_SetGenCtrl(&gen_ctrl_S58_Conv2d_64x32x3x3_Relu, "PADTYPE", AT_OPT_VAL(1));
    
    // generator for CONV_2D_0_22_fusion
    CNN_ConvolutionPoolReLU("S58_Conv2d_64x32x3x3_Relu", &gen_ctrl_S58_Conv2d_64x32x3x3_Relu,
                            2, 2, 2, 2,
                            11, 15, 15, 12,
                            1, 1, 1, 1, 32, 64, 10, 10,
                            KOP_CONV_DP, 3, 3, 1, 1, 2, 2, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_RELU);
    
    
    // generator for CONV_2D_0_23
    CNN_ConvolutionPoolReLU("S61_Conv2d_64x32x1x1", 0,
                            2, 2, 2, 2,
                            11, 15, 15, 13,
                            1, 1, 1, 1, 32, 64, 10, 10,
                            KOP_CONV_DP, 1, 1, 1, 1, 2, 2, 0,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_NONE);
    
    
    // generator for CONV_2D_0_24_fusion
    CNN_ConvolutionPoolReLU("S64_Conv2d_64x64x3x3_Relu", 0,
                            2, 2, 2, 2,
                            12, 14, 13, 13,
                            1, 1, 1, 1, 64, 64, 5, 5,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_RELU);
    
    
    // generator for ADD_0_25
    CNN_MatAddDynAdjust("S65_MatAdd_64x5x5", 0, 2, 2, 2,
                        13, 13, 12, 1, 1, 1, 
                        64, 64, 
                        5, 5, KOP_MATADD_DYNADJUST);
    
    
    // generator for CONV_2D_0_26_fusion
    CNN_ConvolutionPoolReLU("S68_Conv2d_64x64x3x3_Relu", 0,
                            2, 2, 2, 2,
                            12, 15, 15, 13,
                            1, 1, 1, 1, 64, 64, 5, 5,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_RELU);
    
    
    // generator for CONV_2D_0_27
    CNN_ConvolutionPoolReLU("S71_Conv2d_64x64x3x3", 0,
                            2, 2, 2, 2,
                            13, 14, 15, 12,
                            1, 1, 1, 1, 64, 64, 5, 5,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_NONE);
    
    // generator for ADD_0_28
    CNN_MatAdd("S72_MatAdd_64x5x5", 0, 2, 2, 2, 12, 12, 12, 1, 1, 1, 64, 64, 5, 5, KOP_MATADD);
    
    // generator for AVERAGE_POOL_2D_0_29
    CNN_PoolReLU("S73_AveragePool_2x2", 0,
                  2, 2,
                  12, 12,
                  1, 1, 64, 64, 5, 5,
                  KOP_AVGPOOL, 2, 2, 1, 1, 2, 2, 0,
                  KOP_NONE);
    
    
    // generator for FULLY_CONNECTED_0_30
    CNN_LinearReLU("S76_Linear_7x256", 0, 2, 2,
                    2, 2, 12, 15, 15,
                    12, 1, 1, 1, 1, 256, 7, KOP_LINEAR, KOP_NONE);
    
    // generator for SOFTMAX_0_31
    CNN_SoftMax("S77_SoftMax", 0, 2, 2, 12, 15, 1, 1, 7, KOP_SOFTMAX);

#define GRAPH
#ifdef GRAPH
    CreateGraph("resnetCNN",
        /* Arguments either passed or globals */
            CArgs(46,
                TCArgInfo("signed short * __restrict__", "Input_1", ARG_SCOPE_ARG, ARG_DIR_IN, AT_MEM_L2, AT_MEM_L2, 0),
                TCArgInfo("signed short * __restrict__", "Conv1kernel", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Conv1kernel.tensor", 1, 1, 16, 11)),
                TCArgInfo("signed short * __restrict__", "Model_1conv1conv2d_bias", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Model_1conv1conv2d_bias.tensor", 1, 1, 16, 13)),
                TCArgInfo("signed short * __restrict__", "Conv2kernel", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Conv2kernel.tensor", 1, 1, 16, 13)),
                TCArgInfo("signed short * __restrict__", "Model_1conv2conv2d_bias", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Model_1conv2conv2d_bias.tensor", 1, 1, 16, 13)),
                TCArgInfo("signed short * __restrict__", "Res2bbranch2akernel", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Res2bbranch2akernel.tensor", 1, 1, 16, 14)),
                TCArgInfo("signed short * __restrict__", "Model_1res2bbranch2aconv2d_bia", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Model_1res2bbranch2aconv2d_bia.tensor", 1, 1, 16, 13)),
                TCArgInfo("signed short * __restrict__", "Res2bbranch2bkernel", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Res2bbranch2bkernel.tensor", 1, 1, 16, 13)),
                TCArgInfo("signed short * __restrict__", "Model_1res2bbranch2bconv2d_bia", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Model_1res2bbranch2bconv2d_bia.tensor", 1, 1, 16, 14)),
                TCArgInfo("signed short * __restrict__", "Res2cbranch2akernel", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Res2cbranch2akernel.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Model_1res2cbranch2aconv2d_bia", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Model_1res2cbranch2aconv2d_bia.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Res2cbranch2bkernel", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Res2cbranch2bkernel.tensor", 1, 1, 16, 14)),
                TCArgInfo("signed short * __restrict__", "Model_1res2cbranch2bconv2d_bia", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Model_1res2cbranch2bconv2d_bia.tensor", 1, 1, 16, 13)),
                TCArgInfo("signed short * __restrict__", "Res3a_branch2akernel", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Res3a_branch2akernel.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Model_1res3a_branch2aconv2d_bi", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Model_1res3a_branch2aconv2d_bi.tensor", 1, 1, 16, 14)),
                TCArgInfo("signed short * __restrict__", "Res3a_branch1kernel", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Res3a_branch1kernel.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Model_1res3a_branch1conv2d_bia", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Model_1res3a_branch1conv2d_bia.tensor", 1, 1, 16, 14)),
                TCArgInfo("signed short * __restrict__", "Res3a_branch2bkernel", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Res3a_branch2bkernel.tensor", 1, 1, 16, 14)),
                TCArgInfo("signed short * __restrict__", "Model_1res3a_branch2bconv2d_bi", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Model_1res3a_branch2bconv2d_bi.tensor", 1, 1, 16, 13)),
                TCArgInfo("signed short * __restrict__", "Res3bbranch2akernel", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Res3bbranch2akernel.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Model_1res3bbranch2aconv2d_bia", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Model_1res3bbranch2aconv2d_bia.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Res3bbranch2bkernel", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Res3bbranch2bkernel.tensor", 1, 1, 16, 14)),
                TCArgInfo("signed short * __restrict__", "Model_1res3bbranch2bconv2d_bia", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Model_1res3bbranch2bconv2d_bia.tensor", 1, 1, 16, 13)),
                TCArgInfo("signed short * __restrict__", "Res4a_branch2akernel", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Res4a_branch2akernel.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Model_1res4a_branch2aconv2d_bi", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Model_1res4a_branch2aconv2d_bi.tensor", 1, 1, 16, 14)),
                TCArgInfo("signed short * __restrict__", "Res4a_branch1kernel", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Res4a_branch1kernel.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Model_1res4a_branch1conv2d_bia", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Model_1res4a_branch1conv2d_bia.tensor", 1, 1, 16, 14)),
                TCArgInfo("signed short * __restrict__", "Res4a_branch2bkernel", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Res4a_branch2bkernel.tensor", 1, 1, 16, 14)),
                TCArgInfo("signed short * __restrict__", "Model_1res4a_branch2bconv2d_bi", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Model_1res4a_branch2bconv2d_bi.tensor", 1, 1, 16, 12)),
                TCArgInfo("signed short * __restrict__", "Res4bbranch2akernel", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Res4bbranch2akernel.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Model_1res4bbranch2aconv2d_bia", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Model_1res4bbranch2aconv2d_bia.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Res4bbranch2bkernel", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Res4bbranch2bkernel.tensor", 1, 1, 16, 14)),
                TCArgInfo("signed short * __restrict__", "Model_1res4bbranch2bconv2d_bia", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Model_1res4bbranch2bconv2d_bia.tensor", 1, 1, 16, 13)),
                TCArgInfo("signed short * __restrict__", "Res5a_branch2akernel", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Res5a_branch2akernel.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Model_1res5a_branch2aconv2d_bi", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Model_1res5a_branch2aconv2d_bi.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Res5a_branch1kernel", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Res5a_branch1kernel.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Model_1res5a_branch1conv2d_bia", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Model_1res5a_branch1conv2d_bia.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Res5a_branch2bkernel", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Res5a_branch2bkernel.tensor", 1, 1, 16, 14)),
                TCArgInfo("signed short * __restrict__", "Model_1res5a_branch2bconv2d_bi", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Model_1res5a_branch2bconv2d_bi.tensor", 1, 1, 16, 13)),
                TCArgInfo("signed short * __restrict__", "Res5bbranch2akernel", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Res5bbranch2akernel.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Model_1res5bbranch2aconv2d_bia", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Model_1res5bbranch2aconv2d_bia.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Res5bbranch2bkernel", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Res5bbranch2bkernel.tensor", 1, 1, 16, 14)),
                TCArgInfo("signed short * __restrict__", "Model_1res5bbranch2bconv2d_bia", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Model_1res5bbranch2bconv2d_bia.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Weightedaveragekerneltranspose", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Weightedaveragekerneltranspose.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "M2weightedaveragematmul_bias", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/M2weightedaveragematmul_bias.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Output_1", ARG_SCOPE_ARG, ARG_DIR_OUT, AT_MEM_L2, AT_MEM_L2, 0)
            ),
        /* Locals, allocated dynamically */
        CArgs(31,
            TCArgInfo("signed short * __restrict__", "S4_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S7_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S10_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S13_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S14_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S17_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S20_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S21_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S24_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S27_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S30_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S31_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S34_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S37_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S38_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S41_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S44_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S47_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S48_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S51_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S54_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S55_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S58_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S61_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S64_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S65_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S68_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S71_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S72_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S73_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S76_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0)
        )
    );

    /* Stacked tensors - Concats */
    // no concats in graph so not stacked tensors created

    // Node S4_Conv2d_8x1x3x3_Relu inq 15 weightsq 11 outq 12 biasesq 13
    AddNode("S4_Conv2d_8x1x3x3_Relu", Bindings(4, GNodeArg(GNA_IN, "Input_1", 0), GNodeArg(GNA_IN, "Conv1kernel", 0), GNodeArg(GNA_IN, "Model_1conv1conv2d_bias", 0), GNodeArg(GNA_OUT, "S4_Output", 0)));
    // Node S7_Conv2d_8x8x3x3_Relu inq 12 weightsq 13 outq 11 biasesq 13
    AddNode("S7_Conv2d_8x8x3x3_Relu", Bindings(4, GNodeArg(GNA_IN, "S4_Output", 0), GNodeArg(GNA_IN, "Conv2kernel", 0), GNodeArg(GNA_IN, "Model_1conv2conv2d_bias", 0), GNodeArg(GNA_OUT, "S7_Output", 0)));
    // Node S10_Conv2d_8x8x3x3_Relu inq 11 weightsq 14 outq 12 biasesq 13
    AddNode("S10_Conv2d_8x8x3x3_Relu", Bindings(4, GNodeArg(GNA_IN, "S7_Output", 0), GNodeArg(GNA_IN, "Res2bbranch2akernel", 0), GNodeArg(GNA_IN, "Model_1res2bbranch2aconv2d_bia", 0), GNodeArg(GNA_OUT, "S10_Output", 0)));
    // Node S13_Conv2d_8x8x3x3 inq 12 weightsq 13 outq 10 biasesq 14
    AddNode("S13_Conv2d_8x8x3x3", Bindings(4, GNodeArg(GNA_IN, "S10_Output", 0), GNodeArg(GNA_IN, "Res2bbranch2bkernel", 0), GNodeArg(GNA_IN, "Model_1res2bbranch2bconv2d_bia", 0), GNodeArg(GNA_OUT, "S13_Output", 0)));
    // Node ADD_0_4 inq1 10 inq2 11 outq 10
    AddNode("S14_MatAdd_8x39x39", Bindings(3, GNodeArg(GNA_IN, "S13_Output", 0), GNodeArg(GNA_IN, "S7_Output", 0), GNodeArg(GNA_OUT, "S14_Output", 0)));
    // Node S17_Conv2d_8x8x3x3_Relu inq 10 weightsq 15 outq 12 biasesq 15
    AddNode("S17_Conv2d_8x8x3x3_Relu", Bindings(4, GNodeArg(GNA_IN, "S14_Output", 0), GNodeArg(GNA_IN, "Res2cbranch2akernel", 0), GNodeArg(GNA_IN, "Model_1res2cbranch2aconv2d_bia", 0), GNodeArg(GNA_OUT, "S17_Output", 0)));
    // Node S20_Conv2d_8x8x3x3 inq 12 weightsq 14 outq 11 biasesq 13
    AddNode("S20_Conv2d_8x8x3x3", Bindings(4, GNodeArg(GNA_IN, "S17_Output", 0), GNodeArg(GNA_IN, "Res2cbranch2bkernel", 0), GNodeArg(GNA_IN, "Model_1res2cbranch2bconv2d_bia", 0), GNodeArg(GNA_OUT, "S20_Output", 0)));
    // Node ADD_0_7 inq1 11 inq2 10 outq 10
    AddNode("S21_MatAdd_8x39x39", Bindings(3, GNodeArg(GNA_IN, "S20_Output", 0), GNodeArg(GNA_IN, "S14_Output", 0), GNodeArg(GNA_OUT, "S21_Output", 0)));
    // Node S24_Conv2d_16x8x3x3_Relu inq 10 weightsq 15 outq 12 biasesq 14
    AddNode("S24_Conv2d_16x8x3x3_Relu", Bindings(4, GNodeArg(GNA_IN, "S21_Output", 0), GNodeArg(GNA_IN, "Res3a_branch2akernel", 0), GNodeArg(GNA_IN, "Model_1res3a_branch2aconv2d_bi", 0), GNodeArg(GNA_OUT, "S24_Output", 0)));
    // Node S27_Conv2d_16x8x1x1 inq 10 weightsq 15 outq 11 biasesq 14
    AddNode("S27_Conv2d_16x8x1x1", Bindings(4, GNodeArg(GNA_IN, "S21_Output", 0), GNodeArg(GNA_IN, "Res3a_branch1kernel", 0), GNodeArg(GNA_IN, "Model_1res3a_branch1conv2d_bia", 0), GNodeArg(GNA_OUT, "S27_Output", 0)));
    // Node S30_Conv2d_16x16x3x3_Relu inq 12 weightsq 14 outq 12 biasesq 13
    AddNode("S30_Conv2d_16x16x3x3_Relu", Bindings(4, GNodeArg(GNA_IN, "S24_Output", 0), GNodeArg(GNA_IN, "Res3a_branch2bkernel", 0), GNodeArg(GNA_IN, "Model_1res3a_branch2bconv2d_bi", 0), GNodeArg(GNA_OUT, "S30_Output", 0)));
    // Node ADD_0_11 inq1 12 inq2 11 outq 11
    AddNode("S31_MatAdd_16x20x20", Bindings(3, GNodeArg(GNA_IN, "S30_Output", 0), GNodeArg(GNA_IN, "S27_Output", 0), GNodeArg(GNA_OUT, "S31_Output", 0)));
    // Node S34_Conv2d_16x16x3x3_Relu inq 11 weightsq 15 outq 12 biasesq 15
    AddNode("S34_Conv2d_16x16x3x3_Relu", Bindings(4, GNodeArg(GNA_IN, "S31_Output", 0), GNodeArg(GNA_IN, "Res3bbranch2akernel", 0), GNodeArg(GNA_IN, "Model_1res3bbranch2aconv2d_bia", 0), GNodeArg(GNA_OUT, "S34_Output", 0)));
    // Node S37_Conv2d_16x16x3x3 inq 12 weightsq 14 outq 11 biasesq 13
    AddNode("S37_Conv2d_16x16x3x3", Bindings(4, GNodeArg(GNA_IN, "S34_Output", 0), GNodeArg(GNA_IN, "Res3bbranch2bkernel", 0), GNodeArg(GNA_IN, "Model_1res3bbranch2bconv2d_bia", 0), GNodeArg(GNA_OUT, "S37_Output", 0)));
    // Node ADD_0_14 inq1 11 inq2 11 outq 11
    AddNode("S38_MatAdd_16x20x20", Bindings(3, GNodeArg(GNA_IN, "S37_Output", 0), GNodeArg(GNA_IN, "S31_Output", 0), GNodeArg(GNA_OUT, "S38_Output", 0)));
    // Node S41_Conv2d_32x16x3x3_Relu inq 11 weightsq 15 outq 12 biasesq 14
    AddNode("S41_Conv2d_32x16x3x3_Relu", Bindings(4, GNodeArg(GNA_IN, "S38_Output", 0), GNodeArg(GNA_IN, "Res4a_branch2akernel", 0), GNodeArg(GNA_IN, "Model_1res4a_branch2aconv2d_bi", 0), GNodeArg(GNA_OUT, "S41_Output", 0)));
    // Node S44_Conv2d_32x16x1x1 inq 11 weightsq 15 outq 11 biasesq 14
    AddNode("S44_Conv2d_32x16x1x1", Bindings(4, GNodeArg(GNA_IN, "S38_Output", 0), GNodeArg(GNA_IN, "Res4a_branch1kernel", 0), GNodeArg(GNA_IN, "Model_1res4a_branch1conv2d_bia", 0), GNodeArg(GNA_OUT, "S44_Output", 0)));
    // Node S47_Conv2d_32x32x3x3_Relu inq 12 weightsq 14 outq 12 biasesq 12
    AddNode("S47_Conv2d_32x32x3x3_Relu", Bindings(4, GNodeArg(GNA_IN, "S41_Output", 0), GNodeArg(GNA_IN, "Res4a_branch2bkernel", 0), GNodeArg(GNA_IN, "Model_1res4a_branch2bconv2d_bi", 0), GNodeArg(GNA_OUT, "S47_Output", 0)));
    // Node ADD_0_18 inq1 12 inq2 11 outq 11
    AddNode("S48_MatAdd_32x10x10", Bindings(3, GNodeArg(GNA_IN, "S47_Output", 0), GNodeArg(GNA_IN, "S44_Output", 0), GNodeArg(GNA_OUT, "S48_Output", 0)));
    // Node S51_Conv2d_32x32x3x3_Relu inq 11 weightsq 15 outq 12 biasesq 15
    AddNode("S51_Conv2d_32x32x3x3_Relu", Bindings(4, GNodeArg(GNA_IN, "S48_Output", 0), GNodeArg(GNA_IN, "Res4bbranch2akernel", 0), GNodeArg(GNA_IN, "Model_1res4bbranch2aconv2d_bia", 0), GNodeArg(GNA_OUT, "S51_Output", 0)));
    // Node S54_Conv2d_32x32x3x3 inq 12 weightsq 14 outq 11 biasesq 13
    AddNode("S54_Conv2d_32x32x3x3", Bindings(4, GNodeArg(GNA_IN, "S51_Output", 0), GNodeArg(GNA_IN, "Res4bbranch2bkernel", 0), GNodeArg(GNA_IN, "Model_1res4bbranch2bconv2d_bia", 0), GNodeArg(GNA_OUT, "S54_Output", 0)));
    // Node ADD_0_21 inq1 11 inq2 11 outq 11
    AddNode("S55_MatAdd_32x10x10", Bindings(3, GNodeArg(GNA_IN, "S54_Output", 0), GNodeArg(GNA_IN, "S48_Output", 0), GNodeArg(GNA_OUT, "S55_Output", 0)));
    // Node S58_Conv2d_64x32x3x3_Relu inq 11 weightsq 15 outq 12 biasesq 15
    AddNode("S58_Conv2d_64x32x3x3_Relu", Bindings(4, GNodeArg(GNA_IN, "S55_Output", 0), GNodeArg(GNA_IN, "Res5a_branch2akernel", 0), GNodeArg(GNA_IN, "Model_1res5a_branch2aconv2d_bi", 0), GNodeArg(GNA_OUT, "S58_Output", 0)));
    // Node S61_Conv2d_64x32x1x1 inq 11 weightsq 15 outq 13 biasesq 15
    AddNode("S61_Conv2d_64x32x1x1", Bindings(4, GNodeArg(GNA_IN, "S55_Output", 0), GNodeArg(GNA_IN, "Res5a_branch1kernel", 0), GNodeArg(GNA_IN, "Model_1res5a_branch1conv2d_bia", 0), GNodeArg(GNA_OUT, "S61_Output", 0)));
    // Node S64_Conv2d_64x64x3x3_Relu inq 12 weightsq 14 outq 13 biasesq 13
    AddNode("S64_Conv2d_64x64x3x3_Relu", Bindings(4, GNodeArg(GNA_IN, "S58_Output", 0), GNodeArg(GNA_IN, "Res5a_branch2bkernel", 0), GNodeArg(GNA_IN, "Model_1res5a_branch2bconv2d_bi", 0), GNodeArg(GNA_OUT, "S64_Output", 0)));
    // Node ADD_0_25 inq1 13 inq2 13 outq 12
    AddNode("S65_MatAdd_64x5x5", Bindings(3, GNodeArg(GNA_IN, "S64_Output", 0), GNodeArg(GNA_IN, "S61_Output", 0), GNodeArg(GNA_OUT, "S65_Output", 0)));
    // Node S68_Conv2d_64x64x3x3_Relu inq 12 weightsq 15 outq 13 biasesq 15
    AddNode("S68_Conv2d_64x64x3x3_Relu", Bindings(4, GNodeArg(GNA_IN, "S65_Output", 0), GNodeArg(GNA_IN, "Res5bbranch2akernel", 0), GNodeArg(GNA_IN, "Model_1res5bbranch2aconv2d_bia", 0), GNodeArg(GNA_OUT, "S68_Output", 0)));
    // Node S71_Conv2d_64x64x3x3 inq 13 weightsq 14 outq 12 biasesq 15
    AddNode("S71_Conv2d_64x64x3x3", Bindings(4, GNodeArg(GNA_IN, "S68_Output", 0), GNodeArg(GNA_IN, "Res5bbranch2bkernel", 0), GNodeArg(GNA_IN, "Model_1res5bbranch2bconv2d_bia", 0), GNodeArg(GNA_OUT, "S71_Output", 0)));
    // Node ADD_0_28 inq1 12 inq2 12 outq 12
    AddNode("S72_MatAdd_64x5x5", Bindings(3, GNodeArg(GNA_IN, "S71_Output", 0), GNodeArg(GNA_IN, "S65_Output", 0), GNodeArg(GNA_OUT, "S72_Output", 0)));
    // Node AVERAGE_POOL_2D_0_29 inq Q4.12 outq Q4.12
    AddNode("S73_AveragePool_2x2", Bindings(2, GNodeArg(GNA_IN, "S72_Output", 0), GNodeArg(GNA_OUT, "S73_Output", 0)));
    // Node FULLY_CONNECTED_0_30 inq 12 weightsq 15 outq 12
    AddNode("S76_Linear_7x256", Bindings(4, GNodeArg(GNA_IN, "S73_Output", 0), GNodeArg(GNA_IN, "Weightedaveragekerneltranspose", 0), GNodeArg(GNA_IN, "M2weightedaveragematmul_bias", 0), GNodeArg(GNA_OUT, "S76_Output", 0)));
    // Node SOFTMAX_0_31 inq 12 outq 15
    AddNode("S77_SoftMax", Bindings(2, GNodeArg(GNA_IN, "S76_Output", 0), GNodeArg(GNA_OUT, "Output_1", 0)));
    CloseGraph();
#endif
}

int main(int argc, char **argv)

{
    if (TilerParseOptions(argc, argv)) {
            printf("Failed to initialize or incorrect output arguments directory.\n"); return 1;
    }
    resnetModel(64000, 300000, 8000000, 20*1024*1024);
    GenerateTilingCode();
    return 0;
}
