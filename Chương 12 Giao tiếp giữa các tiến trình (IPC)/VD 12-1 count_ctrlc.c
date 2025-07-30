#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>


//Định nghĩa biến đếm số  lần phím Ctrl-C được nhấn

int ctrl_c_count = 0;

#define CTRL_C_MAX 5

/*Hàm xử lý đón bắt tín hiệu INT khi Ctrl-C được nhấn */
void catch_int(int sig_num){
    sigset_t mask_set; /*Biến sử dụng để thiết lập mặt nạ tín hiệu*/
    sigset_t old_set;   /*Biến sử dụng để lưu mặt nạ tín hiệu trước đó*/

    /*Đặt lại bẫy xử lý tín hiệu cho lần kế tiếp*/
    signal(SIGINT, catch_int);

    /*Khóa tất cả các tín hiệu khác khi ta đang xử lý tín hiệu INT*/
    sigfillset(&mask_set);
    sigprocmask(SIG_SETMASK, &mask_set, &old_set);

    /*
    Tăng số lần nhận được tín hiệu INT cũng có nghãi là số lần
    ctrl-C được nhấn
    */
   ctrl_c_count++;

   /*Kiểm tra số lần nhấn Ctrl-C đạt 5 lần hay chưa*/
   if(ctrl_c_count >= CTRL_C_MAX){
        char answer[30];

        /*Hỏi người dùng có muốn chấm dứt tiến trình hay không*/
        printf("\nRealy Exit> [y/N]:");
        fflush(stdout);
        fgets(answer, sizeof(answer), stdin);
        if(answer[0] == 'y' || answer[0] == 'Y'){
            fflush(stdout);
            exit(0);
        }
        else{
            printf("\nContinuing\n");
            fflush(stdout);

            /*Khởi động lại biến đếm*/
            ctrl_c_count = 0;
   }
}
/*
    Hàm xử lý tín hiệu đã hoàn tất -  khôi phục mặt nạ tín hiệu về
    trạng thái trước đó. Cho phép tiếp tục nhận tín hiệu kế tiếp
*/
    sigprocmask(SIG_SETMASK, &old_set, NULL);
}

// Hàm đón bắt và xử lý tín hiệu TSTP khi người dùng nhấn Ctrl-Z
void catch_suspend(int sig_num)
{
    sigset_t mask_set; /*Biến sử dụng để thiết lập mặt nạ tín hiệu*/
    sigset_t old_set; /*Biến sử dụng để lưu mặt nạ tín hiệu trước đó*/

    /*Đặt lại bẫy xử lý tín hiệu cho lần kế tiếp*/
    signal(SIGTSTP, catch_suspend);

    /*Khóa tất cả các tín hiệu khác khi ta đang xử ly tín hiệu TSTP*/
    sigfillset(&mask_set);
    sigprocmask(SIG_SETMASK, &mask_set, &old_set);

    /*In giá trị hiện hành của biến đếm*/
    printf("\n\nSo Far, '%d' Ctrl-C presses were counted\n\n", ctrl_c_count);

    fflush(stdout);

    /*Khôi phục lại mặt nạ - cho phép nhận các tín hiệu tiếp theo*/
    sigprocmask(SIG_SETMASK, &old_set, NULL);
}

int main()
{

    /*Đặt bẫy đón bắt tín hiệu khi người dùng nhấn Ctrl-C và Ctrl-Z*/
    signal(SIGINT, catch_int);
    signal(SIGTSTP, catch_suspend);

    printf("Please random press Ctrl-C or Ctrl-Z");
    /*Lặp - chờ nhận tín hiệu*/
    while(1){
        sleep(1);
    }
    return 0;
}