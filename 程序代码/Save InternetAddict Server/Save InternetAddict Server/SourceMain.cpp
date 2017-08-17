#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#include "SocketServer.h"

int main()
{
    while(true) {
		bool isSuccess = false;
        SocketServer *socketServer = new SocketServer();
        isSuccess = socketServer->initServer();
		if (!isSuccess) {
			socketServer->clearSocket();
			delete socketServer;
			continue;
		}
        isSuccess = socketServer->listen();
		if (!isSuccess) {
			socketServer->clearSocket();
			delete socketServer;
			continue;
		}
        isSuccess = socketServer->communication();
        socketServer->clearSocket();
        delete socketServer;
    }
    return 0;
}