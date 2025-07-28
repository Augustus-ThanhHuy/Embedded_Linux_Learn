#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_THREADS 6

void *do_thread(void *data);

int main(){

    int res;
    int thread_num;
    pthread_t a_thread[MAX_THREADS];

    void *thread_result;

    for(thread_num=1; thread_num<MAX_THREADS; thread_num++)
    {
        res=pthread_create(&(a_thread[thread_num]), NULL, do_thread, (void*) thread_num);
    }
    if(res != 0){
        perror("Thread created error");
        exit(EXIT_FAILURE);
    }
    sleep(1);

    printf("Waiting for threads to finish...\n");
    for(thread_num=MAX_THREADS-1; thread_num>0; thread_num--)
    {
        res=pthread_join(a_thread[thread_num], &thread_result);

        if(res != 0){
            perror("Thread exited error");
        }
        else {
            printf("Pickup a thread \n");
        }
    }
    printf("All thread comple ted \n");

    return 0;
}

void *do_thread(void *data)
{
    int my_number= (int)data;
    printf("thread function is running. Data argument was %d\n", my_number);
    sleep(3);
    printf("Finish - bye from %d\n", my_number);
}