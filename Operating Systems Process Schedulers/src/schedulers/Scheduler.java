package tema1POO.schedulers;

import tema1POO.cache.Cache;
import tema1POO.inputOutput.HomeworkWriter;
import tema1POO.inputOutput.ProcessStructure;
import tema1POO.tasks.CheckPrime;
import tema1POO.tasks.Cube;
import tema1POO.tasks.Factorial;
import tema1POO.tasks.Fibonacci;
import tema1POO.tasks.NextPrime;
import tema1POO.tasks.Sqrt;
import tema1POO.tasks.Square;
import tema1POO.tasks.Tasks;

/**
 * Clasa parinte pentru schedulere.
 * @author Vlad Ilie
 */
public abstract class Scheduler {
    protected ProcessStructure[] processes;
    protected int[] numbersToBeProcessed;
    protected Tasks[] tasks;
    protected Cache cache;
    protected HomeworkWriter write;
    
    /**
     * Creaza un task de tip "type".
     * @param type tipul task-ului.
     * @return returneaza obiectul creat.
     */
    private Tasks newTask(String type) {
    	switch(type) {
    	case "CheckPrime": return new CheckPrime();
    	case "Cube": return new Cube();
    	case "Factorial": return new Factorial();
    	case "Fibonacci": return new Fibonacci();
    	case "NextPrime": return new NextPrime();
    	case "Sqrt": return new Sqrt();
    	case "Square": return new Square();
    	default: return null;
    	}
    }
	
    /**
     * Functia creaza un vector de task-uri si deschide fisierul de output.
     * @param processes vectorul cu procese citit din fisier.
     * @param numbersToBeProcessed vectorul de numere.
     * @param cache cache-ul.
     */
	public Scheduler(ProcessStructure[] processes, int[] numbersToBeProcessed, Cache cache, String out) {
		this.processes = processes;
		this.numbersToBeProcessed = numbersToBeProcessed;
		this.cache = cache;
		tasks = new Tasks[processes.length];
		write = new HomeworkWriter(out);
		for(int i = 0; i < processes.length; i++) //creaza cate un obiect pentru fiecare proces
			tasks[i] = newTask(processes[i].getType());
	}
	
	/**
	 * Functia alege cate un proces pentru fiecare numar si calculeaza rezultatul.
	 * Daca exista si cache, il foloseste si pe acesta pentru stocarea rezultatelor.
	 */
	public abstract void choose();
}
