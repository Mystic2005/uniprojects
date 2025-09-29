function [Error] = ridge_regression_cost_function(Theta, Y, FeatureMatrix, lambda)
  m = size(FeatureMatrix, 1);
  h = zeros(m,1);
  FeatureMatrix = [ones(m,1), FeatureMatrix];
  for i = 1:m
    h(i) = FeatureMatrix(i,:)*Theta;
  endfor
  % acelasi algoritm ca la linear regression
  % formula schimbata + norma L2
  Error = 1/(2*m)*sum((h-Y).^2) + lambda * sum(Theta .^ 2);
end
