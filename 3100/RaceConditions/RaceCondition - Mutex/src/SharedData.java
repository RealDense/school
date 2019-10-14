import java.util.concurrent.Semaphore;

public class SharedData {
    public long value;
    public Semaphore lock = new Semaphore(1);

    public SharedData() {
        this.value = 0;

    }

}
