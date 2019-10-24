import java.util.Arrays;
import java.util.Hashtable;
import java.util.LinkedList;
import java.util.Queue;

public class TaskFIFO implements Runnable{
    public int[] sequence;
    public int maxMemoryFrames;
    public int maxPageReference;
    public int[] pageFaults;

    public TaskFIFO(int[] sequence, int maxMemoryFrames, int maxPageReference, int[] pageFaults){
        this.sequence = sequence;
        this.maxMemoryFrames = maxMemoryFrames;
        this.maxPageReference = maxPageReference;
        this.pageFaults = pageFaults;
    }

    public void run(){
        Queue<Integer> fifo = new LinkedList<>();
        int pf = 0;
        if(maxMemoryFrames == 0){
            return;
        }
        Boolean[] pages = new Boolean[maxPageReference];
        Arrays.fill(pages, Boolean.FALSE);
        int framesFilled = 0;

        for(int i = 0; i < sequence.length; i++){
            int current = sequence[i];
            if(pages[current]){
                //Do nothing
            }else if(framesFilled < maxMemoryFrames){
                pages[current] = Boolean.TRUE;
                fifo.add(current);
                framesFilled ++;
                pf++;
            }else{
                int temp = fifo.remove();
                pages[temp] = Boolean.FALSE;
                pages[current] = Boolean.TRUE;
                fifo.add(current);
                pf++;
            }

        }
        pageFaults[maxMemoryFrames] = pf;
        return;



    }
}
