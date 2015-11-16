// Regist.cpp : 实现文件
//

#include "stdafx.h"
#include "bankmanagement.h"
#include "Regist.h"
#include "afxdialogex.h"
#include "Hello.h"

// Regist 对话框

IMPLEMENT_DYNAMIC(Regist, CDialogEx)

Regist::Regist(CWnd* pParent /*=NULL*/)
	: CDialogEx(Regist::IDD, pParent)
	, m_RegUsername(_T("用户名为字母与数字组合"))
	, m_RegPwdConfirm(_T(""))
	, m_RegPwd(_T(""))
	, m_RegPhone(_T(""))
	, m_RegIdcard(_T(""))
	, m_RegEmail(_T(""))
	, m_RegAddress(_T(""))
//	, m_RegPwdconfirm(_T(""))
{

}

Regist::~Regist()
{
}

void Regist::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_REGIST_USERNAME, m_RegUsername);
	DDX_Text(pDX, IDC_EDIT_REGIST_PWD, m_RegPwd);
	DDX_Text(pDX, IDC_EDIT_REGIST_PHONE, m_RegPhone);
	DDX_Text(pDX, IDC_EDIT_REGIST_IDCARD, m_RegIdcard);
	DDX_Text(pDX, IDC_EDIT_REGIST_EMAIL, m_RegEmail);
	DDX_Text(pDX, IDC_EDIT_REGIST_ADDRESS, m_RegAddress);
	DDX_Text(pDX, IDC_EDIT_REGIST_PWD_CONFIRM, m_RegPwdConfirm);
}


BEGIN_MESSAGE_MAP(Regist, CDialogEx)
ON_BN_CLICKED(IDC_REGIST_REGIST, &Regist::OnClickedRegistRegist)
//	ON_EN_CHANGE(IDC_EDIT_REGIST_PWD, &Regist::OnEnChangeEditRegistPwd)
ON_EN_SETFOCUS(IDC_EDIT_REGIST_USERNAME, &Regist::OnSetfocusEditRegistUsername)
ON_EN_KILLFOCUS(IDC_EDIT_REGIST_USERNAME, &Regist::OnKillfocusEditRegistUsername)
//ON_EN_SETFOCUS(IDC_EDIT_REGIST_PWD, &Regist::OnSetfocusEditRegistPwd)
ON_BN_CLICKED(IDC_REGIST_CANCEL, &Regist::OnClickedRegistCancel)
ON_EN_KILLFOCUS(IDC_EDIT_REGIST_EMAIL, &Regist::OnKillfocusEditRegistEmail)
END_MESSAGE_MAP()

BOOL Regist::OnInitDialog()
{
	this->GetParent()->SendMessage(WM_CLOSE);//关闭父对话框
	CDialogEx::OnInitDialog();
	ModifyStyleEx(0, WS_EX_APPWINDOW);
	HICON m_hIcon;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	return true;
}

// Regist 消息处理程序


void Regist::OnClickedRegistRegist()
{
	CDatabase db;
	db.Open("bankmanagement");
	CString sqlstr;//,username,idcard,pwd,address,email,number;
	UpdateData(TRUE);//更新文本框变量
	//MessageBox(m_RegUsername);

	sqlstr.Format(_T("insert into user(user_name,user_idcard,user_pwd,user_address,user_email,phone_number) values('%s','%s','%s','%s','%s','%s')"), m_RegUsername, m_RegIdcard, m_RegPwd, m_RegAddress, m_RegEmail, m_RegPhone);
	if (m_RegUsername.IsEmpty() || m_RegPwd.IsEmpty() || m_RegPwdConfirm.IsEmpty() || m_RegIdcard.IsEmpty() || m_RegAddress.IsEmpty() || m_RegEmail.IsEmpty())
	{
		MessageBox("带*为必填项", "输入有误");
	}
	else if (m_RegUsername == "用户名为字母与数字组合")
	{
		MessageBox("用户名未修改");
	}
	else if (m_RegPwd.GetLength() < 6)
	{
		MessageBox("密码太短！","输入有误");
	}
	else if (m_RegPwd != m_RegPwdConfirm)
	{
		MessageBox("输入密码不一致", "输入有误");
	}
	else
	{
		db.ExecuteSQL(sqlstr);
		db.Close();
		MessageBox("注册成功！返回登录。");
		//this->GetParent()->SendMessage(WM_CLOSE);//关闭父对话框
		Hello dlg;
		fatherflag = 1;
		ShowWindow(SW_HIDE);
		dlg.DoModal();
		ShowWindow(SW_SHOW);
	}
	// TODO:  在此添加控件通知处理程序代码
}


//void Regist::OnEnChangeEditRegistPwd()
//{
//	// TODO:  如果该控件是 RICHEDIT 控件，它将不
//	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
//	// 函数并调用 CRichEditCtrl().SetEventMask()，
//	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
//
//	// TODO:  在此添加控件通知处理程序代码
//}


void Regist::OnSetfocusEditRegistUsername()
{
	UpdateData(TRUE);
	if (m_RegUsername == "用户名为字母与数字组合")
		SetDlgItemText(IDC_EDIT_REGIST_USERNAME, "");///////点击编辑框清空内容
	// TODO:  在此添加控件通知处理程序代码
}


void Regist::OnKillfocusEditRegistUsername()
{
	UpdateData(TRUE);
	CDatabase db;
	db.Open("bankmanagement");
	CString sqlstr;
	sqlstr.Format(_T("select count(*) from user where user_name='%s'"), m_RegUsername);
	CRecordset rs(&db);
	rs.Open(CRecordset::forwardOnly, (_T("%s"), sqlstr));
	CString	count;
	rs.GetFieldValue(_T("count(*)"),count);
	//MessageBox(count);
	if (count == '1')
	{
		GetDlgItem(IDC_NAME_NOTICE)->SetWindowTextA((CString)"×用户名已存在！");
		GetDlgItem(IDC_REGIST_REGIST)->EnableWindow(false);
	}//MessageBox("用户名已存在，请重新输入。", "输入有误");
	else
	{
		GetDlgItem(IDC_NAME_NOTICE)->SetWindowTextA((CString)"√可以使用");
		GetDlgItem(IDC_REGIST_REGIST)->EnableWindow(true);
	}
	rs.Close();
	db.Close();
	// TODO:  在此添加控件通知处理程序代码
}


//void Regist::OnSetfocusEditRegistPwd()
//{
//	UpdateData(TRUE);
//	if (m_RegUsername == "密码至少6位")
//	{
//		SetDlgItemText(IDC_EDIT_REGIST_PWD, "");
//		GetDlgItem(IDC_EDIT_REGIST_PWD)->
//	}
//		// TODO:  在此添加控件通知处理程序代码
//}


void Regist::OnClickedRegistCancel()
{
	Hello dlg;
	fatherflag = 1;
	ShowWindow(SW_HIDE);
	dlg.DoModal();
	ShowWindow(SW_SHOW);
	// TODO:  在此添加控件通知处理程序代码
}


void Regist::OnKillfocusEditRegistEmail()
{
	UpdateData(TRUE);
	CDatabase db;
	db.Open("bankmanagement");
	CString sqlstr;
	sqlstr.Format(_T("select count(*) from user where user_email='%s'"), m_RegEmail);
	CRecordset rs(&db);
	rs.Open(CRecordset::forwardOnly, (_T("%s"), sqlstr));
	CString	count;
	rs.GetFieldValue(_T("count(*)"), count);
	//MessageBox(count);
	if (count == '1')
	{
		GetDlgItem(IDC_EMAIL_NOTICE)->SetWindowTextA((CString)"×邮箱已被注册！");
		GetDlgItem(IDC_REGIST_REGIST)->EnableWindow(false);
	}//MessageBox("用户名已存在，请重新输入。", "输入有误");
	else
	{
		GetDlgItem(IDC_EMAIL_NOTICE)->SetWindowTextA((CString)"√可以使用");
		GetDlgItem(IDC_REGIST_REGIST)->EnableWindow(true);
	}
	rs.Close();
	db.Close();
	// TODO:  在此添加控件通知处理程序代码
}
