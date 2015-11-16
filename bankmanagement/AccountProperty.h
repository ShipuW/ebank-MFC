#pragma once
#include "afxwin.h"


// AccountProperty �Ի���

class AccountProperty : public CDialogEx
{
	DECLARE_DYNAMIC(AccountProperty)

public:
	AccountProperty(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~AccountProperty();

// �Ի�������
	enum { IDD = IDD_ACCOUNT_PROPERTY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
