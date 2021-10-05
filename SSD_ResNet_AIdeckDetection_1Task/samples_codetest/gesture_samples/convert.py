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
    for filename in os.listdir(in_name):
        print(filename)  # 仅仅是为了测试
        file_path = in_name + "/" + filename
        write_path = out_name + "/" + filename.split('.')[0] + '.pgm'
        Image.open(file_path).save(write_path)


if __name__ == '__main__':
    Resize('original', 'resize', 244, 324)
    convert('resize', 'converted')
