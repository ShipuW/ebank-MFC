#pragma once
#include "afxcmn.h"
#include "AccountDeposit.h"
#include "AccountDraw.h"
#include "AccountInfo.h"
#include "AccountProperty.h"
#include "AccountTransfer.h"


// Account 对话框

class Account : public CDialogEx
{
	DECLARE_DYNAMIC(Account)

public:
	Account(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Account();

// 对话框数据
	enum { IDD = IDD_ACCOUNT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnInitDialog();
	CTabCtrl m_tab;
	int m_CurSelTab;
	AccountDeposit PageDeposit;
	AccountDraw PageDraw;
	AccountInfo PageInfo;
	AccountProperty PageProperty;
	AccountTransfer PageTransfer;
	CDialog* pDialog[5];  //用来保存对话框对象指针
	afx_msg void OnTcnSelchangeAccountTab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickedAccountLogout();
};
