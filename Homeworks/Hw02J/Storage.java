import java.util.ArrayList;
import java.util.List;

import static java.lang.Math.abs;

public class Storage {
    private Integer bestPackageWeight;
    private Integer bestPackageTime;
    private Room mainRoom;
    private List<Room> allRooms;
    private List<Integer> packages;
    private Integer totalWeight;

    public Storage(Room mainRoom){
        this.mainRoom = mainRoom;
        this.allRooms = new ArrayList<>();
        this.allRooms.add(mainRoom);
        this.packages = new ArrayList<>();
        this.bestPackageWeight = Integer.MAX_VALUE;
        this.bestPackageTime = Integer.MAX_VALUE;
        this.totalWeight = 0;
    }


    public void makeConnection(Integer parentId, Integer childId, Integer transportTime){
        Room parent = this.allRooms.get(parentId);
        Room child = new Room(childId, transportTime);
        child.setPrevious(parent);
        child.setTotalTime(parent.getTotalTime() + transportTime);

        if (parent.getLeft() == null){
            parent.setLeft(child);
        } else {
            parent.setRight(child);
        }

        this.allRooms.add(child);
    }

    public Integer calculateWeight(Room parent, Room child){
        int weight = -1;

        if(parent != null && child != null){
            weight = abs(parent.getCurrentWeight() - child.getCurrentWeight());
            this.totalWeight += weight;
        }

        return weight;
    }

    public Integer getBestPackageWeight() {
        return bestPackageWeight;
    }

    public Integer getBestPackageTime() {
        return bestPackageTime;
    }

    public Room getMainRoom() {
        return mainRoom;
    }

    public List<Room> getAllRooms() {
        return allRooms;
    }

    public List<Integer> getPackages() {
        return packages;
    }

    public Integer getTotalWeight() {
        return totalWeight;
    }

    public void setBestPackageWeight(Integer bestPackageWeight) {
        this.bestPackageWeight = bestPackageWeight;
    }

    public void setBestPackageTime(Integer bestPackageTime) {
        this.bestPackageTime = bestPackageTime;
    }

    public void setMainRoom(Room mainRoom) {
        this.mainRoom = mainRoom;
    }

    public void setAllRooms(List<Room> allRooms) {
        this.allRooms = allRooms;
    }

    public void setPackages(List<Integer> packages) {
        this.packages = packages;
    }

    public void setTotalWeight(Integer totalWeight) {
        this.totalWeight = totalWeight;
    }
}
