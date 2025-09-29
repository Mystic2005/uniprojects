function [Y, InitialMatrix] = parse_data_set_file(file_path)

  input = fopen(file_path, 'r'); % input file

  buffer = fgetl(input);
  [m, n] = strtok(buffer, ' '); % marimea de pe prima linie
  n = str2num(n);
  m = str2num(m);

  Y = [];
  InitialMatrix = cell(m,n);
  for i = 1:m
    buffer = fgetl(input);
    [v, buffer] = strtok(buffer, ' ');
    Y = [Y, str2double(v)]; % Y e prima coloana
    for j = 1:n
      [v, buffer] = strtok(buffer, ' ');
      InitialMatrix{i, j} = v; % atribui pe linii
     endfor
  endfor
  fclose(input);

end
