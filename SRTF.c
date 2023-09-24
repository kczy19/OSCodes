#include<stdio.h>
#include<stdbool.h>
#include<limits.h>

typedef struct process
{
    int id;
    int arrival;
    int burst;
    int remaining;
    int completion;
    int turn_around_time;
    int waiting_time;
    int response_time;
    bool completed;
}process;

int minIndFind(process* processes, int n, int currTime){
    int ind = -1;
    int shortestTime = INT_MAX;
    for(int i = 0;i<n;++i){
        if(processes[i].remaining < shortestTime && !processes[i].completed && processes[i].arrival <= currTime){
            ind = i;
            shortestTime = processes[i].remaining;
        }
    }
    return ind;
}

int main()
{
    int n;
    scanf("%d",&n);
    process processes[n];
    for(int i = 0;i<n;++i){
        processes[i].id = i + 1;
        printf("Enter Arrival And Burst Time Of Process %d: ",i+1);
        scanf("%d %d",&processes[i].arrival,&processes[i].burst);
        processes[i].remaining = processes[i].burst;
        processes[i].completed = false;
        processes[i].response_time = -1;
    }

    int currTime = 0;
    int totalProcesses = 0;
    while(totalProcesses < n){
        int minInd = minIndFind(processes, n, currTime);
        if(minInd == -1){
            currTime++;
            continue;
        }
        if(processes[minInd].response_time == -1){
            processes[minInd].response_time = currTime;
        }
        processes[minInd].remaining--;
        currTime++;
        if(processes[minInd].remaining == 0){
            processes[minInd].completed = true;
            totalProcesses++;
            processes[minInd].completion = currTime;
            processes[minInd].turn_around_time = processes[minInd].completion - processes[minInd].arrival;
            processes[minInd].waiting_time = processes[minInd].turn_around_time - processes[minInd].burst; 
        }
    }
    for(int i = 0;i<n;++i){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",processes[i].id,processes[i].arrival,processes[i].burst,processes[i].completion,processes[i].turn_around_time,processes[i].waiting_time,processes[i].response_time);
    }
}
