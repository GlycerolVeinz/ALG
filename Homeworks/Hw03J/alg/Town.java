package alg;

public class Town {
    private final Town parentTown;
    private Town leftTown;
    private Town rightTown;
    private int leftBranchMaxDepth = 0;
    private int rightBranchMaxDepth = 0;
    private int rightSubtreeSize = 0;
    private int leftSubtreeSize = 0;


    public Town(int townID, int townDepth, Town parentTown) {
        this.parentTown = parentTown;
    }

    public void setLeftTown(Town leftTown) {
        this.leftTown = leftTown;
    }
    public void setRightTown(Town rightTown) {
        this.rightTown = rightTown;
    }
    public Town getLeftTown() {
        return leftTown;
    }
    public Town getRightTown() {
        return rightTown;
    }
    public int getLeftBranchMaxDepth() {
        return leftBranchMaxDepth;
    }
    public void setLeftBranchMaxDepth(int leftBranchMaxDepth) {
        this.leftBranchMaxDepth = leftBranchMaxDepth;
    }
    public void setRightBranchMaxDepth(int rightBranchMaxDepth) {
        this.rightBranchMaxDepth = rightBranchMaxDepth;
    }
    public int getRightBranchMaxDepth() {
        return rightBranchMaxDepth;
    }

    public Town getParentTown() {
        return parentTown;
    }

    public int getRightSubtreeSize() {
        return rightSubtreeSize;
    }

    public void setRightSubtreeSize(int rightSubtreeSize) {
        this.rightSubtreeSize = rightSubtreeSize;
    }

    public int getLeftSubtreeSize() {
        return leftSubtreeSize;
    }

    public void setLeftSubtreeSize(int leftSubtreeSize) {
        this.leftSubtreeSize = leftSubtreeSize;
    }
}
