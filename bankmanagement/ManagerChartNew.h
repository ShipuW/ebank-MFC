#pragma once
#include "tchart1.h"
#include "CTChart0.h"
#include "CSeries0.h"

// ManagerChartNew 对话框

class ManagerChartNew : public CDialogEx
{
	DECLARE_DYNAMIC(ManagerChartNew)

public:
	ManagerChartNew(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ManagerChartNew();

// 对话框数据
	enum { IDD = IDD_CHART_NEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnInitDialog();
	CTchart1 m_chartnew;
};
