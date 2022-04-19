#include "kalman_filter.h"
#include "sot_tracker.h"

void track_init(STrack* track_p, float* first_tlwh)
{
    for(int i=0;i<4;i++)
    {
        track_p->tlwh[i] = first_tlwh[i];
    }
    track_p->state = TRACKED;
}