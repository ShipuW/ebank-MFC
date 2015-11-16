// ChangeCardPassword.cpp : 实现文件
//

#include "stdafx.h"
#include "bankmanagement.h"
#include "ChangeCardPassword.h"
#include "afxdialogex.h"


// ChangeCardPassword 对话框

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
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	return true;
}

// ChangeCardPassword 消息处理程序


void ChangeCardPassword::OnClickedChangeCardChange()
{
	CDatabase db;
	db.Open("bankmanagement");
	CString sqlstr, dbpwd;
	UpdateData(TRUE);//更新文本框变量
	sqlstr.Format(_T("select user_pwd from user where user_name='%s'"), CurrentUser);
	CRecordset rs(&db);

	rs.Open(CRecordset::forwardOnly, (_T("%s"), sqlstr));
	rs.GetFieldValue(_T("user_pwd"), dbpwd);
	if (dbpwd == m_ChangecardPasswordbefore){
		sqlstr.Format(_T("update card set card_password='%s'where card_number='%s'"), m_ChangecardPassword, CardDetail);
		if (m_ChangecardPassword.IsEmpty() || m_ChangecardPasswordconfirm.IsEmpty())
		{
			MessageBox("带*为必填项", "输入有误");
		}
		else if (m_ChangecardPassword.GetLength() != 6)
		{
			MessageBox("密码太短！", "输入有误");
		}
		else if (m_ChangecardPassword != m_ChangecardPasswordconfirm)
		{
			MessageBox("输入密码不一致", "输入有误");
		}
		else
		{
			db.ExecuteSQL(sqlstr);
			db.Close();
			MessageBox("修改成功！");
			this->SendMessage(WM_CLOSE);
			//this->GetParent()->SendMessage(WM_CLOSE);//关闭父对话框

		}
	}
	else MessageBox("原密码错误！");
	// TODO:  在此添加控件通知处理程序代码
}
