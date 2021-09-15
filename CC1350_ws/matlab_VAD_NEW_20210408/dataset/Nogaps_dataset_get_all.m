%% This code
% 作用：1.将原来的语音数据集修改成无空隙的纯“正样本”数据集。
%       2.截取任意长度的“正样本”语音数据集，在其上叠加对应SNR的噪声，并输出相同长度的噪声数据集。
% Haolin Chen    1170100218@stu.hit.edu.cn
% 2021/3/17
clc             % command line
clear           % work space
close all       % figure 
want_clear_gaps = 0;
%% load the original data and remove its gaps
if(want_clear_gaps == 1)
    original=load('dataset_19_227_all.mat');
    data = original.data;
    figure();
    plot(data);title('original all data');
    rfs = 16000;
    subframesize=round(0.008*rfs); % each subframe 8ms
    framesize=round(15*subframesize); % each frame 120ms
    enframe = buffer(data,framesize);
    framenum = size(enframe,2);
    label1=zeros(framenum,1);
    for i = 1:framenum
        count = 0;
        for j = 1:framesize
            if(abs(enframe(j,i))>0.01)
                count = count + 1;
            end
        end
        if(count>round(framesize/2))
            label1(i,1)=1;
        else
            label1(i,1)=-1;
        end
    end
    enframe_nogaps = enframe(:,label1==1);
    data_nogaps = enframe_nogaps(:);
    figure();
    plot(data_nogaps);title('original all no gaps data');
    save('nogaps_dataset_19_227_all.mat','data_nogaps');
    audiowrite('nogaps_dataset_19_227_all.wav',data_nogaps,rfs);
end
%%
if(want_clear_gaps == 0)
    original=load('nogaps_dataset_19_227_all.mat');
    rfs = 16000 ;
    subframesize=round(0.008*rfs); % each subframe 8ms
    framesize=round(15*subframesize); % each frame 120ms
    data1 = original.data_nogaps;
    enframe = buffer(data1,framesize);
    framenum = size(enframe,2);
    X = enframe(:,1);
    for j = 2:framenum
        X = [X ; enframe(:,j)];
    end
    data1 = X;
%     frame_0 = 501 ; % 输入开始帧 第一帧为1
%     frame_1 = 1000 ; % 输入结束帧
%     data1 = original.data_nogaps((frame_0-1)*framesize+1 : frame_1*framesize);
%     framenum = frame_1 - frame_0 + 1;
    N1 = size(data1,1);
    %% 按一定信噪比生成城市环境噪声并保存
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
    signalPower = mean(abs(data1).^2);
    niosePower0 = mean(abs(data_n).^2);
    SNR = 0;
    niosePower_wanted = signalPower/(10.^(SNR/10));
    K = niosePower_wanted/niosePower0;
    data_n = data_n*K;
    figure();
    plot(data_n);title([num2str(SNR),'dB ',num2str(framenum),'frames test noise data']);
    filename = ['ADC_dataset\ADCtest',num2str(SNR),'dB_19_227_noise.wav'];
    audiowrite(filename,data_n,rfs);
    %% 叠加城市环境噪声并保存
    data_new = data_n + data1;
    figure();
    plot(data_new);title([num2str(SNR),'dB ',num2str(framenum),'frames test signal data']);
    filename = ['ADC_dataset\ADCtest',num2str(SNR),'dB_19_227_nogaps.wav'];
    audiowrite(filename,data_new,rfs);
end








