#include <sys/types.h>
#include <unistd.h> /* Khai báo sử dụng fork(), và pid_t */
#include <sys/wait.h> /* Khai báo sử dụng wait() */
#include <stdio.h>

int main()
{
	char *message;
	int n;

	pid_t child_pid;
	int child_status;
/* Nhân bản tiến trình, tạo bản sao mới */
	child_pid = fork();
	
/* Kiểm tra xem đang ở tiến trình con hay tiến trình cha */
	switch (child_pid) {
		case -1:
			perror("fork fail ");
			exit(1);
			
		case 0:
			printf("hello world from child \n");
			n = 0;
			for (;n < 3; n++){
				printf("This is the child");
				sleep(1);
			}
			exit(0);
		default:
			message = "This is the parent";
			n = 3;
			for(; n > 0; n--){
				printf("%s", message);
				sleep(1);
			}
		/* Chờ tiến trình con kết thúc*/
			child_pid = wait(&child_status);
			
		/* Kiểm tra và in ra mã lỗi trả về của tiến trình con */
		printf("Child has finished: PID = %d\n", child_pid);
		
				if(WIFEXITED(child_status))
					printf("Child exited with code %d\n", WEXITSTATUS(child_status));
				else
					printf("Child terminated abnormally\n");
					
				break;
		}
		exit(0);
	}
return 0;
}