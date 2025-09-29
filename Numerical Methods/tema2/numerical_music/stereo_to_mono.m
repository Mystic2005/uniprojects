function mono = stereo_to_mono(stereo)
    % transforma stereo in mono

    % face media pe canale
    mono = mean(stereo, 2);

    % normalizeaza
    val_max = max(abs(mono));

    if val_max > 0
        mono = mono / val_max;
    end

    % asigura ca e vector coloana
    mono = mono(:);
end
