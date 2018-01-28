package tema1POO.tasks;

/**
 * Check Prime
 * @author Vlad Ilie
 */
public class CheckPrime implements Tasks {

	/**
	 * Il imparte pe n la toti posibilii divizori. Daca gaseste
	 * unul, returneaza 1. Altfel, returneaza 0.
	 */
	@Override
	public int calcul(int n) {
		int prim = 1;
		
		if(n <= 1)
			return 0;
		
		for(int i = 2; i <= n/2; i++)
			if(n % i == 0) {
				prim = 0;
				break;
			}
		
		return prim;
	}

}
