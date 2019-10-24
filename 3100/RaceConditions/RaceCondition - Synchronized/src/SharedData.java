public class SharedData {
    public long value;

    public SharedData() {
        this.value = 0;
    }

    public synchronized void increment() {
        long before = this.value;
        this.value++;
        long after = this.value;

        if (before != (after - 1)) {
            System.out.println("Increment - Problem detected!!");
            System.out.printf("Expected : %d\n", before + 1);
            System.out.printf("Got      : %d\n", after);
        }
    }

    public synchronized  void decrement() {
        long before = this.value;
        this.value--;
        long after = this.value;

        if (after != (before - 1)) {
            System.out.println("Decrement - Problem detected!!");
            System.out.printf("Expected : %d\n", before + 1);
            System.out.printf("Got      : %d\n", after);
        }
    }

}
