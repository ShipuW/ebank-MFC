#pragma once
#include "afxcmn.h"


// ManagerPropertyFeeDetail �Ի���

class ManagerPropertyFeeDetail : public CDialogEx
{
	DECLARE_DYNAMIC(ManagerPropertyFeeDetail)

public:
	ManagerPropertyFeeDetail(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ManagerPropertyFeeDetail();

// �Ի�������
	enum { IDD = IDD_FEE_DETAIL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl FeeDetailList;
public:
	afx_msg BOOL OnInitDialog();
};
