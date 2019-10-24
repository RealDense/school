public class Consumer implements Runnable {
    private SharedData data;

    public Consumer(SharedData data) {
        this.data = data;
    }

    @Override
    public void run() {

        while (true) {
            this.data.decrement();
        }
    }

}
