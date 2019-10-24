import java.util.*;


public class TaskLRU implements Runnable{
    public int[] sequence;
    public int maxMemoryFrames;
    public int maxPageReference;
    public int[] pageFaults;

    class LRU{
        int time;
        int task;

        LRU(int task, int time){
            this.task = task;
            this.time = time;
        }

    }

    class CompareLRU implements Comparator<LRU>{
        public int compare(LRU lru1, LRU lru2){
            if(lru1.time < lru2.time){
                return -1;
            }
            else if(lru1.time > lru2.time){
                return 1;
            }

            return 0;
        }


    }

    public TaskLRU(int[] sequence, int maxMemoryFrames, int maxPageReference, int[] pageFaults){
        this.sequence = sequence;
        this.maxMemoryFrames = maxMemoryFrames;
        this.maxPageReference = maxPageReference;
        this.pageFaults = pageFaults;
    }

    public void run(){
        //int mru;
        int pf = 0;
        //int[] frames = new int[maxMemoryFrames];
        if(maxMemoryFrames == 0){
            pageFaults[0] = 0;
            return;
        }
        Hashtable<Integer, LRU> hash = new Hashtable<>();
        Boolean[] pages = new Boolean[maxPageReference];
        Arrays.fill(pages, Boolean.FALSE);
        int framesFilled = 0;
        PriorityQueue<LRU> pq = new PriorityQueue<>(1, new CompareLRU());
        //LinkedHashMap<Integer, Integer> hash = new LinkedHashMap<>();

        for(int i = 0; i < sequence.length; i++){
            int current = sequence[i];
            if(pages[current]){
                //update pq

                //remove current from pq
                //int time = hash.get(current);
                LRU old = hash.get(current);
                pq.remove(old);
                LRU temp = new LRU(current, i);
                hash.remove(current);
                hash.put(current, temp);
                //pq.add(new LRU(current, i));
                pq.add(temp);
                //LRU old = new LRU(current, time);
                //add current with current frame count
                //hash.put(current, i);

            }else if(framesFilled < maxMemoryFrames){
                //put current in pq
                //if(pq.size()>maxMemoryFrames){
                //    System.out.printf("%d     %d\n", pq.size(), maxMemoryFrames);
                //}
                //hash.remove(current);
                LRU temp = new LRU(current, i);
                pq.add(temp);
                hash.put(current, temp);
                //udate pages to say current is true
                pages[current] = Boolean.TRUE;
                framesFilled ++;
                //iterate pagefault
                pf++;
            }else{
                //remove lru from pq
                //try {
                //System.out.printf("hask table size is %d\n", pq.size());
                //LRU leastTask = pq.peek();
                //System.out.printf("hask table size is %d\n", hash.size());
                LRU old = pq.poll();
                pages[old.task] = Boolean.FALSE;


                //replace lru with current in pq
                LRU temp = new LRU(current, i);
                pq.add(temp);
                pages[current] = Boolean.TRUE;
                hash.remove(old.task);
                hash.put(current, temp);

                //place current in pq
                //pq.add(new LRU(current, i));

                //interate lru
                pf++;
                //}
                //catch (Exception ex){
                 //   System.out.printf("Exception thrown\n");
                //}
            }

        }
        pageFaults[maxMemoryFrames] = pf;
        return;
    }
}
