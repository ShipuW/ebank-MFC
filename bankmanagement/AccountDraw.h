#pragma once
#include "afxwin.h"


// AccountDraw �Ի���

class AccountDraw : public CDialogEx
{
	DECLARE_DYNAMIC(AccountDraw)

public:
	AccountDraw(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~AccountDraw();

// �Ի�������
	enum { IDD = IDD_ACCOUNT_DRAW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnInitDialog();
	CComboBox ComboDraw;
	CString m_DrawCardnumber;
	float m_DrawAmount;
	CString m_DrawPassword;
	afx_msg void OnClickedDrawDraw();
//	afx_msg void OnCbnSelchangeComboDraw();
	afx_msg void OnSetfocusComboDraw();
	CEdit DrawEdit;
};
