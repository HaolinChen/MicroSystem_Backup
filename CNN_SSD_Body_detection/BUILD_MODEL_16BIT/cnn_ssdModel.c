#include <stdint.h>
#include <stdio.h>
#include "AutoTilerLib.h"
#include "CNN_Generators.h"

#include "CNN_Copy_Generators.h"





void cnn_ssdModel(unsigned int L1Memory, unsigned int L2Memory, unsigned int L3Memory, unsigned int L3Flash)
{
    KernelOper_T Cop = KOP_CONV;

    // SetKernelOpts(KER_OPT_NONE, KER_OPT_BUFFER_PROMOTE);
    SetSymbolDynamics();

    SetUsedFilesNames(0, 2, "CNN_BasicKernels.h", "cnn_ssd.h");
    SetGeneratedFilesNames("cnn_ssdKernels.c", "cnn_ssdKernels.h");
    AT_SetGraphCtrl(AT_GRAPH_MONITOR_CYCLES, AT_OPT_ON);
    AT_SetGraphCtrl(AT_GRAPH_PRODUCE_NODE_NAMES, AT_OPT_ON);
    AT_SetGraphCtrl(AT_GRAPH_PRODUCE_OPERINFOS, AT_OPT_ON);
    AT_SetGraphCtrl(AT_GRAPH_CONST_EXEC_FROM_FLASH, AT_OPT_ON);

    SetMemoryDeviceInfos(4,
        AT_MEM_L1, L1Memory, "cnn_ssd_L1_Memory", 0, 0,
        AT_MEM_L2, L2Memory, "cnn_ssd_L2_Memory", 0, 0,
        AT_MEM_L3_HRAM, L3Memory, "cnn_ssd_L3_Memory", 0, 1,
        AT_MEM_L3_HFLASH, L3Flash, "cnn_ssd_L3_Flash", "cnn_ssd_L3_Flash_Const.dat", 0
    );

    LoadCNNLibrary();


    
    // generator for Conv_0_fusion
    CNN_ConvolutionPoolReLU("S3_Conv2d_8x1x3x3_MaxPool_2x2_Relu", 0,
                            2, 2, 2, 2,
                            15, 11, 14, 11,
                            1, 1, 1, 1, 1, 8, 160, 128,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_MAXPOOL, 2, 2, 1, 1, 2, 2, 0,
                            KOP_RELU);
    
    
    // generator for Conv_3_fusion
    CNN_ConvolutionPoolReLU("S6_Conv2d_16x8x3x3_MaxPool_2x2_Relu", 0,
                            2, 2, 2, 2,
                            11, 14, 15, 12,
                            1, 1, 1, 1, 8, 16, 80, 64,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_MAXPOOL, 2, 2, 1, 1, 2, 2, 0,
                            KOP_RELU);
    
    
    // generator for Conv_6_fusion
    CNN_ConvolutionPoolReLU("S9_Conv2d_16x16x3x3_MaxPool_2x2_Relu", 0,
                            2, 2, 2, 2,
                            12, 14, 13, 12,
                            1, 1, 1, 1, 16, 16, 40, 32,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_MAXPOOL, 2, 2, 1, 1, 2, 2, 0,
                            KOP_RELU);
    
    
    // generator for Conv_9_fusion
    CNN_ConvolutionPoolReLU("S12_Conv2d_32x16x3x3_Relu", 0,
                            2, 2, 2, 2,
                            12, 14, 13, 12,
                            1, 1, 1, 1, 16, 32, 20, 16,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_RELU);
    
    
    // generator for MaxPool_13
    CNN_PoolReLU("S13_MaxPool_2x2", 0,
                  2, 2,
                  12, 12,
                  1, 1, 32, 32, 20, 16,
                  KOP_MAXPOOL, 2, 2, 1, 1, 2, 2, 0,
                  KOP_NONE);
    
    
    // generator for Conv_11
    CNN_ConvolutionPoolReLU("S16_Conv2d_18x32x3x3", 0,
                            2, 2, 2, 2,
                            12, 15, 15, 11,
                            1, 1, 1, 1, 32, 18, 20, 16,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_NONE);
    
    
    // generator for Conv_12
    CNN_ConvolutionPoolReLU("S20_Conv2d_24x32x3x3", 0,
                            2, 2, 2, 2,
                            12, 15, 15, 11,
                            1, 1, 1, 1, 32, 24, 20, 16,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_NONE);
    
    
    // generator for Conv_14_fusion
    CNN_ConvolutionPoolReLU("S24_Conv2d_64x32x3x3_Relu", 0,
                            2, 2, 2, 2,
                            12, 15, 13, 13,
                            1, 1, 1, 1, 32, 64, 10, 8,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_RELU);
    
    
    // generator for MaxPool_18
    CNN_PoolReLU("S25_MaxPool_2x2", 0,
                  2, 2,
                  13, 13,
                  1, 1, 64, 64, 10, 8,
                  KOP_MAXPOOL, 2, 2, 1, 1, 2, 2, 0,
                  KOP_NONE);
    
    
    // generator for Conv_16
    CNN_ConvolutionPoolReLU("S28_Conv2d_18x64x3x3", 0,
                            2, 2, 2, 2,
                            13, 14, 15, 11,
                            1, 1, 1, 1, 64, 18, 10, 8,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_NONE);
    
    
    // generator for Conv_17
    CNN_ConvolutionPoolReLU("S32_Conv2d_24x64x3x3", 0,
                            2, 2, 2, 2,
                            13, 15, 15, 12,
                            1, 1, 1, 1, 64, 24, 10, 8,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_NONE);
    
    
    // generator for Conv_19_fusion
    CNN_ConvolutionPoolReLU("S36_Conv2d_128x64x3x3_Relu", 0,
                            2, 2, 2, 2,
                            13, 15, 13, 13,
                            1, 1, 1, 1, 64, 128, 5, 4,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_RELU);
    
    
    // generator for MaxPool_23
    CNN_PoolReLU("S37_MaxPool_2x2", 0,
                  2, 2,
                  13, 13,
                  1, 1, 128, 128, 5, 4,
                  KOP_MAXPOOL, 2, 2, 1, 1, 2, 2, 0,
                  KOP_NONE);
    
    
    // generator for Conv_21
    CNN_ConvolutionPoolReLU("S40_Conv2d_18x128x3x3", 0,
                            2, 2, 2, 2,
                            13, 14, 15, 11,
                            1, 1, 1, 1, 128, 18, 5, 4,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_NONE);
    
    
    // generator for Conv_22
    CNN_ConvolutionPoolReLU("S44_Conv2d_24x128x3x3", 0,
                            2, 2, 2, 2,
                            13, 15, 15, 12,
                            1, 1, 1, 1, 128, 24, 5, 4,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_NONE);
    
    
    // generator for Conv_24_fusion
    CNN_ConvolutionPoolReLU("S48_Conv2d_128x128x3x3_Relu", 0,
                            2, 2, 2, 2,
                            13, 15, 15, 14,
                            1, 1, 1, 1, 128, 128, 2, 2,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_RELU);
    
    
    // generator for Conv_26
    CNN_ConvolutionPoolReLU("S51_Conv2d_18x128x3x3", 0,
                            2, 2, 2, 2,
                            14, 14, 15, 12,
                            1, 1, 1, 1, 128, 18, 2, 2,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_NONE);
    
    
    // generator for Conv_27
    CNN_ConvolutionPoolReLU("S55_Conv2d_24x128x3x3", 0,
                            2, 2, 2, 2,
                            14, 15, 15, 13,
                            1, 1, 1, 1, 128, 24, 2, 2,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_NONE);
    

#define GRAPH
#ifdef GRAPH
    CreateGraph("cnn_ssdCNN",
        /* Arguments either passed or globals */
            CArgs(39,
                TCArgInfo("signed short * __restrict__", "Input_1", ARG_SCOPE_ARG, ARG_DIR_IN, AT_MEM_L2, AT_MEM_L2, 0),
                TCArgInfo("signed short * __restrict__", "Conv_0_weights", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_16BIT/tensors/Conv_0_weights.tensor", 1, 1, 16, 11)),
                TCArgInfo("signed short * __restrict__", "Constant_103", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_16BIT/tensors/Constant_103.tensor", 1, 1, 16, 14)),
                TCArgInfo("signed short * __restrict__", "Conv_3_weights", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_16BIT/tensors/Conv_3_weights.tensor", 1, 1, 16, 14)),
                TCArgInfo("signed short * __restrict__", "Constant_106", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_16BIT/tensors/Constant_106.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Conv_6_weights", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_16BIT/tensors/Conv_6_weights.tensor", 1, 1, 16, 14)),
                TCArgInfo("signed short * __restrict__", "Constant_109", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_16BIT/tensors/Constant_109.tensor", 1, 1, 16, 13)),
                TCArgInfo("signed short * __restrict__", "Conv_9_weights", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_16BIT/tensors/Conv_9_weights.tensor", 1, 1, 16, 14)),
                TCArgInfo("signed short * __restrict__", "Constant_112", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_16BIT/tensors/Constant_112.tensor", 1, 1, 16, 13)),
                TCArgInfo("signed short * __restrict__", "Conv_11_weights", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_16BIT/tensors/Conv_11_weights.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Constant_classification_headers.0.bias", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_16BIT/tensors/Constant_classification_headers.0.bias.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Conv_12_weights", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_16BIT/tensors/Conv_12_weights.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Constant_regression_headers.0.bias", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_16BIT/tensors/Constant_regression_headers.0.bias.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Conv_14_weights", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_16BIT/tensors/Conv_14_weights.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Constant_115", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_16BIT/tensors/Constant_115.tensor", 1, 1, 16, 13)),
                TCArgInfo("signed short * __restrict__", "Conv_16_weights", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_16BIT/tensors/Conv_16_weights.tensor", 1, 1, 16, 14)),
                TCArgInfo("signed short * __restrict__", "Constant_classification_headers.1.bias", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_16BIT/tensors/Constant_classification_headers.1.bias.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Conv_17_weights", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_16BIT/tensors/Conv_17_weights.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Constant_regression_headers.1.bias", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_16BIT/tensors/Constant_regression_headers.1.bias.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Conv_19_weights", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_16BIT/tensors/Conv_19_weights.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Constant_118", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_16BIT/tensors/Constant_118.tensor", 1, 1, 16, 13)),
                TCArgInfo("signed short * __restrict__", "Conv_21_weights", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_16BIT/tensors/Conv_21_weights.tensor", 1, 1, 16, 14)),
                TCArgInfo("signed short * __restrict__", "Constant_classification_headers.2.bias", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_16BIT/tensors/Constant_classification_headers.2.bias.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Conv_22_weights", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_16BIT/tensors/Conv_22_weights.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Constant_regression_headers.2.bias", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_16BIT/tensors/Constant_regression_headers.2.bias.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Conv_24_weights", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_16BIT/tensors/Conv_24_weights.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Constant_121", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_16BIT/tensors/Constant_121.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Conv_26_weights", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_16BIT/tensors/Conv_26_weights.tensor", 1, 1, 16, 14)),
                TCArgInfo("signed short * __restrict__", "Constant_classification_headers.3.bias", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_16BIT/tensors/Constant_classification_headers.3.bias.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Conv_27_weights", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_16BIT/tensors/Conv_27_weights.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Constant_regression_headers.3.bias", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_16BIT/tensors/Constant_regression_headers.3.bias.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Output_1", ARG_SCOPE_ARG, ARG_DIR_OUT, AT_MEM_L2, AT_MEM_L3_HRAM, 0),
                TCArgInfo("signed short * __restrict__", "Output_2", ARG_SCOPE_ARG, ARG_DIR_OUT, AT_MEM_L2, AT_MEM_L3_HRAM, 0),
                TCArgInfo("signed short * __restrict__", "Output_3", ARG_SCOPE_ARG, ARG_DIR_OUT, AT_MEM_L2, AT_MEM_L3_HRAM, 0),
                TCArgInfo("signed short * __restrict__", "Output_4", ARG_SCOPE_ARG, ARG_DIR_OUT, AT_MEM_L2, AT_MEM_L3_HRAM, 0),
                TCArgInfo("signed short * __restrict__", "Output_5", ARG_SCOPE_ARG, ARG_DIR_OUT, AT_MEM_L2, AT_MEM_L3_HRAM, 0),
                TCArgInfo("signed short * __restrict__", "Output_6", ARG_SCOPE_ARG, ARG_DIR_OUT, AT_MEM_L2, AT_MEM_L3_HRAM, 0),
                TCArgInfo("signed short * __restrict__", "Output_7", ARG_SCOPE_ARG, ARG_DIR_OUT, AT_MEM_L2, AT_MEM_L3_HRAM, 0),
                TCArgInfo("signed short * __restrict__", "Output_8", ARG_SCOPE_ARG, ARG_DIR_OUT, AT_MEM_L2, AT_MEM_L3_HRAM, 0)
            ),
        /* Locals, allocated dynamically */
        CArgs(10,
            TCArgInfo("signed short * __restrict__", "S3_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S6_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S9_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S12_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S13_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S24_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S25_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S36_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S37_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S48_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0)
        )
    );

    /* Stacked tensors - Concats */
    // no concats in graph so not stacked tensors created

    // Node S3_Conv2d_8x1x3x3_MaxPool_2x2_Relu inq 15 weightsq 11 outq 11 biasesq 14
    AddNode("S3_Conv2d_8x1x3x3_MaxPool_2x2_Relu", Bindings(4, GNodeArg(GNA_IN, "Input_1", 0), GNodeArg(GNA_IN, "Conv_0_weights", 0), GNodeArg(GNA_IN, "Constant_103", 0), GNodeArg(GNA_OUT, "S3_Output", 0)));
    // Node S6_Conv2d_16x8x3x3_MaxPool_2x2_Relu inq 11 weightsq 14 outq 12 biasesq 15
    AddNode("S6_Conv2d_16x8x3x3_MaxPool_2x2_Relu", Bindings(4, GNodeArg(GNA_IN, "S3_Output", 0), GNodeArg(GNA_IN, "Conv_3_weights", 0), GNodeArg(GNA_IN, "Constant_106", 0), GNodeArg(GNA_OUT, "S6_Output", 0)));
    // Node S9_Conv2d_16x16x3x3_MaxPool_2x2_Relu inq 12 weightsq 14 outq 12 biasesq 13
    AddNode("S9_Conv2d_16x16x3x3_MaxPool_2x2_Relu", Bindings(4, GNodeArg(GNA_IN, "S6_Output", 0), GNodeArg(GNA_IN, "Conv_6_weights", 0), GNodeArg(GNA_IN, "Constant_109", 0), GNodeArg(GNA_OUT, "S9_Output", 0)));
    // Node S12_Conv2d_32x16x3x3_Relu inq 12 weightsq 14 outq 12 biasesq 13
    AddNode("S12_Conv2d_32x16x3x3_Relu", Bindings(4, GNodeArg(GNA_IN, "S9_Output", 0), GNodeArg(GNA_IN, "Conv_9_weights", 0), GNodeArg(GNA_IN, "Constant_112", 0), GNodeArg(GNA_OUT, "S12_Output", 0)));
    // Node MaxPool_13 inq Q4.12 outq Q4.12
    AddNode("S13_MaxPool_2x2", Bindings(2, GNodeArg(GNA_IN, "S12_Output", 0), GNodeArg(GNA_OUT, "S13_Output", 0)));
    // Node S16_Conv2d_18x32x3x3 inq 12 weightsq 15 outq 11 biasesq 15
    AddNode("S16_Conv2d_18x32x3x3", Bindings(4, GNodeArg(GNA_IN, "S12_Output", 0), GNodeArg(GNA_IN, "Conv_11_weights", 0), GNodeArg(GNA_IN, "Constant_classification_headers.0.bias", 0), GNodeArg(GNA_OUT, "Output_1", 0)));
    // Node S20_Conv2d_24x32x3x3 inq 12 weightsq 15 outq 11 biasesq 15
    AddNode("S20_Conv2d_24x32x3x3", Bindings(4, GNodeArg(GNA_IN, "S12_Output", 0), GNodeArg(GNA_IN, "Conv_12_weights", 0), GNodeArg(GNA_IN, "Constant_regression_headers.0.bias", 0), GNodeArg(GNA_OUT, "Output_2", 0)));
    // Node S24_Conv2d_64x32x3x3_Relu inq 12 weightsq 15 outq 13 biasesq 13
    AddNode("S24_Conv2d_64x32x3x3_Relu", Bindings(4, GNodeArg(GNA_IN, "S13_Output", 0), GNodeArg(GNA_IN, "Conv_14_weights", 0), GNodeArg(GNA_IN, "Constant_115", 0), GNodeArg(GNA_OUT, "S24_Output", 0)));
    // Node MaxPool_18 inq Q3.13 outq Q3.13
    AddNode("S25_MaxPool_2x2", Bindings(2, GNodeArg(GNA_IN, "S24_Output", 0), GNodeArg(GNA_OUT, "S25_Output", 0)));
    // Node S28_Conv2d_18x64x3x3 inq 13 weightsq 14 outq 11 biasesq 15
    AddNode("S28_Conv2d_18x64x3x3", Bindings(4, GNodeArg(GNA_IN, "S24_Output", 0), GNodeArg(GNA_IN, "Conv_16_weights", 0), GNodeArg(GNA_IN, "Constant_classification_headers.1.bias", 0), GNodeArg(GNA_OUT, "Output_3", 0)));
    // Node S32_Conv2d_24x64x3x3 inq 13 weightsq 15 outq 12 biasesq 15
    AddNode("S32_Conv2d_24x64x3x3", Bindings(4, GNodeArg(GNA_IN, "S24_Output", 0), GNodeArg(GNA_IN, "Conv_17_weights", 0), GNodeArg(GNA_IN, "Constant_regression_headers.1.bias", 0), GNodeArg(GNA_OUT, "Output_4", 0)));
    // Node S36_Conv2d_128x64x3x3_Relu inq 13 weightsq 15 outq 13 biasesq 13
    AddNode("S36_Conv2d_128x64x3x3_Relu", Bindings(4, GNodeArg(GNA_IN, "S25_Output", 0), GNodeArg(GNA_IN, "Conv_19_weights", 0), GNodeArg(GNA_IN, "Constant_118", 0), GNodeArg(GNA_OUT, "S36_Output", 0)));
    // Node MaxPool_23 inq Q3.13 outq Q3.13
    AddNode("S37_MaxPool_2x2", Bindings(2, GNodeArg(GNA_IN, "S36_Output", 0), GNodeArg(GNA_OUT, "S37_Output", 0)));
    // Node S40_Conv2d_18x128x3x3 inq 13 weightsq 14 outq 11 biasesq 15
    AddNode("S40_Conv2d_18x128x3x3", Bindings(4, GNodeArg(GNA_IN, "S36_Output", 0), GNodeArg(GNA_IN, "Conv_21_weights", 0), GNodeArg(GNA_IN, "Constant_classification_headers.2.bias", 0), GNodeArg(GNA_OUT, "Output_5", 0)));
    // Node S44_Conv2d_24x128x3x3 inq 13 weightsq 15 outq 12 biasesq 15
    AddNode("S44_Conv2d_24x128x3x3", Bindings(4, GNodeArg(GNA_IN, "S36_Output", 0), GNodeArg(GNA_IN, "Conv_22_weights", 0), GNodeArg(GNA_IN, "Constant_regression_headers.2.bias", 0), GNodeArg(GNA_OUT, "Output_6", 0)));
    // Node S48_Conv2d_128x128x3x3_Relu inq 13 weightsq 15 outq 14 biasesq 15
    AddNode("S48_Conv2d_128x128x3x3_Relu", Bindings(4, GNodeArg(GNA_IN, "S37_Output", 0), GNodeArg(GNA_IN, "Conv_24_weights", 0), GNodeArg(GNA_IN, "Constant_121", 0), GNodeArg(GNA_OUT, "S48_Output", 0)));
    // Node S51_Conv2d_18x128x3x3 inq 14 weightsq 14 outq 12 biasesq 15
    AddNode("S51_Conv2d_18x128x3x3", Bindings(4, GNodeArg(GNA_IN, "S48_Output", 0), GNodeArg(GNA_IN, "Conv_26_weights", 0), GNodeArg(GNA_IN, "Constant_classification_headers.3.bias", 0), GNodeArg(GNA_OUT, "Output_7", 0)));
    // Node S55_Conv2d_24x128x3x3 inq 14 weightsq 15 outq 13 biasesq 15
    AddNode("S55_Conv2d_24x128x3x3", Bindings(4, GNodeArg(GNA_IN, "S48_Output", 0), GNodeArg(GNA_IN, "Conv_27_weights", 0), GNodeArg(GNA_IN, "Constant_regression_headers.3.bias", 0), GNodeArg(GNA_OUT, "Output_8", 0)));
    CloseGraph();
#endif
}

int main(int argc, char **argv)

{
    if (TilerParseOptions(argc, argv)) {
            printf("Failed to initialize or incorrect output arguments directory.\n"); return 1;
    }
    cnn_ssdModel(52000, 300*1024, 8*1024*1024, 20*1024*1024);
    GenerateTilingCode();
    return 0;
}
