function [x, err, steps] = perform_iterative (G, c, x0, tol, max_steps)
  % met jacobi din lab5
  x = x0;
  steps = 1;
  err = Inf;
  while (steps <= max_steps)
    x_prev = x;
    x = G*x + c;
    if norm(x-x_prev) < tol
      err = norm(x-x_prev);
      break
    endif
    steps++;
  endwhile
end
