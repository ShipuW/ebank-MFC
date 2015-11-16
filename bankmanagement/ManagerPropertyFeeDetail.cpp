// ManagerPropertyFeeDetail.cpp : 实现文件
//

#include "stdafx.h"
#include "bankmanagement.h"
#include "ManagerPropertyFeeDetail.h"
#include "afxdialogex.h"


// ManagerPropertyFeeDetail 对话框

IMPLEMENT_DYNAMIC(ManagerPropertyFeeDetail, CDialogEx)

ManagerPropertyFeeDetail::ManagerPropertyFeeDetail(CWnd* pParent /*=NULL*/)
	: CDialogEx(ManagerPropertyFeeDetail::IDD, pParent)
{

}

ManagerPropertyFeeDetail::~ManagerPropertyFeeDetail()
{
}

void ManagerPropertyFeeDetail::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_FEE_DETAIL, FeeDetailList);
}


BEGIN_MESSAGE_MAP(ManagerPropertyFeeDetail, CDialogEx)
END_MESSAGE_MAP()


BOOL ManagerPropertyFeeDetail::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	FeeDetailList.InsertColumn(1, _T("银行卡号"), LVCFMT_LEFT, 80);
	FeeDetailList.InsertColumn(2, _T("操作金额"), LVCFMT_LEFT, 80);
	FeeDetailList.InsertColumn(3, _T("操作类型"), LVCFMT_LEFT, 80);
	FeeDetailList.InsertColumn(4, _T("操作时间"), LVCFMT_LEFT, 200);
	
	CString sqlstr;
	sqlstr.Format(_T("select card_number,money_amount,operate_type,operate_time from operate_bank"));

	FeeDetailList.DeleteAllItems();
	CDatabase db;
	db.Open("bankmanagement");
	CRecordset rs(&db);
	rs.Open(CRecordset::forwardOnly, (_T("%s"), sqlstr));
	while (!rs.IsEOF())
	{
		CString varCardNumber;
		rs.GetFieldValue(_T("card_number"), varCardNumber);
		FeeDetailList.InsertItem(0, varCardNumber);
		CString varMoneyAmount;
		rs.GetFieldValue(_T("money_amount"), varMoneyAmount);
		FeeDetailList.SetItemText(0, 1, varMoneyAmount);
		CString varOperateType;
		rs.GetFieldValue(_T("operate_type"), varOperateType);
		FeeDetailList.SetItemText(0, 2, varOperateType);
		CString varOperateTime;
		rs.GetFieldValue(_T("operate_time"), varOperateTime);
		FeeDetailList.SetItemText(0, 3, varOperateTime);
		rs.MoveNext();
	}
	FeeDetailList.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	rs.Close();
	db.Close();
	return true;
}


// ManagerPropertyFeeDetail 消息处理程序
