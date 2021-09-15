
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "matrix.h"
#include "blindSVM_chl.h"

#define Sensor_Num 2//���崫����������The number of rows in the matrix��
#define Time_Num 20 //�����������The number of columns in the matrix.��

double Original_Data2[Sensor_Num][Time_Num]={
13 , 10 , 20.6, 33.3, 20.5, 10, 12.7, 36.5, 37.1, 25.5, 26.5, 22.3, 30.8, 25.3, 31.2, 22.7, 31.2, 13.2, 11.1, 20.7,
9.7, 7.5, 12.5,19.0, 14.2, 6.7,  5.7,15.7, 14.3, 12.9, 14.5, 8.4,  7.4,  7.0,  11.6, 10.1, 9.6,  6.6,  6.7,  9.6,
};
double Data_label[1][Time_Num]={1,1,1,1,1,1,1,1,1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
//double Predict_label[1][Time_Num]={0};
/*
double Original_Data[Sensor_Num][Time_Num]={
13 , 10 , 20.6, 33.3, 20.5, 10, 12.7, 36.5, 37.1, 25.5, 26.5, 22.3, 30.8, 25.3, 31.2, 22.7, 31.2, 13.2, 11.1, 20.7,
9.7, 7.5, 12.5,19.0, 14.2, 6.7,  5.7,15.7, 14.3, 12.9, 14.5, 8.4,  7.4,  7.0,  11.6, 10.1, 9.6,  6.6,  6.7,  9.6,
1.5,1.5,2.3,2.8,1.9,2.2,2.9,2.3,2.1,1.9,2.4,4.0,2.7,4.8,2.4,3.3,2.4,2,2.2,3.1,
6.4,6.5,7.0,5.8,6.9,7.0,6.7,7.2,7.2,7.3,6.7,7.0,6.4,7.3,6.3,6.3,6,5.8,7.2,5.9
};
*/

//blindSVMʵ�ֺ���
void blindSVM_test(void)
{
    //��������
    int d = sizeof(Original_Data2) / sizeof(Original_Data2[0]);
    int num_data = sizeof(Original_Data2[0]) / sizeof(Original_Data2[0][0]);
    Matirx* X0 = Matrix_gen(d,num_data,&Original_Data2[0][0]);
    Matirx* train_data = M_T(X0);
    printf("\n\n\n*********Train data********\n\n");
    M_print(train_data);
    Matirx* X1 = Matrix_gen(1,num_data,&Data_label[0][0]);
    Matirx* label = M_T(X1);
    printf("\n\n\n*********Label********\n\n");
    M_print(label);
    //��������������
    double alphas_M[num_data][1]; //������ʼ��Ϊ0
    int p;//���ھ����ʼ����forѭ��
    for(p=0;p<num_data;p++)
    {
        alphas_M[p][0]=0;
    }
    Matirx* alphas = Matrix_gen(num_data,1,&alphas_M[0][0]);
    printf("\n\n\n*********Alphas********\n\n");
    M_print(alphas);
    //ϵ��
    double b,b1,b2 = 0;
    //�ɳڱ���Ӱ������
    double C = 0.6;
    int iter = 0; //ѭ������
    int max_iter = 40; //���ѭ������
    int alpha_change=0;
    double alphasI_old,alphasJ_old;
    while (iter < max_iter)
    {
        alpha_change = 0;
        int i,j,z;
        int temp;
        double H,L;//������
        for (i = 0;i<num_data;i++)
        {
            //���Ŀ��ֵ
            double data_i_M[d][1]; //����Ϊ��������ʡȥ��֮������ת��
            for(int p=0;p<d;p++)
            {
                data_i_M[p][0]=0;
            }
            for(z=0;z<d;z++)
            {
                data_i_M[z][0]=train_data->data[i*d+z];
            }
            Matirx* data_i = Matrix_gen(d,1,&data_i_M[0][0]);
            Matirx* data_i_T = M_T(data_i);
            Matirx* Temp = M_mul(M_T(M_mul2(alphas,label)),M_mul(train_data,data_i));
            double pre_Li = Temp->data[0]+b;
            //����i���
            double Ei = pre_Li - label->data[i];
            //���õ㲻����KKT����������Ҫ����
            if ((label->data[i]*Ei<-0.001 && alphas->data[i]<C)||(label->data[i]*Ei>0.001 && alphas->data[i]>0))//label(i)*Ei�൱��yi*ui-1
            {
                //ѡ��һ���� i ����ͬ�Ĵ��ı��alpha(2)--alpha(j)
                srand((unsigned)time(NULL));//���������
                j = rand()%num_data;
                if (j == i)
                {
                    temp = 1;
                    while(temp)
                    {
                       srand((unsigned)time(NULL));//���������
                       j = rand()%num_data;
                       if(j!=i)
                       {
                          temp = 0;
                       }
                    }
                }
                //����j�����ֵ
                double data_j_M[d][1]; //����Ϊ��������ʡȥ��֮������ת��
                for(int p=0;p<d;p++)
                {
                    data_j_M[p][0]=0;
                }
                for(z=0;z<d;z++)
                {
                    data_j_M[z][0]=train_data->data[j*d+z];
                }
                Matirx* data_j = Matrix_gen(d,1,&data_j_M[0][0]);
                Matirx* data_j_T = M_T(data_j);
                Matirx* Temp2 = M_mul(M_T(M_mul2(alphas,label)),M_mul(train_data,data_j));
                double pre_Lj = Temp2->data[0]+b;
                //����j���
                double Ej = pre_Lj - label->data[j];
                //����������
                if (label->data[i] != label->data[j]) //���ǩ����ͬ��ͬ
                {
                    L = max_one(0,alphas->data[j] - alphas->data[i]);
                    H = min_one(C,C + alphas->data[j] - alphas->data[i]);
                }
                else
                {
                    L = max_one(0,alphas->data[j] + alphas->data[i] -C);
                    H = min_one(C,alphas->data[j] + alphas->data[i]);
                }
                if (L!=H)  //������һ����������ѭ��
                {
                    //����eta
                    double eta = 2*M_mul(data_i_T,data_j)->data[0] - M_mul(data_i_T,data_i)->data[0] - M_mul(data_j_T,data_j)->data[0];
                    //�����ֵ
                    alphasI_old = alphas->data[i];
                    alphasJ_old = alphas->data[j];
                    //����alpha(2)��Ҳ����alpha(j)
                    alphas->data[j] = alphas->data[j] - label->data[j]*(Ei-Ej)/eta;
                    //���Ʒ�Χ
                    if (alphas->data[j] > H)
                    {
                        alphas->data[j] = H;
                    }
                    else if (alphas->data[j] < L)
                    {
                        alphas->data[j] = L;
                    }
                    //���alpha(j)û��ô�ı䣬��������ѭ��
                    if (fabs(alphas->data[j] - alphasJ_old)<0.0001)
                    {
                        ;
                    }
                    else
                    {
                        //����alpha(1)��Ҳ����alpha(i)
                        alphas->data[i] = alphas->data[i] + label->data[i]*label->data[j]*(alphasJ_old-alphas->data[j]);
                        //����ϵ��b
                        b1 = b - Ei - label->data[i]*(alphas->data[i]-alphasI_old)*M_mul(data_i_T,data_i)->data[0] - label->data[j]*(alphas->data[j]-alphasJ_old)*M_mul(data_i_T,data_j)->data[0];
                        b1 = b - Ei - label->data[i]*(alphas->data[i]-alphasI_old)*M_mul(data_i_T,data_j)->data[0] - label->data[j]*(alphas->data[j]-alphasJ_old)*M_mul(data_j_T,data_j)->data[0];
                    //b�ļ���ѡ�����
                    if (alphas->data[i]>0 && alphas->data[i]<C)
                    {
                        b = b1;
                    }
                    else if (alphas->data[j]>0 && alphas->data[j]<C)
                    {
                       b = b2;
                    }
                    else
                    {
                        b = (b1+b2)/2;
                    }
                    //ȷ�������ˣ���¼һ��
                    alpha_change = alpha_change + 1;//�ҵ�һ��������ĵ㣬�ͻ����һ��
                    }
                }
            }
        }
        //û��ʵ��alpha������������1
        if (alpha_change == 0)
            iter = iter + 1;
        //ʵ���˽�����������0
        else
            iter = 0;
    }
    //����ȨֵW
    Matirx* W = M_mul(M_T(M_mul2(alphas,label)),train_data);
    //����Ԥ����
    Matirx* predict = M_mul(M_T(M_mul2(alphas,label)),M_mul(train_data,M_T(train_data)));
    for(p=0;p<num_data;p++)
    {
        predict->data[p]=predict->data[p] + b;
    }
    //���ź��� -1 0 +1
    for(p=0;p<num_data;p++)
    {
        if(predict->data[p]>=0)
            predict->data[p]=1;
        else if(predict->data[p]<0)
            predict->data[p]=-1;
    }
    //��ʾ���
    Matirx* predict_T = M_T(predict);
    printf("\n\n\n*********Predict********\n\n");
    M_print(predict_T);
 }

