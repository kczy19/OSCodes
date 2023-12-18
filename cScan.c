#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);

    int disk[200] = {0};
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        disk[x]++;
    }

    int init_pos, dir;
    scanf("%d %d", &init_pos, &dir);

    int totalTime = 0;

    if (dir == 0) {
        int pos = init_pos;

        for (int i = pos; i < 200; ++i) {
            if (disk[i]) {
                totalTime += abs(i - pos);
                disk[i] = 0;
                pos = i;
            }
        }
        totalTime += abs(199 - pos);
        totalTime += 199;
        pos = 0;
        for (int i = pos; i <= init_pos; ++i) {
            if (disk[i]) {
                totalTime += abs(i - pos);
                disk[i] = 0;
                pos = i;
            }
        }
    } else {
        int pos = init_pos;

        for (int i = pos; i >= 0; --i) {
            if (disk[i]) {
                totalTime += abs(i - pos);
                disk[i] = 0;
                pos = i;
            }
        }

        totalTime += abs(0 - pos);
        totalTime += 200;
        pos = 200;

        for (int i = pos; i >= init_pos; --i) {
            if (disk[i]) {
                totalTime += abs(i - pos);
                disk[i] = 0;
                pos = i;
            }
        }
    }

    printf("Total time: %d\n", totalTime);

    return 0;
}
