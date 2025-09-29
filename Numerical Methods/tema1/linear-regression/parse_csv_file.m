function [Y, InitialMatrix] = parse_csv_file(file_path)
  input = textread(file_path, '%s', 'delimiter', '\n');

  %parsing cu strsplit
  m = length(strsplit(input{1}, ','));
  Y = zeros(length(input)-1,1);
  for i = 1:length(input)-1
    aux = strsplit(input{i+1}, ',');
    Y(i) = str2double(aux{1});
    for j = 1:m-1
    InitialMatrix{i,j} = aux{j+1};
  endfor
end
