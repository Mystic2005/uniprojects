function [Theta] = gradient_descent(FeatureMatrix, Y, n, m, alpha, iter)
  Theta = zeros(n+1,1);
  FeatureMatrix = [zeros(m,1), FeatureMatrix]; %bias
  %algoritmul;
  for i = 1:iter
    for j = 2:n+1
    Theta(j) = Theta(j) - alpha/m * sum((FeatureMatrix*Theta - Y) .* FeatureMatrix(:, j));
    endfor
  endfor
end
