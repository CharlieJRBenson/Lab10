#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>  /* Necessary because errno value used */
#include <stdlib.h> /* Necessary for exit() */
#include <string.h> /* Necessary for strerror() */
void error(char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

int main()
{
    pid_t pi;
    int counter = 0;
    printf("--The beginning of the parent program\n");
    pi = fork();
    if (pi == -1)
        error("Cannot fork() process!!");
    if (pi == 0)
    { /* child process */
        int i = 0;
        for (; i < 5; ++i)
        {
            printf("child process: counter=%d\n", ++counter);
        }
        printf("--end of child program--\n");
    }
    else if (pi > 0)
    { /* parent process */
        int j = 0;
        for (; j < 5; ++j)
        {
            printf("parent process: counter=%d\n", ++counter);
        }
        printf("--end of parent program--\n");
    }
    return 0;
}