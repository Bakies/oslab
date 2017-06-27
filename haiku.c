#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

int main() { 
	struct sockaddr_in serv_addr;
	// TODO make this a haiku
	char haiku[] = "This is a test";
	char sendBuff[1024];
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	int connfd = 0;

	memset(&serv_addr, '0', sizeof(serv_addr));
	memset(sendBuff, '0', sizeof(sendBuff));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(5000);
	
	bind(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	listen(sock, 10);

	while (1) {
		connfd = accept(sock, (struct sockaddr*)NULL, NULL);
		snprintf(sendBuff, sizeof(sendBuff), "%s\r\n", haiku);
		write(connfd, sendBuff, strlen(sendBuff));

		close(connfd);
	}
	return 0;
}
