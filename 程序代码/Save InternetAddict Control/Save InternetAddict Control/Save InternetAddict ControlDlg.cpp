
// Save InternetAddict ControlDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Save InternetAddict Control.h"
#include "Save InternetAddict ControlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSaveInternetAddictControlDlg 对话框




CSaveInternetAddictControlDlg::CSaveInternetAddictControlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSaveInternetAddictControlDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSaveInternetAddictControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, listCtrl);
}

BEGIN_MESSAGE_MAP(CSaveInternetAddictControlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CSaveInternetAddictControlDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSaveInternetAddictControlDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CSaveInternetAddictControlDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CSaveInternetAddictControlDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CSaveInternetAddictControlDlg 消息处理程序

BOOL CSaveInternetAddictControlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	CRect rect;
	this->listCtrl.GetHeaderCtrl()->EnableWindow(false);                     //固定标题不被移动
	this->listCtrl.GetClientRect(&rect);                                     //获取编程语言列表视图控件的位置和大小
	this->listCtrl.SetExtendedStyle(this->listCtrl.GetExtendedStyle()
		| LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);                          //为列表视图控件添加全行选中和栅格风格
	this->listCtrl.InsertColumn(0, _T("IP地址"), LVCFMT_CENTER, rect.Width() * 2 / 3 - 10, 0);
	this->listCtrl.InsertColumn(1, _T("状态"), LVCFMT_CENTER, rect.Width() / 3, 0);

	char name[255];
	WSADATA wsaData;
	CString ipAddress;
	PHOSTENT hostinfo;
	WORD wVersionRequested;
	wVersionRequested = MAKEWORD(2, 0);

	if (WSAStartup( wVersionRequested, &wsaData ) == 0) {
		if( gethostname (name, sizeof(name)) == 0) {
			if((hostinfo = gethostbyname(name)) != NULL) {
				ipAddress = inet_ntoa(*(struct in_addr *)*hostinfo->h_addr_list);
			}
		}
		WSACleanup();
	}
	GetDlgItem(IDC_IPADDRESS1)->SetWindowText(ipAddress);
	GetDlgItem(IDC_IPADDRESS2)->SetWindowText((CString)("255.255.255.0"));
	GetDlgItem(IDC_IPADDRESS3)->SetWindowText(ipAddress);

	GetDlgItem(IDC_EDIT1)->SetWindowText((CString)("0"));
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(true);
	((CButton*)GetDlgItem(IDC_RADIO4))->SetCheck(true);
	((CButton*)GetDlgItem(IDC_RADIO6))->SetCheck(true);
	((CButton*)GetDlgItem(IDC_RADIO8))->SetCheck(true);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSaveInternetAddictControlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSaveInternetAddictControlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSaveInternetAddictControlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSaveInternetAddictControlDlg::RefreshListCtrl()
{
	bool state;
	this->listCtrl.DeleteAllItems();
	for (int i = 0; i < (int) this->LANIPList.size(); ++i) {
		state = this->LANIPList[i].state;
		this->listCtrl.InsertItem(i, this->LANIPList[i].ipAddress);
		if (state) {
			this->listCtrl.SetItemText(i, 1, _T("在线"));
		} else {
			this->listCtrl.SetItemText(i, 1, _T("离线"));
		}
	}
}

IPAddress CSaveInternetAddictControlDlg::ChangetoStruct(CString ipAddress)
{
	int pointIndex[3];
	CString kindIP[4];
	pointIndex[0] = ipAddress.Find(_T("."), 0);
	pointIndex[1] = ipAddress.Find(_T("."), pointIndex[0] + 1);
	pointIndex[2] = ipAddress.Find(_T("."), pointIndex[1] + 1);

	kindIP[0] = ipAddress.Mid(0, pointIndex[0]);
	kindIP[1] = ipAddress.Mid(pointIndex[0] + 1, pointIndex[1]);
	kindIP[2] = ipAddress.Mid(pointIndex[1] + 1, pointIndex[2]);
	kindIP[3] = ipAddress.Mid(pointIndex[2] + 1);

	IPAddress ip(0, 0, 0, 0);
	ip.kindAddress[0] = _ttoi(kindIP[0]);
	ip.kindAddress[1] = _ttoi(kindIP[1]);
	ip.kindAddress[2] = _ttoi(kindIP[2]);
	ip.kindAddress[3] = _ttoi(kindIP[3]);
	return ip;
}

bool CSaveInternetAddictControlDlg::CheckSubnetMask(IPAddress subnetMask)
{
	int norm[9] = {0, 128, 192, 224, 240, 248, 252, 254, 255};
	int index = 0;
	while (index != 4 && subnetMask.kindAddress[index++] == 255) {}
	index--;

	while (index != 4) {
		int i = 0;
		for (; i < 9; ++i) {
			if (norm[i] == subnetMask.kindAddress[index]) {
				break;
			}
		}
		if (i == 9) {
			return false;
		}
		index++;
	}
	return true;
}

vector<IPAddress> CSaveInternetAddictControlDlg::GetDomainIP(IPAddress begin, IPAddress end)
{
	int index = 0;
	while (begin.kindAddress[index] == end.kindAddress[index]) {
		index++;
	}
	index--;

	vector<IPAddress> ipAddress;
	while (true) {
		if (begin.kindAddress[0] == end.kindAddress[0] &&
			begin.kindAddress[1] == end.kindAddress[1] &&
			begin.kindAddress[2] == end.kindAddress[2] &&
			begin.kindAddress[3] == end.kindAddress[3]) {
				break;
		}

		ipAddress.push_back(begin);

		for (int i = 3; i >= 0; --i) {
			begin.kindAddress[i] += 1;
			if (begin.kindAddress[i] == 256) {
				begin.kindAddress[i] = 0;
			} else {
				break;
			}
		}

	}
	return ipAddress;
}

void CSaveInternetAddictControlDlg::GetBroadcastDomain(IPAddress ip, IPAddress subnetMask, IPAddress &begin, IPAddress &end)
{
	int index = 0;
	for (int i = 0; i < 4; ++i) {
		if (subnetMask.kindAddress[i] == 255) {
			begin.kindAddress[i] = ip.kindAddress[i];
			end.kindAddress[i] = ip.kindAddress[i];
		} else {
			index = i;
			break;
		}
	}

	if (index < 4) {
		int baseNumber = 0;
		for (int i = 7; i >= 0; --i) {
			if ((baseNumber + (int) pow((double) 2, i)) > subnetMask.kindAddress[index]) {
				break;
			} else {
				baseNumber += (int) pow((double) 2, i);
			}
		}
		int endNumber = baseNumber + (256 - subnetMask.kindAddress[index]) - 1;
		begin.kindAddress[index] = baseNumber;
		end.kindAddress[index] = endNumber;
	}

	for (int i = index + 1; i < 4; ++i) {
		begin.kindAddress[i] = 0;
		end.kindAddress[i] = 255;
	}
}

void CSaveInternetAddictControlDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString subnetMask;
	GetDlgItem(IDC_IPADDRESS2)->GetWindowText(subnetMask);
	if (!this->CheckSubnetMask(this->ChangetoStruct(subnetMask))) {
		MessageBoxW(_T("请使用正确的子网掩码！"), _T("错误！"), MB_ICONHAND);
		GetDlgItem(IDC_IPADDRESS2)->SetWindowText((CString)("255.255.255.0"));
		return ;
	}

	CString ipAddress;
	IPAddress begin(0, 0, 0, 0), end(0, 0, 0, 0);
	GetDlgItem(IDC_IPADDRESS1)->GetWindowText(ipAddress);
	this->GetBroadcastDomain(this->ChangetoStruct(ipAddress), this->ChangetoStruct(subnetMask), begin, end);

	this->LANIPList.clear();
	vector<IPAddress> domainIP = this->GetDomainIP(begin, end);
	for (int i = 0; i < (int) domainIP.size(); ++i) {
		IPItem item(domainIP[i].toCString(), false);
		this->LANIPList.push_back(item);
	}

	this->RefreshListCtrl();
}


void CSaveInternetAddictControlDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CSaveInternetAddictControlDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CString addIpAddress;
	GetDlgItem(IDC_IPADDRESS3)->GetWindowText(addIpAddress);
	for (int i = 0; i < (int) this->LANIPList.size(); ++i) {
		if (this->LANIPList[i].ipAddress == addIpAddress) {
			return;
		}
	}
	IPItem ipItem(addIpAddress, false);
	this->LANIPList.push_back(ipItem);

	this->RefreshListCtrl();
}


void CSaveInternetAddictControlDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
}
