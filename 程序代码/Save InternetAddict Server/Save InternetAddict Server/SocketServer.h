#pragma once
#pragma comment(lib, "ws2_32.lib")
#define PORT 5000

#include <winsock.h>
#include "SystemAction.h"

class SocketServer
{
private:
    int port;
    char* message;
    WSADATA wsaData;
    SOCKET sListen, sAccept;
    struct sockaddr_in server, client;                                       //服务器、客户的地址

    void systemProcess(int msgLen);
public:
    SocketServer() {
        this->port = PORT;
        this->message = new char[500];
    }

    bool initServer();
    bool listen();
    bool communication();
    bool clearSocket();
};