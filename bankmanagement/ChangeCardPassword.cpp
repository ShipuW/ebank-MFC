// ChangeCardPassword.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "bankmanagement.h"
#include "ChangeCardPassword.h"
#include "afxdialogex.h"


// ChangeCardPassword �Ի���

IMPLEMENT_DYNAMIC(ChangeCardPassword, CDialogEx)

ChangeCardPassword::ChangeCardPassword(CWnd* pParent /*=NULL*/)
	: CDialogEx(ChangeCardPassword::IDD, pParent)
	, m_ChangecardPassword(_T(""))
	, m_ChangecardPasswordconfirm(_T(""))
	, m_ChangecardPasswordbefore(_T(""))
{

}

ChangeCardPassword::~ChangeCardPassword()
{
}

void ChangeCardPassword::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CHANGE_CARD_PWD, m_ChangecardPassword);
	DDX_Text(pDX, IDC_EDIT_CHANGE_CARD_PWD_CONFIRM, m_ChangecardPasswordconfirm);
	DDV_MaxChars(pDX, m_ChangecardPassword, 6);
	DDV_MaxChars(pDX, m_ChangecardPasswordconfirm, 6);
	DDX_Text(pDX, IDC_CARD_PASSWORD_BEFORE, m_ChangecardPasswordbefore);
}


BEGIN_MESSAGE_MAP(ChangeCardPassword, CDialogEx)
	ON_BN_CLICKED(IDC_CHANGE_CARD_CHANGE, &ChangeCardPassword::OnClickedChangeCardChange)
END_MESSAGE_MAP()

BOOL ChangeCardPassword::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ModifyStyleEx(0, WS_EX_APPWINDOW);
	HICON m_hIcon;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	return true;
}

// ChangeCardPassword ��Ϣ�������


void ChangeCardPassword::OnClickedChangeCardChange()
{
	CDatabase db;
	db.Open("bankmanagement");
	CString sqlstr, dbpwd;
	UpdateData(TRUE);//�����ı������
	sqlstr.Format(_T("select user_pwd from user where user_name='%s'"), CurrentUser);
	CRecordset rs(&db);

	rs.Open(CRecordset::forwardOnly, (_T("%s"), sqlstr));
	rs.GetFieldValue(_T("user_pwd"), dbpwd);
	if (dbpwd == m_ChangecardPasswordbefore){
		sqlstr.Format(_T("update card set card_password='%s'where card_number='%s'"), m_ChangecardPassword, CardDetail);
		if (m_ChangecardPassword.IsEmpty() || m_ChangecardPasswordconfirm.IsEmpty())
		{
			MessageBox("��*Ϊ������", "��������");
		}
		else if (m_ChangecardPassword.GetLength() != 6)
		{
			MessageBox("����̫�̣�", "��������");
		}
		else if (m_ChangecardPassword != m_ChangecardPasswordconfirm)
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
