#pragma once


// Regist �Ի���

class Regist : public CDialogEx
{
	DECLARE_DYNAMIC(Regist)

public:
	Regist(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Regist();

// �Ի�������
	enum { IDD = IDD_REGIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_RegUsername;
	CString m_RegPwdConfirm;
	CString m_RegPwd;
	CString m_RegPhone;
	CString m_RegIdcard;
	CString m_RegEmail;
	CString m_RegAddress;
	afx_msg void OnClickedRegistRegist();
	//CString m_RegPwdconfirm;
//	afx_msg void OnEnChangeEditRegistPwd();
	afx_msg void OnSetfocusEditRegistUsername();
	afx_msg void OnKillfocusEditRegistUsername();
//	afx_msg void OnSetfocusEditRegistPwd();
	afx_msg BOOL OnInitDialog();
	afx_msg void OnClickedRegistCancel();
	afx_msg void OnKillfocusEditRegistEmail();
};
