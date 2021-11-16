import os
from PIL import Image
import cv2

def Resize(in_name,out_name, size_H, size_W):
    print("Start resize picture:")
    for filename in os.listdir(in_name):
        print(filename)
        file_path = in_name + "/" + filename
        write_path = out_name + "/" + filename
        img = cv2.imread(file_path, cv2.IMREAD_GRAYSCALE)
        img_resize = cv2.resize(img, (int(size_W), int(size_H)))
        cv2.imwrite(write_path, img_resize)

def convert(in_name, out_name):
    print("Start convert picture:")
    count = 0
    for filename in os.listdir(in_name):
        new_name = 'gesture_%d' % count
        print(filename + '  to  ' + new_name + '.pgm')  # 仅仅是为了测试
        file_path = in_name + "/" + filename
        # write_path = out_name + "/" + filename.split('.')[0] + '.pgm'
        write_path = out_name + "/" + new_name + '.pgm'
        Image.open(file_path).save(write_path)
        count +=1


if __name__ == '__main__':
    Resize('original', 'resize', 244, 324)
    convert('resize', 'converted')
