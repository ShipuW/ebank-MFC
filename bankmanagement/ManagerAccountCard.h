#pragma once
#include "afxcmn.h"


// ManagerAccountCard �Ի���

class ManagerAccountCard : public CDialogEx
{
	DECLARE_DYNAMIC(ManagerAccountCard)

public:
	ManagerAccountCard(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ManagerAccountCard();

// �Ի�������
	enum { IDD = IDD_MANAGER_ACCOUNT_CARD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnInitDialog();
	CListCtrl ManagerAccountCardList;
};


