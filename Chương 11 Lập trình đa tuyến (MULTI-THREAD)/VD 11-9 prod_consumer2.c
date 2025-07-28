#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int product_val=2;
sem_t semaphore;

void *do_thread(void *data);

int main(){
    int res, i;
    pthread_t a_thread;

    void *thread_result;
/* Khởi tạo đối tượng semaphore - Ở đây ta đặt giá trị cho semaphore là 2 */
    res=sem_init(&semaphore, 0, 2);
    if (res!=0)
    {
        perror("Semaphore init error");
        exit(EXIT_FAILURE);
    }
    
/* Khởi tạo tuyến đóng vai trò người tiêu thụ - consumer */
    res=pthread_create(&a_thread, NULL, do_thread, NULL);

    if(res != 0){
        perror("Thread create error");
        exit(EXIT_FAILURE);
    }
/* Tuyến chính đóng vai trò người sản xuất*/
    for (i = 0; i < 5; i++)
    {
        product_val++;
        printf("Producer product_val = %d \n\n", product_val);
/* Tăng giá trị semaphore (lên 1 ) - thông báo sản phẩm đã được đưa thêm vào kho*/
        sem_post(&semaphore);
        sleep(2);
    }
    
    printf("All done\n");
    exit(EXIT_SUCCESS);
}

void *do_thread(void *data){

    printf("Consumer thread function is running...\n");

    while (1)
    {
        /* Yêu cầu semaphore cho biết có được phép lấy sản phẩm khỏi kho hay không*/
        sem_wait(&semaphore);

        product_val--;
        printf("Consumer product_val = %d \n", product_val);
        sleep(1);
    }
    pthread_exit(NULL);
    
}