// ManagerAccountCard.cpp : 实现文件
//

#include "stdafx.h"
#include "bankmanagement.h"
#include "ManagerAccountCard.h"
#include "afxdialogex.h"


// ManagerAccountCard 对话框

IMPLEMENT_DYNAMIC(ManagerAccountCard, CDialogEx)

ManagerAccountCard::ManagerAccountCard(CWnd* pParent /*=NULL*/)
	: CDialogEx(ManagerAccountCard::IDD, pParent)
{

}

ManagerAccountCard::~ManagerAccountCard()
{
}

void ManagerAccountCard::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MANAGER_ACCOUNT_CARD, ManagerAccountCardList);
}


BEGIN_MESSAGE_MAP(ManagerAccountCard, CDialogEx)
END_MESSAGE_MAP()

BOOL ManagerAccountCard::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ModifyStyleEx(0, WS_EX_APPWINDOW);
	HICON m_hIcon;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ManagerAccountCardList.InsertColumn(1, _T("账户名"), LVCFMT_LEFT, 80);
	ManagerAccountCardList.InsertColumn(2, _T("银行卡号"), LVCFMT_LEFT, 80);
	ManagerAccountCardList.InsertColumn(3, _T("注册时间"), LVCFMT_LEFT, 80);
	ManagerAccountCardList.InsertColumn(4, _T("余额"), LVCFMT_LEFT, 80);
	ManagerAccountCardList.InsertColumn(5, _T("利率"), LVCFMT_LEFT, 80);
	ManagerAccountCardList.InsertColumn(6, _T("银行卡类型"), LVCFMT_LEFT, 80);
	ManagerAccountCardList.InsertColumn(7, _T("银行卡状态"), LVCFMT_LEFT, 80);

	CString sqlstr;
	sqlstr.Format(_T("select user.user_name,card.card_number,card.register_time,card.money_balance,card.money_interest,card.card_type,card.card_status from user,card where card.user_id='%d' and card.user_id=user.user_id"), dealid);

	ManagerAccountCardList.DeleteAllItems();
	CDatabase db;
	db.Open("bankmanagement");
	CRecordset rs(&db);
	rs.Open(CRecordset::forwardOnly, (_T("%s"), sqlstr));
	while (!rs.IsEOF())
	{
		CString varUserName;
		rs.GetFieldValue(_T("user_name"), varUserName);
		ManagerAccountCardList.InsertItem(0, varUserName);
		CString varCardNumber;
		rs.GetFieldValue(_T("card_number"), varCardNumber);
		ManagerAccountCardList.SetItemText(0, 1, varCardNumber);
		CString varRegisterTime;
		rs.GetFieldValue(_T("register_time"), varRegisterTime);
		ManagerAccountCardList.SetItemText(0, 2, varRegisterTime);
		CString varMoneyBalance;
		rs.GetFieldValue(_T("money_balance"), varMoneyBalance);
		ManagerAccountCardList.SetItemText(0, 3, varMoneyBalance);
		CString varMoneyInterest;
		rs.GetFieldValue(_T("money_interest"), varMoneyInterest);
		ManagerAccountCardList.SetItemText(0, 4, varMoneyInterest);
		CString varCardType;
		rs.GetFieldValue(_T("card_type"), varCardType);
		ManagerAccountCardList.SetItemText(0, 5, varCardType);
		CString varCardStatus;
		rs.GetFieldValue(_T("card_status"), varCardStatus);
		ManagerAccountCardList.SetItemText(0, 6, varCardStatus);

		rs.MoveNext();
	}
	ManagerAccountCardList.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);


	rs.Close();
	db.Close();
	return true;
}
// ManagerAccountCard 消息处理程序
