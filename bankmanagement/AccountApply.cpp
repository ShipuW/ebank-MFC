// AccountApply.cpp : 实现文件
//

#include "stdafx.h"
#include "bankmanagement.h"
#include "AccountApply.h"
#include "afxdialogex.h"


// AccountApply 对话框

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
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	return true;
}
// AccountApply 消息处理程序


void AccountApply::OnCbnSelchangeApplyCombo()
{
	// TODO:  在此添加控件通知处理程序代码
}


void AccountApply::OnClickedApplyApply()
{
	CDatabase db;
	db.Open("bankmanagement");
	CString sqlstr, sqlstrsearch;//, username, idcard, pwd, address, email, number;
	
	UpdateData(TRUE);//更新文本框变量
	sqlstrsearch.Format(_T("select user_id from user where user_name='%s'"),CurrentUser);
	CRecordset rs(&db);
	rs.Open(CRecordset::forwardOnly, (_T("%s"), sqlstrsearch));
	CString struserid;
	rs.GetFieldValue(_T("user_id"), struserid);
	int userid = _ttoi(struserid);/////////////////////////////CString 强制转换为int
	CString timestr;//////获取系统时间
	CTime tm; tm = CTime::GetCurrentTime();
	timestr = tm.Format("%Y年%m月%d日 %X");
	sqlstr.Format(_T("insert into card(user_id,card_password,card_type,card_status,register_time) values('%d','%s','%s','待审核','%s')"), userid, m_ApplycardPwd, m_ApplycardType,timestr);
	if (m_ApplycardType.IsEmpty() || m_ApplycardPwd.IsEmpty() || m_ApplycardPwdConfirm.IsEmpty() )
	{
		MessageBox("带*为必填项", "输入有误");
	}
	else if (m_ApplycardPwd.GetLength() != 6)
	{
		MessageBox("密码不符！", "输入有误");
	}
	else if (m_ApplycardPwd != m_ApplycardPwdConfirm)
	{
		MessageBox("输入密码不一致", "输入有误");
	}
	else
	{
		db.ExecuteSQL(sqlstr);
		db.Close();
		MessageBox("申请成功！\n您的申请将会在10个工作日内处理。");
		//this->GetParent()->SendMessage(WM_CLOSE);//关闭父对话框
		OnOK();
	}
	// TODO:  在此添加控件通知处理程序代码
}
