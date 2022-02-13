#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
    char cwd_buf[512];
    char env_buf[512];
    memset(cwd_buf,0x31,sizeof(cwd_buf));
    memset(env_buf,0x31,sizeof(env_buf));
    char *pcwd;
    char *penv;

    pcwd = getcwd(cwd_buf,sizeof(cwd_buf));
    // int len1 = strlen(pcwd);
    // pcwd[len1]='\n';
    // int len2 = strlen(cwd_buf);
    // cwd_buf[len2] = '\n';
    penv = getenv("HOME");
    // strcpy(env_buf,penv);
    // int len_env = strlen(penv);
    // env_buf[len_env] = '\n';

    printf("cwd_buf = %s,strlen(cwd_buf)=%ld\n",cwd_buf,strlen(cwd_buf));
    printf("pcwd = %s,strlen(pcwd)=%ld\n",pcwd,strlen(pcwd));
    printf("env = %s lenenv = %ld\n",penv,strlen(penv));

    return 0;
}