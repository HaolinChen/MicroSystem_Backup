#include <stdio.h>
#include <stdlib.h>
#include "fft_CHL.h"

double x_real[size_x] = {1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8};
complex x[size_x];
complex W[size_x];
double x_abs[size_x]; // optiional: save the half data(NFFT2) since the specturm is Symmetrical
int main()
{
    printf("Hello world!\n");
    int i;
    for(i=0; i<size_x; i++)
    {
        x[i].real = x_real[i];
        x[i].img = 0;
    }
    initW(&W[0]);
    fft(&x[0],&W[0]);
    output(&x[0]);
    output_abs(&x[0],&x_abs[0]);
    return 0;
}
