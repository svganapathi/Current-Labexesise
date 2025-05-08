/* SJF Scheduling - sjf.c */
#include <stdio.h>

struct process {
    int pid;
    int btime;
    int wtime;
    int ttime;
};

int main() {
    struct process p[10], temp;
    int i, j, k, n, ttur = 0, twat = 0;
    float awat, atur;

    printf("Enter no. of process: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Burst time for process P%d (in ms): ", (i + 1));
        scanf("%d", &p[i].btime);
        p[i].pid = i + 1;
    }

    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if ((p[i].btime > p[j].btime) || (p[i].btime == p[j].btime && p[i].pid > p[j].pid)) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    p[0].wtime = 0;
    for (i = 0; i < n - 1; i++) {
        p[i + 1].wtime = p[i].wtime + p[i].btime;
    }

    for (i = 0; i < n; i++) {
        p[i].ttime = p[i].wtime + p[i].btime;
        ttur += p[i].ttime;
        twat += p[i].wtime;
    }

    awat = (float)twat / n;
    atur = (float)ttur / n;

    printf("-----------------------------\n");
    printf("      SJF Scheduling\n\n");
    printf("-----------------------------\n");
    printf(" Process | B-Time | T-Time | W-Time\n");
    printf("-----------------------------\n");
    for (i = 0; i < n; i++) {
        printf(" P%-4d  | %6d | %6d | %6d\n", p[i].pid, p[i].btime, p[i].ttime, p[i].wtime);
    }
    printf("-----------------------------\n");
    printf("\nAverage waiting time: %.2fms\n", awat);
    printf("Average turn around time: %.2fms\n", atur);
    printf("\n\n          GANTT Chart\n");
    printf("-------------------------------\n");
    printf("|");
    for (i = 0; i < n; i++) {
        for (j = 0; j < p[i].btime; j++) {
            printf(" ");
        }
        printf("P%d", p[i].pid);
        for (j = 0; j < p[i].btime; j++) {
            printf(" ");
        }
        printf("|");
    }
    printf("\n-------------------------------\n");
    printf("0");
    for (i = 0; i < n; i++) {
        for (j = 0; j < p[i].btime; j++) {
            printf(" ");
        }
        printf("%-2d", p[i].ttime);
    }
    printf("\n");

    return 0;
}