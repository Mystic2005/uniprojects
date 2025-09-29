function [S, f, t] = spectrogram(signal, fs, window_size)
    % face spectrograma simplu

    signal = signal(:);
    n = length(signal);
    nr_ferestre = floor(n / window_size);

    % matrice pt spectrograma
    S = zeros(window_size, nr_ferestre);

    % fereastra hann
    fereastra_hann = hanning(window_size);

    for i = 1:nr_ferestre
        % extrage fereastra curenta
        start = (i-1)*window_size + 1;
        sfarsit = i*window_size;
        fereastra = signal(start:sfarsit);

        % aplica fereastra hann
        fereastra = fereastra .* fereastra_hann;

        % fft cu zero-padding
        fft_fereastra = fft(fereastra, window_size*2);

        % ia doar jumatate (partea utila)
        S(:, i) = abs(fft_fereastra(1:window_size));
    end

    % vectori de frecvente si timp
    f = (0:window_size-1)' * fs / (window_size*2);
    t = (0:nr_ferestre-1)' * window_size / fs;
end
