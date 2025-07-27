#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	pid_t pid;
	char *message;
	int n;
	printf("fork program starting\n");
	pid = fork();
	
	switch(pid)
	{
		case -1:
			perror("Can not call fork");
			exit(1);
		case 0:
			message = "This is the child";
			n = 0;
			for(; n < 5; n++){
				printf("%s", message);
				sleep(1);
			}
			break;
		default:
			message = "This is the parent";
			n = 0;
			for(;n < 3; n++){
				printf("%s", message);
				sleep(1);
			}
			break;
	}
	exit(0);
}