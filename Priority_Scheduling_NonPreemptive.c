#include<stdio.h>
#include<limits.h>
#include<stdbool.h>

typedef struct process {
    int id;
    int priority;
    int arrival;
    int burst;
    int completion;
    int turn_around_time;
    int waiting_time;
    int response_time;
    bool completed;
} process;

int maxPriorityInd(process* processes, int n, int currTime){
    int ind = -1;
    int priority = INT_MAX;
    int arrival = INT_MAX;
    for(int i = 0;i<n;++i){
        if(processes[i].priority <= priority && !processes[i].completed && processes[i].arrival <= currTime){
            if(processes[i].priority == priority){
                if(processes[i].arrival >= arrival){
                    continue;
                }
            }
            ind = i;
            priority = processes[i].priority;
            arrival = processes[i].arrival;
        }
    }
    return ind;
}
int main(){
    int n;
    scanf("%d", &n);
    process processes[n];
    for (int i = 0; i < n; ++i) {
        printf("Enter Priority, Arrival And Burst Time Of Process %d: ", i + 1);
        scanf("%d %d %d",&processes[i].priority,&processes[i].arrival, &processes[i].burst);
        processes[i].id = i + 1;
        processes[i].response_time = -1;
        processes[i].completed = false;
    }

    int currTime = 0;
    int totalProcesses = 0;

    currTime += processes[0].burst;
    processes[0].response_time = 0;
    processes[0].completed = true;   
    processes[0].completion = currTime;
    processes[0].turn_around_time = processes[0].completion - processes[0].arrival;
    processes[0].waiting_time = processes[0].turn_around_time - processes[0].burst; 
    totalProcesses++;
    
    while(totalProcesses < n){
        int highestPriorityInd = maxPriorityInd(processes, n, currTime);
        if(highestPriorityInd == -1){
            currTime++;
            continue;
        }
        if(processes[highestPriorityInd].response_time == -1){
            processes[highestPriorityInd].response_time = currTime;
        }
        currTime += processes[highestPriorityInd].burst;
        processes[highestPriorityInd].completed = true;
        processes[highestPriorityInd].completion = currTime;
        processes[highestPriorityInd].turn_around_time = processes[highestPriorityInd].completion - processes[highestPriorityInd].arrival;
        processes[highestPriorityInd].waiting_time = processes[highestPriorityInd].turn_around_time - processes[highestPriorityInd].burst; 
        totalProcesses++;
    }
    printf("\nPID\tPR\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; ++i) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].id, processes[i].priority,processes[i].arrival, processes[i].burst, processes[i].completion, processes[i].turn_around_time, processes[i].waiting_time, processes[i].response_time);
    }
}

