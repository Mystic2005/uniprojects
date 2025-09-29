function out = preprocess(mat, min_reviews)
    % numara reviewuri per user
    rev = sum(mat ~= 0, 2);

    % ia doar userii cu destule reviewuri
    ok = rev >= min_reviews;
    out = mat(ok, :);
end
