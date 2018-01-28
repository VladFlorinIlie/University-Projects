package tema1POO.cache;

/**
 * Lfu Cache
 * @author Vlad Ilie
 */
public class LfuCache extends Cache {

	public LfuCache(int numarLinii) {
		super(numarLinii);
	}

	/**
	 * Cat timp cache-ul nu este plin, adauga elemente in cache si
	 * creste poz. Atunci cand cache-ul este plin, cauta elementul
	 * cu cele mai putine folosiri si il inlocuieste cu cel curent.
	 */
	@Override
	public void add(String proces, int numar, int calcul) {
		int pozNoua = poz, min = Integer.MAX_VALUE;
		
		if(poz < numarLinii - 1) {
			poz++;
			pozNoua = poz;
		}
		else {
			for(int i = 0; i <= poz; i++)
				if(cache[i].numarFolosiri < min) {
					min = cache[i].numarFolosiri;
					pozNoua = i;
				}
		}
		
		cache[pozNoua].numar = numar;
		cache[pozNoua].numeProces = proces;
		cache[pozNoua].rezultat = calcul;
		cache[pozNoua].numarFolosiri = 0;
	}

	/**
	 * Cauta in cache perechea proces-numar. Daca o gaseste, ii creste
	 * numarul de folosiri si intoarce rezultatul din cache. Altfel
	 * intoarce MIN_VALUE.
	 */
	@Override
	public int find(String proces, int numar) {
		for(int i = 0; i <= poz; i++)
			if(proces.equals(cache[i].numeProces) && cache[i].numar == numar) {
				cache[i].numarFolosiri++;
				return cache[i].rezultat;
			}
		return Integer.MIN_VALUE;
	}

}
