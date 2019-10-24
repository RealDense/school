public class ComputePrimes implements Runnable {
    private String name;
    private long start;
    private long end;
    private java.util.ArrayList<Long> primes = new java.util.ArrayList<>();

    public ComputePrimes(String name, long start, long end) {
        this.name = name;
        this.start = start;
        this.end = end;
    }

    /**
     * Runnable interface implementation
     */
    public void run() {
        long current = start;

        while (current <= end) {
            if (isPrime(current)) {
                primes.add(current);
            }
            current++;
        }

        reportPrimes();
    }

    /**
     * Report our prime number finding results
     */
    private void reportPrimes() {
        System.out.printf("%s found %d primes\n", this.name, this.primes.size());
//        for (long prime : this.primes) {
//            System.out.printf("%s: %,d is prime\n", this.name, prime);
//        }
    }

    /**
     * Reference: https://www.quora.com/Is-every-prime-number-other-than-2-and-3-of-the-form-6k%C2%B11-Is-this-a-proven-result-What-are-other-resources-about-it
     */
    private boolean isPrime(long number) {
        if (number == 2 || number == 3) return true;
        if (number % 2 == 0 || number % 3 == 0) return false;

        long i = 5;
        long w = 2;

        while (i * i <= number) {
            if (number % i == 0) {
                return false;
            }
            i += w;
            w = 6 - w;
        }

        return true;
    }
}
