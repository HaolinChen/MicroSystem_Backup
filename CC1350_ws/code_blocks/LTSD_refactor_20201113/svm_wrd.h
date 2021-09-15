#ifndef _SVM_WRD_H
#define _SVM_WRD_H

#include "stm32f4xx.h"
#include "stdio.h"
#include "math.h"


#define VECTOR_DIM	1

#define SVM_VECTORS	40
//#define QMATRIX_COLUMN	(SVM_VECTORS*2)
#define QMATRIX_ROW	(SVM_VECTORS*2)

#define RBF_GAMMA 10

extern u32 Select_WorkingSet_Time[5000];
extern u32 Garden_Change_Time[5000];
extern float G_MaxMin[5000];


void Q_Matrix_Init(float VectorsMatrix[SVM_VECTORS][VECTOR_DIM]);
void Y_Matrix_Init(void);
void G_Matrix_Init(float *ResultMatrix, float epsilon);
void Alpha2_Matrix_Init(void);
//void Update_Alpha2Status(float C);
int Select_WorkingSet(int *select_i, int *select_j, float epsilon, float C);
void SMO_Slover(float C, float epsilon);

int SMO_GetIteration(void);

float Calculate_Rho(float C);
void Calculate_Alpha(void);
float *Get_AlphaMatrix(void);

float SVR_Predict(float VectorsMatrix[SVM_VECTORS][VECTOR_DIM], float *PreX);

#endif
