#include <stdio.h>
#include <time.h>
#include <Windows.h>

#include "kalman_filter.h"
#include "byte_sot.h"
#include "matrix.h"

// The output of yolox
float input_tlwh_1[4] = {116.69109344, 41.40723801, 52.05139923, 162.01501465}; // Frame 1 detected
float input_tlwh_2[4] = {114.49170685, 43.87109375, 53.1997757, 161.69975281};  // Frame 2 detected
float input_tlwh_3[4] = {115.02397156, 43.32092285, 53.34561157, 162.32003784}; // Frame 3 detected
float input_xyah[4] = {0, 0, 0, 0};
float score = 0.8689026;

void tlwh_to_xyah(float *tlwh_p, float *xyah_p)
{
    xyah_p[0] = tlwh_p[0] + tlwh_p[2] / 2;
    xyah_p[1] = tlwh_p[1] + tlwh_p[3] / 2;
    xyah_p[2] = tlwh_p[2] / tlwh_p[3];
    xyah_p[3] = tlwh_p[3];
}

int main(void)
{
    printf("\n\nRunning byte_sot now...\n");
    STrack tracklet;

    // Timer
    double run_time;
    LARGE_INTEGER time_start;
    LARGE_INTEGER time_end;
    double dqFreq;
    LARGE_INTEGER f;
    QueryPerformanceFrequency(&f);
    dqFreq = (double)f.QuadPart;

    printf("\nFrame 1");
    QueryPerformanceCounter(&time_start); // Start timer
    // YOLOX output: (t,l,w,h) format
    tlwh_to_xyah(&input_tlwh_1[0], &input_xyah[0]);
    // Initialize the first frame of the tracklet
    track_init(&tracklet, &input_tlwh_1[0]);
    // Initialize KF
    kf_initiate(&input_xyah[0]);
    QueryPerformanceCounter(&time_end); // End timer
    run_time = 1000000 * (time_end.QuadPart - time_start.QuadPart) / dqFreq;
    printf("\nTime: %f us.", run_time);
    // printf("\n-------------- initial mean --------------\n");
    // mat_show(&mean[0], 1, 8);
    // printf("\n-------------- initial covariance --------------\n");
    // mat_show(&covariance[0][0], 8, 8);

    printf("\nFrame 2");
    QueryPerformanceCounter(&time_start); // Start timer
    tlwh_to_xyah(&input_tlwh_2[0], &input_xyah[0]);
    kf_predict(&mean[0], &covariance[0][0]);
    kf_update(&mean[0], &covariance[0][0], &input_xyah[0]);
    QueryPerformanceCounter(&time_end); // End timer
    run_time = 1000000 * (time_end.QuadPart - time_start.QuadPart) / dqFreq;
    printf("\nTime: %f us.", run_time);

    printf("\nFrame 3");
    QueryPerformanceCounter(&time_start);
    tlwh_to_xyah(&input_tlwh_3[0], &input_xyah[0]);
    kf_predict(&mean[0], &covariance[0][0]);
    // printf("\n-------------- predicted mean --------------\n");
    // mat_show(&mean[0], 1, 8);
    // printf("\n-------------- predicted covariance --------------\n");
    // mat_show(&covariance[0][0], 8, 8);

    kf_update(&mean[0], &covariance[0][0], &input_xyah[0]);
    // printf("\n-------------- updated mean --------------\n");
    // mat_show(&mean[0], 1, 8);
    // printf("\n-------------- updated covariance --------------\n");
    // mat_show(&covariance[0][0], 8, 8);
    QueryPerformanceCounter(&time_end); // End timer
    run_time = 1000000 * (time_end.QuadPart - time_start.QuadPart) / dqFreq;
    printf("\nTime: %f us.", run_time);

    printf("\n--- END ---\n\n\n");
    return 0;
}