#pragma once
#include "afxcmn.h"


// ManagerDeal 对话框

class ManagerDeal : public CDialogEx
{
	DECLARE_DYNAMIC(ManagerDeal)

public:
	ManagerDeal(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ManagerDeal();

// 对话框数据
	enum { IDD = IDD_MANAGER_DEAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl CardApplyList;
	CListCtrl CardFreezeList;
	afx_msg BOOL OnInitDialog();
	afx_msg void OnRclickListDealApply(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRclickListDealFreeze(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnApplyPass();
	afx_msg void OnApplyNotpass();
	afx_msg void OnFreezeCancel();
	afx_msg void OnFreezeConfirm();
	afx_msg void OnLvnItemchangedListDealForget(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl CardWithdrawList;
	CListCtrl CardForgetList;
	afx_msg void OnRclickListDealWithdraw(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRclickListDealForget(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSendPwd();
	afx_msg void OnWithdrawConfirm();
	afx_msg void OnWithdrawReject();
};
