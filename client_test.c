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
// #define SERVER_IP "192.168.1.15"
#define SERVER_IP "127.0.0.1"

typedef struct Os_lxCanMessage_Tag
{
    uint32_t                messageId;                   /**< \brief ID, Identifier */
    uint32_t                messageIdLength;             /**< \brief XTD, Message Id length (Standard / Extended) */
    uint32_t                dataLengthCode;              /**< \brief DLC, Data Length Code */
    uint64_t                data;
}Os_lxCanMessage;

void udp_msg_sender(int fd, struct sockaddr* dst)
{
    Os_lxCanMessage lxMessage;
    socklen_t len;

    memset(&lxMessage, 0, sizeof(lxMessage));
    lxMessage.messageId = 123;
    lxMessage.messageIdLength = 88;
    lxMessage.dataLengthCode = 1024;
    lxMessage.data = 13579;

    while(1)
    {
        len = sizeof(*dst);
        sendto(fd, &lxMessage, BUFF_LEN, 0, dst, len);           //Os_lxCanMessage_Tag
        sleep(1);
    }
}

/*
    client:
            socket-->sendto-->revcfrom-->close
*/

int main(int argc, char* argv[])
{
    int client_fd;
    struct sockaddr_in ser_addr;

    client_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(client_fd < 0)
    {
        printf("create socket fail!\n");
        return -1;
    }

    memset(&ser_addr, 0, sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    // ser_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);               //注意网络序转换
    ser_addr.sin_port = htons(SERVER_PORT);                     //PORT

    udp_msg_sender(client_fd, (struct sockaddr*)&ser_addr);

    close(client_fd);

    return 0;
}
