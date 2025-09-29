function signal_out = apply_reverb(signal_in, impulse_response)
    % baga reverb pe semnal cu raspunsul ala impuls

    % daca e stereo, facem mono
    if size(impulse_response, 2) > 1
        impulse_response = stereo_to_mono(impulse_response);
    end

    % verifica daca e mono sau stereo
    if size(signal_in, 2) == 1
        % merge pe un singur canal
        semnal_cu_ecou = fftconv(signal_in, impulse_response);
    else
        % merge pe ambele canale
        canal_stanga = fftconv(signal_in(:, 1), impulse_response);
        canal_dreapta = fftconv(signal_in(:, 2), impulse_response);
        semnal_cu_ecou = [canal_stanga, canal_dreapta];
    end

    % normalizeaza ca sa nu dea overflow
    val_max = max(abs(semnal_cu_ecou(:)));

    if val_max > 0
        signal_out = semnal_cu_ecou / val_max;
    else
        signal_out = semnal_cu_ecou;
    end
end
