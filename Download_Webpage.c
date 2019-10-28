#include<stdio.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include <netdb.h>
#include<unistd.h>
int main(int argc,char *argv[]) {
   int sockfd, portno, n,i=0,flag=0;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[4096];
    FILE *fp = fopen("downloaded_webpage.html","w+");
    char *host = "www.google.com";
    portno = 80;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        perror("ERROR opening socket");
    server = gethostbyname(host);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) perror("ERROR connecting");
    const char * header = "GET /index.html HTTP/1.1\r\nHost: www.google.com\r\nConnection: close\r\n\r\n";
    send(sockfd,header,strlen(header),0);
while (1) {
	        bzero(buffer,4096);
		n = recv(sockfd,buffer,4095, 0);
		if (n <= 0) {
		    perror("Reached End of file");
		    break;
		}
		if (n == 0) {
		    break;
		}
		if(buffer!=NULL)
		{
			fprintf(fp,"%s\n",buffer);
		}
}
    close(sockfd);
    fclose(fp);
    return 0;
}
