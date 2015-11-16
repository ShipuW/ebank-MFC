#pragma once


// AccountInfo 对话框

class AccountInfo : public CDialogEx
{
	DECLARE_DYNAMIC(AccountInfo)

public:
	AccountInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AccountInfo();

// 对话框数据
	enum { IDD = IDD_ACCOUNT_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnInitDialog();
	CString m_InfoUsername;
	CString m_Infoaddress;
	CString m_Infoemail;
	CString m_Infophone;
	CString m_InfoIdcard;
	int infoflag = 1;
	afx_msg void OnClickedChangeInfo();
	afx_msg void OnClickedChangePassword();
//	afx_msg void OnEnChangeEditInfoIdcard();
};
