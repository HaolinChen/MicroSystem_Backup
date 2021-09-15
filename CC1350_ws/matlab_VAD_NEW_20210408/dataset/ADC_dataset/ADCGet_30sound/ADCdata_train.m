clear 
close all
% 加载用ADC采集到的txt数据并制作完成.mat数据用于offline训练
%% Prepare
fs = 8000;
subframesize = round(0.008*fs); % each subframe 8ms
L = 7;% 实际上就是order
subframe_total = L*2+1;
framesize = round(subframesize*15/subframe_total);
featurenum = 8; % 5 is better actually
%% Get Dataset and Plot(Original rfs=8000)
%% 0dB Signal
data1 = load('train0dB30sound2min.txt');
enframe = buffer(data1,framesize*subframe_total);
framenum = size(enframe,2)-1;
% featurevector=zeros(framenum,15);
data1 = enframe(:,1);
for j = 2:framenum
    data1 = [data1 ; enframe(:,j)];
end
figure();
subplot(221);
plot(data1);
title('Train 0dB data');
label1 = ones(framenum,1);
%% 5dB Signal
data2 = load('train5dB30sound2min.txt');
enframe = buffer(data2,framesize*subframe_total);
framenum = size(enframe,2)-1;
% featurevector=zeros(framenum,15);
data2 = enframe(:,1);
for j = 2:framenum
    data2 = [data2 ; enframe(:,j)];
end
subplot(222);
plot(data2);
title('Train 5dB data');
label2 = ones(framenum,1);
%% 10dB Signal
data3 = load('train10dB30sound2min.txt');
enframe = buffer(data3,framesize*subframe_total);
framenum = size(enframe,2)-1;
% featurevector=zeros(framenum,15);
data3 = enframe(:,1);
for j = 2:framenum
    data3 = [data3 ; enframe(:,j)];
end
subplot(223);
plot(data3);
title('Train 10dB data');
label3 = ones(framenum,1);
%% 15dB Signal
data4 = load('train15dB30sound2min.txt');
enframe = buffer(data4,framesize*subframe_total);
framenum = size(enframe,2)-1;
% featurevector=zeros(framenum,15);
data4 = enframe(:,1);
for j = 2:framenum
    data4 = [data4 ; enframe(:,j)];
end
subplot(224);
plot(data4);
title('Train 15dB data');
label4 = ones(framenum,1);
%% Noisy data
%% 0dB Noise
noise1 = load('trainNoise0dB30sound2min.txt');
enframe = buffer(noise1,framesize*subframe_total);
framenum = size(enframe,2)-1;
% featurevector=zeros(framenum,15);
noise1 = enframe(:,1);
for j = 2:framenum
    noise1 = [noise1 ; enframe(:,j)];
end
figure();
subplot(221);
plot(noise1);
title('Train 0dB noise data');
noiselabel1 = -1*ones(framenum,1);
%% 5dB Noise
noise2 = load('trainNoise5dB30sound2min.txt');
enframe = buffer(noise2,framesize*subframe_total);
framenum = size(enframe,2)-1;
% featurevector=zeros(framenum,15);
noise2 = enframe(:,1);
for j = 2:framenum
    noise2 = [noise2 ; enframe(:,j)];
end
subplot(222);
plot(noise2);
title('Train 5dB noise data');
noiselabel2 = -1*ones(framenum,1);
%% 10dB Noise
noise3 = load('trainNoise10dB30sound2min.txt');
enframe = buffer(noise3,framesize*subframe_total);
framenum = size(enframe,2)-1;
% featurevector=zeros(framenum,15);
noise3 = enframe(:,1);
for j = 2:framenum
    noise3 = [noise3 ; enframe(:,j)];
end
subplot(223);
plot(noise3);
title('Train 10dB noise data');
noiselabel3 = -1*ones(framenum,1);
%% 15dB Noise
noise4 = load('trainNoise15dB30sound2min.txt');
enframe = buffer(noise4,framesize*subframe_total);
framenum = size(enframe,2)-1;
% featurevector=zeros(framenum,15);
noise4 = enframe(:,1);
for j = 2:framenum
    noise4 = [noise4 ; enframe(:,j)];
end
subplot(224);
plot(noise4);
title('Train 15dB noise data');
noiselabel4 = -1*ones(framenum,1);
%% Save Data
train_data = [data1;data2;data3;data4;noise1;noise2;noise3;noise4];
train_label = [label1;label2;label3;label4;noiselabel1;noiselabel2;noiselabel3;noiselabel4];
save('ADCget_traindata','train_data','train_label'); % save label