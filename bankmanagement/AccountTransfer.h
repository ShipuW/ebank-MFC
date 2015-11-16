#pragma once
#include "afxwin.h"


// AccountTransfer 对话框

class AccountTransfer : public CDialogEx
{
	DECLARE_DYNAMIC(AccountTransfer)

public:
	AccountTransfer(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AccountTransfer();

// 对话框数据
	enum { IDD = IDD_ACCOUNT_TRANSFER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox ComboTransfer;
	CString m_TransferFromcardnumber;
	CString m_TransferTocardnumber;
	CString m_TransferTousername;
	float m_TransferAmount;
	CString m_TransferPassword;
	afx_msg void OnClickedTransferTransfer();
	afx_msg BOOL OnInitDialog();
	afx_msg void OnKillfocusEditTransferTarget();
//	afx_msg void OnCbnSelchangeComboTransfer();
//	afx_msg void OnSetfocusComboTransfer();
	afx_msg void OnSetfocusComboTransfer();
	CEdit TransferEdit;
};
