// AccountApply.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "bankmanagement.h"
#include "AccountApply.h"
#include "afxdialogex.h"


// AccountApply �Ի���

IMPLEMENT_DYNAMIC(AccountApply, CDialogEx)

AccountApply::AccountApply(CWnd* pParent /*=NULL*/)
	: CDialogEx(AccountApply::IDD, pParent)
	, m_ApplycardType(_T(""))
	, m_ApplycardPwd(_T(""))
	, m_ApplycardPwdConfirm(_T(""))
{

}

AccountApply::~AccountApply()
{
}

void AccountApply::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_APPLY_COMBO, m_ApplycardType);
	DDX_Text(pDX, IDC_EDIT1, m_ApplycardPwd);
	DDX_Text(pDX, IDC_EDIT2, m_ApplycardPwdConfirm);
	DDV_MaxChars(pDX, m_ApplycardPwdConfirm, 6);
	DDV_MaxChars(pDX, m_ApplycardPwd, 6);
}


BEGIN_MESSAGE_MAP(AccountApply, CDialogEx)
	ON_CBN_SELCHANGE(IDC_APPLY_COMBO, &AccountApply::OnCbnSelchangeApplyCombo)
	ON_BN_CLICKED(IDC_APPLY_APPLY, &AccountApply::OnClickedApplyApply)
END_MESSAGE_MAP()

BOOL AccountApply::OnInitDialog()
{
	
	CDialogEx::OnInitDialog();
	HICON m_hIcon;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	return true;
}
// AccountApply ��Ϣ�������


void AccountApply::OnCbnSelchangeApplyCombo()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void AccountApply::OnClickedApplyApply()
{
	CDatabase db;
	db.Open("bankmanagement");
	CString sqlstr, sqlstrsearch;//, username, idcard, pwd, address, email, number;
	
	UpdateData(TRUE);//�����ı������
	sqlstrsearch.Format(_T("select user_id from user where user_name='%s'"),CurrentUser);
	CRecordset rs(&db);
	rs.Open(CRecordset::forwardOnly, (_T("%s"), sqlstrsearch));
	CString struserid;
	rs.GetFieldValue(_T("user_id"), struserid);
	int userid = _ttoi(struserid);/////////////////////////////CString ǿ��ת��Ϊint
	CString timestr;//////��ȡϵͳʱ��
	CTime tm; tm = CTime::GetCurrentTime();
	timestr = tm.Format("%Y��%m��%d�� %X");
	sqlstr.Format(_T("insert into card(user_id,card_password,card_type,card_status,register_time) values('%d','%s','%s','�����','%s')"), userid, m_ApplycardPwd, m_ApplycardType,timestr);
	if (m_ApplycardType.IsEmpty() || m_ApplycardPwd.IsEmpty() || m_ApplycardPwdConfirm.IsEmpty() )
	{
		MessageBox("��*Ϊ������", "��������");
	}
	else if (m_ApplycardPwd.GetLength() != 6)
	{
		MessageBox("���벻����", "��������");
	}
	else if (m_ApplycardPwd != m_ApplycardPwdConfirm)
	{
		MessageBox("�������벻һ��", "��������");
	}
	else
	{
		db.ExecuteSQL(sqlstr);
		db.Close();
		MessageBox("����ɹ���\n�������뽫����10���������ڴ���");
		//this->GetParent()->SendMessage(WM_CLOSE);//�رո��Ի���
		OnOK();
	}
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
