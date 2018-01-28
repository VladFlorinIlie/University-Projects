package tema2POO.operators;

/**
 * Fabrica de operatori.
 * @author Vlad Ilie
 *
 */
public class OperatorsFactory {
	private static OperatorsFactory factoryInstance;
	
	private OperatorsFactory() {}
	
	/**
	 * Instantiaza o fabrica de operatori.
	 * @return fabrica.
	 */
	public static OperatorsFactory getInstance() {
		if(factoryInstance == null)
			factoryInstance = new OperatorsFactory();
		
		return factoryInstance;
	}
	
	/**
	 * Creaza un operator.
	 * @param type tipul operatorului.
	 * @param str valoarea sau numele din filtru (depinde ce se verifica).
	 * @param strFeed vectorul de contine numele si valoarea feed-ului curent.
	 * @param nameOrValue verifica daca este nume sau valoare.
	 * @return operatorul creat.
	 */
	public IOperator createOp(String type, String str, String[] strFeed, String nameOrValue) {
		switch(type) {
		case "gt":	return new OperatorGt(str, strFeed);
		case "ge":	return new OperatorGe(str, strFeed);
		case "lt":	return new OperatorLt(str, strFeed);
		case "le":	return new OperatorLe(str, strFeed);
		case "eq":	return new OperatorEq(str, strFeed, nameOrValue);
		case "ne":	return new OperatorNe(str, strFeed, nameOrValue);
		default:	return null;
		}
	}
}
