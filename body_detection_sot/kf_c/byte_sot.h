#ifndef BYTE_SOT_H
#define BYTE_SOT_H


#define TRACKED 1
#define LOST 0 
typedef struct
{
    float tlwh[4];
    float mean;
    float covariance;
    int is_activated;
    int state; // TRACKED or LOST
    float score;
} STrack;

void track_init(STrack* track_p, float* first_tlwh);

#endif