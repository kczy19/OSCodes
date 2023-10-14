#include <stdio.h>
#include <stdbool.h>
#include<limits.h>

typedef struct process {
    int id;
    int burst;
    int arrival;
    int completion;
    int remaining;
    int turn_around_time;
    int waiting_time;
    int response_time;
    bool completed;
} process;

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    process processes[n];
    for (int i = 0; i < n; ++i) {
        printf("Enter Arrival And Burst Time Of Process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival, &processes[i].burst);
        processes[i].id = i + 1;
        processes[i].remaining = processes[i].burst;
        processes[i].response_time = -1;
        processes[i].completed = false;
    }
    int timeQuanta;
    printf("Enter Time Quanta: ");
    scanf("%d", &timeQuanta);

    int totalProcesses = 0;
    int currTime = 0;
    
    int idleTime = 0;
    float averageTurnAroundTime = 0;
    float averageWaitingTime = 0;

    while (totalProcesses < n) {
        bool found = false;
        for (int i = 0; i < n; ++i) {
            if (processes[i].completed) {
                continue;
            }
            if (processes[i].response_time == -1) {
                processes[i].response_time = currTime - processes[i].arrival;
            }
            int time_slice = (processes[i].remaining < timeQuanta) ? processes[i].remaining : timeQuanta;
            currTime += time_slice;
            processes[i].remaining -= time_slice;
            if (processes[i].remaining == 0) {
                processes[i].completion = currTime;
                processes[i].turn_around_time = processes[i].completion - processes[i].arrival;
                processes[i].waiting_time = processes[i].turn_around_time - processes[i].burst;
                processes[i].completed = true;
                averageTurnAroundTime += processes[i].turn_around_time;
                averageWaitingTime += processes[i].waiting_time;
                totalProcesses++;
            }
            found = true;
        }

        if (!found) {
            int nextArrival = INT_MAX;
            for (int i = 0; i < n; ++i) {
                if (!processes[i].completed && processes[i].arrival < nextArrival) {
                    nextArrival = processes[i].arrival;
                }
            }
            idleTime += nextArrival - currTime;
            currTime = nextArrival;
        }
    }
    float cpu_util = ((currTime - idleTime)/(1.0*currTime))*100;
    float throughput = ((1.0)*n)/currTime;
    averageTurnAroundTime /= (1.0*n);
    averageWaitingTime /= (1.0*n);

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; ++i) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].id, processes[i].arrival, processes[i].burst, processes[i].completion, processes[i].turn_around_time, processes[i].waiting_time, processes[i].response_time);
    }

    printf("CPU Utilization: %f\n",cpu_util);
    printf("Idle Time: %d\n",idleTime);
    printf("Average Turn Around Time: %f\n",averageTurnAroundTime);
    printf("Average Waiting Time: %f\n",averageWaitingTime);
    printf("Throughput: %f: \n",throughput);
}
