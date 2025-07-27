#include <sys/types.h> 
#include <unistd.h> 
#include <sys/wait.h> 
#include <stdio.h>

int main()
{
    pid_t child_id;

    printf("Starting process \n");

    child_id=fork();
    switch (child_id)
    {
    case -1:
        printf("Fork error");
        break;
    case 0:
        execlp("ps", "ps", "-af", 0);

    default:
        wait(0);
        printf("from parent: child finished \n");
    }

    return 0;
}