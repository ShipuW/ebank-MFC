// ManagerDeal.cpp : 实现文件
//

#include "stdafx.h"
#include "bankmanagement.h"
#include "ManagerDeal.h"
#include "afxdialogex.h"


// ManagerDeal 对话框

IMPLEMENT_DYNAMIC(ManagerDeal, CDialogEx)

ManagerDeal::ManagerDeal(CWnd* pParent /*=NULL*/)
	: CDialogEx(ManagerDeal::IDD, pParent)
{

}

ManagerDeal::~ManagerDeal()
{
}

void ManagerDeal::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DEAL_APPLY, CardApplyList);
	DDX_Control(pDX, IDC_LIST_DEAL_FREEZE, CardFreezeList);
	DDX_Control(pDX, IDC_LIST_DEAL_WITHDRAW, CardWithdrawList);
	DDX_Control(pDX, IDC_LIST_DEAL_FORGET, CardForgetList);
}


BEGIN_MESSAGE_MAP(ManagerDeal, CDialogEx)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_DEAL_APPLY, &ManagerDeal::OnRclickListDealApply)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_DEAL_FREEZE, &ManagerDeal::OnRclickListDealFreeze)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_DEAL_WITHDRAW, &ManagerDeal::OnRclickListDealWithdraw)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_DEAL_FORGET, &ManagerDeal::OnRclickListDealForget)
	ON_COMMAND(ID_APPLY_PASS, &ManagerDeal::OnApplyPass)
	ON_COMMAND(ID_APPLY_NOTPASS, &ManagerDeal::OnApplyNotpass)
	ON_COMMAND(ID_FREEZE_CANCEL, &ManagerDeal::OnFreezeCancel)
	ON_COMMAND(ID_FREEZE_CONFIRM, &ManagerDeal::OnFreezeConfirm)
	ON_COMMAND(ID_SEND_PWD, &ManagerDeal::OnSendPwd)
	ON_COMMAND(ID_WITHDRAW_CONFIRM, &ManagerDeal::OnWithdrawConfirm)
	ON_COMMAND(ID_WITHDRAW_REJECT, &ManagerDeal::OnWithdrawReject)
END_MESSAGE_MAP()

CString cardid;

BOOL ManagerDeal::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	while (CardApplyList.DeleteColumn(0));
	CardApplyList.InsertColumn(1, _T("卡片编号"), LVCFMT_LEFT, 80);
	CardApplyList.InsertColumn(2, _T("账户名称"), LVCFMT_LEFT, 80);
	CardApplyList.InsertColumn(3, _T("身份证号"), LVCFMT_LEFT, 80);
	CardApplyList.InsertColumn(4, _T("开户地"), LVCFMT_LEFT, 80);
	CardApplyList.InsertColumn(5, _T("申请类型"), LVCFMT_LEFT, 80);
	CardApplyList.InsertColumn(6, _T("申请时间"), LVCFMT_LEFT, 150);

	while (CardFreezeList.DeleteColumn(0));
	CardFreezeList.InsertColumn(1, _T("卡片编号"), LVCFMT_LEFT, 80);
	CardFreezeList.InsertColumn(2, _T("银行卡号"), LVCFMT_LEFT, 80);
	CardFreezeList.InsertColumn(3, _T("账户名称"), LVCFMT_LEFT, 80);
	//CardFreezeList.InsertColumn(3, _T("冻结时间"), LVCFMT_LEFT, 80);

	while (CardForgetList.DeleteColumn(0));
	CardForgetList.InsertColumn(1, _T("卡片编号"), LVCFMT_LEFT, 80);
	CardForgetList.InsertColumn(2, _T("银行卡号"), LVCFMT_LEFT, 80);
	CardForgetList.InsertColumn(3, _T("账户名称"), LVCFMT_LEFT, 80);

	while (CardWithdrawList.DeleteColumn(0));
	CardWithdrawList.InsertColumn(1, _T("卡片编号"), LVCFMT_LEFT, 80);
	CardWithdrawList.InsertColumn(2, _T("银行卡号"), LVCFMT_LEFT, 80);
	CardWithdrawList.InsertColumn(3, _T("账户名称"), LVCFMT_LEFT, 80);

	CString sqlstrapply, sqlstrfreeze, sqlstrforget, sqlstrwithdraw;
	sqlstrapply.Format(_T("select card.card_id,user.user_name,user.user_idcard,user.user_address,card.card_type,card.register_time from user,card where user.user_id=card.user_id and card.card_status='待审核'"));
	sqlstrfreeze.Format(_T("select card.card_id,card.card_number,user.user_name from user,card where user.user_id=card.user_id and card.card_status='冻结'"));
	sqlstrforget.Format(_T("select card.card_id,card.card_number,user.user_name from user,card where user.user_id=card.user_id and card.card_status='申请密码找回'"));
	sqlstrwithdraw.Format(_T("select card.card_id,card.card_number,user.user_name from user,card where user.user_id=card.user_id and card.card_status='申请注销'"));

	CardApplyList.DeleteAllItems();
	CardFreezeList.DeleteAllItems();
	CardForgetList.DeleteAllItems();
	CardWithdrawList.DeleteAllItems();

	CDatabase db;
	db.Open("bankmanagement");
	
	CRecordset rs(&db);
	rs.Open(CRecordset::forwardOnly, (_T("%s"), sqlstrapply));
	while (!rs.IsEOF())
	{

		CString varCardId;
		rs.GetFieldValue(_T("card_id"), varCardId);
		CardApplyList.InsertItem(0, varCardId);
		
		CString varUserName;
		rs.GetFieldValue(_T("user_name"), varUserName);
		CardApplyList.SetItemText(0, 1, varUserName);

		CString varUserIdcard;
		rs.GetFieldValue(_T("user_idcard"), varUserIdcard);
		CardApplyList.SetItemText(0, 2, varUserIdcard);

		CString varUserAddress;
		rs.GetFieldValue(_T("user_address"), varUserAddress);
		CardApplyList.SetItemText(0, 3, varUserAddress);

		CString varCardType;
		rs.GetFieldValue(_T("card_type"), varCardType);
		CardApplyList.SetItemText(0, 4, varCardType);
		
		CString varRegisterTime;
		rs.GetFieldValue(_T("register_time"), varRegisterTime);
		CardApplyList.SetItemText(0, 5, varRegisterTime);
		
		rs.MoveNext();
	}
	CardApplyList.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	rs.Close();
	
	CRecordset rss(&db);
	rss.Open(CRecordset::forwardOnly, (_T("%s"), sqlstrfreeze));
	while (!rss.IsEOF())
	{
		CString varCardId;
		rss.GetFieldValue(_T("card_id"), varCardId);
		CardFreezeList.InsertItem(0, varCardId);

		CString varCardNumber;
		rss.GetFieldValue(_T("card_number"), varCardNumber);
		CardFreezeList.SetItemText(0, 1, varCardNumber);

		
		CString varUserName;
		rss.GetFieldValue(_T("user_name"), varUserName);
		CardFreezeList.SetItemText(0, 2, varUserName);

		rss.MoveNext();
	}
	CardFreezeList.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	rss.Close();

	CRecordset rsss(&db);
	rsss.Open(CRecordset::forwardOnly, (_T("%s"), sqlstrforget));
	while (!rsss.IsEOF())
	{
		CString varCardId;
		rsss.GetFieldValue(_T("card_id"), varCardId);
		CardForgetList.InsertItem(0, varCardId);

		CString varCardNumber;
		rsss.GetFieldValue(_T("card_number"), varCardNumber);
		CardForgetList.SetItemText(0, 1, varCardNumber);


		CString varUserName;
		rsss.GetFieldValue(_T("user_name"), varUserName);
		CardForgetList.SetItemText(0, 2, varUserName);

		rsss.MoveNext();
	}
	CardForgetList.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	rsss.Close();

	CRecordset rssss(&db);
	rssss.Open(CRecordset::forwardOnly, (_T("%s"), sqlstrwithdraw));
	while (!rssss.IsEOF())
	{
		CString varCardId;
		rssss.GetFieldValue(_T("card_id"), varCardId);
		CardWithdrawList.InsertItem(0, varCardId);

		CString varCardNumber;
		rssss.GetFieldValue(_T("card_number"), varCardNumber);
		CardWithdrawList.SetItemText(0, 1, varCardNumber);


		CString varUserName;
		rssss.GetFieldValue(_T("user_name"), varUserName);
		CardWithdrawList.SetItemText(0, 2, varUserName);

		rssss.MoveNext();
	}
	CardWithdrawList.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	rssss.Close();

	db.Close();
	return true;
}

// ManagerDeal 消息处理程序


void ManagerDeal::OnRclickListDealApply(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE >(pNMHDR);
	CMenu popMenu;
	popMenu.LoadMenu(IDR_MENU_APPLY);
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


void ManagerDeal::OnRclickListDealFreeze(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	CMenu popMenu;
	popMenu.LoadMenu(IDR_MENU_FREEZE);
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

void ManagerDeal::OnRclickListDealWithdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE >(pNMHDR);
	CMenu popMenu;
	popMenu.LoadMenu(IDR_MENU_WITHDRAW);
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


void ManagerDeal::OnRclickListDealForget(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE >(pNMHDR);
	CMenu popMenu;
	popMenu.LoadMenu(IDR_MENU_FORGET);
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ManagerDeal::OnApplyPass()
{
	int i = CardApplyList.GetSelectionMark();
	cardid = CardApplyList.GetItemText(i, 0);
	//MessageBox(cardid);

	if (cardid.IsEmpty());
	else{
		CDatabase db;
		db.Open("bankmanagement");
		CString timestr, cardtimestr;//////获取系统时间,卡号分配


		CTime tm; tm = CTime::GetCurrentTime();
		timestr = tm.Format("%Y年%m月%d日 %X");
		cardtimestr = tm.Format("%Y%m%d");
		CString cardnumber, cardtype, cardtypenumber, cardnumberlastthree;
		CString sqlstr;
		sqlstr.Format(_T("select card_type from card where card_id='%s'"), cardid);
		CRecordset rsss(&db);
		rsss.Open(CRecordset::forwardOnly, (_T("%s"), sqlstr));
		rsss.GetFieldValue(_T("card_type"), cardtype);
		if (cardtype == "VIP卡"){ cardtypenumber = '0'; }
		else if (cardtype == "年卡"){ cardtypenumber = '1'; }
		else if (cardtype == "月卡"){ cardtypenumber = '2'; }
		else if (cardtype == "日卡"){ cardtypenumber = '3'; }
		int number = rand() % 1000;;
		CString sqlstrisrepeat, strrepeatnumber;
		cardnumberlastthree.Format(_T("%03d"), number);
		cardnumber = cardtimestr + cardtypenumber +cardnumberlastthree;
		int repeatnumber;
		rsss.Close();
		
		CRecordset rss(&db);
		while (1)
		{
			
			sqlstrisrepeat.Format(_T("select count(*) from card where card_number='%s'"), cardnumber);
			
			rss.Open(CRecordset::forwardOnly, (_T("%s"), sqlstrisrepeat));
			rss.GetFieldValue(_T("count(*)"), strrepeatnumber);
			repeatnumber = _ttoi(strrepeatnumber);
			rss.Close();
			if (strrepeatnumber == '0') { break; }
			number = rand() % 1000;
			cardnumberlastthree.Format(_T("%03d"), number);
			cardnumber = cardtimestr + cardtypenumber + cardnumberlastthree;
		}
		
		sqlstr.Format(_T("update card set card_number='%s',card_status='正常',register_time='%s' where card_id='%s'"), cardnumber, timestr,cardid);
		db.ExecuteSQL(sqlstr);

		db.Close();
		MessageBox("处理成功！");
		ManagerDeal::OnInitDialog();
	}
	// TODO:  在此添加命令处理程序代码
}


void ManagerDeal::OnApplyNotpass()
{
	int i = CardApplyList.GetSelectionMark();
	cardid = CardApplyList.GetItemText(i, 0);
	//MessageBox(cardid);
	if (cardid.IsEmpty());
	else
	{
		CDatabase db;
		db.Open("bankmanagement");
		CString sqlstr;
		sqlstr.Format(_T("update card set card_status='未通过' where card_id='%s'"), cardid);
		db.ExecuteSQL(sqlstr);
		db.Close();
		MessageBox("处理成功！");
		ManagerDeal::OnInitDialog();
	}
	// TODO:  在此添加命令处理程序代码
}


void ManagerDeal::OnFreezeCancel()
{
	int i = CardFreezeList.GetSelectionMark();
	cardid = CardFreezeList.GetItemText(i, 0);
	//MessageBox(cardid);
	if (cardid.IsEmpty());
	else
	{
		CDatabase db;
		db.Open("bankmanagement");
		CString sqlstr;
		sqlstr.Format(_T("update card set card_status='正常' where card_id='%s'"), cardid);
		db.ExecuteSQL(sqlstr);
		db.Close();
		MessageBox("处理成功！");
		ManagerDeal::OnInitDialog();
	}
	// TODO:  在此添加命令处理程序代码
}


void ManagerDeal::OnFreezeConfirm()
{
	int i = CardFreezeList.GetSelectionMark();
	cardid = CardFreezeList.GetItemText(i, 0);
	//MessageBox(cardid);
	if (cardid.IsEmpty());
	else
	{
		CDatabase db;
		db.Open("bankmanagement");
		CString sqlstr;
		sqlstr.Format(_T("update card set card_status='注销',card_number='' where card_id='%s'"), cardid);
		db.ExecuteSQL(sqlstr);
		db.Close();
		MessageBox("处理成功！");
		ManagerDeal::OnInitDialog();
	}
	// TODO:  在此添加命令处理程序代码
}






void ManagerDeal::OnSendPwd()
{
	int i = CardForgetList.GetSelectionMark();
	cardid = CardForgetList.GetItemText(i, 0);
	//MessageBox(cardid);
	if (cardid.IsEmpty());
	else
	{
		CDatabase db;
		db.Open("bankmanagement");
		CString sqlstr;
		sqlstr.Format(_T("update card set card_password='111111',card_status='正常' where card_id='%s'"), cardid);
		db.ExecuteSQL(sqlstr);
		db.Close();
		MessageBox("处理成功！");
		ManagerDeal::OnInitDialog();
	}
	// TODO:  在此添加命令处理程序代码
}


void ManagerDeal::OnWithdrawConfirm()
{
	int i = CardWithdrawList.GetSelectionMark();
	cardid = CardWithdrawList.GetItemText(i, 0);
	//MessageBox(cardid);
	if (cardid.IsEmpty());
	else
	{
		CDatabase db;
		db.Open("bankmanagement");
		CString sqlstr;
		sqlstr.Format(_T("update card set card_status='注销',card_number='' where card_id='%s'"), cardid);
		db.ExecuteSQL(sqlstr);
		db.Close();
		MessageBox("处理成功！");
		ManagerDeal::OnInitDialog();
	}
	// TODO:  在此添加命令处理程序代码
}


void ManagerDeal::OnWithdrawReject()
{
	int i = CardWithdrawList.GetSelectionMark();
	cardid = CardWithdrawList.GetItemText(i, 0);
	//MessageBox(cardid);
	if (cardid.IsEmpty());
	else
	{
		CDatabase db;
		db.Open("bankmanagement");
		CString sqlstr;
		sqlstr.Format(_T("update card set card_status='正常' where card_id='%s'"), cardid);
		db.ExecuteSQL(sqlstr);
		db.Close();
		MessageBox("处理成功！");
		ManagerDeal::OnInitDialog();
	}
	// TODO:  在此添加命令处理程序代码
	// TODO:  在此添加命令处理程序代码
}
