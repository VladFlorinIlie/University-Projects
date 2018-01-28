package tema2POO;

import java.util.Scanner;

/**
 * 
 * @author Vlad Ilie
 *
 */
public class Main {

	public static void main(String[] args) {
		String currentLine;
		String[] lineSplit;
		Feed feed = Feed.getFeedInstance();
		ObserversFactory factory = ObserversFactory.getFactory();

		Scanner input = new Scanner(System.in);
		currentLine = input.nextLine();
		currentLine = input.nextLine();
		
		while(!currentLine.equals("end")) {
			lineSplit = currentLine.split("\\s+", 3);
			
			switch(lineSplit[0]) {
			case "create_obs":	factory.getObserver(Integer.parseInt(lineSplit[1]), lineSplit[2], feed);
								break;
			case "delete_obs":	feed.remove(Integer.parseInt(lineSplit[1]));
								break;
			case "print":		feed.print(Integer.parseInt(lineSplit[1]));
								break;
			case "feed":		feed.setNewFeed(lineSplit[1], lineSplit[2]);
								break;
			default:			
			}
			
			currentLine = input.nextLine();
		}
		
		input.close();
	}

}
