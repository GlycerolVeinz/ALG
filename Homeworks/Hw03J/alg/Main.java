package alg;

import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        TrainSystem trainSystem = readInput();
        trainSystem.trainSystemBuilder.buildTownSystem(trainSystem);

        RailwayPlacer railwayPlacer = new RailwayPlacer(trainSystem);
        railwayPlacer.placeRailways();

        System.out.println(trainSystem.getResult());
    }
    
    public static TrainSystem readInput() {
        Scanner scanner = new Scanner(System.in);
        int numOfNodes = scanner.nextInt();
        ArrayList<Integer> townsPreorder = new ArrayList<Integer>();
        ArrayList<Integer> townsInorder = new ArrayList<Integer>();

        for (int i = 1; i <= numOfNodes; i++) {
            townsPreorder.add(scanner.nextInt());
            townsInorder.add(i);
        }
        scanner.close();


        return new TrainSystem(townsPreorder, townsInorder);
    }
}


