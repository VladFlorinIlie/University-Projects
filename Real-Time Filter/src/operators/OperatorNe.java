package tema2POO.operators;

/**
 * Operatorul Ne.
 * @author Vlad Ilie
 *
 */
public class OperatorNe implements IOperator {
	private String str, nameOrValue, strFeed[];
	
	OperatorNe(String str, String[] strFeed, String nameOrValue) {
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
			return (Double.parseDouble(strFeed[1]) != Double.parseDouble(str));
		return !str.equals(strFeed[0]);
	}
	
}
