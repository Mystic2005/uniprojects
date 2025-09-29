function [Adj] = get_adjacency_matrix (Labyrinth)

  [m, n] = size(Labyrinth);

  i_sparse = []; %vectori unidimensionali pentru mat Adj sparse
  j_sparse = [];
  val_sparse = [];

  for i = 1:m
    for j = 1:n
      current = (i-1)*n + j; % numerotare conform explicatiilor

      if(~bitand(Labyrinth(i,j), 0b0001)) %bit0
        i_sparse = [i_sparse, current];
        val_sparse = [val_sparse, 1];
        if (j > 1) % verif daca e la margine lose
          j_sparse = [j_sparse, current-1];
        else
          j_sparse = [j_sparse, m*n+2]; %lose
        endif
      endif

      if(~bitand(Labyrinth(i,j), 0b0010)) %bit1
        i_sparse = [i_sparse, current];
        val_sparse = [val_sparse, 1];
        if (j < n) % verif daca e la margine lose
          j_sparse = [j_sparse, current+1];
        else
          j_sparse = [j_sparse, m*n+2]; %lose
        endif
      endif

      if(~bitand(Labyrinth(i,j), 0b0100)) %bit2
        i_sparse = [i_sparse, current];
        val_sparse = [val_sparse, 1];
        if (i < m) % verif daca e la margine win
          j_sparse = [j_sparse, current + n];
        else
          j_sparse = [j_sparse, m*n+1]; %win
        endif
      endif

      if(~bitand(Labyrinth(i,j), 0b1000)) %bit3
        i_sparse = [i_sparse, current];
        val_sparse = [val_sparse, 1];
        if (i > 1) % verif daca e la margine win
          j_sparse = [j_sparse, current - n];
        else
          j_sparse = [j_sparse, m*n+1]; %win
        endif
      endif
    endfor
  endfor

  i_sparse = [i_sparse, n*m+1];
  j_sparse = [j_sparse, n*m+1];
  val_sparse = [val_sparse, 1];
  i_sparse = [i_sparse, n*m+2];
  j_sparse = [j_sparse, n*m+2];
  val_sparse = [val_sparse, 1];

  Adj = sparse(i_sparse, j_sparse, val_sparse, n*m+2, n*m+2);

end
