#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>
#pragma comment(lib, "ws2_32.lib") //或者在项目属性的连接器的输入的附加依赖项中添加ws2_32.lib
#define  PORT 5000
void main()
{
	int port = PORT;
	WSADATA wsaData;
	SOCKET sListen, sAccept;

	int iLen;  //客户地址长度
	int iSend;  //发送数据长度
	char buf[] = "hello,how are you";//需要发送的信息
	struct sockaddr_in serv, client;//服务器、客户的地址
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("Winsock load failed\n");
		return;
	}

	sListen = socket(AF_INET, SOCK_STREAM, 0);//创建套接字
	if (sListen == INVALID_SOCKET)
	{
		//创建套接字失败
		printf("socket failed:%d\n", WSAGetLastError());//输出错误
		return;
	}

	//建立服务器地址
	serv.sin_family = AF_INET;
	serv.sin_port = htons(port);//把一个双字节主机字节顺序的数据转换为网络字节顺序
	serv.sin_addr.s_addr = htonl(INADDR_ANY);//把四字节主机字节顺序转换为网络字节顺序，INADDR_ANY为系统指定的IP地址

											 //绑定
	if (bind(sListen, (LPSOCKADDR)&serv, sizeof(serv)) == SOCKET_ERROR)
	{
		//绑定失败
		printf("bind() failed:%d\n", WSAGetLastError());
		return;
	}

	//进入监听状态
	if (listen(sListen, 5) == SOCKET_ERROR)//正在等待连接的最大个数是5
	{
		//侦听出错
		printf("listen() failed:%d\n", WSAGetLastError());
		return;
	}

	iLen = sizeof(client);//初始化客户地址长度

						  //进入循环等待客户端连接请求
	while (1)
	{
		sAccept = accept(sListen, (struct sockaddr*)&client, &iLen);
		if (sAccept == INVALID_SOCKET)
		{
			printf("accept() failed:%d\n", WSAGetLastError());
			break;
		}
		//printf("accepted client IP:[%s],port:[%d]\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

		char* msg = new char[500];
		int msgLen = recv(sAccept, msg, 500, 0);
		msg[msgLen] = '\0';
		if (msgLen>0)
			printf("%s\n", msg);


		//给客户端发送数据
		iSend = send(sAccept, buf, sizeof(buf), 0);
		if (iSend == SOCKET_ERROR)
		{
			printf("send() failed:%d\n", WSAGetLastError());
			break;
		}
		else if (iSend == 0)
		{
			break;
		}
		else
		{
			printf("send() byte:%d\n", iSend);
		}

		closesocket(sAccept);
	}

	closesocket(sListen);
	WSACleanup();
}
