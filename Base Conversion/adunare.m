function x = adunare(y, z)
  ly = length(y);
  lz = length(z);
  r = 0;
  x = '';
  if ly >= lz
    max = ly;
    min = lz;
  else
    max = lz;
    min = ly;
  endif
  
  y = flip(y);
  z = flip(z);
  
  for i = 1:max
    if i <= min
      aux = (y(i) - 48) + (z(i) - 48) + r;
    elseif ly < lz
      aux = (z(i) - 48) + r;
    else
      aux = (y(i) - 48) + r;
    endif
    if aux >= 10
      x = strcat(x, mod(aux, 10) + 48);
      r = floor(aux / 10);
    else
      x = strcat(x, aux + 48);
      r = 0;
    endif
  endfor
  if r != 0
    x = strcat(x, r + 48);
  endif
    
  x = flip(x);    
    
endfunction