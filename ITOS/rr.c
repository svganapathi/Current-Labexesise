/* Round robin scheduling- rr.c*/
#include <stdio.h>

int main()
{
    int i, x = -1, k[10], m = 0, n, t, s = 0;
    int a[50], temp, b[50], p[10], bur[10], bur1[10];
    int wat[10], tur[10], ttur = 0, twat = 0, j = 0;
    float awat, atur;

    printf("Enter no. of process: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        printf("Burst time for process P%d: ", (i + 1));
        scanf("%d", &bur[i]);
        bur1[i] = bur[i];
    }

    printf("Enter the time slice (in ms): ");
    scanf("%d", &t);

    for (i = 0; i < n; i++)
    {
        b[i] = bur[i] / t;
        if ((bur[i] % t) != 0)
            b[i] += 1;
        m += b[i];
    }

    printf("\n\t\tRound Robin Scheduling\n");
    printf("\nGANTT Chart\n");
    for (i = 0; i < m; i++)
        printf("---");
    printf("\n");

    a[0] = 0;
    while (j < m)
    {
        if (x == n - 1)
            x = 0;
        else
            x++;

        if (bur[x] > 0)
        {
            if (bur[x] >= t)
            {
                bur[x] -= t;
                a[j + 1] = a[j] + t;
                printf("P%d ", x + 1);
            }
            else
            {
                a[j + 1] = a[j] + bur[x];
                printf("P%d ", x + 1);
                bur[x] = 0;
            }
            p[s] = x;
            k[s] = a[j + 1];
            s++;
            j++;
        }
    }
    printf("\n");
    for (i = 0; i < m; i++)
        printf("---");
    printf("\n");
    for (j = 0; j <= m; j++)
    {
        printf("%-3d", a[j]);
    }
    printf("\n");

    for (i = 0; i < n; i++)
    {
        wat[i] = k[i] - bur1[i];
        tur[i] = k[i];
        ttur += tur[i];
        twat += wat[i];
    }

    printf("\n\n");
    for (i = 0; i < 30; i++)
        printf("-");
    printf("\nProcess\tBurst\tTrnd\tWait\n");
    for (i = 0; i < 30; i++)
        printf("-");
    for (i = 0; i < n; i++)
        printf("\nP%-4d\t%4d\t%4d\t%4d", i + 1, bur1[i], tur[i], wat[i]);
    printf("\n");
    for (i = 0; i < 30; i++)
        printf("-");

    awat = (float)twat / n;
    atur = (float)ttur / n;

    printf("\n\nAverage waiting time: %.2f ms", awat);
    printf("\nAverage turnaround time: %.2f ms\n", atur);

    return 0;
}