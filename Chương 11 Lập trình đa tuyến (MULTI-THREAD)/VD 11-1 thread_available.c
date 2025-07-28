#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){

    printf("POSIX version is set to %ld\n", _POSIX_VERSION);
    if (_POSIX_VERSION < 199506L){
        
        if(_POSIX_C_SOURCE >= 199506L){
            printf("This system does not support thread!\n");
        }
        else {
            printf("Try with-D_POSIX_C_SOURCE=199506L\n");
        }
    }
    else {
        printf("Thread is available in this system");

        #ifdef _POSIX_THREAD_PRIORITY_SCHEDULING
            printf("With scheduling support");
        #else
            printf("but no scheduling support");
        #endif
    }

    return 0;
}