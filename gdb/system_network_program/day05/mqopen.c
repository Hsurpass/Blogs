#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

int main()
{
    mqd_t mqd = mq_open("/mymqueue",O_CREAT,0664,NULL);
    if (-1 == mqd)
    {
        perror("mq_open");
        _exit(0);
    }

    printf("create mqueue success\n");

    struct mq_attr mqattr;
    int ret = 0;
    ret = mq_getattr(mqd,&mqattr);
    if (-1 == ret)
    {
        perror("mq_getattr");
    }
    printf("nonblock flag:%ld\n",mqattr.mq_flags);
    printf("max msgs: %ld\n",mqattr.mq_maxmsg);
    printf("max msg size: %ld\n",mqattr.mq_msgsize);
    printf("current msg count: %ld\n",mqattr.mq_curmsgs);
    printf("--------------------------------------\n");

    mqattr.mq_maxmsg = 8;
    mqattr.mq_msgsize = 1024;
    mqattr.mq_flags = O_NONBLOCK;
    mq_setattr(mqd,&mqattr,NULL);

    printf("nonblock flag:%ld\n",mqattr.mq_flags);
    printf("max msgs: %ld\n",mqattr.mq_maxmsg);
    printf("max msg size: %ld\n",mqattr.mq_msgsize);
    printf("current msg count: %ld\n",mqattr.mq_curmsgs);

    mq_close(mqd);
    mq_unlink("/mymqueue");

    return 0;
}