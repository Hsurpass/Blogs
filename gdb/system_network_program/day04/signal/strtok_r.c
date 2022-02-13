#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

char buf0[] = "1 2 3 4 5 6";
char buf1[] = "a b c d e f";

void sighandle(int sig)
{
    char *p,*psave;
    p = strtok_r(buf1," ",&psave); 
    while (p)
    {
        printf("%s\n",p);
        p = strtok_r(psave," ",&psave);
        sleep(1);
    }
}
int main()
{
    signal(SIGINT,sighandle);
    char *p,*psave;
    p = strtok_r(buf0," ",&psave);
    while (p)
    {
        printf("%s\n",p);
        p = strtok_r(psave," ",&psave);
        sleep(1);
    }
    return 0;
}

// void sighandle(int sig)
// {
//     char *p = strtok(buf1," "); 
// }
// int main()
// {
//     signal(SIGINT,sighandle);
//     char *p = strtok(buf0," ");
//     while (p)
//     {
//         printf("%s\n",p);
//         p = strtok(NULL," ");
//         sleep(1);
//     }
//     return 0;
// }