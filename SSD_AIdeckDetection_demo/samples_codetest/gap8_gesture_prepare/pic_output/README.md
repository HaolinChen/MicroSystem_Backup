# CNN-SSD + ResNet Performance Test
2021/11/16  HaolinChen  
PC Input: 324x244 gray pictures.  
Camera Input: 324x244 gray pictures.  

### Test Dataset Information:

| Label |   Text   | Total Numbers |
| :---: | :------: | :-----------: |
|   0   | backward |      59       |
|   1   |   down   |      64       |
|   2   | forward  |      59       |
|   3   |   left   |      63       |
|   4   |  right   |      62       |
|   5   |    up    |      66       |

### Detection Rate:

| Confidence | backward |   down   | forward  |   left   |  right   |    up    |  Total   |
| :--------: | :------: | :------: | :------: | :------: | :------: | :------: | :------: |
|    0.25    | 0.644068 | 0.609375 | 0.305085 | 0.380952 | 0.483871 | 0.863636 | 0.547831 |
### Accuracy:

| Confidence | backward |   down   | forward  |   left   |  right   |    up    | Total |
| :--------: | :------: | :------: | :------: | :------: | :------: | :------: | :---: |
|    0.25    |    0     | 0.125000 | 0.152542 | 0.206349 | 0.112903 | 0.393939 |       |


