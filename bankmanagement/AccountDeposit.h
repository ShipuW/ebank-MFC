#pragma once


// AccountDeposit 对话框

class AccountDeposit : public CDialogEx
{
	DECLARE_DYNAMIC(AccountDeposit)

public:
	AccountDeposit(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AccountDeposit();

// 对话框数据
	enum { IDD = IDD_ACCOUNT_DEPOSIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
