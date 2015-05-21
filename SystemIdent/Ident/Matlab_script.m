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
   n = 0:1/100:100;
   f = 1/1;
   y = transpose(chop(0.799760*sin(2*pi*f*n),5));
   plot(n,y); 
   csvwrite('onetenth_sample10_t100.csv',transpose(y));