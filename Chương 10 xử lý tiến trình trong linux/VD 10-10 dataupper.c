#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    char *filename;

    if(argc != 2){
        fprintf(stderr, "usage: useupper file\n");
        exit(1);
    }

    filename = argv[1];
    if(!freopen(filename, "r", stdin)){
        fprintf(stderr, "could not redirect stdin to file %s\n", filename);
        exit(2);
    }

    execl("./upper", "upper", 0);
    fprintf(stderr, "could not exec upper!\n");
    exit(3);
}