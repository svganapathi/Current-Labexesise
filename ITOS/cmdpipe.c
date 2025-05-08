/* No. of users logged cmdpipe.c*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
    int pfds[2];
    pipe(pfds);
    if (!fork())
    {
        close(1);
        dup(pfds[1]);
        close(pfds[0]);
        execlp("who", "who", NULL);
        exit(0); // Add this to prevent the child from entering the else block
    }
    else
    {
        close(0);
        dup(pfds[0]);
        close(pfds[1]);
        execlp("wc", "wc", "-l", NULL); // Corrected option for line count
    }
    return 0;
}