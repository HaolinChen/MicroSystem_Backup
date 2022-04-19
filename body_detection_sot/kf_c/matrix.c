#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "matrix.h"

// Square and transform to a diagonal matrix
void diag_square(float *covariance_p, float *std_p, int size)
{
    for (int i = 0; i < size; i++)
    {
        covariance_p[i * size + i] = std_p[i] * std_p[i];
    }
}

// Matrix multiply
void mat_multi(float *mat_a, float *mat_b, float *mat_c, int height, int mid, int width)
{
    int i, j, k;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            mat_c[i * width + j] = 0;
            for (k = 0; k < mid; k++)
            {
                mat_c[i * width + j] = mat_c[i * width + j] + mat_a[i * mid + k] * mat_b[k * width + j];
            }
        }
    }
}

// Three matrix multiply
void mat_multi_triple(float *mat_a, float *mat_b, float *mat_c, float *mat_d, int height, int mid1, int mid2, int width)
{
    float *mat_temp = (float *)malloc(sizeof(float) * height * mid2);
    mat_zeros(mat_temp, height, mid2);
    if (mat_temp == 0)
    {
        printf("Create mat_temp failed.\n");
        exit(0);
    }
    mat_multi(mat_a, mat_b, mat_temp, height, mid1, mid2);
    mat_multi(mat_temp, mat_c, mat_d, height, mid2, width);
    free(mat_temp);
    mat_temp = NULL;
}

/*
Matrix transpose
----------
Parameters:
    mat_a : height * width
    mat_a_t : width * height
*/
void mat_trans(float *mat_a, float *mat_a_t, int height, int width)
{
    int i, j;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            mat_a_t[j * height + i] = mat_a[i * width + j];
        }
    }
}

/*
Matrix add
Save results to mat_a
----------
Parameters:
    mat_a : height * width
    mat_b : height * width
*/
void mat_add(float *mat_a, float *mat_b, int height, int width)
{
    int i, j;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            mat_a[i * width + j] = mat_a[i * width + j] + mat_b[i * width + j];
        }
    }
}

/*
Matrix minus
Save results to mat_c
----------
Parameters:
    mat_a : height * width
    mat_b : height * width
*/
void mat_minus(float *mat_a, float *mat_b, float *mat_c, int height, int width)
{
    int i, j;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            mat_c[i * width + j] = mat_a[i * width + j] - mat_b[i * width + j];
        }
    }
}

// Copy matrix A  to matrix B
void mat_copy(float *mat_a, float *mat_b, int height, int width)
{
    int i, j;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            mat_b[i * width + j] = mat_a[i * width + j];
        }
    }
}

// Zero the matrix A
void mat_zeros(float *mat_a, int height, int width)
{
    int i, j;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            mat_a[i * width + j] = 0;
        }
    }
}

// Calculate the determinant of a matrix
float mat_value(float *mat_a, int order)
{
    float result = 0, cofactor = 0;
    int sign = 1, i;

    if (order == 1)
    {
        result = mat_a[0];
    }
    else
        for (i = 0; i < order; i++)
        {
            // Expand by the first column
            if (mat_a[i * order])
            {
                cofactor = laplace_expansion(mat_a, i, 0, order);
                result += sign * mat_a[i * order] * cofactor;
            }
            sign *= -1;
        }
    // printf("%f\n", result);

    return result;
}

// For the original mat_a, start laplace expansion at (r,c)
float laplace_expansion(float *mat_a, int r, int c, int order)
{
    // printf("\n In laplace_expansion \n");
    float result = 0;
    int temp_i, temp_j, i, j;
    int order_new = order - 1;
    float *mat_temp_laplace = (float *)malloc(sizeof(float) * order_new * order_new);
    mat_zeros(mat_temp_laplace, order_new, order_new);

    for (i = 0; i < order; i++)
    {
        for (j = 0; j < order; j++)
        {
            if (i == r || j == c)
            {
                ;
            }
            else
            {
                if (i > r)
                {
                    temp_i = i - 1;
                }
                else
                {
                    temp_i = i;
                }
                if (j > c)
                {
                    temp_j = j - 1;
                }
                else
                {
                    temp_j = j;
                }
                mat_temp_laplace[temp_i * order_new + temp_j] = mat_a[i * order + j];
            }
        }
    }

    if (order_new >= 1)
        result = mat_value(mat_temp_laplace, order_new);

    free(mat_temp_laplace);
    mat_temp_laplace = NULL;
    return result;
}

// Generate adjoint matrix mat_b from mat_a
void mat_adjoint(float *mat_a, float *mat_b, int order)
{
    float result = 0;
    int i, j;

    for (i = 0; i < order; i++)
    {
        for (j = 0; j < order; j++)
        {
            if (order == 1 & i == 0 & j == 0)
            {
                mat_b[0] = 1;
            }
            else
            {
                mat_b[i * order + j] = pow(-1, i + j) * laplace_expansion(mat_a, j, i, order);
            }
        }
    }
}

// Generate inverse matrix mat_b from mat_a
void mat_inverse(float *mat_a, float *mat_b, int order)
{
    int i, j;
    float *mat_temp = (float *)malloc(sizeof(float) * order * order);
    mat_zeros(mat_temp, order, order);

    float val = mat_value(mat_a, order);
    // printf(" val:   %f", val);
    mat_adjoint(mat_a, mat_temp, order);

    for (i = 0; i < order; i++)
    {
        for (j = 0; j < order; j++)
        {
            mat_b[i * order + j] = mat_temp[i * order + j] / val;
        }
    }
    free(mat_temp);
    mat_temp = NULL;
}

void mat_show(float *mat_a, int height, int width)
{
    // printf("\nShowing matrix......\n");
    int i, j;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            printf("%f\t", mat_a[i * width + j]);
        }
        printf("\n");
    }
}