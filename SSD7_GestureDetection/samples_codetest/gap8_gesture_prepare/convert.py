import os
from PIL import Image
import cv2

folder_names = ['6']


def Resize(in_name, out_name, size_H, size_W):
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
        count += 1


def resize_convert(in_folder, out_folder, size_H, size_W):
    if not os.path.exists(in_folder):
        os.mkdir('./gesture_resized' + os.sep + in_folder)
    # os.mkdir('./pic_output' + os.sep + in_folder)
    print("Start resize and convert pic...")
    for i, filename in enumerate(os.listdir('./gesture_original' + os.sep + in_folder)):
        print(filename)
        file_path = './gesture_original' + os.sep + in_folder + os.sep + filename
        temp_path = './gesture_resized' + os.sep + in_folder + os.sep + filename
        out_path = './pic_input' + os.sep + out_folder + \
            os.sep + 'label'+out_folder + '_num' + str(i) + '.pgm'
        img = cv2.imread(file_path, cv2.IMREAD_GRAYSCALE)
        img_resize = cv2.resize(img, (int(size_W), int(size_H)))
        cv2.imwrite(temp_path, img_resize)
        Image.open(temp_path).save(out_path)


if __name__ == '__main__':
    for folder_name in folder_names:
        resize_convert(folder_name, folder_name, 244, 324)
