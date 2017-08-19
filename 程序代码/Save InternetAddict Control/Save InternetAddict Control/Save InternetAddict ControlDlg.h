
// Save InternetAddict ControlDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"

#include <vector>
#include "StructInfo.h"
#include "SocketLink.h"
#include "ThreadControlMachine.h"
using namespace std;


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
	int timerID;                                                             //用户保存定时器的ID
	vector<IPItem> LANIPList;                                                //IP列表中显示的内容

	bool isTesing;                                                           //标识是否正在测试，用于控制防止重复测试与扫描列表

	int GetItemSelect();                                                     //获取某个listControl当前选中项的行号
	void RefreshListCtrl();                                                  //刷新列表，即将LANIPList中的内容重新写入到列表中
	IPAddress ChangetoStruct(CString ipAddress);                             //将CString的IP转化为本地容易处理的IP
	bool CheckSubnetMask(IPAddress subnetMask);                              //检查子网掩码是否符合要求
	vector<IPAddress> GetDomainIP(IPAddress begin, IPAddress end);           //将begin到end中间的所有IP保存进vector
	void GetBroadcastDomain(IPAddress ip, IPAddress subnetMask, IPAddress &begin, IPAddress &end); //根据IP地址和子网掩码获取开始IP和结束IP
public:
	CListCtrl listCtrl;
	CSliderCtrl sliderCtrl;
	CProgressCtrl progressCtrl;
	void OnTimer(UINT_PTR nIDEvent);                                         //系统定时器，定时刷新进度条
	afx_msg void OnBnClickedButton1();                                       //显示范围内的IP
	afx_msg void OnBnClickedButton2();                                       //将范围内的IP进行连接测试
	afx_msg void OnBnClickedButton3();                                       //添加一个指定IP
	afx_msg void OnBnClickedButton4();                                       //进行操作处理
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
};
