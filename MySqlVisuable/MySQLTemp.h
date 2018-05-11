#pragma once
#include "afxcmn.h"
#include <vector>
#include <string>
#include "C:\Program Files\MySQL\MySQL Server 5.7\include\mysql.h" 


// MySQLTemp 对话框

class MySQLTemp : public CDialogEx
{
	DECLARE_DYNAMIC(MySQLTemp)

public:
	MySQLTemp(CWnd* pParent = NULL);   // 标准构造函数
	MySQLTemp(MYSQL mmy,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MySQLTemp();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	std::vector<std::string> tablesVecString;//全局变量，用于存储上级结果
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
	MYSQL myCont;			//数据库句柄

public:
	afx_msg void OnBnClickedButton4();
	virtual BOOL OnInitDialog();
};
