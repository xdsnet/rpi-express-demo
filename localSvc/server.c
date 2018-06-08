#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <string.h>
#include <wiringPi.h>

#define MAXLINE 1024
// 定义LED灯的GPIO管脚

#define LEDpin 1

int setLEDon(void){ // 定义亮灯处理
	//digitalWrite(LEDpin,HIGH); 
	return HIGH;
}

int setLEDoff(void){ // 定义灭灯处理
	//digitalWrite(LEDpin,LOW); 
	return LOW;
}

int getLED( int flag ){ // 获取灯状态值
	return flag;
}

int main(int argc,char **argv)
{
	int listenfd,connfd;
	struct sockaddr_in sockaddr;
	char buff[ MAXLINE ];
	char sendMsg[ MAXLINE ];
	int n;
	int LEDflag=0;  // LED等状态标志 HIGH 亮灯，LOW 灭灯
	char *LEDON="on";
	char *LEDOFF="off";
	char *GETSTR="getLed";
/* // 涉及硬件的实现部分 先调通服务程序，后面调试添加
	if(-1 == wiringPiSetup() ){
		// 如果不能正确初始化则服务退出
		printf( "Err: init wiring Error!" );
		exit( -1 );
	}
	// 初始化LED所接管脚状态
    pinMode(LEDpin,OUTPUT);  
//*/
	memset(&sockaddr,0,sizeof(sockaddr));
    
        sockaddr.sin_family = AF_INET;
        sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        sockaddr.sin_port = htons(10004);

	listenfd = socket(AF_INET,SOCK_STREAM,0);
	
	bind(listenfd,(struct sockaddr *) &sockaddr,sizeof(sockaddr));
    
	listen(listenfd,1024);

    
	printf("Please wait for the client information\n");

	for(;;)
	{
		if((connfd = accept(listenfd,(struct sockaddr*)NULL,NULL))==-1)
		{
			printf("accpet socket error: %s errno :%d\n",strerror(errno),errno);
			continue;
		}
		
		n = recv(connfd,buff,MAXLINE,0); // 获取客户端传来的消息
		buff[n] = '\0';
		if(strcmp(buff,LEDON)){
			LEDflag=setLEDon();
			sprintf(sendMsg,"setLEDON&LEDFLAG=%d",LEDflag);
		}else if(strcmp(buff,LEDOFF)){
			LEDflag=setLEDoff();
			sprintf(sendMsg,"setLEDOFF&LEDFLAG=%d",LEDflag);
		}else if(strcmp(buff,GETSTR)){
			LEDflag=getLED( LEDflag );
			sprintf(sendMsg,"getLED&LEDFLAG=%d",LEDflag);
		}else{
			sprintf(sendMsg,"getMsg=%s&LEDFLAG=%d",buff,LEDflag);
		}
		printf("recv msg from client:%s and sedMsg:%s",buff, sendMsg);
		if((send(connfd,sendMsg,strlen(sendMsg),0)) < 0){
			printf("send mes error: %s errno : %d",strerror(errno),errno);
			exit(0);
		}
		//send();// 向客户端返回消息
		close(connfd);
	}
	close(listenfd);
}
