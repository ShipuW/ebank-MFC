// ForgetPassword.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "bankmanagement.h"
#include "ForgetPassword.h"
#include "afxdialogex.h"
#include "winsock2.h"  
#pragma comment(lib,"WSOCK32")  
#define SMTP_MAXLINE  76
// ForgetPassword �Ի���

IMPLEMENT_DYNAMIC(ForgetPassword, CDialogEx)

ForgetPassword::ForgetPassword(CWnd* pParent /*=NULL*/)
	: CDialogEx(ForgetPassword::IDD, pParent)
	, m_ForgetpasswordUsername(_T(""))
	, m_ForgetpasswordIdcard(_T(""))
	, m_ForgetpasswordEmail(_T(""))
{

}

ForgetPassword::~ForgetPassword()
{
}

void ForgetPassword::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FORGET_USERNAME, m_ForgetpasswordUsername);
	DDX_Text(pDX, IDC_FORGET_IDCARD, m_ForgetpasswordIdcard);
	DDX_Text(pDX, IDC_FORGET_EMAIL, m_ForgetpasswordEmail);
}


BEGIN_MESSAGE_MAP(ForgetPassword, CDialogEx)
	ON_BN_CLICKED(IDC_FORGET_FIND, &ForgetPassword::OnClickedForgetFind)
END_MESSAGE_MAP()


BOOL ForgetPassword::OnInitDialog()
{
	CDialog::OnInitDialog();
	ModifyStyleEx(0, WS_EX_APPWINDOW);
	
	HICON m_hIcon;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	m_Name = _T("��ʿ��");               //������
	m_Addr = _T("w424065448@126.com");     //���ŵ�ַ
	m_Server = _T("smtp.126.com");   //smtp������
	m_Port = 25;                     //smtp�ı����˿�
	m_User = _T("w424065448");             //�û���
	m_Pass = _T("135795");           //����

	m_Receiver = _T("424065448@qq.com"); //�����˵�ַ
	m_Title = _T("�����һؽ��");            //����
	m_CC = _T("");                   //����
	m_BCC = _T("");                  //����
	m_Letter = _T("test");               //�ż�����
	m_Attach = _T("");               //����
	UpdateData(FALSE);               //�����û�����

	return TRUE;  // return TRUE  unless you set the focus to a control
}


////////////////////////////////////////////////////////////////////////////////////Email
/////////////////////////////////////////////////////////////////////////////////////////
// ForgetPassword ��Ϣ�������


void ForgetPassword::OnClickedForgetFind()
{
	CDatabase db;
	db.Open("bankmanagement");
	CString sqlstr, dbusernumber,dbidcard, dbemail,dbpwd;//,username,idcard,pwd,address,email,number;
	UpdateData(TRUE);//�����ı������
	//MessageBox(m_RegUsername);

	sqlstr.Format(_T("select count(*),user_idcard,user_pwd,user_email from user where user_name='%s'"), m_ForgetpasswordUsername);
	CRecordset rs(&db);
	//MessageBox(sqlstr);
	rs.Open(CRecordset::forwardOnly, (_T("%s"), sqlstr));
	rs.GetFieldValue(_T("count(*)"), dbusernumber);
	
	if (m_ForgetpasswordUsername.IsEmpty() || m_ForgetpasswordIdcard.IsEmpty() || m_ForgetpasswordEmail.IsEmpty() )
	{
		MessageBox("��*Ϊ������", "��������");
	}
	else if (dbusernumber == "0")
	{
		MessageBox("δ�ҵ��û�");
	}
	else
	{
		rs.GetFieldValue(_T("user_idcard"), dbidcard);
		rs.GetFieldValue(_T("user_email"), dbemail);
		rs.GetFieldValue(_T("user_pwd"), dbpwd);
		if (dbidcard == m_ForgetpasswordIdcard&&dbemail == m_ForgetpasswordEmail){
			
			

			m_Letter = _T("�����˻� ") + m_ForgetpasswordUsername + _T(" ����Ϊ��") + dbpwd + _T("\n�����Ʊ��棬�Է�й©��");
			//////////////////////////////////////////////////////////////////////////////////
			//�趨smtp��ı�����ʹָ֮�򱾶Ի����Ա㴫����Ϣ
			smtpSocket.SetParent(this);
			UpdateData(TRUE);           //ȡ���û��ڶԻ��������������
			smtpSocket.Create();        //�����׽��ֶ���ĵײ��׽���
			smtpSocket.Connect((LPCSTR)m_Server, m_Port); //����pop3������
			//�б�����
			//while (m_listInfo.GetCount()!=0)
			//          m_listInfo.DeleteString(0);
			UpdateData(FALSE);          //�����û�����
			////////////////////////////////////////////////////////////////////////////////////
			MessageBox("���������ѷ�������������\n��û�յ���鿴������");
			rs.Close();
			db.Close();

			this->SendMessage(WM_CLOSE);//�رո��Ի���
		}
		else MessageBox("��Ϣ����");
		
	}
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}



////////////////////////////////////////////////////////////////////////Email
void ForgetPassword::Disp(LONG flag)
{
	CString s;
	switch (flag)
	{
	case S_CONNECT: //�����ӵ�����������ʾ��Ϣ
		s = "�Ѿ����ӵ�" + m_Server + "������\r\n";
		m_Info += s;
		//m_listInfo.AddString(s);
		break;
	case S_RECEIVE: //�յ�����������������,��ʾ������
		m_Info += smtpSocket.lastMsg;
		//m_listInfo.AddString(smtpSocket.lastMsg);
		break;
	case S_CLOSE: //��ʾ�ر����ӵ���Ϣ
		m_Info += smtpSocket.error;
		//		m_listInfo.AddString(smtpSocket.error);
		s = "�����Ѿ��ر�\r\n";
		m_Info += s;
		//m_listInfo.AddString(s); 
		break;
	}
	UpdateData(FALSE);   //�����û�����
}

void ForgetPassword::GetHeader()
{
	UpdateData(TRUE);
	CString sepa;
	CString sReply;
	sReply = _T("");

	//���� "Date:" ����������
	CTime now(CTime::GetCurrentTime());
	CString sDate(now.Format(_T("%a, %d %b %Y %H:%M:%S ")));
	sDate += "+0800 (CST)";

	CString sBuf(sReply);
	if (m_Attach.GetLength())
	{
		sReply.Format(_T("MIME-Version: 1.0\r\n"));
		sBuf += sReply;
	}

	//��� From �� to �ֶ�
	//From: "=?GB2312?B?XXXXXXXXXX=?=" // �����ˣ������˱���
	//To: Li@163.com 

	coder.Encode(m_Addr);
	sReply.Format(_T("From: %s\r\n"), m_Addr);
	//	sReply.Format(_T("From: =?gb2312?B?%s?=\r\n"), coder.EncodedMessage());
	sBuf += sReply;

	sReply.Format(_T("To: %s\r\n"), m_Receiver);
	sBuf += sReply;

	//��� Date�ֶ�
	//Date: Wed, 8 Apr 2004 16:16:16 +0800 // ���ŵ�����ʱ��
	sReply.Format(_T("Date: %s\r\n"), sDate);
	sBuf += sReply;

	//��� subject�ֶ�
	//Subject: =?GB2312?B?XXXXXX=?= // ���⣬�����˱���
	coder.Encode(m_Title);
	sReply.Format(_T("Subject: %s\r\n"), m_Title);
	//	sReply.Format(_T("Subject: =?gb2312?B?%s?=\r\n"),coder.EncodedMessage());
	sBuf += sReply;

	//����У���� Cc �ֶ�
	if (m_CC.GetLength())
	{
		sReply.Format(_T("Cc: %s\r\n"), m_CC);
		sBuf += sReply;
	}

	//����У����Bcc �ֶ�
	if (m_BCC.GetLength())
	{
		sReply.Format(_T("Bcc: %s\r\n"), m_BCC);
		sBuf += sReply;
	}

	//�����Ҫ����� Mime �ֶ�
	//MIME-Version: 1.0               // MIME�汾
	//Content-type: multipart/mixed;  // ���������Ƕಿ��/�����
	//boundary = "NextPart_000_00A"  // ָ��һ���߽������ַ���

	sepa = _T("Boundary-=_HfNFaIwtPvzJDUQrvChaEKIMklNx");
	if (m_Attach.GetLength())
	{
		//		sReply.Format(_T("MIME-Version: 1.0\r\n"));
		//		sBuf += sReply;
		sReply.Format("Content-Type:Multipart/mixed;boundary=%s\r\n", sepa);
		sBuf += sReply;
		sBuf += _T("\r\n");
	}
	else {
		sBuf += _T("\r\n");
		sReply.Format(_T(" %s\r\n"), m_Letter);
		sBuf += sReply;
		sReply.Format(_T("%c%c.%c%c"), 13, 10, 13, 10);
		sBuf += sReply;
	}
	smtpSocket.Send((LPCSTR)sBuf, sBuf.GetLength());
	m_Info += sBuf;

	if (m_Attach.GetLength())
	{
		sReply.Format(_T("--%s\r\n"), sepa);
		sBuf = sReply;

		sBuf += _T("Content-Type: text/plain; charset='gb2312'\r\n");
		sBuf += _T("Content-Transfer-Encoding: base64\r\n");
		sBuf += _T("\r\n");

		coder.Encode(m_Letter);
		sReply.Format(_T("%s\r\n"), coder.EncodedMessage());
		sBuf += sReply;

		sReply.Format(_T("--%s\r\n"), sepa);
		sBuf += sReply;

		sBuf += _T("Content-Type: text/plain; charset='gb2312'\r\n");
		sBuf += _T("Content-Transfer-Encoding: base64\r\n");
		sBuf += _T("\r\n");

		//add Letter	
		LPSTR pszBody = NULL;
		int nBodySize = 0;
		if (!GetBody(pszBody, nBodySize))
		{
			TRACE(_T("Failed in call to send body parts body, GetLastError returns: %d\n"), GetLastError());
		}
		sReply = pszBody;
		sBuf += sReply;
		sReply.Format(_T("--%s\r\n"), sepa);
		sBuf += sReply;

		sReply.Format(_T("%c%c.%c%c"), 13, 10, 13, 10);
		sBuf += sReply;
		smtpSocket.Send((LPCSTR)sBuf, sBuf.GetLength());
		m_Info += sBuf;
	}
	UpdateData(FALSE);
}

BOOL ForgetPassword::GetBody(LPSTR& pszBody, int& nBodySize)
{
	BOOL bSuccess = FALSE;

	//�򿪸����ļ�
	CFile infile;
	if (infile.Open(m_Attach, CFile::modeRead | CFile::shareDenyWrite))
	{
		DWORD dwSize = infile.GetLength();
		if (dwSize)
		{
			//��������
			BYTE* pszIn = new BYTE[dwSize];
			try
			{
				infile.Read(pszIn, dwSize);
				bSuccess = TRUE;
			}
			catch (CFileException* pEx)
			{
				bSuccess = FALSE;
				pEx->Delete();
			}

			if (bSuccess)
			{
				coder.Encode(pszIn, dwSize); //����
				delete[] pszIn;               //ɾ�������뻺����
				infile.Close();                //�ر������ļ�

				//�γɱ����ķ�������
				LPSTR pszEncoded = coder.EncodedMessage();
				int nEncodedSize = coder.EncodedMessageSize();
				nBodySize = nEncodedSize + (((nEncodedSize / 76) + 1) * 2) + 1;
				pszBody = new char[nBodySize];
				--nBodySize;

				int nInPos = 0;
				int nOutPos = 0;
				while (nInPos < nEncodedSize)
				{
					int nThisLineSize = min(nEncodedSize - nInPos, SMTP_MAXLINE);
					CopyMemory(&pszBody[nOutPos], &pszEncoded[nInPos], nThisLineSize);
					nOutPos += nThisLineSize;
					CopyMemory(&pszBody[nOutPos], "\r\n", 2);
					nOutPos += 2;
					nInPos += nThisLineSize;
				}
				pszBody[nOutPos] = '\0'; //�Կ��ַ�������
			}
		}
		else  {
			bSuccess = TRUE;
			pszBody = NULL;
			nBodySize = 0;
		}
	}
	else
		TRACE(_T("No bodypart body text or filename specified!\n"));

	return bSuccess;
}


