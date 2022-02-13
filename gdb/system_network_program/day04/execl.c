#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(int argc,char **argv,char **env)
{
    int ret = execle("/bin/ls","ls","-l","-a",NULL,env);
    if(-1 == ret)
    {
        perror("execl");
    }
    printf("hello\n");
    return 0;
}
