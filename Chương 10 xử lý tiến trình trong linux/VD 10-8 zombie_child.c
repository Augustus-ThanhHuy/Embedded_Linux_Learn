#include <sys/types.h> 
#include <unistd.h> 
#include <stdio.h>

int main(){
    pid_t child_id;
    int i;
    printf("Starting process \n");

    child_id=fork();
    switch (child_id)
    {
    case -1:
        printf("fork error");
        break;
    case 0:
        for(i=0; i<10;i++){
            printf("from child: %d\n",i);
            sleep(1);
        }
    exit(0);
    default:
        printf("parent exited \n");
    }


    return 0;
}