import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.*;
import java.util.concurrent.Executor;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

import static java.lang.Runtime.*;

public class Assign4 {


    public static void main( String[] args){
        int cpus = Runtime.getRuntime().availableProcessors();
        int numOfDigits = 1000;
        long start, end;

        TaskQueue taskQueue = new TaskQueue(numOfDigits);
        ResultsTable resultsTable = new ResultsTable();

        Executor threadPool = Executors.newFixedThreadPool(cpus);
        start = System.currentTimeMillis();

        for(int i = 0; i < numOfDigits; i++){
            Runnable worker = new WorkerThread(taskQueue.getTask(), resultsTable);
            threadPool.execute(worker);
            //put data in results table
        }
        System.out.println();
        int old = -1;
        while(resultsTable.getSize() < numOfDigits) {
            if ((resultsTable.getSize() % 10) == 0 && resultsTable.getSize() != old) {
                old = resultsTable.getSize();
                System.out.printf(".");
            }
        }
        ((ExecutorService) threadPool).shutdown();
//        while (!threadPool.isTerminated())
//            ;   // Busy wait
        try {
            ((ExecutorService) threadPool).awaitTermination(Long.MAX_VALUE, TimeUnit.DAYS);
        }
        catch (Exception ex) {
            System.out.println("Error in waiting for shutdown");
        }


        resultsTable.printPI();

        end = System.currentTimeMillis();

        System.out.printf("The total time to calculate PI was %d milliseconds\n\n", end-start);


    }
}
