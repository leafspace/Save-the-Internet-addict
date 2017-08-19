#include "stdafx.h"
#include "SocketLink.h"

bool SocketLink::initSocket(string ip)
{
	this->targetIP = ip;
    if (WSAStartup(MAKEWORD(2, 2), &this->wsaData) != 0) {
		return false;
    }

	int nNetTimeout = 500;
	setsockopt(this->client, SOL_SOCKET, SO_SNDTIMEO, (char *)&nNetTimeout, sizeof(int));
	setsockopt(this->client, SOL_SOCKET, SO_RCVTIMEO, (char *)&nNetTimeout, sizeof(int));

    //需要连接的服务器地址信息
	this->server.sin_family = AF_INET;                                       //需要连接的服务器的地址信息
	this->server.sin_addr.s_addr = inet_addr(ip.data());                     //将命令行的IP地址转换为二进制表示的网络字节顺序IP地址
    this->server.sin_port = htons(this->port);
    
    this->client = socket(AF_INET, SOCK_STREAM, 0);                          //建立客户端流套接字
    if (this->client == INVALID_SOCKET) {
		return false;
    }

    return true;
}

bool SocketLink::linkServer(void)
{
    if (connect(this->client, (struct sockaddr*)&this->server, sizeof(this->server)) == INVALID_SOCKET) {
		return false;
	}
	return true;
}

bool SocketLink::sendOrders(string orders)
{
    int msgLen;
    if ((msgLen = send(this->client, orders.data(), strlen(orders.data()), 0)) == SOCKET_ERROR) {
        return false;
    }
	return true;
}

void SocketLink::freeSocket(void)
{
    closesocket(this->client);
	WSACleanup();
}
