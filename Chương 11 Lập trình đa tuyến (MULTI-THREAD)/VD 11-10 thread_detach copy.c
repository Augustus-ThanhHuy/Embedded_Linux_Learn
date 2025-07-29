#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *do_thread(void *data);

char message[]="Hello World";
int thread_finished=0;

int main(){
    int res;
    pthread_t a_thread;
    pthread_attr_t thread_attr; //Biến thuộc tính
/*Khởi tạo biến thuộc tính*/
    res=pthread_attr_init(&thread_attr);

    if(res!=0){
        perror("Init atribute error");
        exit(EXIT_FAILURE);
    }

/*Đặt thuộc tính*/
    res=pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);

    if(res!=0){
        perror("Set thread detached error");
        exit(EXIT_FAILURE);
    }

/*Tạo tuyến mang thuộc tính tách rời*/
    res=pthread_create(&a_thread, &thread_attr, do_thread, (void*)message);
    if(res!=0){
        perror("Thread create error");
        exit(EXIT_FAILURE);
    }
    while(!thread_finished){
        printf("Waiting for thread say it's finished...\n");
        sleep(1);
    }
    printf("Thread detached done \n");
    exit(EXIT_SUCCESS);

}
void *do_thread(void *data){
    printf("Thread function is running. Argument was %s \n", (char *)data);
    sleep(4);
    printf("Sub thread setting finished flag and exiting now \n");
    thread_finished=1;
    pthread_exit(NULL);
}
