/*socket tcp客户端*/
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define SERVER_PORT 5555

#define LINE_MAX 1024
#define CMDLEN 5

/*
 连接到服务器后，会不停循环，等待输入，
 输入quit后，断开与服务器的连接
 */

int main(){
    //客户端只需要一个套接字文件描述符，用于和服务器通信
	int clientSocket;
    //描述服务器的socket
	struct sockaddr_in serverAddr;
//	char sendbuf[ LINE_MAX ];
	char recvbuf[ LINE_MAX ];
	int iDataNum;
  int i;
	char *LED_ON = "on" ;
	char *LED_OFF = "off" ;
	char *KEY_GET = "get" ;
	char *CLOSE_MSG = "quit";
  char *cmd[ CMDLEN];
  cmd[0]=KEY_GET;
  cmd[1]=LED_ON;
  cmd[2]=LED_OFF;
  cmd[3]=KEY_GET;
  cmd[4]=CLOSE_MSG;
	if((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("socket");
		return 1;
	}

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);
    //指定服务器端的ip，本地测试：127.0.0.1
    //inet_addr()函数，将点分十进制IP转换成网络字节序IP
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	if(connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0){
		perror("connect");
		return 1;
	}

	printf("connect with destination host...\n");

  for( i=0; i<CMDLEN; i++){
		printf("Send cmd:%s:",cmd[i]);
		printf("\n");

		send(clientSocket, cmd[i] , strlen(cmd[i]), 0);
		if(strcmp( cmd[i], CLOSE_MSG) == 0)
			break;
		iDataNum = recv(clientSocket, recvbuf, 200, 0);
		recvbuf[iDataNum] = '\0';
		printf("recv data of my world is: %s\n", recvbuf);
	}
	close(clientSocket);
	return 0;
}
