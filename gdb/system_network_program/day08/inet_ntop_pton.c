#include <stdio.h>
#include <arpa/inet.h>

int main()
{
    char buf[] = "192.168.1.255";
    unsigned int n_ip; 
    inet_pton(AF_INET,buf,&n_ip);
    printf("buf = %s,n_ip = %x\n",buf,n_ip);

    char ip[16];
    inet_ntop(AF_INET,&n_ip,ip,sizeof(ip));
    printf("ip = %s,n_ip = %x\n",ip,n_ip);

    printf("htonl = %x\n",htonl(n_ip));  
    printf("ntohl = %x\n",ntohl(n_ip) );  
    return 0;
}
