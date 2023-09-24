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
            if(processes[j].arrival > processes[j+1].arrival){
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
    for(int i = 0;i<n;++i){
        currTime = currTime>processes[i].arrival?currTime:processes[i].arrival;
        processes[i].completion = currTime + processes[i].burst;
        currTime = processes[i].completion;
        processes[i].turn_around_time = processes[i].completion - processes[i].arrival;
        processes[i].waiting = processes[i].turn_around_time - processes[i].burst;
        processes[i].response_time = processes[i].waiting;
    }
}
int main(){
    int n;
    scanf("%d",&n);
    process processes[n];
    for(int i = 0;i<n;++i){
        processes[i].id = i + 1;
        printf("Enter Arrival Time of %d process: ",i+1);
        scanf("%d",&processes[i].arrival);
        printf("Enter Burst Time of %d process: ",i+1);
        scanf("%d",&processes[i].burst);
    }
    compute(processes,n);
    for(int i = 0;i<n;++i){
        printf("%d %d %d %d %d %d %d\n",processes[i].id,processes[i].arrival,processes[i].burst,processes[i].completion,processes[i].turn_around_time,processes[i].waiting,processes[i].response_time);
    }
}