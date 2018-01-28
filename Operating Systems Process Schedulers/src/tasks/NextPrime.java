package tema1POO.tasks;

/**
 * Next Prime
 * @author Vlad Ilie
 */
public class NextPrime implements Tasks {

	/**
	 * Calculeaza urmatorul numar prim dupa n cu ajutorul
	 * lui CheckPrime.
	 */
	@Override
	public int calcul(int n) {
		CheckPrime prim = new CheckPrime();
		n++;
		
		while(prim.calcul(n) == 0)
			n++;
		
		return n;
	}

}
