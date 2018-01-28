function r = baza(sursa, b1, b2)
  if b1 >= 2 && b1 <= 30 && b2 >=2 && b2 <= 30
    l = length(sursa);
    b1dec = '0';
    putere = '1';
    r = '';
    if b1 != 10
      for i=l:-1:1
        if i != l
          putere = inmultire(b1 + 48, putere);
        endif
        if sursa(i) >= 97 && sursa(i) <= 116 %codul ascii de la a la t
          b1dec = adunare(b1dec, inmultire((sursa(i) - 87) + 48, putere));
        elseif sursa(i) >= 65 && sursa(i) <= 84 %codul ascii de la A la T
          b1dec = adunare(b1dec, inmultire((sursa(i) - 55) + 48, putere));
        else %daca nu e litera
          b1dec = adunare(b1dec, inmultire((sursa(i) - 48) + 48, putere));
        endif
      endfor
    else
      b1dec = sursa;
    endif
 
    if b2 != 10
      if strcmp(b1dec, '0') == 1
        r = '0';
      else
        while strcmp(b1dec, '0') != 1
          [b1dec rest] = impartire(b1dec, b2);
          if rest >= 10 && rest <= 29
            r = strcat(r, rest + 87);
          else
            r = strcat(r, rest + 48);
          endif
        endwhile
      endif
      r = flip(r);
    else
      r = b1dec;
    endif
  endif
  
endfunction