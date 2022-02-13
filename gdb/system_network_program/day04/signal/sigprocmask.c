#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

void print_signalset(sigset_t *sig_mask)
{
    int i = 0;
    for(i = 1;i < 32;i++)
    {
        if (sigismember(sig_mask,i) == 1)
        {
            putchar('1');
        }
        else
        {
            putchar('0');
        }
    }
    putchar(10);
}

int main()
{
    // printf("%ld\n",sizeof(sigset_t));
    sigset_t mask_set,pending_mask;
    sigemptyset(&mask_set);
    sigaddset(&mask_set,SIGINT);
    __sigaddset(&mask_set,SIGQUIT);

    sigprocmask(SIG_BLOCK,&mask_set,NULL);

    int count = 0;
    while (1)
    {
        sigpending(&pending_mask);
        print_signalset(&pending_mask);
        if (count++ == 10)
        {
            sigprocmask(SIG_UNBLOCK,&mask_set,NULL);
        }
        
        sleep(1);    
    }
    

    while (1)
    {
        sleep(1);
    }
    
    return 0;
}