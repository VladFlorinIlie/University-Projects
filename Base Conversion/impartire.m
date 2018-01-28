function [c r] = impartire(y, z)
  ly = length(y);
  imp = 0;
  cnt = 0;
  c = '';
  
  for i = 1:ly
    imp = imp * 10 + y(i) - 48;
    if imp >= z
      c = strcat(c, floor(imp / z) + 48);
      imp = mod(imp, z);
    elseif strcmp(c, '') != 1
      c = strcat(c, '0');
    endif
  endfor
  r = imp;
  if strcmp(c, '') == 1 %daca y < z
    c = '0';
  endif
  
endfunction