#pragma once


// ChangeCardPassword �Ի���

class ChangeCardPassword : public CDialogEx
{
	DECLARE_DYNAMIC(ChangeCardPassword)

public:
	ChangeCardPassword(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ChangeCardPassword();

// �Ի�������
	enum { IDD = IDD_CHANGE_CARD_PASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_ChangecardPassword;
	CString m_ChangecardPasswordconfirm;
	afx_msg void OnClickedChangeCardChange();
	CString m_ChangecardPasswordbefore;
	afx_msg BOOL OnInitDialog();
};
