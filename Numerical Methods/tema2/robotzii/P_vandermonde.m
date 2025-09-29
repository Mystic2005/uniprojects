function rez = P_vandermonde(coef, x_interp)
    % calculeaza polinomul in punctele x_interp
    % coef = coeficientii polinomului [a0 a1 ... an]
    % rez = valorile calculate

    n = length(coef) - 1;
    rez = zeros(size(x_interp));

    for i = 1:length(x_interp)
        val = 0;
        for j = 1:n+1
            val = val + coef(j) * x_interp(i)^(j-1);
        end
        rez(i) = val;
    end

    rez = rez(:);
end
