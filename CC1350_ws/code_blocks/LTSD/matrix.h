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

#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <stdio.h>
#include <stdlib.h>
#include "state.h"

typedef struct _Matrix {
	/*Store Matrix
	�洢����*/
	int row;
	int column;
	MATRIX_TYPE * data;
} Matrix;

typedef struct _Elementary_Transformation{
	/*Store the Operation of Elementary_Transformation
	�洢���ȱ仯���������*/
	int minuend_line;
	int subtractor_line;
	TRANS_TYPE scale;
	struct _Elementary_Transformation* forward_E_trans;
	struct _Elementary_Transformation* next_E_trans;
}Etrans_struct;

typedef struct _Upper_triangular_transformation{
	/*Store the result of Upper_triangular_transformation
	�洢�����ǻ���������*/
	Matrix* trans_matrix;
	Matrix* Uptri_matrix;
}Uptri_struct;

typedef struct _Lower_triangular_transformation{
	/*Store the result of Upper_triangular_transformation
	�洢�����ǻ���������*/
	Matrix* trans_matrix;
	Matrix* Lowtri_matrix;
}Lowtri_struct;

typedef struct _Diagonalization_transformation{
	/*Store the result of Upper_triangular_transformation
	�洢�Խǻ�����������*/
	Matrix* trans_leftmatrix;
	Matrix* Diatri_matrix;
	Matrix* trans_rightmatrix;
}Dia_struct;

typedef struct _matrix_inverse_struct{
	/*Store the result of matrix_inverse
	�洢����������м���������㷨Ч��*/
	Matrix* _matrix;
	struct _Elementary_Transformation* _Etrans_head;
}M_inv_struct;



Matrix* Matrix_gen(int row, int column, MATRIX_TYPE* data);
Matrix* Matrix_copy(Matrix* _mat_sourse);
Matrix* M_mul(Matrix* _mat_left,Matrix* _mat_right);
Matrix* M_mul2(Matrix* _mat_left,Matrix* _mat_right);// Matrix dot product
Matrix* M_multi_k(Matrix* _mat,MATRIX_TYPE k);// Matrix multiplied by a constant
Matrix* M_add_sub(MATRIX_TYPE scale_mat_subed,Matrix* _mat_subed,MATRIX_TYPE scale_mat_minus,Matrix* _mat_minus);
int M_print(Matrix* _mat);
Matrix* M_I(int order);
int M_E_trans(Matrix* _mat,Etrans_struct* _Etrans_,int line_setting);
Matrix* Etrans_2_Matrix(Etrans_struct* _Etrans_,int order,int line_setting);
Matrix* Etrans_2_Inverse(Etrans_struct* _Etrans_,int order,int line_setting);
Uptri_struct* M_Uptri_(Matrix* _mat_source);
Uptri_struct* M_Uptri_4inv (Matrix* _mat_source);
Lowtri_struct* M_Lowtri_(Matrix* _mat_source);
Lowtri_struct* M_Lowtri_4inv (Matrix* _mat_source);
Matrix* M_Dia_Inv(Matrix* _mat_source);
Dia_struct* M_Diatri_(Matrix* _mat_source);
Matrix* M_Inverse(Matrix* _mat);
int M_Swap(Matrix* _mat,int _line_1,int _line_2,int line_setting);
Matrix* M_Cut(Matrix* _mat,int row_head,int row_tail,int column_head,int column_tail);
Matrix* M_T(Matrix* _mat_source);
int M_free(Matrix* _mat);
MATRIX_TYPE M_tr(Matrix* _mat);
MATRIX_TYPE M_det(Matrix* _mat);
Matrix* M_full(Matrix* _mat,int row_up,int row_down,int column_left,int column_right,MATRIX_TYPE full_data);
double fabs(double a);
Matrix* M_zero(Matrix* _mat);

//�ȴ�С����
double max_one(double x,double y);
double min_one(double x,double y);

#endif
