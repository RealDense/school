public class ThreadsDemo {
    public static void main(String[] args) {
        final long INCREMENT = 1_000_000;
        try {
            Thread[] threads = new Thread[Runtime.getRuntime().availableProcessors()];
            long start = 1;
            long end = INCREMENT;

            long timeStart = System.currentTimeMillis();
            for (int thread = 0; thread < Runtime.getRuntime().availableProcessors(); thread++){
                threads[thread] = new Thread(new ComputePrimes(String.format("Thread %d", thread + 1), start, end));
                threads[thread].start();
                start += INCREMENT;
                end += INCREMENT;
            }

//            for (Thread t : threads) {
//                t.join();
//            }
            long timeEnd = System.currentTimeMillis();
            System.out.printf("%d ms\n", timeEnd - timeStart);
        }
        catch (Exception ex) {
            System.out.println("Something bad happened");
        }
    }
}
