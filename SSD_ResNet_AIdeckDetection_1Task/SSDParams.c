#include "SSDParams.h"



PI_L2 Alps * anchor_layer_1;
PI_L2 float n_aspect_ratios_1[]= {1.000000,2.000000,0.500000,3.000000,0.333333,};
PI_L2 float n_variances_1[]={0.100000,0.100000,0.200000,0.200000,};
PI_L2 anchorWH_t anchorWH_1[]={
{25.600000,25.600000},
{33.865616,33.865616},
{36.203869,18.101934},
{18.101934,36.203869},
{44.340500,14.780168},
{14.780168,44.340500},
};
int initAnchorLayer_1(){
	anchor_layer_1 = (Alps*) pmsis_l2_malloc(sizeof(Alps));
	if(anchor_layer_1==NULL) return 1;
	anchor_layer_1->feature_map_width  = 20;
	anchor_layer_1->feature_map_height = 16;
	anchor_layer_1->n_classes  = 2;
	anchor_layer_1->img_width  = 160;
	anchor_layer_1->img_height = 128;
	anchor_layer_1->this_scale = 0.200000;
	anchor_layer_1->next_scale = 0.350000;
	anchor_layer_1->anchor_params = 4;
	anchor_layer_1->iou_thr = 0.100000;
	anchor_layer_1->step_height= 8.000000;
	anchor_layer_1->step_width = 8.000000;
	anchor_layer_1->offset_height = 0.500000;
	anchor_layer_1->offset_width  = 0.500000;
	anchor_layer_1->aspect_ratios = n_aspect_ratios_1;
	anchor_layer_1->variances = n_variances_1;
	anchor_layer_1->two_boxes_for_ar1 = true;
	anchor_layer_1->confidence_thr = 13106;
	anchor_layer_1->n_aspect_ratios =  5;
	anchor_layer_1->n_anchors   =  6;
	anchor_layer_1->n_variances =  4;
	anchor_layer_1->anchorsWH = anchorWH_1;
	return 0;
}




PI_L2 Alps * anchor_layer_2;
PI_L2 float n_aspect_ratios_2[]= {1.000000,2.000000,0.500000,3.000000,0.333333,};
PI_L2 float n_variances_2[]={0.100000,0.100000,0.200000,0.200000,};
PI_L2 anchorWH_t anchorWH_2[]={
{44.799999,44.799999},
{53.546242,53.546242},
{63.356766,31.678383},
{31.678383,63.356766},
{77.595879,25.865292},
{25.865292,77.595871},
};
int initAnchorLayer_2(){
	anchor_layer_2 = (Alps*) pmsis_l2_malloc(sizeof(Alps));
	if(anchor_layer_2==NULL) return 1;
	anchor_layer_2->feature_map_width  = 10;
	anchor_layer_2->feature_map_height = 8;
	anchor_layer_2->n_classes  = 2;
	anchor_layer_2->img_width  = 160;
	anchor_layer_2->img_height = 128;
	anchor_layer_2->this_scale = 0.350000;
	anchor_layer_2->next_scale = 0.500000;
	anchor_layer_2->anchor_params = 4;
	anchor_layer_2->iou_thr = 0.100000;
	anchor_layer_2->step_height= 16.000000;
	anchor_layer_2->step_width = 16.000000;
	anchor_layer_2->offset_height = 0.500000;
	anchor_layer_2->offset_width  = 0.500000;
	anchor_layer_2->aspect_ratios = n_aspect_ratios_2;
	anchor_layer_2->variances = n_variances_2;
	anchor_layer_2->two_boxes_for_ar1 = true;
	anchor_layer_2->confidence_thr = 13106;
	anchor_layer_2->n_aspect_ratios =  5;
	anchor_layer_2->n_anchors   =  6;
	anchor_layer_2->n_variances =  4;
	anchor_layer_2->anchorsWH = anchorWH_2;
	return 0;
}




PI_L2 Alps * anchor_layer_3;
PI_L2 float n_aspect_ratios_3[]= {1.000000,2.000000,0.500000,3.000000,0.333333,};
PI_L2 float n_variances_3[]={0.100000,0.100000,0.200000,0.200000,};
PI_L2 anchorWH_t anchorWH_3[]={
{64.000000,64.000000},
{72.971230,72.971230},
{90.509666,45.254833},
{45.254833,90.509666},
{110.851250,36.950417},
{36.950417,110.851250},
};
int initAnchorLayer_3(){
	anchor_layer_3 = (Alps*) pmsis_l2_malloc(sizeof(Alps));
	if(anchor_layer_3==NULL) return 1;
	anchor_layer_3->feature_map_width  = 5;
	anchor_layer_3->feature_map_height = 4;
	anchor_layer_3->n_classes  = 2;
	anchor_layer_3->img_width  = 160;
	anchor_layer_3->img_height = 128;
	anchor_layer_3->this_scale = 0.500000;
	anchor_layer_3->next_scale = 0.650000;
	anchor_layer_3->anchor_params = 4;
	anchor_layer_3->iou_thr = 0.100000;
	anchor_layer_3->step_height= 32.000000;
	anchor_layer_3->step_width = 32.000000;
	anchor_layer_3->offset_height = 0.500000;
	anchor_layer_3->offset_width  = 0.500000;
	anchor_layer_3->aspect_ratios = n_aspect_ratios_3;
	anchor_layer_3->variances = n_variances_3;
	anchor_layer_3->two_boxes_for_ar1 = true;
	anchor_layer_3->confidence_thr = 13106;
	anchor_layer_3->n_aspect_ratios =  5;
	anchor_layer_3->n_anchors   =  6;
	anchor_layer_3->n_variances =  4;
	anchor_layer_3->anchorsWH = anchorWH_3;
	return 0;
}




PI_L2 Alps * anchor_layer_4;
PI_L2 float n_aspect_ratios_4[]= {1.000000,2.000000,0.500000,3.000000,0.333333,};
PI_L2 float n_variances_4[]={0.100000,0.100000,0.200000,0.200000,};
PI_L2 anchorWH_t anchorWH_4[]={
{83.199997,83.199997},
{92.302109,92.302109},
{117.662567,58.831284},
{58.831284,117.662567},
{144.106628,48.035542},
{48.035542,144.106613},
};
int initAnchorLayer_4(){
	anchor_layer_4 = (Alps*) pmsis_l2_malloc(sizeof(Alps));
	if(anchor_layer_4==NULL) return 1;
	anchor_layer_4->feature_map_width  = 2;
	anchor_layer_4->feature_map_height = 2;
	anchor_layer_4->n_classes  = 2;
	anchor_layer_4->img_width  = 160;
	anchor_layer_4->img_height = 128;
	anchor_layer_4->this_scale = 0.650000;
	anchor_layer_4->next_scale = 0.800000;
	anchor_layer_4->anchor_params = 4;
	anchor_layer_4->iou_thr = 0.100000;
	anchor_layer_4->step_height= 64.000000;
	anchor_layer_4->step_width = 80.000000;
	anchor_layer_4->offset_height = 0.500000;
	anchor_layer_4->offset_width  = 0.500000;
	anchor_layer_4->aspect_ratios = n_aspect_ratios_4;
	anchor_layer_4->variances = n_variances_4;
	anchor_layer_4->two_boxes_for_ar1 = true;
	anchor_layer_4->confidence_thr = 13106;
	anchor_layer_4->n_aspect_ratios =  5;
	anchor_layer_4->n_anchors   =  6;
	anchor_layer_4->n_variances =  4;
	anchor_layer_4->anchorsWH = anchorWH_4;
	return 0;
}

