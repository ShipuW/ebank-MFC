// Account.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "bankmanagement.h"
#include "Account.h"
#include "afxdialogex.h"
#include "Hello.h"

// Account �Ի���

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


// Account ��Ϣ�������
BOOL Account::OnInitDialog()
{
	errortimes = 3;///////���´����Դ���
	this->GetParent()->SendMessage(WM_CLOSE); fatherflag = 0;
	CDialogEx::OnInitDialog();

	ModifyStyleEx(0, WS_EX_APPWINDOW);
	HICON m_hIcon;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	m_tab.InsertItem(0, _T("�ʲ�����"));
	m_tab.InsertItem(1, _T("ת��"));
	m_tab.InsertItem(2, _T("���"));
	m_tab.InsertItem(3, _T("ȡ��"));
	m_tab.InsertItem(4, _T("������Ϣ"));

	//���������Ի���
	PageDeposit.Create(IDD_ACCOUNT_DEPOSIT, &m_tab);
	PageDraw.Create(IDD_ACCOUNT_DRAW, &m_tab);
	PageInfo.Create(IDD_ACCOUNT_INFO, &m_tab);
	PageProperty.Create(IDD_ACCOUNT_PROPERTY, &m_tab);
	PageTransfer.Create(IDD_ACCOUNT_TRANSFER, &m_tab);
	//�趨��Tab����ʾ�ķ�Χ
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

	//�ѶԻ������ָ�뱣������
	pDialog[0] = &PageProperty;
	pDialog[1] = &PageTransfer;
	pDialog[2] = &PageDeposit;
	pDialog[3] = &PageDraw;
	pDialog[4] = &PageInfo;
	//��ʾ��ʼҳ��
	pDialog[0]->ShowWindow(SW_SHOW);
	pDialog[1]->ShowWindow(SW_HIDE);
	pDialog[2]->ShowWindow(SW_HIDE);
	pDialog[3]->ShowWindow(SW_HIDE);
	pDialog[4]->ShowWindow(SW_HIDE);

	//���浱ǰѡ��
	m_CurSelTab = 0;
	return TRUE;
}



void Account::OnTcnSelchangeAccountTab(NMHDR *pNMHDR, LRESULT *pResult)
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

void Account::OnClickedAccountLogout()
{
	Hello dlg;
	CurrentUser = "";
	fatherflag = 1;
	refreshflag = 1;
	ShowWindow(SW_HIDE);
	dlg.DoModal();
	ShowWindow(SW_SHOW);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
