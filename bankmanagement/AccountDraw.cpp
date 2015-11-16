// AccountDraw.cpp : 实现文件
//

#include "stdafx.h"
#include "bankmanagement.h"
#include "AccountDraw.h"
#include "afxdialogex.h"




// AccountDraw 对话框

IMPLEMENT_DYNAMIC(AccountDraw, CDialogEx)

AccountDraw::AccountDraw(CWnd* pParent /*=NULL*/)
	: CDialogEx(AccountDraw::IDD, pParent)
	, m_DrawCardnumber(_T(""))
	, m_DrawAmount(0)
	, m_DrawPassword(_T(""))
{

}

AccountDraw::~AccountDraw()
{
}

void AccountDraw::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_DRAW, ComboDraw);
	DDX_CBString(pDX, IDC_COMBO_DRAW, m_DrawCardnumber);
	DDX_Text(pDX, IDC_EDIT_DRAW_AMOUNT, m_DrawAmount);
	DDV_MinMaxFloat(pDX, m_DrawAmount, 1, 10000);
	DDX_Text(pDX, IDC_EDIT_DRAW_PWD, m_DrawPassword);
	DDX_Control(pDX, IDC_EDIT_DRAW_PWD, DrawEdit);
}


BEGIN_MESSAGE_MAP(AccountDraw, CDialogEx)
	ON_BN_CLICKED(IDC_DRAW_DRAW, &AccountDraw::OnClickedDrawDraw)
//	ON_CBN_SELCHANGE(IDC_COMBO_DRAW, &AccountDraw::OnCbnSelchangeComboDraw)
ON_CBN_SETFOCUS(IDC_COMBO_DRAW, &AccountDraw::OnSetfocusComboDraw)
END_MESSAGE_MAP()

int errortimes = 3;

BOOL AccountDraw::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ComboDraw.ResetContent();
	CString sqlstr;
	sqlstr.Format(_T("select card_number from card where user_id=(select user_id from user where user_name='%s') and card_status='正常'"), CurrentUser);
	m_DrawAmount = 100;
	UpdateData(false);
	CDatabase db;
	db.Open("bankmanagement");
	CRecordset rs(&db);
	rs.Open(CRecordset::forwardOnly, (_T("%s"), sqlstr));
	while (!rs.IsEOF())
	{
		CString varCardNumber;
		rs.GetFieldValue(_T("card_number"), varCardNumber);
		ComboDraw.AddString(varCardNumber);
		rs.MoveNext();
	}
	rs.Close();
	db.Close();
	return true;
}

// AccountDraw 消息处理程序


void AccountDraw::OnClickedDrawDraw()
{
	CDatabase db;
	db.Open("bankmanagement");
	CString sqlstr, sqlstraccount,sqlstrverify;//,username,idcard,pwd,address,email,number;
	UpdateData(TRUE);//更新文本框变量
	if (m_DrawAmount<1 || m_DrawAmount>10000);
	else{
		sqlstrverify.Format(_T("select card_password from card where card_number='%s'"), m_DrawCardnumber);//核对银行卡密码
		//MessageBox(sqlstr);
		CRecordset rs(&db);
		rs.Open(CRecordset::forwardOnly, (_T("%s"), sqlstrverify));
		CString pwd;
		rs.GetFieldValue(_T("card_password"), pwd);
		if (pwd == m_DrawPassword){
			CString timestr;//////获取系统时间
			CTime tm; tm = CTime::GetCurrentTime();
			timestr = tm.Format("%Y年%m月%d日 %X");

			sqlstr.Format(_T("insert into operate_draw(card_number,money_value,operate_time) values('%s','%f','%s')"), m_DrawCardnumber, m_DrawAmount,timestr);//更新数据处理记录
			sqlstraccount.Format(_T("update card set money_balance=money_balance-'%f'where card_number='%s'"), m_DrawAmount, m_DrawCardnumber);//更新卡上信息
			MessageBox("确定吗？");
			CString sqlstrbalance;
			sqlstrbalance.Format(_T("select money_balance from card where card_number='%s'"), m_DrawCardnumber);//判断余额
			CRecordset rss(&db);
			rss.Open(CRecordset::forwardOnly, (_T("%s"), sqlstrbalance));
			CString strbalance;
			//MessageBox("test");
			rss.GetFieldValue(_T("money_balance"), strbalance);

			float balance = _tstof(strbalance);

			if (m_DrawAmount > balance)
			{
				MessageBox("余额不足");
				rss.Close();
				rs.Close();
				db.Close();
			}
			else
			{
				db.ExecuteSQL(sqlstr);
				db.ExecuteSQL(sqlstraccount);
				errortimes = 3;
				rss.Close();
				rs.Close();
				db.Close();
				MessageBox("取款成功！");
				m_DrawCardnumber = "";
				m_DrawPassword = "";
				m_DrawAmount = 0;
				UpdateData(FALSE);
			}
		}
		else
		{
			if (errortimes == 1)////////////////////////////////////冻结处理
			{
				CDatabase db;
				db.Open("bankmanagement");
				CString sqlstr;//,username,idcard,pwd,address,email,number;
				UpdateData(TRUE);//更新文本框变量
				//MessageBox(m_RegUsername);
				sqlstr.Format(_T("update card set card_status='冻结'where card_number='%s'"), m_DrawCardnumber);
				db.ExecuteSQL(sqlstr);
				db.Close();
				
				MessageBox("这张卡已冻结，请联系管理员");
				errortimes = 3;
				AccountDraw::OnInitDialog();
				//AccountProperty::OnInitDialog();
			}
			else{
				errortimes--;
				CString warningstr;
				MessageBox("确定吗？");
				warningstr.Format(_T("密码不匹配\n您还有%d次机会"), errortimes);
				MessageBox(warningstr);
				DrawEdit.SetFocus();
				DrawEdit.SetSel(0,-1);
			}
		}
	}
	// TODO:  在此添加控件通知处理程序代码
}


//void AccountDraw::OnCbnSelchangeComboDraw()
//{
//	AccountDraw::OnInitDialog();
//	// TODO:  在此添加控件通知处理程序代码
//}


void AccountDraw::OnSetfocusComboDraw()
{
	ComboDraw.ResetContent();
	AccountDraw::OnInitDialog();
	// TODO:  在此添加控件通知处理程序代码
}
