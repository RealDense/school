import java.util.LinkedList;
import java.util.Queue;

class SchedulerRR extends SchedulerBase implements Scheduler {
    Queue<Process> processes = new LinkedList<>();
    Platform logger;
    int quantum;

    public SchedulerRR(Platform l, int quantum){
        this.logger = l;
        this.quantum = quantum;
    }

    //@Override
    public void notifyNewProcess(Process p) {
        //add all processes to list in order received
        processes.add(p);
    }

    public Process update(Process cpu){
        //if no process is running and there is a process available schedule that process
        if(cpu == null && processes != null){
            //starting a process, add context switch
            this.contextSwitches ++;
            cpu = processes.peek();
            processes.remove();
            logger.log("Scheduled: " + cpu.getName());
            return cpu;
        }else if(cpu.isExecutionComplete()){
            //if execution is done, log it
            logger.log("Process " + cpu.getName() + " execution complete");
            this.contextSwitches ++;
            //if there are no more processes return null
            if(processes.isEmpty()){
                return null;
            }
            //schedule next process in line, increment context switch, log it
            cpu = processes.peek();
            this.contextSwitches ++;
            logger.log("Scheduled: " + cpu.getName());
            processes.remove();
            return cpu;

        }
        //If elapsed burst is greater than quantum, log it, schedule next process
        //if multiple of quantum is for the last process.
        else if(cpu.getElapsedBurst() >= this.quantum && cpu.getElapsedBurst()%this.quantum == 0){
            logger.log("Time quantum complete for " + cpu.getName());

            this.contextSwitches ++;
            if(cpu.isExecutionComplete()){
                logger.log("Process " + cpu.getName() + " execution complete");
                //if there are no more processes return null
                if(processes.isEmpty()){
                    return null;
                }
            }else{
                //add process to the end of the queue
                processes.add(cpu);
            }
            cpu = processes.peek();
            this.contextSwitches ++;
            logger.log("Scheduled: " + cpu.getName());
            processes.remove();
            return cpu;
        }


        return cpu;
    }
}
