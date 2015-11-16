// Regist.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "bankmanagement.h"
#include "Regist.h"
#include "afxdialogex.h"
#include "Hello.h"

// Regist �Ի���

IMPLEMENT_DYNAMIC(Regist, CDialogEx)

Regist::Regist(CWnd* pParent /*=NULL*/)
	: CDialogEx(Regist::IDD, pParent)
	, m_RegUsername(_T("�û���Ϊ��ĸ���������"))
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
	this->GetParent()->SendMessage(WM_CLOSE);//�رո��Ի���
	CDialogEx::OnInitDialog();
	ModifyStyleEx(0, WS_EX_APPWINDOW);
	HICON m_hIcon;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	return true;
}

// Regist ��Ϣ�������


void Regist::OnClickedRegistRegist()
{
	CDatabase db;
	db.Open("bankmanagement");
	CString sqlstr;//,username,idcard,pwd,address,email,number;
	UpdateData(TRUE);//�����ı������
	//MessageBox(m_RegUsername);

	sqlstr.Format(_T("insert into user(user_name,user_idcard,user_pwd,user_address,user_email,phone_number) values('%s','%s','%s','%s','%s','%s')"), m_RegUsername, m_RegIdcard, m_RegPwd, m_RegAddress, m_RegEmail, m_RegPhone);
	if (m_RegUsername.IsEmpty() || m_RegPwd.IsEmpty() || m_RegPwdConfirm.IsEmpty() || m_RegIdcard.IsEmpty() || m_RegAddress.IsEmpty() || m_RegEmail.IsEmpty())
	{
		MessageBox("��*Ϊ������", "��������");
	}
	else if (m_RegUsername == "�û���Ϊ��ĸ���������")
	{
		MessageBox("�û���δ�޸�");
	}
	else if (m_RegPwd.GetLength() < 6)
	{
		MessageBox("����̫�̣�","��������");
	}
	else if (m_RegPwd != m_RegPwdConfirm)
	{
		MessageBox("�������벻һ��", "��������");
	}
	else
	{
		db.ExecuteSQL(sqlstr);
		db.Close();
		MessageBox("ע��ɹ������ص�¼��");
		//this->GetParent()->SendMessage(WM_CLOSE);//�رո��Ի���
		Hello dlg;
		fatherflag = 1;
		ShowWindow(SW_HIDE);
		dlg.DoModal();
		ShowWindow(SW_SHOW);
	}
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


//void Regist::OnEnChangeEditRegistPwd()
//{
//	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
//	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
//	// ���������� CRichEditCtrl().SetEventMask()��
//	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
//
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//}


void Regist::OnSetfocusEditRegistUsername()
{
	UpdateData(TRUE);
	if (m_RegUsername == "�û���Ϊ��ĸ���������")
		SetDlgItemText(IDC_EDIT_REGIST_USERNAME, "");///////����༭���������
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
		GetDlgItem(IDC_NAME_NOTICE)->SetWindowTextA((CString)"���û����Ѵ��ڣ�");
		GetDlgItem(IDC_REGIST_REGIST)->EnableWindow(false);
	}//MessageBox("�û����Ѵ��ڣ����������롣", "��������");
	else
	{
		GetDlgItem(IDC_NAME_NOTICE)->SetWindowTextA((CString)"�̿���ʹ��");
		GetDlgItem(IDC_REGIST_REGIST)->EnableWindow(true);
	}
	rs.Close();
	db.Close();
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


//void Regist::OnSetfocusEditRegistPwd()
//{
//	UpdateData(TRUE);
//	if (m_RegUsername == "��������6λ")
//	{
//		SetDlgItemText(IDC_EDIT_REGIST_PWD, "");
//		GetDlgItem(IDC_EDIT_REGIST_PWD)->
//	}
//		// TODO:  �ڴ���ӿؼ�֪ͨ����������
//}


void Regist::OnClickedRegistCancel()
{
	Hello dlg;
	fatherflag = 1;
	ShowWindow(SW_HIDE);
	dlg.DoModal();
	ShowWindow(SW_SHOW);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
		GetDlgItem(IDC_EMAIL_NOTICE)->SetWindowTextA((CString)"�������ѱ�ע�ᣡ");
		GetDlgItem(IDC_REGIST_REGIST)->EnableWindow(false);
	}//MessageBox("�û����Ѵ��ڣ����������롣", "��������");
	else
	{
		GetDlgItem(IDC_EMAIL_NOTICE)->SetWindowTextA((CString)"�̿���ʹ��");
		GetDlgItem(IDC_REGIST_REGIST)->EnableWindow(true);
	}
	rs.Close();
	db.Close();
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
