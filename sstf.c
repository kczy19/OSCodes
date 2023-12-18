#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
int findIndex(int activity[], int init_pos, int n){
    int ind = -1;
    int time = INT_MAX;
    for(int i = 0;i<n;++i){
        if(activity[i] == -1) continue;
        int newTime = abs(init_pos - activity[i]);
        if(newTime < time){
            time = newTime;
            ind = i;
        }
    }
    return ind;
}

int main()
{
    int n;
    scanf("%d",&n);
    int activity[n];
    for(int i = 0;i<n;++i){
        scanf("%d",&activity[i]);
    }
    int init_pos;
    scanf("%d",&init_pos);
    int totalTime = 0;
    for(int i = 0;i<n;++i){
        int ind = findIndex(activity, init_pos, n);
        totalTime += abs(activity[ind] - init_pos);
        printf("%d to %d\n", init_pos, activity[ind]);
        init_pos = activity[ind];
        activity[ind] = -1;
    }
    printf("TOTAL: %d\n",totalTime);

}