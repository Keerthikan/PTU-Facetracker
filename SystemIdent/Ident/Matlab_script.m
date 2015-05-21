 %% Time specifications:
   Fs = 100;                   % samples per second
   dt = 1/Fs;                   % seconds per sample
   StopTime = 1;             % seconds
   t = (0:dt:StopTime-dt)';     % seconds
   Fc = 1;                     % hertz
   x = chop(0.799760*sin(2*pi*Fc*t),5); %plot sine wave and chop the input to 5 sign. decimal
   x = transpose(x);    % transposin => becomes a vector
   % Plot the signal versus time:
   figure;
   plot(t,x);
   %xlabel('time (in seconds)');
   %title('Signal versus Time');
   csvwrite('onehertz_sample10.csv',x) % save the data somewhere on github. 
   %%
   fs = 10;
   Ts = 1/fs;
   n = 0:1000;
   f = 0.1;
   x = chop(0.799760*sin(2*pi*f*N*Ts));