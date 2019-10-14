import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class DemoThreadPool {
    public static void main(String[] args) {

        ExecutorService threadPool = Executors.newFixedThreadPool(4);

        for (int i = 0; i < 10; i++) {
            Runnable worker = new WorkerThread(String.format("%d", i + 1), 100 + i * 100);
            threadPool.execute(worker);
        }

        threadPool.shutdown();
//        while (!threadPool.isTerminated())
//            ;   // Busy wait
        try {
            threadPool.awaitTermination(Long.MAX_VALUE, TimeUnit.DAYS);
        }
        catch (Exception ex) {
            System.out.println("Error in waiting for shutdown");
        }

        System.out.println("ThreadPool has completed processing all threads");
    }
}
