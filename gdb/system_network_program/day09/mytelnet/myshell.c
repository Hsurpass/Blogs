#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

#define MAXBUF 1024

int main()
{
    char buf[MAXBUF];
    char cwd_buf[MAXBUF];
    char *pcwd;
    char *phome;
    memset(buf,0x31,sizeof(buf)); 
    memset(cwd_buf,0x31,sizeof(cwd_buf));  
    int ret = 0;
    char* arg[10];
    int n = 0;
    while (1)
    {
        pcwd = getcwd(cwd_buf,sizeof(cwd_buf));
        phome = getenv("HOME");
        if(strncmp(pcwd,phome,strlen(phome)) == 0)//???? \n dangji
        {
            printf("%s@ubuntu:~%s$ ",getenv("USER"),cwd_buf+strlen(phome));
        }
        else
        {
            printf("%s@ubuntu:%s$ ",getenv("USER"),getcwd(NULL,0));
        }
        fflush(stdout);

        ret = read(STDIN_FILENO,buf,sizeof(buf));
        if (ret == -1)
        {
            perror("read");
        }
        
        buf[ret-1] = '\0';
        if(strlen(buf) == 0)
        {
            continue;
        }
        n=0;
        arg[0] = strtok(buf," ");
        while (arg[++n] = strtok(NULL," "));
        // printf("n = %d,sizeof(arg)/sizeof(arg[0]) = %ld\n",n,sizeof(arg)/sizeof(arg[0]));
        // for (size_t i = 0; i <= n; i++)
        // {
        //     printf("arg[%ld] = %s\n",i,arg[i]);
        // }
            // if (arg[0] == NULL) 
            // {
            //     continue;
            // }
        
        if (strcmp(arg[0],"cd") == 0)
        {
            if(n == 2)
            {
                chdir(arg[1]);
            }
            else if (n == 1)
            {
                chdir(getenv("HOME"));
            }
            continue;
        }
        else if (strcmp(arg[0],"exit") == 0 && n == 1)
        {
            exit(2);
        }
        

        pid_t pid = fork();
        if (pid == 0)
        {
            // printf("child process, pid = %d\n",getpid());
            ret = execvp(arg[0],arg);
            if(-1 == ret)
            {
                perror("execvp");
            }
            exit(1);
        }
        else if (pid > 0)
        {
            pid_t childpid = wait(NULL);
            //printf("parent process, ppid = %d,childpid = %d\n",getpid(), childpid);
            // exit(0);
        }
        else
        {
            perror("fork");
        }
    
    }
    
    return 0;
}