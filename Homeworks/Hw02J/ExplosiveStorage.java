import java.util.ArrayList;
import java.util.Scanner;

public class ExplosiveStorage {
    public static void main(String[] args) {
        Storage storage = readInput();
        recursivePlace(storage, 0, 0);
        System.out.println(storage.getBestPackageWeight() + " " + storage.getBestPackageTime());
    }

    public static Storage readInput(){
        int numberOfRooms, numberOfPackages;
        Scanner scan = new Scanner(System.in);

        numberOfRooms = scan.nextInt();
        numberOfPackages = scan.nextInt();

        ArrayList<Integer> rooms = readPackages(scan, numberOfPackages);

        return readRooms(scan, numberOfRooms, rooms);
    }

    public static ArrayList<Integer> readPackages(Scanner scan, int numberOfPackages){
        ArrayList<Integer> packages = new ArrayList<>();
        int packageWeight;

        for(int i = 0; i < numberOfPackages; i++){
            packageWeight = scan.nextInt();
            packages.add(packageWeight);
        }

        return packages;
    }

    public static Storage readRooms(Scanner scan, int numberOfRooms, ArrayList<Integer> packages){
        Room mainRoom = new Room(0, 0);
        Storage storage = new Storage(mainRoom);

        for(int i = 1; i < numberOfRooms; i++){
            int parentId = scan.nextInt();
            int childId = scan.nextInt();
            int transportTime = scan.nextInt();

            storage.makeConnection(parentId, childId, transportTime);
        }

        storage.setPackages(packages);

        return storage;
    }

    public static void recursivePlace(Storage storage, int currentPackageId, int currentTime){
        if ((currentPackageId + 1) == storage.getPackages().size()){
            Integer totalWeight = 0;
            Integer totalTime = currentTime;

            for (Room currentRoom : storage.getAllRooms()){
                totalWeight += currentRoom.getCurrentWeight();
            }

            if (totalWeight < storage.getBestPackageWeight()){
                storage.setBestPackageWeight(totalWeight);
                storage.setBestPackageTime(totalTime);
            } else if (totalWeight.equals(storage.getBestPackageWeight())){
                if(totalTime < storage.getBestPackageTime()){
                    storage.setBestPackageTime(totalTime);
                }
            }

        } else {
            int currentPackage = storage.getPackages().get(currentPackageId);

            for (Room currentRoom : storage.getAllRooms()){
                if(!currentRoom.isLeaf() || currentRoom.willBlock()) continue;

                currentRoom.placePackage(currentPackage);
                currentTime += currentRoom.getTotalTime();

                if (storage.calculateWeight(currentRoom.getPrevious(), currentRoom) == -1){
                    throw new IllegalArgumentException("You are stupid to check null");
                }

                recursivePlace(storage, ++currentPackageId, currentTime);

                currentRoom.removePackage(currentPackage);
                --currentPackageId;
            }
        }
    }
}
