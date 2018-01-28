package tema2POO.visitTree;

/**
 * Nodul And.
 * @author Vlad Ilie
 *
 */
public class AndNode implements IVisitNode {
	private IVisitNode left;
	private IVisitNode right;
	
	public AndNode(IVisitNode left, IVisitNode right) {
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
