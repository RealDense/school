import java.io.File;
import java.lang.Process;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;
import java.lang.*;
import java.util.concurrent.TimeUnit;
import java.util.regex.Matcher;
import java.util.regex.Pattern;


public class Assign3{

    List<String[]> hst = new ArrayList<>();
    File folder = new File(System.getProperty("user.dir"));
    long totalTime = 0;
    boolean running = true;

    public void addToHist(String[] newCmd){
        this.hst.add(newCmd);
    }

    public void printHist(){
        System.out.println("-- Command History --");
        for(int i = 0; i < this.hst.size(); i++){
            System.out.printf("%d : ", i+1);
            for(int j = 0; j < this.hst.get(i).length; j++){
                System.out.printf("%s ", this.hst.get(i)[j]);
            }
            System.out.print("\n");
            //System.out.printf("%d : %s\n", i+1, Arrays.toString(hst.get(i)));
            //System.out.println("here");
        }
    }

    public String[] callHist(int i){
        return this.hst.get(i-1);
    }

    public void listFile(){
        for (final File fileEntry : this.folder.listFiles()){
            System.out.printf(" %s%s%s%s",
                    fileEntry.isDirectory() ? 'd' : '-',
                    fileEntry.canRead() ? 'r' : '-',
                    fileEntry.canWrite() ? 'w' : '-',
                    fileEntry.canExecute() ? 'x' : '-');
            System.out.printf(" %10s", fileEntry.length());
            System.out.printf(" %tb %<te, %<tY %<tH:%<tM ", fileEntry.lastModified());

            System.out.println(fileEntry.getName());
        }

    }

    static File changeDirectory(File location, String destination){
        File newLocation = new File(location, destination);
        if (destination.equals("..")) {
           return location.getParentFile();
        } else if(newLocation.isDirectory()){
            return newLocation;
        }
        else{
            System.out.println("Not a valid directory");
        }
        return location;
    }

    public void runCmd(String[] cmd){
        ProcessBuilder pb = new ProcessBuilder(cmd);
        pb.redirectInput(ProcessBuilder.Redirect.INHERIT);
        pb.redirectOutput(ProcessBuilder.Redirect.INHERIT);
        pb.directory(this.folder);
        long start = System.currentTimeMillis();
        long end = System.currentTimeMillis();

        try{
            //time
            start = System.currentTimeMillis();
            Process p = pb.start();

            if(!cmd[cmd.length - 1].equals("&")){
                p.waitFor();
            }

            //time
            end = System.currentTimeMillis();


        }catch(Exception ex){
            System.out.printf("Invalid command: ");
            for(int j = 0; j < cmd.length; j++){
                System.out.printf("%s ", cmd[j]);
            }
            System.out.printf("\n");
        }
        this.totalTime += (end - start);
    }

    public void runMultCmd(String[] cmd) {

        int pipe = 0;

        for(int i = 0; i < cmd.length; i++){
            if(cmd[i].equals("|")){
                pipe = i;
                break;
            }
        }


        List<String> cmdList1 = new ArrayList<>();
        List<String> cmdList2 = new ArrayList<>();


        for(int i = 0; i < pipe; i ++){
            cmdList1.add(cmd[i]);
        }
        for(int i = pipe +1; i < cmd.length; i ++){
            cmdList2.add(cmd[i]);
        }
        String[] cmd1 = new String[cmdList1.size()];
        String[] cmd2 = new String[cmdList2.size()];
        cmd1 = cmdList1.toArray(cmd1);
        cmd2 = cmdList2.toArray(cmd2);

        ProcessBuilder pb1 = new ProcessBuilder(cmd1);
        ProcessBuilder pb2 = new ProcessBuilder(cmd2);
        pb1.redirectInput(ProcessBuilder.Redirect.INHERIT);
        pb2.redirectOutput(ProcessBuilder.Redirect.INHERIT);
        pb1.directory(this.folder);
        pb2.directory(this.folder);

        long start = System.currentTimeMillis();
        long end = System.currentTimeMillis();

        try {
            //time
            start = System.currentTimeMillis();
            Process p1 = pb1.start();
            Process p2 = pb2.start();

            java.io.InputStream in = p1.getInputStream();
            java.io.OutputStream out = p2.getOutputStream();

            int c;
            while ((c = in.read()) != -1) {
                out.write(c);
            }
            out.flush();
            out.close();

            p1.waitFor();
            p2.waitFor();

            //time
            end = System.currentTimeMillis();

        } catch (Exception exce) {
            System.out.printf("Invalid command: ");
            for (int j = 0; j < cmd1.length; j++) {
                System.out.printf("%s ", cmd1[j]);
            }
            System.out.printf("\n");
        }
        this.totalTime  += (end - start);
    }

   public void tryCommand(String[] s){
       List<String> forPipe = Arrays.asList(s);
       try{
       if(s[0].equals("list")){
           listFile();
       }else if(s[0].equals("history")){
           printHist();
       }else if(s[0].equals("cd")){
           if(s.length == 1){
               //System.out.println("made it");
               this.folder = new File(System.getProperty("user.home"));
           }else {
               this.folder = changeDirectory(this.folder, s[1]);
           }
       }else if(s[0].equals("ptime")){
           System.out.printf("Total time spent in child processes: %.4f seconds\n", (float) (this.totalTime/1000.0));
       }
       //System.out.println("did I make it?");
       else if(s[0].equals("exit")) {
           this.running = false;
       }else if(s[0].equals("^")){
           tryCommand(callHist(Integer.parseInt(s[1])));
       }else if(forPipe.contains("|")){
           //time
           //stuf
           //System.out.println("made it");
           runMultCmd(s);
           //time

       }else{
           //time
           //stuff
           runCmd(s);
           //time
       }
       }catch(Exception ex){

           System.out.printf("Invalid command: ");
           for (int j = 0; j < s.length; j++) {
               System.out.printf("%s ", s[j]);
           }
           System.out.printf("\n");
       }

   }

    /**
     * Split the user command by spaces, but preserving them when inside double-quotes.
     * Code Adapted from: https://stackoverflow.com/questions/366202/regex-for-splitting-a-string-using-space-when-not-surrounded-by-single-or-double
     */
    public static String[] splitCommand(String command) {
        java.util.List<String> matchList = new java.util.ArrayList<>();

        Pattern regex = Pattern.compile("[^\\s\"']+|\"([^\"]*)\"|'([^']*)'");
        Matcher regexMatcher = regex.matcher(command);
        while (regexMatcher.find()) {
            if (regexMatcher.group(1) != null) {
                // Add double-quoted string without the quotes
                matchList.add(regexMatcher.group(1));
            } else if (regexMatcher.group(2) != null) {
                // Add single-quoted string without the quotes
                matchList.add(regexMatcher.group(2));
            } else {
                // Add unquoted word
                matchList.add(regexMatcher.group());
            }
        }

        return matchList.toArray(new String[matchList.size()]);
    }

   public void run(){
       //List<String[]> hst = new ArrayList<>();
       //File folder = new File(System.getProperty("user.dir"));
       //long totalTime = 0;
       //boolean running = true;
       Scanner cmd = new Scanner(System.in);
       String str;
       while (this.running) {
           //final File folder = new File(System.getProperty("user.dir"));
           System.out.print("[");
           System.out.print(this.folder.getPath());
           System.out.print("]: ");
           str = cmd.nextLine();
           //String[] s =  str.split(" ");
           String[] s = splitCommand(str);
           addToHist(s);
           //System.out.printf("%8s\n", s);
           tryCommand(s);
       }


   }

    public static void main(String[] args) {
        Assign3 program = new Assign3();
        program.run();
    }


}