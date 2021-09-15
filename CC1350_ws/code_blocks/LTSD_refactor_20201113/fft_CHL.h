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
void    add(complex,complex,complex *);   /*�����ӷ�*/
void    mul(complex,complex,complex *);   /*�����˷�*/
void    sub(complex,complex,complex *);   /*��������*/
void    divi(complex,complex,complex *);  /*��������*/
void    output(complex* x);  /*������*/
void    output_abs(complex* x,double* y);





#endif // _fft_CHL_H_
