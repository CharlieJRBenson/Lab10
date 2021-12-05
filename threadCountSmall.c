#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

void error(char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

int count = 0;

void *countFunc(void *a)
{
    int i;
    for (i = 0; i < 100; i++)
    {
        count++;
    }
    return NULL;
}

int main()
{
    pthread_t threads[15];
    int t;
    void *result;
    printf("Counting to 100, with 15 threads");
    for (t = 0; t < 15; t++)
    {
        if (pthread_create(&threads[t], NULL, countFunc, NULL) == -1)
            error("Cannot create thread");
    }
    for (t = 0; t < 15; t++)
    {
        if (pthread_join(threads[t], &result) == -1)
            error("Cannot Join Thread");
    }
    printf("\nThe count is now %i\n", count);
    return 0;
}

/*
The reason we cant accurately get the expected output
when each thread increments say 1 mil times is an issue
called interleaving.
Interleaving is where multiple threads accessing the same
count variable perform the same action at the time where 
the value is changing. Therefore erasing the competing 
threads work. So over large volumes/numbers the data becomes
further from the expected output.

We use mutexes to solve this
*/