import java.util.LinkedList;

class SchedulerPriority extends SchedulerBase implements Scheduler {
    LinkedList<Process> processes = new LinkedList<>();
    Platform logger;

    public SchedulerPriority(Platform l){
        this.logger = l;
    }

    //@Override
    public void notifyNewProcess(Process p) {
        //if queue is empty add process
        boolean inserted = false;
        if(processes.size() == 0) {
            processes.add(p);
        }else {
            //Insert processes into queue according to priority
            for (int i = 0; i < processes.size(); i++) {
                if (processes.get(i).getPriority() > p.getPriority()) {
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
        //If there is no process running and there is a process available schedule that process
        if(cpu == null && processes != null){
            //starting a process, increment context switch
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
                logger.log("Process " + cpu.getName() + " execution complete");
                //If there are no more processes return null
                if(processes.isEmpty()){
                    return null;
                }
            }else{
                //execution should be complete by now
                processes.add(cpu);
            }
            //Schedule new process and increment context switch
            cpu = processes.peek();
            this.contextSwitches ++;
            logger.log("Scheduled: " + cpu.getName());
            processes.remove();
            return cpu;
        }

        return cpu;
    }
}
