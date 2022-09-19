#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h> 
#include <arpa/inet.h>
#include <unistd.h>
 
int main(void)
{
	int client_sockfd;
	int len;
	struct sockaddr_in remote_addr; //服务器端网络地址结构体
	char buf[BUFSIZ];  //数据传送的缓冲区
	memset(&remote_addr,0,sizeof(remote_addr)); //清零
	remote_addr.sin_family=AF_INET; //设置为IP通信
	remote_addr.sin_addr.s_addr=inet_addr("127.0.0.1");//服务器IP地址
	remote_addr.sin_port=htons(8192); //服务器端口号
	
	/*创建客户端套接字--IPv4协议，面向连接通信，TCP协议*/
	if((client_sockfd=socket(PF_INET,SOCK_STREAM,0))<0)
	{
		perror("socket error");
		return -1;
	}
	
	/*将套接字绑定到服务器的网络地址上*/
	if(connect(client_sockfd,(struct sockaddr *)&remote_addr,sizeof(struct sockaddr))<0)
	{
		perror("connect error");
		return -1;
	}
	printf("connected to server\n");
	len=recv(client_sockfd,buf,BUFSIZ,0);//接收服务器端信息
        buf[len]='/0';
	printf("%s",buf); //打印服务器端信息
	
	while(1)
	{
		printf("Enter string to send:");
		scanf("%s",buf);
		if(!strcmp(buf,"exit"))
			break;
		len=send(client_sockfd,buf,strlen(buf),0);
		len=recv(client_sockfd,buf,BUFSIZ,0);
		buf[len]='\0';
		printf("received:%s\n",buf);
	}
	
	/*关闭套接字*/
	close(client_sockfd);
    
	return 0;
}