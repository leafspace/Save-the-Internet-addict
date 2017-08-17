#pragma once

#include <string>
#include <iostream>

using namespace std;

class SystemAction
{
private:
    int processMode;                                                         //处理方式（1表示关机；2表示重启；3表示注销）
    bool fast;                                                               //是否强制处理并不显示警告
    int duration;                                                            //响应时长
    string cmdOrders;

    SystemAction() {
        this->processMode = 1;
        this->fast = true;
        this->duration = 0;
        this->cmdOrders = "shutdown";
    }
public:
    SystemAction(int processMode) {
        SystemAction();
        this->processMode = processMode;
    }

    SystemAction(int processMode, bool fast) {
        SystemAction();
        this->processMode = processMode;
        this->fast = fast;
    }

    SystemAction(int processMode, int duration) {
        SystemAction();
        this->processMode = processMode;
        this->duration = duration;
    }

    SystemAction(int processMode, bool fast, int duration) {
        SystemAction();
        this->processMode = processMode;
        this->fast = fast;
        this->duration = duration;
    }

    void setProcessMode(int processMode);
    void setFast(bool fast);
    void setTime(int duration);

    int getProcessMode(void);
    bool getFast(void);
    int getTime(void);

    string initCmdOrders(void);
    void runCMD(void);
};