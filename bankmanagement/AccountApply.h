#pragma once


// AccountApply �Ի���

class AccountApply : public CDialogEx
{
	DECLARE_DYNAMIC(AccountApply)

public:
	AccountApply(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~AccountApply();

// �Ի�������
	enum { IDD = IDD_ACCOUNT_APPLY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeApplyCombo();
	CString m_ApplycardType;
	CString m_ApplycardPwd;
	CString m_ApplycardPwdConfirm;
	afx_msg void OnClickedApplyApply();
	afx_msg BOOL OnInitDialog();
};
