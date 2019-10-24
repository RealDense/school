import java.util.Hashtable;

public class ResultsTable {

    //hash table goes here
    Hashtable<Integer, Integer> ResultsTable = new Hashtable<Integer, Integer>();

    public ResultsTable(){

    }

    public synchronized void insertDigit(int index, int digit){
        this.ResultsTable.put(index, digit);

    }

    public int getSize(){
        return this.ResultsTable.size();
    }

    public void printPI(){
        System.out.printf("\n3.");
        for(int i = 1; i <= this.ResultsTable.size(); i++){
            System.out.printf("%d", this.ResultsTable.get(i));

        }
        System.out.println();
    }

}
