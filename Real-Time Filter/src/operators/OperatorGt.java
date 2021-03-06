package tema2POO.operators;

/**
 * Operatorul Gt.
 * @author Vlad Ilie
 *
 */
public class OperatorGt implements IOperator {
	private String str, strFeed[];
	
	OperatorGt(String str, String[] strFeed) {
		this.str = str;
		this.strFeed = strFeed;
	}
	
	/**
	 * Face verificarea intre valoarea feed-ului curent
	 * (strFeed[1]) si valoarea din filtru.
	 */
	@Override
	public boolean evaluate() {
		return Double.parseDouble(strFeed[1]) > Double.parseDouble(str);
	}
}
