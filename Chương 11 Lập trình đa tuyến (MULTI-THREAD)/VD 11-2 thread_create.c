#include <stdio.h>
#include <pthread.h>

void* do_loop(void* data)
{
    int i;
    int me = (int*)data;

    for(int i = 0; i < 5; i++){
        sleep(1);
        printf("'%d' - Got '%d'\n", me, i);
    }

    pthread_exit(NULL);
}

int main(int argc, char* argv[]){
    int thr_id; /*Định danh tuyến*/
    pthread_t p_thread; /* Cấu trúc lưu trữ các thông tin về tuyến*/
    int a = 1; /*Định danh tuyến thứ 1*/
    int b = 2; /*Định danh tuyến thứ 2*/

    /*Tạo tuyến*/
    thr_id = pthread_create(&p_thread, NULL, do_loop, (void*)a);

    /*Chạy do_loop trong tuyến chính*/
    do_loop((void*)b);
    
    return 0;
}