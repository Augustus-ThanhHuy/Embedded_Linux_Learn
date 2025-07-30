#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void catch_int(int sig_num)
{
    //khôi phục lại bộ xử lý tín hiệu để có thể bẫy lại tín hiệu trong lần kế tiếp
    signal(SIGINT, catch_int);
    printf("Don't press Ctrl-C to stop me\n");
}

int main(int argc, char* argv[])
{
    int count = 0;

    //Thiết lập hàm xử lý cho tín hiệu INT (Ctrl-C)
    signal(SIGINT, catch_int);

    /*
    signal(SIGINT, SIG_IGN); // Bỏ qua Ctrl+C
    */

    /*
    signal(SIGINT, SIG_DFL); // Bỏ qua Ctrl+C
    */
    while(1){
        printf("Process is calculating ...%d\n", count++);
        sleep(1);
    }
}