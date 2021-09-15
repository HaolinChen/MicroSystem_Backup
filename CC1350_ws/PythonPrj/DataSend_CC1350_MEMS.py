
import serial
import time
import numpy
import matplotlib.pyplot as plt
numpy.set_printoptions(suppress=True)

try:
    # x = numpy.loadtxt('G:\\MatlabCode\\VAD_NEW\\dataset\\c_dataset\\C_LTSDtest5dBNEW_19_198_501_1000.txt')
    # y = numpy.loadtxt('G:\\MatlabCode\\VAD_NEW\\dataset\\c_dataset\\C_LTSDtest5dBNEW_LABEL_19_198_501_1000.txt')
    port_open = "COM4"
    # 波特率，标准值之一：50,75,110,134,150,200,300,600,1200,1800,2400,4800,9600,19200,38400,57600,115200
    bps = 115200
    # 超时设置,None：永远等待操作，0为立即返回请求结果，其他值为等待超时时间(单位为秒）
    timex = None  # which controls the behavior of read()
    # 打开串口，并得到串口对象
    ser = serial.Serial(port_open, bps, timeout=timex)
    print("串口详情参数：", ser)
    frame_num = 500
    y_predict = numpy.zeros(shape=frame_num)
    test_label = 1  # 提前设定测试的数据集是人声dataset还是噪声dataset
    result = ser.write('1')
    time.sleep(0.3)
    if ser.in_waiting:
        str_get = ser.read(ser.in_waiting).decode("gbk")
    print("-------------GET Predicted label：", str_get)
    for i in range(0, frame_num):
        if str_get[i] == '0':
            y_predict[i] = -1
        elif str_get[i] == '1':
            y_predict[i] = 1
    print("---------------")
    ser.close()  # 关闭串口
    # Performance evaluation
    TP = 0  # True positive num
    TN = 0  # True negative num
    FP = 0  # False positive num
    FN = 0  # False negative num
    for i in range(0, frame_num):
        if y_predict[i] == test_label:
            if test_label == 1:
                TP = TP + 1
            if test_label == -1:
                TN = TN + 1
        if y_predict[i] != test_label:
            if test_label == 1:
                FN = FN + 1
            if test_label == -1:
                FP = FP + 1

    print("TP = ", TP)
    print("TN = ", TN)
    print("FP = ", FP)
    print("FN = ", FN)
    accuracy = (TP + TN) / frame_num
    print("Accuracy = ", accuracy)
    if test_label == 1:
        TPR = TP/(TP+FN)
        print("TPR = ", TPR)

    for i in range(0, frame_num):
        y_predict[i] = (y_predict[i]+1)/2
    pl = plt.figure(figsize=(10,10))
    # pl.add_subplot(2, 1, 1)
    # x = [i for i in range(1, len(y_predict)+1)]
    # plt.bar(x, y[start_num: start_num + len(y_predict)], color="r", label="label")
    # plt.minorticks_on()
    # plt.title("Test Dataset 5dB  401~500 Frames True Label")

    # pl.add_subplot(2,1,2)
    x = [i for i in range(1, len(y_predict)+1)]
    print(y_predict)
    plt.bar(x, y_predict, color="b", label="predict label")
    plt.minorticks_on()
    if test_label == 1:
        plt.title("Voice Test Dataset Predict Label")
    elif test_label == -1:
        plt.title("Noise Test Dataset Predict Label")
    plt.show()


except Exception as e:
    print("---异常---：", e)
