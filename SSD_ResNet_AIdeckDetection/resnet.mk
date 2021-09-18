# FROM_CAMERA=1
#################################
#0.define quantization_bits
QUANTIZATION_BITS=16# use different build folder name
$(info Building GAP8 mode with $(QUANTIZATION_BITS) bit quantization)

ifeq ($(QUANTIZATION_BITS),8)
  GAP_FLAGS += -DQUANTIZATION_8BIT
  NNTOOL_SCRIPT=model/nntool_script8
  MODEL_SUFFIX = _8BIT
else
  ifeq ($(QUANTIZATION_BITS),16)
    GAP_FLAGS += -DQUANTIZATION_16BIT
    NNTOOL_SCRIPT=model/nntool_RESNET_script16
    MODEL_SUFFIX = _RESNET
  else
    $(error Don't know how to build with this bit width)
  endif
endif

########################################
#define some VARs
#1.define some name-VARs
NAME=resnet
MAIN=$(NAME).c
# MODEL_NAME=${NAME}.onnx
MODEL_NAME=${NAME}.tflite
MODEL_BUILD=BUILD_MODEL${MODEL_SUFFIX}
# MODEL_TFLITE =BUILD_MODEL_16BIT/body_detection.tflite
MODEL_TFLITE =model/${MODEL_NAME}
MODEL_STATE =${MODEL_BUILD}/${NAME}.json
# NNTOOL_SCRIPT=model/nntool_RESNET_script16
MODEL_SRC = $(NAME)Model.c
MODEL_GEN = $(MODEL_BUILD)/$(NAME)Kernels
MODEL_GEN_C = $(addsuffix .c, $(MODEL_GEN))
TENSORS_DIR=${MODEL_BUILD}/tensors
MODEL_TENSORS = $(MODEL_BUILD)/$(NAME)_L3_Flash_Const.dat #should include tensors
MODEL_HEADER=${NAME}Info.h

MODEL_GEN_EXE=./GenTile


MODEL_POW2=1
include common.mk
#2. define necessary VARs
#1)_SQ8/_POW2 
#many VARs can be found in common.mk
RESIZE_GEN=ResizeGenerator.c
####################################
#2)
# Here we set the memory allocation for the generated kernels
# REMEMBER THAT THE L1 MEMORY ALLOCATION MUST INCLUDE SPACE
# FOR ALLOCATED STACKS!
# FC stack size:
MAIN_STACK_SIZE=1024
# Cluster PE0 stack size:
CLUSTER_STACK_SIZE=6096
# Cluster PE1-PE7 stack size:
CLUSTER_SLAVE_STACK_SIZE=1024
TOTAL_STACK_SIZE=$(shell expr $(CLUSTER_STACK_SIZE) \+ $(CLUSTER_SLAVE_STACK_SIZE) \* 7)
#define FC,L1/L2/L3 memory
FREQ_FC?=250
FREQ_CL?=175
MODEL_L1_MEMORY=$(shell expr 60000 \- $(TOTAL_STACK_SIZE))
MODEL_L2_MEMORY=200000
MODEL_L3_MEMORY=8388608

MODEL_L3_EXEC=hram
MODEL_L3_CONST=hflash
####################################
#3)
#APP_  for pmsis
pulpChip = GAP
APP = ${NAME}
#be care of APP_SRCS
# APP_SRCS += main.c ImgIO.c ImageDraw.c SSDKernels.c SSDBasicKernels.c SSDParams.c $(MODEL_GEN_C) $(CNN_LIB) 
#MODEL_COMMON_INC ?= $(GAP_SDK_HOME)/libs/gap_lib/include
APP_SRCS += $(MAIN) ImgIO.c ResizeGenerator.c ResizeBasicKernels.c $(MODEL_GEN_C) $(MODEL_COMMON_SRCS) $(CNN_LIB)
#to check?
APP_CFLAGS += -O3
APP_CFLAGS += -I. -I./helpers -I$(TILER_EMU_INC) -I$(TILER_INC) -I$(MODEL_COMMON_INC) -I$(GEN_PATH) -I$(MODEL_BUILD) $(CNN_LIB_INCLUDE)
APP_CFLAGS += -DCLUSTER_STACK_SIZE=$(CLUSTER_STACK_SIZE) -DCLUSTER_SLAVE_STACK_SIZE=$(CLUSTER_SLAVE_STACK_SIZE)
APP_CFLAGS += -DFREQ_CL=$(FREQ_CL) -DFREQ_FC=$(FREQ_FC)
ifeq ($(SILENT),1) #mute printf
  APP_CFLAGS += -DSILENT=1
endif


ifeq ($(FROM_CAMERA),1)
  APP_CFLAGS += -DFROM_CAMERA=1
endif

ifeq ($(NO_BRIDGE),1)
  APP_CFLAGS += -DNO_BRIDGE=1
endif


ifeq ($(platform),gvsoc)
  $(info Platform is GVSOC)
  READFS_FILES=$(MODEL_TENSORS)
else
  $(info Platform is GAPUINO)
  PLPBRIDGE_FLAGS = -f
  READFS_FILES=$(MODEL_TENSORS)
endif


# all depends on the model
all:: model

clean::
	rm -rf ${MODEL_BUILD}


.PHONY: model

include model_rules.mk
include $(RULES_DIR)/pmsis_rules.mk