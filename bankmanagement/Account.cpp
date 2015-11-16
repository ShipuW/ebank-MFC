// Account.cpp : 实现文件
//

#include "stdafx.h"
#include "bankmanagement.h"
#include "Account.h"
#include "afxdialogex.h"
#include "Hello.h"

// Account 对话框

IMPLEMENT_DYNAMIC(Account, CDialogEx)

Account::Account(CWnd* pParent /*=NULL*/)
	: CDialogEx(Account::IDD, pParent)
{

}

Account::~Account()
{
}

void Account::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ACCOUNT_TAB, m_tab);
}


BEGIN_MESSAGE_MAP(Account, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_ACCOUNT_TAB, &Account::OnTcnSelchangeAccountTab)
	ON_BN_CLICKED(IDC_ACCOUNT_LOGOUT, &Account::OnClickedAccountLogout)
END_MESSAGE_MAP()


// Account 消息处理程序
BOOL Account::OnInitDialog()
{
	errortimes = 3;///////更新错误尝试次数
	this->GetParent()->SendMessage(WM_CLOSE); fatherflag = 0;
	CDialogEx::OnInitDialog();

	ModifyStyleEx(0, WS_EX_APPWINDOW);
	HICON m_hIcon;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_tab.InsertItem(0, _T("资产管理"));
	m_tab.InsertItem(1, _T("转账"));
	m_tab.InsertItem(2, _T("存款"));
	m_tab.InsertItem(3, _T("取款"));
	m_tab.InsertItem(4, _T("个人信息"));

	//创建两个对话框
	PageDeposit.Create(IDD_ACCOUNT_DEPOSIT, &m_tab);
	PageDraw.Create(IDD_ACCOUNT_DRAW, &m_tab);
	PageInfo.Create(IDD_ACCOUNT_INFO, &m_tab);
	PageProperty.Create(IDD_ACCOUNT_PROPERTY, &m_tab);
	PageTransfer.Create(IDD_ACCOUNT_TRANSFER, &m_tab);
	//设定在Tab内显示的范围
	CRect rc;
	m_tab.GetClientRect(rc);
	rc.top += 30;
	rc.bottom -= 8;
	rc.left += 8;
	rc.right -= 8;
	PageDeposit.MoveWindow(&rc);
	PageDraw.MoveWindow(&rc);
	PageInfo.MoveWindow(&rc);
	PageProperty.MoveWindow(&rc);
	PageTransfer.MoveWindow(&rc);

	//把对话框对象指针保存起来
	pDialog[0] = &PageProperty;
	pDialog[1] = &PageTransfer;
	pDialog[2] = &PageDeposit;
	pDialog[3] = &PageDraw;
	pDialog[4] = &PageInfo;
	//显示初始页面
	pDialog[0]->ShowWindow(SW_SHOW);
	pDialog[1]->ShowWindow(SW_HIDE);
	pDialog[2]->ShowWindow(SW_HIDE);
	pDialog[3]->ShowWindow(SW_HIDE);
	pDialog[4]->ShowWindow(SW_HIDE);

	//保存当前选择
	m_CurSelTab = 0;
	return TRUE;
}



void Account::OnTcnSelchangeAccountTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	//把当前的页面隐藏起来
	pDialog[m_CurSelTab]->ShowWindow(SW_HIDE);
	//得到新的页面索引
	m_CurSelTab = m_tab.GetCurSel();
	//把新的页面显示出来
	pDialog[m_CurSelTab]->ShowWindow(SW_SHOW);
	*pResult = 0;
}

void Account::OnClickedAccountLogout()
{
	Hello dlg;
	CurrentUser = "";
	fatherflag = 1;
	refreshflag = 1;
	ShowWindow(SW_HIDE);
	dlg.DoModal();
	ShowWindow(SW_SHOW);
	// TODO:  在此添加控件通知处理程序代码
}
