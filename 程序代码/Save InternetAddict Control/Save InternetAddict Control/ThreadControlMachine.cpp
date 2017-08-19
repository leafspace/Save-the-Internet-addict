#include "stdafx.h"
#include "ThreadControlMachine.h"

ThreadControlMachine *threadControlMachine;

void ThreadControlMachine::run()
{
	this->mainThread = CreateThread(NULL, 0, MainThreadProc, NULL, 0, NULL); //创建主工作线程
}

void ThreadControlMachine::freeMachine()
{
	CloseHandle(this->mainThread);                                           //关闭主要线程
	for (int i = 0; i < this->threadNumber; ++i) {                           //循环关闭每一个子线程
		if (this->threadOpened[i]) {
			CloseHandle(this->threadList[i]);
		}
	}

	delete threadList;                                                       //清理内存
	delete threadState;                                                      //清理内存
	delete threadWorkNumber;                                                 //清理内存
	delete threadOpened;                                                     //清理内存
}

bool ThreadControlMachine::AnalysisFile(string targetIP)
{
	char fileName[256] = "temp//";
	char cmdstr[256] = "";
	strcat_s(fileName, this->rand_str(this->torken, 20));
	strcat_s(fileName, ".txt");

	strcat_s(cmdstr, "cmd /c ping ");
	strcat_s(cmdstr, targetIP.data());
	strcat_s(cmdstr, " -n 1 -w 500 >");
	strcat_s(cmdstr, fileName);

	WinExec(cmdstr, SW_HIDE);
	Sleep(500);

	ifstream inStream(fileName, ios::binary);
	if (!inStream.is_open()) {
		return false;
	}

	char buffer[512];
	inStream.getline(buffer, 512);
	inStream.getline(buffer, 512);
	inStream.getline(buffer, 512);

	if (strcmp(buffer, "请求超时。") == 0) {
		return false;
	} else {
		return true;
	}
}

char* ThreadControlMachine::rand_str(char *str, const int len)
{
	srand((unsigned long)time(NULL));
	int i;
	for (i = 0; i < len; ++i)
	{
		switch ((rand() % 3))
		{
		case 1:
			str[i] = 'A' + rand() % 26;
			break;
		case 2:
			str[i] = 'a' + rand() % 26;
			break;
		default:
			str[i] = '0' + rand() % 10;
			break;
		}
	}
	str[i] = 0;
	return str;
}

DWORD WINAPI MainThreadProc(LPVOID lpParameter)                              //主工作线程，用于分配工作
{
	threadControlMachine->threadList = new HANDLE[threadControlMachine->threadNumber];
	threadControlMachine->threadState = new bool[threadControlMachine->threadNumber];
	threadControlMachine->threadWorkNumber = new int[threadControlMachine->threadNumber];
	threadControlMachine->threadOpened = new bool[threadControlMachine->threadNumber];

	for (int i = 0; i < threadControlMachine->threadNumber; ++i) {           //初始化线程状态
		threadControlMachine->threadState[i] = false;
		threadControlMachine->threadOpened[i] = false;
	}

	for (int i = 0; i < (int)threadControlMachine->LANIPList.size(); ++i) {  //每个工作分配任务
		CString ctargetIP = threadControlMachine->LANIPList[i].ipAddress;
		string targetIP = CT2A(ctargetIP);
		bool ret = threadControlMachine->AnalysisFile(targetIP);
		if (ret == false) {
			continue;
		}

		int leisureIndex = -1;
		while (leisureIndex == -1) {                                         //不停的找到空闲的线程
			for (int j = 0; j < threadControlMachine->threadNumber; ++j) {
				if (threadControlMachine->threadState[j] == false) {         //如果线程为空闲，则返回空闲线程号
					leisureIndex = j;
					break;
				}
			}
		}

		if (threadControlMachine->threadOpened[leisureIndex]) {
			CloseHandle(threadControlMachine->threadList[leisureIndex]);
		} else {
			threadControlMachine->threadOpened[leisureIndex] = true;         //设置此线程创建过
		}

		threadControlMachine->threadState[leisureIndex] = true;              //设置空闲线程的状态为忙碌
		threadControlMachine->threadWorkNumber[leisureIndex] = i;            //设置该线程的工作目标为第i个数据
		threadControlMachine->threadList[leisureIndex] = CreateThread(NULL, 0, WorkThreadProc, &leisureIndex, 0, NULL);//传输当前为第leisureIndex个线程给线程内
		Sleep(300);                                                          //防止创建线程后获取数据时数据变化为-1
	}
	return 0;
}

DWORD WINAPI WorkThreadProc(LPVOID lpParameter)                              //工作线程，用于进行自定义处理
{
	int *workThreadIndex = (int*)lpParameter;                                //获取工作的线程号
	int threadIndex = *workThreadIndex;
	int workIndex = threadControlMachine->threadWorkNumber[threadIndex];     //获取当前是处理的第workIndex号数据
	CString ipAddress = threadControlMachine->LANIPList[workIndex].ipAddress;//获取要处理的ip地址
	string ip = CT2A(ipAddress);
	SocketLink *socketLink = new SocketLink();
	socketLink->initSocket(ip);
	bool isSuccess = socketLink->linkServer();
	socketLink->freeSocket();
	delete socketLink;

	if (isSuccess) {                                                         //如果成功了就修改状态
		threadControlMachine->LANIPList[workIndex].state = true;
	}

	threadControlMachine->workSchedule++;                                    //完成一个工作，工作进度增加
	threadControlMachine->threadState[threadIndex] = false;                  //设置当前线程为空闲
	return 0;
}