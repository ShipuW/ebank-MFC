#pragma once
#include "afxcmn.h"


// ManagerAccount 对话框

class ManagerAccount : public CDialogEx
{
	DECLARE_DYNAMIC(ManagerAccount)

public:
	ManagerAccount(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ManagerAccount();

// 对话框数据
	enum { IDD = IDD_MANAGER_ACCOUNT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl ListAccount;
	afx_msg BOOL OnInitDialog();
	afx_msg void OnAccountDelete();
	afx_msg void OnAccountModify();
	afx_msg void OnRclickListAccount(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDblclkListAccount(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnAccountCard();
};
