#pragma comment(lib, "ws2_32.lib")
#define PORT 5000

class SocketServer
{
private:
    int port;
    WSADATA wsaData;
    SOCKET sListen, sAccept;
    struct sockaddr_in server, client;                                       //服务器、客户的地址
public:
    SocketServer() {
        this->port = PORT;
    }

    bool initServer();
    bool listen();
    bool communication();
    bool clearSocket();
};