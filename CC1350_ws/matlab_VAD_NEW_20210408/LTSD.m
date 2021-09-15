%% This code is based on the following paper:
% Haolin Chen    1170100218@stu.hit.edu.cn
% 2021/3/17

classdef LTSD
    properties
        winsize
        window
        order
        amplitude
        avgnoise
        windownum
        alpha
        speechThr
        firstWindownum
    end
    methods (Access = public) %设置访问权限：可以任意访问
        function ltsds = compute(obj,signal)
            enframe = buffer(signal,obj.winsize,round(obj.winsize/2)); %把信号分解成长度为winsize的帧，每一帧的前一半和前一帧的后一半重叠,第一帧前一半补零
            obj.windownum = size(enframe,2);
            ltsds = zeros(obj.windownum,1);
            %Calculate the average noise spectrum amplitude based on 20 frames in the head parts of input signal.
            obj.avgnoise = compute_noise_avg_spectrum(obj,signal(1:obj.winsize*obj.firstWindownum)).^2;
            for k =1:obj.windownum
                [obj,ltsds(k)] = ltsd(obj,enframe,k,obj.order);
            end
        end
        
        function [obj,ret] = ltsd(obj,signal,k,order) %  long-term spectral divergence Eqn(2)
            if(k < order || (k+order >= obj.windownum))
                ret =  0;
            else
                [obj,sp0]  = ltse(obj,signal,k,order);
                sp = sp0.^2./obj.avgnoise;
                ret = 10 * log10(sum(sp,1)./length(obj.avgnoise));                
                if(~isempty(obj.alpha)&& ret<obj.speechThr)
                    obj.avgnoise = obj.alpha * obj.avgnoise + (1-obj.alpha)*(sum(sp0,1)./length(obj.avgnoise));%更新噪声函数
                end
            end
        end
        
        function [ltsds2,LTSE2] = compute2(obj,signal,K) %K表示每一帧的特征数(不是阶数)
            enframe = buffer(signal,obj.winsize); %把信号分解成长度为winsize的帧，每一帧的前一半和前一帧的后一半重叠,第一帧前一半补零
%             obj.windownum = size(enframe,2);
            obj.windownum = size(enframe,2)/(obj.order*2+1);
%             obj.windownum = size(enframe,2)/3;
            ltsds2 = zeros(obj.windownum,K);
            %%%%%%%%%%这里属于改进算法%%%%%%%%%
            obj.winsize = 64;
            %%%%%%%%%%%%%%%%%%%
            N = obj.winsize;
            NFFT2 = N/2 + 1;
            ltse_total = zeros(NFFT2,obj.windownum);%每一行代表一个频率，相当于论文中的 band k,每一列是一帧
            for t =1:obj.windownum
%                 if(t <= obj.order || (t+obj.order >= obj.windownum))
%                     ltse_total(:,t) =  0;
%                 else
%                     [obj,ltse_total(:,t)] = ltse(obj,enframe,t,obj.order);
%                 end

                [obj,ltse_total(:,t)] = ltse(obj,enframe,t,obj.order);
            end
            k=(0:1:K)';
            mk= round(N.*k./(2*K))+1;
            for t =1:obj.windownum
                for k2 = 1:1:K
                    ltsds2(t,k2) = 2.*K./N.*sum(ltse_total(mk(k2):mk(k2+1)-1,t),'all');                   
                end 
            end  
            LTSE2 = ltse_total;
        end
        
        function [obj,maxamp] = ltse(obj,signal,k,order) % long-term spectral envelope Eqn(1)
            NFFT2 = obj.winsize/2 + 1;
            maxmag = zeros(NFFT2,1);%每一行代表一个频率，相当于论文中的 band k
%             for idx=k-order:k+order %这里已经限制了k的值，k>order || (k+order < obj.windownum)
            for idx=(k-1)*(order*2+1)+1:k*(order*2+1) %这里已经限制了k的值，k>order || (k+order < obj.windownum)
                [obj,amp] = get_amplitude(obj,signal,idx);
                maxamp = max(maxmag,amp); %取两个矩阵中对应位置较大的元素构成新矩阵
                maxmag = maxamp;  
            end
        end
        
        function res =  compute_noise_avg_spectrum(obj,signal)
            enframe = buffer(signal,obj.winsize,round(obj.winsize/2));
            wnum = size(enframe,2); %帧数
            NFFT2 = obj.winsize/2 + 1;
            avgamp = zeros(NFFT2,1);
            for k =1:wnum
                s =  enframe(:,k); %第k帧
                Y = fft(s.*obj.window);
                avgamp = avgamp + abs(Y(1:NFFT2)); %各帧fft后的对应频率幅值（绝对值）相加
            end
            res = avgamp./wnum; %取平均值
        end
        
        function obj = LTSD(varargin) %winsize,window,order,adap_rate,threshold,firstWindownum
            if nargin>3 %函数输入参数数目
                obj.firstWindownum = varargin{6};
                obj.speechThr = varargin{5};
                obj.alpha = varargin{4};
            end
            obj.winsize = varargin{1};
            obj.window = varargin{2};
            obj.order = varargin{3};
            obj.amplitude = {}; 
        end
        
        function [obj,amp] = get_amplitude(obj,signal,k) %第k帧
%             if(length(obj.amplitude)>=(k)) %避免重复计算
%                 amp = obj.amplitude{k}; %使用先前的计算结果
%             else %有新增加的帧
%                 NFFT2 = obj.winsize/2 + 1;
%                 s = signal(:,k+1);
% %                 Y = fft(s.*obj.window);
%                 Y = fft(s,obj.winsize);
%                 amp  = abs(Y(1:NFFT2));
%                 obj.amplitude{k} = amp;
%             end
            NFFT2 = obj.winsize/2 + 1;
            s = signal(:,k);
%                 Y = fft(s.*obj.window);
            Y = fft(s,obj.winsize);
            amp  = abs(Y(1:NFFT2));
        end
        
    end
end


