package tema1POO.tasks;

/**
 * Cube
 * @author Vlad Ilie
 */
public class Cube implements Tasks {

	/**
	 * Returneaza cubul numarului n.
	 */
	@Override
	public int calcul(int n) {
		return (int) Math.pow(n, 3);
	}

}
