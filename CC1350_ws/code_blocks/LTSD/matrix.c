
#include "matrix.h"

Matrix* Matrix_gen(int row,int column,MATRIX_TYPE* data) {/*Generate Matrix Struct
	导入_生成矩阵*/
	Matrix* _mat = (Matrix*)malloc(sizeof(Matrix));
	_mat->row = row;
	_mat->column = column;
	int size = _mat->row*_mat->column;
	_mat->data = (MATRIX_TYPE*)malloc((size) * sizeof(MATRIX_TYPE));
	int i;
	for (i = 0; i<size; i++) {
		_mat->data[i] = data[i];
	}
	return _mat;
}

Matrix* Matrix_copy(Matrix* _mat_sourse){/*Copy Mtrix(gen new one)
	复制矩阵（生成新矩阵）*/
	Matrix* _mat_copy = Matrix_gen(_mat_sourse->row,_mat_sourse->column,_mat_sourse->data);
	return _mat_copy;
}

Matrix* M_add_sub(MATRIX_TYPE scale_mat_subed,Matrix* _mat_subed,MATRIX_TYPE scale_mat_minus,Matrix* _mat_minus){/*Add & Sub
	矩阵加减法*/
	Matrix* _mat_result = NULL;
	if((_mat_subed->column == _mat_minus->column)&&(_mat_subed->row == _mat_minus->row)){
		_mat_result = Matrix_copy(_mat_subed);
		int size = (_mat_subed->row)*(_mat_subed->column),i;
		for (i=0;i<size;i++){
			_mat_result->data[i] = (_mat_result->data[i])*scale_mat_subed - (_mat_minus->data[i])*scale_mat_minus;
		}
	}else{
		printf(M_add_sub_003);
	}
	return _mat_result;
}

Matrix* M_mul(Matrix* _mat_left,Matrix* _mat_right){/*Matrix Multiply
	矩阵乘法
	_mat_result = _mat_left*_mat_right */
	//printf(">>Matrix_%x * Matrix_%x =\n",_mat_left,_mat_right);
	/*Determine_Matrix_Dimensions*/
	Matrix* _mat_result = NULL;
	if (_mat_left->column != _mat_right->row){
		printf(M_mul_001);
	}else{
		_mat_result = (Matrix*)malloc(sizeof(Matrix));
		int row = _mat_left->row;
		int mid = _mat_left->column;
		int column = _mat_right->column;
		int i,j,k;
		MATRIX_TYPE* _data = (MATRIX_TYPE*)malloc((row*column)*sizeof(MATRIX_TYPE));
		MATRIX_TYPE temp = 0;
		/*Ergodic*/
		for(i=0;i<row;i++){
			for(j=0;j<column;j++){
				/*Caculate Element*/
				temp = 0;
				for (k=0;k<mid;k++){
					temp += (_mat_left->data[i*mid+k])*(_mat_right->data[k*column+j]);
				}
				_data[i*column+j] = temp;
			}
		}
		_mat_result->row = row;
		_mat_result->column = column;
		_mat_result->data = _data;
	}
	//printf("\tMatrix_%x\n",_mat_result);
	return _mat_result;
}

Matrix* M_mul2(Matrix* _mat_left,Matrix* _mat_right){/*Matrix Multiply
	矩阵点乘
	_mat_result = _mat_left.*_mat_right */
	/*Determine_Matrix_Dimensions*/
	Matrix* _mat_result = NULL;
    _mat_result = (Matrix*)malloc(sizeof(Matrix));
    int row = _mat_left->row;
    int column = _mat_left->column;
    int i,j,k;
    MATRIX_TYPE* _data = (MATRIX_TYPE*)malloc((row*column)*sizeof(MATRIX_TYPE));
    MATRIX_TYPE temp = 0;
    for(i=0;i<row;i++){
        for(j=0;j<column;j++){
            /*Caculate Element*/
            temp = _mat_left->data[i*column+j]*_mat_right->data[i*column+j];
            _data[i*column+j] = temp;
			}
		}
    _mat_result->row = row;
    _mat_result->column = column;
    _mat_result->data = _data;
	return _mat_result;
}

int M_print(Matrix* _mat){/*Print Matrix
	打印矩阵*/
	//printf(">>Matrix_%x:\n",_mat);
	int i,j;
	for (i=0;i<_mat->row;i++){
		for(j=0;j<_mat->column;j++){
			printf(PRECISION,_mat->data[i*(_mat->column)+j]);
		}
		printf("\n");
	}
	return 0;
}

Matrix* M_I(int order){/*Generate I _matrix
	生成单位矩阵*/
	Matrix* I_mat = (Matrix*)malloc(sizeof(Matrix));
	I_mat->column = order;
	I_mat->row = order;
	int size = order*order,i;
	MATRIX_TYPE* data = (MATRIX_TYPE*)malloc((size) * sizeof(MATRIX_TYPE));
	for(i=0;i<size;i++){
		data[i] = 0;
	}
	for(i=0;i<order;i++){
		data[i*(order+1)] = 1;
	}
	I_mat->data = data;
	return I_mat;
}

int M_E_trans(Matrix* _mat,Etrans_struct* _Etrans_,int line_setting){/*Element teransfor Matrix
	对矩阵初等变换*/
/*lin3_sstting 设置是行初等变换还是列初等变换*/
	int line_num,i;
	if (line_setting == _ROW_){
		/*行初等变换*/
		line_num = _mat->column;
		if (_Etrans_->scale){
			for(i=0;i<line_num;i++){
				_mat->data[(_Etrans_->minuend_line-1)*(_mat->column)+i] -= (_Etrans_->scale)*(_mat->data[(_Etrans_->subtractor_line-1)*(_mat->column)+i]);

			}
		}else{
			if((_Etrans_->minuend_line <0)&&(_Etrans_->subtractor_line<0)){/*交换*/
				M_Swap(_mat,-(_Etrans_->minuend_line),-(_Etrans_->subtractor_line),line_setting);
			}
		}
	}else{
		/*列初等变换*/
		line_num = _mat->row;
		if (_Etrans_->scale){
			for(i=0;i<line_num;i++){
			_mat->data[(_Etrans_->minuend_line-1)+(_mat->column)*i] -= (_Etrans_->scale)*(_mat->data[(_Etrans_->subtractor_line-1)+(_mat->column)*i]);
			}
		}else{
			if((_Etrans_->minuend_line <0)&&(_Etrans_->subtractor_line<0)){/*交换*/
				M_Swap(_mat,-(_Etrans_->minuend_line),-(_Etrans_->subtractor_line),line_setting);
			}
		}
	}
	return 0;
}

Matrix* Etrans_2_Inverse(Etrans_struct* _Etrans_,int order,int line_setting){/*Inverse_Element_trans_to_Matrix
	基本变换转矩阵的转置*/
//	if (_mat_sourse == NULL){
		Matrix* _mat_result = M_I(order);
		Etrans_struct* temp_Etrans = _Etrans_;
		do{
			M_E_trans(_mat_result,temp_Etrans,line_setting);
			temp_Etrans = temp_Etrans->next_E_trans;
		}while(temp_Etrans!=NULL);
		return _mat_result;
//	}else{
//		Matirx* _mat_result = _mat_sourse;//M_I(order);
//		Etrans_struct* temp_Etrans = _Etrans_;
//		do{
//			M_E_trans(_mat_result,temp_Etrans,line_setting);
//			temp_Etrans = temp_Etrans->next_E_trans;
//		}while(temp_Etrans!=NULL);
//		return _mat_result;
//	}
}

Matrix* Etrans_2_Matrix(Etrans_struct* _Etrans_,int order,int line_setting){/*Element_trans_to_Matrix
	基本变换转矩阵*/
	Etrans_struct* temp_Etrans = _Etrans_;
	Matrix* _mat_result = M_I(order);
	if (_Etrans_ != NULL){
		while ((temp_Etrans->next_E_trans)!=NULL){
			temp_Etrans = temp_Etrans->next_E_trans;
		}
		//M_print(_mat_result);
		do{
			temp_Etrans->scale = (-1)*temp_Etrans->scale;
			M_E_trans(_mat_result,temp_Etrans,line_setting);
			temp_Etrans->scale = (-1)*temp_Etrans->scale;
			temp_Etrans = temp_Etrans->forward_E_trans;
			//M_print(_mat_result);
		}while(temp_Etrans!=NULL);
	}
	return _mat_result;
}

Uptri_struct* M_Uptri_(Matrix* _mat_source){/*Upper_triangular_transformation
	上三角化*/
	Matrix* _mat = Matrix_copy(_mat_source);
	int i,j,k,flag;
	Etrans_struct* _Etrans_temp_last = NULL;
	Etrans_struct*_Etrans_temp_head = NULL;

	/*初等变换*/
	for(i=0;i<_mat->column;i++){
		for(j=i+1;j<_mat->row;j++){
			flag = 0;
			Etrans_struct* _Etrans_temp = (Etrans_struct*)malloc(sizeof(Etrans_struct));
			_Etrans_temp->minuend_line = j+1;
			_Etrans_temp->subtractor_line = i+1;
			if ((_mat->data[(_mat->column)*i+i])!= 0){
				_Etrans_temp->scale = (_mat->data[(_mat->column)*j+i])/(_mat->data[(_mat->column)*i+i]);
			}else{
				_Etrans_temp->scale = 0;
				for(k=i+1;k<_mat->row;k++){
					flag = 1;//无可替代行
					if((_mat->data[(_mat->column)*k+i])!=0){
						_Etrans_temp->minuend_line = -(i+1);
						_Etrans_temp->subtractor_line = -(k+1);
						flag = 2;//表示能够替换行
						break;
					}
				}
				if(flag == 1){
					break;
				}
			}
			_Etrans_temp->forward_E_trans = NULL;
			_Etrans_temp->next_E_trans = NULL;
			if(_Etrans_temp_head ==NULL){
				_Etrans_temp_head = _Etrans_temp;
				_Etrans_temp->forward_E_trans = NULL;
			}else{
				_Etrans_temp->forward_E_trans = _Etrans_temp_last;

			}
			if ((i+1)==_mat->column){
					_Etrans_temp->next_E_trans = NULL;
			}else{
				if (_Etrans_temp_last != NULL){
					_Etrans_temp_last->next_E_trans = _Etrans_temp;
				}
			}
			M_E_trans(_mat,_Etrans_temp,_ROW_);
			//M_print(_mat); //显示具体矩阵
			_Etrans_temp_last = _Etrans_temp;

			if(flag==2){
					i = i-1;
					break;
			}
			}
		}
	Matrix* trans_mat = Etrans_2_Matrix(_Etrans_temp_head,_mat->row,_ROW_);
	Uptri_struct* _Uptri = (Uptri_struct*)malloc(sizeof(Uptri_struct));
	_Uptri->trans_matrix = trans_mat;
	_Uptri->Uptri_matrix = _mat;
	printf(">>Uptri(Matrix_%x)=\n",_mat_source);
	printf("\tMatrix_%x * Matrix_%x\n",trans_mat,_mat);
	return _Uptri;
}

Uptri_struct* M_Uptri_4inv (Matrix* _mat_source){/*Upper_triangular_transformation_for_Inverse
	上三角化_求逆使用*/
	Matrix* _mat = Matrix_copy(_mat_source);
	int i,j,k,flag;
	Etrans_struct* _Etrans_temp_last = NULL;
	Etrans_struct*_Etrans_temp_head = NULL;

	/*初等变换*/
	for(i=0;i<_mat->column;i++){
		for(j=i+1;j<_mat->row;j++){
			flag = 0;
			Etrans_struct* _Etrans_temp = (Etrans_struct*)malloc(sizeof(Etrans_struct));
			_Etrans_temp->minuend_line = j+1;
			_Etrans_temp->subtractor_line = i+1;
			if ((_mat->data[(_mat->column)*i+i])!= 0){
				_Etrans_temp->scale = (_mat->data[(_mat->column)*j+i])/(_mat->data[(_mat->column)*i+i]);
			}else{
				_Etrans_temp->scale = 0;
				for(k=i+1;k<_mat->row;k++){
					flag = 1;//无可替代行
					if((_mat->data[(_mat->column)*k+i])!=0){
						_Etrans_temp->minuend_line = -(i+1);
						_Etrans_temp->subtractor_line = -(k+1);
						flag = 2;//表示能够替换行
						break;
					}
				}
				if(flag == 1){
					break;
				}
			}
			_Etrans_temp->forward_E_trans = NULL;
			_Etrans_temp->next_E_trans = NULL;
			//if (j==1){
			if(_Etrans_temp_head ==NULL){
				_Etrans_temp_head = _Etrans_temp;
				_Etrans_temp->forward_E_trans = NULL;
			}else{
				_Etrans_temp->forward_E_trans = _Etrans_temp_last;

			}
			if ((i+1)==_mat->column){
					_Etrans_temp->next_E_trans = NULL;
			}else{
				if (_Etrans_temp_last != NULL){
					_Etrans_temp_last->next_E_trans = _Etrans_temp;
				}
			}
			M_E_trans(_mat,_Etrans_temp,_ROW_);
			//M_print(_mat); //显示具体矩阵
			_Etrans_temp_last = _Etrans_temp;

			if(flag==2){
					i = i-1;
					break;
			}
		}
	}
	Matrix* trans_mat = Etrans_2_Inverse(_Etrans_temp_head,_mat->row,_ROW_);
	Uptri_struct* _Uptri = (Uptri_struct*)malloc(sizeof(Uptri_struct));
	_Uptri->trans_matrix = trans_mat;
	_Uptri->Uptri_matrix = _mat;
//	M_inv_struct* _Uptri =  (M_inv_struct*)malloc(sizeof(M_inv_struct));
//	 _Uptri->_matrix = _mat;
//	 _Uptri->_Etrans_head = _Etrans_temp_head;
//	printf(">>Uptri(Matrix_%x)=\n",_mat_source);
//	printf("\tMatrix_%x * Matrix_%x\n",_mat,trans_mat);
	return _Uptri;
}

Lowtri_struct* M_Lowtri_(Matrix* _mat_source){/*Lower_triangular_transformation
	下三角化*/
	Matrix* _mat = Matrix_copy(_mat_source);
	int i,j,k,flag;
	Etrans_struct* _Etrans_temp_last = NULL;
	Etrans_struct*_Etrans_temp_head = NULL;
	for(i=0;i<_mat->row;i++){
		for(j=i+1;j<_mat->column;j++){
			flag = 0;
			Etrans_struct* _Etrans_temp = (Etrans_struct*)malloc(sizeof(Etrans_struct));
			_Etrans_temp->minuend_line = j+1;
			_Etrans_temp->subtractor_line = i+1;


			if ((_mat->data[(_mat->column)*i+i])!= 0){
				_Etrans_temp->scale = (_mat->data[(_mat->column)*i+j])/(_mat->data[(_mat->column)*i+i]);;
			}else{
				_Etrans_temp->scale = 0;
				for(k=i+1;k<_mat->row;k++){
					flag = 1;//无可替代行
					if((_mat->data[(_mat->column)*k+i])!=0){
						_Etrans_temp->minuend_line = -(i+1);
						_Etrans_temp->subtractor_line = -(k+1);
						flag = 2;//表示能够替换行
						break;
					}
				}
				if(flag == 1){
					break;
				}
			}

			_Etrans_temp->forward_E_trans = NULL;
			_Etrans_temp->next_E_trans = NULL;
			if (_Etrans_temp_head ==NULL){
				_Etrans_temp_head = _Etrans_temp;
				_Etrans_temp->forward_E_trans = NULL;
			}else{
				_Etrans_temp->forward_E_trans = _Etrans_temp_last;
			}
			if ((i+1)==_mat->column){
					_Etrans_temp->next_E_trans = NULL;
			}else{
				if (_Etrans_temp_last != NULL){
					_Etrans_temp_last->next_E_trans = _Etrans_temp;
				}
			}
			M_E_trans(_mat,_Etrans_temp,_COLUMN_);
			M_print(_mat); //显示具体矩阵
			_Etrans_temp_last = _Etrans_temp;
			if(flag==2){
					i = i-1;
					break;
			}
		}
	}
	Matrix* trans_mat = Etrans_2_Matrix(_Etrans_temp_head,_mat->row,_COLUMN_);
	Lowtri_struct* _Lowtri = (Lowtri_struct*)malloc(sizeof(Lowtri_struct));
	_Lowtri->trans_matrix = trans_mat;
	_Lowtri->Lowtri_matrix = _mat;
	printf(">>Lowtri(Matrix_%x)=\n",_mat_source);
	printf("\tMatrix_%x * Matrix_%x\n",_mat,trans_mat);
	return _Lowtri;
}

Lowtri_struct*  M_Lowtri_4inv (Matrix* _mat_source){/*_Lower_triangular_transformation_for_Inverse
	下三角化_求逆使用*/
	Matrix* _mat = Matrix_copy(_mat_source);
	int i,j,k,flag;
	Etrans_struct* _Etrans_temp_last = NULL;
	Etrans_struct*_Etrans_temp_head = NULL;
	for(i=0;i<_mat->row;i++){
		for(j=i+1;j<_mat->column;j++){
			flag = 0;
			Etrans_struct* _Etrans_temp = (Etrans_struct*)malloc(sizeof(Etrans_struct));
			_Etrans_temp->minuend_line = j+1;
			_Etrans_temp->subtractor_line = i+1;


			if ((_mat->data[(_mat->column)*i+i])!= 0){
				_Etrans_temp->scale = (_mat->data[(_mat->column)*i+j])/(_mat->data[(_mat->column)*i+i]);;
			}else{
				_Etrans_temp->scale = 0;
				for(k=i+1;k<_mat->row;k++){
					flag = 1;//无可替代行
					if((_mat->data[(_mat->column)*k+i])!=0){
						_Etrans_temp->minuend_line = -(i+1);
						_Etrans_temp->subtractor_line = -(k+1);
						flag = 2;//表示能够替换行
						break;
					}
				}
				if(flag == 1){
					break;
				}
			}

			_Etrans_temp->forward_E_trans = NULL;
			_Etrans_temp->next_E_trans = NULL;
			if (_Etrans_temp_head ==NULL){
				_Etrans_temp_head = _Etrans_temp;
				_Etrans_temp->forward_E_trans = NULL;
			}else{
				_Etrans_temp->forward_E_trans = _Etrans_temp_last;
			}
			if ((i+1)==_mat->column){
					_Etrans_temp->next_E_trans = NULL;
			}else{
				if (_Etrans_temp_last != NULL){
					_Etrans_temp_last->next_E_trans = _Etrans_temp;
				}
			}
			M_E_trans(_mat,_Etrans_temp,_COLUMN_);
			//M_print(_mat); //显示具体矩阵
			_Etrans_temp_last = _Etrans_temp;
			if(flag==2){
					i = i-1;
					break;
			}
		}
	}
	Matrix* trans_mat = Etrans_2_Inverse(_Etrans_temp_head,_mat->row,_COLUMN_);
	Lowtri_struct* _Lowtri = (Lowtri_struct*)malloc(sizeof(Lowtri_struct));
	_Lowtri->trans_matrix = trans_mat;
	_Lowtri->Lowtri_matrix = _mat;

//	printf(">>Lowtri(Matrix_%x)=\n",_mat_source);
//	printf("\tMatrix_%x * Matrix_%x\n",_mat,trans_mat);
	return _Lowtri;
}

Matrix* M_Dia_Inv(Matrix* _mat_source){/*M_Inv for Dia_matrix
	对角矩阵求逆*/
	Matrix* _mat_inv = NULL;
	if(_mat_source->row != _mat_source->column){
		printf(M_Dia_Inv_002);
	}else{
		_mat_inv = Matrix_copy(_mat_source);
		MATRIX_TYPE* data = _mat_inv->data;
		int i,order = _mat_source->column;
		for(i=0;i<order;i++){
			(data)[i*(order+1)] = 1/(data[i*(order+1)]);
		}
	}
	return _mat_inv;
}

Dia_struct* M_Diatri_(Matrix* _mat_source){/*Diagonalization
	对角化*/
	Dia_struct* _Dia_instance = (Dia_struct*)malloc(sizeof(Dia_struct));
	Uptri_struct* _Uptri_ =  M_Uptri_(_mat_source);
	Lowtri_struct* _Lowtri_ =  M_Lowtri_(_Uptri_->Uptri_matrix);
	_Dia_instance->trans_leftmatrix = _Uptri_->trans_matrix;
	_Dia_instance->Diatri_matrix = _Lowtri_->Lowtri_matrix;
	_Dia_instance->trans_rightmatrix = _Lowtri_->trans_matrix;
	printf(">>Diag(Matrix_%x)=\n",_mat_source);
	printf("\tMatrixdl%x * Matrix_d%x * Matrixr_%x\n",_Uptri_->trans_matrix,_Lowtri_->Lowtri_matrix,_Lowtri_->trans_matrix);
	return _Dia_instance;
}

Matrix* M_Inverse(Matrix* _mat){/*Matrix_Inverse
	矩阵求逆*/
	Uptri_struct* _Uptri_  =  M_Uptri_4inv(_mat);
	Lowtri_struct* _Lowtri_ =  M_Lowtri_4inv(_Uptri_->Uptri_matrix);
	Matrix* _mat_dia_inv = M_Dia_Inv(_Lowtri_->Lowtri_matrix);
	Matrix* _mat_inv = M_mul(M_mul(_Lowtri_->trans_matrix,_mat_dia_inv),_Uptri_->trans_matrix);
	printf(">>Inv(Matrix_%x)=\n",_mat);
	printf("\tMatrix_inv_%x\n",_mat_inv);
	return _mat_inv;
}

int M_Swap(Matrix* _mat,int _line_1,int _line_2,int line_setting){/*Swap Line
	交换指定行和列*/
	_line_1 = _line_1-1;
	_line_2 = _line_2-1;
	int i;
	MATRIX_TYPE temp;
	if (line_setting == _ROW_){
		if((_line_1<_mat->row)&&(_line_2<_mat->row)){
			for (i=0;i<(_mat->column);i++){
				temp = _mat->data[_line_1*(_mat->column)+i];
				_mat->data[_line_1*(_mat->column)+i] = _mat->data[_line_2*(_mat->column)+i];
				_mat->data[_line_2*(_mat->column)+i] = temp;
				}
			}else{
				printf(M_swap_004);
				system("pause");
			}
	}else{
		if((_line_1<_mat->column)&&(_line_2<_mat->column)){
			for (i=0;i<(_mat->row);i++){
				temp = _mat->data[_line_1+(_mat->column)*i];
				_mat->data[_line_1+(_mat->column)*i] = _mat->data[_line_2+(_mat->column)*i];
				_mat->data[_line_2+(_mat->column)*i] = temp;
			}
		}else{
			printf(M_swap_004);
				system("pause");
		}
	}
	return 0;
}

Matrix* M_Cut(Matrix* _mat,int row_head,int row_tail,int column_head,int column_tail){/*Cut_out_part_of_Matrix
	切取部分矩阵*/
	Matrix* mat_result = NULL;
	if (row_tail<0){
		if (row_tail == _END_){
			row_tail = _mat->row;
		}else{
			printf(M_Cut_007);
			system("pause");
		}
	}

	if (row_head<0){
		if (row_head == _END_){
			row_head = _mat->row;
		}else{
			printf(M_Cut_007);
			system("pause");
		}
	}

	if (column_tail<0){
		if (column_tail == _END_){
			column_tail = _mat->column;
		}else{
			printf(M_Cut_007);
			system("pause");
		}
	}

	if (column_head<0){
		if (column_head == _END_){
			column_head = _mat->column;
		}else{
			printf(M_Cut_007);
			system("pause");
		}
	}

	if ((row_tail>_mat->row)||(column_tail>>_mat->column)){
		printf(M_Cut_005);
		system("pause");
	}else{
		if ((row_head>row_tail)||(column_head>column_tail)){
			printf(M_Cut_006);
			system("pause");
		}else{
				row_head = row_head -1;
				column_head = column_head-1;
				mat_result = (Matrix*)malloc(sizeof(Matrix));
				mat_result->row = row_tail-row_head;
				mat_result->column = column_tail-column_head;
				mat_result->data = (MATRIX_TYPE*)malloc(sizeof(MATRIX_TYPE)*(mat_result->row)*(mat_result->column));
				int i,j;
				for(i=0;i<(row_tail-row_head);i++){
					for(j=0;j<(column_tail-column_head);j++){
						mat_result->data[i*(mat_result->column)+j] = _mat->data[(i+row_head)*(_mat->column)+(j+column_head)];
					}
				}
		}
	}
	return mat_result;
}
Matrix* M_T(Matrix* _mat_source){/*Transpose
	转置*/
	Matrix* _mat = (Matrix*)malloc(sizeof(Matrix));//动态分配内存空间
	_mat->column = _mat_source->row;
	_mat->row = _mat_source->column ;
	MATRIX_TYPE* data = (MATRIX_TYPE*)malloc(sizeof(MATRIX_TYPE)*(_mat->column)*_mat->row);
	_mat->data = data;
	int i,j;
	for (i=0;i<(_mat->row);i++){
		for(j=0;j<(_mat->column);j++){
			_mat->data[i*(_mat->column)+j] = _mat_source->data[j*(_mat->row)+i];
			//_mat->data[i*(_mat->column)+j] =1;
		}
	}
	return _mat;
}

int M_free(Matrix* _mat){
	free(_mat->data);
	printf(">>Matrix_%x has been freed.\n",_mat);
	free(_mat);
	return 0;
}

MATRIX_TYPE M_tr(Matrix* _mat){/*Trace
	矩阵的迹*/
	MATRIX_TYPE _tr_mat = 0;
	if (_mat->column == _mat->row){
		int i;
		for (i=0;i<_mat->column;i++){
			_tr_mat += _mat->data[i*(_mat->column+1)];
		}
	}else{
		printf(M_tr_008);
		system("poause");
	}
	return _tr_mat;
}

MATRIX_TYPE M_det(Matrix* _mat_){/*Determinant
	行列式*/
	MATRIX_TYPE _det_mat = 0;
	if (_mat_->column == _mat_->row){
		Uptri_struct* _Uptri_ =  M_Uptri_(_mat_);
		Matrix* _mat = _Uptri_->Uptri_matrix;
		_det_mat = 1;
		int i;
		for (i=0;i<_mat->column;i++){
			_det_mat *= _mat->data[i*(_mat->column+1)];
		}
	}else{
		printf(M_det_009);
		system("poause");
	}
	return 	_det_mat;
}

Matrix* M_full(Matrix* _mat,int row_up,int row_down,int column_left,int column_right,MATRIX_TYPE full_data){/*Full
	填充矩阵*/
	Matrix* mat_result = NULL;
	mat_result = (Matrix*)malloc(sizeof(Matrix));
	mat_result->row = (_mat->row+row_up+row_down);
	mat_result->column = (_mat->column+column_left+column_right);
	mat_result->data = (MATRIX_TYPE*)malloc(sizeof(MATRIX_TYPE)*(mat_result->row)*(mat_result->column));
	int i,j;
	for(i=0;i<mat_result->row;i++){
		for(j=0;j<mat_result->column;j++){
			if((i>=row_up)&&(i<(row_up+_mat->row))){/*这里的双判断，可以优化*/
				if((j>=column_left)&&(j<(column_left+_mat->column))){
					mat_result->data[i*(mat_result->column)+j] = _mat->data[(_mat->column)*(i-row_up)+(j-column_left)];
				}else{
					mat_result->data[i*(mat_result->column)+j] = full_data;
				}
			}else{
				mat_result->data[i*(mat_result->column)+j] = full_data;
			}
		}
	}
	printf(">>Full<U%d,D%d,L%d,R%d>(Matrix_%x)=\n",row_up,row_down,column_left,column_right,_mat);
	printf("\tMatrix_%x\n",mat_result);
	return mat_result;
}

double fabs(double a)
{
    double temp=0;
    if(a<=0)
    {
        temp=-a;
    }
    else
    {
        temp=a;
    }
    return temp;

}

Matrix* M_zero(Matrix* _mat){/*Matrix Zero mean
	对矩阵零均值化
	每一行都减去这一行的均值 */
	Matrix* _mat_result = NULL;

	_mat_result = Matrix_copy(_mat);
	int row = _mat->row;
	int column = _mat->column;
	int i,j;
    MATRIX_TYPE count=0;
	for(i=0;i<row;i++)
    {
        for(j=0;j<column;j++)
        {
			count=count+_mat->data[i*column+j];
		}
        count=count/column;
        for(j=0;j<column;j++)
        {
			_mat_result->data[i*column+j]=_mat->data[i*column+j]-count;
		}
        count=0;
	}



	return _mat_result;
}

Matrix* M_multi_k(Matrix* _mat,MATRIX_TYPE k){/*Matrix Multiply by a constant k
	矩阵乘以常数 k  */
	Matrix* _mat_result = NULL;
	_mat_result = Matrix_copy(_mat);
	int row = _mat->row;
	int column = _mat->column;
	int i,j;
	for(i=0;i<row;i++)
    {
        for(j=0;j<column;j++)
        {
			_mat_result->data[i*column+j]=_mat->data[i*column+j]*k;
		}
	}



	return _mat_result;
}

double max_one(double x,double y)
{
    if(x>=y)
    {
       return x;
    }
    else
    {
       return y;
    }
}
double min_one(double x,double y)
{
    if(x<=y)
    {
       return x;
    }
    else
    {
       return y;
    }
}

