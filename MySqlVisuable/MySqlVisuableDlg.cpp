
// MySqlVisuableDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MySqlVisuable.h"
#include "MySqlVisuableDlg.h"
#include "afxdialogex.h"
//#include <Windows.h>
#include "MySQLTemp.h"
#include "C:\Program Files\MySQL\MySQL Server 5.7\include\mysql.h" 
#pragma comment(lib,"libmysql.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMySqlVisuableDlg 对话框



CMySqlVisuableDlg::CMySqlVisuableDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MYSQLVISUABLE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMySqlVisuableDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMySqlVisuableDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT2, &CMySqlVisuableDlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDOK, &CMySqlVisuableDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMySqlVisuableDlg::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT1, &CMySqlVisuableDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, &CMySqlVisuableDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT3, &CMySqlVisuableDlg::OnEnChangeEdit3)
END_MESSAGE_MAP()


// CMySqlVisuableDlg 消息处理程序

BOOL CMySqlVisuableDlg::OnInitDialog()
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	AfxInitRichEdit2();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMySqlVisuableDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMySqlVisuableDlg::OnPaint()
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
HCURSOR CMySqlVisuableDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMySqlVisuableDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CMySqlVisuableDlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMySqlVisuableDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();

	//char useName[256], passWord[256];
	//GetDlgItem(IDC_EDIT1)->GetWindowText(useName, 256);
	//GetDlgItem(IDC_EDIT2)->GetWindowText(passWord, 256);


	
	//GetDlgItem(IDC_EDIT3)->SetWindowText(char3);
}


void CMySqlVisuableDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


//MySQLTemp m_theMySqlApp;
//MYSQL myCont;			//数据库句柄


void CMySqlVisuableDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString useName, passWord;
	GetDlgItemText(IDC_EDIT1, useName);
	GetDlgItemText(IDC_EDIT2, passWord);

	int n = useName.GetLength(); //获取str的字符数  
	int len = WideCharToMultiByte(CP_ACP, 0, useName, n, NULL, 0, NULL, NULL); //获取宽字节字符的大小，大小是按字节计算的  
	char *useNameChar = new char[len + 1]; //以字节为单位  
	WideCharToMultiByte(CP_ACP, 0, useName, n, useNameChar, len, NULL, NULL); //宽字节编码转换成多字节编码  
	useNameChar[len] = '\0'; //多字节字符以'\0'结束  
	//cout << pChar << endl;
	n = passWord.GetLength(); //获取str的字符数  
	len = WideCharToMultiByte(CP_ACP, 0, passWord, n, NULL, 0, NULL, NULL); //获取宽字节字符的大小，大小是按字节计算的  
	char *passWordChar = new char[len + 2]; //以字节为单位  
	WideCharToMultiByte(CP_ACP, 0, passWord, n, passWordChar, len, NULL, NULL); //宽字节编码转换成多字节编码  
	passWordChar[len] = '\0'; //多字节字符以'\0'结束  

	SetDlgItemText(IDC_EDIT1, _T(""));
	SetDlgItemText(IDC_EDIT2, _T(""));

	CString state;
	state = _T("正在登录MySQL...");
	SetDlgItemText(IDC_EDIT3,state);
	//AfxMessageBox(_T("正在登录MySQL..."));
	
	//const char user[] = "root";         //username
	//const char pswd[] = "clx123456";    //password
	const char host[] = "localhost";    //or"127.0.0.1"
	const char table[] = "xscj";        //database
	unsigned int port = 3306;           //server port        
	//MYSQL_RES *result;
	//MYSQL_ROW sql_row;
	//MYSQL_FIELD *fd;
	//int res;
	MYSQL myCont;
	mysql_init(&myCont);
	if (mysql_real_connect(&myCont, host, useNameChar, passWordChar, table, port, NULL, 0))
	{
		SetDlgItemText(IDC_EDIT3, _T("登录成功"));
		MySQLTemp m_theMySqlApp(myCont);
		ShowWindow(SW_HIDE); //隐藏当前对话框
		m_theMySqlApp.DoModal();
		//m_theMySqlApp.GetTablesInfo();
		ShowWindow(SW_SHOW); //恢复当前对话框
		mysql_close(&myCont);//断开连接
	}
	else
	{
		SetDlgItemText(IDC_EDIT3, _T("登录失败"));
		AfxMessageBox(_T("用户名或密码错误，请重新登录"));
	}
	delete[] useNameChar;
	delete[] passWordChar;
	

}


void CMySqlVisuableDlg::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
