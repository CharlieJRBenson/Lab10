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

void runChild(void)
{
    printf("\n I am the child! My pid is %d\n", getpid());
}

int main()
{
    pid_t pi;
    pi = fork();

    if (pi == -1)
        error("Cannot fork() process!!");
    if (pi == 0)
    { /* child process */
        runChild();
    }
    else if (pi > 0)
    { /* parent process */
        
        sleep(5);
        printf("\n I am the Parent (it's been 5 seconds) and I'm still here! My pid is %d\n The child's pid is %d\n", getpid(), pi);
    }
    return 0;
}