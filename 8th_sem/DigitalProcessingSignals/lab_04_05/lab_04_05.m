function lab_04_05
    % Initial state
    A = 1.0;
    sigma = 0.5;
    mult = 5;
    step = 0.005;
    t = -mult:step:mult;
    
    % Impulse
    x0 = gaussian_impulse(t,A,sigma);
    
    % Gaussian noise generation
    NA = 0;
    NS = 0.05;
    n1 = normrnd(NA,NS,[1 length(x0)]);
    x1 = x0+n1;
    
    % Impulsive noise generation
    count = 7;
    M = 0.4;
    n2 = impulsive_noise(length(x0),count,M);
    x2 = x0+n2;
    
    % Calculation of filtering arrays
    [B,A] = butter(6,0.5,'high');
    GH = gaussian_filter(4,20,'high');
    GL = gaussian_filter(4,20,'low');
    BBH = butterworth_filter(6,20,'high');
    BBL = butterworth_filter(6,20,'low');
    
    figure;
    
    subplot(5,1,1);
    title('Исходные сигналы');
    hold on;
    grid on;
    plot(t, x0, 'r');
    plot(t, x1, 'g');
    plot(t, x2, 'b');
    legend('Без помех', 'Помеха по Гауссу', 'Импульсная помеха');
    
    subplot(5,1,2);
    title('Гауссовский фильтр (high)');
    hold on;
    grid on;
    plot(t, x0, 'r');
    plot(t, x1-filtfilt(GH,1,x1), 'g');
    plot(t, x2-filtfilt(GH,1,x2), 'b');
    legend('Без помех', 'Помеха по Гауссу', 'Импульсная помеха');
    
    subplot(5,1,3);
    title('Гауссовский фильтр (low)');
    hold on;
    grid on;
    plot(t, x0, 'r');
    plot(t, filtfilt(GL,1,x1), 'g');
    plot(t, filtfilt(GL,1,x2), 'b');
    legend('Без помех', 'Помеха по Гауссу', 'Импульсная помеха');
    
    subplot(5,1,4);
    title('Фильтр Баттеруорта (high)');
    hold on;
    grid on;
    plot(t, x0, 'r');
    plot(t, x1-filtfilt(BBH,1,x1), 'g');
    plot(t, x2-filtfilt(BBH,1,x2), 'b');
    legend('Без помех', 'Помеха по Гауссу', 'Импульсная помеха');
    
    subplot(5,1,5);
    title('Фильтр Баттеруорта (low)');
    hold on;
    grid on;
    plot(t, x0, 'r');
    plot(t, filtfilt(BBL,1,x1), 'g');
    wait = plot(t, filtfilt(BBL,1,x2), 'b');
    legend('Без помех', 'Помеха по Гауссу', 'Импульсная помеха');
    
    waitfor(wait)
end
    
% Gaussian impulse
function y = gaussian_impulse(x,A,s)
    y = A * exp(-(x/s).^2);
end
    
% Impulsive noise
function y = impulsive_noise(size,N,mult)
    step = floor(size/N);
    y = zeros(1,size);
    for i = 1:floor(N/2)
      y(round(size/2)+i*step) = mult*(0.5+rand);
      y(round(size/2)-i*step) = mult*(0.5+rand);
    end
end
    
% Butterworth filter
function y = butterworth_filter(D,size,type)
    x = linspace(-size/2,size/2,size);
    if (strcmp(type,'low'))
      y = 1./(1+(x./D).^4);
    elseif (strcmp(type,'high'))
      y = 1./(1+(D./x).^4);
    else
      y = x*sum(x);
    end
    y = y/sum(y);
end

% Gaussian filter
function y = gaussian_filter(sigma,size,type)
    x = linspace(-size/2,size/2,size);
    if (strcmp(type,'low'))
      y = exp(-x.^2/(2*sigma^2));
    elseif (strcmp(type,'high'))
      y = 1 - exp(-x.^2/(2*sigma^2));
    else
      y = x*sum(x);
    end
    y = y/sum(y);
end