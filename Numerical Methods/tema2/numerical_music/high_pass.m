function filtered_signal = high_pass(x, fs, fc)
    % filtru trece sus basic

    % facem vector coloana
    x = x(:);

    % fft-ul clasik
    X = fft(x);
    n = length(X);

    % frecventele pt fft
    frec = (0:n-1)' * fs / n;

    % masca pt frecvente > fc
    masca = frec > fc;

    % partea simetrica (frecvente negative)
    masca(n:-1:ceil(n/2)+1) = masca(2:floor(n/2)+1);

    % aplica masca
    X_filtrat = X .* masca;

    % ifft inapoi la timp
    filtered_signal = real(ifft(X_filtrat));

    % normalizeaza
    filtered_signal = filtered_signal / max(abs(filtered_signal));
end
