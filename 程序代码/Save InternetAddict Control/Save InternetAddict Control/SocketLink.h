#pragma once
#pragma  comment(lib,"ws2_32.lib")
#define PORT 5000

#include <string>
#include <winsock.h>

using namespace std;

class SocketLink
{
private:
    int port;
    SOCKET client;
    WSADATA wsaData;
    struct sockaddr_in server;                                               //服务器端地址

public:
    SocketLink() {
        this->port = PORT;
    }

    bool initSocket(string ip);
    bool linkServer(void);
    bool sendOrders(string orders);
    void freeSocket(void);
};
