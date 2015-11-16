// ManagerAccount.cpp : 实现文件
//

#include "stdafx.h"
#include "bankmanagement.h"
#include "ManagerAccount.h"
#include "afxdialogex.h"
#include "ManageAccount.h"
#include "ManagerAccountCard.h"

// ManagerAccount 对话框

IMPLEMENT_DYNAMIC(ManagerAccount, CDialogEx)

ManagerAccount::ManagerAccount(CWnd* pParent /*=NULL*/)
	: CDialogEx(ManagerAccount::IDD, pParent)
{

}

ManagerAccount::~ManagerAccount()
{
}

void ManagerAccount::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ACCOUNT, ListAccount);
}


BEGIN_MESSAGE_MAP(ManagerAccount, CDialogEx)
	ON_COMMAND(ID_ACCOUNT_DELETE, &ManagerAccount::OnAccountDelete)
	ON_COMMAND(ID_ACCOUNT_MODIFY, &ManagerAccount::OnAccountModify)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_ACCOUNT, &ManagerAccount::OnRclickListAccount)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ACCOUNT, &ManagerAccount::OnDblclkListAccount)
	ON_COMMAND(ID_ACCOUNT_CARD, &ManagerAccount::OnAccountCard)
END_MESSAGE_MAP()

int modifyflag = 0;
CString userid;
int dealid;

BOOL ManagerAccount::OnInitDialog()
	{
	CDialogEx::OnInitDialog();
	while (ListAccount.DeleteColumn(0));
	ListAccount.InsertColumn(1, _T("账户编号"), LVCFMT_LEFT, 80);
	ListAccount.InsertColumn(2, _T("账户名称"), LVCFMT_LEFT, 200);
	

	CString sqlstr;
	sqlstr.Format(_T("select user_id,user_name from user"));
	

	ListAccount.DeleteAllItems();
	
	CDatabase db;
	db.Open("bankmanagement");

	CRecordset rs(&db);
	rs.Open(CRecordset::forwardOnly, (_T("%s"), sqlstr));
	while (!rs.IsEOF())
	{

		CString varUserId;
		rs.GetFieldValue(_T("user_id"), varUserId);
		ListAccount.InsertItem(0, varUserId);

		CString varUserName;
		rs.GetFieldValue(_T("user_name"), varUserName);
		ListAccount.SetItemText(0, 1, varUserName);


		rs.MoveNext();
	}
	ListAccount.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	rs.Close();

	
	db.Close();
	return true;
}

// ManagerAccount 消息处理程序


void ManagerAccount::OnAccountDelete()
{
	int i = ListAccount.GetSelectionMark();
	userid = ListAccount.GetItemText(i, 0);
	//MessageBox(cardid);
	if (userid.IsEmpty());
	else{
		CDatabase db;
		db.Open("bankmanagement");
		CString sqlstr;
		
		sqlstr.Format(_T("delete from user where user_id='%d'"), _ttoi(userid));
		db.ExecuteSQL(sqlstr);
		db.Close();
		MessageBox("处理成功！");
		ManagerAccount::OnInitDialog();
	}
	// TODO:  在此添加命令处理程序代码
}


void ManagerAccount::OnAccountModify()
{
	modifyflag = 1;
	int i = ListAccount.GetSelectionMark();
	userid = ListAccount.GetItemText(i, 0);
	dealid = _ttoi(userid);
	ManageAccount dlg;
	//ShowWindow(SW_HIDE);
	dlg.DoModal();
	//ShowWindow(SW_SHOW);
	// TODO:  在此添加命令处理程序代码
}


void ManagerAccount::OnRclickListAccount(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	CMenu popMenu;
	popMenu.LoadMenu(IDR_MENU_ACCOUNT);
	CMenu *pPopup;
	pPopup = popMenu.GetSubMenu(0);

	CPoint point;
	::GetCursorPos(&point);
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	pPopup->Detach();
	popMenu.DestroyMenu();
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
}


void ManagerAccount::OnDblclkListAccount(NMHDR *pNMHDR, LRESULT *pResult)//////////////////////查看详细信息
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	modifyflag = 0;
	int i = ListAccount.GetSelectionMark();
	userid = ListAccount.GetItemText(i, 0);
	dealid = _ttoi(userid);
	ManageAccount dlg;
	//ShowWindow(SW_HIDE);
	dlg.DoModal();
	//ShowWindow(SW_SHOW);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
}


void ManagerAccount::OnAccountCard()
{
	int i = ListAccount.GetSelectionMark();
	userid = ListAccount.GetItemText(i, 0);
	dealid = _ttoi(userid);
	ManagerAccountCard dlg;
	//ShowWindow(SW_HIDE);
	dlg.DoModal();
	//ShowWindow(SW_SHOW);
	// TODO:  在此添加命令处理程序代码
}
