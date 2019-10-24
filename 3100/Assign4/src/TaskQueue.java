import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedList;
import java.util.Queue;

public class TaskQueue {

    Queue<Integer> TaskQueue =  new LinkedList<>();

    public TaskQueue(int numOfDigits){

        ArrayList<Integer> digis = new ArrayList<Integer>(numOfDigits);
        for(int i = 0; i < numOfDigits; i++){
            digis.add(i, i+1);
        }
        Collections.shuffle(digis);
        //System.out.println(digis.size());
        for(int i = 0; i < numOfDigits; i++){
            this.TaskQueue.add(digis.remove(0));
        }
    }

    public int getSize(){
        return this.TaskQueue.size();
    }

    public synchronized int getTask(){
        if(this.TaskQueue.size() == 0){
            return -1;
        }
        return this.TaskQueue.remove();
    }
}
