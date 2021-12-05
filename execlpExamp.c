#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h> /*necessar for waiting calls*/
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
    printf("exec command: ls -aF :");
    execlp("ls", " ‐aF /", "/", NULL) != 0;
    
}

int main()
{
    pid_t pi;
    pi = fork();
    int status;

    if (pi == -1)
        error("Cannot fork() process!!");
    if (pi == 0)
    { /* child process */
        runChild();
    }
    else if (pi > 0)
    { /* parent process */      
        printf("\nI am the Parent! My pid is %d\nThe child's pid is %d\n", getpid(), pi);
    }
    return 0;
}