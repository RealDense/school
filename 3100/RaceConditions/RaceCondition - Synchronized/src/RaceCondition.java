public class RaceCondition {
    public static void main(String[] args) {
        SharedData shared = new SharedData();

        Producer myProducer = new Producer(shared);
        Consumer myConsumer = new Consumer(shared);


        try {
            Thread t1 = new Thread(myProducer);
            Thread t2 = new Thread(myConsumer);

            t1.start();
            t2.start();

            t1.join();
            t2.join();

        }
        catch (Exception ex) {
            System.out.println("Something bad happened!");
        }
    }
}
