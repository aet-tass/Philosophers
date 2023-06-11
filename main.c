#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 5

void* thread_function(void* arg)
{
    int thread_id = *((int*)arg);
    printf("Hello from thread %d\n", thread_id);
    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];
    int i;

    for (i = 0; i < NUM_THREADS; i++) {
        thread_args[i] = i;
        if (pthread_create(&threads[i], NULL, thread_function, &thread_args[i]) != 0) {
            printf("Failed to create thread %d\n", i);
            return 1;
        }
    }

    for (i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            printf("Failed to join thread %d\n", i);
            return 1;
        }
    }
    return 0;
}
