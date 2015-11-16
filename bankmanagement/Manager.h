#pragma once
#include "afxcmn.h"
#include "ManagerAccount.h"
#include "ManagerDeal.h"
#include "ManagerProperty.h"

// Manager �Ի���

class Manager : public CDialogEx
{
	DECLARE_DYNAMIC(Manager)

public:
	Manager(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Manager();

// �Ի�������
	enum { IDD = IDD_MANAGER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnInitDialog();
	CTabCtrl m_tab;
	int m_CurSelTab;
	ManagerAccount PageAccount;
	ManagerDeal PageDeal;
	ManagerProperty PageProperty;
	CDialog* pDialog[3];  //��������Ի������ָ��
	afx_msg void OnTcnSelchangeManagerTab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickedManagerLogout();
};
