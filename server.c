#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

#define SERVER_PORT 10000
#define BUFF_LEN 1024

typedef struct Os_lxCanMessage_Tag
{
    uint32_t                messageId;                   /**< \brief ID, Identifier */
    uint32_t                messageIdLength;             /**< \brief XTD, Message Id length (Standard / Extended) */
    uint32_t                dataLengthCode;              /**< \brief DLC, Data Length Code */
    uint64_t                data;
}Os_lxCanMessage;

void handle_udp_msg(int fd)
{
    char buf[BUFF_LEN];                                 //接收缓冲区，1024字节
    int count;
    int times_ = 0;

    socklen_t len;
    Os_lxCanMessage lxMessage;
    struct sockaddr_in clent_addr;                      //clent_addr用于记录发送方的地址信息

    memset(&lxMessage, 0, sizeof(lxMessage));

    while(1)
    {
        times_++;

        memset(buf, 0, BUFF_LEN);
        len = sizeof(clent_addr);
        count = recvfrom(fd, buf, BUFF_LEN, 0, (struct sockaddr*)&clent_addr, &len);  //recvfrom是拥塞函数，没有数据就一直拥塞

        if(count == -1)
        {
            printf("recieve data fail!\n");
            return;
        }

        memcpy(&lxMessage, buf,sizeof(lxMessage));

        printf("*****************************************\n");
        printf("recieve data of client times : %d\n",times_);
        printf("lxMessage.messageId: \t\t%d\nlxMessage.messageIdLength: \t%d\nlxMessage.dataLengthCode: \t%d\nlxMessage.data: \t\t%ld\n"
                ,lxMessage.messageId,lxMessage.messageIdLength,lxMessage.dataLengthCode,lxMessage.data);
    }
}


/*
    server:
            socket-->bind-->recvfrom-->sendto-->close
*/

int main(int argc, char* argv[])
{
    int server_fd, ret;
    struct sockaddr_in ser_addr;

    server_fd = socket(AF_INET, SOCK_DGRAM, 0); //AF_INET:IPV4;SOCK_DGRAM:UDP
    if(server_fd < 0)
    {
        printf("create socket fail!\n");
        return -1;
    }

    memset(&ser_addr, 0, sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_addr.s_addr = INADDR_ANY; //IP地址，需要进行网络序转换，INADDR_ANY：所有本地地址
    ser_addr.sin_port = htons(SERVER_PORT);  //端口号，需要网络序转换

    ret = bind(server_fd, (struct sockaddr*)&ser_addr, sizeof(ser_addr));
    if(ret < 0)
    {
        printf("socket bind fail!\n");
        return -1;
    }

    handle_udp_msg(server_fd);   //处理接收到的数据

    close(server_fd);
    return 0;
}