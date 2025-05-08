/* Priority Scheduling- priority.c*/
#include <stdio.h>
struct process
{ int pid; int btime; int pri; int wtime; int ttime; } p[10], temp;
int main()
{
    int i,j,k,n,ttur,twat;
    float awat,atur;
    printf("Enter no. of process: ");
    scanf("%d", &n);
    for(i=0; i<n; i++)
    {
        printf("Burst time for process P%d (in ms): ", (i+1));
        scanf("%d", &p[i].btime);
        printf("Priority for process P%d: ", (i+1));
        scanf("%d", &p[i].pri);
        p[i].pid = i + 1;
    }
    for(i=0; i<n-1; i++)
    {
        for(j=i+1; j<n; j++) {
            if((p[i].pri > p[j].pri) || (p[i].pri == p[j].pri && p[i].pid > p[j].pid)) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
    p[0].wtime = 0;
    for(i=0; i<n-1; i++)
    {
        p[i+1].wtime = p[i].wtime + p[i].btime;
        p[i].ttime = p[i].wtime + p[i].btime;
    }
    p[n-1].ttime = p[n-1].wtime + p[n-1].btime;

    ttur = 0;
    twat = 0;
    for(i=0; i<n; i++) {
        ttur += p[i].ttime;
        twat += p[i].wtime;
    }
    awat = (float)twat/n;
    atur = (float)ttur/n;
    printf("\n\t Priority Scheduling\n\n");
    for(i=0; i<38; i++)
        printf("-");
    printf("\nProcess B-Time Priority T-Time W-Time\n");
    for(i=0; i<38; i++)
        printf("-");
    for (i=0; i<n; i++)
        printf("\nP%4d\t%4d\t%3d\t%4d\t%4d",p[i].pid,p[i].btime,p[i].pri,p[i].ttime, p[i].wtime);
    printf("\n");
    for(i=0; i<38; i++)
        printf("-");
    printf("\n\nAverage waiting time: %5.2fms", awat);
    printf("\nAverage turn around time: %5.2fms\n", atur);
    printf("\n\nGANTT Chart\n");
    printf("-");
    for(i=0; i<(p[n-1].ttime + 2*n); i++)
        printf("-");
    printf("\n");
    printf("0");
    for(i=0; i<n; i++)
    {
        k = p[i].btime;
        for(j=0; j<k; j++)
            printf(" ");
        printf("P%d ",p[i].pid);
    }
    printf("\n");
    printf("-");
    for(i=0; i<(p[n-1].ttime + 2*n); i++)
        printf("-");
    printf("\n");
    int gantt_time = 0;
    for(i=0; i<n; i++)
    {
        gantt_time += p[i].btime;
        printf("%-4d", gantt_time);
    }
    printf("\n");
    return 0;
}