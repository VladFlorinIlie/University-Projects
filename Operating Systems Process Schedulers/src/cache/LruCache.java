package tema1POO.cache;

/**
 * Lru Cache
 * @author Vlad
 */
public class LruCache extends Cache {

	public LruCache(int numarLinii) {
		super(numarLinii);
	}
	
	/**
	 * Shift-eaza toate elementele de la "pozitie" pana la capat
	 * spre stanga. Elementul de pe "pozitie" va fi mutat la capat.
	 * @param pozitie pozitia elementului ce va fi mutat la capatul din dreapta.
	 */
	private void shiftStanga(int pozitie) {
		CacheStructure aux;
		
		aux = cache[pozitie];
		for(int i = pozitie + 1; i <= poz; i++)
			cache[i - 1] = cache[i];
		cache[poz] = aux;
	}

	/**
	 * Cat timp cache-ul nu e plin, adauga elemente si creste pozitia.
	 * Cand cache-ul e plin, shift-eaza tot vectorul spre stanga iar la
	 * capatul din dreapta adauga elementul nou.
	 */
	@Override
	public void add(String proces, int numar, int calcul) {
		if(poz < numarLinii - 1) {
			poz++;
		}
		else {
			shiftStanga(0); //scoate primul elem din vector
		}
		
		cache[poz].numar = numar;
		cache[poz].numeProces = proces;
		cache[poz].rezultat = calcul;
	}

	/**
	 * Cauta in cache perechea proces-numar. Daca o gaseste, o muta
	 * la capatul din dreapta si returneaza rezultatul. Altfel,
	 * returneaza MIN_VALUE.
	 */
	@Override
	public int find(String proces, int numar) {
		for(int i = 0; i <= poz; i++)
			if(proces.equals(cache[i].numeProces) && cache[i].numar == numar) {
				shiftStanga(i);
				return cache[poz].rezultat;
			}
		return Integer.MIN_VALUE;
	}

}
