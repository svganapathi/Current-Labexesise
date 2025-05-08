/* Load a program in child process exec.c*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h> // Need to include this for wait()

int main()
{
    pid_t pid;
    switch(pid = fork())
    {
    case -1:
        perror("Fork failed");
        exit(-1);
    case 0:
        printf("Child process\n");
        execl("/bin/date", "date", (char *)0); // Correct way to terminate argument list
        perror("Exec failed"); // This will only be reached if execl fails
        exit(1);
    default:
        wait(NULL);
        printf("Child Terminated\n");
        exit(0);
    }
}