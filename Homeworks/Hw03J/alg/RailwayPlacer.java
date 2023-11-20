package alg;

public class RailwayPlacer {
    private final TrainSystem trainSystem;

    public RailwayPlacer(TrainSystem trainSystem) {
        this.trainSystem = trainSystem;
    }

    public void placeRailways() {
        Town rootTown = trainSystem.getRootTown();
        placeRailwaysHelper(rootTown, 0);
    }

    private void placeRailwaysHelper(Town currentTown, int railwaySize) {
        if (currentTown == null) {
            if (railwaySize > trainSystem.getResult()) {
                trainSystem.setResult(railwaySize);
            }
        } else {
            boolean leftSubtreeIsBigger = currentTown.getLeftSubtreeSize() > currentTown.getRightSubtreeSize();
            boolean rightSubtreeIsBigger = currentTown.getRightSubtreeSize() > currentTown.getLeftSubtreeSize();

            boolean leftBranchIsLonger = currentTown.getLeftBranchMaxDepth() > currentTown.getRightBranchMaxDepth();
            boolean rightBranchIsLonger = currentTown.getRightBranchMaxDepth() > currentTown.getLeftBranchMaxDepth();

            int railwaySizeGoingLeft = railwaySize + 1 + currentTown.getRightBranchMaxDepth();
            int railwaySizeGoingRight = railwaySize + 1 + currentTown.getLeftBranchMaxDepth();

            if (leftSubtreeIsBigger && leftBranchIsLonger) {
                placeRailwaysHelper(currentTown.getLeftTown(), railwaySizeGoingLeft);
            } else if (rightSubtreeIsBigger && rightBranchIsLonger) {
                placeRailwaysHelper(currentTown.getRightTown(), railwaySizeGoingRight);
            } else {
                placeRailwaysHelper(currentTown.getLeftTown(), railwaySizeGoingLeft);
                placeRailwaysHelper(currentTown.getRightTown(), railwaySizeGoingRight);
            }
        }
    }
}
