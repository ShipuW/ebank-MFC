// Hello.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "bankmanagement.h"
#include "Hello.h"
#include "afxdialogex.h"
#include "Login.h"
#include "Regist.h"
#include "ManageLogin.h"
// Hello �Ի���

IMPLEMENT_DYNAMIC(Hello, CDialog)
CString CurrentUser="123";///////////////////////////////��ǰ��¼�û���ȫ��
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
	if (fatherflag == 1){ this->GetParent()->SendMessage(WM_CLOSE); fatherflag = 0; }//�رո��Ի���
	CDialogEx::OnInitDialog();
	HICON m_hIcon;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	return true;
}





// Hello ��Ϣ�������





void Hello::OnBnClickedHelloLogin()
{
	Login dlg;
	ShowWindow(SW_HIDE);
	dlg.DoModal();
	ShowWindow(SW_SHOW);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void Hello::OnClickedHelloRegist()
{
	Regist dlg;
	ShowWindow(SW_HIDE);
	dlg.DoModal();
	ShowWindow(SW_SHOW);

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


//void Hello::OnDoubleclickedHelloLogin()
//{
//	MessageBox("sss");
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//}


void Hello::OnClickedHelloManager()
{
	ManageLogin dlg;
	ShowWindow(SW_HIDE);
	dlg.DoModal();
	ShowWindow(SW_SHOW);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

