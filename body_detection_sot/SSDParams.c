#include "SSDParams.h"



PI_L2 Alps * anchor_layer_1;
PI_L2 float n_aspect_ratios_1[]= {0.333333,0.500000,1.000000,2.000000,3.000000,};
PI_L2 float n_variances_1[]={0.100000,0.100000,0.100000,0.100000,};
PI_L2 anchorWH_t anchorWH_1[]={
{6.928203,20.784609},
{8.485281,16.970562},
{12.000000,12.000000},
{20.784611,20.784611},
{16.970562,8.485281},
{20.784609,6.928203},
};
int initAnchorLayer_1(){
	anchor_layer_1 = (Alps*) pmsis_l2_malloc(sizeof(Alps));
	if(anchor_layer_1==NULL) return 1;
	anchor_layer_1->feature_map_width  = 80;
	anchor_layer_1->feature_map_height = 60;
	anchor_layer_1->n_classes  = 2;
	anchor_layer_1->img_width  = 160;
	anchor_layer_1->img_height = 120;
	anchor_layer_1->this_scale = 0.100000;
	anchor_layer_1->next_scale = 0.300000;
	anchor_layer_1->anchor_params = 4;
	anchor_layer_1->iou_thr = 0.100000;
	anchor_layer_1->step_height= 2.000000;
	anchor_layer_1->step_width = 2.000000;
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
PI_L2 float n_aspect_ratios_2[]= {0.250000,0.333333,0.500000,1.000000,2.000000,3.000000,};
PI_L2 float n_variances_2[]={0.100000,0.100000,0.100000,0.100000,};
PI_L2 anchorWH_t anchorWH_2[]={
{18.000000,72.000000},
{20.784611,62.353828},
{25.455845,50.911690},
{36.000000,36.000000},
{46.475800,46.475800},
{50.911690,25.455845},
{62.353828,20.784609},
};
int initAnchorLayer_2(){
	anchor_layer_2 = (Alps*) pmsis_l2_malloc(sizeof(Alps));
	if(anchor_layer_2==NULL) return 1;
	anchor_layer_2->feature_map_width  = 40;
	anchor_layer_2->feature_map_height = 30;
	anchor_layer_2->n_classes  = 2;
	anchor_layer_2->img_width  = 160;
	anchor_layer_2->img_height = 120;
	anchor_layer_2->this_scale = 0.300000;
	anchor_layer_2->next_scale = 0.500000;
	anchor_layer_2->anchor_params = 4;
	anchor_layer_2->iou_thr = 0.100000;
	anchor_layer_2->step_height= 4.000000;
	anchor_layer_2->step_width = 4.000000;
	anchor_layer_2->offset_height = 0.500000;
	anchor_layer_2->offset_width  = 0.500000;
	anchor_layer_2->aspect_ratios = n_aspect_ratios_2;
	anchor_layer_2->variances = n_variances_2;
	anchor_layer_2->two_boxes_for_ar1 = true;
	anchor_layer_2->confidence_thr = 13106;
	anchor_layer_2->n_aspect_ratios =  6;
	anchor_layer_2->n_anchors   =  7;
	anchor_layer_2->n_variances =  4;
	anchor_layer_2->anchorsWH = anchorWH_2;
	return 0;
}




PI_L2 Alps * anchor_layer_3;
PI_L2 float n_aspect_ratios_3[]= {0.200000,0.250000,0.333333,0.500000,1.000000,2.000000,3.000000,};
PI_L2 float n_variances_3[]={0.100000,0.100000,0.100000,0.100000,};
PI_L2 anchorWH_t anchorWH_3[]={
{26.832815,134.164078},
{30.000000,120.000000},
{34.641018,103.923050},
{42.426407,84.852814},
{60.000000,60.000000},
{70.992958,70.992958},
{84.852814,42.426407},
{103.923050,34.641018},
};
int initAnchorLayer_3(){
	anchor_layer_3 = (Alps*) pmsis_l2_malloc(sizeof(Alps));
	if(anchor_layer_3==NULL) return 1;
	anchor_layer_3->feature_map_width  = 20;
	anchor_layer_3->feature_map_height = 15;
	anchor_layer_3->n_classes  = 2;
	anchor_layer_3->img_width  = 160;
	anchor_layer_3->img_height = 120;
	anchor_layer_3->this_scale = 0.500000;
	anchor_layer_3->next_scale = 0.700000;
	anchor_layer_3->anchor_params = 4;
	anchor_layer_3->iou_thr = 0.100000;
	anchor_layer_3->step_height= 8.000000;
	anchor_layer_3->step_width = 8.000000;
	anchor_layer_3->offset_height = 0.500000;
	anchor_layer_3->offset_width  = 0.500000;
	anchor_layer_3->aspect_ratios = n_aspect_ratios_3;
	anchor_layer_3->variances = n_variances_3;
	anchor_layer_3->two_boxes_for_ar1 = true;
	anchor_layer_3->confidence_thr = 13106;
	anchor_layer_3->n_aspect_ratios =  7;
	anchor_layer_3->n_anchors   =  8;
	anchor_layer_3->n_variances =  4;
	anchor_layer_3->anchorsWH = anchorWH_3;
	return 0;
}




PI_L2 Alps * anchor_layer_4;
PI_L2 float n_aspect_ratios_4[]= {0.250000,0.333333,0.500000,1.000000,2.000000,3.000000,};
PI_L2 float n_variances_4[]={0.100000,0.100000,0.100000,0.100000,};
PI_L2 anchorWH_t anchorWH_4[]={
{42.000000,168.000000},
{48.497425,145.492264},
{59.396969,118.793938},
{84.000000,84.000000},
{95.247047,95.247047},
{118.793938,59.396969},
{145.492264,48.497421},
};
int initAnchorLayer_4(){
	anchor_layer_4 = (Alps*) pmsis_l2_malloc(sizeof(Alps));
	if(anchor_layer_4==NULL) return 1;
	anchor_layer_4->feature_map_width  = 10;
	anchor_layer_4->feature_map_height = 7;
	anchor_layer_4->n_classes  = 2;
	anchor_layer_4->img_width  = 160;
	anchor_layer_4->img_height = 120;
	anchor_layer_4->this_scale = 0.700000;
	anchor_layer_4->next_scale = 0.900000;
	anchor_layer_4->anchor_params = 4;
	anchor_layer_4->iou_thr = 0.100000;
	anchor_layer_4->step_height= 17.142857;
	anchor_layer_4->step_width = 16.000000;
	anchor_layer_4->offset_height = 0.500000;
	anchor_layer_4->offset_width  = 0.500000;
	anchor_layer_4->aspect_ratios = n_aspect_ratios_4;
	anchor_layer_4->variances = n_variances_4;
	anchor_layer_4->two_boxes_for_ar1 = true;
	anchor_layer_4->confidence_thr = 13106;
	anchor_layer_4->n_aspect_ratios =  6;
	anchor_layer_4->n_anchors   =  7;
	anchor_layer_4->n_variances =  4;
	anchor_layer_4->anchorsWH = anchorWH_4;
	return 0;
}

