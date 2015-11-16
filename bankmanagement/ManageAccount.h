#pragma once


// ManageAccount 对话框

class ManageAccount : public CDialogEx
{
	DECLARE_DYNAMIC(ManageAccount)

public:
	ManageAccount(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ManageAccount();

// 对话框数据
	enum { IDD = IDD_MANAGE_ACCOUNT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
