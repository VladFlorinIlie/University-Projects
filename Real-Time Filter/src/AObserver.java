package tema2POO;

/**
 * Clasa extinsa de observatori.
 * feed = legatura catre obiectul feed.
 * notified() = functia prin care observatorii sunt notificati.
 * getId() = intoarce id-ul observatorului.
 * @author Vlad Ilie
 *
 */
public abstract class AObserver {
	protected Feed feed;
	public abstract void notified();
	public abstract void print();
	public abstract int getId();
}
