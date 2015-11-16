#pragma once
#include "afxcmn.h"


// ManagerAccount �Ի���

class ManagerAccount : public CDialogEx
{
	DECLARE_DYNAMIC(ManagerAccount)

public:
	ManagerAccount(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ManagerAccount();

// �Ի�������
	enum { IDD = IDD_MANAGER_ACCOUNT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
