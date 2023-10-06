#include<stdio.h>
typedef struct process{
    int id;
    int arrival;
    int burst;
    int completion;
    int turn_around_time;
    int waiting;
    int response_time;
}process;
void sort(process* processes, int n){
    for(int i = 0;i<n-1;++i){
        for(int j = 0;j<n-i-1;++j){
            if(processes[j].burst > processes[j+1].burst){
                process temp = processes[j];
                processes[j] = processes[j+1];
                processes[j+1] = temp;
            }
        }
    }
}
void processSort(process* processes, int n){
    for(int i = 0;i<n-1;++i){
        for(int j = 0;j<n-i-1;++j){
            if(processes[j].id > processes[j+1].id){
                process temp = processes[j];
                processes[j] = processes[j+1];
                processes[j+1] = temp;
            }
        }
    }
}
void compute(process* processes, int n){
    sort(processes,n);
    int currTime = 0;
    int idleTime = 0;
    float averageTurnAroundTime = 0;
    float averageWaitingTime = 0;
    for(int i = 0;i<n;++i){
        if(currTime < processes[i].arrival){
            idleTime += (processes[i].arrival - currTime);
            currTime = processes[i].arrival;
        }
        processes[i].completion = currTime + processes[i].burst;
        currTime = processes[i].completion;
        processes[i].turn_around_time = processes[i].completion - processes[i].arrival;
        processes[i].waiting = processes[i].turn_around_time - processes[i].burst;
        processes[i].response_time = processes[i].waiting;
        averageTurnAroundTime += processes[i].turn_around_time;
        averageWaitingTime += processes[i].waiting;
    }
    processSort(processes,n);
    float cpu_util = ((currTime - idleTime)/(1.0*currTime))*100;
    averageTurnAroundTime /= (1.0*n);
    averageWaitingTime /= (1.0*n);
    float throughput = ((1.0)*n)/currTime;
    printf("\nCPU Utilization: %f\n",cpu_util);
    printf("Idle Time: %d\n",idleTime);
    printf("Average Turn Around Time: %f\n",averageTurnAroundTime);
    printf("Average Waiting Time: %f\n",averageWaitingTime);
    printf("Throughput: %f: \n",throughput);
}
int main(){
    int n;
    scanf("%d",&n);
    process processes[n];
    for(int i = 0;i<n;++i){
        processes[i].id = i + 1;
        printf("Enter Arrival and Burst Time: ");
        scanf("%d%d",&processes[i].arrival, &processes[i].burst);
    }
    compute(processes,n);
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; ++i) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].id, processes[i].arrival, processes[i].burst, processes[i].completion, processes[i].turn_around_time, processes[i].waiting, processes[i].response_time);
    }
}