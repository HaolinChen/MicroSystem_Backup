#ifndef CNN_SSD_GRAPHINFO_H
#define CNN_SSD_GRAPHINFO_H
// Quantized scales can be used round_norm(val * QSCALE, QNORM) giving the real value in Q8

// S0_Op_input_1
#define S0_Op_input_1_Q	14
// S1_Op_Conv_0_weights
#define S1_Op_Conv_0_weights_Q	10
// S2_Op_constant_86
#define S2_Op_constant_86_Q	14
// S3_Conv2d_8x1x3x3_MaxPool_2x2_Relu
#define S3_Conv2d_8x1x3x3_MaxPool_2x2_Relu_Q	10
// S4_Op_Conv_3_weights
#define S4_Op_Conv_3_weights_Q	15
// S5_Op_constant_89
#define S5_Op_constant_89_Q	14
// S6_Conv2d_16x8x3x3_MaxPool_2x2_Relu
#define S6_Conv2d_16x8x3x3_MaxPool_2x2_Relu_Q	12
// S7_Op_Conv_6_weights
#define S7_Op_Conv_6_weights_Q	14
// S8_Op_constant_92
#define S8_Op_constant_92_Q	13
// S9_Conv2d_16x16x3x3_MaxPool_2x2_Relu
#define S9_Conv2d_16x16x3x3_MaxPool_2x2_Relu_Q	13
// S10_Op_Conv_9_weights
#define S10_Op_Conv_9_weights_Q	13
// S11_Op_constant_95
#define S11_Op_constant_95_Q	13
// S12_Conv2d_32x16x3x3_Relu
#define S12_Conv2d_32x16x3x3_Relu_Q	12
// S13_MaxPool_2x2
#define S13_MaxPool_2x2_Q	12
// S14_Op_Conv_11_weights
#define S14_Op_Conv_11_weights_Q	14
// S15_Op_constant_classification_headers.0.bias
#define S15_Op_constant_classification_headers.0.bias_Q	15
// S16_Conv2d_18x32x3x3
#define S16_Conv2d_18x32x3x3_Q	11
// S17_Op_output_1
#define S17_Op_output_1_Q	11
// S18_Op_Conv_12_weights
#define S18_Op_Conv_12_weights_Q	15
// S19_Op_constant_regression_headers.0.bias
#define S19_Op_constant_regression_headers.0.bias_Q	15
// S20_Conv2d_24x32x3x3
#define S20_Conv2d_24x32x3x3_Q	12
// S21_Op_output_2
#define S21_Op_output_2_Q	12
// S22_Op_Conv_14_weights
#define S22_Op_Conv_14_weights_Q	15
// S23_Op_constant_98
#define S23_Op_constant_98_Q	13
// S24_Conv2d_64x32x3x3_Relu
#define S24_Conv2d_64x32x3x3_Relu_Q	12
// S25_MaxPool_2x2
#define S25_MaxPool_2x2_Q	12
// S26_Op_Conv_16_weights
#define S26_Op_Conv_16_weights_Q	14
// S27_Op_constant_classification_headers.1.bias
#define S27_Op_constant_classification_headers.1.bias_Q	15
// S28_Conv2d_18x64x3x3
#define S28_Conv2d_18x64x3x3_Q	11
// S29_Op_output_3
#define S29_Op_output_3_Q	11
// S30_Op_Conv_17_weights
#define S30_Op_Conv_17_weights_Q	15
// S31_Op_constant_regression_headers.1.bias
#define S31_Op_constant_regression_headers.1.bias_Q	15
// S32_Conv2d_24x64x3x3
#define S32_Conv2d_24x64x3x3_Q	12
// S33_Op_output_4
#define S33_Op_output_4_Q	12
// S34_Op_Conv_19_weights
#define S34_Op_Conv_19_weights_Q	15
// S35_Op_constant_101
#define S35_Op_constant_101_Q	13
// S36_Conv2d_128x64x3x3_Relu
#define S36_Conv2d_128x64x3x3_Relu_Q	12
// S37_Op_Conv_21_weights
#define S37_Op_Conv_21_weights_Q	14
// S38_Op_constant_classification_headers.2.bias
#define S38_Op_constant_classification_headers.2.bias_Q	15
// S39_Conv2d_18x128x3x3
#define S39_Conv2d_18x128x3x3_Q	11
// S40_Op_output_5
#define S40_Op_output_5_Q	11
// S41_Op_Conv_22_weights
#define S41_Op_Conv_22_weights_Q	15
// S42_Op_constant_regression_headers.2.bias
#define S42_Op_constant_regression_headers.2.bias_Q	15
// S43_Conv2d_24x128x3x3
#define S43_Conv2d_24x128x3x3_Q	12
// S44_Op_output_6
#define S44_Op_output_6_Q	12
#endif //CNN_SSD_GRAPHINFO_H