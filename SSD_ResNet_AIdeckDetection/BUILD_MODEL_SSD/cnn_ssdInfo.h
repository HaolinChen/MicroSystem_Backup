#ifndef CNN_SSD_GRAPHINFO_H
#define CNN_SSD_GRAPHINFO_H
// Quantized scales can be used round_norm(val * QSCALE, QNORM) giving the real value in Q8

// S0_Op_input_1
#define S0_Op_input_1_Q	15
// S1_Op_Conv_0_weights
#define S1_Op_Conv_0_weights_Q	12
// S2_Op_constant_103
#define S2_Op_constant_103_Q	14
// S3_Conv2d_8x1x3x3_MaxPool_2x2_Relu
#define S3_Conv2d_8x1x3x3_MaxPool_2x2_Relu_Q	12
// S4_Op_Conv_3_weights
#define S4_Op_Conv_3_weights_Q	14
// S5_Op_constant_106
#define S5_Op_constant_106_Q	13
// S6_Conv2d_16x8x3x3_MaxPool_2x2_Relu
#define S6_Conv2d_16x8x3x3_MaxPool_2x2_Relu_Q	12
// S7_Op_Conv_6_weights
#define S7_Op_Conv_6_weights_Q	15
// S8_Op_constant_109
#define S8_Op_constant_109_Q	14
// S9_Conv2d_16x16x3x3_MaxPool_2x2_Relu
#define S9_Conv2d_16x16x3x3_MaxPool_2x2_Relu_Q	13
// S10_Op_Conv_9_weights
#define S10_Op_Conv_9_weights_Q	14
// S11_Op_constant_112
#define S11_Op_constant_112_Q	13
// S12_Conv2d_32x16x3x3_Relu
#define S12_Conv2d_32x16x3x3_Relu_Q	13
// S13_MaxPool_2x2
#define S13_MaxPool_2x2_Q	13
// S14_Op_Conv_11_weights
#define S14_Op_Conv_11_weights_Q	14
// S15_Op_constant_classification_headers.0.bias
#define S15_Op_constant_classification_headers.0.bias_Q	14
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
// S23_Op_constant_115
#define S23_Op_constant_115_Q	13
// S24_Conv2d_64x32x3x3_Relu
#define S24_Conv2d_64x32x3x3_Relu_Q	13
// S25_MaxPool_2x2
#define S25_MaxPool_2x2_Q	13
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
// S35_Op_constant_118
#define S35_Op_constant_118_Q	13
// S36_Conv2d_128x64x3x3_Relu
#define S36_Conv2d_128x64x3x3_Relu_Q	13
// S37_MaxPool_2x2
#define S37_MaxPool_2x2_Q	13
// S38_Op_Conv_21_weights
#define S38_Op_Conv_21_weights_Q	15
// S39_Op_constant_classification_headers.2.bias
#define S39_Op_constant_classification_headers.2.bias_Q	15
// S40_Conv2d_18x128x3x3
#define S40_Conv2d_18x128x3x3_Q	12
// S41_Op_output_5
#define S41_Op_output_5_Q	12
// S42_Op_Conv_22_weights
#define S42_Op_Conv_22_weights_Q	15
// S43_Op_constant_regression_headers.2.bias
#define S43_Op_constant_regression_headers.2.bias_Q	15
// S44_Conv2d_24x128x3x3
#define S44_Conv2d_24x128x3x3_Q	12
// S45_Op_output_6
#define S45_Op_output_6_Q	12
// S46_Op_Conv_24_weights
#define S46_Op_Conv_24_weights_Q	15
// S47_Op_constant_121
#define S47_Op_constant_121_Q	13
// S48_Conv2d_128x128x3x3_Relu
#define S48_Conv2d_128x128x3x3_Relu_Q	13
// S49_Op_Conv_26_weights
#define S49_Op_Conv_26_weights_Q	15
// S50_Op_constant_classification_headers.3.bias
#define S50_Op_constant_classification_headers.3.bias_Q	15
// S51_Conv2d_18x128x3x3
#define S51_Conv2d_18x128x3x3_Q	12
// S52_Op_output_7
#define S52_Op_output_7_Q	12
// S53_Op_Conv_27_weights
#define S53_Op_Conv_27_weights_Q	15
// S54_Op_constant_regression_headers.3.bias
#define S54_Op_constant_regression_headers.3.bias_Q	15
// S55_Conv2d_24x128x3x3
#define S55_Conv2d_24x128x3x3_Q	12
// S56_Op_output_8
#define S56_Op_output_8_Q	12
#endif //CNN_SSD_GRAPHINFO_H