function coef = vandermonde(x, y)
    % calculeaza coeficientii polinomului folosind matricea Vandermonde
    % x, y = punctele de interpolat
    % coef = coeficientii polinomului

    n = length(x) - 1;
    V = zeros(n+1, n+1);

    for i = 1:n+1
        for j = 1:n+1
            V(i, j) = x(i)^(j-1);
        end
    end

    coef = V \ y;
end
