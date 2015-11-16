#pragma once
#include "afxwin.h"


// AccountProperty 对话框

class AccountProperty : public CDialogEx
{
	DECLARE_DYNAMIC(AccountProperty)

public:
	AccountProperty(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AccountProperty();

// 对话框数据
	enum { IDD = IDD_ACCOUNT_PROPERTY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnInitDialog();
	//afx_msg void OnLbnSelchangeList3();
	CListCtrl AccountCard;
	afx_msg void OnClickedAccountPropertyApply();
//	afx_msg void OnLvnItemchangedAccountPropertyList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickedAccountPropertyRefresh();
	afx_msg void OnDblclkAccountPropertyList(NMHDR *pNMHDR, LRESULT *pResult);
};
