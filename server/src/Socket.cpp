#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <cstring>
#include "Socket.h"
#include "message.h"

// #define SERVER_PORT 10000

using namespace std;

Socket::Socket(uint16_t pot)
{
    m_server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(m_server_fd < 0)
    {
        while(true)
        cout<<"create socket fail!"<<endl;
    }
    else
        cout<<"socket create OK!"<<endl;
    
    SERVER_PORT = pot;

    memset(&lxMessage, 0, sizeof(lxMessage));
    memset(&m_ser_addr, 0, sizeof(m_ser_addr));
    memset(buf, 0, BUFF_LEN);
}

void Socket::Socket_init()
{
    m_ser_addr.sin_family = AF_INET;
    m_ser_addr.sin_addr.s_addr = INADDR_ANY; //IP地址，需要进行网络序转换，INADDR_ANY：所有本地地址
    m_ser_addr.sin_port = htons(SERVER_PORT);  //端口号，需要网络序转换

    int ret = bind(m_server_fd, (struct sockaddr*)&m_ser_addr, sizeof(m_ser_addr));
    if (ret < 0)
    {
        while(true)
        cout<<"socket bind fail!"<<endl;
    }
    else
        cout<<"socket bind OK!"<<endl; 
}

void Socket::Socket_recv()
{
    while(true)
    {
        memset(buf, 0, BUFF_LEN);

        len_ = sizeof(clent_addr);
        count = recvfrom(m_server_fd, buf, BUFF_LEN, 0, (struct sockaddr*)&clent_addr, &len_);  //recvfrom是拥塞函数，没有数据就一直拥塞
        if(count != -1)
            cout<<"recieve data ready!"<<endl;
        else
        {
            cout<<"recieve data fail!"<<endl;
            return;
        }

        memcpy(&lxMessage, buf,sizeof(lxMessage));

        cout<<"*****************************************"<<endl;
        cout<<"recieve data of client times : "<<times_<<endl;
        cout<<"lxMessage.messageId: \t\t"<<lxMessage.messageId<<endl;
        cout<<"lxMessage.messageIdLength: \t"<<lxMessage.messageIdLength<<endl;
        cout<<"lxMessage.dataLengthCode: \t"<<lxMessage.dataLengthCode<<endl;
        cout<<"lxMessage.data: \t\t"<<lxMessage.data<<endl;

        times_++;
    }
}