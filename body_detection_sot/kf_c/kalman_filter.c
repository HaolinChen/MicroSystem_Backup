/*
 * Copyright (C) 2022 Haolinchen
 * All rights reserved.
 *
 * A simple Kalman filter for tracking bounding boxes in image space.
 * The 8-dimensional state space:
 *          cx, cy, a, h, vx, vy, va, vh
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "kalman_filter.h"
#include "matrix.h"

/*
Table for the 0.95 quantile of the chi-square distribution with N degrees of
freedom (contains values for N=1, ..., 9). Taken from MATLAB/Octave's chi2inv
function and used as Mahalanobis gating threshold.
*/
float chi2inv95[9] = {3.8415, 5.9915, 7.8147, 9.4877, 11.070, 12.592, 14.067, 15.507, 16.919};
// State transition matrix F: 8x8
float motion_mat[8][8] = {
    {1, 0, 0, 0, 1, 0, 0, 0},
    {0, 1, 0, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 0, 1, 0},
    {0, 0, 0, 1, 0, 0, 0, 1},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 1}};
// State transition matrix F^T: 8x8
float motion_mat_T[8][8] = {
    {1, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {1, 0, 0, 0, 1, 0, 0, 0},
    {0, 1, 0, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 0, 1, 0},
    {0, 0, 0, 1, 0, 0, 0, 1}};
// Measurement matrix H: 4x8
float update_mat[4][8] = {
    {1, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0}};
// Measurement matrix H^T: 8x4
float update_mat_T[8][4] = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}};
// From kf_initiate
// cx, cy, a, h, vx, vy, va, vh
float mean[8] = {0, 0, 0, 0, 0, 0, 0, 0};
float mean_Hx[4] = {0, 0, 0, 0};

float covariance[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}};
float covariance_noise[4][4] = {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}};

/*
Motion and observation uncertainty are chosen relative to the current state estimate.
These weights control the amount of uncertainty in the model.
This is a bit hacky.
*/

float std_weight_position = 0.05;
float std_weight_velocity = 0.00625;

/*
Initiate track from unassociated measurement.
    Parameters
    ----------
    float *xyah_p:
        Bounding box coordinates (x, y, a, h) with center position (x, y),
        aspect ratio a, and height h.
    Output
    ----------
    float mean[8]:
        [x,y,a,h,0,0,0,0]
    float covariance[8][8]
*/

void kf_initiate(float *xyah_p)
{

    // Initialize mean
    for (int i = 0; i < 4; i++)
    {
        mean[i] = xyah_p[i];
    }
    float std[8] = {
        2 * std_weight_position * xyah_p[0], // the center point x
        2 * std_weight_position * xyah_p[1], // the center point y
        1 * xyah_p[2],                       // the ratio of width / height
        2 * std_weight_position * xyah_p[3], // the height
        10 * std_weight_velocity * xyah_p[0],
        10 * std_weight_velocity * xyah_p[1],
        0.1 * xyah_p[2],
        10 * std_weight_velocity * xyah_p[3]};
    // Initialize covariance
    diag_square(&covariance[0][0], &std[0], 8);
}

/*
Run Kalman filter prediction step.
----------
Parameters:
    mean : ndarray
        The state's mean vector (8 dimensional array).
    covariance : ndarray
        The state's covariance matrix (8x8 dimensional).
*/

// i.e. FPF^T
float covariance_FPF[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}};

void kf_predict(float *mean_p, float *covariance_p)
{
    // std = np.r_[std_pos, std_vel]
    float std[8] = {
        std_weight_position * mean_p[3],
        std_weight_position * mean_p[3],
        0.01,
        std_weight_position * mean_p[3],
        std_weight_velocity * mean_p[3],
        std_weight_velocity * mean_p[3],
        0.00001,
        std_weight_velocity * mean_p[3]};

    // noise matrix Q
    float *covariance_updated = (float *)malloc(sizeof(float) * 8 * 8);
    mat_zeros(covariance_updated, 8, 8);
    diag_square(covariance_updated, &std[0], 8);
    // mean predict : x' = Fx
    float *mean_updated = (float *)malloc(sizeof(float) * 8);
    mat_zeros(mean_updated, 1, 8);
    mat_multi(mean_p, &motion_mat_T[0][0], mean_updated, 1, 8, 8);
    // covariance predict : P' = FPF^T + Q
    mat_multi_triple(&motion_mat[0][0], covariance_p, &motion_mat_T[0][0], &covariance_FPF[0][0], 8, 8, 8, 8);
    mat_add(covariance_updated, &covariance_FPF[0][0], 8, 8);
    // Copy output
    mat_copy(mean_updated, &mean[0], 1, 8);
    mat_copy(covariance_updated, &covariance[0][0], 8, 8);

    // Free storage
    free(covariance_updated);
    covariance_updated = NULL;
    free(mean_updated);
    mean_updated = NULL;
}

float covariance_HP[4][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}};
// Map the covariance matrix to the measurement space, i.e. HP'H^T
float covariance_HPH[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}};

/*
Mapping state distribution to measurement space.
----------
Parameters:
    mean : ndarray
        The state's mean vector (8 dimensional array).
    covariance : ndarray
        The state's covariance matrix (8x8 dimensional).
----------
Output:
    mean_map_p : ndarray
        mean_map_p = Hx' (4 dimensional array).
    covariance_map_p : ndarray
        covariance_map_p = HP'H^T + R (4x4 dimensional).
*/

void kf_mapping(float *mean_p, float *covariance_p, float *mean_map_p, float *covariance_map_p)
{

    float std[4] = {
        std_weight_position * mean_p[3],
        std_weight_position * mean_p[3],
        1e-1,
        std_weight_position * mean_p[3]};
    // R: the noise covariance during the measurement
    diag_square(covariance_map_p, &std[0], 4);
    mat_multi(&update_mat[0][0], mean_p, mean_map_p, 4, 8, 1);
    // Map the covariance matrix to the measurement space, i.e. HP'H^T
    // mat_trans(&update_mat[0][0], &update_mat_T[0][0], 4, 8);
    mat_multi_triple(&update_mat[0][0], covariance_p, &update_mat_T[0][0], &covariance_HPH[0][0], 4, 8, 8, 4);
    // mean_map_p = Hx' and covariance_map_p = HP'H^T + R
    mat_add(covariance_map_p, &covariance_HPH[0][0], 4, 4);
}

/*
Run Kalman filter correction step.
Estimate the latest results from estimates and observations.
----------
Parameters:
    mean : ndarray
        The state's mean vector (8 dimensional array).
    covariance : ndarray
        The state's covariance matrix (8x8 dimensional).
*/

void kf_update(float *mean_p, float *covariance_p, float *xyah_p)
{
    // mean_map_p = Hx' and covariance_map_p = HP'H^T + R
    float *mean_map_p = (float *)malloc(sizeof(float) * 8);
    mat_zeros(mean_map_p, 1, 8);
    float *covariance_map_p = (float *)malloc(sizeof(float) * 4 * 4);
    // float covariance_map_p[16];
    mat_zeros(covariance_map_p, 4, 4);
    kf_mapping(mean_p, covariance_p, mean_map_p, covariance_map_p);
    // S = HP'H^T + R
    float *s_inverse_p = (float *)malloc(sizeof(float) * 4 * 4);
    mat_zeros(s_inverse_p, 4, 4);
    mat_inverse(covariance_map_p, s_inverse_p, 4);
    float *s_inverse_T_p = (float *)malloc(sizeof(float) * 4 * 4);
    mat_zeros(s_inverse_T_p, 4, 4);
    mat_trans(s_inverse_p, s_inverse_T_p, 4, 4);
    // Calculate Kalman Gain K = P'H^T(S^-1)^T
    float *kalman_gain_p = (float *)malloc(sizeof(float) * 8 * 4);
    mat_zeros(kalman_gain_p, 8, 4);
    mat_multi_triple(covariance_p, &update_mat_T[0][0], s_inverse_T_p, kalman_gain_p, 8, 8, 4, 4);
    // y = z - Hx' (4 dimensional array)
    mat_minus(xyah_p, mean_map_p, mean_map_p, 1, 4);
    // Update: x = x' + Ky (8 dimensional array)
    float *kalman_gain_T_p = (float *)malloc(sizeof(float) * 4 * 8);
    mat_zeros(kalman_gain_T_p, 4, 8);
    mat_trans(kalman_gain_p, kalman_gain_T_p, 8, 4);
    float *mat_ky_p = (float *)malloc(sizeof(float) * 8);
    mat_zeros(mat_ky_p, 1, 8);
    mat_multi(mean_map_p, kalman_gain_T_p, mat_ky_p, 1, 4, 8);
    mat_add(mean_p, mat_ky_p, 1, 8);
    // Update: P = (I - KH)P' (8*8 dimensional array)
    float *mat_khp_p = (float *)malloc(sizeof(float) * 8 * 8);
    mat_zeros(mat_khp_p, 8, 8);
    mat_multi_triple(kalman_gain_p, covariance_map_p, kalman_gain_T_p, mat_khp_p, 8, 4, 4, 8);
    mat_minus(covariance_p, mat_khp_p, covariance_p, 8, 8);

    // Free storage
    free(mean_map_p);
    mean_map_p = NULL;
    free(covariance_map_p);
    covariance_map_p = NULL;
    free(s_inverse_p);
    s_inverse_p = NULL;
    free(s_inverse_T_p);
    s_inverse_p = NULL;
    free(kalman_gain_p);
    kalman_gain_p = NULL;
    free(kalman_gain_T_p);
    kalman_gain_T_p = NULL;
    free(mat_ky_p);
    mat_ky_p = NULL;
    free(mat_khp_p);
    mat_khp_p = NULL;
}
