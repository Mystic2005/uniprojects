function [Error] = lasso_regression_cost_function(Theta, Y, FeatureMatrix, lambda)
  m = size(FeatureMatrix, 1);
  h = zeros(m,1);
  FeatureMatrix = [ones(m,1), FeatureMatrix];
  for i = 1:m
    h(i) = FeatureMatrix(i,:)*Theta;
  endfor
  % acelasi algoritm ca la linear regression
  % formula schimbata + norma L2
  Error = 1/m*sum((Y-h).^2) + lambda * sum(abs(Theta));
end
