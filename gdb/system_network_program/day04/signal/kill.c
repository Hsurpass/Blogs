#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

int main(int argc,char ** argv)
{
    if (argc != 3)
    {
        printf("usage:%s signal pid\n",argv[0]);
    }
    
    kill(atoi(argv[2]),atoi(argv[1])); 

    return 0;
}