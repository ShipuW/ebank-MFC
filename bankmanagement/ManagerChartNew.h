#pragma once
#include "tchart1.h"
#include "CTChart0.h"
#include "CSeries0.h"

// ManagerChartNew �Ի���

class ManagerChartNew : public CDialogEx
{
	DECLARE_DYNAMIC(ManagerChartNew)

public:
	ManagerChartNew(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ManagerChartNew();

// �Ի�������
	enum { IDD = IDD_CHART_NEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnInitDialog();
	CTchart1 m_chartnew;
};
