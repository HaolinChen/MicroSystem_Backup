#ifndef RESNET_GRAPHINFO_H
#define RESNET_GRAPHINFO_H
// Quantized scales can be used round_norm(val * QSCALE, QNORM) giving the real value in Q8

// S0_Op_input_1
#define S0_Op_input_1_Q	15
// S1_Op_DEPTHWISE_CONV_2D_0_1_r_hwc_chw
#define S1_Op_DEPTHWISE_CONV_2D_0_1_r_hwc_chw_Q	15
// S2_Op_conv1kernel
#define S2_Op_conv1kernel_Q	11
// S3_Op_model_1conv1Conv2D_bias
#define S3_Op_model_1conv1Conv2D_bias_Q	12
// S4_Conv2d_8x1x7x7_MaxPool_3x3_Relu
#define S4_Conv2d_8x1x7x7_MaxPool_3x3_Relu_Q	11
// S5_Op_res2bbranch2akernel
#define S5_Op_res2bbranch2akernel_Q	15
// S6_Op_model_1res2bbranch2aConv2D_bia
#define S6_Op_model_1res2bbranch2aConv2D_bia_Q	13
// S7_Conv2d_8x8x3x3_Relu
#define S7_Conv2d_8x8x3x3_Relu_Q	12
// S8_Op_res2bbranch2bkernel
#define S8_Op_res2bbranch2bkernel_Q	15
// S9_Op_model_1res2bbranch2bConv2D_bia
#define S9_Op_model_1res2bbranch2bConv2D_bia_Q	13
// S10_Conv2d_8x8x3x3
#define S10_Conv2d_8x8x3x3_Q	12
// S11_MatAdd_8x39x39
#define S11_MatAdd_8x39x39_Q	11
// S12_Op_res2cbranch2akernel
#define S12_Op_res2cbranch2akernel_Q	15
// S13_Op_model_1res2cbranch2aConv2D_bia
#define S13_Op_model_1res2cbranch2aConv2D_bia_Q	14
// S14_Conv2d_8x8x3x3_Relu
#define S14_Conv2d_8x8x3x3_Relu_Q	12
// S15_Op_res2cbranch2bkernel
#define S15_Op_res2cbranch2bkernel_Q	15
// S16_Op_model_1res2cbranch2bConv2D_bia
#define S16_Op_model_1res2cbranch2bConv2D_bia_Q	14
// S17_Conv2d_8x8x3x3
#define S17_Conv2d_8x8x3x3_Q	11
// S18_MatAdd_8x39x39
#define S18_MatAdd_8x39x39_Q	11
// S19_Op_res3a_branch2akernel
#define S19_Op_res3a_branch2akernel_Q	15
// S20_Op_model_1res3a_branch2aConv2D_bi
#define S20_Op_model_1res3a_branch2aConv2D_bi_Q	14
// S21_Conv2d_16x8x3x3_Relu
#define S21_Conv2d_16x8x3x3_Relu_Q	12
// S22_Op_res3a_branch1kernel
#define S22_Op_res3a_branch1kernel_Q	14
// S23_Op_model_1res3a_branch1Conv2D_bia
#define S23_Op_model_1res3a_branch1Conv2D_bia_Q	13
// S24_Conv2d_16x8x1x1
#define S24_Conv2d_16x8x1x1_Q	11
// S25_Op_res3a_branch2bkernel
#define S25_Op_res3a_branch2bkernel_Q	15
// S26_Op_model_1res3a_branch2bConv2D_bi
#define S26_Op_model_1res3a_branch2bConv2D_bi_Q	12
// S27_Conv2d_16x16x3x3_Relu
#define S27_Conv2d_16x16x3x3_Relu_Q	12
// S28_MatAdd_16x20x20
#define S28_MatAdd_16x20x20_Q	11
// S29_Op_res3bbranch2akernel
#define S29_Op_res3bbranch2akernel_Q	15
// S30_Op_model_1res3bbranch2aConv2D_bia
#define S30_Op_model_1res3bbranch2aConv2D_bia_Q	14
// S31_Conv2d_16x16x3x3_Relu
#define S31_Conv2d_16x16x3x3_Relu_Q	12
// S32_Op_res3bbranch2bkernel
#define S32_Op_res3bbranch2bkernel_Q	15
// S33_Op_model_1res3bbranch2bConv2D_bia
#define S33_Op_model_1res3bbranch2bConv2D_bia_Q	13
// S34_Conv2d_16x16x3x3
#define S34_Conv2d_16x16x3x3_Q	11
// S35_MatAdd_16x20x20
#define S35_MatAdd_16x20x20_Q	10
// S36_Op_res4a_branch2akernel
#define S36_Op_res4a_branch2akernel_Q	15
// S37_Op_model_1res4a_branch2aConv2D_bi
#define S37_Op_model_1res4a_branch2aConv2D_bi_Q	14
// S38_Conv2d_32x16x3x3_Relu
#define S38_Conv2d_32x16x3x3_Relu_Q	12
// S39_Op_res4a_branch1kernel
#define S39_Op_res4a_branch1kernel_Q	15
// S40_Op_model_1res4a_branch1Conv2D_bia
#define S40_Op_model_1res4a_branch1Conv2D_bia_Q	14
// S41_Conv2d_32x16x1x1
#define S41_Conv2d_32x16x1x1_Q	11
// S42_Op_res4a_branch2bkernel
#define S42_Op_res4a_branch2bkernel_Q	14
// S43_Op_model_1res4a_branch2bConv2D_bi
#define S43_Op_model_1res4a_branch2bConv2D_bi_Q	12
// S44_Conv2d_32x32x3x3_Relu
#define S44_Conv2d_32x32x3x3_Relu_Q	12
// S45_MatAdd_32x10x10
#define S45_MatAdd_32x10x10_Q	11
// S46_Op_res4bbranch2akernel
#define S46_Op_res4bbranch2akernel_Q	15
// S47_Op_model_1res4bbranch2aConv2D_bia
#define S47_Op_model_1res4bbranch2aConv2D_bia_Q	14
// S48_Conv2d_32x32x3x3_Relu
#define S48_Conv2d_32x32x3x3_Relu_Q	13
// S49_Op_res4bbranch2bkernel
#define S49_Op_res4bbranch2bkernel_Q	14
// S50_Op_model_1res4bbranch2bConv2D_bia
#define S50_Op_model_1res4bbranch2bConv2D_bia_Q	13
// S51_Conv2d_32x32x3x3
#define S51_Conv2d_32x32x3x3_Q	11
// S52_MatAdd_32x10x10
#define S52_MatAdd_32x10x10_Q	11
// S53_Op_res5a_branch2akernel
#define S53_Op_res5a_branch2akernel_Q	15
// S54_Op_model_1res5a_branch2aConv2D_bi
#define S54_Op_model_1res5a_branch2aConv2D_bi_Q	14
// S55_Conv2d_64x32x3x3_Relu
#define S55_Conv2d_64x32x3x3_Relu_Q	12
// S56_Op_res5a_branch1kernel
#define S56_Op_res5a_branch1kernel_Q	15
// S57_Op_model_1res5a_branch1Conv2D_bia
#define S57_Op_model_1res5a_branch1Conv2D_bia_Q	15
// S58_Conv2d_64x32x1x1
#define S58_Conv2d_64x32x1x1_Q	12
// S59_Op_res5a_branch2bkernel
#define S59_Op_res5a_branch2bkernel_Q	14
// S60_Op_model_1res5a_branch2bConv2D_bi
#define S60_Op_model_1res5a_branch2bConv2D_bi_Q	13
// S61_Conv2d_64x64x3x3_Relu
#define S61_Conv2d_64x64x3x3_Relu_Q	12
// S62_MatAdd_64x5x5
#define S62_MatAdd_64x5x5_Q	11
// S63_Op_res5bbranch2akernel
#define S63_Op_res5bbranch2akernel_Q	15
// S64_Op_model_1res5bbranch2aConv2D_bia
#define S64_Op_model_1res5bbranch2aConv2D_bia_Q	14
// S65_Conv2d_64x64x3x3_Relu
#define S65_Conv2d_64x64x3x3_Relu_Q	13
// S66_Op_res5bbranch2bkernel
#define S66_Op_res5bbranch2bkernel_Q	15
// S67_Op_model_1res5bbranch2bConv2D_bia
#define S67_Op_model_1res5bbranch2bConv2D_bia_Q	14
// S68_Conv2d_64x64x3x3
#define S68_Conv2d_64x64x3x3_Q	12
// S69_MatAdd_64x5x5
#define S69_MatAdd_64x5x5_Q	11
// S70_AveragePool_2x2
#define S70_AveragePool_2x2_Q	11
// S71_Op_weightedaveragekerneltranspose
#define S71_Op_weightedaveragekerneltranspose_Q	15
// S72_Op_m2weightedaverageMatMul_bias
#define S72_Op_m2weightedaverageMatMul_bias_Q	15
// S73_Linear_7x64x2x2
#define S73_Linear_7x64x2x2_Q	10
// S74_SoftMax
#define S74_SoftMax_Q	15
// S75_Op_output_1
#define S75_Op_output_1_Q	15
#endif //RESNET_GRAPHINFO_H