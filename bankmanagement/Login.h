#pragma once
#include "afxwin.h"


// Login �Ի���

class Login : public CDialogEx
{
	DECLARE_DYNAMIC(Login)

public:
	Login(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Login();

// �Ի�������
	enum { IDD = IDD_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	HICON m_hIcon;
	HCURSOR  m_hCursor;
	RECT  m_StaticRect;
	RECT  m_PicRect;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedLoginLogin();
	CString randomseq;/////////////////���ɵ���֤������
	CString m_LogPwd;
	CString m_LogIdentify;
	CString m_LogUsername;
	afx_msg BOOL OnInitDialog();
	afx_msg void OnClickedLoginCancel();
	afx_msg void OnStnClickedForgetPassword();
//	afx_msg void OnDblclkForgetPassword();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	
	
	
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnShengcheng();
	

	afx_msg void OnSetfocusLoginIdentify();
	CStatic m_bitmap;
	afx_msg void OnClickedVerifyPic();
};
