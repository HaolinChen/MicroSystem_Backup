clear 
close all
fft_long = 64;
NFFT2  = fft_long/2 + 1;
a = 1:1:fft_long;
a = a*0.001 - 0.066;
b = fft(a,fft_long);
amp_b  = abs(b(1:NFFT2));