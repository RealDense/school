public class WorkerThread implements Runnable{
    public int task;
    public int digit;
    private ResultsTable results;

    public WorkerThread(int task, ResultsTable results){
        this.task = task;
        this.results = results;
    }

    public void run(){
        Bpp bbp = new Bpp();
        this.digit = bbp.run(this.task);
        results.insertDigit(this.task, this.digit);
    }

}
