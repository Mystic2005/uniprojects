function [Labyrinth] = parse_labyrinth(file_path)

  input = fopen(file_path, 'r'); % input file

  buffer = fgetl(input);
  [m, n] = strtok(buffer, ' '); % marimea de pe prima linie
  n = str2num(n);
  m = str2num(m);

  Labyrinth = zeros(m,n); % init matrice
  for i = 1:m
    buffer = fgetl(input);
    Labyrinth(i, :) = sscanf(buffer, '%f'); % atribui pe linii
  endfor

  fclose(input);
end
