# CNN-SSD + ResNet Workflow
2021/09/29  HaolinChen  
PC Input: 160x128 gray pictures.  
Camera Input: 324x244 gray pictures.  

### Done:
1.Test pictures from PC.  
2.Tested on gvsoc and gap8.  
2.Tested on camera.  
2.Fixed some BUGs.  

### Not Done:
1.Improve performance.  

### Workflow:

![picture](./pic/workflow.png)

### Picture Processing Strategy:

1.Fill the blank space with gray scale pixel, like 128.

![picture](./pic/fill.png)

2.Resize the cropped box directly.

![picture](./pic/resize.png)

