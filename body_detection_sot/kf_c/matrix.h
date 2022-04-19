#ifndef MATRIX_H
#define MATRIX_H

// Matrix funtion
void diag_square(float *covariance_p, float *std_p, int size);
void mat_multi(float *mat_a, float *mat_b, float *mat_c, int height, int mid, int width);
void mat_multi_triple(float *mat_a, float *mat_b, float *mat_c, float *mat_d, int height, int mid1, int mid2, int width);
void mat_trans(float *mat_a, float *mat_a_t, int height, int width);
void mat_add(float *mat_a, float *mat_b, int height, int width);
void mat_minus(float *mat_a, float *mat_b, float *mat_c, int height, int width);
void mat_copy(float *mat_a, float *mat_b, int height, int width);
void mat_show(float *mat_a, int height, int width);
void mat_zeros(float *mat_a, int height, int width);
float mat_value(float *mat_a, int order);
float laplace_expansion(float *mat_a, int r, int c, int order);
void mat_adjoint(float *mat_a, float *mat_b, int order);
void mat_inverse(float *mat_a, float *mat_b, int order);

#endif