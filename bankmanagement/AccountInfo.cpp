d// AccountInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "bankmanagement.h"
#include "AccountInfo.h"
#include "afxdialogex.h"
#include "ChangePassword.h"

// AccountInfo 对话框

IMPLEMENT_DYNAMIC(AccountInfo, CDialogEx)

AccountInfo::AccountInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(AccountInfo::IDD, pParent)
	, m_InfoUsername(_T(""))
	, m_Infoaddress(_T(""))
	, m_Infoemail(_T(""))
	, m_Infophone(_T(""))
{

}

AccountInfo::~AccountInfo()
{
}

void AccountInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_INFO_USER, m_InfoUsername);
	DDX_Text(pDX, IDC_EDIT_INFO_ADDRESS, m_Infoaddress);
	DDX_Text(pDX, IDC_EDIT_INFO_EMAIL, m_Infoemail);
	DDX_Text(pDX, IDC_EDIT_INFO_PHONE, m_Infophone);
	DDX_Text(pDX, IDC_EDIT_INFO_IDCARD, m_InfoIdcard);
}


BEGIN_MESSAGE_MAP(AccountInfo, CDialogEx)
	ON_BN_CLICKED(IDC_CHANGE_INFO, &AccountInfo::OnClickedChangeInfo)
	ON_BN_CLICKED(IDC_CHANGE_PASSWORD, &AccountInfo::OnClickedChangePassword)
//	ON_EN_CHANGE(IDC_EDIT_INFO_IDCARD, &AccountInfo::OnEnChangeEditInfoIdcard)
END_MESSAGE_MAP()

BOOL AccountInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString sqlstr;
	m_InfoUsername = CurrentUser;
	sqlstr.Format(_T("select user_idcard,user_address,user_email,phone_number from user where user_name='%s'"), CurrentUser);

	//AccountCard.DeleteAllItems();
	CDatabase db;
	db.Open("bankmanagement");
	CRecordset rs(&db);
	rs.Open(CRecordset::forwardOnly, (_T("%s"), sqlstr));
	while (!rs.IsEOF())
	{
		rs.GetFieldValue(_T("user_idcard"), m_InfoIdcard);
		rs.GetFieldValue(_T("user_address"), m_Infoaddress);
		
		rs.GetFieldValue(_T("user_email"), m_Infoemail);
		
		rs.GetFieldValue(_T("phone_number"), m_Infophone);
		rs.MoveNext();
	}
	UpdateData(false);
	
	rs.Close();
	db.Close();
	
	return true;
}

// AccountInfo 消息处理程序


void AccountInfo::OnClickedChangeInfo()
{
	if (infoflag == 1){
		infoflag = 0;
		//GetDlgItem(IDC_EDIT_INFO_USER)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_INFO_IDCARD)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_INFO_ADDRESS)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_INFO_EMAIL)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_INFO_PHONE)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHANGE_INFO)->SetWindowTextA("确认修改");
	}
	else
	{
		infoflag = 1;
		CDatabase db;
		db.Open("bankmanagement");
		CString sqlstr;//,username,idcard,pwd,address,email,number;
		UpdateData(TRUE);//更新文本框变量
		//MessageBox(m_RegUsername);
		sqlstr.Format(_T("update user set user_idcard='%s',user_address='%s',user_email='%s',phone_number='%s' where user_name='%s'"), m_InfoIdcard, m_Infoaddress, m_Infoemail, m_Infophone, m_InfoUsername);
		db.ExecuteSQL(sqlstr);
		db.Close();
		MessageBox("修改成功！");
		UpdateData(FALSE);
		GetDlgItem(IDC_EDIT_INFO_IDCARD)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_INFO_ADDRESS)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_INFO_EMAIL)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_INFO_PHONE)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHANGE_INFO)->SetWindowTextA("修改信息");
	}
	// TODO:  在此添加控件通知处理程序代码
}


void AccountInfo::OnClickedChangePassword()
{
	ChangePassword dlg;
	//ShowWindow(SW_HIDE);
	dlg.DoModal();
	//ShowWindow(SW_SHOW);
	// TODO:  在此添加控件通知处理程序代码
}


//void AccountInfo::OnEnChangeEditInfoIdcard()
//{
//	// TODO:  如果该控件是 RICHEDIT 控件，它将不
//	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
//	// 函数并调用 CRichEditCtrl().SetEventMask()，
//	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
//
//	// TODO:  在此添加控件通知处理程序代码
//}
