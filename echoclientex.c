#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include<string.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <malloc.h>
#include <assert.h>
 
int main(int argc,char **argv)
{
    int sockfd,n;
    char sendline[100];
    char recvline[100];
    struct sockaddr_in servaddr;
 
	FILE* fp = NULL;
	size_t size = 0, cnt = 0;
	char* buf;

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr,sizeof servaddr);
 
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(22000);
 
    inet_pton(AF_INET,"127.0.0.1",&(servaddr.sin_addr));
 
    connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
 
	fp = fopen("test1", "wb");
	ntohl(size);
	recv(sockfd, &size, sizeof(size), 0);
	printf("size  : %d", size);
	
	buf = (char*)malloc(size + 1);
	assert(buf != NULL);

	cnt = recv(sockfd, buf, size, 0);
	fwrite(buf, sizeof(char), cnt, fp);

	fclose(fp);
	free(buf);
	close(sockfd);
}
