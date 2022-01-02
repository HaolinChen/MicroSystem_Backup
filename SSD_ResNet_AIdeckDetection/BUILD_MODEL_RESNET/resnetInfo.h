#ifndef RESNET_GRAPHINFO_H
#define RESNET_GRAPHINFO_H
// Quantized scales can be used round_norm(val * QSCALE, QNORM) giving the real value in Q8

// S0_Op_input_1
#define S0_Op_input_1_Q	15
// S1_Op_DEPTHWISE_CONV_2D_0_0_r_hwc_chw
#define S1_Op_DEPTHWISE_CONV_2D_0_0_r_hwc_chw_Q	15
// S2_Op_conv1kernel
#define S2_Op_conv1kernel_Q	11
// S3_Op_model_1conv1Conv2D_bias
#define S3_Op_model_1conv1Conv2D_bias_Q	13
// S4_Conv2d_8x1x3x3_Relu
#define S4_Conv2d_8x1x3x3_Relu_Q	12
// S5_Op_conv2kernel
#define S5_Op_conv2kernel_Q	13
// S6_Op_model_1conv2Conv2D_bias
#define S6_Op_model_1conv2Conv2D_bias_Q	13
// S7_Conv2d_8x8x3x3_Relu
#define S7_Conv2d_8x8x3x3_Relu_Q	11
// S8_Op_res2bbranch2akernel
#define S8_Op_res2bbranch2akernel_Q	14
// S9_Op_model_1res2bbranch2aConv2D_bia
#define S9_Op_model_1res2bbranch2aConv2D_bia_Q	13
// S10_Conv2d_8x8x3x3_Relu
#define S10_Conv2d_8x8x3x3_Relu_Q	12
// S11_Op_res2bbranch2bkernel
#define S11_Op_res2bbranch2bkernel_Q	13
// S12_Op_model_1res2bbranch2bConv2D_bia
#define S12_Op_model_1res2bbranch2bConv2D_bia_Q	14
// S13_Conv2d_8x8x3x3
#define S13_Conv2d_8x8x3x3_Q	10
// S14_MatAdd_8x39x39
#define S14_MatAdd_8x39x39_Q	10
// S15_Op_res2cbranch2akernel
#define S15_Op_res2cbranch2akernel_Q	15
// S16_Op_model_1res2cbranch2aConv2D_bia
#define S16_Op_model_1res2cbranch2aConv2D_bia_Q	15
// S17_Conv2d_8x8x3x3_Relu
#define S17_Conv2d_8x8x3x3_Relu_Q	12
// S18_Op_res2cbranch2bkernel
#define S18_Op_res2cbranch2bkernel_Q	14
// S19_Op_model_1res2cbranch2bConv2D_bia
#define S19_Op_model_1res2cbranch2bConv2D_bia_Q	13
// S20_Conv2d_8x8x3x3
#define S20_Conv2d_8x8x3x3_Q	11
// S21_MatAdd_8x39x39
#define S21_MatAdd_8x39x39_Q	10
// S22_Op_res3a_branch2akernel
#define S22_Op_res3a_branch2akernel_Q	15
// S23_Op_model_1res3a_branch2aConv2D_bi
#define S23_Op_model_1res3a_branch2aConv2D_bi_Q	14
// S24_Conv2d_16x8x3x3_Relu
#define S24_Conv2d_16x8x3x3_Relu_Q	12
// S25_Op_res3a_branch1kernel
#define S25_Op_res3a_branch1kernel_Q	15
// S26_Op_model_1res3a_branch1Conv2D_bia
#define S26_Op_model_1res3a_branch1Conv2D_bia_Q	14
// S27_Conv2d_16x8x1x1
#define S27_Conv2d_16x8x1x1_Q	11
// S28_Op_res3a_branch2bkernel
#define S28_Op_res3a_branch2bkernel_Q	14
// S29_Op_model_1res3a_branch2bConv2D_bi
#define S29_Op_model_1res3a_branch2bConv2D_bi_Q	13
// S30_Conv2d_16x16x3x3_Relu
#define S30_Conv2d_16x16x3x3_Relu_Q	12
// S31_MatAdd_16x20x20
#define S31_MatAdd_16x20x20_Q	11
// S32_Op_res3bbranch2akernel
#define S32_Op_res3bbranch2akernel_Q	15
// S33_Op_model_1res3bbranch2aConv2D_bia
#define S33_Op_model_1res3bbranch2aConv2D_bia_Q	15
// S34_Conv2d_16x16x3x3_Relu
#define S34_Conv2d_16x16x3x3_Relu_Q	12
// S35_Op_res3bbranch2bkernel
#define S35_Op_res3bbranch2bkernel_Q	14
// S36_Op_model_1res3bbranch2bConv2D_bia
#define S36_Op_model_1res3bbranch2bConv2D_bia_Q	13
// S37_Conv2d_16x16x3x3
#define S37_Conv2d_16x16x3x3_Q	11
// S38_MatAdd_16x20x20
#define S38_MatAdd_16x20x20_Q	11
// S39_Op_res4a_branch2akernel
#define S39_Op_res4a_branch2akernel_Q	15
// S40_Op_model_1res4a_branch2aConv2D_bi
#define S40_Op_model_1res4a_branch2aConv2D_bi_Q	14
// S41_Conv2d_32x16x3x3_Relu
#define S41_Conv2d_32x16x3x3_Relu_Q	12
// S42_Op_res4a_branch1kernel
#define S42_Op_res4a_branch1kernel_Q	15
// S43_Op_model_1res4a_branch1Conv2D_bia
#define S43_Op_model_1res4a_branch1Conv2D_bia_Q	14
// S44_Conv2d_32x16x1x1
#define S44_Conv2d_32x16x1x1_Q	11
// S45_Op_res4a_branch2bkernel
#define S45_Op_res4a_branch2bkernel_Q	14
// S46_Op_model_1res4a_branch2bConv2D_bi
#define S46_Op_model_1res4a_branch2bConv2D_bi_Q	12
// S47_Conv2d_32x32x3x3_Relu
#define S47_Conv2d_32x32x3x3_Relu_Q	12
// S48_MatAdd_32x10x10
#define S48_MatAdd_32x10x10_Q	11
// S49_Op_res4bbranch2akernel
#define S49_Op_res4bbranch2akernel_Q	15
// S50_Op_model_1res4bbranch2aConv2D_bia
#define S50_Op_model_1res4bbranch2aConv2D_bia_Q	15
// S51_Conv2d_32x32x3x3_Relu
#define S51_Conv2d_32x32x3x3_Relu_Q	12
// S52_Op_res4bbranch2bkernel
#define S52_Op_res4bbranch2bkernel_Q	14
// S53_Op_model_1res4bbranch2bConv2D_bia
#define S53_Op_model_1res4bbranch2bConv2D_bia_Q	13
// S54_Conv2d_32x32x3x3
#define S54_Conv2d_32x32x3x3_Q	11
// S55_MatAdd_32x10x10
#define S55_MatAdd_32x10x10_Q	11
// S56_Op_res5a_branch2akernel
#define S56_Op_res5a_branch2akernel_Q	15
// S57_Op_model_1res5a_branch2aConv2D_bi
#define S57_Op_model_1res5a_branch2aConv2D_bi_Q	15
// S58_Conv2d_64x32x3x3_Relu
#define S58_Conv2d_64x32x3x3_Relu_Q	12
// S59_Op_res5a_branch1kernel
#define S59_Op_res5a_branch1kernel_Q	15
// S60_Op_model_1res5a_branch1Conv2D_bia
#define S60_Op_model_1res5a_branch1Conv2D_bia_Q	15
// S61_Conv2d_64x32x1x1
#define S61_Conv2d_64x32x1x1_Q	13
// S62_Op_res5a_branch2bkernel
#define S62_Op_res5a_branch2bkernel_Q	14
// S63_Op_model_1res5a_branch2bConv2D_bi
#define S63_Op_model_1res5a_branch2bConv2D_bi_Q	13
// S64_Conv2d_64x64x3x3_Relu
#define S64_Conv2d_64x64x3x3_Relu_Q	13
// S65_MatAdd_64x5x5
#define S65_MatAdd_64x5x5_Q	12
// S66_Op_res5bbranch2akernel
#define S66_Op_res5bbranch2akernel_Q	15
// S67_Op_model_1res5bbranch2aConv2D_bia
#define S67_Op_model_1res5bbranch2aConv2D_bia_Q	15
// S68_Conv2d_64x64x3x3_Relu
#define S68_Conv2d_64x64x3x3_Relu_Q	13
// S69_Op_res5bbranch2bkernel
#define S69_Op_res5bbranch2bkernel_Q	14
// S70_Op_model_1res5bbranch2bConv2D_bia
#define S70_Op_model_1res5bbranch2bConv2D_bia_Q	15
// S71_Conv2d_64x64x3x3
#define S71_Conv2d_64x64x3x3_Q	12
// S72_MatAdd_64x5x5
#define S72_MatAdd_64x5x5_Q	12
// S73_AveragePool_2x2
#define S73_AveragePool_2x2_Q	12
// S74_Op_weightedaveragekerneltranspose
#define S74_Op_weightedaveragekerneltranspose_Q	15
// S75_Op_m2weightedaverageMatMul_bias
#define S75_Op_m2weightedaverageMatMul_bias_Q	15
// S76_Linear_7x256
#define S76_Linear_7x256_Q	12
// S77_SoftMax
#define S77_SoftMax_Q	15
// S78_Op_output_1
#define S78_Op_output_1_Q	15
#endif //RESNET_GRAPHINFO_H