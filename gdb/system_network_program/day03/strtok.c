#include <stdio.h>
#include <string.h>

int main()
{
    char buf[32];
    memset(buf,'1',sizeof(buf));

    char p[] = "aaaaa@bbbbbbbbbbbb@ccccccccccc@ddddddddd";
    char *ptmp = strtok(p,"@");
    // strcpy(buf,ptmp);
    // printf("buf=%s,sizeof(buf)=%ld,len=%ld\n",buf,sizeof(buf),strlen(buf));
    printf("buf=%s,sizeof(buf)=%ld,len=%ld\n",ptmp,sizeof(ptmp),strlen(ptmp));

    return 0;
}