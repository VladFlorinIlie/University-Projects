package tema2POO.visitTree;

/**
 * Visitor-ul ce va parcurge arborele in care se afla filtrul.
 * @author Vlad Ilie
 *
 */
public class TreeVisitor implements INodeVisitor {

	/**
	 * Viziteaza un AndNode si aplica SI intre fii.
	 */
	@Override
	public boolean visit(AndNode node) {
		return node.getLeft().accept(this) && node.getRight().accept(this);
	}

	/**
	 * Viziteaza un OrNode si aplica SAU intre fii.
	 */
	@Override
	public boolean visit(OrNode node) {
		return node.getLeft().accept(this) || node.getRight().accept(this);
	}

	/**
	 * Viziteaza un OperandNode si apeleaza functia de evaluare a
	 * operatorului din acest nod.
	 */
	@Override
	public boolean visit(OperandNode node) {
		return node.getOp().evaluate();
	}

}
