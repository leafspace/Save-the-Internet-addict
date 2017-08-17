
// Save InternetAddict ControlDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"

#include <vector>
using namespace std;

typedef struct IPItem
{
	CString ipAddress;
	bool state;

	IPItem(CString ipAddress, bool state) {
		this->ipAddress = ipAddress;
		this->state = state;
	}
}IPItem;

typedef struct IPAddress
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


// CSaveInternetAddictControlDlg 对话框
class CSaveInternetAddictControlDlg : public CDialogEx
{
// 构造
public:
	CSaveInternetAddictControlDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SAVEINTERNETADDICTCONTROL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	vector<IPItem> LANIPList;

	void RefreshListCtrl();
	IPAddress ChangetoStruct(CString ipAddress);
	bool CheckSubnetMask(IPAddress subnetMask);
	vector<IPAddress> GetDomainIP(IPAddress begin, IPAddress end);
	void GetBroadcastDomain(IPAddress ip, IPAddress subnetMask, IPAddress &begin, IPAddress &end);
public:
	CListCtrl listCtrl;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};
