function [X_train, y_train, X_test, y_test] = split_dataset(X, y, percent)
  %shuffle
  perm = randperm(size(X,1));
  X = X(perm, :);
  y = y(perm);

  % impart de la 1 la floor(length(y)*percent) si dupa de la +1 pana la end
  y_train = zeros(length(y) * percent, 1);
  y_test = zeros(length(y) -  (length(y) * percent), 1);
  for i = 1:floor(length(y)*percent)
    for j = 1:size(X, 2)
      X_train(i,j) = X(i,j);
    endfor
    y_train(i) = y(i);
  endfor
  new_iter = 1;
  for i = floor(length(y)*percent+1):length(y)
    for j = 1:size(X, 2)
      X_test(new_iter,j) = X(i,j);
    endfor
    y_test(new_iter) = y(i);
    new_iter = new_iter + 1;
  endfor
end
