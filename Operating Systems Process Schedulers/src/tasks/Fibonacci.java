package tema1POO.tasks;

/**
 * Fibonacci
 * @author Vlad Ilie
 */
public class Fibonacci implements Tasks {

	/**
	 * Calculeaza al n-lea numar fibonacci % 9973.
	 */
	@Override
	public int calcul(int n) {
		int fibo1 = 0, fibo2 = 1, aux;
		
		if(n == 1)
			return fibo2;
		else if(n == 0)
			return fibo1;
		else if(n < 0)
			return -1;
		
		for(int i = 1; i < n; i++) {
			fibo1 = (fibo1 + fibo2) % 9973;
			aux = fibo2;
			fibo2 = fibo1;
			fibo1 = aux;
		}
		
		return fibo2;
	}

}
