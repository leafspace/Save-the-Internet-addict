#include "SocketServer.h"

bool SocketServer::initServer()
{
    if (WSAStartup(MAKEWORD(2, 2), &this->wsaData) != 0) {
        cout << "Error : Winsock load failed. " << endl;
		return false;
	}

	this->sListen = socket(AF_INET, SOCK_STREAM, 0);                         //创建套接字
	if (this->sListen == INVALID_SOCKET) {                                   //创建套接字失败
        cout << "Error : Socket failed (" << WSAGetLastError() << ")." << endl;
		return false;
	}

	this->server.sin_family = AF_INET;
	this->server.sin_port = htons(this->port);                               //把一个双字节主机字节顺序的数据转换为网络字节顺序
	this->server.sin_addr.s_addr = htonl(INADDR_ANY);                        //把四字节主机字节顺序转换为网络字节顺序，INADDR_ANY为系统指定的IP地址

	if (bind(this->sListen, (LPSOCKADDR)&this->server, sizeof(this->server)) == SOCKET_ERROR) {
        cout << "Error : Bind failed (" << WSAGetLastError() << ")." << endl;
		return false;
    }
    
    return true;
}

bool SocketServer::listen()
{
    if (listen(this->sListen, 5) == SOCKET_ERROR) {
        cout << "Error : Listen failed (" << WSAGetLastError() << ")." << endl;
		return false;
	}
}

bool SocketServer::communication()
{
    int iLen = sizeof(this->client);
    while (true) {
        this->sAccept = accept(this->sListen, (struct sockaddr*)&this->client, &iLen);
		if (this->sAccept == INVALID_SOCKET) {
            cout << "Error : Accept failed (" << WSAGetLastError() << ")." << endl;
			return false;
        }

        cout << "Information : Accepted client IP : " << inet_ntoa(this->client.sin_addr) << "." << endl;
        cout << "Information : Accepted client PORT : " << ntohs(this->client.sin_port) << "." << endl;

		char* msg = new char[500];
		int msgLen = recv(this->sAccept, msg, 500, 0);
		msg[msgLen] = '\0';
		if (msgLen > 0) {
            cout << msg << endl;
        }

		closesocket(sAccept);
    }
}

bool SocketServer::clearSocket()
{
    closesocket(this->sListen);
	WSACleanup();
}