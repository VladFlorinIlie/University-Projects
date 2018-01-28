package tema2POO.visitTree;

/**
 * Interfata implementata de visitor.
 * Contine metode pentru cele 3 tipuri
 * de noduri.
 * @author Vlad Ilie
 *
 */
public interface INodeVisitor {
	public boolean visit(AndNode node);
	public boolean visit(OrNode node);
	public boolean visit(OperandNode node);
}
