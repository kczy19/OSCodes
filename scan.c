#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    scanf("%d", &n);
    int disk[201] = {0};
    int minn = 99999;
    int maxx = -1;
    for (int i = 0; i < n; ++i)
    {
        int x;
        scanf("%d", &x);
        disk[x]++;
        if (x < minn)
        {
            minn = x;
        }
        if (x > maxx)
        {
            maxx = x;
        }
    }
    int init_pos;
    scanf("%d", &init_pos);
    int dir;
    scanf("%d", &dir);
    int totalTime = 0;
    if (dir == 0)
    {
        int pos = init_pos;
        for (int i = init_pos; i < 201; ++i)
        {
            if (disk[i])
            {
                totalTime += abs(i - pos);
                disk[i] = 0;
                pos = i;
            }
        }
        totalTime += abs(pos - 200);
        pos = 200;
        for (int j = 200; j >= minn; --j)
        {
            if (disk[j])
            {
                totalTime += abs(j - pos);
                disk[j] = 0;
                pos = j;
            }
        }
    }
    else
    {
        int pos = init_pos;
        for (int j = pos; j >= 0; --j)
        {
            if (disk[j])
            {
                totalTime += abs(j - pos);
                disk[j] = 0;
                pos = j;
            }
        }
        totalTime += pos;
        pos = 0;
        for (int i = init_pos; i <= maxx; ++i)
        {
            if (disk[i])
            {
                totalTime += abs(i - pos);
                disk[i] = 0;
                pos = i;
            }
        }
    }
    printf("Total time: %d\n", totalTime);
}