import java.util.LinkedList;
import java.util.Queue;

class SchedulerFCFS extends SchedulerBase implements Scheduler {
    Queue<Process> processes = new LinkedList<>();
    Platform logger;

    public SchedulerFCFS(Platform l){
        this.logger = l;
    }

    //@Override
    public void notifyNewProcess(Process p) {
        //do something
        //System.out.println("here");
        processes.add(p);
    }

    public Process update(Process cpu){
        //System.out.println("process");
        if(cpu == null && processes != null){
            this.contextSwitches ++;
            cpu = processes.peek();
            processes.remove();
            logger.log("Scheduled: " + cpu.getName());
            return cpu;
        }
        else if(cpu.isBurstComplete()){
            logger.log("Process " + cpu.getName() + " burst complete");
            this.contextSwitches ++;
            if(cpu.isExecutionComplete()){
                logger.log("Process " + cpu.getName() + " execution complete");
                if(processes.isEmpty()){
                    return null;
                }
            }else{
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
