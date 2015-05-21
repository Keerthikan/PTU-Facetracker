 %% Time specifications:
   Fs = 1;                   % samples per second
   dt = 1/Fs;                   % seconds per sample
   StopTime = 500;             % seconds
   t = (0:dt:StopTime-dt)';     % seconds
   Fc = 1/100;                     % hertz
   x = 0.799760*sin(2*pi*Fc*t);
   % Plot the signal versus time:
   figure;
   plot(t,x);
   xlabel('time (in seconds)');
   title('Signal versus Time');
   csvwrite('onehundreth_sampl.csv')