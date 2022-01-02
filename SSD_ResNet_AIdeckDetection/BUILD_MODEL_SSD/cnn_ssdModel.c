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
                            14, 10, 14, 10,
                            1, 1, 1, 1, 1, 8, 160, 128,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_MAXPOOL, 2, 2, 1, 1, 2, 2, 0,
                            KOP_RELU);
    
    
    // generator for Conv_3_fusion
    CNN_ConvolutionPoolReLU("S6_Conv2d_16x8x3x3_MaxPool_2x2_Relu", 0,
                            2, 2, 2, 2,
                            10, 15, 14, 12,
                            1, 1, 1, 1, 8, 16, 80, 64,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_MAXPOOL, 2, 2, 1, 1, 2, 2, 0,
                            KOP_RELU);
    
    
    // generator for Conv_6_fusion
    CNN_ConvolutionPoolReLU("S9_Conv2d_16x16x3x3_MaxPool_2x2_Relu", 0,
                            2, 2, 2, 2,
                            12, 14, 13, 13,
                            1, 1, 1, 1, 16, 16, 40, 32,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_MAXPOOL, 2, 2, 1, 1, 2, 2, 0,
                            KOP_RELU);
    
    
    // generator for Conv_9_fusion
    CNN_ConvolutionPoolReLU("S12_Conv2d_32x16x3x3_Relu", 0,
                            2, 2, 2, 2,
                            13, 13, 13, 12,
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
                            12, 14, 15, 11,
                            1, 1, 1, 1, 32, 18, 20, 16,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_NONE);
    
    
    // generator for Conv_12
    CNN_ConvolutionPoolReLU("S20_Conv2d_24x32x3x3", 0,
                            2, 2, 2, 2,
                            12, 15, 15, 12,
                            1, 1, 1, 1, 32, 24, 20, 16,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_NONE);
    
    
    // generator for Conv_14_fusion
    CNN_ConvolutionPoolReLU("S24_Conv2d_64x32x3x3_Relu", 0,
                            2, 2, 2, 2,
                            12, 15, 13, 12,
                            1, 1, 1, 1, 32, 64, 10, 8,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_RELU);
    
    
    // generator for MaxPool_18
    CNN_PoolReLU("S25_MaxPool_2x2", 0,
                  2, 2,
                  12, 12,
                  1, 1, 64, 64, 10, 8,
                  KOP_MAXPOOL, 2, 2, 1, 1, 2, 2, 0,
                  KOP_NONE);
    
    
    // generator for Conv_16
    CNN_ConvolutionPoolReLU("S28_Conv2d_18x64x3x3", 0,
                            2, 2, 2, 2,
                            12, 14, 15, 11,
                            1, 1, 1, 1, 64, 18, 10, 8,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_NONE);
    
    
    // generator for Conv_17
    CNN_ConvolutionPoolReLU("S32_Conv2d_24x64x3x3", 0,
                            2, 2, 2, 2,
                            12, 15, 15, 12,
                            1, 1, 1, 1, 64, 24, 10, 8,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_NONE);
    
    
    // generator for Conv_19_fusion
    CNN_ConvolutionPoolReLU("S36_Conv2d_128x64x3x3_Relu", 0,
                            2, 2, 2, 2,
                            12, 15, 13, 12,
                            1, 1, 1, 1, 64, 128, 5, 4,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_RELU);
    
    
    // generator for Conv_21
    CNN_ConvolutionPoolReLU("S39_Conv2d_18x128x3x3", 0,
                            2, 2, 2, 2,
                            12, 14, 15, 11,
                            1, 1, 1, 1, 128, 18, 5, 4,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_NONE);
    
    
    // generator for Conv_22
    CNN_ConvolutionPoolReLU("S43_Conv2d_24x128x3x3", 0,
                            2, 2, 2, 2,
                            12, 15, 15, 12,
                            1, 1, 1, 1, 128, 24, 5, 4,
                            KOP_CONV_DP, 3, 3, 1, 1, 1, 1, 1,
                            KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                            KOP_NONE);
    

#define GRAPH
#ifdef GRAPH
    CreateGraph("cnn_ssdCNN",
        /* Arguments either passed or globals */
            CArgs(31,
                TCArgInfo("signed short * __restrict__", "Input_1", ARG_SCOPE_ARG, ARG_DIR_IN, AT_MEM_L2, AT_MEM_L2, 0),
                TCArgInfo("signed short * __restrict__", "Conv_0_weights", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_SSD/tensors/Conv_0_weights.tensor", 1, 1, 16, 10)),
                TCArgInfo("signed short * __restrict__", "Constant_86", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_SSD/tensors/Constant_86.tensor", 1, 1, 16, 14)),
                TCArgInfo("signed short * __restrict__", "Conv_3_weights", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_SSD/tensors/Conv_3_weights.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Constant_89", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_SSD/tensors/Constant_89.tensor", 1, 1, 16, 14)),
                TCArgInfo("signed short * __restrict__", "Conv_6_weights", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_SSD/tensors/Conv_6_weights.tensor", 1, 1, 16, 14)),
                TCArgInfo("signed short * __restrict__", "Constant_92", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_SSD/tensors/Constant_92.tensor", 1, 1, 16, 13)),
                TCArgInfo("signed short * __restrict__", "Conv_9_weights", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_SSD/tensors/Conv_9_weights.tensor", 1, 1, 16, 13)),
                TCArgInfo("signed short * __restrict__", "Constant_95", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_SSD/tensors/Constant_95.tensor", 1, 1, 16, 13)),
                TCArgInfo("signed short * __restrict__", "Conv_11_weights", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_SSD/tensors/Conv_11_weights.tensor", 1, 1, 16, 14)),
                TCArgInfo("signed short * __restrict__", "Constant_classification_headers.0.bias", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_SSD/tensors/Constant_classification_headers.0.bias.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Conv_12_weights", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_SSD/tensors/Conv_12_weights.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Constant_regression_headers.0.bias", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_SSD/tensors/Constant_regression_headers.0.bias.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Conv_14_weights", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_SSD/tensors/Conv_14_weights.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Constant_98", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_SSD/tensors/Constant_98.tensor", 1, 1, 16, 13)),
                TCArgInfo("signed short * __restrict__", "Conv_16_weights", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_SSD/tensors/Conv_16_weights.tensor", 1, 1, 16, 14)),
                TCArgInfo("signed short * __restrict__", "Constant_classification_headers.1.bias", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_SSD/tensors/Constant_classification_headers.1.bias.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Conv_17_weights", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_SSD/tensors/Conv_17_weights.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Constant_regression_headers.1.bias", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_SSD/tensors/Constant_regression_headers.1.bias.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Conv_19_weights", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_SSD/tensors/Conv_19_weights.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Constant_101", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_SSD/tensors/Constant_101.tensor", 1, 1, 16, 13)),
                TCArgInfo("signed short * __restrict__", "Conv_21_weights", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_SSD/tensors/Conv_21_weights.tensor", 1, 1, 16, 14)),
                TCArgInfo("signed short * __restrict__", "Constant_classification_headers.2.bias", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_SSD/tensors/Constant_classification_headers.2.bias.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Conv_22_weights", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_SSD/tensors/Conv_22_weights.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Constant_regression_headers.2.bias", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_SSD/tensors/Constant_regression_headers.2.bias.tensor", 1, 1, 16, 15)),
                TCArgInfo("signed short * __restrict__", "Output_1", ARG_SCOPE_ARG, ARG_DIR_OUT, AT_MEM_L2, AT_MEM_L3_HRAM, 0),
                TCArgInfo("signed short * __restrict__", "Output_2", ARG_SCOPE_ARG, ARG_DIR_OUT, AT_MEM_L2, AT_MEM_L3_HRAM, 0),
                TCArgInfo("signed short * __restrict__", "Output_3", ARG_SCOPE_ARG, ARG_DIR_OUT, AT_MEM_L2, AT_MEM_L3_HRAM, 0),
                TCArgInfo("signed short * __restrict__", "Output_4", ARG_SCOPE_ARG, ARG_DIR_OUT, AT_MEM_L2, AT_MEM_L3_HRAM, 0),
                TCArgInfo("signed short * __restrict__", "Output_5", ARG_SCOPE_ARG, ARG_DIR_OUT, AT_MEM_L2, AT_MEM_L3_HRAM, 0),
                TCArgInfo("signed short * __restrict__", "Output_6", ARG_SCOPE_ARG, ARG_DIR_OUT, AT_MEM_L2, AT_MEM_L3_HRAM, 0)
            ),
        /* Locals, allocated dynamically */
        CArgs(8,
            TCArgInfo("signed short * __restrict__", "S3_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S6_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S9_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S12_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S13_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S24_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S25_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S36_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0)
        )
    );

    /* Stacked tensors - Concats */
    // no concats in graph so not stacked tensors created

    // Node S3_Conv2d_8x1x3x3_MaxPool_2x2_Relu inq 14 weightsq 10 outq 10 biasesq 14
    AddNode("S3_Conv2d_8x1x3x3_MaxPool_2x2_Relu", Bindings(4, GNodeArg(GNA_IN, "Input_1", 0), GNodeArg(GNA_IN, "Conv_0_weights", 0), GNodeArg(GNA_IN, "Constant_86", 0), GNodeArg(GNA_OUT, "S3_Output", 0)));
    // Node S6_Conv2d_16x8x3x3_MaxPool_2x2_Relu inq 10 weightsq 15 outq 12 biasesq 14
    AddNode("S6_Conv2d_16x8x3x3_MaxPool_2x2_Relu", Bindings(4, GNodeArg(GNA_IN, "S3_Output", 0), GNodeArg(GNA_IN, "Conv_3_weights", 0), GNodeArg(GNA_IN, "Constant_89", 0), GNodeArg(GNA_OUT, "S6_Output", 0)));
    // Node S9_Conv2d_16x16x3x3_MaxPool_2x2_Relu inq 12 weightsq 14 outq 13 biasesq 13
    AddNode("S9_Conv2d_16x16x3x3_MaxPool_2x2_Relu", Bindings(4, GNodeArg(GNA_IN, "S6_Output", 0), GNodeArg(GNA_IN, "Conv_6_weights", 0), GNodeArg(GNA_IN, "Constant_92", 0), GNodeArg(GNA_OUT, "S9_Output", 0)));
    // Node S12_Conv2d_32x16x3x3_Relu inq 13 weightsq 13 outq 12 biasesq 13
    AddNode("S12_Conv2d_32x16x3x3_Relu", Bindings(4, GNodeArg(GNA_IN, "S9_Output", 0), GNodeArg(GNA_IN, "Conv_9_weights", 0), GNodeArg(GNA_IN, "Constant_95", 0), GNodeArg(GNA_OUT, "S12_Output", 0)));
    // Node MaxPool_13 inq Q4.12 outq Q4.12
    AddNode("S13_MaxPool_2x2", Bindings(2, GNodeArg(GNA_IN, "S12_Output", 0), GNodeArg(GNA_OUT, "S13_Output", 0)));
    // Node S16_Conv2d_18x32x3x3 inq 12 weightsq 14 outq 11 biasesq 15
    AddNode("S16_Conv2d_18x32x3x3", Bindings(4, GNodeArg(GNA_IN, "S12_Output", 0), GNodeArg(GNA_IN, "Conv_11_weights", 0), GNodeArg(GNA_IN, "Constant_classification_headers.0.bias", 0), GNodeArg(GNA_OUT, "Output_1", 0)));
    // Node S20_Conv2d_24x32x3x3 inq 12 weightsq 15 outq 12 biasesq 15
    AddNode("S20_Conv2d_24x32x3x3", Bindings(4, GNodeArg(GNA_IN, "S12_Output", 0), GNodeArg(GNA_IN, "Conv_12_weights", 0), GNodeArg(GNA_IN, "Constant_regression_headers.0.bias", 0), GNodeArg(GNA_OUT, "Output_2", 0)));
    // Node S24_Conv2d_64x32x3x3_Relu inq 12 weightsq 15 outq 12 biasesq 13
    AddNode("S24_Conv2d_64x32x3x3_Relu", Bindings(4, GNodeArg(GNA_IN, "S13_Output", 0), GNodeArg(GNA_IN, "Conv_14_weights", 0), GNodeArg(GNA_IN, "Constant_98", 0), GNodeArg(GNA_OUT, "S24_Output", 0)));
    // Node MaxPool_18 inq Q4.12 outq Q4.12
    AddNode("S25_MaxPool_2x2", Bindings(2, GNodeArg(GNA_IN, "S24_Output", 0), GNodeArg(GNA_OUT, "S25_Output", 0)));
    // Node S28_Conv2d_18x64x3x3 inq 12 weightsq 14 outq 11 biasesq 15
    AddNode("S28_Conv2d_18x64x3x3", Bindings(4, GNodeArg(GNA_IN, "S24_Output", 0), GNodeArg(GNA_IN, "Conv_16_weights", 0), GNodeArg(GNA_IN, "Constant_classification_headers.1.bias", 0), GNodeArg(GNA_OUT, "Output_3", 0)));
    // Node S32_Conv2d_24x64x3x3 inq 12 weightsq 15 outq 12 biasesq 15
    AddNode("S32_Conv2d_24x64x3x3", Bindings(4, GNodeArg(GNA_IN, "S24_Output", 0), GNodeArg(GNA_IN, "Conv_17_weights", 0), GNodeArg(GNA_IN, "Constant_regression_headers.1.bias", 0), GNodeArg(GNA_OUT, "Output_4", 0)));
    // Node S36_Conv2d_128x64x3x3_Relu inq 12 weightsq 15 outq 12 biasesq 13
    AddNode("S36_Conv2d_128x64x3x3_Relu", Bindings(4, GNodeArg(GNA_IN, "S25_Output", 0), GNodeArg(GNA_IN, "Conv_19_weights", 0), GNodeArg(GNA_IN, "Constant_101", 0), GNodeArg(GNA_OUT, "S36_Output", 0)));
    // Node S39_Conv2d_18x128x3x3 inq 12 weightsq 14 outq 11 biasesq 15
    AddNode("S39_Conv2d_18x128x3x3", Bindings(4, GNodeArg(GNA_IN, "S36_Output", 0), GNodeArg(GNA_IN, "Conv_21_weights", 0), GNodeArg(GNA_IN, "Constant_classification_headers.2.bias", 0), GNodeArg(GNA_OUT, "Output_5", 0)));
    // Node S43_Conv2d_24x128x3x3 inq 12 weightsq 15 outq 12 biasesq 15
    AddNode("S43_Conv2d_24x128x3x3", Bindings(4, GNodeArg(GNA_IN, "S36_Output", 0), GNodeArg(GNA_IN, "Conv_22_weights", 0), GNodeArg(GNA_IN, "Constant_regression_headers.2.bias", 0), GNodeArg(GNA_OUT, "Output_6", 0)));
    CloseGraph();
#endif
}

int main(int argc, char **argv)

{
    if (TilerParseOptions(argc, argv)) {
            printf("Failed to initialize or incorrect output arguments directory.\n"); return 1;
    }
    cnn_ssdModel(64000, 300000, 8000000, 20*1024*1024);
    GenerateTilingCode();
    return 0;
}
