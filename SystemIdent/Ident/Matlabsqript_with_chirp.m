a = 1/10;
b = 1;
start = 0;
slut = 100;
fs = b*10;
t = 0:1/fs:100;
y = 0.79*chirp(t, a, t(end), b,'logarithmic');
plot(t, y, '*-');
%%
fs = 10; % sample rate
f1 = 1/10; % start freq
f2 = 1; % end freq
T = 500; %second run time 
 
w1=2*pi*f1;
w2=2*pi*f2;
t=0:1/fs:(T*fs-1)/fs;
K=T*w1/log(w2/w1);
L=T/log(w2/w1);
sweep=0.799760*sin(K.*(exp(t./L)-1)); %sweep data set
csvwrite('newFreqSweep500S10SAMPLEFREQ_ONETEENTHtoONE.csv',sweep);
plot(t,sweep,'*-')