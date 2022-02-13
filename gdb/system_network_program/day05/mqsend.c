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
    struct mq_attr mqattr;
    mqattr.mq_flags = 0;
    mqattr.mq_maxmsg = 8;
    mqattr.mq_msgsize = 1024;
    mqd_t mqd = mq_open(mq_filename, O_WRONLY | O_CREAT,0664,&mqattr);
    if (-1 == mqd)
    {
        perror("mq_open");
        _exit(0);
    }
    printf("create mqueue success\n");
    // mqattr.mq_flags = O_NONBLOCK;
    // mq_setattr(mqd,&mqattr,NULL);
    printf("nonblock flag:%ld\n",mqattr.mq_flags);
    printf("max msgs: %ld\n",mqattr.mq_maxmsg);
    printf("max msg size: %ld\n",mqattr.mq_msgsize);
    printf("current msg count: %ld\n",mqattr.mq_curmsgs);
    printf("--------------------------------------\n");
    int ret = 0;char buf[32];int count=0;
    memset(buf,0x31,sizeof(buf));
    while (1)
    {
        sprintf(buf,"DATA%d",++count);
        ret = mq_send(mqd,buf,strlen(buf)+1,0);
        if (-1 == ret)
        {
            perror("mq_send");
            exit(1);
        }
        printf("send: buf = %s,ret = %d\n",buf,ret);
        sleep(1);
    }
    
    mq_close(mqd);
    mq_unlink(mq_filename);

    return 0;
}