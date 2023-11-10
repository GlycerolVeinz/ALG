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
        child.isViable = false;
        child.setPrevious(parent);
        child.setTotalTime(parent.getTotalTime() + transportTime);

        if (parent.getLeft() == null){
            parent.setLeft(child);
        } else {
            parent.setRight(child);
        }

        this.allRooms.add(child);
    }

    public boolean checkVariant(){
        return allRooms.get(0).getCurrentWeight() == 9
                && allRooms.get(1).getCurrentWeight() == 8
                && allRooms.get(2).getCurrentWeight() == 33
                && allRooms.get(3).getCurrentWeight() == 6
                && allRooms.get(4).getCurrentWeight() == 7
                && allRooms.get(5).getCurrentWeight() == 33;
    }

    public Integer calculateWeight(Room parent, Room child){
        return abs(parent.getCurrentWeight() - child.getCurrentWeight());
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
