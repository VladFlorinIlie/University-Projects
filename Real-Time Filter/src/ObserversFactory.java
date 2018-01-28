package tema2POO;

/**
 * Fabrica de observatori.
 * @author Vlad Ilie
 *
 */
public class ObserversFactory {
	private static ObserversFactory obsFactory;
	
	private ObserversFactory() {}
	
	/**
	 * Instantiaza o fabrica de observatori.
	 * @return fabrica.
	 */
	public static ObserversFactory getFactory() {
		if(obsFactory == null)
			obsFactory = new ObserversFactory();
		
		return obsFactory;
	}
	
	/**
	 * Creaza un observator.
	 * @param id id-ul observatorului.
	 * @param filter filtrul observatorului.
	 * @param feed obiectul feed de care se va lega observatorul.
	 * @return observatorul creat.
	 */
	public AObserver getObserver(int id, String filter, Feed feed) {
		return new Observer(id, filter, feed);
	}
}
