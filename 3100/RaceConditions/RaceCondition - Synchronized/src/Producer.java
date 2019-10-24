public class Producer implements Runnable {
    private SharedData data;

    public Producer(SharedData data) {
        this.data = data;
    }

    @Override
    public void run() {

        while (true) {
            this.data.increment();
        }
    }

}
