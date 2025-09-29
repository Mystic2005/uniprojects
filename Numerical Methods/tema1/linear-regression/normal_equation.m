function [Theta] = normal_equation(FeatureMatrix, Y, tol, iter)
  %Schimb variabilele sa fie mai usor de replicat metoda
  A = FeatureMatrix' * FeatureMatrix;
  b = FeatureMatrix' * Y;
  Theta = zeros(size(b)); % initializez cu x_0 = zerouri ca sol init
  r = b - A * Theta; % rez
  v = r; % dir
  k = 1; % iter
  while ((k <= iter) && (r' * r > tol ^ 2))
    t = (r' * r) / (v' * A * v);
    Theta = Theta + t * v;
    r_vechi = r;
    r = r - t * A * v;
    s = (r' * r) / (r_vechi' * r_vechi);
    v = r + s * v;
    k = k + 1;
  endwhile
  Theta = [0; Theta];
end
