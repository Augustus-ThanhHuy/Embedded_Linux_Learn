#include <sys/types.h> /* Khai báo pid_t, ... */
#include <unistd.h> /* Khai báo sử dụng fork(), và pid_t */
#include <sys/wait.h> /* Khai báo sử dụng wait() */
#include <stdio.h>
#include <signal.h> /* Khai báo sử dụng hàm signal() */

/* Cài đặt hàm xử lý tín hiệu */
void catch_child(int sig_num)
{
/* Khi hàm này được gọi ta biết chắc là tiến trình con đã kết thúc */
	int child_status;
/*
Lấy về trạng thái hay mã lỗi của tiến trình con. Trường hợp này wait() 
sẽ trở về ngay sau khi gọi với mã trạng thái của tiến trình con bởi vì
thật sự tiến trình con đã chấm dứt. 
*/
	wait(&child_status);
/* ... xử ý các tác vụ cần thiết ở đây */

/* Kết thúc */
	printf("from parent:child exited.\n");
}

int main()
{
	int child_pid;
	int i;
/* Cài đặt hàm xử lý tín hiệu gửi đến khi tiến trình con kết thúc */
	signal(SIGCHILD, catch_child);
	child_pid = fork();
	
	switch (child_pid)
	{
	 case -1: /* fork() bị lỗi*/
		 perror("fork fail");
		 exit(1);
	 case 0: /* Xử lý tiến trình con */
		 printf("from child: hello world\n");
		 sleep(1); /* Tạm dừng để thấy rõ sự hoạt động của tiến trình */
		 exit(0);
	 default:   /* Xử lý tiến trình cha*/
        /* Tiến trình cha tiếp tục xử lý công việc không cần đợi tiến trình con*/
        For(int i = 0; < 10; i++){
            printf("%d\n", i);
            sleep(1); /* Tạm dừng 1 giây */
        }
		 break;
	}
	return 0;
}