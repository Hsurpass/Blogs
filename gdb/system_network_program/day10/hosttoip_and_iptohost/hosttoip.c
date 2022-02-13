#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>

#if 0
int main02()
{
    char buf[1024];
    int i = 0;
    char ip[INET_ADDRSTRLEN] = "180.101.49.12";
    struct hostent *hent;
    
    hent = gethostbyaddr(ip,sizeof(ip),AF_INET);
    if (hent != NULL)
    {
        printf("h_name:%s\n", hent->h_name);

        i = 0;
        while (hent->h_aliases[i] != NULL)
        {
            printf("alias:%s\n", hent->h_aliases[i] );
            i++;
        }
        printf("hostaddrtype:%d\n",hent->h_addrtype);
        printf("hostlength:%d\n",hent->h_length);
        i = 0;
        while (hent->h_addr_list[i] != NULL)
        {
            printf("addr_list:%s\n", inet_ntop(AF_INET,hent->h_addr_list[i],buf,sizeof(buf)) );
            i++;
        }
        
    }
    
    return 0;
}
#endif

int main()
{
    char buf[INET_ADDRSTRLEN];
    const char *hostname = "www.baidu.com";
    struct hostent *hent;
    hent = gethostbyname(hostname);
    int i = 0;
    if (hent != NULL)
    {
        printf("h_name:%s\n", hent->h_name);

        i = 0;
        while (hent->h_aliases[i] != NULL)
        {
            printf("alias:%s\n", hent->h_aliases[i] );
            i++;
        }
        printf("hostaddrtype:%d\n",hent->h_addrtype);
        printf("hostlength:%d\n",hent->h_length);
        i = 0;
        while (hent->h_addr_list[i] != NULL)
        {
            printf("addr_list:%s\n", inet_ntop(AF_INET,hent->h_addr_list[i],buf,sizeof(buf)) );
            i++;
        }
        
    }
    return 0;
}

