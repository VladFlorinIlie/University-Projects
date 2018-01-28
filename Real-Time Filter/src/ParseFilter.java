package tema2POO;

import java.util.Stack;

import tema2POO.operators.OperatorsFactory;
import tema2POO.visitTree.IVisitNode;
import tema2POO.visitTree.NodeFactory;

/**
 * Parcurge filtrul si creaza un arbore binar
 * din acesta.
 * @author Vlad Ilie
 *
 */
public class ParseFilter {
	private String filter; //filtrul observatorului
	private String[] feed; //numele si valoarea feed-ului curent
	private OperatorsFactory op;
	private NodeFactory node;

	ParseFilter(String filter, String[] feed) {
		this.filter = filter;
		this.feed = feed;
		op = OperatorsFactory.getInstance();
		node = NodeFactory.getInstance();
	}

	/**
	 * Foloseste algoritmul Shunting-yard pentru a
	 * parcurge filtrul. La fiecare pop din stiva
	 * de operatori (ce contine paranteze, AndNode,
	 * OrNode) scoate si doua noduri OperandNode/
	 * AndNode/OrNode din stiva tree si le leaga
	 * de operatorul respectiv.
	 * @return radacina arborelui.
	 */
	public IVisitNode shuntingYard() {
		char caracter, charFromStack;
		String[] opFnc = new String[3];
		Stack<Character> operator = new Stack<Character>();
		Stack<IVisitNode> tree = new Stack<IVisitNode>();

		for (int i = 0; i < filter.length(); i++) {
			caracter = filter.charAt(i);

			if (caracter >= 'a' && caracter <= 'z') {
				operator.pop();
				opFnc = filter.substring(i).split("\\s+");

				tree.push(node.createNode('o', null, null, op.createOp(opFnc[0], opFnc[2], feed, opFnc[1]))); // dau referinta feed catre
																								// vectorul de feed
				i += opFnc[0].length() + opFnc[1].length() + opFnc[2].length() + 3;  //trece peste aceasta bucata din filtru
			}
			
			else if (caracter == '&' || caracter == '|') {
				while (!operator.empty()) {
					if (operator.peek() != '(' && operator.peek() < caracter) {
						charFromStack = operator.pop(); //scoate operatorul de pe stiva
						IVisitNode right = tree.pop(); //scoate ultimile doua noduri
						IVisitNode left = tree.pop();
						tree.push(node.createNode(charFromStack, left, right, null)); //creaza un nou nod
																					//ce are ca fii cele doua noduri de mai sus
					} else
						break;
				}
				operator.push(caracter);
				i++; // trece peste al doilea caracter
			}

			else if (caracter == '(')
				operator.push(caracter);

			else if (caracter == ')') {
				while (operator.peek() != '(') {
					charFromStack = operator.pop();
					IVisitNode right = tree.pop();
					IVisitNode left = tree.pop();
					tree.push(node.createNode(charFromStack, left, right, null));
				}
				operator.pop();
			}
		}

		while (!operator.empty()) {
			charFromStack = operator.pop();
			IVisitNode right = tree.pop();
			IVisitNode left = tree.pop();
			tree.push(node.createNode(charFromStack, left, right, null));
		}

		IVisitNode root = tree.pop();
		return root;
	}
}
