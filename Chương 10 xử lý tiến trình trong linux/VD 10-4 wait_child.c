#include <sys/types.h>
#include <unistd.h> /* Khai báo sử dụng fork(), và pid_t */
#include <sys/wait.h> /* Khai báo sử dụng wait() */

int main(){
	int
	pid_t child_pid;
	int child_status;
	int n;
	printf("fork program starting\n");

	child_pid = fork();
	
	switch (child_pid) {
		case -1:
			perror("Fork error ");
			exit(1);
			
		case 0:
			message = "This is the child";
			n = 5;
			for(; n > 0; n--){
				printf("%s", message);
				sleep(1);
			}
			exit(37);
			
		default:
			printf("We are in parent. wait for child finish \n");
			/* Chờ tiến trình con kết thúc*/
			wait(&child_status);
			printf("Parent - child finished \n");
		}
		
		return 0;
}