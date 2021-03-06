package tema2POO.operators;

/**
 * Operatorul Ge
 * @author Vlad Ilie
 *
 */
public class OperatorGe implements IOperator {
	private String str, strFeed[];
	
	OperatorGe(String str, String[] strFeed) {
		this.str = str;
		this.strFeed = strFeed;
	}
	
	/**
	 * Face verificarea intre valoarea feed-ului curent
	 * (strFeed[1]) si valoarea din filtru.
	 */
	@Override
	public boolean evaluate() {
		return Double.parseDouble(strFeed[1]) >= Double.parseDouble(str);
	}
	
}
