function coef = spline_c2(x, y)
    % calculeaza coeficientii pentru spline C2
    % x, y = punctele de interpolat
    % coef = coeficientii calculati [a0 b0 c0 d0 a1 b1 ...]

    n = length(x) - 1;
    nr_eq = 4 * n;

    A = zeros(nr_eq, nr_eq);
    b = zeros(nr_eq, 1);
    eq = 1;

    % conditii de interpolare
    for i = 1:n
        start = 4 * (i - 1) + 1;
        A(eq, start) = 1;
        b(eq) = y(i);
        eq = eq + 1;
    end

    % ultimul punct
    start = 4 * (n - 1) + 1;
    h = x(n+1) - x(n);
    A(eq, start) = 1;
    A(eq, start + 1) = h;
    A(eq, start + 2) = h^2;
    A(eq, start + 3) = h^3;
    b(eq) = y(n+1);
    eq = eq + 1;

    % continuitate
    for i = 1:n-1
        start_i = 4 * (i - 1) + 1;
        start_i1 = 4 * i + 1;
        h = x(i+1) - x(i);

        A(eq, start_i) = 1;
        A(eq, start_i + 1) = h;
        A(eq, start_i + 2) = h^2;
        A(eq, start_i + 3) = h^3;
        A(eq, start_i1) = -1;
        eq = eq + 1;
    end

    % derivata continua
    for i = 1:n-1
        start_i = 4 * (i - 1) + 1;
        start_i1 = 4 * i + 1;
        h = x(i+1) - x(i);

        A(eq, start_i + 1) = 1;
        A(eq, start_i + 2) = 2*h;
        A(eq, start_i + 3) = 3*h^2;
        A(eq, start_i1 + 1) = -1;
        eq = eq + 1;
    end

    % derivata a doua continua
    for i = 1:n-1
        start_i = 4 * (i - 1) + 1;
        start_i1 = 4 * i + 1;
        h = x(i+1) - x(i);

        A(eq, start_i + 2) = 2;
        A(eq, start_i + 3) = 6*h;
        A(eq, start_i1 + 2) = -2;
        eq = eq + 1;
    end

    % conditii la capete
    A(eq, 3) = 2;
    eq = eq + 1;

    start = 4 * (n - 1) + 1;
    h = x(n+1) - x(n);
    A(eq, start + 2) = 2;
    A(eq, start + 3) = 6*h;

    coef = A \ b;
end
