import numpy

a = numpy.loadtxt('G:\\MatlabCode\\VAD_NEW\\dataset\\c_dataset\\C_LTSDtest5dBNEW_19_198_501_1000.txt')
print(a[:10])
print(a.shape)
b = a[0] + a[1]
print(b)
