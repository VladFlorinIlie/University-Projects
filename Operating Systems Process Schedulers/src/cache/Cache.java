package tema1POO.cache;

/**
 * Clasa parinte pentru obiectele de tip cache.
 * @author Vlad Ilie
 */
public abstract class Cache {
	protected CacheStructure[] cache;
	protected int numarLinii, poz = -1;
	
	/**
	 * Creaza un vector de tip CacheStructure.
	 * @param numarLinii numarul de linii din cache.
	 */
	public Cache(int numarLinii) {
		this.numarLinii = numarLinii;
		cache = new CacheStructure[numarLinii];
		for(int i = 0; i < numarLinii; i++)
			cache[i] = new CacheStructure();
	}
	
	/**
	 * Functia adauga numele procesului, numarul si rezultatul procesului in cache.
	 * @param proces numele procesului.
	 * @param numar numarul pe baza caruia va fi rulat procesul.
	 * @param calcul rezultatul procesului.
	 */
	public abstract void add(String proces, int numar, int calcul);
	
	/**
	 * Functia verifica daca exista rezultatul procesului "proces" pe "numar" in cache.
	 * @param proces numele procesului.
	 * @param numar numarul pe baza caruia va fi rulat procesul.
	 * @return
	 */
	public abstract int find(String proces, int numar);
}
