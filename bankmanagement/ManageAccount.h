#pragma once


// ManageAccount �Ի���

class ManageAccount : public CDialogEx
{
	DECLARE_DYNAMIC(ManageAccount)

public:
	ManageAccount(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ManageAccount();

// �Ի�������
	enum { IDD = IDD_MANAGE_ACCOUNT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_ManageaccountUsername;
	CString m_ManageaccountIdcard;
	CString m_ManageaccountAddress;
	CString m_ManageaccountEmail;
	CString m_ManageaccountPhone;
	afx_msg void OnClickedManageModifyModify();
	afx_msg BOOL OnInitDialog();
};
