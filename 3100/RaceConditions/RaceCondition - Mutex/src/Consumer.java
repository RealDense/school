public class Consumer implements Runnable {
    private SharedData data;

    public Consumer(SharedData data) {
        this.data = data;
    }

    @Override
    public void run() {

        try {
            while (true) {
                this.data.lock.acquire();
                long before = this.data.value;
                this.data.value--;
                long after = this.data.value;
                this.data.lock.release();

                if (after != (before - 1)) {
                    System.out.println("Consumer - Problem detected!!");
                    System.out.printf("Expected : %d\n", before + 1);
                    System.out.printf("Got      : %d\n", after);
                }
            }
        }
        catch (Exception ex) {

        }
    }

}
