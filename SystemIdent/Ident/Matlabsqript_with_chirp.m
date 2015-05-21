a = 1/10;
b = 1;
start = 0;
slut = 100;
fs = b*100;
t = 0:1/fs:100;
y = 0.79*chirp(t, a, t(end), b,'logarithmic');
plot(t, y, 'b*-');
