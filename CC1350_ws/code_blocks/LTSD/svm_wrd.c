#include "svm_wrd.h"

//ʱ���������
u32 Select_WorkingSet_Time[5000]={0};
u32 Garden_Change_Time[5000]={0};
float G_MaxMin[5000]={0};

float Q_Matrix[QMATRIX_ROW][SVM_VECTORS];
//float QD_Matrix[QMATRIX_ROW];
signed char Y_Matrix[QMATRIX_ROW];
float G_Matrix[QMATRIX_ROW];

//�����ݶȾ���
float Quad_Matrix[SVM_VECTORS][SVM_VECTORS];

float Alpha_Matrix[SVM_VECTORS];
float Alpha2_Matrix[QMATRIX_ROW];
//int Alpha2_Status[QMATRIX_ROW];

//enum { LOWER_BOUND, UPPER_BOUND, FREE };

#define INF	C

//����������
float Dot(float *A, float *B)
{
	float sum = 0;
	int i = 0;

	for (i = 0; i < VECTOR_DIM; i++)
	{
		sum += (*A)*(*B);
		A++;
		B++;
	}
	return sum;
}

//RBF�˺�������
float Kernel_RBF(float *A, float *B, float gamma)
{
	return exp(-gamma*(Dot(A, A) + Dot(B, B) - 2 * Dot(A, B)));
}
//���Ժ˺�������
float Kernel_Linear(float *A, float *B)
{
	return Dot(A, B);
}

//Q�����ʼ����Q_Matrix=yi*yj*K(i,j)
void Q_Matrix_Init(float VectorsMatrix[SVM_VECTORS][VECTOR_DIM])
{
	int i, j;
	for (i = 0; i < SVM_VECTORS; i++)
	{
		for (j = 0; j < SVM_VECTORS; j++)
		{
			Q_Matrix[i][j] = Kernel_RBF(VectorsMatrix[i], VectorsMatrix[j], RBF_GAMMA);
			Q_Matrix[i + SVM_VECTORS][j] = -Q_Matrix[i][j];
			//Q_Matrix[i][j + SVM_VECTORS] = -Q_Matrix[i][j];
			//Q_Matrix[i + SVM_VECTORS][j + SVM_VECTORS] = Q_Matrix[i][j];
		}
		//QD_Matrix[i] = Q_Matrix[i][i];
		//QD_Matrix[i + SVM_VECTORS] = Q_Matrix[i][i];
	}

	//�����ݶȾ���
	for (i = 0; i < SVM_VECTORS; i++)
	{
		for (j = 0; j < SVM_VECTORS; j++)
		{
			Quad_Matrix[i][j] = Q_Matrix[i][i] + Q_Matrix[j][j] - 2 * Q_Matrix[i][j];
		}
	}
}

float Quad_Matrix_GetIJ(int i, int j)
{
	if (i >= SVM_VECTORS)
		i -= SVM_VECTORS;
	if (j >= SVM_VECTORS)
		j -= SVM_VECTORS;

	return Quad_Matrix[i][j];
}

//Y�����ʼ����ǰ�벿��ȫΪ+1����벿��ȫΪ-1
void Y_Matrix_Init(void)
{
	int i;
	for (i = 0; i < SVM_VECTORS; i++)
	{
		Y_Matrix[i] = +1;
		Y_Matrix[i + SVM_VECTORS] = -1;
	}
}

//�ݶȾ����ʼ������epsilon��y
void G_Matrix_Init(float *ResultMatrix, float epsilon)
{
	int i = 0;
	for (i = 0; i < SVM_VECTORS; i++)
	{
		G_Matrix[i] = epsilon - *ResultMatrix;
		G_Matrix[i + SVM_VECTORS] = epsilon + *ResultMatrix;
		ResultMatrix++;
	}
}

//Alpha2�����ʼ��
void Alpha2_Matrix_Init(void)
{
	int i = 0;
	for (i = 0; i < SVM_VECTORS; i++)
	{
		Alpha2_Matrix[i] = 0;
		Alpha2_Matrix[i + SVM_VECTORS] = 0;
	}
}

//����Alpha2����״̬
/*
void Update_Alpha2Status(float C)
{
int i = 0;
for (i = 0; i < QMATRIX_ROW; i++)
{
if (Alpha2_Matrix[i] >= C)
Alpha2_Status[i] = UPPER_BOUND;
else if (Alpha2_Matrix[i] <= 0)
Alpha2_Status[i] = LOWER_BOUND;
else
Alpha2_Status[i] = FREE;
}
}
*/
int iter = 0;
//ѡ���������㷨����ĵط�
int Select_WorkingSet(int *select_i, int *select_j, float epsilon, float C)
{
	int Gmax_idx = -1;
	int Gmin_idx = -1;

	float Gmax = -INF;
	float Gmax2 = -INF;
	float obj_diff_min = INF;

	int t = 0, i = 0, j = 0;

	float grad_diff = 0;
	float quad_coef = 0;

	for (t = 0; t < QMATRIX_ROW; t++)
	{
		if (Y_Matrix[t] == 1)
		{
			if (Alpha2_Matrix[t] < C)
			{
				if (-G_Matrix[t] >= Gmax)
				{
					Gmax = -G_Matrix[t];
					Gmax_idx = t;
				}
			}
		}
		else
		{
			if (Alpha2_Matrix[t] > 0)
			{
				if (G_Matrix[t] >= Gmax)
				{
					Gmax = G_Matrix[t];
					Gmax_idx = t;
				}
			}
		}
	}

	i = Gmax_idx;

	for (j = 0; j < QMATRIX_ROW; j++)
	{
		if (Y_Matrix[j] == 1)
		{
			if (Alpha2_Matrix[j] > 0)
			{

				if (G_Matrix[j] >= Gmax2)
					Gmax2 = G_Matrix[j];

				grad_diff = Gmax + G_Matrix[j];
				if (grad_diff > 0)
				{
					float obj_diff;
					quad_coef = Quad_Matrix_GetIJ(i,j);//Q_Matrix[i][i] + Q_Matrix[j][j] - 2.0*Y_Matrix[i] * Q_Matrix[i][j];

					if (quad_coef > 0)
						obj_diff = -(grad_diff*grad_diff) / quad_coef;

					if (obj_diff <= obj_diff_min)
					{
						Gmin_idx = j;
						obj_diff_min = obj_diff;
					}
				}
			}
		}
		else
		{
			if (Alpha2_Matrix[j] < C)
			{
				if (-G_Matrix[j] >= Gmax2)
					Gmax2 = -G_Matrix[j];

				grad_diff = Gmax - G_Matrix[j];
				if (grad_diff > 0)
				{
					float obj_diff;
					quad_coef = Quad_Matrix_GetIJ(i, j);//Q_Matrix[i][i] + Q_Matrix[j][j] + 2.0*Y_Matrix[i] * Q_Matrix[i][j];

					if (quad_coef > 0)
						obj_diff = -(grad_diff*grad_diff) / quad_coef;

					if (obj_diff <= obj_diff_min)
					{
						Gmin_idx = j;
						obj_diff_min = obj_diff;
					}
				}
			}
		}
	}
	
	//G_MaxMin[iter]=Gmax + Gmax2;

	if (Gmax + Gmax2 < epsilon || Gmin_idx == -1)
	{
		return 1;
	}

	*select_i = Gmax_idx;
	*select_j = Gmin_idx;
	return 0;
}


//SMO�㷨��ִ�У���һ��������㷨��д���˻�����ȫ������
void SMO_Slover(float C, float epsilon)
{

	float old_alpha2_i;
	float old_alpha2_j;

	iter = 0;

	while (iter < 10000)
	{
		int i, j;

		//ѡ�����ŵ�i��j
		if (Select_WorkingSet(&i, &j, epsilon, C) != 0)
		{
			break;
		}
		Select_WorkingSet_Time[iter]=TIM5->CNT;

		

		//����Alpha2������Ҫע��߽�Ĵ���
		old_alpha2_i = Alpha2_Matrix[i];
		old_alpha2_j = Alpha2_Matrix[j];

		if (Y_Matrix[i] != Y_Matrix[j])
		{
			float quad_coef = Quad_Matrix_GetIJ(i, j); //Q_Matrix[i][i] + Q_Matrix[j][j] + 2 * Q_Matrix[i][j];
			float delta = (-G_Matrix[i] - G_Matrix[j]) / quad_coef;
			float sum = Alpha2_Matrix[i] - Alpha2_Matrix[j];

			Alpha2_Matrix[i] += delta;
			Alpha2_Matrix[j] += delta;

			if (sum > 0)
			{
				if (Alpha2_Matrix[j] < 0)
				{
					Alpha2_Matrix[j] = 0;
					Alpha2_Matrix[i] = sum;
				}
				if (Alpha2_Matrix[i] > C)
				{
					Alpha2_Matrix[i] = C;
					Alpha2_Matrix[j] = C - sum;
				}
			}
			else
			{
				if (Alpha2_Matrix[i] < 0)
				{
					Alpha2_Matrix[i] = 0;
					Alpha2_Matrix[j] = -sum;
				}
				if (Alpha2_Matrix[j] > C)
				{
					Alpha2_Matrix[j] = C;
					Alpha2_Matrix[i] = C + sum;
				}
			}
		}
		else
		{
			float quad_coef = Quad_Matrix_GetIJ(i, j); //Q_Matrix[i][i] + Q_Matrix[j][j] - 2 * Q_Matrix[i][j];
			float delta = (G_Matrix[i] - G_Matrix[j]) / quad_coef;
			float sum = Alpha2_Matrix[i] + Alpha2_Matrix[j];

			Alpha2_Matrix[i] -= delta;
			Alpha2_Matrix[j] += delta;

			if (sum > C)
			{
				if (Alpha2_Matrix[i] > C)
				{
					Alpha2_Matrix[i] = C;
					Alpha2_Matrix[j] = sum - C;
				}
				if (Alpha2_Matrix[j] > C)
				{
					Alpha2_Matrix[j] = C;
					Alpha2_Matrix[i] = sum - C;
				}
			}
			else
			{
				if (Alpha2_Matrix[j] < 0)
				{
					Alpha2_Matrix[j] = 0;
					Alpha2_Matrix[i] = sum;
				}
				if (Alpha2_Matrix[i] < 0)
				{
					Alpha2_Matrix[i] = 0;
					Alpha2_Matrix[j] = sum;
				}
			}
		}


		//�����ݶ�
		{
			int k = 0;
			float delta_alpha2_i = Alpha2_Matrix[i] - old_alpha2_i;
			float delta_alpha2_j = Alpha2_Matrix[j] - old_alpha2_j;

			for (k = 0; k < SVM_VECTORS; k++)
			{
				G_Matrix[k] += Q_Matrix[i][k] * delta_alpha2_i + Q_Matrix[j][k] * delta_alpha2_j;
				G_Matrix[k + SVM_VECTORS] -= Q_Matrix[i][k] * delta_alpha2_i + Q_Matrix[j][k] * delta_alpha2_j;
			}
		}
		
		Garden_Change_Time[iter]=TIM5->CNT;
		
		iter++;
		
		//����Alpha2��״̬
		//�˴������ظ�����������ǰ��ֻ��Alpha2_Matrix[i]��Alpha2_Matrix[j]�����˸��£����ֻ�ø���i��j��Alpha2Status
		//Update_Alpha2Status(C);
	}
}

//��ȡ��������
int SMO_GetIteration(void)
{
	return iter;
}

//����ؾ�
static float SVM_Rho = 0;
float Calculate_Rho(float C)
{
	float r;
	int nr_free = 0;
	float ub = INF, lb = -INF, sum_free = 0;
	int i = 0;
	for (i = 0; i < QMATRIX_ROW; i++)
	{
		float yG;
		
		if(Y_Matrix[i] == 1)
		{
			yG = G_Matrix[i];
		}
		else
		{
			yG = -G_Matrix[i];
		}
		
		if (Alpha2_Matrix[i] >= C)
		{
			if (Y_Matrix[i] == -1)
				ub = ub > yG ? yG : ub;
			else
				lb = lb > yG ? lb : yG;
		}
		else if (Alpha2_Matrix[i] <= 0)
		{
			if (Y_Matrix[i] == 1)
				ub = ub > yG ? yG : ub;
			else
				lb = lb > yG ? lb : yG;
		}
		else
		{
			nr_free++;
			sum_free += yG;
		}
	}

	if (nr_free > 0)
		r = sum_free / nr_free;
	else
		r = (ub + lb) / 2;

	SVM_Rho = r;
	return r;
}

//����ԭʼ��Alpha����
void Calculate_Alpha(void)
{
	int i = 0;
	for (i = 0; i < SVM_VECTORS; i++)
	{
		Alpha_Matrix[i] = Alpha2_Matrix[i] - Alpha2_Matrix[i + SVM_VECTORS];
		//printf("%f\n", Alpha_Matrix[i]);
	}
}

//��ȡ������Alpha�����ָ��
float *Get_AlphaMatrix(void)
{
	return Alpha_Matrix;
}

//����ѵ��������Ԥ����
float SVR_Predict(float VectorsMatrix[SVM_VECTORS][VECTOR_DIM], float *PreX)
{
	float sum = 0;
	int i = 0;
	for (i = 0; i < SVM_VECTORS; i++)
	{
		sum += Alpha_Matrix[i] * Kernel_RBF(VectorsMatrix[i], PreX, RBF_GAMMA);
	}

	sum = sum - SVM_Rho;

	return sum;
}
