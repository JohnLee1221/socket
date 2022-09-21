#include <iostream>
#include <cstring>
#include "message.h"
#include "Socket.h"

#define SERVER_PORT 10000               //设置端口号

using namespace std;


int main()
{
    Socket s1(SERVER_PORT);
    s1.Socket_init();
    s1.Socket_recv();

    return 0;
}