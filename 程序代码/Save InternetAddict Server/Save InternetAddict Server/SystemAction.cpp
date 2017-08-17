#include "SystemAction.h"

void SystemAction::setProcessMode(int processMode)
{
    this->processMode = processMode;
}

void SystemAction::setFast(bool fast)
{
    this->fast = fast;
}

void SystemAction::setTime(int duration)
{
    this->duration = duration;    
}

int SystemAction::getProcessMode(void)
{
    return this->processMode;
}

bool SystemAction::getFast(void)
{
    return this->fast;
}

int SystemAction::getTime(void)
{
    return this->duration;
}

string SystemAction::initCmdOrders(void)
{
    switch(this->processMode)
    {
        case 1 : this->cmdOrders += (string)" -s"; break;
        case 2 : this->cmdOrders += (string)" -r"; break;
        case 3 : this->cmdOrders += (string)" -l"; break;
        default : this->cmdOrders += (string)" -s"; break;
    }

    if (this->fast) {
        this->cmdOrders += (string)" -f"; 
    }

    if (this->duration != 0) {
        this->duration = abs(duration);
    }

    this->cmdOrders += (string)" -t"; 
    this->cmdOrders += to_string((long long)this->duration);

    return this->cmdOrders;
}

void SystemAction::runCMD(void)
{
	system(this->initCmdOrders().data());
}