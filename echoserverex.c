#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include<string.h>
#include <malloc.h>
#include <assert.h>

#include <netinet/in.h>
#include <arpa/inet.h>
 
int main()
{
 
    char str[100];
    int listen_fd, comm_fd;
 
    struct sockaddr_in servaddr;
	FILE* fp = NULL;
	size_t total_size = 0;
	size_t size = 0;
	char* buf = NULL;
 
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
 
    bzero( &servaddr, sizeof(servaddr));
 
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    servaddr.sin_port = htons(22000);
 
    bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));
 
    listen(listen_fd, 10);
 
    comm_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL);
 
    fp = fopen("test", "rb");
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	send(comm_fd, &size, sizeof(size), 0);
	
	buf = (char*)malloc(size + 1);
	assert(buf != NULL);
	fread(buf, sizeof(char), size, fp);
	printf("buf : %s\n",buf);
	send(comm_fd, buf, size, 0);
	
	free(buf);
	fclose(fp);
	close(comm_fd);
}
