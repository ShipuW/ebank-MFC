#pragma once
#include "afxcmn.h"
#include "ManagerAccount.h"
#include "ManagerDeal.h"
#include "ManagerProperty.h"

// Manager 对话框

class Manager : public CDialogEx
{
	DECLARE_DYNAMIC(Manager)

public:
	Manager(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Manager();

// 对话框数据
	enum { IDD = IDD_MANAGER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnInitDialog();
	CTabCtrl m_tab;
	int m_CurSelTab;
	ManagerAccount PageAccount;
	ManagerDeal PageDeal;
	ManagerProperty PageProperty;
	CDialog* pDialog[3];  //用来保存对话框对象指针
	afx_msg void OnTcnSelchangeManagerTab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickedManagerLogout();
};
