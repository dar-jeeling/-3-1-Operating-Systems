#include <pthread.h>
#include <stdlib.h>
void *test(void *data)
{
}
int main()
{
    int a = 100;
    pthread_t thread_t;
    int status;
 
    if (pthread_create(&thread_t, NULL, test, (void *)&a) < 0)
    {
        perror("thread create error:");
        exit(0);
    }
    pthread_join(thread_t, (void **)&status);
    printf("Thread End %d\n", status);
    return 1;
}
