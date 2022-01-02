import os
import shutil

gesture_list = ['backward', 'down', 'forward', 'left', 'right', 'up', 'no_gesture']
folder_list = ['0', '1', '2', '3', '4', '5', '6']
original_root = '../total_qy_train_val/images'

if __name__ == '__main__':
    for i, folder_name in enumerate(folder_list):
        save_original = 'original_val' + os.sep + folder_name
        os.mkdir(save_original)
        l = os.listdir('cropped_val' + os.sep + folder_name)
        pic_ids = [x.split('_')[0] for x in l]

        for id in pic_ids:
            if os.path.exists(original_root + os.sep + id + '.jpg'):
                shutil.copyfile(original_root + os.sep + id + '.jpg', save_original + os.sep + id + '.jpg')
                print(str(id) + '.jpg transfer done.')
