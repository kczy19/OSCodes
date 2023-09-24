#include<stdio.h>
#include<limits.h>
#include<stdbool.h>

typedef struct process {
    int id;
    int priority;
    int arrival;
    int burst;
    int completion;
    int remaining;
    int turn_around_time;
    int waiting_time;
    int response_time;
    bool completed;
} process;

int maxPriorityInd(process* processes, int n, int currTime){
    int ind = -1;
    int priority = INT_MAX;
    for(int i = 0;i<n;++i){
        if(processes[i].priority < priority && !processes[i].completed && processes[i].arrival <= currTime){
            ind = i;
            priority = processes[i].priority;
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
        processes[i].remaining = processes[i].burst;
        processes[i].response_time = -1;
        processes[i].completed = false;
    }
    int timeQuanta;
    printf("Enter Time Quanta: ");
    scanf("%d", &timeQuanta);

    int currTime = 0;
    int totalProcesses = 0;
    while(totalProcesses < n){
        int highestPriorityInd = maxPriorityInd(processes, n, currTime);
        if(highestPriorityInd == -1){
            currTime++;
            continue;
        }
        if(processes[highestPriorityInd].response_time == -1){
            processes[highestPriorityInd].response_time = currTime;
        }
        int time_slice = (processes[highestPriorityInd].remaining < timeQuanta) ? processes[highestPriorityInd].remaining : timeQuanta;
        currTime += time_slice;
        processes[highestPriorityInd].remaining -= time_slice;
        if(processes[highestPriorityInd].remaining == 0){
            processes[highestPriorityInd].completed = true;
            totalProcesses++;
            processes[highestPriorityInd].completion = currTime;
            processes[highestPriorityInd].turn_around_time = processes[highestPriorityInd].completion - processes[highestPriorityInd].arrival;
            processes[highestPriorityInd].waiting_time = processes[highestPriorityInd].turn_around_time - processes[highestPriorityInd].burst; 
        }
    }
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; ++i) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].id, processes[i].arrival, processes[i].burst, processes[i].completion, processes[i].turn_around_time, processes[i].waiting_time, processes[i].response_time);
    }
}

