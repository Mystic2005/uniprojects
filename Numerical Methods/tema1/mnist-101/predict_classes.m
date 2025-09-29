function [classes] = predict_classes(X, weights, ...
                  input_layer_size, hidden_layer_size, ...
                  output_layer_size)

  %reshape si forward propagation ca la cost_function.m
  Theta1 = zeros(hidden_layer_size, input_layer_size +1);
  Theta2 = zeros(output_layer_size, hidden_layer_size +1);
  Theta1 = reshape(weights(1:hidden_layer_size*(input_layer_size+ 1)),hidden_layer_size, input_layer_size +1);
  Theta2 = reshape(weights(hidden_layer_size* (input_layer_size+1) + 1:end), output_layer_size,hidden_layer_size +1);

  a = [ones(size(X, 1), 1), X];
  z = a * Theta1';
  a = sigmoid(z);
  a = [ones(size(a,1),1) a];
  z = a * Theta2';
  a = sigmoid(z);

  %iau maximul de pe fiecare linie
  [m, n] = size(a);
  classes = zeros(m, 1);

  for i = 1:m
      max = -Inf;
      for j = 1:n
          if a(i, j) > max
              max = a(i, j);
              classes(i) = j;  % indicele
          end
      end
  end
end
