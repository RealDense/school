public class WorkerThread implements Runnable {
    private String name;
    private long runTime;

    public WorkerThread(String name, long runTime) {
        this.name = name;
        this.runTime = runTime;
    }

    /**
     * Runnable interface implementation
     */
    public void run() {
        try {
            System.out.printf("Thread %s running on pool thread %s is starting to run...\n", this.name, Thread.currentThread().getName());
            Thread.sleep(this.runTime);
            System.out.printf("Thread %s is done processing.\n", this.name);
        }
        catch (Exception ex) {
        }
    }
}
