#pragma once


// ChangePassword �Ի���

class ChangePassword : public CDialogEx
{
	DECLARE_DYNAMIC(ChangePassword)

public:
	ChangePassword(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ChangePassword();

// �Ի�������
	enum { IDD = IDD_CHANGE_PASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedChangPwdChange();
	CString m_Changepassword;
	CString m_Changepasswordconfirm;
	CString m_ChangeaccountPasswordbefore;
	afx_msg BOOL OnInitDialog();
};
