#pragma once


// ManageLogin 对话框

class ManageLogin : public CDialogEx
{
	DECLARE_DYNAMIC(ManageLogin)

public:
	ManageLogin(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ManageLogin();

// 对话框数据
	enum { IDD = IDD_MANAGE_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedManageLoginLogin();
	afx_msg BOOL OnInitDialog();
	CString m_ManageloginName;
	CString m_ManageloginPassword;
	afx_msg void OnClickedManageLoginCancel();
};
