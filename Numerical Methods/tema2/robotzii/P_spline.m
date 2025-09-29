function rez = P_spline(coef, x, x_interp)
    % calculeaza valoarea spline in punctele x_interp
    % coef = [a0 b0 c0 d0 a1 b1 ...] coeficientii pentru fiecare interval
    % x = punctele de divizare
    % rez = valorile interpolate

    n = length(x) - 1;
    rez = zeros(size(x_interp));

    for k = 1:length(x_interp)
        xval = x_interp(k);

        % gaseste intervalul corect
        idx = 1;
        for j = 1:n
            if xval >= x(j) && xval <= x(j+1)
                idx = j;
                break;
            end
        end

        if xval == x(end)
            idx = n;
        end

        % ia coeficientii
        start = 4 * (idx - 1) + 1;
        a = coef(start);
        b = coef(start + 1);
        c = coef(start + 2);
        d = coef(start + 3);

        % calculeaza valoarea
        dx = xval - x(idx);
        rez(k) = a + b*dx + c*dx^2 + d*dx^3;
    end

    rez = rez(:);
end
