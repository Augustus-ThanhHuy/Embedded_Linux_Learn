#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_HANDLER_THREADS 3

pthread_mutex_t request_mutex = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;

pthread_cond_t got_request = PTHREAD_COND_INITIALIZER;

int num_requests = 0;

struct request {
    int number;
    struct request* next;
};

struct request* requests = NULL;

struct request* last_request = NULL; 

void add_request (int request_num, pthread_mutex_t* pthread_mutex, pthread_cond_t* p_cond_var)
{
    int rc;
    struct request* a_request;

    a_request = (struct request*)malloc(sizeof(struct request));
     
    if (!a_request)
    {
        fprintf(stderr, "add_request: out of memory\n");
        exit(1);
    }

    a_request->number = request_num;
    a_request->next = NULL;

    rc = pthread_mutex_lock(p_mutex); 
    
    if (num_requests == 0)
    {
        request = a_request;
        last_request = a_request;
    }
    else{
        last_request->next = a_request;
        last_request = a_request;
    }

    num_requests++;

    #ifdef DEBUG
        printf("add_request: added request with id '%d\n", a_request->number);
        fflush(stdout);
    #endif 
    
    rc = pthread_mutex_unlock(pthread_mutex);
    
    rc = pthread_cond_signal(p_cond_var);
}
struct request* get_request(pthread_mutex_t*p_mutex)
{
    int rc;
    struct request* a_request;

     rc = pthread_mutex_lock(p_mutex);

    if(num_requests > 0){
        a_request = requests;
        requests = a_request->next;
    if (requests == NULL)
        {
            last_request = NULL;
        }
        num_requests--;
    }
    else{
            a_request = NULL;
    }
    rc pthread_mutex_unlock(pthread_mutex);

    return a_request;
}

void handle_request(struc request* a_request, int thread_id)
{
    if (a_request)
    {
        printf("Thread '%d' handle_request '%d'\n", thread_id, a_request->number);
        fflush(stdout);
    }
}

void* handle_requests_loop(void* data)
{
    int rc;
    struct request* a_request;

    int thread_id = *((int*)data);

    #ifdef DEBUG
        printf("Starting thread '%d'\n", thread_id);
        fflush(stdout);
    #endif 

    rc = pthread_mutex_lock(&request_mutex);

    #ifdef DEBUG
        printf("thread '%d' after pthread_mutex_lock\n", thread_id);
        fflush(stdout);
    #endif

    while(1){
    #ifdef DEBUG
        printf("thread '%d', num_requests = %d\n", thread_id, num_requests);
        fflush(stdout);
    #endif

        if(num_requests > 0){
            a_request = get_request(&request_mutex);
            if(a_request){
                handle_request(a_request, thread_id);
                free(a_request);
            }
        }
        else {
    #ifdef DEBUG
        printf("thread '%d' before pthread_cond_wait\n", thread_id);
        fflush(stdout);
    #endif 
            rc = pthread_cond_wait(&got_request, &request_mutex);
    #ifdef DEBUG
        printf("thread '%d' after pthread_cond_wait\n", thread_id);
        fflush(stdout);
    #endif 
        }
    }

}

int main()
{
    int i;
    int thr_id[NUM_HANDLER_THREADS];

    pthread_t p_threads[NUM_HANDLER_THREADS];

    struct timespec delay;

    for (i = 0; i < NUM_HANDLER_THREADS; i++)
    {
        thr_id[i]=i;
        pthread_create(&p_threads[i], NULL, handle_requests_loop, (void*)thr_id[i]);
    }

    for ( i = 0; i < 600; i++)
    {
        add_request(i, &request_mutex, &got_request);

        if (rand() > 3*(RAND_MAX/4))
        {
            delay.tv_sec = 0;
            delay.tv_nsec = 10;
            nanosleep(&delay, NULL);
        }
    }

    sleep(5);

    printf("We are done. \n");

    return 0;
}