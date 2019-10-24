import java.util.LinkedList;

class SchedulerSRTF extends SchedulerBase implements Scheduler {
    LinkedList<Process> processes = new LinkedList<>();
    Platform logger;

    public SchedulerSRTF(Platform l){
        this.logger = l;
    }

    public void insertProcess(Process p){
        //Insert the process according to remaining burst time.
        boolean inserted = false;
        //if(processes == null){ return; }
        for (int i = 0; i < processes.size(); i++) {
            if (processes.get(i).getRemainingBurst() > p.getRemainingBurst()) {
                processes.add(i, p);
                inserted = true;
                break;
            }
        }
        if(!inserted){
            processes.addLast(p);
        }

    }

    public void notifyNewProcess(Process p) {
        //if queue is empty add process
        boolean inserted = false;
        if(processes.size() == 0) {
            processes.add(p);
        }else {
            insertProcess(p);
        }
    }

    public Process update(Process cpu){
        //If there is no process running and there is a process available schedule that process
        if(cpu == null && processes != null) {
            //starting a process, add context switch
            this.contextSwitches++;
            cpu = processes.peek();
            processes.remove();
            logger.log("Scheduled: " + cpu.getName());
            return cpu;
        }
        else if(cpu.isBurstComplete()){
            //If busrt complete, log it and add a context switch
            logger.log("Process " + cpu.getName() + " burst complete");
            this.contextSwitches ++;
            if(cpu.isExecutionComplete()){
                //if execution is done, log it
                logger.log("Process " + cpu.getName() + " execution complete");
                //if there are no more processes return null
                if(processes.isEmpty()){
                    return null;
                }
            }else{
                //if execution not complete insert into processes
                insertProcess(cpu);
            }
            //schedule new process and increment context switch
            cpu = processes.peek();
            this.contextSwitches ++;
            logger.log("Scheduled: " + cpu.getName());
            processes.remove();
            return cpu;
        }else if(!processes.isEmpty()){
            //if current process has a longer remaining time then the shortest time in the other scheduled processes then preemptively stop it.
            if(cpu.getRemainingBurst() > processes.get(0).getRemainingBurst()) {
                insertProcess(cpu);
                this.contextSwitches++;
                cpu = processes.peek();
                logger.log("Preemptively removed: " + cpu.getName());
                this.contextSwitches++;
                logger.log("Scheduled: " + cpu.getName());
                processes.remove();
            }
            return cpu;
        }

        return cpu;
    }
}
