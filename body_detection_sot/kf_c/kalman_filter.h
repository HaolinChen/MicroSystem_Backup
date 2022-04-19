#ifndef KF_H
#define KF_H

extern float chi2inv95[9];
extern float motion_mat[8][8]; // F
extern float update_mat[4][8]; // H
extern float update_mat_T[8][4];
extern float mean[8];
extern float covariance[8][8];
extern float std_weight_position;
extern float std_weight_velocity;

// Kalman filter
void kf_initiate(float *xyah_p);
void kf_predict(float *mean_p, float *covariance_p);
void kf_update(float *mean_p, float *covariance_p, float *xyah_p);
void kf_mapping(float *mean_p, float *covariance_p, float *mean_map_p, float *covariance_map_p);

#endif