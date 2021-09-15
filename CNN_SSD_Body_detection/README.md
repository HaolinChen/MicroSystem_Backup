# CNN-SSD body detection
2021/09/12  
Use GWT template.  
Use Hyper ram to store output directly.  
Input: 128*160 gray pictures. 
### Done:
1.Test pictures from PC.  
2.Test pictures from camera (real time) and send to PC with UART.  
3.Improve model performance.(Fixed SSDBasicKernels.c bug!!!)  
4.Add wifi streamer.  
### Not Done:

   
### Issue:
1.Need to remove the following code at the line 6 of the file gap_sdk/tools/rules/at_common_decl.mk    
```python 
MODEL_LIB_POW2 += $(TILER_CNN_KERNEL_PATH)/CNN_Conv_DW_BasicKernels.c
```
Otherwise, there will be an error.
#

### Reference
refer GreenWaves-Technologies [nn_menu](https://github.com/GreenWaves-Technologies/nn_menu) and [gap_sdk](https://github.com/GreenWaves-Technologies/gap_sdk) for details

