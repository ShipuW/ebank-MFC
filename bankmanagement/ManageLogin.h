#pragma once


// ManageLogin �Ի���

class ManageLogin : public CDialogEx
{
	DECLARE_DYNAMIC(ManageLogin)

public:
	ManageLogin(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ManageLogin();

// �Ի�������
	enum { IDD = IDD_MANAGE_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedManageLoginLogin();
	afx_msg BOOL OnInitDialog();
	CString m_ManageloginName;
	CString m_ManageloginPassword;
	afx_msg void OnClickedManageLoginCancel();
};
