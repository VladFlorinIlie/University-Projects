package tema1POO.tasks;

/**
 * Sqrt
 * @author Vlad Ilie
 */
public class Sqrt implements Tasks {

	/**
	 * Calculeaza radical de ordin 2 din modulul numarului
	 * n si intoarce valoarea intreaga a acestuia.
	 */
	@Override
	public int calcul(int n) {
		Double rad = Math.sqrt(Math.abs(n));
		return rad.intValue();
	}

}
