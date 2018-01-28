package tema1POO.schedulers;

import tema1POO.cache.Cache;
import tema1POO.inputOutput.ProcessStructure;

/**
 * Weighted Scheduler
 * @author Vlad Ilie
 */
public class WeightedScheduler extends Scheduler {

	public WeightedScheduler(ProcessStructure[] processes, int[] numbersToBeProcessed, Cache cache, String out) {
		super(processes, numbersToBeProcessed, cache, out);
	}
	
	/**
	 * Calculeaza CMMDC dintr n1 si n2.
	 */
	private int cmmdc(int n1, int n2) {
		if(n1 == 0 || n2 == 0)
			return n1 + n2;
		return cmmdc(n2, n1 % n2);
	}

	/**
	 * Pentru inceput calculeaza momentul de timp. Dupa aceea, ruleaza
	 * fiecare proces de cate ori este nevoie pentru a-i satisface cota.
	 * Dupa ce ruleaza si ultimul proces, procedeul este luat de la capat
	 * cu primul proces. Afisarea si cache-ul sunt la fel cu cele de la RS
	 * si RSS.
	 */
	@Override
	public void choose() {
		int n = processes.length, cnt = 0, calcul, task = 0, timp = 0, div = processes[0].getWeight(), total;
		
		for(int i = 0; i < n; i++) {
			timp += processes[i].getWeight();
			div = cmmdc(div, processes[i].getWeight());
		}
		total = timp; //calculeaza ecuatia din pdf
		timp /= div;
		
	loop:
		while(cnt < numbersToBeProcessed.length) {
			for(int i = 0; i < (processes[task].getWeight() * timp) / total; i++) { //numarul de rulari al fiecarui proces
				
				if(cache != null) {
					calcul = cache.find(processes[task].getType(), numbersToBeProcessed[cnt]);
					if(calcul == Integer.MIN_VALUE) {
						calcul = tasks[task].calcul(numbersToBeProcessed[cnt]);
						cache.add(processes[task].getType(), numbersToBeProcessed[cnt], calcul);
						write.println(numbersToBeProcessed[cnt] + " " + processes[task].getType() + " " + calcul + " " + "Computed");
					}
					else
						write.println(numbersToBeProcessed[cnt] + " " + processes[task].getType() + " " + calcul + " " + "FromCache");
				}
				else {
					calcul = tasks[task].calcul(numbersToBeProcessed[cnt]);
					write.println(numbersToBeProcessed[cnt] + " " + processes[task].getType() + " " + calcul + " " + "Computed");
				}
				
				cnt++;
				
				if(cnt >= numbersToBeProcessed.length)
					break loop;
			}
			task++;
			task %= n; //alege doar unul din procesele existente
			
		}
		write.close();
		
	}

}
