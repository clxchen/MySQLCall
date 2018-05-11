#pragma once
#include "afxcmn.h"
#include <vector>
#include <string>
#include "C:\Program Files\MySQL\MySQL Server 5.7\include\mysql.h" 


// MySQLTemp �Ի���

class MySQLTemp : public CDialogEx
{
	DECLARE_DYNAMIC(MySQLTemp)

public:
	MySQLTemp(CWnd* pParent = NULL);   // ��׼���캯��
	MySQLTemp(MYSQL mmy,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MySQLTemp();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	std::vector<std::string> tablesVecString;//ȫ�ֱ��������ڴ洢�ϼ����
	int listNum;
	int listNow;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnEnChangeRichedit21();
	CString m_tabledata;
	CRichEditCtrl m_ChatDisplay;

private:

	void DisplayTableData(CString);
	void GetTablesInfo();
	MYSQL myCont;			//���ݿ���

public:
	afx_msg void OnBnClickedButton4();
	virtual BOOL OnInitDialog();
};
