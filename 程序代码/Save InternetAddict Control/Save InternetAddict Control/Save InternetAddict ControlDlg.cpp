
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
	DDX_Control(pDX, IDC_PROGRESS1, progressCtrl);
	DDX_Control(pDX, IDC_SLIDER1, sliderCtrl);
}

BEGIN_MESSAGE_MAP(CSaveInternetAddictControlDlg, CDialogEx)
	ON_WM_TIMER()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CSaveInternetAddictControlDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSaveInternetAddictControlDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CSaveInternetAddictControlDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CSaveInternetAddictControlDlg::OnBnClickedButton4)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CSaveInternetAddictControlDlg::OnNMCustomdrawSlider1)
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

	this->progressCtrl.SetRange(0, 100);                                     //设置进度条的范围
	this->sliderCtrl.SetRange(1, 15, false);                                 //设置拖动条的范围
	this->sliderCtrl.SetLineSize(1);                                         //设置按上下左右键的拖动数
	this->sliderCtrl.SetPageSize(5);                                         //设置按page键的拖动数
	this->sliderCtrl.SetPos(5);                                              //设置初始值
	CString str;
	str.Format(_T("%d%%"), 0);
	GetDlgItem(IDC_STATIC1)->SetWindowText(str);                             //设置进度条的显示值
	str.Format(_T("线程数(%d)"), 0); 
	GetDlgItem(IDC_STATIC2)->SetWindowText(str);                             //设置线程数的显示值

	CRect rect;
	this->listCtrl.GetHeaderCtrl()->EnableWindow(false);                     //固定标题不被移动
	this->listCtrl.GetClientRect(&rect);                                     //获取编程语言列表视图控件的位置和大小
	this->listCtrl.SetExtendedStyle(this->listCtrl.GetExtendedStyle()
		| LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);                          //为列表视图控件添加全行选中和栅格风格
	this->listCtrl.InsertColumn(0, _T("IP地址"), LVCFMT_CENTER, rect.Width() * 2 / 3 - 5, 0);
	this->listCtrl.InsertColumn(1, _T("状态"), LVCFMT_CENTER, rect.Width() / 3, 0);

	char name[255];
	WSADATA wsaData;
	CString ipAddress;
	PHOSTENT hostinfo;
	WORD wVersionRequested;
	wVersionRequested = MAKEWORD(2, 0);

	//获取本地IP
	if (WSAStartup( wVersionRequested, &wsaData ) == 0) {
		if( gethostname (name, sizeof(name)) == 0) {
			if((hostinfo = gethostbyname(name)) != NULL) {
				ipAddress = inet_ntoa(*(struct in_addr *)*hostinfo->h_addr_list);
			}
		}
		WSACleanup();
	}
	GetDlgItem(IDC_IPADDRESS1)->SetWindowText(ipAddress);                    //设置本地IP
	GetDlgItem(IDC_IPADDRESS2)->SetWindowText((CString)("255.255.255.0"));   //设置子网掩码
	GetDlgItem(IDC_IPADDRESS3)->SetWindowText(ipAddress);                    //设置添加的IP

	GetDlgItem(IDC_EDIT1)->SetWindowText((CString)("0"));
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(true);
	((CButton*)GetDlgItem(IDC_RADIO4))->SetCheck(true);
	((CButton*)GetDlgItem(IDC_RADIO6))->SetCheck(true);
	((CButton*)GetDlgItem(IDC_RADIO8))->SetCheck(true);

	this->isTesing = false;

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

int CSaveInternetAddictControlDlg::GetItemSelect()                           //获取某个listControl当前选中项的行号
{
	int count = this->listCtrl.GetItemCount();
	for (int i = 0; i < count; ++i) {
		if (this->listCtrl.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED) {
				return i;
		}
	}
	return -1;
}

void CSaveInternetAddictControlDlg::RefreshListCtrl()                        //刷新列表，即将LANIPList中的内容重新写入到列表中
{
	bool state;
	this->listCtrl.DeleteAllItems();
	for (int i = 0; i < (int) this->LANIPList.size(); ++i) {
		state = this->LANIPList[i].state;
		this->listCtrl.InsertItem(i, this->LANIPList[i].ipAddress);          //插入新的一项
		if (state) {                                                         //true为在线 false为离线
			this->listCtrl.SetItemText(i, 1, _T("在线"));
		} else {
			this->listCtrl.SetItemText(i, 1, _T("离线"));
		}
	}
}

IPAddress CSaveInternetAddictControlDlg::ChangetoStruct(CString ipAddress)   //将CString的IP转化为本地容易处理的IP
{
	int pointIndex[3];
	CString kindIP[4];

	//找到三个分隔点的位置
	pointIndex[0] = ipAddress.Find(_T("."), 0);
	pointIndex[1] = ipAddress.Find(_T("."), pointIndex[0] + 1);
	pointIndex[2] = ipAddress.Find(_T("."), pointIndex[1] + 1);

	//分别区分四段IP
	kindIP[0] = ipAddress.Mid(0, pointIndex[0]);
	kindIP[1] = ipAddress.Mid(pointIndex[0] + 1, pointIndex[1]);
	kindIP[2] = ipAddress.Mid(pointIndex[1] + 1, pointIndex[2]);
	kindIP[3] = ipAddress.Mid(pointIndex[2] + 1);

	//分别转化为数值型数据
	IPAddress ip(0, 0, 0, 0);
	ip.kindAddress[0] = _ttoi(kindIP[0]);
	ip.kindAddress[1] = _ttoi(kindIP[1]);
	ip.kindAddress[2] = _ttoi(kindIP[2]);
	ip.kindAddress[3] = _ttoi(kindIP[3]);
	return ip;
}

bool CSaveInternetAddictControlDlg::CheckSubnetMask(IPAddress subnetMask)    //检查子网掩码是否符合要求
{
	int norm[9] = {0, 128, 192, 224, 240, 248, 252, 254, 255};               //设置基数
	int index = 0;
	while (index != 4 && subnetMask.kindAddress[index++] == 255) {}          //从前向后找到不为255的位置，因为子网掩码形似255.255.255.0
	index--;

	while (index != 4) {
		int i = 0;
		for (; i < 9; ++i) {                                                 //查看index段数据是否符合子网掩码的标准
			if (norm[i] == subnetMask.kindAddress[index]) {                  //如果子网掩码为基数中的一种，则符合要求
				break;
			}
		}
		if (i == 9) {                                                        //不为基数中的一种，则说明不符合规格
			return false;
		}
		index++;
	}
	return true;
}

vector<IPAddress> CSaveInternetAddictControlDlg::GetDomainIP(IPAddress begin, IPAddress end)       //将begin到end中间的所有IP保存进vector
{
	vector<IPAddress> ipAddress;
	while (true) {
		if (begin.kindAddress[0] == end.kindAddress[0] &&
			begin.kindAddress[1] == end.kindAddress[1] &&
			begin.kindAddress[2] == end.kindAddress[2] &&
			begin.kindAddress[3] == end.kindAddress[3]) {                    //当begin=end时，则表示到了结尾
				break;
		}

		ipAddress.push_back(begin);

		for (int i = 3; i >= 0; --i) {
			begin.kindAddress[i] += 1;                                       //数据从末尾开始逐个+1
			if (begin.kindAddress[i] == 256) {                               //逢256进1
				begin.kindAddress[i] = 0;
			} else {
				break;
			}
		}

	}
	return ipAddress;
}

void CSaveInternetAddictControlDlg::GetBroadcastDomain(IPAddress ip, IPAddress subnetMask, IPAddress &begin, IPAddress &end)     //根据IP地址和子网掩码获取开始IP和结束IP
{
	int index = 0;
	for (int i = 0; i < 4; ++i) {
		if (subnetMask.kindAddress[i] == 255) {                              //由于是按位与，所以子网掩码每个为255的则不变
			begin.kindAddress[i] = ip.kindAddress[i];
			end.kindAddress[i] = ip.kindAddress[i];
		} else {
			index = i;
			break;
		}
	}

	if (index < 4) {
		int baseNumber = 256 - subnetMask.kindAddress[index];                //计算每个子网中的数目为多少
		for (int i = 0; i < 256 / baseNumber; ++i) {                         //循环所有子网
			if (ip.kindAddress[index] > i * baseNumber &&
				ip.kindAddress[index] < (i + 1) * baseNumber) {              //找到当前所在的子网
					begin.kindAddress[index] = i * baseNumber;               //首地址
					end.kindAddress[index] = (i + 1) * baseNumber - 1;       //广播地址
					break;
			}
		}
	}

	for (int i = index + 1; i < 4; ++i) {                                    //之后的处理
		begin.kindAddress[i] = 0;
		end.kindAddress[i] = 255;
	}
}

void CSaveInternetAddictControlDlg::OnTimer(UINT_PTR nIDEvent)
{
	int workSchedule = ::threadControlMachine->workSchedule;                 //获得当前已经处理的工作数
	double percent = (double) (workSchedule * 1.0 / ::threadControlMachine->LANIPList.size());   //获取工作的百分比
	int tempNumber = (int) (percent * 100);                                  //获取百分比化的数据
	
	if (tempNumber % 5 == 0) {                                               //定时刷新列表
		this->LANIPList.clear();
		this->LANIPList = ::threadControlMachine->LANIPList;                 //拷贝完成的内容
		this->RefreshListCtrl();
	}
	
	if (workSchedule == ::threadControlMachine->LANIPList.size()) {          //如果已经完成了所有的数据
		::threadControlMachine->freeMachine();                               //清除工作线程
		delete ::threadControlMachine;                                       //清除工作线程
		KillTimer(this->timerID);                                            //关闭定时器
		this->isTesing = false;
		GetDlgItem(IDC_BUTTON2)->SetWindowText(_T("测试连接"));               //恢复显示字样
	}

	CString str;
	str.Format(_T("%d%%"), tempNumber);
	this->progressCtrl.SetPos(tempNumber);
	GetDlgItem(IDC_STATIC1)->SetWindowText(str);                             //设置百分比的数据
}

void CSaveInternetAddictControlDlg::OnBnClickedButton1()                     //显示范围内的IP
{
	// TODO: 在此添加控件通知处理程序代码
	if (this->isTesing) {                                                    //控制无法重复测试
		MessageBoxW(_T("正在测试中！"), _T("错误！"), MB_ICONHAND);
		return ;
	}
	CString subnetMask;
	GetDlgItem(IDC_IPADDRESS2)->GetWindowText(subnetMask);                   //获取子网掩码值
	if (!this->CheckSubnetMask(this->ChangetoStruct(subnetMask))) {          //进行子网掩码值的正确与否的判断
		MessageBoxW(_T("请使用正确的子网掩码！"), _T("错误！"), MB_ICONHAND);
		GetDlgItem(IDC_IPADDRESS2)->SetWindowText((CString)("255.255.255.0"));
		return ;
	}

	CString ipAddress;
	IPAddress begin(0, 0, 0, 0), end(0, 0, 0, 0);
	GetDlgItem(IDC_IPADDRESS1)->GetWindowText(ipAddress);                    //获取设置的ip地址
	this->GetBroadcastDomain(this->ChangetoStruct(ipAddress), this->ChangetoStruct(subnetMask), begin, end); //获取ip地址范围

	this->LANIPList.clear();                                                 //清除列表项
	vector<IPAddress> domainIP = this->GetDomainIP(begin, end);              //获取列表项数值
	for (int i = 0; i < (int) domainIP.size(); ++i) {                        //重新转换存入
		IPItem item(domainIP[i].toCString(), false);
		this->LANIPList.push_back(item);
	}

	this->progressCtrl.SetPos(0);
	GetDlgItem(IDC_STATIC1)->SetWindowText((CString)("0%"));
	this->RefreshListCtrl();
}

void CSaveInternetAddictControlDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	if (this->isTesing) {
		MessageBoxW(_T("正在测试中！"), _T("错误！"), MB_ICONHAND);
		return ;
	}
	::threadControlMachine = new ThreadControlMachine(this->sliderCtrl.GetPos(), this->LANIPList); //创建线程控制机
	::threadControlMachine->run();                                           //运行工作线程
	SetTimer(this->timerID, 1000, 0);                                        //设置定时器定时刷新进度条
	this->isTesing = true;                                                   //表明正在测试
	GetDlgItem(IDC_BUTTON2)->SetWindowText(_T("测试中"));
}


void CSaveInternetAddictControlDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CString addIpAddress;
	GetDlgItem(IDC_IPADDRESS3)->GetWindowText(addIpAddress);                 //获取要添加的IP
	for (int i = 0; i < (int) this->LANIPList.size(); ++i) {                 //循环查看列表是否存在重复的
		if (this->LANIPList[i].ipAddress == addIpAddress) {
			return;
		}
	}
	IPItem ipItem(addIpAddress, false);
	this->LANIPList.push_back(ipItem);                                       //添加进入列表项

	this->RefreshListCtrl();
}


void CSaveInternetAddictControlDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	int processMode = 1;
	for (int i = IDC_RADIO1; i <= IDC_RADIO3; ++i) {                         //获取处理方式
		if (((CButton*)GetDlgItem(i))->GetCheck() == 1) {
			processMode = i - IDC_RADIO1 + 1;
			break;
		}
	}

	int fast = 1;
	if (((CButton*)GetDlgItem(IDC_RADIO4))->GetCheck() != 1) {               //获取是否快速处理无提示
		fast = 0;
	}
	
	int duration = 0;
	if (((CButton*)GetDlgItem(IDC_RADIO7))->GetCheck() == 1) {               //获取定时时间
		CString time;
		GetDlgItem(IDC_EDIT1)->GetWindowText(time);
		duration = _ttoi(time);
	}

	bool isSuccess = false;
	string orders = to_string((long long) processMode) + to_string((long long) fast) + to_string((long long) duration);//发送的数据
	if (((CButton*)GetDlgItem(IDC_RADIO8))->GetCheck() == 1) {               //选择列表处理
		int sumSuccess = 0;                                                  //用于保存所有处理的个数
		for (int i = 0; i < (int) this->LANIPList.size(); ++i) {
			if (this->LANIPList[i].state == false) {
				continue;
			}
			string ip = CT2A(this->LANIPList[i].ipAddress);
			SocketLink *socketLink = new SocketLink();
			isSuccess = socketLink->initSocket(ip);
			if (!isSuccess) {
				socketLink->freeSocket();
				continue;
			}
			isSuccess = socketLink->linkServer();
			if (!isSuccess) {
				socketLink->freeSocket();
				continue;
			}
			socketLink->sendOrders(orders);
			socketLink->freeSocket();
			delete socketLink;
			sumSuccess++;
		}
		CString str;
		str.Format(_T("共发送%d个对象."), sumSuccess);
		MessageBoxW(str, _T("提示"), MB_ICONASTERISK);
	} else {                                                                 //选择单个对象处理
		int selectIndex = this->GetItemSelect();
		string ip = CT2A(this->LANIPList[selectIndex].ipAddress);
		SocketLink *socketLink = new SocketLink();
		isSuccess = socketLink->initSocket(ip);
		if (!isSuccess) {
			socketLink->freeSocket();
			return ;
		}
		isSuccess = socketLink->linkServer();
		if (!isSuccess) {
			socketLink->freeSocket();
			return ;
		}
		socketLink->sendOrders(orders);
		socketLink->freeSocket();
		delete socketLink;
	}
}


void CSaveInternetAddictControlDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	str.Format(_T("线程数(%d)"), this->sliderCtrl.GetPos());                    //设置显示当前的线程数
	GetDlgItem(IDC_STATIC2)->SetWindowText(str);
	*pResult = 0;
}
