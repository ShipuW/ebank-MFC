// ChangePassword.cpp : 实现文件
//

#include "stdafx.h"
#include "bankmanagement.h"
#include "ChangePassword.h"
#include "afxdialogex.h"


// ChangePassword 对话框

IMPLEMENT_DYNAMIC(ChangePassword, CDialogEx)

ChangePassword::ChangePassword(CWnd* pParent /*=NULL*/)
	: CDialogEx(ChangePassword::IDD, pParent)
	, m_Changepassword(_T(""))
	, m_Changepasswordconfirm(_T(""))
	, m_ChangeaccountPasswordbefore(_T(""))
{

}

ChangePassword::~ChangePassword()
{
}

void ChangePassword::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CHANGE_PWD, m_Changepassword);
	DDX_Text(pDX, IDC_EDIT_CHANGE_PWD_CONFIRM, m_Changepasswordconfirm);
	DDX_Text(pDX, IDC_ACCOUNT_PASSWORD_BEFORE, m_ChangeaccountPasswordbefore);
}


BEGIN_MESSAGE_MAP(ChangePassword, CDialogEx)
	ON_BN_CLICKED(IDC_CHANG_PWD_CHANGE, &ChangePassword::OnClickedChangPwdChange)
END_MESSAGE_MAP()

BOOL ChangePassword::OnInitDialog()
{

	CDialogEx::OnInitDialog();
	ModifyStyleEx(0, WS_EX_APPWINDOW);
	HICON m_hIcon;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	return true;
}

// ChangePassword 消息处理程序


void ChangePassword::OnClickedChangPwdChange()
{
	CDatabase db;
	db.Open("bankmanagement");
	CString sqlstr,dbpwd;
	UpdateData(TRUE);//更新文本框变量
	sqlstr.Format(_T("select user_pwd from user where user_name='%s'"), CurrentUser);
	CRecordset rs(&db);
	
	rs.Open(CRecordset::forwardOnly, (_T("%s"), sqlstr));
	rs.GetFieldValue(_T("user_pwd"), dbpwd);
	if (dbpwd == m_ChangeaccountPasswordbefore){

		sqlstr.Format(_T("update user set user_pwd='%s'where user_name='%s'"), m_Changepasswordconfirm, CurrentUser);
		if (m_Changepassword.IsEmpty() || m_Changepasswordconfirm.IsEmpty())
		{
			MessageBox("带*为必填项", "输入有误");
		}
		else if (m_Changepassword.GetLength() < 6)
		{
			MessageBox("密码太短！", "输入有误");
		}
		else if (m_Changepassword != m_Changepasswordconfirm)
		{
			MessageBox("输入密码不一致", "输入有误");
		}
		else
		{
			db.ExecuteSQL(sqlstr);
			db.Close();
			MessageBox("修改成功！");
			this->SendMessage(WM_CLOSE);
			//this->GetParent()->SendMessage(WM_CLOSE);//关闭父对话框

		}
	}
	else MessageBox("原密码错误！");
	// TODO:  在此添加控件通知处理程序代码
}
