#include "SocketServer.h"

void SocketServer::systemProcess(int msgLen)
{
	if (msgLen == 1) {
		return ;
	}
	SystemAction *systemAction = new SystemAction(this->message[0] - '0');
	int fast = this->message[1];
	if (fast == '1') {
		systemAction->setFast(true);
	} else {
		systemAction->setFast(false);
	}
	int duration = 0;
	for (int i = 2; i < msgLen; ++i) {
		duration = duration * 10 + this->message[i] - '0';
	}
	systemAction->setTime(duration);

	cout << "Information : Running (" << systemAction->initCmdOrders() << ")." << endl;
	systemAction->runCMD();
}

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
    if (::listen(this->sListen, 5) == SOCKET_ERROR) {
        cout << "Error : Listen failed (" << WSAGetLastError() << ")." << endl;
		return false;
	} else {
		cout << "Information : Socket is listening." << endl;
	}
	return true;
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

		int msgLen = recv(this->sAccept, this->message, 500, 0);
		this->message[msgLen] = '\0';
		if (msgLen > 0) {
			cout << this->message << endl;
			this->systemProcess(msgLen);
		}
		closesocket(sAccept);
    }
}

bool SocketServer::clearSocket()
{
    closesocket(this->sListen);
	WSACleanup();
	delete this->message;
	return true;
}