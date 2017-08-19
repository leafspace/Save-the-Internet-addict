#pragma once

#include <string>
#include <vector>
#include <fstream>
#include "SocketLink.h"
#include "StructInfo.h"

class ThreadControlMachine
{
public:
    int threadNumber;                                                        //工作线程个数
    HANDLE mainThread;                                                       //分配工作的线程句柄
    HANDLE *threadList;                                                      //工作线程列表
    bool *threadState;                                                       //每个线程的工作状态 true表示正在工作 false表示空闲
    int *threadWorkNumber;                                                   //线程中每个线程所工作的工作号
	bool *threadOpened;                                                      //标识当中的每个线程是否工作过
    int workSchedule;                                                        //当前工作的进度

    vector<IPItem> LANIPList;                                                //自定义的处理内容列表
    ThreadControlMachine(int threadNumber, vector<IPItem> LANIPList) {
        this->threadNumber = threadNumber;
        this->LANIPList = LANIPList;
        this->workSchedule = 0;
    }

    void run();                                                              //开启主要线程
    void freeMachine();

	char torken[20];
	char *rand_str(char *str,const int len);
	bool AnalysisFile(string targetIP);
};

extern ThreadControlMachine *threadControlMachine;

DWORD WINAPI MainThreadProc(LPVOID lpParameter);                             //主工作线程，用于分配工作
DWORD WINAPI WorkThreadProc(LPVOID lpParameter);                             //工作线程，用于进行自定义处理