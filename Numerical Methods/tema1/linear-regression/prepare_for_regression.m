function [FeatureMatrix] = prepare_for_regression(InitialMatrix)
  [m,n] = size(InitialMatrix);
  FeatureMatrix = zeros(m,n+1); % coloana in plus pt furnished
  for i = 1:m
    j_aux = 1; % indice separat de parcurgere pt FeatureMatrix
    for j = 1:n
      if strcmp(InitialMatrix{i,j}, "yes")
        FeatureMatrix(i,j_aux) = 1;
      elseif strcmp(InitialMatrix{i,j}, "no")
        FeatureMatrix(i,j_aux) = 0;
      elseif strcmp(InitialMatrix{i,j}, "semi-furnished")
        FeatureMatrix(i,j_aux) = 1;
        j_aux=j_aux+1;
        FeatureMatrix(i,j_aux) = 0;
      elseif strcmp(InitialMatrix{i,j}, "unfurnished")
        FeatureMatrix(i,j_aux) = 0;
        j_aux=j_aux+1;
        FeatureMatrix(i,j_aux) = 1;
      elseif strcmp(InitialMatrix{i,j}, "furnished")
        FeatureMatrix(i,j_aux) = 0;
        j_aux=j_aux+1;
        FeatureMatrix(i,j_aux) = 0;
      else
        FeatureMatrix(i,j_aux) = str2double(InitialMatrix{i,j});
      endif
      j_aux = j_aux+1;
    endfor
  endfor
end
