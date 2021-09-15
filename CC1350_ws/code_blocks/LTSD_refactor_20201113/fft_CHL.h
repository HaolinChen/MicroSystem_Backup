#ifndef _fft_CHL_H_
#include   <math.h>
#include "state.h"

#define size_x  fft_size
#define PI    3.141592653
//#define NFFT2 size_x/2+1
typedef   struct
{
    double   real;
    double   img;
} complex;


void    fft(complex* x,complex* W);
void    ifft(complex* x,complex* W);
void    initW(complex* W); /* Initialize the transformation kernel */
void    change(complex* x);
void    add(complex,complex,complex *);   /*复数加法*/
void    mul(complex,complex,complex *);   /*复数乘法*/
void    sub(complex,complex,complex *);   /*复数减法*/
void    divi(complex,complex,complex *);  /*复数除法*/
void    output(complex* x);  /*输出结果*/
void    output_abs(complex* x,double* y);





#endif // _fft_CHL_H_
