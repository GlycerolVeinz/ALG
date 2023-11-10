import java.util.ArrayList;
import java.util.List;

public class Room {
    private final Integer Id;
    private Room previous;
    private Room left;
    private Room right;
    private final Integer transportTime;
    private Integer totalTime;
    private Integer currentWeight;
    public boolean isViable;

    Room(Integer Id, Integer transportTime) {
        this.Id = Id;
        this.transportTime = transportTime;
        this.totalTime = 0;
        this.currentWeight = 0;
    }

    public void placePackage(Integer packageWeight) {
        this.currentWeight += packageWeight;
        if (this.left != null){
            this.left.isViable = false;
        }
        if (this.right != null){
            this.right.isViable = false;
        }
    }

    public void removePackage(Integer packageWeight) {
        this.currentWeight -= packageWeight;
        if (this.currentWeight == 0){
            if (this.left != null){
                this.left.isViable = true;
            }
            if (this.right != null){
                this.right.isViable = true;
            }
        }
    }

    boolean isLeaf() {
        return this.left == null && this.right == null;
    }

    boolean willBlock(){
        boolean ret = false;
        if (this.left != null){
            ret = this.left.currentWeight == 0;
        }
        if (this.right != null){
            ret = ret || this.right.currentWeight == 0;
        }
        return ret;
    }

    public void setTotalTime(Integer totalTime) {
        this.totalTime = totalTime;
    }

    public void setPrevious(Room previous) {
        this.previous = previous;
    }

    public void setLeft(Room left) {
        this.left = left;
    }

    public void setRight(Room right) {
        this.right = right;
    }


    public Integer getCurrentWeight() {
        return currentWeight;
    }

    public Integer getId() {
        return Id;
    }

    public Integer getTotalTime() {
        return totalTime;
    }

    public Integer getTransportTime() {
        return transportTime;
    }

    public Room getPrevious() {
        return previous;
    }

    public Room getLeft() {
        return left;
    }

    public Room getRight() {
        return right;
    }
}
