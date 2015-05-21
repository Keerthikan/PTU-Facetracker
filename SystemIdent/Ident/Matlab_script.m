 %% Time specifications:
   Fs = 10;                   % samples per second
   dt = 1/Fs;                   % seconds per sample
   StopTime = 500;             % seconds
   t = (0:dt:StopTime-dt)';     % seconds
   Fc = 1;                     % hertz
   x = chop(0.799760*sin(2*pi*Fc/Fs*t),5); %plot sine wave and chop the input to 5 sign. decimal
   x = transpose(x);    % transposin => becomes a vector
   % Plot the signal versus time:
   figure;
   plot(t,x);
   %xlabel('time (in seconds)');
   %title('Signal versus Time');
   csvwrite('onetenth_sampl.csv',x) % save the data somewhere on github. 