#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>
#pragma comment(lib, "ws2_32.lib") //��������Ŀ���Ե�������������ĸ��������������ws2_32.lib
#define  PORT 5000
void main()
{
	int port = PORT;
	WSADATA wsaData;
	SOCKET sListen, sAccept;

	int iLen;  //�ͻ���ַ����
	int iSend;  //�������ݳ���
	char buf[] = "hello,how are you";//��Ҫ���͵���Ϣ
	struct sockaddr_in serv, client;//���������ͻ��ĵ�ַ
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("Winsock load failed\n");
		return;
	}

	sListen = socket(AF_INET, SOCK_STREAM, 0);//�����׽���
	if (sListen == INVALID_SOCKET)
	{
		//�����׽���ʧ��
		printf("socket failed:%d\n", WSAGetLastError());//�������
		return;
	}

	//������������ַ
	serv.sin_family = AF_INET;
	serv.sin_port = htons(port);//��һ��˫�ֽ������ֽ�˳�������ת��Ϊ�����ֽ�˳��
	serv.sin_addr.s_addr = htonl(INADDR_ANY);//�����ֽ������ֽ�˳��ת��Ϊ�����ֽ�˳��INADDR_ANYΪϵͳָ����IP��ַ

											 //��
	if (bind(sListen, (LPSOCKADDR)&serv, sizeof(serv)) == SOCKET_ERROR)
	{
		//��ʧ��
		printf("bind() failed:%d\n", WSAGetLastError());
		return;
	}

	//�������״̬
	if (listen(sListen, 5) == SOCKET_ERROR)//���ڵȴ����ӵ���������5
	{
		//��������
		printf("listen() failed:%d\n", WSAGetLastError());
		return;
	}

	iLen = sizeof(client);//��ʼ���ͻ���ַ����

						  //����ѭ���ȴ��ͻ�����������
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


		//���ͻ��˷�������
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
