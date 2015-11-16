// ManagerChartNew.cpp : 实现文件
//

#include "stdafx.h"
#include "bankmanagement.h"
#include "ManagerChartNew.h"
#include "afxdialogex.h"


// ManagerChartNew 对话框

IMPLEMENT_DYNAMIC(ManagerChartNew, CDialogEx)

ManagerChartNew::ManagerChartNew(CWnd* pParent /*=NULL*/)
	: CDialogEx(ManagerChartNew::IDD, pParent)
	, m_chartnew()
{

}

ManagerChartNew::~ManagerChartNew()
{
}

void ManagerChartNew::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TCHART1, m_chartnew);
}

BOOL ManagerChartNew::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	///////////////////////////////产生图表
	CSeries0 lineSeries = (CSeries0)m_chartnew.Series(0);
	lineSeries.Clear();




	CString sqlstr;
	sqlstr.Format(_T("CREATE OR REPLACE VIEW `view_day_property`AS SELECT * FROM day_property ORDER BY day_property.dayproperty_id DESC LIMIT 10;"));
	CDatabase db;
	db.Open("bankmanagement");
	db.ExecuteSQL(sqlstr);
	sqlstr.Format(_T("select day_time,bank_balance from view_day_property  ORDER BY dayproperty_id ASC;"));
	CRecordset rs(&db);
	rs.Open(CRecordset::forwardOnly, (_T("%s"), sqlstr));
	CString strx, strbalance;
	double daybalance;


	for (int i = 0; i<10; i++)
	{

		CString varDayTime;
		rs.GetFieldValue(_T("day_time"), varDayTime);
		strx.Format(_T("%s"), varDayTime);

		CString varBankBalance;
		rs.GetFieldValue(_T("bank_balance"), varBankBalance);
		strbalance.Format(_T("%s"), varBankBalance);
		daybalance = _ttof(strbalance);

		lineSeries.AddXY((double)i, daybalance, strx, 0);
		rs.MoveNext();
	}

	rs.Close();


	db.Close();


	return true;
}

BEGIN_MESSAGE_MAP(ManagerChartNew, CDialogEx)
END_MESSAGE_MAP()


// ManagerChartNew 消息处理程序
