// AccountProperty.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "bankmanagement.h"
#include "AccountProperty.h"
#include "afxdialogex.h"
#include "AccountApply.h"
#include "AccountDetail.h"

// AccountProperty �Ի���

IMPLEMENT_DYNAMIC(AccountProperty, CDialogEx)

AccountProperty::AccountProperty(CWnd* pParent /*=NULL*/)
	: CDialogEx(AccountProperty::IDD, pParent)
{

}

AccountProperty::~AccountProperty()
{
}

void AccountProperty::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ACCOUNT_PROPERTY_LIST, AccountCard);
}


BEGIN_MESSAGE_MAP(AccountProperty, CDialogEx)
	//ON_LBN_SELCHANGE(IDC_LIST3, &AccountProperty::OnLbnSelchangeList3)
	ON_BN_CLICKED(IDC_ACCOUNT_PROPERTY_APPLY, &AccountProperty::OnClickedAccountPropertyApply)
//	ON_NOTIFY(LVN_ITEMCHANGED, IDC_ACCOUNT_PROPERTY_LIST, &AccountProperty::OnLvnItemchangedAccountPropertyList)
ON_BN_CLICKED(IDC_ACCOUNT_PROPERTY_REFRESH, &AccountProperty::OnClickedAccountPropertyRefresh)
ON_NOTIFY(NM_DBLCLK, IDC_ACCOUNT_PROPERTY_LIST, &AccountProperty::OnDblclkAccountPropertyList)
END_MESSAGE_MAP()
int refreshflag = 1;
CString CardDetail="";
/////////////////////////////////////////////////�����ݿ�ȡ���������list

BOOL AccountProperty::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	if (refreshflag == 1){
		AccountCard.InsertColumn(1, _T("���п���"), LVCFMT_LEFT, 200);
		AccountCard.InsertColumn(2, _T("���п����"), LVCFMT_LEFT, 80);
		AccountCard.InsertColumn(3, _T("���п�״̬"), LVCFMT_LEFT, 80);
		refreshflag = 0;
	}
	CString sqlstr;
	sqlstr.Format(_T("select card_number,money_balance,card_status from card where user_id=(select user_id from user where user_name='%s')"), CurrentUser);

	AccountCard.DeleteAllItems();
	CDatabase db;
	db.Open("bankmanagement");
	CRecordset rs(&db);
	rs.Open(CRecordset::forwardOnly, (_T("%s"), sqlstr));
	while (!rs.IsEOF())
	{
		CString varCardNumber;
		rs.GetFieldValue(_T("card_number"), varCardNumber);
		AccountCard.InsertItem(0, varCardNumber);
		CString varMoneyBalance;
		rs.GetFieldValue(_T("money_balance"), varMoneyBalance);
		AccountCard.SetItemText(0,1, varMoneyBalance);
		CString varCardStatus;
		rs.GetFieldValue(_T("card_status"), varCardStatus);
		//MessageBox(varCardStatus);
		//varCardStatus = "��ʿ��";
		AccountCard.SetItemText(0, 2, varCardStatus);
		rs.MoveNext();
	}
	AccountCard.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	

	rs.Close();
	db.Close();
	return true;
}
// AccountProperty ��Ϣ�������



void AccountProperty::OnClickedAccountPropertyApply()
{
	AccountApply dlg;
//	ShowWindow(SW_HIDE);
	dlg.DoModal();
//	ShowWindow(SW_SHOW);

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}





void AccountProperty::OnClickedAccountPropertyRefresh()
{
	AccountProperty::OnInitDialog();
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void AccountProperty::OnDblclkAccountPropertyList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int i = AccountCard.GetSelectionMark();
	CardDetail = AccountCard.GetItemText(i, 0);/////////////////////�õ�����п���
	if (CardDetail.IsEmpty())MessageBox("���ܲ鿴���������п�");
	else
	{
		AccountDetail dlg;
	//	ShowWindow(SW_HIDE);
		dlg.DoModal();
	//	ShowWindow(SW_SHOW);
	}
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}
