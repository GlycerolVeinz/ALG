package alg;

import java.util.ArrayList;

public class TrainSystemBuilder {
//    inorder = left root right
//    preorder = root left right

    public void buildTownSystem(TrainSystem trainSystem) {
        ArrayList<Integer> townsPreorder = trainSystem.getTownsPreorder();
        ArrayList<Integer> townsInorder = trainSystem.getTownsInorder();
        Town rootTown = buildTreeHelper(townsPreorder, townsInorder, null, 0);
        trainSystem.setRootTown(rootTown);
    }

    private Town buildTreeHelper(ArrayList<Integer> preorder, ArrayList<Integer> inorder, Town parentTown, int depth) {
//        no Town escape sequence
        if (preorder.isEmpty() || inorder.isEmpty()) {
            return null;
        }

//      take root from preorder
        int rootID = preorder.get(0);
        Town currentTown = new Town(rootID, depth, parentTown);

//        return if last Town
        if (preorder.size() == 1) {
            return currentTown;
        }

//      split inorder into left and right
        ArrayList<Integer> leftInorder = getLeftInorder(inorder, rootID);
        ArrayList<Integer> rightInorder = getRightInorder(inorder, rootID);
//      split preorder into left and right
        ArrayList<Integer> leftPreorder = new ArrayList<Integer>(preorder.subList(1, leftInorder.size() + 1));
        ArrayList<Integer> rightPreorder = new ArrayList<Integer>(preorder.subList(leftInorder.size() + 1, preorder.size()));

        currentTown.setLeftSubtreeSize(leftInorder.size());
        currentTown.setRightSubtreeSize(rightInorder.size());

//      build left and right
        Town leftTown = buildTreeHelper(leftPreorder, leftInorder, currentTown, depth + 1);
        Town rightTown = buildTreeHelper(rightPreorder, rightInorder, currentTown, depth + 1);

//      set left and right
        currentTown.setLeftTown(leftTown);
        currentTown.setRightTown(rightTown);

//        calculate left and right branch depth
        calculateLeftBranchDepth(currentTown, leftTown);
        calculateRightBranchDepth(currentTown, rightTown);

        return currentTown;
    }

    void calculateLeftBranchDepth(Town currentTown, Town childTown){
        if (childTown == null) {
            currentTown.setLeftBranchMaxDepth(0);
        } else {
            int maxDepth = Math.max(childTown.getLeftBranchMaxDepth(), childTown.getRightBranchMaxDepth());
            currentTown.setLeftBranchMaxDepth(maxDepth + 1);
        }
    }

    void calculateRightBranchDepth(Town currentTown, Town childTown){
        if (childTown == null) {
            currentTown.setRightBranchMaxDepth(0);
        } else {
            int maxDepth = Math.max(childTown.getLeftBranchMaxDepth(), childTown.getRightBranchMaxDepth());
            currentTown.setRightBranchMaxDepth(maxDepth + 1);
        }
    }

    private ArrayList<Integer> getLeftInorder(ArrayList<Integer> inorder, int rootID) {
        ArrayList<Integer> left = new ArrayList<Integer>();
        for (int value : inorder){
            if (value == rootID) {
                break;
            }
            left.add(value);
        };
        return left;
    }

    private ArrayList<Integer> getRightInorder(ArrayList<Integer> inorder, int rootID) {
        ArrayList<Integer> right = new ArrayList<Integer>();
        boolean start = false;
        for (int value : inorder){
            if (value == rootID) {
                start = true;
                continue;
            }
            if (start) {
                right.add(value);
            }
        };
        return right;
    }
}
