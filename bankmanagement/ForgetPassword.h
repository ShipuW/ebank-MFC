#pragma once
#include "mySock.h"
#include  "Base64.h"

// ForgetPassword �Ի���

class ForgetPassword : public CDialogEx
{
	DECLARE_DYNAMIC(ForgetPassword)

public:
	void Disp(LONG flag);
	void GetHeader();
	mySock smtpSocket;    //�׽��������

	ForgetPassword(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ForgetPassword();

// �Ի�������
	enum { IDD = IDD_FORGET_PASSWORD };
	CString	m_Addr;
	CString	m_Attach;
	CString	m_BCC;
	CString	m_CC;
	CString	m_Letter;
	CString	m_Name;
	CString	m_Pass;
	UINT	m_Port;
	CString	m_Receiver;
	CString	m_Server;
	CString	m_Title;
	CString	m_User;
	CString	m_Info;

protected:
	//HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnInitDialog();
	CString m_ForgetpasswordUsername;
	//afx_msg HCURSOR OnQueryDragIcon();
	CString m_ForgetpasswordIdcard;
	CString m_ForgetpasswordEmail;
	afx_msg void OnClickedForgetFind();

private:
	CBase64 coder;
	BOOL GetBody(LPSTR& pszBody, int& nBodySize);
};
