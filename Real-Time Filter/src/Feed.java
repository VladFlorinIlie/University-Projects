package tema2POO;

import java.util.ArrayList;
import java.util.List;
import java.util.TreeMap;

/**
 * Feed este subiectul observatorilor.
 * @author Vlad Ilie
 *
 */
public class Feed {
	private static Feed feedInstance;
	private List<AObserver> observers;
	private String newFeedName;
	private TreeMap<String, String> feedMap;
	
	private Feed() {
		observers = new ArrayList<AObserver>();
		feedMap = new TreeMap<String, String>();
	}
	
	/**
	 * Instantiaza un obiect de tip feed.
	 * @return obiectul feed.
	 */
	public static Feed getFeedInstance() {
		if(feedInstance == null)
			feedInstance = new Feed();
		
		return feedInstance;
	}
	
	/**
	 *
	 * @return numele feed-ului curent.
	 */
	public String getNewFeedName() {
		return newFeedName;
	}
	
	/**
	 *
	 * @return colectia de feed-uri.
	 */
	public TreeMap<String, String> getFeedMap() {
		return feedMap;
	}
	
	/**
	 * Seteaza un nou feed si notifica observatorii.
	 * @param newFeedName numele feed-ului.
	 * @param newFeedValue valoarea feed-ului.
	 */
	public void setNewFeed(String newFeedName, String newFeedValue) {
		this.newFeedName = newFeedName;
		feedMap.put(newFeedName, newFeedValue);
		notifyObservers();
	}
	
	/**
	 * Ataseaza un observer.
	 * @param observer referinta catre observer.
	 */
	public void attach(AObserver observer) {
		observers.add(observer);
	}
	
	/**
	 * Sterge un observer.
	 * @param id id-ul observer-ului.
	 */
	public void remove(int id) {
		for(AObserver obs : observers) {
			if(obs.getId() == id) {
				observers.remove(obs);
				break;
			}
		}
	}
	
	/**
	 * Afiseaza un observer.
	 * @param id id-ul observer-ului.
	 */
	public void print(int id) {
		for(AObserver obs : observers) {
			if(obs.getId() == id) {
				obs.print();
				break;
			}
		}
	}
	
	/**
	 * Notifica toti observer.
	 */
	public void notifyObservers() {
		for(AObserver obs : observers) {
			obs.notified();
		}
	}
}
