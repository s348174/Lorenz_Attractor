function plot_lorenz(filename)
    % Function per plottare la traiettoria del'attrattore di Lorenz.
    % Legge un file CSV con colonne x,y,z e plottalo in 3D
    % NOTA: filename deve essere una stringa (es: 'nomefile.csv')
    data = readmatrix(filename); % se la versione di Matlab non è aggiornata, usare csvread

    x = data(:,1);
    y = data(:,2);
    z = data(:,3);

    figure;
    plot3(x, y, z, 'LineWidth', 1.2);
    hold off;
    hold on;
    plot3(x(1), y(1), z(1), 'go', 'MarkerSize', 3, 'MarkerFaceColor', 'g'); % Punto iniziale
    plot3(x(end), y(end), z(end), 'ro', 'MarkerSize', 3, 'MarkerFaceColor', 'r'); % Punto finale
    grid on;
    xlabel('x');
    ylabel('y');
    zlabel('z');
    title('Attrattore di Lorenz');
    legend({'Traiettoria', 'Inizio', 'Fine'}, 'Location', 'Best');
    axis equal;
    view(3);
end

