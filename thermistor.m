%% Thermistor Parameters
R0 = 10e3;       % NTC 10k
Beta = 3435;     
T0 = 25+273.15;  
Vcc = 5;         
Rfixed = 10e3;   % fixed resistor at bottom

%% Temperature vector
T = 0:5:50;      
Tk = T + 273.15; 

%% NTC Resistance
Rt = R0 .* exp(Beta.*(1./Tk - 1./T0));

%% Voltage (NTC on top -> T↑ => Vo↓)
Vo = Vcc .* (Rt ./ (Rt + Rfixed));

%% Display table
disp('Vo(V)     T(°C)')
disp([Vo' T'])

%% Polynomial fits n = 1 to 5
ordenes = 1:5;
colores = lines(length(ordenes));  % different colors

for n = ordenes
    % Polynomial fit
    p = polyfit(Vo, T, n);
    T_fit = polyval(p, Vo);
    
    % Create separate figure
    figure;
    
    % Small discrete points
    plot(Vo, T, 'ko', 'MarkerSize',4, 'MarkerFaceColor','k'); hold on;
    
    % Thin polynomial fit line
    plot(Vo, T_fit, '-', 'Color', colores(n,:), 'LineWidth',1.2);
    
    xlabel('Voltage Vo (V)');
    ylabel('Temperature T (°C)');
    title(sprintf('Polynomial Fit Degree %d', n));
    legend('Discrete Data','Polynomial Fit', 'Location','best');
    grid on;

    % Display coefficients and RMSE in console
    fprintf('\nDegree %d coefficients: ', n); disp(p);
    rmse = sqrt(mean((T_fit - T).^2));
    fprintf('RMSE degree %d: %.4f °C\n', n, rmse);
    
    % Display polynomial on the figure
    eq_str = sprintf('T(V_o) = %.4f', p(1));
    for k = 2:length(p)
        eq_str = [eq_str sprintf(' + %.4f*Vo^%d', p(k), length(p)-k)];
    end
    eq_str = [eq_str sprintf('\nRMSE = %.3f °C', rmse)];
    
    % Add text to plot (top-left corner)
    x_pos = min(Vo) + 0.05*(max(Vo)-min(Vo));
    y_pos = max(T) - 0.05*(max(T)-min(T));
    text(x_pos, y_pos, eq_str, 'FontSize',9, 'BackgroundColor','w', 'EdgeColor','k');
end
