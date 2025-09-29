function s = cosine_similarity(a, b)
    % produs scalar
    p = a' * b;

    % normele lor
    na = sqrt(a' * a);
    nb = sqrt(b' * b);

    % formula din curs
    if na == 0 || nb == 0
        s = 0;
    else
        s = p / (na * nb);
    end
end
