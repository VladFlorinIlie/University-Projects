package tema2POO;

import java.util.Map;
import java.util.TreeMap;

import tema2POO.visitTree.INodeVisitor;
import tema2POO.visitTree.IVisitNode;
import tema2POO.visitTree.TreeVisitor;

/**
 * 
 * @author Vlad Ilie
 *
 */
public class Observer extends AObserver {
	private int id;
	private TreeMap<String, FeedInfo> feedInfoMap;
	private String filter;
	private IVisitNode filterTree;
	private INodeVisitor visitor;
	private String[] feedCurent;

	Observer(int id, String filter, Feed feed) {
		this.id = id;
		this.filter = filter;
		this.feed = feed;
		feedInfoMap = new TreeMap<String, FeedInfo>();
		feedCurent = new String[2];

		if (!filter.equals("nil")) {
			visitor = new TreeVisitor();
			filterTree = new ParseFilter(filter, feedCurent).shuntingYard(); // creaza arborele; foloseste feedCurent pe
																				// post de pointer
		}
		
		this.feed.attach(this);
	}

	/**
	 * La fiecare notificare, ia numele feed-ului curent si
	 * si ii creste numarul de schimbari din TreeMap-ul
	 * feedInfoMap.
	 */
	@Override
	public void notified() {
		FeedInfo value;
		String name = feed.getNewFeedName();

		if (feedInfoMap.containsKey(name)) {
			value = feedInfoMap.get(name);
			value.noChanges++;
		} else
			feedInfoMap.put(name, new FeedInfo());

	}

	/**
	 * Parcurge colectia de feed-uri din Feed, actualizeaza
	 * informatia din obiectul feedCurent (pe care il foloseste
	 * filtrul) apoi verifica daca feed-ul respectiv trece de
	 * filtru. Daca da, actualizeaza increase si afiseaza.
	 * In final seteaza noChanges la 0. Daca nu a mai detectat
	 * schimbari asupra feed-ului initializeaza valorile din
	 * feedValue cu 0 si afiseaza.
	 */
	@Override
	public void print() {
		double increase;
		double value;
		TreeMap<String, String> feedMap = feed.getFeedMap();
		FeedInfo feedValue;

		for (Map.Entry<String, String> feedMapValues : feedMap.entrySet()) {
			feedCurent[0] = feedMapValues.getKey(); // actualizeaza cheia si valoarea folosite de arbore
			feedCurent[1] = feedMapValues.getValue();
			value = Double.parseDouble(feedMapValues.getValue());

			if (filter.equals("nil") ? true : filterTree.accept(visitor)) { //trece feed-ul prin filtru
				if (feedInfoMap.containsKey(feedMapValues.getKey())) {

					feedValue = feedInfoMap.get(feedMapValues.getKey());

					if (Double.isNaN(feedValue.increase))
						increase = 0.0d;
					else { //calculeaza increase
						increase = (value - feedValue.increase) / feedValue.increase * 100;
						increase = Math.round(increase * 100);
						increase /= 100;
					}

					System.out.println("obs " + id + ": " + feedMapValues.getKey() + " " + value + " " + increase + "% "
							+ feedValue.noChanges);

					feedValue.increase = value;
					feedValue.noChanges = 0;

				} else {

					feedValue = new FeedInfo();
					feedValue.noChanges = 0;
					increase = 0.0d;

					System.out.println("obs " + id + ": " + feedMapValues.getKey() + " " + value + " " + increase + "% "
							+ feedValue.noChanges);

					feedValue.increase = value;
					feedInfoMap.put(feedMapValues.getKey(), feedValue);
				}
			}
		}

	}

	/**
	 * Returneaza id-ul observer-ului.
	 */
	@Override
	public int getId() {
		return id;
	}

}
