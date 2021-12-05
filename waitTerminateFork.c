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
    printf("\nI am the child! My pid is %d\n", getpid());
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
        wait(&status);
        if (WEXITSTATUS(status) != 0){
            printf("Child Process finished with an error");
        }
        else{
            printf("Child process terminated succesfully");
        }
        
        printf("\nI am the Parent and I'm still here! My pid is %d\nThe child's pid is %d\n", getpid(), pi);
    }
    return 0;
}