// Manager.cpp : 实现文件
//

#include "stdafx.h"
#include "bankmanagement.h"
#include "Manager.h"
#include "afxdialogex.h"
#include "Hello.h"

// Manager 对话框

IMPLEMENT_DYNAMIC(Manager, CDialogEx)

Manager::Manager(CWnd* pParent /*=NULL*/)
	: CDialogEx(Manager::IDD, pParent)
{

}

Manager::~Manager()
{
}

void Manager::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MANAGER_TAB, m_tab);//////////////////////////////未加这一句报错。。。。
}


BEGIN_MESSAGE_MAP(Manager, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_MANAGER_TAB, &Manager::OnTcnSelchangeManagerTab)
	ON_BN_CLICKED(IDC_MANAGER_LOGOUT, &Manager::OnClickedManagerLogout)
END_MESSAGE_MAP()


// Manager 消息处理程序
BOOL Manager::OnInitDialog()
{
	this->GetParent()->SendMessage(WM_CLOSE); fatherflag = 0;
	CDialogEx::OnInitDialog();
	
	ModifyStyleEx(0, WS_EX_APPWINDOW);
	HICON m_hIcon;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_tab.InsertItem(0, _T("银行资产管理"));
	m_tab.InsertItem(1, _T("卡处理"));
	m_tab.InsertItem(2, _T("账户管理"));


	//创建两个对话框
	PageAccount.Create(IDD_MANAGER_ACCOUNT, &m_tab);
	PageDeal.Create(IDD_MANAGER_DEAL, &m_tab);
	PageProperty.Create(IDD_MANAGER_PROPERTY, &m_tab);
	
	//设定在Tab内显示的范围
	CRect rc;
	m_tab.GetClientRect(rc);
	rc.top += 30;
	rc.bottom -= 8;
	rc.left += 8;
	rc.right -= 8;
	PageAccount.MoveWindow(&rc);
	PageDeal.MoveWindow(&rc);
	PageProperty.MoveWindow(&rc);
	

	//把对话框对象指针保存起来
	pDialog[0] = &PageProperty;
	pDialog[1] = &PageDeal;
	pDialog[2] = &PageAccount;
	
	//显示初始页面
	pDialog[0]->ShowWindow(SW_SHOW);
	pDialog[1]->ShowWindow(SW_HIDE);
	pDialog[2]->ShowWindow(SW_HIDE);
	//保存当前选择
	m_CurSelTab = 0;
	return TRUE;
}



void Manager::OnTcnSelchangeManagerTab(NMHDR *pNMHDR, LRESULT *pResult)
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


void Manager::OnClickedManagerLogout()
{
	Hello dlg;
	CurrentUser = "";
	fatherflag = 1;
	ShowWindow(SW_HIDE);
	dlg.DoModal();
	ShowWindow(SW_SHOW);
	// TODO:  在此添加控件通知处理程序代码
}
