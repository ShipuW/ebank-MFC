#pragma once
#include "afxcmn.h"


// ManagerPropertyFeeDetail 对话框

class ManagerPropertyFeeDetail : public CDialogEx
{
	DECLARE_DYNAMIC(ManagerPropertyFeeDetail)

public:
	ManagerPropertyFeeDetail(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ManagerPropertyFeeDetail();

// 对话框数据
	enum { IDD = IDD_FEE_DETAIL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl FeeDetailList;
public:
	afx_msg BOOL OnInitDialog();
};
