package tema1POO.schedulers;

import java.util.Random;

import tema1POO.cache.Cache;
import tema1POO.inputOutput.ProcessStructure;

/**
 * Random Scheduler
 * @author Vlad Ilie
 */
public class RandomScheduler extends Scheduler {

	public RandomScheduler(ProcessStructure[] processes, int[] numbersToBeProcessed, Cache cache, String out) {
		super(processes, numbersToBeProcessed, cache, out);
	}

	/**
	 * Cat timp exista numere ce trbuie procesate, alege un numar random
	 * intre 0 si n-1. Daca exista cache, cauta rezultatul in cache. In cazul
	 * in care exista rezultatul, il afiseaza, altfel il calculeaza, il adauga
	 * in cache si apoi il afiseaza. Daca nu exista cache, face calculul apoi
	 * il afiseaza. Variabila cnt reprezinta contorul pentru vectorul de numere.
	 */
	@Override
	public void choose() {
		int n = processes.length, rand, cnt = 0, calcul;
		Random random = new Random();
		
		while(cnt < numbersToBeProcessed.length) {
			rand = random.nextInt(n);
			
			if(cache != null) {
				calcul = cache.find(processes[rand].getType(), numbersToBeProcessed[cnt]);
				if(calcul == Integer.MIN_VALUE) {
					calcul = tasks[rand].calcul(numbersToBeProcessed[cnt]);
					cache.add(processes[rand].getType(), numbersToBeProcessed[cnt], calcul);
					write.println(numbersToBeProcessed[cnt] + " " + processes[rand].getType() + " " + calcul + " " + "Computed");
				}
				else
					write.println(numbersToBeProcessed[cnt] + " " + processes[rand].getType() + " " + calcul + " " + "FromCache");
			}
			else {
				calcul = tasks[rand].calcul(numbersToBeProcessed[cnt]);
				write.println(numbersToBeProcessed[cnt] + " " + processes[rand].getType() + " " + calcul + " " + "Computed");
			}
			
			cnt++;
		}
		write.close();
		
	}

}
