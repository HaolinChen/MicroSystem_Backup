import serial
import time
import numpy
numpy.set_printoptions(suppress=True)

import matplotlib.pyplot as plt

try:
    x = numpy.loadtxt('G:\\MatlabCode\\VAD_NEW\\dataset\\c_dataset\\C_LTSDtest5dBNEW_19_198_501_1000.txt')
    y = numpy.loadtxt('G:\\MatlabCode\\VAD_NEW\\dataset\\c_dataset\\C_LTSDtest5dBNEW_LABEL_19_198_501_1000.txt')
    # a = 3.1415927
    # a_send = str(a) + "\r\n"
    # 端口，GNU / Linux上的/ dev / ttyUSB0 等 或 Windows上的 COM3 等
    port_open = "COM4"
    # 波特率，标准值之一：50,75,110,134,150,200,300,600,1200,1800,2400,4800,9600,19200,38400,57600,115200
    bps = 115200
    # 超时设置,None：永远等待操作，0为立即返回请求结果，其他值为等待超时时间(单位为秒）
    timex = 5  # which controls the behavior of read()
    # 打开串口，并得到串口对象
    ser = serial.Serial(port_open, bps, timeout=timex)
    print("串口详情参数：", ser)
    frame_size = 64*15
    # frame_size = 6
    frame_num = 100
    T = 0   # num of the present frame
    start_num = 400  # 起始点
    i = 0 + start_num*frame_size
    error_count = 0  # 统计接收错误的次数
    str_get = 0
    num_double = 0
    flag = 1
    flag_e = 0  # 判断是否使用了科学计数法
    y_predict = numpy.zeros(shape=(frame_num))
    while True:
        # x_send = str(x[i])+"\r\n"
        # x_send = str(x[i])
        x_send = format(x[i], '.8f')
        real = x_send.encode("utf-8")
        result = ser.write(real)
        time.sleep(0.01)
        if ser.in_waiting:
            str_get = ser.read(ser.in_waiting).decode("gbk")
            print("收到数据：", str_get)
        for j in range(0, len(x_send)-2):  # 小数点后6位相同就认为是相同的
            if x_send[j] != str_get[j]:
                flag = 0
        if flag == 1 or error_count == 5:  # 退出标志（换个思路）
            x_send = 't'
            result = ser.write(x_send.encode("utf-8"))
            i = i + 1
            error_count = 0
            print(i)
        else:
            error_count = error_count + 1
            x_send = 'f'
            result = ser.write(x_send.encode("utf-8"))
        flag = 1

        if i == frame_size+(T + start_num)*frame_size:
            print("********Frame_Done：", T)
            time.sleep(0.3)
            if ser.in_waiting:
                str_get = ser.read(ser.in_waiting).decode("gbk")
                print("-------------GET Predicted label：", str_get)
                if str_get == '0':
                    y_predict[T] = -1
                elif str_get == '1':
                    y_predict[T] = 1
            T = T + 1
        if T == frame_num:
            break
    print("---------------")
    ser.close()  # 关闭串口
    # Performance evaluation
    TP = 0  # True positive num
    TN = 0  # True negative num
    FP = 0  # False positive num
    FN = 0  # False negative num
    for i in range(0, frame_num):
        print("-------------Predicted label：", y_predict[i])
        if y_predict[i] == y[i + start_num]:
            if y[i + start_num] == 1:
                TP = TP + 1
            if y[i + start_num] == -1:
                TN = TN + 1
        if y_predict[i] != y[i + start_num]:
            if y[i + start_num] == 1:
                FN = FN + 1
            if y[i + start_num] == -1:
                FP = FP + 1
    accuracy = (TP+TN)/frame_num
    print("TP = ", TP)
    print("TN = ", TN)
    print("FP = ", FP)
    print("FN = ", FN)
    print("Accuracy = ", accuracy)
    TPR = TP/(TP+FN)
    print("TPR = ", TPR)

    for i in range(0, frame_num):
        y[i + start_num] = (y[i + start_num]+1)/2
        y_predict[i] = (y_predict[i]+1)/2
    pl = plt.figure(figsize=(10,10))
    pl.add_subplot(2, 1, 1)
    x = [i for i in range(1, len(y_predict)+1)]
    plt.bar(x, y[start_num: start_num + len(y_predict)], color="r", label="label")
    plt.minorticks_on()
    plt.title("Test Dataset 5dB  401~500 Frames True Label")

    pl.add_subplot(2,1,2)
    x = [i for i in range(1, len(y_predict)+1)]
    print(y_predict)
    plt.bar(x, y_predict, color="b", label="predict label")
    plt.minorticks_on()
    plt.title("Test Dataset 5dB  401~500 Frames Predict Label")
    plt.show()


except Exception as e:
    print("---异常---：", e)
