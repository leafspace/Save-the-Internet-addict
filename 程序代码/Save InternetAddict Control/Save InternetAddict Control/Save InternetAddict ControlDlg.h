
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
public:
	CListCtrl listCtrl;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};
