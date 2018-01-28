package tema1POO.tasks;

/**
 * Square
 * @author Vlad Ilie
 */
public class Square implements Tasks {

	/**
	 * Calculeaza patratul numarului n.
	 */
	@Override
	public int calcul(int n) {
		return (int) Math.pow(n, 2);
	}

}
