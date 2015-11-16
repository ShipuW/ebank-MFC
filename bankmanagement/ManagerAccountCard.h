#pragma once
#include "afxcmn.h"


// ManagerAccountCard 对话框

class ManagerAccountCard : public CDialogEx
{
	DECLARE_DYNAMIC(ManagerAccountCard)

public:
	ManagerAccountCard(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ManagerAccountCard();

// 对话框数据
	enum { IDD = IDD_MANAGER_ACCOUNT_CARD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnInitDialog();
	CListCtrl ManagerAccountCardList;
};


