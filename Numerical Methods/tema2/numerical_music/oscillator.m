function x = oscillator(freq, fs, dur, A, D, S, R)
    % face un sunet cu envelope adsr

    % calculeaza nr de esantioane
    nr_esantioane = round(dur * fs);
    t = (0:nr_esantioane - 1)' / fs;

    % semnalul sinus de baza
    x = sin(2 * pi * freq * t);

    % duratele pt fiecare faza
    A_es = round(A * fs);  % attack
    D_es = round(D * fs);  % decay
    R_es = round(R * fs);  % release
    S_es = nr_esantioane - (A_es + D_es + R_es);  % sustain

    % verificare sa nu iasa negativ
    if S_es < 0
        S_es = 0;
        R_es = nr_esantioane - (A_es + D_es);
    end

    % construieste envelope-ul
    envelope = [linspace(0, 1, A_es), ...  % attack
               linspace(1, S, D_es), ...  % decay
               S * ones(1, S_es), ...     % sustain
               linspace(S, 0, R_es)];     % release

    % ajusteaza dimensiunea
    envelope = envelope(:);
    if length(envelope) < nr_esantioane
        envelope = [envelope; zeros(nr_esantioane - length(envelope), 1)];
    elseif length(envelope) > nr_esantioane
        envelope = envelope(1:nr_esantioane);
    end

    % aplica envelope-ul
    x = x .* envelope;
end
