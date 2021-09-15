#include "LTSD_chl.h"
#include "FFTCode.h"
#include "fft_CHL.h"
Matrix* compute(LTSD* ltsd,Matrix* signal, int K,int T) //return one featurevector
{
    double ltsd_new[K][1];
    Array_zero(K,1,&ltsd_new[0][0]);
    Matrix* ltsd_vector = Matrix_gen(K,1,&ltsd_new[0][0]);
    //Matrix* ltsd_vector = (Matrix*)malloc(sizeof(Matrix)); // save the result
    //ltsd_vector->row = 1;
    //ltsd_vector->column = K ;
    double N = ltsd->fftsize ;
    int NFFT2 = N/2 +1 ;
    int T_now = T;
    double ltse[NFFT2][1];
    Array_zero(NFFT2,1,&ltse[0][0]);
    Matrix* ltse_vector = Matrix_gen(NFFT2,1,&ltse[0][0]);
    if((T_now<ltsd->order) || (T_now+ltsd->order>ltsd->windownum)||(T_now+ltsd->order==ltsd->windownum))
    {
        ;
    }
    else
    {
        ltse_vector = ltse_CHL(ltsd,signal,T_now);
    }
    int mk[K+1];
    int i,j;
    double sum=0;
    for(i=0;i<K+1;i++)
    {
        mk[i] = N*i/(2*K)+1;
    }
    for(j=0;j<K;j++)
    {
        for(i=mk[j];i<mk[j+1]-1;i++)
        {
            sum = sum + ltse_vector->data[i];
        }
        ltsd_vector->data[j] = sum*2*K/N;
    }
    return ltsd_vector;
}

Matrix* ltse_CHL(LTSD* ltsd,Matrix* signal,int T)
{
    int NFFT2 = ltsd->fftsize/2+1;
    double maxmag[NFFT2][1];
    double amp[NFFT2][1];
    double maxamp[NFFT2][1];
    Array_zero(NFFT2,1,&maxmag[0][0]);
    Array_zero(NFFT2,1,&amp[0][0]);
    Matrix* maxmag_vector = Matrix_gen(NFFT2,1,&maxmag[0][0]);
    Matrix* amp_vector = Matrix_gen(NFFT2,1,&amp[0][0]);
    Matrix* maxamp_vector = Matrix_gen(NFFT2,1,&maxamp[0][0]);
    int idx ;
    /*
    for(idx= T-ltsd->order; idx<T+ltsd->order;idx++)
    {
        amp_vector = get_amplitude(ltsd,signal,idx);
        maxamp_vector = max_vector(maxmag_vector,amp_vector);
        maxmag_vector = maxamp_vector;
    }
    */
    for(idx= 0; idx<ltsd->order*2+1;idx++)
    {
        amp_vector = get_amplitude(ltsd,signal,idx);
        maxamp_vector = max_vector(maxmag_vector,amp_vector);
        maxmag_vector = maxamp_vector;
    }
    return maxamp_vector;
}

Matrix* get_amplitude(LTSD* ltsd,Matrix* signal,int idx)
{
    complex x[fft_size];
    complex W[fft_size];
    int NFFT2 = ltsd->fftsize/2+1;
    double final_output[NFFT2];
    int frame_now = idx;
    int i;
    //generate the input data
    Array_zero(NFFT2,1,&final_output[0]);
    for (i=0; i<fft_size; i++)
    {
        if(i < frame_size)
        {
            x[i].real = signal->data[frame_now*frame_size+i];
        }
        else
        {
            x[i].real = 0;
        }
        x[i].img = 0;
	}
    initW(&W[0]);
    fft(&x[0],&W[0]);
    output_abs(&x[0],&final_output[0]);
    //double final_output[frame_size];
	Matrix* final_vector = Matrix_gen(NFFT2,1,&final_output[0]);
	return final_vector;
}

Matrix* max_vector(Matrix* a,Matrix* b)
{
    int row = a->row;
    int column = a->column;
    double result[row][column];
    Array_zero(row,column,&result[0][0]);

    int i,j;
    for(i=0;i<row;i++)
    {
        for(j=0;j<column;j++)
        {
            if(a->data[i*column+j]>b->data[i*column+j])
            {
                result[i][j] = a->data[i*column+j];
            }
            else
            {
                result[i][j] = b->data[i*column+j];
            }
        }
    }
    Matrix* result_vector = Matrix_gen(row,column,&result[0][0]);
    return result_vector;
}

void Array_zero(int row,int column,double* a)
{
    int size = row*column;
	int i;
	for (i = 0; i<size; i++)
    {
		a[i] = 0;
	}
}
