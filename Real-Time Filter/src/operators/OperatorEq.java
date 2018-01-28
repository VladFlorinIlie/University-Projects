package tema2POO.operators;

/**
 * Operatorul Eq
 * @author Vlad Ilie
 *
 */
public class OperatorEq implements IOperator {
	private String str, nameOrValue, strFeed[]; //[0] = numele; [1] = valoarea din feed
	
	OperatorEq(String str, String[] strFeed, String nameOrValue) {
		this.str = str;
		this.strFeed = strFeed;
		this.nameOrValue = nameOrValue;
	}
	
	/**
	 * Verifica daca trebuie sa evalueze un nume
	 * sau o valoare, apoi evalueaza.
	 */
	@Override
	public boolean evaluate() {
		if(nameOrValue.equals("value"))
			return (Double.parseDouble(strFeed[1]) == Double.parseDouble(str));
		return str.equals(strFeed[0]);
	}
	
}
