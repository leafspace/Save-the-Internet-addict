#pragma once

#include "afxcmn.h"

typedef struct IPItem                                                        //用于列表项处理用
{
	CString ipAddress;
	bool state;

	IPItem(CString ipAddress, bool state) {
		this->ipAddress = ipAddress;
		this->state = state;
	}
}IPItem;

typedef struct IPAddress                                                     //提供ip范围处理用
{
	int kindAddress[4];

	IPAddress(int kindA, int kindB, int kindC, int kindD) {
		this->kindAddress[0] = kindA;
		this->kindAddress[1] = kindB;
		this->kindAddress[2] = kindC;
		this->kindAddress[3] = kindD;
	}

	CString toCString() {
		CString str;
		str.Format(_T("%d.%d.%d.%d"), this->kindAddress[0], this->kindAddress[1], this->kindAddress[2], this->kindAddress[3]);
		return str;
	}
}IPAddress;