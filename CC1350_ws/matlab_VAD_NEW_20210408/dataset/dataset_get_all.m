clc             % command line
clear           % work space
close all       % figure 
want_train = 0;
%% Extract all files in one folder at same time and splice them
% Path = 'G:\MatlabCode\VAD\LibriSpeechASRcorpus\LibriSpeech_train\train-clean-100\19\227';                   % 设置数据存放的文件夹路径
% File = dir(fullfile(Path,'*.flac'));  % 显示文件夹下所有符合后缀名为.txt文件的完整信息
% 
% Length_Names = size(File,1);    % 获取所提取数据文件的个数
% data = [];
% 
% for k = 1 : Length_Names
%     % 连接路径和文件名得到完整的文件路径
%     K_Trace = [Path '\' File(k).name];
%     [X,fs] = audioread(K_Trace);
%     data = [data;X];
% end
% save('dataset_19_227_all.mat','data');
% %存储.wav音频文件
% filename = ('dataset_19_227_all.wav'); %给文件取名
% audiowrite(filename,data,fs) %存储.wav音频文件，在这里文件名为test.wav
%% load the original data and see its Amplitude
original=load('dataset_19_198_all.mat');
%% not first save data
rfs = 16000 ; 
subframesize=round(0.008*rfs); % each subframe 8ms
framesize=round(15*subframesize); % each frame 120ms
frame_0 = 501 ; % 输入开始帧 第一帧为1
frame_1 = 1000 ; % 输入结束帧
data = original.data((frame_0-1)*framesize+1 : frame_1*framesize);
enframe = buffer(data,framesize);
framenum = size(enframe,2);
X = enframe(:,1);
for j = 2:framenum
    X = [X ; enframe(:,j)];
end
label1=zeros(framenum,1);
figure();
plot(X);title('original data');
data1 = X;
for i = 1:framenum
    count = 0;
    for j = 1:framesize
        if(abs(enframe(j,i))>0.01)
            count = count + 1;
        end
    end
    if(count>round(framesize/2)) %?????????????????????????有问题，检查，重新制作数据集
        label1(i,1)=1;
    else
        label1(i,1)=-1;
    end
end
%% 制作训练集的时候需要使用
if (want_train == 1)
    % 补充数据，保证正样本和负样本数量相当
    pos_num = sum(label1(:)==1);
    neg_num = sum(label1(:)==-1);
    need_num = pos_num - neg_num;
    label1 = [-1*ones(need_num,1);label1];
    for ii = 1:need_num
        data1 = [zeros(framesize,1);data1];
    end
    figure();
    subplot(211);plot(data1);axis([0 inf -inf inf]);title('original train data');
    subplot(212);bar((label1+1)/2,'red');axis([0 inf 0 2]);title('original true label');
end
N1 = size(data1,1);
%% 按一定信噪比叠加城市环境噪声
Path = 'G:\MatlabCode\VAD\urbantraffic.mp3';
[X_n,rfs2] = audioread(Path);
X_n = X_n(:,1);
fs_mid = round(rfs2/rfs);
t_mid = 1:fs_mid:size(X_n,1);
data2 = X_n(t_mid,1);
N2 = size(data2,1); 
data_n = zeros(N1,1);
for i = 1:N1
    temp = mod(i,N2);
    data_n(i) =data2(temp+1);
end
%set SNR and adjust the data_n
% data1_mid = data1(abs(data1)>=0.01);
signalPower = mean(abs(data1).^2);
niosePower0 = mean(abs(data_n).^2);
% sigPower = sum(abs(X).^2)/length(X)             %求出信号功率
% noisePower=sum(abs(Y-X).^2)/length(Y-X)         %求出噪声功率
% SNR_10=10*log10(sigPower/noisePower)            %由信噪比定义求出信噪比，单位为db
SNR = 0 ; 
niosePower_wanted = signalPower/(10.^(SNR/10));
K = niosePower_wanted/niosePower0;
data_n = data_n*K;
data_new = data_n + data1;
figure();
plot(data_new);%title('final data');
save(['LTSDtest',num2str(SNR),'dB_19_198_501_1000.mat'],'data_new','label1'); % save label
%存储.wav音频文件
% filename = ('urban\test_1711_2510_-5dB.wav'); %给文件取名
% audiowrite(filename,data_new,rfs1) %存储.wav音频文件，在这里文件名为test.wav
%% 训练集不输出txt文件，测试集要输出txt文件
% original2=load('dataset\LTSDtest5dB_19_198_501_1000.mat');
% data_new = original2.data_new;
% label1 = original2.label1;
if(want_train ~= 1)
    % 这里直接进行采样，这样用C测试可以不用再次进行采样，也减小了数据量
    rfs = 16000;
    fs = 8000; % 对于ULPS阶段，为250Hz
    fs_mid = rfs/fs;
    t_mid = 1:fs_mid:size(data_new,1);
    c_data = data_new(t_mid,1);
    figure();
    plot(c_data);title('C DATA');
    %存储结果数据
    fid=fopen(['c_dataset\C_LTSDtest',num2str(SNR),'dBNEW_19_198_501_1000.txt'],'w');%建立文件
    %循环写入数据
    for i=1:size(c_data,1)
        if i==size(c_data,1)
            fprintf(fid,'%.8f\r\n',c_data(i,:));%保存小数点后8位，c_data为结果数据  
        else
            fprintf(fid,'%.8f\r\n',c_data(i,:));%保存小数点后8位，c_data为结果数据  
        end
    end
    fclose(fid);
    fid=fopen(['c_dataset\C_LTSDtest',num2str(SNR),'dBNEW_LABEL_19_198_501_1000.txt'],'w');%建立文件
    %循环写入数据
    for i=1:size(label1,1)
        if i == size(label1,1)
            fprintf(fid,'%.8f\r\n',label1(i,:));%保存小数点后8位，c_data为结果数据  
        else
            fprintf(fid,'%.8f\r\n',label1(i,:));%保存小数点后8位，c_data为结果数据  
        end
    end
    fclose(fid);
end






