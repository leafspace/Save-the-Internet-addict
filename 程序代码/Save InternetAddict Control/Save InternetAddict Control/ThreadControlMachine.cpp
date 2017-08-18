#include "stdafx.h"
#include "ThreadControlMachine.h"

ThreadControlMachine *threadControlMachine;

void ThreadControlMachine::run()
{
    this->mainThread = CreateThread(NULL, 0, MainThreadProc, NULL, 0, NULL);
}

void ThreadControlMachine::freeMachine()
{
    CloseHandle(this->mainThread);
    for (int i = 0; i < this->threadNumber; ++i) {
        CloseHandle(this->threadList[i]);
    }
    delete threadList;
    delete threadState;
	delete threadWorkNumber;
}

DWORD WINAPI MainThreadProc(LPVOID lpParameter)                              //主工作线程，用于分配工作
{
    threadControlMachine->threadList = new HANDLE[threadControlMachine->threadNumber];
    threadControlMachine->threadState = new bool[threadControlMachine->threadNumber];
    threadControlMachine->threadWorkNumber = new int[threadControlMachine->threadNumber];

	for (int i = 0; i < threadControlMachine->threadNumber; ++i) {
		threadControlMachine->threadState[i] = false;
	}

    for (int i = 0; i < (int) threadControlMachine->LANIPList.size(); ++i) {
        int leisureIndex = -1;
        while (leisureIndex == -1) {
            for (int j = 0; j < threadControlMachine->threadNumber; ++j) {
                if (threadControlMachine->threadState[j] == false) {
                    leisureIndex = j;
                    break;
                }
            }
        }

        threadControlMachine->threadState[leisureIndex] = true;
        threadControlMachine->threadWorkNumber[leisureIndex] = i;
        threadControlMachine->workSchedule = i;
        threadControlMachine->threadList[leisureIndex] = CreateThread(NULL, 0, WorkThreadProc, &leisureIndex, 0, NULL);
		Sleep(300);
    }
	threadControlMachine->workSchedule++;
	return 0;
}

DWORD WINAPI WorkThreadProc(LPVOID lpParameter)                              //工作线程，用于进行自定义处理
{
    int *workThreadIndex = (int*) lpParameter;
    int workIndex = threadControlMachine->threadWorkNumber[*workThreadIndex];
	CString ipAddress = threadControlMachine->LANIPList[workIndex].ipAddress;
    string ip = CT2A(ipAddress);
    SocketLink *socketLink = new SocketLink();
    socketLink->initSocket(ip);
    bool isSuccess = socketLink->linkServer();
    socketLink->freeSocket();
    delete socketLink;

    if (isSuccess) {
        threadControlMachine->LANIPList[workIndex].state = true;
    }
    
    threadControlMachine->threadState[*workThreadIndex] = false;
	return 0;
}