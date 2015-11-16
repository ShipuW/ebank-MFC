// AccountTransfer.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "bankmanagement.h"
#include "AccountTransfer.h"
#include "afxdialogex.h"


// AccountTransfer �Ի���

IMPLEMENT_DYNAMIC(AccountTransfer, CDialogEx)

AccountTransfer::AccountTransfer(CWnd* pParent /*=NULL*/)
	: CDialogEx(AccountTransfer::IDD, pParent)
	, m_TransferFromcardnumber(_T(""))
	, m_TransferTocardnumber(_T(""))
	, m_TransferTousername(_T(""))
	, m_TransferAmount(0)
	, m_TransferPassword(_T(""))
{

}

AccountTransfer::~AccountTransfer()
{
}

void AccountTransfer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_TRANSFER, ComboTransfer);
	DDX_CBString(pDX, IDC_COMBO_TRANSFER, m_TransferFromcardnumber);
	DDX_Text(pDX, IDC_EDIT_TRANSFER_TARGET, m_TransferTocardnumber);
	DDX_Text(pDX, IDC_EDIT_TRANSFER_TARGET_USERNAME, m_TransferTousername);
	DDX_Text(pDX, IDC_TRANSFER_AMOUNT, m_TransferAmount);
	DDV_MinMaxFloat(pDX, m_TransferAmount, 1, 5000);
	DDX_Text(pDX, IDC_TRANSFER_PWD, m_TransferPassword);
	DDV_MaxChars(pDX, m_TransferPassword, 6);
	DDX_Control(pDX, IDC_TRANSFER_PWD, TransferEdit);
}


BEGIN_MESSAGE_MAP(AccountTransfer, CDialogEx)
	ON_BN_CLICKED(IDC_TRANSFER_TRANSFER, &AccountTransfer::OnClickedTransferTransfer)
	ON_EN_KILLFOCUS(IDC_EDIT_TRANSFER_TARGET, &AccountTransfer::OnKillfocusEditTransferTarget)
//	ON_CBN_SELCHANGE(IDC_COMBO_TRANSFER, &AccountTransfer::OnCbnSelchangeComboTransfer)
//	ON_CBN_SETFOCUS(IDC_COMBO_TRANSFER, &AccountTransfer::OnSetfocusComboTransfer)
ON_CBN_SETFOCUS(IDC_COMBO_TRANSFER, &AccountTransfer::OnSetfocusComboTransfer)
END_MESSAGE_MAP()

//int errortimes = 3;

BOOL AccountTransfer::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString sqlstr;
	sqlstr.Format(_T("select card_number from card where user_id=(select user_id from user where user_name='%s') and card_status='����'"), CurrentUser);
	m_TransferAmount = 100;
	UpdateData(false);
	CDatabase db;
	db.Open("bankmanagement");
	CRecordset rs(&db);
	rs.Open(CRecordset::forwardOnly, (_T("%s"), sqlstr));
	while (!rs.IsEOF())
	{
		CString varCardNumber;
		rs.GetFieldValue(_T("card_number"), varCardNumber);
		ComboTransfer.AddString(varCardNumber);
		rs.MoveNext();
	}
	rs.Close();
	db.Close();
	GetDlgItem(IDC_TRANSFER_HINT)->ShowWindow(SW_HIDE);
	return true;
}

int transferotherflag = 0;
// AccountTransfer ��Ϣ�������


void AccountTransfer::OnClickedTransferTransfer()
{
	CDatabase db;
	db.Open("bankmanagement");
	CString sqlstr, sqlstraccountfrom,sqlstraccountto, sqlstrverify;//,username,idcard,pwd,address,email,number;
	UpdateData(TRUE);//�����ı������
	if (m_TransferAmount<1 || m_TransferAmount>10000);
	else{
		sqlstrverify.Format(_T("select card_password from card where card_number='%s'"), m_TransferFromcardnumber);//�˶����п�����
		//MessageBox(sqlstr);
		CRecordset rs(&db);
		rs.Open(CRecordset::forwardOnly, (_T("%s"), sqlstrverify));
		CString pwd;
		rs.GetFieldValue(_T("card_password"), pwd);
		if (pwd == m_TransferPassword){
			CString timestr;//////��ȡϵͳʱ��
			CTime tm; tm = CTime::GetCurrentTime();
			timestr = tm.Format("%Y��%m��%d�� %X");
			sqlstr.Format(_T("insert into operate_transfer(money_value,card_number_from,card_number_to,operate_time) values('%f','%s','%s','%s')"), m_TransferAmount, m_TransferFromcardnumber, m_TransferTocardnumber,timestr);//�������ݴ���
			
			if (transferotherflag == 0){
				sqlstraccountfrom.Format(_T("update card set money_balance=money_balance-'%f'where card_number='%s'"), m_TransferAmount, m_TransferFromcardnumber);//���¿�����Ϣ
			}
			else
			{
				sqlstraccountfrom.Format(_T("update card set money_balance=money_balance-'%f'where card_number='%s'"), m_TransferAmount*1.01, m_TransferFromcardnumber);//���¿�����Ϣ,�û���ת�˼�������
				CString sqlstrtransferother,sqlstrtransferotherrecord;
				sqlstrtransferother.Format(_T("update bank_account set money_amount=money_amount+'%f'"), m_TransferAmount*0.01);//������ת�������˻�
				sqlstrtransferotherrecord.Format(_T("insert into operate_bank(card_number,money_amount,operate_type,operate_time) values('%s','%f','ת��������','%s')"), m_TransferFromcardnumber, m_TransferAmount*0.01,timestr);//������ת���¼
				db.ExecuteSQL(sqlstrtransferother);
				db.ExecuteSQL(sqlstrtransferotherrecord);
			}
			sqlstraccountto.Format(_T("update card set money_balance=money_balance+'%f'where card_number='%s'"), m_TransferAmount, m_TransferTocardnumber);
			MessageBox("ȷ����");
			CString sqlstrbalance;
			sqlstrbalance.Format(_T("select money_balance from card where card_number='%s'"), m_TransferFromcardnumber);//�ж����
			CRecordset rss(&db);
			rss.Open(CRecordset::forwardOnly, (_T("%s"), sqlstrbalance));
			CString strbalance;
			//MessageBox("test");
			rss.GetFieldValue(_T("money_balance"), strbalance);

			float balance = _tstof(strbalance);

			if (m_TransferAmount > balance)
			{
				MessageBox("����");
				rss.Close();
				rs.Close();
				db.Close();
			}
			else
			{
				db.ExecuteSQL(sqlstr);
				db.ExecuteSQL(sqlstraccountfrom);
				db.ExecuteSQL(sqlstraccountto);
				rss.Close();
				rs.Close();
				db.Close();
				MessageBox("ת���ɹ���");
				errortimes = 3;
				m_TransferFromcardnumber = "";
				m_TransferTocardnumber = "";
				m_TransferPassword = "";
				m_TransferTousername = "";
				m_TransferAmount = 0;
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
				sqlstr.Format(_T("update card set card_status='����'where card_number='%s'"), m_TransferFromcardnumber);
				db.ExecuteSQL(sqlstr);
				db.Close();

				MessageBox("���ſ��Ѷ��ᣬ����ϵ����Ա");
				errortimes = 3;
				AccountTransfer::OnInitDialog();
				//AccountProperty::OnInitDialog();
			}
			else{
				errortimes--;
				CString warningstr;
				warningstr.Format(_T("���벻ƥ��\n������%d�λ���"), errortimes);
				MessageBox(warningstr);
				TransferEdit.SetFocus();
				TransferEdit.SetSel(0, -1);
			}
		}
	}
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void AccountTransfer::OnKillfocusEditTransferTarget()
{
	UpdateData(TRUE);
	CDatabase db;
	db.Open("bankmanagement");
	CString sqlstrconfirm,foundflag;
	sqlstrconfirm.Format(_T("select count(user_name) from user where user_id=(select user_id from card where card_number='%s')"), m_TransferTocardnumber);
	CRecordset rs(&db);
	rs.Open(CRecordset::forwardOnly, (_T("%s"), sqlstrconfirm));
	rs.GetFieldValue(_T("count(user_name)"), foundflag);
	if (foundflag == '0'){
		MessageBox("���ſ�������");
		GetDlgItem(IDC_TRANSFER_TRANSFER)->EnableWindow(false);
	}
	else
	{
		
		GetDlgItem(IDC_TRANSFER_TRANSFER)->EnableWindow(true);
		CString sqlstr;
		sqlstr.Format(_T("select user_name from user where user_id=(select user_id from card where card_number='%s')"), m_TransferTocardnumber);
		CRecordset rss(&db);
		rss.Open(CRecordset::forwardOnly, (_T("%s"), sqlstr));
		rss.GetFieldValue(_T("user_name"), m_TransferTousername);
		if (m_TransferTousername == CurrentUser);
		else
		{
			GetDlgItem(IDC_TRANSFER_HINT)->ShowWindow(SW_SHOW);
			transferotherflag = 1;
		}
		//MessageBox(m_DepositUsername);
		UpdateData(FALSE);
		rss.Close();
	}
	rs.Close();
	db.Close();
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


//void AccountTransfer::OnCbnSelchangeComboTransfer()
//{
//	AccountTransfer::OnInitDialog();
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//}


//void AccountTransfer::OnSetfocusComboTransfer()
//{
//	CDialogEx::OnInitDialog();
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//}


void AccountTransfer::OnSetfocusComboTransfer()
{
	ComboTransfer.ResetContent();
	AccountTransfer::OnInitDialog();
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
