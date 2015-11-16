// ChangePassword.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "bankmanagement.h"
#include "ChangePassword.h"
#include "afxdialogex.h"


// ChangePassword �Ի���

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
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	return true;
}

// ChangePassword ��Ϣ�������


void ChangePassword::OnClickedChangPwdChange()
{
	CDatabase db;
	db.Open("bankmanagement");
	CString sqlstr,dbpwd;
	UpdateData(TRUE);//�����ı������
	sqlstr.Format(_T("select user_pwd from user where user_name='%s'"), CurrentUser);
	CRecordset rs(&db);
	
	rs.Open(CRecordset::forwardOnly, (_T("%s"), sqlstr));
	rs.GetFieldValue(_T("user_pwd"), dbpwd);
	if (dbpwd == m_ChangeaccountPasswordbefore){

		sqlstr.Format(_T("update user set user_pwd='%s'where user_name='%s'"), m_Changepasswordconfirm, CurrentUser);
		if (m_Changepassword.IsEmpty() || m_Changepasswordconfirm.IsEmpty())
		{
			MessageBox("��*Ϊ������", "��������");
		}
		else if (m_Changepassword.GetLength() < 6)
		{
			MessageBox("����̫�̣�", "��������");
		}
		else if (m_Changepassword != m_Changepasswordconfirm)
		{
			MessageBox("�������벻һ��", "��������");
		}
		else
		{
			db.ExecuteSQL(sqlstr);
			db.Close();
			MessageBox("�޸ĳɹ���");
			this->SendMessage(WM_CLOSE);
			//this->GetParent()->SendMessage(WM_CLOSE);//�رո��Ի���

		}
	}
	else MessageBox("ԭ�������");
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
