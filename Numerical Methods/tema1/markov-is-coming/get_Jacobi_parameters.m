function [G, c] = get_Jacobi_parameters (Link)
  [m,n] = size(Link);

  i_sparse = [];
  j_sparse = [];
  val_sparse = [];
  for i = 1:m-2 %formez G fara starile win/lose
    for j = 1:n-2
      if Link(i,j) != 0
        i_sparse = [i_sparse, i];
        j_sparse = [j_sparse, j];
        val_sparse = [val_sparse, Link(i,j)];
      endif
    endfor
  endfor
  G = sparse(i_sparse, j_sparse, val_sparse, (m-2), (n-2));

  i_sparse = [];
  j_sparse = [];
  val_sparse = [];
  for i = 1:m-2 % formez doar starea de win
    j = n-1;
    if Link(i,j) != 0
      i_sparse = [i_sparse, i];
      j_sparse = [j_sparse, 1];
      val_sparse = [val_sparse, Link(i,j)];
    endif
  endfor
  c = sparse(i_sparse, j_sparse, val_sparse, m-2, 1);
endfunction
