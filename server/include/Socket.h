#ifndef __SOCKET__
#define __SOCKET__
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include "message.h"

#define BUFF_LEN 1024

using namespace std;

class Socket
{
public:
    Socket(uint16_t pot);
    void Socket_init();
    void Socket_recv();
    
public:
    char buf[BUFF_LEN];                     //接收缓冲区，1024字节
    int m_server_fd , count; 
    // int SERVER_PORT;  
    uint16_t SERVER_PORT;                 
                    
    struct sockaddr_in m_ser_addr;
    struct sockaddr_in clent_addr;          //clent_addr用于记录发送方的地址信息
    socklen_t len_;

    Os_lxCanMessage lxMessage;
};

#endif