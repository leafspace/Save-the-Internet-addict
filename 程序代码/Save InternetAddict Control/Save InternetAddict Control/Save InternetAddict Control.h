
// Save InternetAddict Control.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSaveInternetAddictControlApp:
// �йش����ʵ�֣������ Save InternetAddict Control.cpp
//

class CSaveInternetAddictControlApp : public CWinApp
{
public:
	CSaveInternetAddictControlApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSaveInternetAddictControlApp theApp;