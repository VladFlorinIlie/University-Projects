package tema1POO.tasks;

/**
 * Factorial
 * @author Vlad Ilie
 */
public class Factorial implements Tasks {

	/**
	 * Calculeaza n! % 9973.
	 */
	@Override
	public int calcul(int n) {
		int fact = 1;
		
		if(n < 0)
			return 0;
		
		for(int i = 1; i <= n; i++)
			fact = (fact * i) % 9973;
		
		return fact;
	}

}
