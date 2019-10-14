import java.util.Arrays;
import java.util.Hashtable;

public class TaskMRU implements Runnable{
    public int[] sequence;
    public int maxMemoryFrames;
    public int maxPageReference;
    public int[] pageFaults;


    public TaskMRU(int[] sequence, int maxMemoryFrames, int maxPageReference, int[] pageFaults){
        this.sequence = sequence;
        this.maxMemoryFrames = maxMemoryFrames;
        this.maxPageReference = maxPageReference;
        this.pageFaults = pageFaults;
    }

    public void run(){
        int mru = -1;
        int pf = 0;
        Hashtable<Integer, Integer> hash = new Hashtable<Integer, Integer>();
        Boolean[] pages = new Boolean[maxPageReference];
        Arrays.fill(pages, Boolean.FALSE);
        int framesFilled = 0;
        if(maxMemoryFrames == 0){
            return;
        }

        for(int i = 0; i < sequence.length; i++){
            int current = sequence[i];
            if(pages[current]){
                mru = current;
            }else if(framesFilled < maxMemoryFrames){
                pages[current] = Boolean.TRUE;
                mru = current;
                framesFilled ++;
                pf++;
            }else{
                pages[mru] = Boolean.FALSE;
                pages[current] = Boolean.TRUE;
                mru = current;
                pf++;
            }

        }
        pageFaults[maxMemoryFrames] = pf;
        return;
    }
}
