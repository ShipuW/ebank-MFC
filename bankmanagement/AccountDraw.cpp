// AccountDraw.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "bankmanagement.h"
#include "AccountDraw.h"
#include "afxdialogex.h"




// AccountDraw �Ի���

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
	sqlstr.Format(_T("select card_number from card where user_id=(select user_id from user where user_name='%s') and card_status='����'"), CurrentUser);
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

// AccountDraw ��Ϣ�������


void AccountDraw::OnClickedDrawDraw()
{
	CDatabase db;
	db.Open("bankmanagement");
	CString sqlstr, sqlstraccount,sqlstrverify;//,username,idcard,pwd,address,email,number;
	UpdateData(TRUE);//�����ı������
	if (m_DrawAmount<1 || m_DrawAmount>10000);
	else{
		sqlstrverify.Format(_T("select card_password from card where card_number='%s'"), m_DrawCardnumber);//�˶����п�����
		//MessageBox(sqlstr);
		CRecordset rs(&db);
		rs.Open(CRecordset::forwardOnly, (_T("%s"), sqlstrverify));
		CString pwd;
		rs.GetFieldValue(_T("card_password"), pwd);
		if (pwd == m_DrawPassword){
			CString timestr;//////��ȡϵͳʱ��
			CTime tm; tm = CTime::GetCurrentTime();
			timestr = tm.Format("%Y��%m��%d�� %X");

			sqlstr.Format(_T("insert into operate_draw(card_number,money_value,operate_time) values('%s','%f','%s')"), m_DrawCardnumber, m_DrawAmount,timestr);//�������ݴ����¼
			sqlstraccount.Format(_T("update card set money_balance=money_balance-'%f'where card_number='%s'"), m_DrawAmount, m_DrawCardnumber);//���¿�����Ϣ
			MessageBox("ȷ����");
			CString sqlstrbalance;
			sqlstrbalance.Format(_T("select money_balance from card where card_number='%s'"), m_DrawCardnumber);//�ж����
			CRecordset rss(&db);
			rss.Open(CRecordset::forwardOnly, (_T("%s"), sqlstrbalance));
			CString strbalance;
			//MessageBox("test");
			rss.GetFieldValue(_T("money_balance"), strbalance);

			float balance = _tstof(strbalance);

			if (m_DrawAmount > balance)
			{
				MessageBox("����");
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
				MessageBox("ȡ��ɹ���");
				m_DrawCardnumber = "";
				m_DrawPassword = "";
				m_DrawAmount = 0;
				UpdateData(FALSE);
			}
		}
		else
		{
			if (errortimes == 1)////////////////////////////////////���ᴦ��
			{
				CDatabase db;
				db.Open("bankmanagement");
				CString sqlstr;//,username,idcard,pwd,address,email,number;
				UpdateData(TRUE);//�����ı������
				//MessageBox(m_RegUsername);
				sqlstr.Format(_T("update card set card_status='����'where card_number='%s'"), m_DrawCardnumber);
				db.ExecuteSQL(sqlstr);
				db.Close();
				
				MessageBox("���ſ��Ѷ��ᣬ����ϵ����Ա");
				errortimes = 3;
				AccountDraw::OnInitDialog();
				//AccountProperty::OnInitDialog();
			}
			else{
				errortimes--;
				CString warningstr;
				MessageBox("ȷ����");
				warningstr.Format(_T("���벻ƥ��\n������%d�λ���"), errortimes);
				MessageBox(warningstr);
				DrawEdit.SetFocus();
				DrawEdit.SetSel(0,-1);
			}
		}
	}
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


//void AccountDraw::OnCbnSelchangeComboDraw()
//{
//	AccountDraw::OnInitDialog();
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//}


void AccountDraw::OnSetfocusComboDraw()
{
	ComboDraw.ResetContent();
	AccountDraw::OnInitDialog();
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
