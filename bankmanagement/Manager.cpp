// Manager.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "bankmanagement.h"
#include "Manager.h"
#include "afxdialogex.h"
#include "Hello.h"

// Manager �Ի���

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
	DDX_Control(pDX, IDC_MANAGER_TAB, m_tab);//////////////////////////////δ����һ�䱨��������
}


BEGIN_MESSAGE_MAP(Manager, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_MANAGER_TAB, &Manager::OnTcnSelchangeManagerTab)
	ON_BN_CLICKED(IDC_MANAGER_LOGOUT, &Manager::OnClickedManagerLogout)
END_MESSAGE_MAP()


// Manager ��Ϣ�������
BOOL Manager::OnInitDialog()
{
	this->GetParent()->SendMessage(WM_CLOSE); fatherflag = 0;
	CDialogEx::OnInitDialog();
	
	ModifyStyleEx(0, WS_EX_APPWINDOW);
	HICON m_hIcon;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	m_tab.InsertItem(0, _T("�����ʲ�����"));
	m_tab.InsertItem(1, _T("������"));
	m_tab.InsertItem(2, _T("�˻�����"));


	//���������Ի���
	PageAccount.Create(IDD_MANAGER_ACCOUNT, &m_tab);
	PageDeal.Create(IDD_MANAGER_DEAL, &m_tab);
	PageProperty.Create(IDD_MANAGER_PROPERTY, &m_tab);
	
	//�趨��Tab����ʾ�ķ�Χ
	CRect rc;
	m_tab.GetClientRect(rc);
	rc.top += 30;
	rc.bottom -= 8;
	rc.left += 8;
	rc.right -= 8;
	PageAccount.MoveWindow(&rc);
	PageDeal.MoveWindow(&rc);
	PageProperty.MoveWindow(&rc);
	

	//�ѶԻ������ָ�뱣������
	pDialog[0] = &PageProperty;
	pDialog[1] = &PageDeal;
	pDialog[2] = &PageAccount;
	
	//��ʾ��ʼҳ��
	pDialog[0]->ShowWindow(SW_SHOW);
	pDialog[1]->ShowWindow(SW_HIDE);
	pDialog[2]->ShowWindow(SW_HIDE);
	//���浱ǰѡ��
	m_CurSelTab = 0;
	return TRUE;
}



void Manager::OnTcnSelchangeManagerTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//�ѵ�ǰ��ҳ����������
	pDialog[m_CurSelTab]->ShowWindow(SW_HIDE);
	//�õ��µ�ҳ������
	m_CurSelTab = m_tab.GetCurSel();
	//���µ�ҳ����ʾ����
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
