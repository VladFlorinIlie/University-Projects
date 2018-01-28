function x = inmultire(y, z) %pentru un timp cat mai bun, y < z
  ly = length(y);
  lz = length(z);
  x = '0';
  adun = '';
  r = 0;
  
  y = flip(y);
  z = flip(z);
  
  for i = 1:ly
    for j = 1:lz
      aux = (y(i) - 48) * (z(j) - 48) + r;
      if aux >= 10
        adun = strcat(adun, mod(aux, 10) + 48);
        r = floor(aux / 10);
      else
        adun = strcat(adun, aux + 48);
        r = 0;
      endif
    endfor
    if r != 0
      adun = strcat(adun, r + 48);
      r = 0;
    endif
    adun = strcat(zeros(1, i - 1) + 48, adun);
    x = adunare(x, flip(adun));
    adun = '';
  endfor

endfunction      