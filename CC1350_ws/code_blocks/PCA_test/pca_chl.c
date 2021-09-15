
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"
#include "pca_chl.h"



//int CPCAAlg_JacbiCor(double * pMatrix,int nDim, double *pdblVects, double *pdbEigenValues, double dbEps,int nJt);

#define Sensor_Num 4//���崫����������The number of rows in the matrix��
#define Time_Num 20 //�����������The number of columns in the matrix.��
MATRIX_TYPE Result_Vects_1[4*4]={0};//����ΪnDim*nDim�����飬������������(���д洢)
MATRIX_TYPE Result_Values_1[4*4]={0};//����ֵ����

MATRIX_TYPE Original_Data[Time_Num][Sensor_Num]={
        13,   9.7,  1.5, 6.4,
        10,   7.5,  1.5, 6.5,
        20.6, 12.5, 2.3, 7.0,
        33.3, 19.0, 2.8, 5.8,
        20.5, 14.2, 1.9, 6.9,
        10,   6.7,  2.2, 7.0,
        12.7, 5.7,  2.9, 6.7,
        36.5, 15.7, 2.3, 7.2,
        37.1, 14.3, 2.1, 7.2,
        25.5, 12.9, 1.9, 7.3,
        26.5, 14.5, 2.4, 6.7,
        22.3, 8.4,  4.0, 7.0,
        30.8, 7.4,  2.7, 6.4,
        25.3, 7.0,  4.8, 7.3,
        31.2, 11.6, 2.4, 6.3,
        22.7, 10.1, 3.3, 6.3,
        31.2, 9.6,  2.4, 6,
        13.2, 6.6,  2,   5.8,
        11.1, 6.7,  2.2, 7.2,
        20.7, 9.6,  3.1, 5.9};

/*
double Original_Data[Sensor_Num][Time_Num]={
13 , 10 , 20.6, 33.3, 20.5, 10, 12.7, 36.5, 37.1, 25.5, 26.5, 22.3, 30.8, 25.3, 31.2, 22.7, 31.2, 13.2, 11.1, 20.7,
9.7, 7.5, 12.5,19.0, 14.2, 6.7,  5.7,15.7, 14.3, 12.9, 14.5, 8.4,  7.4,  7.0,  11.6, 10.1, 9.6,  6.6,  6.7,  9.6,
1.5,1.5,2.3,2.8,1.9,2.2,2.9,2.3,2.1,1.9,2.4,4.0,2.7,4.8,2.4,3.3,2.4,2,2.2,3.1,
6.4,6.5,7.0,5.8,6.9,7.0,6.7,7.2,7.2,7.3,6.7,7.0,6.4,7.3,6.3,6.3,6,5.8,7.2,5.9
};
*/
//PCAʵ�ֺ���
void PCA_test(void)
{
    int row = sizeof(Original_Data) / sizeof(Original_Data[0]);
    int column = sizeof(Original_Data[0]) / sizeof(Original_Data[0][0]);
    Matirx* X0 = Matrix_gen(row,column,&Original_Data[0][0]);
    M_print(X0);
    //X0=Matrix_copy(X0);
    //M_print(X0);
    Matirx* X = M_T(X0);
    //Matirx* X = Matrix_copy(X0);
    printf("\n\n\nOriginal X\n\n");
    M_print(X);
    Matirx* X1 = M_zero(X);//���ֵ��
    printf("\n\n\nZero X1\n\n");
    M_print(X1);
    Matirx* X2 = M_T(X1);//ԭʼ�����ת��
    printf("\n\n\nTranspose X2\n\n");
    M_print(X2);
    Matirx*  C = M_mul(X1,X2);
    printf("\n\n\nCovariance C\n\n");
    M_print(C);
    //ϵ�� k=1/Time_Num
    double k_Deno=Time_Num;
    double k_C=1/k_Deno;
    C = M_multi_k(C,k_C);
    printf("\n\n\nCovariance C_k\n\n");
    M_print(C);
    int nDim=C->column;
    double *Result_Vects=&Result_Vects_1[0];//����ΪnDim*nDim�����飬������������(���д洢)
    double *Result_Values=&Result_Values_1[0];//����ֵ����
    double dbEps=10;//����Ҫ��
    int nJt=10;//����������
    CPCAAlg_JacbiCor( C->data , nDim , Result_Vects , Result_Values , dbEps , nJt );//�õ�����ֵ������������ͬʱ������ֵ�Ĵ�С��������������
    Matirx* P=Matrix_copy(C);
    //P->column=nDim;
    //P->row=nDim;
    for(int i=0;i<nDim;i++)
    {
        for(int j=0;j<nDim;j++)
        {
            P->data[i*nDim+j]=Result_Vects_1[j*nDim+i];//��ֵ��ͬʱ���ת��
        }
    }
    printf("\n\n\nP\n\n");
    M_print(P);
    //ȡǰk�й���P������Ϊ��kά
    int k=3;
    Matirx* P_k=Matrix_copy(P);
    P_k->column=nDim;
    P_k->row=k;
    int i,j;
    for(i=0;i<P_k->row;i++)
    {
        for(j=0;j<P_k->column;j++)
        {
            P_k->data[i*column+j]=P->data[i*column+j];
        }
    }
    printf("\n\n\nP_k\n\n");
    M_print(P_k);
    //��ά�������
    Matirx* Y = M_mul(P_k,X);//XΪԭʼ����
    printf("\n\n\nY\n\n");
    M_print(Y);
    Matirx* Y1 = M_mul(P_k,X1);//X1Ϊ���ֵ���������
    printf("\n\n\nY1\n\n");
    M_print(Y1);

}


/**
* @brief ��ʵ�Գƾ��������ֵ�������������ſ˱ȷ�
* �����Ÿ��(Jacobi)������ʵ�Գƾ����ȫ������ֵ����������
* @param pMatrix				����Ϊn*n�����飬���ʵ�Գƾ���
* @param nDim					����Ľ���
* @param pdblVects				����Ϊn*n�����飬������������(���д洢)
* @param dbEps					����Ҫ��
* @param nJt					���ͱ�������������������
* @param pdbEigenValues			����ֵ����
* @return
*/
int CPCAAlg_JacbiCor(double * pMatrix,int nDim, double *pdblVects, double *pdbEigenValues, double dbEps,int nJt)
{
	//��ʼ����������Ϊ�Խ���
    for(int i = 0; i < nDim; i ++)
	{
		pdblVects[i*nDim+i] = 1.0f; //�Խ���Ԫ�ض���1
		for(int j = 0; j < nDim; j ++)
		{
			if(i != j)
				pdblVects[i*nDim+j]=0.0f; //�ǶԽ���Ԫ��Ϊ0
		}
	}
    printf("?????????\n");
	int nCount = 0;		//��������
	while(1)
	{
		//��pMatrix�ķǶԽ������ҵ����Ԫ��
		double dbMax = pMatrix[1];//��һ���ǶԽ���Ԫ��
		int nRow = 0;//��¼��ǰ���Ԫ��������
		int nCol = 1;//��¼��ǰ���Ԫ��������
		for (int i = 0; i < nDim; i ++)			//��
		{
			for (int j = 0; j < nDim; j ++)		//��
			{
				double d = fabs(pMatrix[i*nDim+j]);

				if((i!=j) && (d> dbMax))
				{
					dbMax = d;
					nRow = i;
					nCol = j;
				}
			}
		}

		if(dbMax < dbEps)     //���ȷ���Ҫ��
			break;

		if(nCount > nJt)       //����������������
			break;

		nCount++;

		double dbApp = pMatrix[nRow*nDim+nRow];
		double dbApq = pMatrix[nRow*nDim+nCol];
		double dbAqq = pMatrix[nCol*nDim+nCol];

		//������ת�Ƕ�
		double dbAngle = 0.5*atan2(-2*dbApq,dbAqq-dbApp);
		double dbSinTheta = sin(dbAngle);
		double dbCosTheta = cos(dbAngle);
		double dbSin2Theta = sin(2*dbAngle);
		double dbCos2Theta = cos(2*dbAngle);

		pMatrix[nRow*nDim+nRow] = dbApp*dbCosTheta*dbCosTheta +
			dbAqq*dbSinTheta*dbSinTheta + 2*dbApq*dbCosTheta*dbSinTheta;
		pMatrix[nCol*nDim+nCol] = dbApp*dbSinTheta*dbSinTheta +
			dbAqq*dbCosTheta*dbCosTheta - 2*dbApq*dbCosTheta*dbSinTheta;
		pMatrix[nRow*nDim+nCol] = 0.5*(dbAqq-dbApp)*dbSin2Theta + dbApq*dbCos2Theta;
		pMatrix[nCol*nDim+nRow] = pMatrix[nRow*nDim+nCol];

		for(int i = 0; i < nDim; i ++)
		{
			if((i!=nCol) && (i!=nRow))
			{
				int u = i*nDim + nRow;	//p
				int w = i*nDim + nCol;	//q
				dbMax = pMatrix[u];
				pMatrix[u]= pMatrix[w]*dbSinTheta + dbMax*dbCosTheta;
				pMatrix[w]= pMatrix[w]*dbCosTheta - dbMax*dbSinTheta;
			}
		}

		for (int j = 0; j < nDim; j ++)
		{
			if((j!=nCol) && (j!=nRow))
			{
				int u = nRow*nDim + j;	//p
				int w = nCol*nDim + j;	//q
				dbMax = pMatrix[u];
                //����ֵ��ֵ
				pMatrix[u]= pMatrix[w]*dbSinTheta + dbMax*dbCosTheta;
				pMatrix[w]= pMatrix[w]*dbCosTheta - dbMax*dbSinTheta;
			}
		}

		//������������
		for(int i = 0; i < nDim; i ++)
		{
			int u = i*nDim + nRow;		//p
			int w = i*nDim + nCol;		//q
			dbMax = pdblVects[u];
            //����������ֵ
			pdblVects[u] = pdblVects[w]*dbSinTheta + dbMax*dbCosTheta;
			pdblVects[w] = pdblVects[w]*dbCosTheta - dbMax*dbSinTheta;
		}

	}

	//������ֵ���������Լ�����������������,����ֵ��pMatrix���Խ����ϵ�Ԫ��
    // ����
    double temp=0;
    for (int i = 0; i < nDim; i++)
    {
        for (int j = 0; j < nDim - i; j++) //ÿ������һ��ð�ݺ󣬾ͼ���һ�αȽ�
        {
         if (pMatrix[j*nDim+j] < pMatrix[(j+1)*nDim+j+1])
            {
                temp = pMatrix[j*nDim+j];
                pMatrix[j*nDim+j] = pMatrix[(j+1)*nDim+j+1];
                pMatrix[(j+1)*nDim+j+1] = temp;
                //����ֵ����󣬶�Ӧ����������ҲҪ��������
                //��ʱ��Ϊÿһ������ֵ��Ӧÿһ����������
                for(int i=0;i<nDim;i++)
                {
                  temp=pdblVects[i*nDim+j];
                  pdblVects[i*nDim+j]=pdblVects[i*nDim+j+1];
                  pdblVects[i*nDim+j+1]=temp;
                }

            }
        }

    }


    /*
	std::map<double,int> mapEigen;
	for(int i = 0; i < nDim; i ++)
	{
		pdbEigenValues[i] = pMatrix[i*nDim+i];

		mapEigen.insert(make_pair( pdbEigenValues[i],i ) );
	}

	double *pdbTmpVec = new double[nDim*nDim];
	std::map<double,int>::reverse_iterator iter = mapEigen.rbegin();
	for (int j = 0; iter != mapEigen.rend(),j < nDim; ++iter,++j)
	{
		for (int i = 0; i < nDim; i ++)
		{
			pdbTmpVec[i*nDim+j] = pdblVects[i*nDim + iter->second];
		}

		//����ֵ��������
		pdbEigenValues[j] = iter->first;
	}
 */
	//�趨������
	for(int i = 0; i < nDim; i ++)
	{
		double dSumVec = 0;
		for(int j = 0; j < nDim; j ++)
			dSumVec += pdblVects[j * nDim + i];
		if(dSumVec<0)
		{
			for(int j = 0;j < nDim; j ++)
				pdblVects[j * nDim + i] *= -1;
		}
	}

	//memcpy(pdblVects,pdbTmpVec,sizeof(double)*nDim*nDim);
	//delete []pdbTmpVec;

	return 1;
}






