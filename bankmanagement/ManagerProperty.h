#pragma once
#include "tchart1.h"
#include "CTChart0.h"
#include "CSeries0.h"

// ManagerProperty 对话框

class ManagerProperty : public CDialogEx
{
	DECLARE_DYNAMIC(ManagerProperty)

public:
	ManagerProperty(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ManagerProperty();

// 对话框数据
	enum { IDD = IDD_MANAGER_PROPERTY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnInitDialog();
	float m_ManagerPropertyamount;
	afx_msg void OnClickedInterestFee();
	afx_msg void OnClickedAddPropertyInfo();
	afx_msg void OnClickedFeeDetail();
	
	CTchart1 m_chartfinal;
};
