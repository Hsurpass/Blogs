#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc,char **argv)
{
    if(argc < 2)
    {
        printf("usage:%s [filename]\n",argv[0]);
    }
    if(access(argv[1],F_OK | W_OK | R_OK|X_OK) == 0)
    {
        printf("access F_OK exist\n");
    }
    else
    {
        printf("not exist\n");
    }   
    


    return 0;
}