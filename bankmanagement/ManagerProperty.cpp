// ManagerProperty.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "bankmanagement.h"
#include "ManagerProperty.h"
#include "afxdialogex.h"
#include "ManagerPropertyFeeDetail.h"

// ManagerProperty �Ի���

IMPLEMENT_DYNAMIC(ManagerProperty, CDialogEx)

ManagerProperty::ManagerProperty(CWnd* pParent /*=NULL*/)
	: CDialogEx(ManagerProperty::IDD, pParent)
	, m_ManagerPropertyamount(0)
	
	, m_chartfinal()
{

}

ManagerProperty::~ManagerProperty()
{
}

void ManagerProperty::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MANAGE_PROPERTY_AMOUNT, m_ManagerPropertyamount);

	DDX_Control(pDX, IDC_TCHART1, m_chartfinal);
}


BEGIN_MESSAGE_MAP(ManagerProperty, CDialogEx)
	ON_BN_CLICKED(IDC_INTEREST_FEE, &ManagerProperty::OnClickedInterestFee)
	ON_BN_CLICKED(IDC_ADD_PROPERTY_INFO, &ManagerProperty::OnClickedAddPropertyInfo)
	ON_BN_CLICKED(IDC_FEE_DETAIL, &ManagerProperty::OnClickedFeeDetail)
END_MESSAGE_MAP()

BOOL ManagerProperty::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//this->GetParent()->SendMessage(WM_CLOSE);//�رո��Ի���
	CDatabase db;
	db.Open("bankmanagement");
	CString sqlstr,sqlstramount;
	sqlstr.Format(_T("select manager_name from manager where manager_login_name='%s'"), CurrentUser);
	CRecordset rs(&db);
	rs.Open(CRecordset::forwardOnly, (_T("%s"), sqlstr));
	CString	name;
	rs.GetFieldValue(_T("manager_name"), name);
	GetDlgItem(IDC_MANAGER_NAME)->SetWindowTextA((CString)name);
	rs.Close();
	////////////////////////////�������½��
	sqlstramount.Format(_T("select money_amount from bank_account"));
	CRecordset rss(&db);
	rss.Open(CRecordset::forwardOnly, (_T("%f"), sqlstramount));
	CString	stramount;
	rss.GetFieldValue(_T("money_amount"), stramount);
	m_ManagerPropertyamount = _tstof(stramount);
	UpdateData(FALSE);
	rss.Close();
	db.Close();


	///////////////////////////////����ͼ��
	CSeries0 lineSeries = (CSeries0)m_chartfinal.Series(0);
	lineSeries.Clear();

	
	sqlstr.Format(_T("CREATE OR REPLACE VIEW `view_day_property`AS SELECT * FROM day_property ORDER BY day_property.dayproperty_id DESC LIMIT 10;"));
	
	db.Open("bankmanagement");
	db.ExecuteSQL(sqlstr);
	sqlstr.Format(_T("select day_time,bank_balance from view_day_property  ORDER BY dayproperty_id ASC;"));
	CRecordset rssss(&db);
	rssss.Open(CRecordset::forwardOnly, (_T("%s"), sqlstr));
	CString strx, strbalance;
	double daybalance;


	for (int i = 0; i<10; i++)
	{

		CString varDayTime;
		rssss.GetFieldValue(_T("day_time"), varDayTime);
		strx.Format(_T("%s"), varDayTime);

		CString varBankBalance;
		rssss.GetFieldValue(_T("bank_balance"), varBankBalance);
		strbalance.Format(_T("%s"), varBankBalance);
		daybalance = _ttof(strbalance);

		lineSeries.AddXY((double)i, daybalance, strx, 0);
		rssss.MoveNext();
	}

	rssss.Close();


	db.Close();


	return true;
}
// ManagerProperty ��Ϣ�������


void ManagerProperty::OnClickedInterestFee()
{
	CDatabase db;
	db.Open("bankmanagement");
	CString sqlstr,sqlstrcardnumber,sqlstrafteramount,sqlstrupdate,updatenumber;
	int cardnumber;
	
	sqlstr.Format(_T("update card set money_balance=money_balance-2 where card_status='����'"));//////�۷�
	db.ExecuteSQL(sqlstr);

	sqlstr.Format(_T("select count(*) from card where card_status='����'"));/////�����Ƭ��
	CRecordset rss(&db);
	rss.Open(CRecordset::forwardOnly, (_T("%f"), sqlstr));
	rss.GetFieldValue(_T("count(*)"), sqlstrcardnumber);
	cardnumber = _ttoi(sqlstrcardnumber);
	UpdateData(FALSE);
	rss.Close();
	
	sqlstr.Format(_T("select card_number from card where card_status='����'"));/////��¼�շ�����
	CRecordset r(&db);
	r.Open(CRecordset::forwardOnly, (_T("%f"), sqlstr));
	CString timestr;///////////get system time
	CTime tm;
	while (!r.IsEOF())
	{
		tm = CTime::GetCurrentTime();
		timestr = tm.Format("%Y��%m��%d�� %X");
		r.GetFieldValue(_T("card_number"), updatenumber);
		sqlstrupdate.Format(_T("insert into operate_bank(card_number,money_amount,operate_type,operate_time) values('%s',2,'�������','%s')"), updatenumber,timestr);
		db.ExecuteSQL(sqlstrupdate);
		r.MoveNext();
	}
	
	r.Close();

	float fee = cardnumber*2.0;//////ת�������˻�
	sqlstr.Format(_T("update bank_account set money_amount=money_amount+'%f'"), fee);
	db.ExecuteSQL(sqlstr);

	sqlstr.Format(_T("select money_amount from bank_account"));////������ʵ�����˻����
	CRecordset rs(&db);
	rs.Open(CRecordset::forwardOnly, (_T("%f"), sqlstr));
	CString	stramount;
	rs.GetFieldValue(_T("money_amount"), stramount);
	m_ManagerPropertyamount = _tstof(stramount);
	UpdateData(FALSE);
	rs.Close();

	db.Close();
	MessageBox("�����Ѵ���ɹ���");
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void ManagerProperty::OnClickedAddPropertyInfo()
{
	CDatabase db;
	db.Open("bankmanagement");
	CString sqlstr,strbankbalance;
	float bankbalance;
	CString timestr;//////��ȡϵͳʱ��
	CTime tm; tm = CTime::GetCurrentTime();
	timestr = tm.Format("%Y-%m-%d");
	
	sqlstr.Format(_T("select sum(money_balance) from card"));
	CRecordset rsss(&db);
	rsss.Open(CRecordset::forwardOnly, (_T("%f"), sqlstr));
	rsss.GetFieldValue(_T("sum(money_balance)"), strbankbalance);
	bankbalance = _ttof(strbankbalance);
	sqlstr.Format(_T("insert into day_property(bank_balance,day_time)values('%f','%s')"), bankbalance,timestr);
	
	db.ExecuteSQL(sqlstr);
	db.Close();
	MessageBox("����ɹ���");
	ManagerProperty::OnInitDialog();
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void ManagerProperty::OnClickedFeeDetail()
{
	ManagerPropertyFeeDetail dlg;
	//ShowWindow(SW_HIDE);
	dlg.DoModal();
	//ShowWindow(SW_SHOW);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
