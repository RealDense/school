import java.util.LinkedList;
import java.util.Queue;

class SchedulerSJF extends SchedulerBase implements Scheduler {
    LinkedList<Process> processes = new LinkedList<>();
    Platform logger;

    public SchedulerSJF(Platform l){
        this.logger = l;
    }

    public void notifyNewProcess(Process p) {
        //if queue is empty add process
        boolean inserted = false;
        if(processes.size() == 0) {
            processes.add(p);
        }else {
            //Insert processes by Shortest time
            for (int i = 0; i < processes.size(); i++) {
                if (processes.get(i).getTotalTime() > p.getTotalTime()) {
                    processes.add(i, p);
                    inserted = true;
                    break;
                }
            }
            if(!inserted){
                processes.addLast(p);
            }

        }
    }

    public Process update(Process cpu){
        //If no process is running and there is a process available, run a process
        if(cpu == null && processes != null){
            //start a process, add a context switch
            this.contextSwitches ++;
            cpu = processes.peek();
            processes.remove();
            logger.log("Scheduled: " + cpu.getName());
            return cpu;
        }
        else if(cpu.isBurstComplete()){
            //If burst is complete, log it and add a context switch
            logger.log("Process " + cpu.getName() + " burst complete");
            this.contextSwitches ++;
            if(cpu.isExecutionComplete()){
                //If execution is done, log it
                logger.log("Process " + cpu.getName() + " execution complete");
                //If there are no more processes return null
                if(processes.isEmpty()){
                    return null;
                }
            }else{
                //If execution is not complete insert into processes
                processes.add(cpu);
            }
            //Schedule new process and increment into processes
            cpu = processes.peek();
            this.contextSwitches ++;
            logger.log("Scheduled: " + cpu.getName());
            processes.remove();
            return cpu;
        }

        return cpu;
    }
}
