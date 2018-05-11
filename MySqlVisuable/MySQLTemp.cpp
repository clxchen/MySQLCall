// MySQLTemp.cpp : ʵ���ļ�
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

// MySQLTemp �Ի���

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


// MySQLTemp ��Ϣ�������
void MySQLTemp::GetTablesInfo()
{
	tablesVecString.clear();
	mysql_query(&myCont, "SET NAMES GBK"); //���ñ����ʽ,������cmd���޷���ʾ����
	int res = mysql_query(&myCont, "show tables");//��ѯ���
	if (!res)
	{
		result = mysql_store_result(&myCont);//�����ѯ�������ݵ�result
		if (result)
		{
			int i, j;
			for (i = 0; fd = mysql_fetch_field(result); i++)//��ȡ����
			{
				std::string ss(fd->name);
				tablesVecString.push_back(ss);
			}
			j = mysql_num_fields(result);
			while (sql_row = mysql_fetch_row(result))//��ȡ���������
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
		std::string ss("����Ϊ��");
		tablesVecString.push_back(ss);
	}
	if (result != NULL) mysql_free_result(result);//�ͷŽ����Դ

												  //�����б�
	CComboBox *pWaitSelect = (CComboBox *)GetDlgItem(IDC_COMBO1); // ȡ�������б���
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

	int n = temp.GetLength(); //��ȡstr���ַ���  
	int len = WideCharToMultiByte(CP_ACP, 0, temp, n, NULL, 0, NULL, NULL); //��ȡ���ֽ��ַ��Ĵ�С����С�ǰ��ֽڼ����  
	char *tempChar = new char[len + 1]; //���ֽ�Ϊ��λ  
	WideCharToMultiByte(CP_ACP, 0, temp, n, tempChar, len, NULL, NULL); //���ֽڱ���ת���ɶ��ֽڱ���  
	tempChar[len] = '\0'; //���ֽ��ַ���'\0'����  

	m_ChatDisplay.SetSel(0,-1);
	m_ChatDisplay.Clear();
	int res = mysql_query(&myCont, tempChar);//��ѯ
	//res = mysql_query(&myCont, "select * from student");//��ѯ
	if (!res)
	{
		result = mysql_store_result(&myCont);//�����ѯ�������ݵ�result
		if (result)
		{
			int i, j;
			//cout << "number of result: " << (unsigned long)mysql_num_rows(result) << endl;
			for (i = 0; fd = mysql_fetch_field(result); i++)//��ȡ����
			{
				//strcpy(&column[i][0], fd->name);
				//strcpy_s(&column[i][0], fd->name);
				//string ss(fd->name);
				//column.push_back(ss);
				//nTotalTextLength = m_ChatDisplay.GetWindowTextLength(); // ����CWnd��GetWindowTextLength�ӿڻ�ȡ��ǰ�ַ���     
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
			while (sql_row = mysql_fetch_row(result))//��ȡ���������
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
		m_ChatDisplay.ReplaceSel(_T("��ѯʧ��"));
	}
	if (result != NULL) mysql_free_result(result);//�ͷŽ����Դ
	
	delete[] tempChar;


}


//BOOL MySQLTemp::OnInitDialog()
//{
//	CDialogEx::OnInitDialog();
//
//	// ��������...���˵�����ӵ�ϵͳ�˵��С�
//
//	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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
//	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
//	//  ִ�д˲���
//	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
//	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
//
//									// TODO: �ڴ���Ӷ���ĳ�ʼ������
//	AfxInitRichEdit2();
//
//	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
//}












void MySQLTemp::OnBnClickedButton1()
{
	if (listNow == 0)
	{
		GetTablesInfo();
	}
	else if(listNow == 1)
	{
		CComboBox *pWaitSelect = (CComboBox *)GetDlgItem(IDC_COMBO1); // ȡ�������б���
		int nIndex = pWaitSelect->GetCurSel();
		CString strCBText;
		pWaitSelect->GetLBText(nIndex, strCBText);
		if (nIndex > 0)
		{
			DisplayTableData(strCBText);

		}
		//��ȡѡ��
		//��ѯ
		//��ʾ
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void MySQLTemp::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void MySQLTemp::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void MySQLTemp::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ChatDisplay.SetSel(0, -1);
	m_ChatDisplay.Clear();
}


BOOL MySQLTemp::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GetTablesInfo();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
