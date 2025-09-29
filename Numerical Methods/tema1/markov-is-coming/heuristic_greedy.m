function [path] = heuristic_greedy (start_position, probabilities, Adj)
  %functia algoritm euristic din tema
  [n,m] = size(probabilities);
  path = [start_position];
  visited = zeros(n, 1);
  visited(start_position) = 1;
  while (length(path) != 0)
    position = path(end);
    if Adj(position, n-1)!= 0 % n-1 e starea win
      path = [path, n-1]; %starea win
      return;
    endif
    neighbors = []; % caut vecinii nevizitati
    for i = 1:n
      if (Adj(position, i)!=0 && ~visited(i))
        neighbors = [neighbors, i];
      endif
    endfor

    if (length(neighbors) == 0) % nu exista vecini
      path(end) = []; % elimin position din path
    else
      max = -inf;
      for i = 1:length(neighbors) % aflu maximul de prob dintre neighbors
        if (probabilities(neighbors(i)) > max)
          neigh = neighbors(i);
          max = probabilities(neigh);
        endif
      endfor
      visited(neigh) = 1;
      path = [path, neigh]; % adaug noul nod in path
    endif
  endwhile
  return;
end
