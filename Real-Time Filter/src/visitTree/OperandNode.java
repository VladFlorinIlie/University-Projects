package tema2POO.visitTree;

/**
 * Nodul Operand.
 */
import tema2POO.operators.IOperator;

public class OperandNode implements IVisitNode {
	private IOperator op;
	
	public OperandNode(IOperator op) {
		this.op = op;
	}

	/**
	 * Accepta obiectul de tip visitor.
	 */
	@Override
	public boolean accept(INodeVisitor visitor) {
		return visitor.visit(this);
	}

	/**
	 * 
	 * @return intoarce operatorul pentru a fi evaluat.
	 */
	public IOperator getOp() {
		return op;
	}

}
