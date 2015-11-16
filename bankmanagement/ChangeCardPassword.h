#pragma once


// ChangeCardPassword 对话框

class ChangeCardPassword : public CDialogEx
{
	DECLARE_DYNAMIC(ChangeCardPassword)

public:
	ChangeCardPassword(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ChangeCardPassword();

// 对话框数据
	enum { IDD = IDD_CHANGE_CARD_PASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_ChangecardPassword;
	CString m_ChangecardPasswordconfirm;
	afx_msg void OnClickedChangeCardChange();
	CString m_ChangecardPasswordbefore;
	afx_msg BOOL OnInitDialog();
};
