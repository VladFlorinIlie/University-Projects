package tema1POO.schedulers;

import tema1POO.cache.Cache;
import tema1POO.inputOutput.ProcessStructure;

/**
 * Round Robin Scheduler
 * @author Vlad
 */
public class RoundRobinScheduler extends Scheduler {

	public RoundRobinScheduler(ProcessStructure[] processes, int[] numbersToBeProcessed, Cache cache, String out) {
		super(processes, numbersToBeProcessed, cache, out);
	}

	/**
	 * Round Robin executa fiecare proces o data pentru un numar. Dupa executia
	 * fiecarui proces, creste contorul pentru numere. Acest for se repeta atat
	 * timp cat exista numere de procesat. Partea de cautare in cache si afisare
	 * este la fel ca la celelalte schedulere.
	 */
	@Override
	public void choose() {
		int n = processes.length, cnt = 0, calcul;
		
		loop:
			while(cnt < numbersToBeProcessed.length) {
				for(int i = 0; i < n; i++) {
					
					if(cache != null) {
						calcul = cache.find(processes[i].getType(), numbersToBeProcessed[cnt]);
						if(calcul == Integer.MIN_VALUE) {
							calcul = tasks[i].calcul(numbersToBeProcessed[cnt]);
							cache.add(processes[i].getType(), numbersToBeProcessed[cnt], calcul);
							write.println(numbersToBeProcessed[cnt] + " " + processes[i].getType() + " " + calcul + " " + "Computed");
						}
						else
							write.println(numbersToBeProcessed[cnt] + " " + processes[i].getType() + " " + calcul + " " + "FromCache");
					}
					else {
						calcul = tasks[i].calcul(numbersToBeProcessed[cnt]);
						write.println(numbersToBeProcessed[cnt] + " " + processes[i].getType() + " " + calcul + " " + "Computed");
					}
					
					cnt++;
					
					if(cnt >= numbersToBeProcessed.length)
						break loop;
				}
			}
		
		write.close();
		
	}
	
}
