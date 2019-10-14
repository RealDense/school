import java.util.concurrent.atomic.AtomicLong;

public class SharedData {
    public AtomicLong value = new AtomicLong();

    public void increment() {
        this.value.incrementAndGet();
    }

    public void increment2() {
        while (true) {
            long before = this.value.get();
            long after = before + 1;
            if (this.value.compareAndSet(before, after)) {
                //System.out.println("DID Increment");
                return;
            }
            //System.out.println("NOT Increment");
        }
    }

    public void decrement() {
        this.value.decrementAndGet();
    }

    public void decrement2() {
        //this.value.decrementAndGet();

        while (true) {
            long before = this.value.get();
            long after = before - 1;
            if (this.value.compareAndSet(before, after)) {
                //System.out.println("DID Decrement");
                return;
            }
            //System.out.println("NOT Decrement");
        }
    }
}
