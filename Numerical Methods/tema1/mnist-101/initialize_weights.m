function [matrix] = initialize_weights(L_prev, L_next)
  epsi = sqrt(6/(L_prev + L_next));
  matrix = rand(L_next, L_prev+1); % generez val random intre 0,1
  matrix = matrix * 2 * epsi - epsi; % schimb intervalu in -e, e
end
