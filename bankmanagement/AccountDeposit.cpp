// AccountDeposit.cpp : 实现文件
//

#include "stdafx.h"
#include "bankmanagement.h"
#include "AccountDeposit.h"
#include "afxdialogex.h"


// AccountDeposit 对话框

IMPLEMENT_DYNAMIC(AccountDeposit, CDialogEx)

AccountDeposit::AccountDeposit(CWnd* pParent /*=NULL*/)
	: CDialogEx(AccountDeposit::IDD, pParent)
	, m_DepositCardnumber(_T(""))
	, m_DepositUsername(_T(""))
	, m_DepositAmount(0)
{

}

AccountDeposit::~AccountDeposit()
{
}

void AccountDeposit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DEPOSIT_CARD, m_DepositCardnumber);
	DDX_Text(pDX, IDC_EDIT_DEPOSIT_USERNAME, m_DepositUsername);
	DDX_Text(pDX, IDC_EDIT_DEPOSIT_AMOUNT, m_DepositAmount);
	DDV_MinMaxFloat(pDX, m_DepositAmount, 1, 10000);
}


BEGIN_MESSAGE_MAP(AccountDeposit, CDialogEx)
	ON_BN_CLICKED(IDC_ACCOUNT_DEPOSIT_COMFIRM, &AccountDeposit::OnClickedAccountDepositComfirm)
//	ON_EN_CHANGE(IDC_EDIT_DEPOSIT_AMOUNT, &AccountDeposit::OnEnChangeEditDepositAmount)
ON_EN_KILLFOCUS(IDC_EDIT_DEPOSIT_CARD, &AccountDeposit::OnKillfocusEditDepositCard)
//ON_EN_SETFOCUS(IDC_EDIT_DEPOSIT_AMOUNT, &AccountDeposit::OnSetfocusEditDepositAmount)
END_MESSAGE_MAP()
BOOL AccountDeposit::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_DepositAmount = 100;
	UpdateData(false);
	return true;
}
// AccountDeposit 消息处理程序


void AccountDeposit::OnClickedAccountDepositComfirm()
{
	CDatabase db;
	db.Open("bankmanagement");
	CString sqlstr,sqlstraccount;//,username,idcard,pwd,address,email,number;
	
	UpdateData(true);
	if (m_DepositAmount<1 || m_DepositAmount>10000);
	else{
		CString timestr;//////获取系统时间
		CTime tm; tm = CTime::GetCurrentTime();
		timestr = tm.Format("%Y年%m月%d日 %X");
		sqlstr.Format(_T("insert into operate_deposit(card_number,money_value,operate_time) values('%s','%f','%s')"), m_DepositCardnumber, m_DepositAmount,timestr);
		sqlstraccount.Format(_T("update card set money_balance=money_balance+'%f'where card_number='%s'"), m_DepositAmount, m_DepositCardnumber);
		MessageBox("确定吗？");
		db.ExecuteSQL(sqlstr);
		db.ExecuteSQL(sqlstraccount);
		db.Close();
		MessageBox("存款成功！");
		m_DepositCardnumber = "";
		m_DepositUsername = "";
		m_DepositAmount = 0;
		UpdateData(FALSE);
	}
	// TODO:  在此添加控件通知处理程序代码
}


//void AccountDeposit::OnEnChangeEditDepositAmount()
//{
//	// TODO:  如果该控件是 RICHEDIT 控件，它将不
//	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
//	// 函数并调用 CRichEditCtrl().SetEventMask()，
//	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
//
//	// TODO:  在此添加控件通知处理程序代码
//}


void AccountDeposit::OnKillfocusEditDepositCard()
{
	UpdateData(TRUE);
	CDatabase db;
	db.Open("bankmanagement");
	CString sqlstrconfirm,foundflag;
	sqlstrconfirm.Format(_T("select count(user_name) from user where user_id=(select user_id from card where card_number='%s')"), m_DepositCardnumber);
	CRecordset rs(&db);
	rs.Open(CRecordset::forwardOnly, (_T("%s"), sqlstrconfirm));
	rs.GetFieldValue(_T("count(user_name)"), foundflag);
	if (foundflag == '0'){
		MessageBox("这张卡不存在");
		GetDlgItem(IDC_ACCOUNT_DEPOSIT_COMFIRM)->EnableWindow(false);
	}
	else
	{
		GetDlgItem(IDC_ACCOUNT_DEPOSIT_COMFIRM)->EnableWindow(true);
		CString sqlstr;
		sqlstr.Format(_T("select user_name from user where user_id=(select user_id from card where card_number='%s')"), m_DepositCardnumber);
		CRecordset rss(&db);
		rss.Open(CRecordset::forwardOnly, (_T("%s"), sqlstr));
		rss.GetFieldValue(_T("user_name"), m_DepositUsername);
		//MessageBox(m_DepositUsername);
		UpdateData(FALSE);
		rss.Close();
	}
	rs.Close();
	db.Close();
	// TODO:  在此添加控件通知处理程序代码
}


//void AccountDeposit::OnSetfocusEditDepositAmount()
//{
//	/*UpdateData(TRUE);
//	if (m_DepositAmount == 0)GetDlgItem(IDC_EDIT_DEPOSIT_AMOUNT)->SetWindowTextA(_T(""));*/
//	// TODO:  在此添加控件通知处理程序代码
//}
