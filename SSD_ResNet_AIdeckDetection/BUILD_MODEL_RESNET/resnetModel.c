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


    
    // generator for DEPTHWISE_CONV_2D_0_1_fusion
    CNN_ConvolutionPoolReLU("S4_Conv2d_8x1x7x7_MaxPool_3x3_Relu", 0,
                            2, 2, 2, 2,
                            15, 11, 13, 12,
                            1, 1, 1, 1, 1, 8, 160, 160,
                            KOP_CONV_DP, 7, 7, 1, 1, 2, 2, 1,
                            KOP_MAXPOOL, 3, 3, 1, 1, 2, 2, 0,
                            KOP_RELU);
    
    
    // generator for CONV_2D_0_3_fusion
    CNN_ConvolutionPoolReLU("S7_Conv2d_8x8x3x3_Relu", 0,
                            2, 2, 2, 2,
                            12, 15, 12, 13,
                            1, 1, 1, 1, 8, 8, 39, 39,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_RELU);
    
    
    // generator for CONV_2D_0_4
    CNN_ConvolutionPoolReLU("S10_Conv2d_8x8x3x3", 0,
                            2, 2, 2, 2,
                            13, 15, 13, 12,
                            1, 1, 1, 1, 8, 8, 39, 39,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_NONE);
    
    
    // generator for ADD_0_5
    CNN_MatAddDynAdjust("S11_MatAdd_8x39x39", 0, 2, 2, 2,
                        12, 12, 11, 1, 1, 1, 
                        8, 8, 
                        39, 39, KOP_MATADD_DYNADJUST);
    
    
    // generator for CONV_2D_0_6_fusion
    CNN_ConvolutionPoolReLU("S14_Conv2d_8x8x3x3_Relu", 0,
                            2, 2, 2, 2,
                            11, 15, 14, 12,
                            1, 1, 1, 1, 8, 8, 39, 39,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_RELU);
    
    
    // generator for CONV_2D_0_7
    CNN_ConvolutionPoolReLU("S17_Conv2d_8x8x3x3", 0,
                            2, 2, 2, 2,
                            12, 15, 14, 12,
                            1, 1, 1, 1, 8, 8, 39, 39,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_NONE);
    
    
    // generator for ADD_0_8
    CNN_MatAddDynAdjust("S18_MatAdd_8x39x39", 0, 2, 2, 2,
                        12, 11, 11, 1, 1, 1, 
                        8, 8, 
                        39, 39, KOP_MATADD_DYNADJUST);
    
    
    // generator for CONV_2D_0_9_fusion
    CNN_ConvolutionPoolReLU("S21_Conv2d_16x8x3x3_Relu", 0,
                            2, 2, 2, 2,
                            11, 15, 14, 12,
                            1, 1, 1, 1, 8, 16, 39, 39,
                            KOP_CONV_DP, 3, 3, 1, 1, 2, 2, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_RELU);
    
    
    // generator for CONV_2D_0_10
    CNN_ConvolutionPoolReLU("S24_Conv2d_16x8x1x1", 0,
                            2, 2, 2, 2,
                            11, 14, 13, 11,
                            1, 1, 1, 1, 8, 16, 39, 39,
                            KOP_CONV_DP, 1, 1, 1, 1, 2, 2, 0,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_NONE);
    
    
    // generator for CONV_2D_0_11_fusion
    CNN_ConvolutionPoolReLU("S27_Conv2d_16x16x3x3_Relu", 0,
                            2, 2, 2, 2,
                            12, 15, 12, 12,
                            1, 1, 1, 1, 16, 16, 20, 20,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_RELU);
    
    
    // generator for ADD_0_12
    CNN_MatAddDynAdjust("S28_MatAdd_16x20x20", 0, 2, 2, 2,
                        12, 11, 11, 1, 1, 1, 
                        16, 16, 
                        20, 20, KOP_MATADD_DYNADJUST);
    
    
    // generator for CONV_2D_0_13_fusion
    CNN_ConvolutionPoolReLU("S31_Conv2d_16x16x3x3_Relu", 0,
                            2, 2, 2, 2,
                            11, 15, 14, 13,
                            1, 1, 1, 1, 16, 16, 20, 20,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_RELU);
    
    
    // generator for CONV_2D_0_14
    CNN_ConvolutionPoolReLU("S34_Conv2d_16x16x3x3", 0,
                            2, 2, 2, 2,
                            13, 14, 13, 11,
                            1, 1, 1, 1, 16, 16, 20, 20,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_NONE);
    
    // generator for ADD_0_15
    CNN_MatAdd("S35_MatAdd_16x20x20", 0, 2, 2, 2, 11, 11, 11, 1, 1, 1, 16, 16, 20, 20, KOP_MATADD);
    CNN_GenControl_T gen_ctrl_S38_Conv2d_32x16x3x3_Relu;
    CNN_InitGenCtrl(&gen_ctrl_S38_Conv2d_32x16x3x3_Relu);
    CNN_SetGenCtrl(&gen_ctrl_S38_Conv2d_32x16x3x3_Relu, "PADTYPE", AT_OPT_VAL(1));
    
    // generator for CONV_2D_0_16_fusion
    CNN_ConvolutionPoolReLU("S38_Conv2d_32x16x3x3_Relu", &gen_ctrl_S38_Conv2d_32x16x3x3_Relu,
                            2, 2, 2, 2,
                            11, 15, 14, 12,
                            1, 1, 1, 1, 16, 32, 20, 20,
                            KOP_CONV_DP, 3, 3, 1, 1, 2, 2, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_RELU);
    
    
    // generator for CONV_2D_0_17
    CNN_ConvolutionPoolReLU("S41_Conv2d_32x16x1x1", 0,
                            2, 2, 2, 2,
                            11, 15, 14, 11,
                            1, 1, 1, 1, 16, 32, 20, 20,
                            KOP_CONV_DP, 1, 1, 1, 1, 2, 2, 0,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_NONE);
    
    
    // generator for CONV_2D_0_18_fusion
    CNN_ConvolutionPoolReLU("S44_Conv2d_32x32x3x3_Relu", 0,
                            2, 2, 2, 2,
                            12, 15, 12, 12,
                            1, 1, 1, 1, 32, 32, 10, 10,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_RELU);
    
    
    // generator for ADD_0_19
    CNN_MatAddDynAdjust("S45_MatAdd_32x10x10", 0, 2, 2, 2,
                        12, 11, 11, 1, 1, 1, 
                        32, 32, 
                        10, 10, KOP_MATADD_DYNADJUST);
    
    
    // generator for CONV_2D_0_20_fusion
    CNN_ConvolutionPoolReLU("S48_Conv2d_32x32x3x3_Relu", 0,
                            2, 2, 2, 2,
                            11, 15, 14, 13,
                            1, 1, 1, 1, 32, 32, 10, 10,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_RELU);
    
    
    // generator for CONV_2D_0_21
    CNN_ConvolutionPoolReLU("S51_Conv2d_32x32x3x3", 0,
                            2, 2, 2, 2,
                            13, 15, 14, 12,
                            1, 1, 1, 1, 32, 32, 10, 10,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_NONE);
    
    
    // generator for ADD_0_22
    CNN_MatAddDynAdjust("S52_MatAdd_32x10x10", 0, 2, 2, 2,
                        12, 11, 11, 1, 1, 1, 
                        32, 32, 
                        10, 10, KOP_MATADD_DYNADJUST);
    
    CNN_GenControl_T gen_ctrl_S55_Conv2d_64x32x3x3_Relu;
    CNN_InitGenCtrl(&gen_ctrl_S55_Conv2d_64x32x3x3_Relu);
    CNN_SetGenCtrl(&gen_ctrl_S55_Conv2d_64x32x3x3_Relu, "PADTYPE", AT_OPT_VAL(1));
    
    // generator for CONV_2D_0_23_fusion
    CNN_ConvolutionPoolReLU("S55_Conv2d_64x32x3x3_Relu", &gen_ctrl_S55_Conv2d_64x32x3x3_Relu,
                            2, 2, 2, 2,
                            11, 15, 14, 13,
                            1, 1, 1, 1, 32, 64, 10, 10,
                            KOP_CONV_DP, 3, 3, 1, 1, 2, 2, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_RELU);
    
    
    // generator for CONV_2D_0_24
    CNN_ConvolutionPoolReLU("S58_Conv2d_64x32x1x1", 0,
                            2, 2, 2, 2,
                            11, 15, 15, 13,
                            1, 1, 1, 1, 32, 64, 10, 10,
                            KOP_CONV_DP, 1, 1, 1, 1, 2, 2, 0,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_NONE);
    
    
    // generator for CONV_2D_0_25_fusion
    CNN_ConvolutionPoolReLU("S61_Conv2d_64x64x3x3_Relu", 0,
                            2, 2, 2, 2,
                            13, 14, 13, 12,
                            1, 1, 1, 1, 64, 64, 5, 5,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_RELU);
    
    
    // generator for ADD_0_26
    CNN_MatAddDynAdjust("S62_MatAdd_64x5x5", 0, 2, 2, 2,
                        12, 13, 12, 1, 1, 1, 
                        64, 64, 
                        5, 5, KOP_MATADD_DYNADJUST);
    
    
    // generator for CONV_2D_0_27_fusion
    CNN_ConvolutionPoolReLU("S65_Conv2d_64x64x3x3_Relu", 0,
                            2, 2, 2, 2,
                            12, 15, 14, 13,
                            1, 1, 1, 1, 64, 64, 5, 5,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_RELU);
    
    
    // generator for CONV_2D_0_28
    CNN_ConvolutionPoolReLU("S68_Conv2d_64x64x3x3", 0,
                            2, 2, 2, 2,
                            13, 15, 14, 13,
                            1, 1, 1, 1, 64, 64, 5, 5,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_NONE);
    
    
    // generator for ADD_0_29
    CNN_MatAddDynAdjust("S69_MatAdd_64x5x5", 0, 2, 2, 2,
                        13, 12, 11, 1, 1, 1, 
                        64, 64, 
                        5, 5, KOP_MATADD_DYNADJUST);
    
    
    // generator for AVERAGE_POOL_2D_0_30
    CNN_PoolReLU("S70_AveragePool_2x2", 0,
                  2, 2,
                  11, 11,
                  1, 1, 64, 64, 5, 5,
                  KOP_AVGPOOL, 2, 2, 1, 1, 2, 2, 0,
                  KOP_NONE);
    
    
    // generator for FULLY_CONNECTED_0_31
    CNN_LinearReLU("S73_Linear_7x64x2x2", 0, 2, 2,
                    2, 2, 11, 15, 15,
                    12, 1, 1, 1, 1, 256, 7, KOP_LINEAR, KOP_NONE);
    
    // generator for SOFTMAX_0_32
    CNN_SoftMax("S74_SoftMax", 0, 2, 2, 12, 15, 1, 1, 7, KOP_SOFTMAX);

#define GRAPH
#ifdef GRAPH
    CreateGraph("resnetCNN",
        /* Arguments either passed or globals */
            CArgs(44,
                TCArgInfo("signed short * __restrict__", "Input_1", ARG_SCOPE_ARG, ARG_DIR_IN, AT_MEM_L2, AT_MEM_L2, 0),
                TCArgInfo("signed short * __restrict__", "Conv1kernel", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Conv1kernel.tensor", 1, 1, 16, 11)),
                TCArgInfo("signed short * __restrict__", "Model_1conv1conv2d_bias", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Model_1conv1conv2d_bias.tensor", 1, 1, 16, 13)),
                TCArgInfo("signed short * __restrict__", "Res2bbranch2akernel", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Res2bbranch2akernel.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Model_1res2bbranch2aconv2d_bia", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Model_1res2bbranch2aconv2d_bia.tensor", 1, 1, 16, 12)),
                TCArgInfo("signed short * __restrict__", "Res2bbranch2bkernel", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Res2bbranch2bkernel.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Model_1res2bbranch2bconv2d_bia", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Model_1res2bbranch2bconv2d_bia.tensor", 1, 1, 16, 13)),
                TCArgInfo("signed short * __restrict__", "Res2cbranch2akernel", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Res2cbranch2akernel.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Model_1res2cbranch2aconv2d_bia", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Model_1res2cbranch2aconv2d_bia.tensor", 1, 1, 16, 14)),
                TCArgInfo("signed short * __restrict__", "Res2cbranch2bkernel", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Res2cbranch2bkernel.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Model_1res2cbranch2bconv2d_bia", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Model_1res2cbranch2bconv2d_bia.tensor", 1, 1, 16, 14)),
                TCArgInfo("signed short * __restrict__", "Res3a_branch2akernel", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Res3a_branch2akernel.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Model_1res3a_branch2aconv2d_bi", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Model_1res3a_branch2aconv2d_bi.tensor", 1, 1, 16, 14)),
                TCArgInfo("signed short * __restrict__", "Res3a_branch1kernel", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Res3a_branch1kernel.tensor", 1, 1, 16, 14)),
                TCArgInfo("signed short * __restrict__", "Model_1res3a_branch1conv2d_bia", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Model_1res3a_branch1conv2d_bia.tensor", 1, 1, 16, 13)),
                TCArgInfo("signed short * __restrict__", "Res3a_branch2bkernel", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Res3a_branch2bkernel.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Model_1res3a_branch2bconv2d_bi", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Model_1res3a_branch2bconv2d_bi.tensor", 1, 1, 16, 12)),
                TCArgInfo("signed short * __restrict__", "Res3bbranch2akernel", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Res3bbranch2akernel.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Model_1res3bbranch2aconv2d_bia", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Model_1res3bbranch2aconv2d_bia.tensor", 1, 1, 16, 14)),
                TCArgInfo("signed short * __restrict__", "Res3bbranch2bkernel", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Res3bbranch2bkernel.tensor", 1, 1, 16, 14)),
                TCArgInfo("signed short * __restrict__", "Model_1res3bbranch2bconv2d_bia", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Model_1res3bbranch2bconv2d_bia.tensor", 1, 1, 16, 13)),
                TCArgInfo("signed short * __restrict__", "Res4a_branch2akernel", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Res4a_branch2akernel.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Model_1res4a_branch2aconv2d_bi", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Model_1res4a_branch2aconv2d_bi.tensor", 1, 1, 16, 14)),
                TCArgInfo("signed short * __restrict__", "Res4a_branch1kernel", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Res4a_branch1kernel.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Model_1res4a_branch1conv2d_bia", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Model_1res4a_branch1conv2d_bia.tensor", 1, 1, 16, 14)),
                TCArgInfo("signed short * __restrict__", "Res4a_branch2bkernel", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Res4a_branch2bkernel.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Model_1res4a_branch2bconv2d_bi", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Model_1res4a_branch2bconv2d_bi.tensor", 1, 1, 16, 12)),
                TCArgInfo("signed short * __restrict__", "Res4bbranch2akernel", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Res4bbranch2akernel.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Model_1res4bbranch2aconv2d_bia", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Model_1res4bbranch2aconv2d_bia.tensor", 1, 1, 16, 14)),
                TCArgInfo("signed short * __restrict__", "Res4bbranch2bkernel", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Res4bbranch2bkernel.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Model_1res4bbranch2bconv2d_bia", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Model_1res4bbranch2bconv2d_bia.tensor", 1, 1, 16, 14)),
                TCArgInfo("signed short * __restrict__", "Res5a_branch2akernel", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Res5a_branch2akernel.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Model_1res5a_branch2aconv2d_bi", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Model_1res5a_branch2aconv2d_bi.tensor", 1, 1, 16, 14)),
                TCArgInfo("signed short * __restrict__", "Res5a_branch1kernel", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Res5a_branch1kernel.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Model_1res5a_branch1conv2d_bia", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Model_1res5a_branch1conv2d_bia.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Res5a_branch2bkernel", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Res5a_branch2bkernel.tensor", 1, 1, 16, 14)),
                TCArgInfo("signed short * __restrict__", "Model_1res5a_branch2bconv2d_bi", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Model_1res5a_branch2bconv2d_bi.tensor", 1, 1, 16, 13)),
                TCArgInfo("signed short * __restrict__", "Res5bbranch2akernel", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Res5bbranch2akernel.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Model_1res5bbranch2aconv2d_bia", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Model_1res5bbranch2aconv2d_bia.tensor", 1, 1, 16, 14)),
                TCArgInfo("signed short * __restrict__", "Res5bbranch2bkernel", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Res5bbranch2bkernel.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Model_1res5bbranch2bconv2d_bia", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Model_1res5bbranch2bconv2d_bia.tensor", 1, 1, 16, 14)),
                TCArgInfo("signed short * __restrict__", "Weightedaveragekerneltranspose", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/Weightedaveragekerneltranspose.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "M2weightedaveragematmul_bias", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_RESNET/tensors/M2weightedaveragematmul_bias.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Output_1", ARG_SCOPE_ARG, ARG_DIR_OUT, AT_MEM_L2, AT_MEM_L2, 0)
            ),
        /* Locals, allocated dynamically */
        CArgs(30,
            TCArgInfo("signed short * __restrict__", "S4_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S7_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S10_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S11_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S14_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S17_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S18_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S21_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S24_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S27_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S28_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S31_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S34_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S35_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S38_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S41_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S44_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S45_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S48_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S51_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S52_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S55_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S58_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S61_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S62_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S65_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S68_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S69_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S70_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S73_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0)
        )
    );

    /* Stacked tensors - Concats */
    // no concats in graph so not stacked tensors created

    // Node S4_Conv2d_8x1x7x7_MaxPool_3x3_Relu inq 15 weightsq 11 outq 12 biasesq 13
    AddNode("S4_Conv2d_8x1x7x7_MaxPool_3x3_Relu", Bindings(4, GNodeArg(GNA_IN, "Input_1", 0), GNodeArg(GNA_IN, "Conv1kernel", 0), GNodeArg(GNA_IN, "Model_1conv1conv2d_bias", 0), GNodeArg(GNA_OUT, "S4_Output", 0)));
    // Node S7_Conv2d_8x8x3x3_Relu inq 12 weightsq 15 outq 13 biasesq 12
    AddNode("S7_Conv2d_8x8x3x3_Relu", Bindings(4, GNodeArg(GNA_IN, "S4_Output", 0), GNodeArg(GNA_IN, "Res2bbranch2akernel", 0), GNodeArg(GNA_IN, "Model_1res2bbranch2aconv2d_bia", 0), GNodeArg(GNA_OUT, "S7_Output", 0)));
    // Node S10_Conv2d_8x8x3x3 inq 13 weightsq 15 outq 12 biasesq 13
    AddNode("S10_Conv2d_8x8x3x3", Bindings(4, GNodeArg(GNA_IN, "S7_Output", 0), GNodeArg(GNA_IN, "Res2bbranch2bkernel", 0), GNodeArg(GNA_IN, "Model_1res2bbranch2bconv2d_bia", 0), GNodeArg(GNA_OUT, "S10_Output", 0)));
    // Node ADD_0_5 inq1 12 inq2 12 outq 11
    AddNode("S11_MatAdd_8x39x39", Bindings(3, GNodeArg(GNA_IN, "S10_Output", 0), GNodeArg(GNA_IN, "S4_Output", 0), GNodeArg(GNA_OUT, "S11_Output", 0)));
    // Node S14_Conv2d_8x8x3x3_Relu inq 11 weightsq 15 outq 12 biasesq 14
    AddNode("S14_Conv2d_8x8x3x3_Relu", Bindings(4, GNodeArg(GNA_IN, "S11_Output", 0), GNodeArg(GNA_IN, "Res2cbranch2akernel", 0), GNodeArg(GNA_IN, "Model_1res2cbranch2aconv2d_bia", 0), GNodeArg(GNA_OUT, "S14_Output", 0)));
    // Node S17_Conv2d_8x8x3x3 inq 12 weightsq 15 outq 12 biasesq 14
    AddNode("S17_Conv2d_8x8x3x3", Bindings(4, GNodeArg(GNA_IN, "S14_Output", 0), GNodeArg(GNA_IN, "Res2cbranch2bkernel", 0), GNodeArg(GNA_IN, "Model_1res2cbranch2bconv2d_bia", 0), GNodeArg(GNA_OUT, "S17_Output", 0)));
    // Node ADD_0_8 inq1 12 inq2 11 outq 11
    AddNode("S18_MatAdd_8x39x39", Bindings(3, GNodeArg(GNA_IN, "S17_Output", 0), GNodeArg(GNA_IN, "S11_Output", 0), GNodeArg(GNA_OUT, "S18_Output", 0)));
    // Node S21_Conv2d_16x8x3x3_Relu inq 11 weightsq 15 outq 12 biasesq 14
    AddNode("S21_Conv2d_16x8x3x3_Relu", Bindings(4, GNodeArg(GNA_IN, "S18_Output", 0), GNodeArg(GNA_IN, "Res3a_branch2akernel", 0), GNodeArg(GNA_IN, "Model_1res3a_branch2aconv2d_bi", 0), GNodeArg(GNA_OUT, "S21_Output", 0)));
    // Node S24_Conv2d_16x8x1x1 inq 11 weightsq 14 outq 11 biasesq 13
    AddNode("S24_Conv2d_16x8x1x1", Bindings(4, GNodeArg(GNA_IN, "S18_Output", 0), GNodeArg(GNA_IN, "Res3a_branch1kernel", 0), GNodeArg(GNA_IN, "Model_1res3a_branch1conv2d_bia", 0), GNodeArg(GNA_OUT, "S24_Output", 0)));
    // Node S27_Conv2d_16x16x3x3_Relu inq 12 weightsq 15 outq 12 biasesq 12
    AddNode("S27_Conv2d_16x16x3x3_Relu", Bindings(4, GNodeArg(GNA_IN, "S21_Output", 0), GNodeArg(GNA_IN, "Res3a_branch2bkernel", 0), GNodeArg(GNA_IN, "Model_1res3a_branch2bconv2d_bi", 0), GNodeArg(GNA_OUT, "S27_Output", 0)));
    // Node ADD_0_12 inq1 12 inq2 11 outq 11
    AddNode("S28_MatAdd_16x20x20", Bindings(3, GNodeArg(GNA_IN, "S27_Output", 0), GNodeArg(GNA_IN, "S24_Output", 0), GNodeArg(GNA_OUT, "S28_Output", 0)));
    // Node S31_Conv2d_16x16x3x3_Relu inq 11 weightsq 15 outq 13 biasesq 14
    AddNode("S31_Conv2d_16x16x3x3_Relu", Bindings(4, GNodeArg(GNA_IN, "S28_Output", 0), GNodeArg(GNA_IN, "Res3bbranch2akernel", 0), GNodeArg(GNA_IN, "Model_1res3bbranch2aconv2d_bia", 0), GNodeArg(GNA_OUT, "S31_Output", 0)));
    // Node S34_Conv2d_16x16x3x3 inq 13 weightsq 14 outq 11 biasesq 13
    AddNode("S34_Conv2d_16x16x3x3", Bindings(4, GNodeArg(GNA_IN, "S31_Output", 0), GNodeArg(GNA_IN, "Res3bbranch2bkernel", 0), GNodeArg(GNA_IN, "Model_1res3bbranch2bconv2d_bia", 0), GNodeArg(GNA_OUT, "S34_Output", 0)));
    // Node ADD_0_15 inq1 11 inq2 11 outq 11
    AddNode("S35_MatAdd_16x20x20", Bindings(3, GNodeArg(GNA_IN, "S34_Output", 0), GNodeArg(GNA_IN, "S28_Output", 0), GNodeArg(GNA_OUT, "S35_Output", 0)));
    // Node S38_Conv2d_32x16x3x3_Relu inq 11 weightsq 15 outq 12 biasesq 14
    AddNode("S38_Conv2d_32x16x3x3_Relu", Bindings(4, GNodeArg(GNA_IN, "S35_Output", 0), GNodeArg(GNA_IN, "Res4a_branch2akernel", 0), GNodeArg(GNA_IN, "Model_1res4a_branch2aconv2d_bi", 0), GNodeArg(GNA_OUT, "S38_Output", 0)));
    // Node S41_Conv2d_32x16x1x1 inq 11 weightsq 15 outq 11 biasesq 14
    AddNode("S41_Conv2d_32x16x1x1", Bindings(4, GNodeArg(GNA_IN, "S35_Output", 0), GNodeArg(GNA_IN, "Res4a_branch1kernel", 0), GNodeArg(GNA_IN, "Model_1res4a_branch1conv2d_bia", 0), GNodeArg(GNA_OUT, "S41_Output", 0)));
    // Node S44_Conv2d_32x32x3x3_Relu inq 12 weightsq 15 outq 12 biasesq 12
    AddNode("S44_Conv2d_32x32x3x3_Relu", Bindings(4, GNodeArg(GNA_IN, "S38_Output", 0), GNodeArg(GNA_IN, "Res4a_branch2bkernel", 0), GNodeArg(GNA_IN, "Model_1res4a_branch2bconv2d_bi", 0), GNodeArg(GNA_OUT, "S44_Output", 0)));
    // Node ADD_0_19 inq1 12 inq2 11 outq 11
    AddNode("S45_MatAdd_32x10x10", Bindings(3, GNodeArg(GNA_IN, "S44_Output", 0), GNodeArg(GNA_IN, "S41_Output", 0), GNodeArg(GNA_OUT, "S45_Output", 0)));
    // Node S48_Conv2d_32x32x3x3_Relu inq 11 weightsq 15 outq 13 biasesq 14
    AddNode("S48_Conv2d_32x32x3x3_Relu", Bindings(4, GNodeArg(GNA_IN, "S45_Output", 0), GNodeArg(GNA_IN, "Res4bbranch2akernel", 0), GNodeArg(GNA_IN, "Model_1res4bbranch2aconv2d_bia", 0), GNodeArg(GNA_OUT, "S48_Output", 0)));
    // Node S51_Conv2d_32x32x3x3 inq 13 weightsq 15 outq 12 biasesq 14
    AddNode("S51_Conv2d_32x32x3x3", Bindings(4, GNodeArg(GNA_IN, "S48_Output", 0), GNodeArg(GNA_IN, "Res4bbranch2bkernel", 0), GNodeArg(GNA_IN, "Model_1res4bbranch2bconv2d_bia", 0), GNodeArg(GNA_OUT, "S51_Output", 0)));
    // Node ADD_0_22 inq1 12 inq2 11 outq 11
    AddNode("S52_MatAdd_32x10x10", Bindings(3, GNodeArg(GNA_IN, "S51_Output", 0), GNodeArg(GNA_IN, "S45_Output", 0), GNodeArg(GNA_OUT, "S52_Output", 0)));
    // Node S55_Conv2d_64x32x3x3_Relu inq 11 weightsq 15 outq 13 biasesq 14
    AddNode("S55_Conv2d_64x32x3x3_Relu", Bindings(4, GNodeArg(GNA_IN, "S52_Output", 0), GNodeArg(GNA_IN, "Res5a_branch2akernel", 0), GNodeArg(GNA_IN, "Model_1res5a_branch2aconv2d_bi", 0), GNodeArg(GNA_OUT, "S55_Output", 0)));
    // Node S58_Conv2d_64x32x1x1 inq 11 weightsq 15 outq 13 biasesq 15
    AddNode("S58_Conv2d_64x32x1x1", Bindings(4, GNodeArg(GNA_IN, "S52_Output", 0), GNodeArg(GNA_IN, "Res5a_branch1kernel", 0), GNodeArg(GNA_IN, "Model_1res5a_branch1conv2d_bia", 0), GNodeArg(GNA_OUT, "S58_Output", 0)));
    // Node S61_Conv2d_64x64x3x3_Relu inq 13 weightsq 14 outq 12 biasesq 13
    AddNode("S61_Conv2d_64x64x3x3_Relu", Bindings(4, GNodeArg(GNA_IN, "S55_Output", 0), GNodeArg(GNA_IN, "Res5a_branch2bkernel", 0), GNodeArg(GNA_IN, "Model_1res5a_branch2bconv2d_bi", 0), GNodeArg(GNA_OUT, "S61_Output", 0)));
    // Node ADD_0_26 inq1 12 inq2 13 outq 12
    AddNode("S62_MatAdd_64x5x5", Bindings(3, GNodeArg(GNA_IN, "S61_Output", 0), GNodeArg(GNA_IN, "S58_Output", 0), GNodeArg(GNA_OUT, "S62_Output", 0)));
    // Node S65_Conv2d_64x64x3x3_Relu inq 12 weightsq 15 outq 13 biasesq 14
    AddNode("S65_Conv2d_64x64x3x3_Relu", Bindings(4, GNodeArg(GNA_IN, "S62_Output", 0), GNodeArg(GNA_IN, "Res5bbranch2akernel", 0), GNodeArg(GNA_IN, "Model_1res5bbranch2aconv2d_bia", 0), GNodeArg(GNA_OUT, "S65_Output", 0)));
    // Node S68_Conv2d_64x64x3x3 inq 13 weightsq 15 outq 13 biasesq 14
    AddNode("S68_Conv2d_64x64x3x3", Bindings(4, GNodeArg(GNA_IN, "S65_Output", 0), GNodeArg(GNA_IN, "Res5bbranch2bkernel", 0), GNodeArg(GNA_IN, "Model_1res5bbranch2bconv2d_bia", 0), GNodeArg(GNA_OUT, "S68_Output", 0)));
    // Node ADD_0_29 inq1 13 inq2 12 outq 11
    AddNode("S69_MatAdd_64x5x5", Bindings(3, GNodeArg(GNA_IN, "S68_Output", 0), GNodeArg(GNA_IN, "S62_Output", 0), GNodeArg(GNA_OUT, "S69_Output", 0)));
    // Node AVERAGE_POOL_2D_0_30 inq Q5.11 outq Q5.11
    AddNode("S70_AveragePool_2x2", Bindings(2, GNodeArg(GNA_IN, "S69_Output", 0), GNodeArg(GNA_OUT, "S70_Output", 0)));
    // Node FULLY_CONNECTED_0_31 inq 11 weightsq 15 outq 12
    AddNode("S73_Linear_7x64x2x2", Bindings(4, GNodeArg(GNA_IN, "S70_Output", 0), GNodeArg(GNA_IN, "Weightedaveragekerneltranspose", 0), GNodeArg(GNA_IN, "M2weightedaveragematmul_bias", 0), GNodeArg(GNA_OUT, "S73_Output", 0)));
    // Node SOFTMAX_0_32 inq 12 outq 15
    AddNode("S74_SoftMax", Bindings(2, GNodeArg(GNA_IN, "S73_Output", 0), GNodeArg(GNA_OUT, "Output_1", 0)));
    CloseGraph();
#endif
}

int main(int argc, char **argv)

{
    if (TilerParseOptions(argc, argv)) {
            printf("Failed to initialize or incorrect output arguments directory.\n"); return 1;
    }
    resnetModel(52000, 300*1024, 8*1024*1024, 20*1024*1024);
    GenerateTilingCode();
    return 0;
}
