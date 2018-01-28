package tema2POO.visitTree;

/**
 * Nodul Or.
 * @author Vlad Ilie
 *
 */
public class OrNode implements IVisitNode {
	private IVisitNode left;
	private IVisitNode right;
	
	public OrNode(IVisitNode left, IVisitNode right) {
		this.left = left;
		this.right = right;
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
	 * @return fiul stang.
	 */
	public IVisitNode getLeft() {
		return left;
	}

	/**
	 * 
	 * @return fiul drept.
	 */
	public IVisitNode getRight() {
		return right;
	}

}
