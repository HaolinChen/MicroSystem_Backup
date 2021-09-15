original=load('LTSDtest5dB_19_198_501_1000.mat');
SNR = 5;
rfs = 16000;
fs = 8000; % 对于ULPS阶段，为250Hz
fs_mid = rfs/fs;
subframesize=round(0.008*rfs); % each subframe 8ms
framesize=round(15*subframesize); % each frame 120ms
frame_0 = 501 ; % 输入开始帧 第一帧为1
frame_1 = 600 ; % 输入结束帧
data = original.data_new((frame_0-501)*framesize+1 : (frame_1-500)*framesize);
label1 = original.label1(frame_0-500 : frame_1-500);
t_mid = 1:fs_mid:size(data,1);
c_data = data(t_mid,1);
%存储结果数据
fid=fopen(['c_dataset\C_LTSDtest',num2str(SNR),'dB_19_198_',num2str(frame_0),'_',num2str(frame_1),'.txt'],'w');%建立文件
%循环写入数据
for i=1:size(c_data,1)
    if i==size(c_data,1)
        fprintf(fid,'%.8f\r\n',c_data(i,:));%保存小数点后8位，c_data为结果数据  
    else
        fprintf(fid,'%.8f,\r\n',c_data(i,:));%保存小数点后8位，c_data为结果数据  
    end
end
fclose(fid);
fid=fopen(['c_dataset\C_LTSDtest',num2str(SNR),'dB_LABEL_19_198_',num2str(frame_0),'_',num2str(frame_1),'.txt'],'w');%建立文件
%循环写入数据
for i=1:size(label1,1)
    if i == size(label1,1)
        fprintf(fid,'%.8f\r\n',label1(i,:));%保存小数点后8位，c_data为结果数据  
    else
        fprintf(fid,'%.8f,\r\n',label1(i,:));%保存小数点后8位，c_data为结果数据  
    end
end
fclose(fid);