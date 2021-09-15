/*
%% IMFORMATION
%% MATRIX_HUB
% Author: Xiping Yu
% Email:Amoiensis@outlook.com
% Github: https://github.com/Amoiensis/Matrix_hub
% Data: 2020.02.12 
% Case: Matrix Operation 
% Dtailed: the code_file of Matrix_hub
*/ 

#include <stdio.h>
#include <stdlib.h>
#include "state.h"

typedef struct _Matrix {
	/*Store Matrix
	存储矩阵*/
	int row;
	int column;
	MATRIX_TYPE * data;
} Matirx;

typedef struct _Elementary_Transformation{
	/*Store the Operation of Elementary_Transformation
	存储初等变化的运算过程*/
	int minuend_line;
	int subtractor_line;
	TRANS_TYPE scale;
	struct _Elementary_Transformation* forward_E_trans;
	struct _Elementary_Transformation* next_E_trans;
}Etrans_struct;

typedef struct _Upper_triangular_transformation{
	/*Store the result of Upper_triangular_transformation
	存储上三角化的运算结果*/
	Matirx* trans_matrix;
	Matirx* Uptri_matrix;
}Uptri_struct;

typedef struct _Lower_triangular_transformation{
	/*Store the result of Upper_triangular_transformation
	存储下三角化的运算结果*/
	Matirx* trans_matrix;
	Matirx* Lowtri_matrix;
}Lowtri_struct;

typedef struct _Diagonalization_transformation{
	/*Store the result of Upper_triangular_transformation
	存储对角化化的运算结果*/
	Matirx* trans_leftmatrix;
	Matirx* Diatri_matrix;
	Matirx* trans_rightmatrix;
}Dia_struct;

typedef struct _matrix_inverse_struct{
	/*Store the result of matrix_inverse
	存储求逆运算的中间结果，提高算法效率*/
	Matirx* _matrix;
	struct _Elementary_Transformation* _Etrans_head;
}M_inv_struct;



Matirx* Matrix_gen(int row, int column, MATRIX_TYPE* data);
Matirx* Matrix_copy(Matirx* _mat_sourse); 
Matirx* M_mul(Matirx* _mat_left,Matirx* _mat_right);
Matirx* M_add_sub(MATRIX_TYPE scale_mat_subed,Matirx* _mat_subed,MATRIX_TYPE scale_mat_minus,Matirx* _mat_minus);
int M_print(Matirx* _mat);
Matirx* M_I(int order);
int M_E_trans(Matirx* _mat,Etrans_struct* _Etrans_,int line_setting);
Matirx* Etrans_2_Matrix(Etrans_struct* _Etrans_,int order,int line_setting);
Matirx* Etrans_2_Inverse(Etrans_struct* _Etrans_,int order,int line_setting);
Uptri_struct* M_Uptri_(Matirx* _mat_source);
Uptri_struct* M_Uptri_4inv (Matirx* _mat_source);
Lowtri_struct* M_Lowtri_(Matirx* _mat_source);
Lowtri_struct* M_Lowtri_4inv (Matirx* _mat_source);
Matirx* M_Dia_Inv(Matirx* _mat_source);
Dia_struct* M_Diatri_(Matirx* _mat_source);
Matirx* M_Inverse(Matirx* _mat);
int M_Swap(Matirx* _mat,int _line_1,int _line_2,int line_setting);
Matirx* M_Cut(Matirx* _mat,int row_head,int row_tail,int column_head,int column_tail); 
Matirx* M_T(Matirx* _mat_source);
int M_free(Matirx* _mat);
MATRIX_TYPE M_tr(Matirx* _mat);
MATRIX_TYPE M_det(Matirx* _mat);
Matirx* M_full(Matirx* _mat,int row_up,int row_down,int column_left,int column_right,MATRIX_TYPE full_data);
double fabs(double a);
Matirx* M_zero(Matirx* _mat);
Matirx* M_multi_k(Matirx* _mat,MATRIX_TYPE k);