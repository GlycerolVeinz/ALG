package alg;

import java.util.ArrayList;

public class TrainSystem {
    private final ArrayList<Integer> townsPreorder;
    private final ArrayList<Integer> townsInorder;
    private Town rootTown;

    private int result = 0;

    public final TrainSystemBuilder trainSystemBuilder = new TrainSystemBuilder();

    public TrainSystem(ArrayList<Integer> townsPreorder, ArrayList<Integer> townsInorder) {
        this.townsPreorder = townsPreorder;
        this.townsInorder = townsInorder;
        int numOfTowns = townsPreorder.size();
        this.rootTown = null;
    }

    public ArrayList<Integer> getTownsPreorder() {
        return townsPreorder;
    }
    public Town getRootTown() {
        return rootTown;
    }
    public ArrayList<Integer> getTownsInorder() {
        return townsInorder;
    }

    public void setRootTown(Town town) {
        this.rootTown = town;
    }
    public void setResult(int result) {
        this.result = result;
    }
    public int getResult() {
        return result;
    }
}
