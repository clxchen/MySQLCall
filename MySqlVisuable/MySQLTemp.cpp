// MySQLTemp.cpp : 实现文件
//

#include "stdafx.h"
#include "MySqlVisuable.h"
#include "MySQLTemp.h"
#include "afxdialogex.h"
#include <string>
#include <vector>
#include "C:\Program Files\MySQL\MySQL Server 5.7\include\mysql.h" 
#pragma comment(lib,"libmysql.lib")

extern MYSQL myCont;
MYSQL_RES *result;
MYSQL_ROW sql_row;
MYSQL_FIELD *fd;

// MySQLTemp 对话框

IMPLEMENT_DYNAMIC(MySQLTemp, CDialogEx)

MySQLTemp::MySQLTemp(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_tabledata(_T(""))
{

}
MySQLTemp::MySQLTemp(MYSQL mmy, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_tabledata(_T(""))
	, myCont(mmy)
{

}

MySQLTemp::~MySQLTemp()
{
}

void MySQLTemp::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_RICHEDIT21, m_tabledata);
	DDX_Control(pDX, IDC_RICHEDIT21, m_ChatDisplay);
}


BEGIN_MESSAGE_MAP(MySQLTemp, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &MySQLTemp::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &MySQLTemp::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &MySQLTemp::OnBnClickedButton3)
	ON_EN_CHANGE(IDC_RICHEDIT21, &MySQLTemp::OnEnChangeRichedit21)
	ON_BN_CLICKED(IDC_BUTTON4, &MySQLTemp::OnBnClickedButton4)
END_MESSAGE_MAP()


// MySQLTemp 消息处理程序
void MySQLTemp::GetTablesInfo()
{
	tablesVecString.clear();
	mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式,否则在cmd下无法显示中文
	int res = mysql_query(&myCont, "show tables");//查询表格
	if (!res)
	{
		result = mysql_store_result(&myCont);//保存查询到的数据到result
		if (result)
		{
			int i, j;
			for (i = 0; fd = mysql_fetch_field(result); i++)//获取列名
			{
				std::string ss(fd->name);
				tablesVecString.push_back(ss);
			}
			j = mysql_num_fields(result);
			while (sql_row = mysql_fetch_row(result))//获取具体的数据
			{
				for (i = 0; i<j; i++)
				{
					std::string ss(sql_row[i]);
					tablesVecString.push_back(ss);

				}
			}
		}
	}
	else
	{
		std::string ss("数据为空");
		tablesVecString.push_back(ss);
	}
	if (result != NULL) mysql_free_result(result);//释放结果资源

												  //绘制列表
	CComboBox *pWaitSelect = (CComboBox *)GetDlgItem(IDC_COMBO1); // 取得下拉列表句柄
	pWaitSelect->SetFont(GetFont());
	//pWaitSelect->SetCurSel(-1);
	pWaitSelect->ResetContent();
	for (int i = 0; i < tablesVecString.size(); ++i)
	{
		CString ss2(tablesVecString[i].c_str());
		pWaitSelect->InsertString(i, ss2);
	}
	pWaitSelect->SetCurSel(0);
	++listNow;
}

void MySQLTemp::DisplayTableData(CString ss)
{
	CString temp("select * from ");
	temp = temp + ss;
	//temp.Format(_T("select * from %s"), ss);

	int n = temp.GetLength(); //获取str的字符数  
	int len = WideCharToMultiByte(CP_ACP, 0, temp, n, NULL, 0, NULL, NULL); //获取宽字节字符的大小，大小是按字节计算的  
	char *tempChar = new char[len + 1]; //以字节为单位  
	WideCharToMultiByte(CP_ACP, 0, temp, n, tempChar, len, NULL, NULL); //宽字节编码转换成多字节编码  
	tempChar[len] = '\0'; //多字节字符以'\0'结束  

	m_ChatDisplay.SetSel(0,-1);
	m_ChatDisplay.Clear();
	int res = mysql_query(&myCont, tempChar);//查询
	//res = mysql_query(&myCont, "select * from student");//查询
	if (!res)
	{
		result = mysql_store_result(&myCont);//保存查询到的数据到result
		if (result)
		{
			int i, j;
			//cout << "number of result: " << (unsigned long)mysql_num_rows(result) << endl;
			for (i = 0; fd = mysql_fetch_field(result); i++)//获取列名
			{
				//strcpy(&column[i][0], fd->name);
				//strcpy_s(&column[i][0], fd->name);
				//string ss(fd->name);
				//column.push_back(ss);
				//nTotalTextLength = m_ChatDisplay.GetWindowTextLength(); // 调用CWnd的GetWindowTextLength接口获取当前字符数     
				//m_ChatDisplay.SetSel(nTotalTextLength, nTotalTextLength);
				//m_ChatDisplay.SetSel(-1, -1);
				std::string ss(fd->name);
				CString ss2(ss.c_str());
				m_ChatDisplay.SetSel(-1, -1);
				m_ChatDisplay.ReplaceSel(ss2);
				m_ChatDisplay.SetSel(-1, -1);
				m_ChatDisplay.ReplaceSel(_T("\t"));
			}
			m_ChatDisplay.SetSel(-1, -1);
			m_ChatDisplay.ReplaceSel(_T("\r\n"));
			j = mysql_num_fields(result);
			//for (i = 0; i<j; i++)
			//{
			//	//printf("%s\t", column[i]);
			//	//cout << column[i] << '\t';
			//	std::string ss(fd->name);
			//	CString ss2(ss.c_str());
			//	m_ChatDisplay.SetSel(0, 0);
			//	m_ChatDisplay.ReplaceSel(ss2);
			//	m_ChatDisplay.ReplaceSel(_T("\t"));


			//}
			//printf("\n");
			while (sql_row = mysql_fetch_row(result))//获取具体的数据
			{
				for (i = 0; i<j; i++)
				{
					//printf("%s\t", sql_row[i]);
					std::string ss(sql_row[i]);
					CString ss2(ss.c_str());
					m_ChatDisplay.SetSel(-1, -1);
					m_ChatDisplay.ReplaceSel(ss2);
					m_ChatDisplay.SetSel(-1, -1);
					m_ChatDisplay.ReplaceSel(_T("\t"));
				}
				m_ChatDisplay.SetSel(-1, -1);
				m_ChatDisplay.ReplaceSel(_T("\r\n"));
			}
		}
	}
	else
	{
		m_ChatDisplay.ReplaceSel(_T("查询失败"));
	}
	if (result != NULL) mysql_free_result(result);//释放结果资源
	
	delete[] tempChar;


}


//BOOL MySQLTemp::OnInitDialog()
//{
//	CDialogEx::OnInitDialog();
//
//	// 将“关于...”菜单项添加到系统菜单中。
//
//	// IDM_ABOUTBOX 必须在系统命令范围内。
//	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
//	ASSERT(IDM_ABOUTBOX < 0xF000);
//
//	CMenu* pSysMenu = GetSystemMenu(FALSE);
//	if (pSysMenu != NULL)
//	{
//		BOOL bNameValid;
//		CString strAboutMenu;
//		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
//		ASSERT(bNameValid);
//		if (!strAboutMenu.IsEmpty())
//		{
//			pSysMenu->AppendMenu(MF_SEPARATOR);
//			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
//		}
//	}
//
//	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
//	//  执行此操作
//	SetIcon(m_hIcon, TRUE);			// 设置大图标
//	SetIcon(m_hIcon, FALSE);		// 设置小图标
//
//									// TODO: 在此添加额外的初始化代码
//	AfxInitRichEdit2();
//
//	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
//}












void MySQLTemp::OnBnClickedButton1()
{
	if (listNow == 0)
	{
		GetTablesInfo();
	}
	else if(listNow == 1)
	{
		CComboBox *pWaitSelect = (CComboBox *)GetDlgItem(IDC_COMBO1); // 取得下拉列表句柄
		int nIndex = pWaitSelect->GetCurSel();
		CString strCBText;
		pWaitSelect->GetLBText(nIndex, strCBText);
		if (nIndex > 0)
		{
			DisplayTableData(strCBText);

		}
		//获取选项
		//查询
		//显示
	}
	// TODO: 在此添加控件通知处理程序代码
}


void MySQLTemp::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
}


void MySQLTemp::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ChatDisplay.SetSel(0, -1);
	m_ChatDisplay.Clear();
	if(listNow>0)
		--listNow;
	if (listNow == 0)
	{
		GetTablesInfo();
	}

}


void MySQLTemp::OnEnChangeRichedit21()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void MySQLTemp::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ChatDisplay.SetSel(0, -1);
	m_ChatDisplay.Clear();
}


BOOL MySQLTemp::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GetTablesInfo();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
