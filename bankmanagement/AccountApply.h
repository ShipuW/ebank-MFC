#pragma once


// AccountApply 对话框

class AccountApply : public CDialogEx
{
	DECLARE_DYNAMIC(AccountApply)

public:
	AccountApply(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AccountApply();

// 对话框数据
	enum { IDD = IDD_ACCOUNT_APPLY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeApplyCombo();
	CString m_ApplycardType;
	CString m_ApplycardPwd;
	CString m_ApplycardPwdConfirm;
	afx_msg void OnClickedApplyApply();
	afx_msg BOOL OnInitDialog();
};
