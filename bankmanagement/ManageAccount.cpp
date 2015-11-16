// ManageAccount.cpp : 实现文件
//

#include "stdafx.h"
#include "bankmanagement.h"
#include "ManageAccount.h"
#include "afxdialogex.h"


// ManageAccount 对话框

IMPLEMENT_DYNAMIC(ManageAccount, CDialogEx)

ManageAccount::ManageAccount(CWnd* pParent /*=NULL*/)
	: CDialogEx(ManageAccount::IDD, pParent)
	, m_ManageaccountUsername(_T(""))
	, m_ManageaccountIdcard(_T(""))
	, m_ManageaccountAddress(_T(""))
	, m_ManageaccountEmail(_T(""))
	, m_ManageaccountPhone(_T(""))
{

}

ManageAccount::~ManageAccount()
{
}

void ManageAccount::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MANAGE_ACCOUNT_USERNAME, m_ManageaccountUsername);
	DDX_Text(pDX, IDC_MANAGE_ACCOUNT_IDCARD, m_ManageaccountIdcard);
	DDX_Text(pDX, IDC_MANAGE_ACCOUNT_ADDRESS, m_ManageaccountAddress);
	DDX_Text(pDX, IDC_MANAGE_ACCOUNT_EMAIL, m_ManageaccountEmail);
	DDX_Text(pDX, IDC_MANAGE_ACCOUNT_PHONE, m_ManageaccountPhone);
}


BEGIN_MESSAGE_MAP(ManageAccount, CDialogEx)
	ON_BN_CLICKED(IDC_MANAGE_MODIFY_MODIFY, &ManageAccount::OnClickedManageModifyModify)
END_MESSAGE_MAP()

BOOL ManageAccount::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString sqlstr;
	sqlstr.Format(_T("select user_name,user_idcard,user_address,user_email,phone_number from user where user_id ='%d'"), dealid);
	
	CDatabase db;
	db.Open("bankmanagement");
	CRecordset rs(&db);
	rs.Open(CRecordset::forwardOnly, (_T("%s"), sqlstr));
	rs.GetFieldValue(_T("user_name"), m_ManageaccountUsername);
	rs.GetFieldValue(_T("user_idcard"), m_ManageaccountIdcard);
	rs.GetFieldValue(_T("user_address"), m_ManageaccountAddress);
	rs.GetFieldValue(_T("user_email"), m_ManageaccountEmail);
	rs.GetFieldValue(_T("phone_number"), m_ManageaccountPhone);
	

	rs.Close();
	db.Close();
	UpdateData(false);
	if (modifyflag == 0)
	{
		GetDlgItem(IDC_MANAGE_ACCOUNT_USERNAME)->EnableWindow(false);
		GetDlgItem(IDC_MANAGE_ACCOUNT_IDCARD)->EnableWindow(false);
		GetDlgItem(IDC_MANAGE_ACCOUNT_ADDRESS)->EnableWindow(false);
		GetDlgItem(IDC_MANAGE_ACCOUNT_EMAIL)->EnableWindow(false);
		GetDlgItem(IDC_MANAGE_ACCOUNT_PHONE)->EnableWindow(false);
		GetDlgItem(IDC_MANAGE_MODIFY_MODIFY)->ShowWindow(SW_HIDE);
	}
	else
	{
		GetDlgItem(IDC_MANAGE_ACCOUNT_USERNAME)->EnableWindow(false);
		GetDlgItem(IDC_MANAGE_ACCOUNT_IDCARD)->EnableWindow(true);
		GetDlgItem(IDC_MANAGE_ACCOUNT_ADDRESS)->EnableWindow(true);
		GetDlgItem(IDC_MANAGE_ACCOUNT_EMAIL)->EnableWindow(true);
		GetDlgItem(IDC_MANAGE_ACCOUNT_PHONE)->EnableWindow(true);
		GetDlgItem(IDC_MANAGE_MODIFY_MODIFY)->ShowWindow(SW_SHOW);
	}
	return true;
}

// ManageAccount 消息处理程序


void ManageAccount::OnClickedManageModifyModify()
{
	UpdateData(true);
	CString sqlstr;
	sqlstr.Format(_T("update user set user_name='%s',user_idcard='%s',user_address='%s',user_email='%s',phone_number='%s' where user_id ='%d'"), m_ManageaccountUsername, m_ManageaccountIdcard, m_ManageaccountAddress, m_ManageaccountEmail, m_ManageaccountPhone,dealid);
	CDatabase db;
	db.Open("bankmanagement");
	db.ExecuteSQL(sqlstr);
	db.Close();
	MessageBox("更新成功，点击返回。");
	OnOK();
	// TODO:  在此添加控件通知处理程序代码
}
