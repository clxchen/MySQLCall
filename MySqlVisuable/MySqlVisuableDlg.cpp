
// MySqlVisuableDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMySqlVisuableDlg �Ի���



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


// CMySqlVisuableDlg ��Ϣ�������

BOOL CMySqlVisuableDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	AfxInitRichEdit2();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMySqlVisuableDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMySqlVisuableDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMySqlVisuableDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void CMySqlVisuableDlg::OnEnChangeEdit2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMySqlVisuableDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();

	//char useName[256], passWord[256];
	//GetDlgItem(IDC_EDIT1)->GetWindowText(useName, 256);
	//GetDlgItem(IDC_EDIT2)->GetWindowText(passWord, 256);


	
	//GetDlgItem(IDC_EDIT3)->SetWindowText(char3);
}


void CMySqlVisuableDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


//MySQLTemp m_theMySqlApp;
//MYSQL myCont;			//���ݿ���


void CMySqlVisuableDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString useName, passWord;
	GetDlgItemText(IDC_EDIT1, useName);
	GetDlgItemText(IDC_EDIT2, passWord);

	int n = useName.GetLength(); //��ȡstr���ַ���  
	int len = WideCharToMultiByte(CP_ACP, 0, useName, n, NULL, 0, NULL, NULL); //��ȡ���ֽ��ַ��Ĵ�С����С�ǰ��ֽڼ����  
	char *useNameChar = new char[len + 1]; //���ֽ�Ϊ��λ  
	WideCharToMultiByte(CP_ACP, 0, useName, n, useNameChar, len, NULL, NULL); //���ֽڱ���ת���ɶ��ֽڱ���  
	useNameChar[len] = '\0'; //���ֽ��ַ���'\0'����  
	//cout << pChar << endl;
	n = passWord.GetLength(); //��ȡstr���ַ���  
	len = WideCharToMultiByte(CP_ACP, 0, passWord, n, NULL, 0, NULL, NULL); //��ȡ���ֽ��ַ��Ĵ�С����С�ǰ��ֽڼ����  
	char *passWordChar = new char[len + 2]; //���ֽ�Ϊ��λ  
	WideCharToMultiByte(CP_ACP, 0, passWord, n, passWordChar, len, NULL, NULL); //���ֽڱ���ת���ɶ��ֽڱ���  
	passWordChar[len] = '\0'; //���ֽ��ַ���'\0'����  

	SetDlgItemText(IDC_EDIT1, _T(""));
	SetDlgItemText(IDC_EDIT2, _T(""));

	CString state;
	state = _T("���ڵ�¼MySQL...");
	SetDlgItemText(IDC_EDIT3,state);
	//AfxMessageBox(_T("���ڵ�¼MySQL..."));
	
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
		SetDlgItemText(IDC_EDIT3, _T("��¼�ɹ�"));
		MySQLTemp m_theMySqlApp(myCont);
		ShowWindow(SW_HIDE); //���ص�ǰ�Ի���
		m_theMySqlApp.DoModal();
		//m_theMySqlApp.GetTablesInfo();
		ShowWindow(SW_SHOW); //�ָ���ǰ�Ի���
		mysql_close(&myCont);//�Ͽ�����
	}
	else
	{
		SetDlgItemText(IDC_EDIT3, _T("��¼ʧ��"));
		AfxMessageBox(_T("�û�����������������µ�¼"));
	}
	delete[] useNameChar;
	delete[] passWordChar;
	

}


void CMySqlVisuableDlg::OnEnChangeEdit3()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
