#pragma once
#include "afxwin.h"


// AccountTransfer �Ի���

class AccountTransfer : public CDialogEx
{
	DECLARE_DYNAMIC(AccountTransfer)

public:
	AccountTransfer(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~AccountTransfer();

// �Ի�������
	enum { IDD = IDD_ACCOUNT_TRANSFER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
