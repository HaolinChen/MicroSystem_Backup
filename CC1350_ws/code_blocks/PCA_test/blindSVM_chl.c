
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "matrix.h"
#include "blindSVM_chl.h"

#define Sensor_Num 2//气体传感器个数（The number of rows in the matrix）
#define Time_Num 20 //采样点个数（The number of columns in the matrix.）

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

//blindSVM实现函数
void blindSVM_test(void)
{
    //加载数据
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
    //定义向量机参数
    double alphas_M[num_data][1]; //将α初始化为0
    int p;//用于矩阵初始化的for循环
    for(p=0;p<num_data;p++)
    {
        alphas_M[p][0]=0;
    }
    Matirx* alphas = Matrix_gen(num_data,1,&alphas_M[0][0]);
    printf("\n\n\n*********Alphas********\n\n");
    M_print(alphas);
    //系数
    double b,b1,b2 = 0;
    //松弛变量影响因子
    double C = 0.6;
    int iter = 0; //循环次数
    int max_iter = 40; //最大循环次数
    int alpha_change=0;
    double alphasI_old,alphasJ_old;
    while (iter < max_iter)
    {
        alpha_change = 0;
        int i,j,z;
        int temp;
        double H,L;//上下限
        for (i = 0;i<num_data;i++)
        {
            //输出目标值
            double data_i_M[d][1]; //这里为列向量，省去了之后计算的转置
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
            //样本i误差
            double Ei = pre_Li - label->data[i];
            //若该点不满足KKT条件，则需要调整
            if ((label->data[i]*Ei<-0.001 && alphas->data[i]<C)||(label->data[i]*Ei>0.001 && alphas->data[i]>0))//label(i)*Ei相当于yi*ui-1
            {
                //选择一个和 i 不相同的待改变的alpha(2)--alpha(j)
                srand((unsigned)time(NULL));//随机数播种
                j = rand()%num_data;
                if (j == i)
                {
                    temp = 1;
                    while(temp)
                    {
                       srand((unsigned)time(NULL));//随机数播种
                       j = rand()%num_data;
                       if(j!=i)
                       {
                          temp = 0;
                       }
                    }
                }
                //样本j的输出值
                double data_j_M[d][1]; //这里为列向量，省去了之后计算的转置
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
                //样本j误差
                double Ej = pre_Lj - label->data[j];
                //更新上下限
                if (label->data[i] != label->data[j]) //类标签不相同相同
                {
                    L = max_one(0,alphas->data[j] - alphas->data[i]);
                    H = min_one(C,C + alphas->data[j] - alphas->data[i]);
                }
                else
                {
                    L = max_one(0,alphas->data[j] + alphas->data[i] -C);
                    H = min_one(C,alphas->data[j] + alphas->data[i]);
                }
                if (L!=H)  //上下限一样结束本次循环
                {
                    //计算eta
                    double eta = 2*M_mul(data_i_T,data_j)->data[0] - M_mul(data_i_T,data_i)->data[0] - M_mul(data_j_T,data_j)->data[0];
                    //保存旧值
                    alphasI_old = alphas->data[i];
                    alphasJ_old = alphas->data[j];
                    //更新alpha(2)，也就是alpha(j)
                    alphas->data[j] = alphas->data[j] - label->data[j]*(Ei-Ej)/eta;
                    //限制范围
                    if (alphas->data[j] > H)
                    {
                        alphas->data[j] = H;
                    }
                    else if (alphas->data[j] < L)
                    {
                        alphas->data[j] = L;
                    }
                    //如果alpha(j)没怎么改变，结束本次循环
                    if (fabs(alphas->data[j] - alphasJ_old)<0.0001)
                    {
                        ;
                    }
                    else
                    {
                        //更新alpha(1)，也就是alpha(i)
                        alphas->data[i] = alphas->data[i] + label->data[i]*label->data[j]*(alphasJ_old-alphas->data[j]);
                        //更新系数b
                        b1 = b - Ei - label->data[i]*(alphas->data[i]-alphasI_old)*M_mul(data_i_T,data_i)->data[0] - label->data[j]*(alphas->data[j]-alphasJ_old)*M_mul(data_i_T,data_j)->data[0];
                        b1 = b - Ei - label->data[i]*(alphas->data[i]-alphasI_old)*M_mul(data_i_T,data_j)->data[0] - label->data[j]*(alphas->data[j]-alphasJ_old)*M_mul(data_j_T,data_j)->data[0];
                    //b的几种选择机制
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
                    //确定更新了，记录一次
                    alpha_change = alpha_change + 1;//找到一个不满足的点，就会更新一次
                    }
                }
            }
        }
        //没有实行alpha交换，迭代加1
        if (alpha_change == 0)
            iter = iter + 1;
        //实行了交换，迭代清0
        else
            iter = 0;
    }
    //计算权值W
    Matirx* W = M_mul(M_T(M_mul2(alphas,label)),train_data);
    //计算预测结果
    Matirx* predict = M_mul(M_T(M_mul2(alphas,label)),M_mul(train_data,M_T(train_data)));
    for(p=0;p<num_data;p++)
    {
        predict->data[p]=predict->data[p] + b;
    }
    //符号函数 -1 0 +1
    for(p=0;p<num_data;p++)
    {
        if(predict->data[p]>=0)
            predict->data[p]=1;
        else if(predict->data[p]<0)
            predict->data[p]=-1;
    }
    //显示结果
    Matirx* predict_T = M_T(predict);
    printf("\n\n\n*********Predict********\n\n");
    M_print(predict_T);
 }

