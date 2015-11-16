// AccountDetail.cpp : 实现文件
//

#include "stdafx.h"
#include "bankmanagement.h"
#include "AccountDetail.h"
#include "afxdialogex.h"
#include "ChangeCardPassword.h"

// AccountDetail 对话框

IMPLEMENT_DYNAMIC(AccountDetail, CDialogEx)

AccountDetail::AccountDetail(CWnd* pParent /*=NULL*/)
	: CDialogEx(AccountDetail::IDD, pParent)
	, m_DetailCard(_T(""))
	, m_DetailTime(_T(""))
	, m_DetailBalance(_T(""))
	, m_DetailType(_T(""))
	, m_DetailradioType(0)
{

}

AccountDetail::~AccountDetail()
{
}

void AccountDetail::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DETAIL_CARD, m_DetailCard);
	DDX_Text(pDX, IDC_EDIT_DETAIL_TIME, m_DetailTime);
	DDX_Text(pDX, IDC_EDIT_DETAIL_BALANCE, m_DetailBalance);
	DDX_Text(pDX, IDC_EDIT_DETAIL_TYPE, m_DetailType);
	DDX_Control(pDX, IDC_LIST_DETAIL_OPERATE, AccountOperate);
	DDX_Radio(pDX, IDC_RADIO_DEPOSIT, m_DetailradioType);
}


BEGIN_MESSAGE_MAP(AccountDetail, CDialogEx)
	ON_BN_CLICKED(IDC_CARD_CHANGE_PWD, &AccountDetail::OnClickedCardChangePwd)
	ON_BN_CLICKED(IDC_RADIO_DEPOSIT, &AccountDetail::OnClickedRadioDeposit)
	ON_BN_CLICKED(IDC_RADIO_DRAW, &AccountDetail::OnClickedRadioDeposit)
	ON_BN_CLICKED(IDC_RADIO_TRANSFER, &AccountDetail::OnClickedRadioDeposit)
	ON_BN_CLICKED(IDC_CARD_FORGET_PWD, &AccountDetail::OnClickedCardForgetPwd)
	ON_BN_CLICKED(IDC_CARD_WITHDRAW, &AccountDetail::OnClickedCardWithdraw)
END_MESSAGE_MAP()



BOOL AccountDetail::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ModifyStyleEx(0, WS_EX_APPWINDOW);
	HICON m_hIcon;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	
	AccountOperate.InsertColumn(1, _T("操作类型"), LVCFMT_LEFT, 200);
	AccountOperate.InsertColumn(2, _T("金额"), LVCFMT_LEFT, 80);
	AccountOperate.InsertColumn(3, _T("时间"), LVCFMT_LEFT, 80);
	
	
	CString sqlstr;
	sqlstr.Format(_T("select money_value,operate_time from operate_deposit where card_number ='%s'"), CardDetail);
	AccountOperate.DeleteAllItems();

	CDatabase db;
	db.Open("bankmanagement");
	CRecordset rs(&db);
	rs.Open(CRecordset::forwardOnly, (_T("%s"), sqlstr));
	while (!rs.IsEOF())
	{
		CString varOperateType;
		varOperateType = "存款";
		AccountOperate.InsertItem(0, varOperateType);
		CString varOperateAmount;
		rs.GetFieldValue(_T("money_value"), varOperateAmount);
		AccountOperate.SetItemText(0, 1, varOperateAmount);
		CString varOperateTime;
		rs.GetFieldValue(_T("operate_time"), varOperateTime);
		AccountOperate.SetItemText(0, 2, varOperateTime);
		rs.MoveNext();
	}
	rs.Close();
	AccountOperate.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//////////////////////////////////////////////////上面是list control内容，下面是编辑框内容
	
	
	CString sqlstrinfo;
	m_DetailCard = CardDetail;
	sqlstrinfo.Format(_T("select register_time,money_balance,card_type from card where card_number='%s'"),m_DetailCard);
	CRecordset rss(&db);
	rss.Open(CRecordset::forwardOnly, (_T("%s"), sqlstrinfo));
	
	while (!rss.IsEOF())
	{
		
		rss.GetFieldValue(_T("register_time"), m_DetailTime);
		
		rss.GetFieldValue(_T("money_balance"), m_DetailBalance);
		
		rss.GetFieldValue(_T("card_type"), m_DetailType);
		rss.MoveNext();
	}
	UpdateData(false);



	rss.Close();
	db.Close();
	return true;
}

// AccountDetail 消息处理程序


void AccountDetail::OnClickedCardChangePwd()
{
	ChangeCardPassword dlg;

	ShowWindow(SW_HIDE);
	dlg.DoModal();
	ShowWindow(SW_SHOW);
	// TODO:  在此添加控件通知处理程序代码
}


void AccountDetail::OnClickedRadioDeposit()//////////////////////////////////////切换查看类型
{
	UpdateData(TRUE);
	switch (m_DetailradioType)
	{
	case 0:
	{
			  CString sqlstr;
			  sqlstr.Format(_T("select money_value,operate_time from operate_deposit where card_number ='%s'"), CardDetail);
			  AccountOperate.DeleteAllItems();

			  CDatabase db;
			  db.Open("bankmanagement");
			  CRecordset rs(&db);
			  rs.Open(CRecordset::forwardOnly, (_T("%s"), sqlstr));
			  while (!rs.IsEOF())
			  {
				  CString varOperateType;
				  varOperateType = "存款";
				  AccountOperate.InsertItem(0, varOperateType);
				  CString varOperateAmount;
				  rs.GetFieldValue(_T("money_value"), varOperateAmount);
				  AccountOperate.SetItemText(0, 1, varOperateAmount);
				  CString varOperateTime;
				  rs.GetFieldValue(_T("operate_time"), varOperateTime);
				  AccountOperate.SetItemText(0, 2, varOperateTime);
				  rs.MoveNext();
			  }
			  rs.Close();
			  AccountOperate.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
			  break;
	}
	case 1:
	{
			  CString sqlstr;
			  sqlstr.Format(_T("select money_value,operate_time from operate_draw where card_number ='%s'"), CardDetail);
			  AccountOperate.DeleteAllItems();

			  CDatabase db;
			  db.Open("bankmanagement");
			  CRecordset rs(&db);
			  rs.Open(CRecordset::forwardOnly, (_T("%s"), sqlstr));
			  while (!rs.IsEOF())
			  {
				  CString varOperateType;
				  varOperateType = "取款";
				  AccountOperate.InsertItem(0, varOperateType);
				  CString varOperateAmount;
				  rs.GetFieldValue(_T("money_value"), varOperateAmount);
				  AccountOperate.SetItemText(0, 1, varOperateAmount);
				  CString varOperateTime;
				  rs.GetFieldValue(_T("operate_time"), varOperateTime);
				  AccountOperate.SetItemText(0, 2, varOperateTime);
				  rs.MoveNext();
			  }
			  rs.Close();
			  AccountOperate.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
			  break;
	}
	case 2:
	{
			  CString sqlstr;
			  sqlstr.Format(_T("select money_value,operate_time from operate_transfer where card_number_from ='%s'"), CardDetail);
			  AccountOperate.DeleteAllItems();

			  CDatabase db;
			  db.Open("bankmanagement");
			  CRecordset rs(&db);
			  rs.Open(CRecordset::forwardOnly, (_T("%s"), sqlstr));
			  while (!rs.IsEOF())
			  {
				  CString varOperateType;
				  varOperateType = "转账";
				  AccountOperate.InsertItem(0, varOperateType);
				  CString varOperateAmount;
				  rs.GetFieldValue(_T("money_value"), varOperateAmount);
				  AccountOperate.SetItemText(0, 1, varOperateAmount);
				  CString varOperateTime;
				  rs.GetFieldValue(_T("operate_time"), varOperateTime);
				  AccountOperate.SetItemText(0, 2, varOperateTime);
				  rs.MoveNext();
			  }
			  rs.Close();
			  AccountOperate.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	}
	}
	// TODO:  在此添加控件通知处理程序代码
}


void AccountDetail::OnClickedCardForgetPwd()
{
	CDatabase db;
	db.Open("bankmanagement");
	CString sqlstr;//,username,idcard,pwd,address,email,number;
	sqlstr.Format(_T("update card set card_status='申请密码找回' where card_number='%s'"), m_DetailCard);
	db.ExecuteSQL(sqlstr);
	db.Close();
	MessageBox("管理员处理后会将密码设置为：111111");
	// TODO:  在此添加控件通知处理程序代码
}


void AccountDetail::OnClickedCardWithdraw()
{
	CDatabase db;
	db.Open("bankmanagement");
	CString sqlstr;//,username,idcard,pwd,address,email,number;
	sqlstr.Format(_T("update card set card_status='申请注销' where card_number='%s'"), m_DetailCard);
	db.ExecuteSQL(sqlstr);
	db.Close();
	MessageBox("管理员会在10个工作日内处理");
	// TODO:  在此添加控件通知处理程序代码
}
