/* Fibonacci and Prime using pipe - fibprime.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h> // Include for wait()

int main() {
    pid_t pid;
    int pfd[2];
    int i, j, flg, f1, f2, f3;
    static unsigned int ar[25], br[25];

    if (pipe(pfd) == -1) {
        printf("Error in pipe\n");
        exit(-1);
    }

    pid = fork();

    if (pid == 0) {
        printf("Child process generates Fibonacci series\n");
        f1 = 0; // Corrected initial value
        f2 = 1; // Corrected initial value
        printf("%d\t%d\t", f1, f2); // Print the first two Fibonacci numbers
        ar[0] = f1;
        ar[1] = f2;
        for (i = 2; i < 25; i++) {
            f3 = f1 + f2;
            printf("%d\t", f3);
            f1 = f2;
            f2 = f3;
            ar[i] = f3;
        }
        close(pfd[0]); // Close read end in child
        write(pfd[1], ar, 25 * sizeof(int));
        close(pfd[1]); // Close write end in child
        printf("\n");
        exit(0); // It's good practice to exit the child process
    } else if (pid > 0) {
        wait(NULL);
        close(pfd[1]); // Close write end in parent
        read(pfd[0], br, 25 * sizeof(int));
        close(pfd[0]); // Close read end in parent
        printf("\nParent prints Fibonacci that are Prime\n");
        for (i = 0; i < 25; i++) {
            flg = 0;
            if (br[i] <= 1) {
                flg = 1;
            } else {
                for (j = 2; j <= br[i] / 2; j++) {
                    if (br[i] % j == 0) {
                        flg = 1;
                        break;
                    }
                }
            }
            if (flg == 0) {
                printf("%d\t", br[i]);
            }
        }
        printf("\n");
    } else {
        printf("Process creation failed\n");
        exit(-1);
    }

    return 0; // Added return 0 for main function
}