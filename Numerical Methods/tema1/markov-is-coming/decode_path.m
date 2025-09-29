function [decoded_path] = decode_path (path, lines, cols)
  path(end) = [];
  decoded_path = zeros(length(path),2);
  %formula pentru decodat path
  for i = length(path):-1:1
    decoded_path(i,1) = ceil(path(i)/cols);
    decoded_path(i,2) = path(i) - (decoded_path(i,1)-1)*cols;
  endfor
end
