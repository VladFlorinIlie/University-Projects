package tema2POO.visitTree;

import tema2POO.operators.IOperator;

/**
 * Fabrica de noduri.
 * @author Vlad Ilie
 *
 */
public class NodeFactory {
	private static NodeFactory factoryInstance;
	
	private NodeFactory() {}
	
	/**
	 * Instantiaza o fabrica de noduri.
	 * @return fabrica.
	 */
	public static NodeFactory getInstance() {
		if(factoryInstance == null)
			factoryInstance = new NodeFactory();
		
		return factoryInstance;
	}
	
	/**
	 * Creaza un nod.
	 * @param type tipul nodului.
	 * @param left fiul stanga (daca exista).
	 * @param right fiul drept (daca exista).
	 * @param operator referinta catre un opetator (daca exista).
	 * @return nodul creat.
	 */
	public IVisitNode createNode(char type, IVisitNode left, IVisitNode right, IOperator operator) {
		switch(type) {
		case '&':	return new AndNode(left, right);
		case '|':	return new OrNode(left, right);
		default:	return new OperandNode(operator);
		}
	}
}
