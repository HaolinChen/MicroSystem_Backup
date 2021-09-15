#include "fft_CHL.h"



/* Base-2 fft */
void fft(complex* x,complex* W)
{
    int   i=0,j=0,k=0,l=0;
    complex   up,down,product;
    change(x);
    for(i=0; i<log(size_x)/log(2); i++) /* 一级蝶形运算 */
    {
        l=1<<i;
        for(j=0; j<size_x; j+=2*l) /* 一组蝶形运算 */
        {
            for(k=0; k<l; k++) /* 一个蝶形运算 */
            {
                mul(x[j+k+l],W[size_x*k/2/l],&product);
                add(x[j+k],product,&up);
                sub(x[j+k],product,&down);
                x[j+k]=up;
                x[j+k+l]=down;
            }
        }
    }
}
void   ifft(complex* x,complex* W)
{
    int   i=0,j=0,k=0,l=size_x;
    complex   up,down;
    for(i=0; i<(int)(log(size_x)/log(2)); i++) /* 一级蝶形运算 */
    {
        l/=2;
        for(j=0; j<size_x; j+=2*l) /* 一组蝶形运算 */
        {
            for(k=0; k<l; k++) /* 一个蝶形运算 */
            {
                add(x[j+k],x[j+k+l],&up);
                up.real/=2;
                up.img/=2;
                sub(x[j+k],x[j+k+l],&down);
                down.real/=2;
                down.img/=2;
                divi(down,W[size_x*k/2/l],&down);
                x[j+k]=up;
                x[j+k+l]=down;
            }
        }
    }
    change(x);
}
/* 初始化变化核 */
void initW(complex* W)
{
    int i;
    //W=(complex*)malloc(sizeof(complex)*size_x);
    for(i=0; i<size_x; i++)
    {
        W[i].real=cos(2*PI/size_x*i);
        W[i].img=-1*sin(2*PI/size_x*i);
    }
}
/* 变址计算，将 x(n) 码位倒置 */
void   change(complex* x)
{
    complex   temp;
    unsigned   short   i=0,j=0,k=0;
    double   t;
    for(i=0; i<size_x; i++)
    {
        k=i;
        j=0;
        t=(log(size_x)/log(2));
        while(   (t--)>0   )
        {
            j=j<<1;
            j|=(k   &   1);
            k=k>>1;
        }
        if(j>i)
        {
            temp=x[i];
            x[i]=x[j];
            x[j]=temp;
        }
    }
}
void   output(complex* x)   /* 输出结果 */
{
    int   i;
    printf("The   result   are   as   follows\n");
    for(i=0; i<size_x; i++)
    {
        printf("%.4f",x[i].real);
        if(x[i].img>=0.0001) // >0
            printf("+%.4fj\n",x[i].img);
        else   if(fabs(x[i].img)<0.0001) // =0
            printf("\n");
        else
            printf("%.4fj\n",x[i].img); // <0
    }
}

void    output_abs(complex* x,double* y)
{
    int   i;
    printf("The   abs result   are   as   follows\n");
    for(i=0; i<size_x; i++) //  NFFT2 = size_x/2+1
    {
        y[i] = sqrt( x[i].real*x[i].real + x[i].img*x[i].img);
        printf("%.4f\n",y[i]);
    }
}


void   add(complex   a,complex   b,complex   *c)
{
    c->real=a.real+b.real;
    c->img=a.img+b.img;
}
void   mul(complex   a,complex   b,complex   *c)
{
    c->real=a.real*b.real   -   a.img*b.img;
    c->img=a.real*b.img   +   a.img*b.real;
}
void   sub(complex   a,complex   b,complex   *c)
{
    c->real=a.real-b.real;
    c->img=a.img-b.img;
}
void   divi(complex   a,complex   b,complex   *c)
{
    c->real=(   a.real*b.real+a.img*b.img   )/(
                b.real*b.real+b.img*b.img);
    c->img=(   a.img*b.real-a.real*b.img)/(b.real*b.real+b.img*b.img);
}
