
// Save InternetAddict ControlDlg.h : ͷ�ļ�
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


// CSaveInternetAddictControlDlg �Ի���
class CSaveInternetAddictControlDlg : public CDialogEx
{
// ����
public:
	CSaveInternetAddictControlDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SAVEINTERNETADDICTCONTROL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
