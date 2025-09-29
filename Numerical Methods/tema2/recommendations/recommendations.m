function recoms = recommendations(path, liked_theme, num_recoms, min_reviews, num_features)
    % incarca datele
    m = read_mat(path);

    % curata datele
    mclean = preprocess(m, min_reviews);

    % face magie cu svd daca trebuie
    if num_features > 0 && num_features < size(mclean, 2)
        [u, s, v] = svd(mclean);
        v = v(:, 1:num_features);
    else
        % altfel face altceva
        v = mclean';
        v = v ./ sqrt(sum(v.^2, 2));
    end

    % ia tema preferata
    vp = v(liked_theme, :);

    % calculeaza cat de similare sunt
    sim = zeros(size(v, 1), 1);
    for i = 1:size(v, 1)
        if i ~= liked_theme
            vc = v(i, :);
            % formula din curs
            p = sum(vp .* vc);
            n1 = sqrt(sum(vp.^2));
            n2 = sqrt(sum(vc.^2));

            if n1 == 0 || n2 == 0
                sim(i) = 0;
            else
                sim(i) = p / (n1 * n2);
            end
        else
            sim(i) = -Inf;
        end
    end

    % sorteaza si ia cele mai bune
    [~, idx] = sort(sim, 'descend');
    recoms = idx(1:min(num_recoms, length(idx)))';
end
