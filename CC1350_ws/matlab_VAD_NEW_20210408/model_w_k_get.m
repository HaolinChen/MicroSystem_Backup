%  This code can get w value and b value of the SVM model
%  You have to run LTSD_stage.m and get a model first

%支持向量索引(Support Vectors Index)
SVs_idx = model.sv_indices;
%支持向量特征属性和类别属性
x_SVs = featurevector(SVs_idx,:);% or use: SVs=full(model.SVs);
y_SVs = label(SVs_idx);

%求平面w^T x + b = 0的法向量w
alpha_SVs = model.sv_coef;%实际是a_i*y_i
w = sum(diag(alpha_SVs)*x_SVs)';%即西瓜书公式(6.9) 
%对角阵和x_SVs相乘的结果等效于x_SVs的每一行的每一个元素乘以对应的a_i*y_i，sum用于列相加

%求平面w^T x + b = 0的偏移项b
%由于是软件隔支持向量机，所以先找出正好在最大间隔边界上的支持向量
SVs_on = (abs(alpha_SVs)<1);%C=1 by parameter '-c 1'
y_SVs_on = y_SVs(SVs_on,:);
x_SVs_on = x_SVs(SVs_on,:);
%理论上可选取任意在最大间隔边界上的支持向量通过求解西瓜书式(6.17)获得b
b_temp = zeros(1,sum(SVs_on));%所有的b
for idx=1:sum(SVs_on)
    b_temp(idx) = 1/y_SVs_on(idx)-x_SVs_on(idx,:)*w;
end
b = mean(b_temp);%更鲁棒的做法是使用所有支持向量求解的平均值

%将手动计算出的偏移项b与svmtrain给出的偏移项b对比
b_model = -model.rho;%model中的rho为-b
b-b_model

% %将手动计算出的决策值与svmpredict输出的决策值对比
% %决策值f(x)=w^T x + b
% f_x = x * w + b;
% sum(abs(f_x-dec_values))