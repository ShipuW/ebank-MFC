#pragma once
#include "afxcmn.h"


// AccountDetail 对话框

class AccountDetail : public CDialogEx
{
	DECLARE_DYNAMIC(AccountDetail)

public:
	AccountDetail(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AccountDetail();

// 对话框数据
	enum { IDD = IDD_ACCOUNT_DETAIL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnInitDialog();
	CString m_DetailCard;
	CString m_DetailTime;
	CString m_DetailBalance;
	CString m_DetailType;
	afx_msg void OnClickedCardChangePwd();
	CListCtrl AccountOperate;
	int m_DetailradioType;
	afx_msg void OnClickedRadioDeposit();
	afx_msg void OnClickedCardForgetPwd();
	afx_msg void OnClickedCardWithdraw();
};
