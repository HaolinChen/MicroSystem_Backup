/*
%% IMFORMATION
%% LTSD_chl
% Author: Haolin Chen
% Email:1170100218@stu.hit.edu.cn
% Github:
% Date: 2020.10.19
% Case: VAD LTSD Operation
% Dtailed: the code_file of LTSD_chl.c
*/

#ifndef _LTSD_CHL_H_
#define _LTSD_CHL_H_

#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

typedef struct _LTSD {
	/*LTSD
	parameter*/
	int order;
	int windowsize;
	double amplitude;
	double avgnoise;
	int windownum;
	double alpha;
	double speechThr;
	double firstWindownum;
} LTSD;

// description: return one featurevector( one frame, k dimensions )
// ltsd: ltsd parameters
// signal: one frame signal
// K: K features for each frame
// T: the Tth frame
Matrix* compute(LTSD* ltsd,Matrix* signal, int K,int T);
void Array_zero(int row,int column,double* a);
Matrix* ltse_CHL(LTSD* ltsd,Matrix* signal,int T);
Matrix* get_amplitude(LTSD* ltsd,Matrix* signal,int idx);
Matrix* max_vector(Matrix* a,Matrix* b); // need the same dimension








#endif



