#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
int main(int argc, char** argv)
{
	struct sockaddr_in sin;
	char buf[16];
	memset(&sin, 0, sizeof(sin));
	sin.sin_family=AF_INET;
	sin.sin_port=htons(3001);
	inet_pton(AF_INET, "192.168.1.111", &sin.sin_addr.s_addr);
	printf("%s\n", inet_ntop(AF_INET, &sin.sin_addr, buf, sizeof(buf)));
	return 0;
}
