# Copyright (C) 2020 GreenWaves Technologies
# All rights reserved.

# This software may be modified and distributed under the terms
# of the BSD license.  See the LICENSE file for details.

ifndef GAP_SDK_HOME
  $(error Source sourceme in gap_sdk first)
endif

io=host

MAIN?=main.c

include model_decl.mk

APP = SSD_ResNet

APP_SRCS += $(MAIN) ImgIO.c ImageDraw.c $(CNN_LIB)
APP_SRCS += BUILD_MODEL_SSD/cnn_ssdKernels.c SSDKernels.c SSDBasicKernels.c SSDParams.c BUILD_MODEL_RESNET/resnetKernels.c


PMSIS_OS=pulpos

JENKINS?=0
ifeq ($(JENKINS), 1)
	APP_CFLAGS += -DONE_ITER -DTEST
else
	ifeq ($(platform), gvsoc)
		APP_CFLAGS += -DPERF -DONE_ITER
	else
		APP_CFLAGS += -DSILENT -DHAVE_HIMAX -DHAVE_LCD
	endif
endif

CLUSTER_STACK_SIZE=6096
CLUSTER_SLAVE_STACK_SIZE=1024
ifeq '$(TARGET_CHIP_FAMILY)' 'GAP9'
	FREQ_CL?=50
	FREQ_FC?=50
else
	ifeq '$(TARGET_CHIP)' 'GAP8_V3'
		FREQ_CL?=175
	else
		FREQ_CL?=50
	endif
	FREQ_FC?=250
endif
# APP_CFLAGS += -g -w #-DNORM_ROUND
# APP_CFLAGS += -O3 -s -mno-memcpy -fno-tree-loop-distribute-patterns
APP_CFLAGS += -O3
APP_CFLAGS += -I. -I./helpers -I$(TILER_EMU_INC) -I$(TILER_INC) $(CNN_LIB_INCLUDE)
APP_CFLAGS += -DCLUSTER_STACK_SIZE=$(CLUSTER_STACK_SIZE) -DCLUSTER_SLAVE_STACK_SIZE=$(CLUSTER_SLAVE_STACK_SIZE)
APP_CFLAGS += -DFREQ_CL=$(FREQ_CL) -DFREQ_FC=$(FREQ_FC)
APP_CFLAGS += -IBUILD_MODEL_SSD -IBUILD_MODEL_RESNET
ifeq ($(PERF), 1)
	APP_CFLAGS += -DPERF
endif

MODEL_TENSORS = BUILD_MODEL_SSD/cnn_ssd_L3_Flash_Const.dat BUILD_MODEL_RESNET/resnet_L3_Flash_Const.dat
READFS_FILES=$(abspath $(MODEL_TENSORS))
PLPBRIDGE_FLAGS += -f



BUILD_MODEL_SSD/cnn_ssdKernels.c: 
	make -f cnnssd.mk model SSD_model
BUILD_MODEL_RESNET/resnetKernels.c: 
	make -f resnet.mk model

# all depends on the models
all:: BUILD_MODEL_SSD/cnn_ssdKernels.c BUILD_MODEL_RESNET/resnetKernels.c

clean::
	rm -rf BUILD

clean_models:
	rm -rf BUILD_MODEL*
	cd SSDParamsGenerator && $(MAKE) clean
	rm -rf SSDParams.c SSDParams.h
	rm -rf SSDKernels.c SSDKernels.h
	rm -rf GenTile GenSSDTile

$(info APP_SRCS... $(APP_SRCS))
$(info APP_CFLAGS... $(APP_CFLAGS))
include $(RULES_DIR)/pmsis_rules.mk

