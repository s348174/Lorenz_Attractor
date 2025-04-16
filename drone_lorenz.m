function env = adsr_env(fs, attack, decay, sustain_level, sustain_time, release)
    % Funzione che crea unvettore envelope che codifica una modulazione del
    % volume della nota nell'intervallo di tempo
    % 
    % fs: frequenza di campionamento (es. 44100)
    % attack, decay, release: durate in secondi
    % sustain_level: ampiezza costante del sustain (0-1)
    % sustain_time: durata in secondi del sustain

    % Numero di campioni per ciascuna fase
    A = round(fs * attack);
    D = round(fs * decay);
    S = round(fs * sustain_time);
    R = round(fs * release);

    % Envelope: vettore che codifica le transizioni con coefficienti in
    % [0,1]
    env_attack = linspace(0, 1, A);
    env_decay = linspace(1, sustain_level, D);
    env_sustain = sustain_level * ones(1, S);
    env_release = linspace(sustain_level, 0, R);

    % Concatenazione fasi
    env = [env_attack, env_decay, env_sustain, env_release];
end

% Parametri iniziali
fs = 44100;             % Frequenza di campionamento
note_duration = 6;      % Ogni tono dura 6s

% Lettura dati
data = readmatrix('data/Lorenz_attractor_trajectory.csv');
x = data(:,1);
y = data(:,2);
z = data(:,3);

% Downsample (1 punto ogni 200)
stride = 200;
x_slow = x(1:stride:end);
y_slow = y(1:stride:end);
z_slow = z(1:stride:end);

% Mappa a frequenze basse
x_freq = rescale(x_slow, 40, 100);
y_freq = rescale(y_slow, 120, 240);
z_freq = rescale(z_slow, 220, 340);

% Envelope ADSR
adsr = adsr_env(fs, 2, 1, 0.7, note_duration - 4, 1);

% Generazione del drone
drone = [];
t = linspace(0, note_duration, fs * note_duration);

% Modulazione di frequenza
I_x = 4 + 5*rand()*t/max(t);
I_y = 2 + 6*rand()*t/max(t);
I_z = 3 + 4*rand()*t/max(t);

for i = 1:length(x_freq)
    % Envelope ADSR diversi per ogni traccia
    adsr_x = adsr_env(fs, 2, 1, 0.6 + 0.2*unifrnd(0,1), 2, 1);
    adsr_y = adsr_env(fs, 1.5, 1.2, 0.7 + 0.1*unifrnd(0,1), 2.5, 0.8);
    adsr_z = adsr_env(fs, 1.8, 0.9, 0.75 + 0.15*unifrnd(0,1), 2.1, 1.2);

    % Generazione della nota
    tone_x = 0.9 * sin(2*pi*x_freq(i)*t + I_x .* sin(2*pi*x_freq(i)*t)) .* adsr_x;
    tone_y = 0.8 * sin(2*pi*y_freq(i)*t + I_y .* sin(2*pi*y_freq(i)*t)) .* adsr_y;
    tone_z = 0.5 * sin(2*pi*z_freq(i)*t + I_z .* sin(2*pi*z_freq(i)*t)) .* adsr_z;
    
    % Inserimento nella musica
    tone = (tone_x + tone_y + tone_z)/3;
    drone = [drone, tone];
end

% Normalizzazione e salvataggio
drone = drone / max(abs(drone));
audiowrite("music/lorenz_drone_track.wav", drone, fs);
sound(drone, fs);