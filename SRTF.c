#include<stdio.h>
#include<stdbool.h>
#include<limits.h>

typedef struct process{
    int id;
    int arrival;
    int burst;
    int remaining;
    int completion;
    int turn_around_time;
    bool completed;
    int waiting;
    int response_time;
}process;

int findMinInd(process* processes, int n, int CurrTime){
    int ind = -1;
    int shortestTime = INT_MAX;
    for(int i = 0;i<n;++i){
        if(processes[i].remaining < shortestTime && processes[i].completed == false && processes[i].arrival <= CurrTime){
            ind = i;
            shortestTime = processes[i].remaining;
        }
    }
    return ind;
}
int main(){
    int n;
    scanf("%d",&n);
    process processes[n];
    for(int i = 0;i<n;++i){
        printf("Enter Arrival and Burst Time: ");
        scanf("%d%d",&processes[i].arrival, &processes[i].burst);
        processes[i].id = i + 1;
        processes[i].completed = false;
        processes[i].response_time = -1;
        processes[i].remaining = processes[i].burst;
    }
    int totalProcesses = 0;
    int currTime = 0;
    int idleTime = 0;
    float averageTurnAroundTime = 0;
    float averageWaitingTime = 0;
    while(totalProcesses < n){
        int minInd = findMinInd(processes, n, currTime);
        if(minInd == -1){
            currTime++;
            idleTime++;
            continue;
        }
        if(processes[minInd].response_time == -1){
            processes[minInd].response_time -= processes[minInd].arrival;
        }
        processes[minInd].remaining--;
        currTime++;

        if(processes[minInd].remaining == 0){
            processes[minInd].completed = true;
            totalProcesses++;
            processes[minInd].completion = currTime;
            processes[minInd].turn_around_time = currTime - processes[minInd].arrival;
            processes[minInd].waiting = processes[minInd].turn_around_time - processes[minInd].burst;
            averageTurnAroundTime += processes[minInd].turn_around_time;
            averageWaitingTime += processes[minInd].waiting;
        }
    }
    float cpu_util = ((currTime - idleTime)/(1.0*currTime))*100;
    averageTurnAroundTime /= (1.0*n);
    averageWaitingTime /= (1.0*n);
    float throughput = ((1.0)*n)/currTime;
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; ++i) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].id, processes[i].arrival, processes[i].burst, processes[i].completion, processes[i].turn_around_time, processes[i].waiting, processes[i].response_time);
    }
    printf("CPU Utilization: %f\n",cpu_util);
    printf("Idle Time: %d\n",idleTime);
    printf("Average Turn Around Time: %f\n",averageTurnAroundTime);
    printf("Average Waiting Time: %f\n",averageWaitingTime);
    printf("Throughput: %f: \n",throughput);
}