function mat = read_mat(path)
    % deschide fisieru
    f = fopen(path, 'r');

    % citeste liniile alea
    l = {};
    k = 0;
    while ~feof(f)
        lin = fgetl(f);
        if ischar(lin)
            k = k + 1;
            l{k} = lin;
        end
    end
    fclose(f);

    % sarim peste prima linie
    l = l(2:end);
    n = length(l);

    % vezi cate coloane sunt
    b = strsplit(l{1}, ',');
    m = length(b) - 1;

    % facem matricea goala
    mat = zeros(n, m);

    % umplem matricea
    for i = 1:n
        p = strsplit(l{i}, ',');
        for j = 2:length(p)
            mat(i, j-1) = str2double(p{j});
        end
    end
end
