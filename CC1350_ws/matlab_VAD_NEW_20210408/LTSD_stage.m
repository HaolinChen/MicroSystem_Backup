clear 
close all
%% Get Dataset (Original rfs=16000)
% original=load('dataset\train_LTSD_19_198_3204_0_10.mat');
original=load('dataset\LTSDtrain0dB_19_198_1_500.mat');
data = original.data_new;
label = original.label1;
original2=load('dataset\LTSDtrain5dB_19_198_1_500.mat');
data2 = original2.data_new;
label2 = original2.label1;
original3=load('dataset\LTSDtrain10dB_19_198_1_500.mat');
data3 = original3.data_new;
label3 = original3.label1;
original4=load('dataset\LTSDtrain15dB_19_198_1_500.mat');
data4 = original4.data_new;
label4 = original4.label1;
% original5=load('urban\20dB_LTSD_19_198_3204_0_10_new.mat');
% data5 = original5.data_new;
% label5 = original5.label2;
data = [data;data2;data3;data4];
label = [label;label2;label3;label4];
% ULPS sampling fs = 8000 Hz
rfs = 16000; 
fs = 8000;
fs_mid = rfs/fs;
t_mid = 1:fs_mid:size(data,1);
xt = data(t_mid,1);
N = size(xt,1);
%%
subframesize = round(0.008*fs); % each subframe 8ms
L = 7;% 实际上就是order
subframe_total = L*2+1;
% framesize = round(15*subframesize); % each frame 120ms
% framesize = round(5*subframesize); %这里的framesize实际上为子帧，order为1，3*5*subframesize正好为一帧
framesize = round(subframesize*15/subframe_total);
enframe = buffer(xt,framesize*subframe_total);
% framenum = size(enframe,2)/3;
framenum = size(enframe,2);
enframe = buffer(xt,framesize);
featurenum = 8; % 5 is better actually
% featurevector=zeros(framenum,15);
%% Show in time domain and spectral domain
figure();
plot(xt);
title('Train Data');
% hold on;
% for i = 1:framenum
%     bar(i*framesize-1,0.3,100,'r'); 
% end
% xt_fft=abs(fft(xt));
% NFFT2 = round(N/2) + 1;
% figure();
% plot(xt_fft(1:NFFT2));
% title('Spectral Data');
%% LTSD
THRESHOLD = -6; % Threshold to update the noise spectrum
ALPHA = 0.4; % update rate (forgotten factor)
NORDER = L; % order
WINSIZE = framesize; % window size
WINDOW = hamming(WINSIZE,'symmetric'); % hamming window
FIRSTWindowNUM = 5; % number of window frames to get the initial noise statistc => the first FIRSTWindowNUM * WINSIZE / rfs seconds
ltsd = LTSD(WINSIZE,WINDOW,NORDER,ALPHA,THRESHOLD, FIRSTWindowNUM);
% if you don't want the noise to be adapted 
% ltsd = LTSD(WINSIZE,WINDOW,NORDER);
% res =  ltsd.compute(xt);
[featurevector,LTSE1] =  ltsd.compute2(xt,featurenum); % framenum*featurenum
%% Test dataset
% original2=load('newdataset\test_LTSD_27_123349_1711_2510.mat');
original2=load('dataset\LTSDtest15dB_19_198_2001_2500.mat');
data2 = original2.data_new;
label2 = original2.label1;
% ULPS sampling fs = 8000 Hz
% rfs = 16000; 
% fs = 8000;
% fs_mid = rfs/fs;
t_mid2 = 1:fs_mid:size(data2,1);
xt2 = data2(t_mid2,1);
N2 = size(xt2,1);

% subframesize = round(0.008*fs); % each subframe 8ms
% framesize = round(15*subframesize); % each frame 120ms
enframe2 = buffer(xt2,framesize);
framenum2 = size(enframe2,2)/subframe_total;
% featurenum = 8;
% featurevector=zeros(framenum,15);

figure();
plot(xt2);
title('Test Data');

THRESHOLD = -6; % Threshold to update the noise spectrum
ALPHA = 0.4; % update rate (forgotten factor)
WINSIZE = framesize; % window size
WINDOW = hamming(WINSIZE,'symmetric'); % hamming window
FIRSTWindowNUM = 5; % number of window frames to get the initial noise statistc => the first FIRSTWindowNUM * WINSIZE / rfs seconds
ltsd2 = LTSD(WINSIZE,WINDOW,NORDER,ALPHA,THRESHOLD, FIRSTWindowNUM);
% if you don't want the noise to be adapted 
% ltsd = LTSD(WINSIZE,WINDOW,NORDER);
% res =  ltsd2.compute(xt2);
[featurevector2,LTSE2] =  ltsd2.compute2(xt2,featurenum); % framenum*featurenum
%% SVM
model = libsvmtrain(label, featurevector,'-t 0 -g 0.125 -c 1');
figure();
% test_num = 200;
% svmplotroc(label2(1:test_num,:), featurevector2(1:test_num,:),model);
% [predicted_label, accuracy, prob_estimates] = svmpredict(label2(1:test_num,:), featurevector2(1:test_num,:), model,'-b 0');
svmplotroc(label2, featurevector2,model);
[predicted_label, accuracy, prob_estimates] = svmpredict(label2, featurevector2, model,'-b 0');
figure();
subplot(311);
plot(xt2,'green');
% title(['Train Data:ALL  ','Test Data:Non-homologous 5dB  ','Featurenum:',num2str(featurenum)]);
title(['Train Data:ALL  ','Test Data: 0dB  ','Featurenum:',num2str(featurenum)]);
subplot(312);
bar((label2+1)/2,'red');axis([0 inf 0 2]);
title('True label');
% subplot(313);
% bar((predicted_label+1)/2,'blue');axis([0 inf 0 2]);
% title(['Predicted label  Accuracy =',num2str(accuracy(1)),'%']);
TP = 0;
FN = 0;
for i = 1 : size(label2,1)
    if(label2(i,1) == 1 && predicted_label(i,1) == 1)
        TP = TP + 1;
    elseif(label2(i,1) == 1 && predicted_label(i,1) == -1)
        FN = FN + 1;
    end
end
TPR = TP/(TP+FN);
OUTPUT = ['ACCURACY = ', num2str(TPR*100),'%'];
disp(OUTPUT);
subplot(313);
bar((predicted_label+1)/2,'blue');axis([0 inf 0 2]);
title(['Predicted label  Accuracy =',num2str(TPR*100),'%']);