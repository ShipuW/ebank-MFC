#pragma once


// AccountDeposit �Ի���

class AccountDeposit : public CDialogEx
{
	DECLARE_DYNAMIC(AccountDeposit)

public:
	AccountDeposit(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~AccountDeposit();

// �Ի�������
	enum { IDD = IDD_ACCOUNT_DEPOSIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnInitDialog();
	afx_msg void OnClickedAccountDepositComfirm();
	CString m_DepositCardnumber;
	CString m_DepositUsername;
	float m_DepositAmount;
//	afx_msg void OnEnChangeEditDepositAmount();
	afx_msg void OnKillfocusEditDepositCard();
//	afx_msg void OnSetfocusEditDepositAmount();
};
