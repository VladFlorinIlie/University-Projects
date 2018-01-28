package tema1POO;

import tema1POO.cache.Cache;
import tema1POO.cache.LfuCache;
import tema1POO.cache.LruCache;
import tema1POO.inputOutput.HomeworkReader;
import tema1POO.inputOutput.ProblemData;
import tema1POO.inputOutput.ProcessStructure;
import tema1POO.schedulers.RandomScheduler;
import tema1POO.schedulers.RoundRobinScheduler;
import tema1POO.schedulers.Scheduler;
import tema1POO.schedulers.WeightedScheduler;

/**
 * @author Vlad Ilie
 */
public class Main {
	
	/**
	 * Functia creaza un nou cache de tip "type".
	 * @param type tipul cache-ului
	 * @param lines numarul de linii din cache
	 * @return
	 */
	private static Cache newCache(String type, int lines) {
		switch(type) {
		case "LfuCache": return new LfuCache(lines);
		case "LruCache": return new LruCache(lines);
		default: return null;
		}
	}
	
	/**
	 * Functia creaza un nou scheduler de tip "type".
	 * @param type tipul scheduler-ului
	 * @param processes vectorul de procese citite din fisier
	 * @param numbers vectorul de numere
	 * @param cache obiectul de tip cache
	 * @return
	 */
	private static Scheduler newScheduler(String type, ProcessStructure[] processes, int[] numbers, Cache cache, String out) {
		switch(type) {
		case "RandomScheduler": return new RandomScheduler(processes, numbers, cache, out);
		case "RoundRobinScheduler": return new RoundRobinScheduler(processes, numbers, cache, out);
		case "WeightedScheduler": return new WeightedScheduler(processes, numbers, cache, out);
		default: return null;
		}
	}

	public static void main(String[] args) {
		HomeworkReader read = new HomeworkReader(args[0]);
		ProblemData date;
		Scheduler scheduler;
		Cache cache;
		
		date = read.readData();
		cache = newCache(date.getCacheType(), date.getCacheCapacity());
		scheduler = newScheduler(date.getSchedulerType(), date.getProcesses(), date.getNumbersToBeProcessed(), cache, args[1]);
		
		scheduler.choose();
	}

}
