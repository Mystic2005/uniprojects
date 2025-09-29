function [Error] = linear_regression_cost_function(Theta, Y, FeatureMatrix)
  m = size(FeatureMatrix, 1);
  h = zeros(m,1);
  FeatureMatrix = [ones(m, 1), FeatureMatrix]; % theta0 are coeficientul 1
  for i = 1:m
    h(i) = FeatureMatrix(i,:)*Theta; % fiecare element = combinatie liniara
  endfor
  Error = 1/(2*m)*sum((h-Y).^2); % calcul eroare cu formula pt J
end
