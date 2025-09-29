function [x, y] = parse_data(nume_fisier)
    % citeste datele din fisier
    % format: n pe prima linie, apoi x si y

    f = fopen(nume_fisier, 'r');
    if f == -1
        error('Nu pot deschide fisierul');
    end

    n = fscanf(f, '%d', 1);
    x = fscanf(f, '%f', n+1);
    y = fscanf(f, '%f', n+1);

    x = x(:);
    y = y(:);

    fclose(f);
end
