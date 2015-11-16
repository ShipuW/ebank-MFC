// Hello.cpp : 实现文件
//

#include "stdafx.h"
#include "bankmanagement.h"
#include "Hello.h"
#include "afxdialogex.h"
#include "Login.h"
#include "Regist.h"
#include "ManageLogin.h"
// Hello 对话框

IMPLEMENT_DYNAMIC(Hello, CDialog)
CString CurrentUser="123";///////////////////////////////当前登录用户，全局
int fatherflag = 0;
Hello::Hello(CWnd* pParent /*=NULL*/)
	: CDialogEx(Hello::IDD, pParent)
{

}

Hello::~Hello()
{
}

void Hello::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Hello, CDialog)
	ON_BN_CLICKED(IDC_HELLO_LOGIN, &Hello::OnBnClickedHelloLogin)
	ON_BN_CLICKED(IDC_HELLO_REGIST, &Hello::OnClickedHelloRegist)
//	ON_BN_DOUBLECLICKED(IDC_HELLO_LOGIN, &Hello::OnDoubleclickedHelloLogin)
ON_BN_CLICKED(IDC_HELLO_MANAGER, &Hello::OnClickedHelloManager)
//ON_BN_CLICKED(IDC_BUTTON3, &Hello::OnClickedButton3)
END_MESSAGE_MAP()

BOOL Hello::OnInitDialog()
{
	if (fatherflag == 1){ this->GetParent()->SendMessage(WM_CLOSE); fatherflag = 0; }//关闭父对话框
	CDialogEx::OnInitDialog();
	HICON m_hIcon;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	return true;
}





// Hello 消息处理程序





void Hello::OnBnClickedHelloLogin()
{
	Login dlg;
	ShowWindow(SW_HIDE);
	dlg.DoModal();
	ShowWindow(SW_SHOW);
	// TODO:  在此添加控件通知处理程序代码
}


void Hello::OnClickedHelloRegist()
{
	Regist dlg;
	ShowWindow(SW_HIDE);
	dlg.DoModal();
	ShowWindow(SW_SHOW);

	// TODO:  在此添加控件通知处理程序代码
}


//void Hello::OnDoubleclickedHelloLogin()
//{
//	MessageBox("sss");
//	// TODO:  在此添加控件通知处理程序代码
//}


void Hello::OnClickedHelloManager()
{
	ManageLogin dlg;
	ShowWindow(SW_HIDE);
	dlg.DoModal();
	ShowWindow(SW_SHOW);
	// TODO:  在此添加控件通知处理程序代码
}

