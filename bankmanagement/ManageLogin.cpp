// ManageLogin.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "bankmanagement.h"
#include "ManageLogin.h"
#include "afxdialogex.h"
#include "Manager.h"
#include "Hello.h"

// ManageLogin �Ի���

IMPLEMENT_DYNAMIC(ManageLogin, CDialogEx)

ManageLogin::ManageLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(ManageLogin::IDD, pParent)
	, m_ManageloginName(_T(""))
	, m_ManageloginPassword(_T(""))
{

}

ManageLogin::~ManageLogin()
{
}

void ManageLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MANAGE_LOGIN_NAME, m_ManageloginName);
	DDX_Text(pDX, IDC_EDIT_MANAGE_LOGIN_PWD, m_ManageloginPassword);
}


BEGIN_MESSAGE_MAP(ManageLogin, CDialogEx)
	ON_BN_CLICKED(IDC_MANAGE_LOGIN_LOGIN, &ManageLogin::OnClickedManageLoginLogin)
	ON_BN_CLICKED(IDC_MANAGE_LOGIN_CANCEL, &ManageLogin::OnClickedManageLoginCancel)
END_MESSAGE_MAP()

BOOL ManageLogin::OnInitDialog()
{
	this->GetParent()->SendMessage(WM_CLOSE);//�رո��Ի���
	CDialogEx::OnInitDialog();
	ModifyStyleEx(0, WS_EX_APPWINDOW);
	HICON m_hIcon;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	return true;
}

// ManageLogin ��Ϣ�������


void ManageLogin::OnClickedManageLoginLogin()
{
	//MessageBox("2");
	//CString CurrentUser = "";//��¼�˻�����ȫ�ֺ��� 
	UpdateData(TRUE);
	//MessageBox(m_LogUsername);
	CDatabase db;
	db.Open("bankmanagement");
	CString sqlstr;
	sqlstr.Format(_T("select manager_password from manager where manager_login_name='%s'"), m_ManageloginName);
	CRecordset rs(&db);
	//MessageBox(sqlstr);
	rs.Open(CRecordset::forwardOnly, (_T("%s"), sqlstr));
	CString	pwd;
	if (m_ManageloginName.IsEmpty())
	{
		MessageBox("���������Ĺ���Ա�˺�");
	}
	else if (rs.GetRecordCount() == 0)
	{
		MessageBox("�˺Ų����ڣ�");
	}
	else
	{
		rs.GetFieldValue(_T("manager_password"), pwd);
		rs.Close();
		db.Close();
		if (pwd == m_ManageloginPassword)
		{
			MessageBox("��¼�ɹ�");
			//MessageBox(CurrentUser);
			CurrentUser = m_ManageloginName;
			//MessageBox(CurrentUser);
			Manager dlg;
			ShowWindow(SW_HIDE);
			dlg.DoModal();
			ShowWindow(SW_SHOW);
		}
		else
		{
			MessageBox("�������");
		}
	}
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void ManageLogin::OnClickedManageLoginCancel()
{
	Hello dlg;
	fatherflag = 1;
	ShowWindow(SW_HIDE);
	dlg.DoModal();
	ShowWindow(SW_SHOW);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
