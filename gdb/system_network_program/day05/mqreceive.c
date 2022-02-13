#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* mq_filename = "/mymqueue";
int main()
{
    mqd_t mqd = mq_open(mq_filename, O_RDWR | O_CREAT,0664,NULL);
    if (-1 == mqd)
    {
        perror("mq_open");
        _exit(0);
    }
    printf("create mqueue success\n");
    int ret = 0;
    //char buf[32];
    int count=0;
    // memset(buf,0x31,sizeof(buf));
    struct mq_attr mqattr;
    // mqattr.mq_flags = O_NONBLOCK;
    // mq_setattr(mqd,&mqattr,NULL);
    mq_getattr(mqd,&mqattr);
    printf("nonblock flag:%ld\n",mqattr.mq_flags);
    printf("max msgs: %ld\n",mqattr.mq_maxmsg);
    printf("max msg size: %ld\n",mqattr.mq_msgsize);
    printf("current msg count: %ld\n",mqattr.mq_curmsgs);
    printf("--------------------------------------\n");
    char *buf = (char*)malloc(mqattr.mq_msgsize);
    unsigned int msgprio;
    while (1)
    {
        ret = mq_receive(mqd,buf,mqattr.mq_msgsize,&msgprio);
        if (-1 == ret)
        {
            perror("mq_send");
            exit(1);
        }
        printf("receive: buf = %s,ret = %d,msg prio = %d\n",buf,ret,msgprio);
        sleep(1);
    }
    
    mq_close(mqd);
    mq_unlink(mq_filename);

    return 0;
}