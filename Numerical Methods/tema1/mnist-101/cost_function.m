function [J, grad] = cost_function(params, X, y, lambda, ...
                   input_layer_size, hidden_layer_size, ...
                   output_layer_size)

  % reshape
  Theta1 = zeros(hidden_layer_size, input_layer_size +1);
  Theta2 = zeros(output_layer_size, hidden_layer_size +1);
  Theta1 = reshape(params(1:hidden_layer_size*(input_layer_size+ 1)),hidden_layer_size, input_layer_size +1);
  Theta2 = reshape(params(hidden_layer_size* (input_layer_size+1) + 1:end), output_layer_size,hidden_layer_size +1);

  % forward propagation
  a = [ones(size(X, 1), 1), X];
  first_a = a;
  z = Theta1 * a';
  a = sigmoid(z);
  second_a = a;
  second_a = [ones(1, size(second_a,2)); second_a];
  z = Theta2 * second_a;
  a = sigmoid(z)';

  m = size(X, 1);
  yfrecv = zeros(m, output_layer_size); % vector de frecventa
  for i = 1:m
      yfrecv(i, y(i)) = 1;
  endfor

  %back propagation + eroare
  eroare3 = a - yfrecv;
  grad1 = eroare3'*(second_a');
  second_a = second_a(2:end, :);
  eroare = (Theta2' * eroare3');
  eroare = eroare(2:size(eroare,1), :);
  eroare = eroare .* (second_a .* (1 - second_a));
  grad2 = eroare * first_a;

  %cost
  mat_cost = -yfrecv .* log(a) - (1 - yfrecv) .* log(1 - a);
  other_half = (lambda / (2 * m)) * (sum(sum(Theta1(:,2:end).^2)) + sum(sum(Theta2(:,2:end).^2)));
  J = (1 / m) * sum(sum(mat_cost)) + other_half;

  %regularizare gradienti
  new_theta1 = zeros(size(Theta1));
  new_theta2 = zeros(size(Theta2));
  for i = 2:size(new_theta1, 2)
    new_theta1(:, i) = (lambda / m) * Theta1(:, i);
  endfor
  for i = 2:size(new_theta2, 2)
    new_theta2(:, i) = (lambda / m) * Theta2(:, i);
  endfor
  new_theta1 = (1 / m) * grad2 + new_theta1;
  new_theta2 = (1 / m) * grad1 + new_theta2;

  grad = [new_theta1(:); new_theta2(:)];

end

