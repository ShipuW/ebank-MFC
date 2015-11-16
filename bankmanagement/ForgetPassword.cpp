// ForgetPassword.cpp : 实现文件
//

#include "stdafx.h"
#include "bankmanagement.h"
#include "ForgetPassword.h"
#include "afxdialogex.h"
#include "winsock2.h"  
#pragma comment(lib,"WSOCK32")  
#define SMTP_MAXLINE  76
// ForgetPassword 对话框

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
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_Name = _T("王士溥");               //发信人
	m_Addr = _T("w424065448@126.com");     //发信地址
	m_Server = _T("smtp.126.com");   //smtp服务器
	m_Port = 25;                     //smtp的保留端口
	m_User = _T("w424065448");             //用户名
	m_Pass = _T("135795");           //口令

	m_Receiver = _T("424065448@qq.com"); //收信人地址
	m_Title = _T("密码找回结果");            //主题
	m_CC = _T("");                   //抄送
	m_BCC = _T("");                  //暗送
	m_Letter = _T("test");               //信件内容
	m_Attach = _T("");               //附件
	UpdateData(FALSE);               //更新用户界面

	return TRUE;  // return TRUE  unless you set the focus to a control
}


////////////////////////////////////////////////////////////////////////////////////Email
/////////////////////////////////////////////////////////////////////////////////////////
// ForgetPassword 消息处理程序


void ForgetPassword::OnClickedForgetFind()
{
	CDatabase db;
	db.Open("bankmanagement");
	CString sqlstr, dbusernumber,dbidcard, dbemail,dbpwd;//,username,idcard,pwd,address,email,number;
	UpdateData(TRUE);//更新文本框变量
	//MessageBox(m_RegUsername);

	sqlstr.Format(_T("select count(*),user_idcard,user_pwd,user_email from user where user_name='%s'"), m_ForgetpasswordUsername);
	CRecordset rs(&db);
	//MessageBox(sqlstr);
	rs.Open(CRecordset::forwardOnly, (_T("%s"), sqlstr));
	rs.GetFieldValue(_T("count(*)"), dbusernumber);
	
	if (m_ForgetpasswordUsername.IsEmpty() || m_ForgetpasswordIdcard.IsEmpty() || m_ForgetpasswordEmail.IsEmpty() )
	{
		MessageBox("带*为必填项", "输入有误");
	}
	else if (dbusernumber == "0")
	{
		MessageBox("未找到用户");
	}
	else
	{
		rs.GetFieldValue(_T("user_idcard"), dbidcard);
		rs.GetFieldValue(_T("user_email"), dbemail);
		rs.GetFieldValue(_T("user_pwd"), dbpwd);
		if (dbidcard == m_ForgetpasswordIdcard&&dbemail == m_ForgetpasswordEmail){
			
			

			m_Letter = _T("您的账户 ") + m_ForgetpasswordUsername + _T(" 密码为：") + dbpwd + _T("\n请妥善保存，以防泄漏。");
			//////////////////////////////////////////////////////////////////////////////////
			//设定smtp类的变量，使之指向本对话框，以便传递信息
			smtpSocket.SetParent(this);
			UpdateData(TRUE);           //取来用户在对话框中输入的数据
			smtpSocket.Create();        //创建套接字对象的底层套接字
			smtpSocket.Connect((LPCSTR)m_Server, m_Port); //连接pop3服务器
			//列表框清空
			//while (m_listInfo.GetCount()!=0)
			//          m_listInfo.DeleteString(0);
			UpdateData(FALSE);          //更新用户界面
			////////////////////////////////////////////////////////////////////////////////////
			MessageBox("您的密码已发送至您的邮箱\n若没收到请查看垃圾箱");
			rs.Close();
			db.Close();

			this->SendMessage(WM_CLOSE);//关闭父对话框
		}
		else MessageBox("信息不符");
		
	}
	// TODO:  在此添加控件通知处理程序代码
}



////////////////////////////////////////////////////////////////////////Email
void ForgetPassword::Disp(LONG flag)
{
	CString s;
	switch (flag)
	{
	case S_CONNECT: //已连接到服务器，显示信息
		s = "已经连接到" + m_Server + "服务器\r\n";
		m_Info += s;
		//m_listInfo.AddString(s);
		break;
	case S_RECEIVE: //收到服务器发来的数据,显示该数据
		m_Info += smtpSocket.lastMsg;
		//m_listInfo.AddString(smtpSocket.lastMsg);
		break;
	case S_CLOSE: //显示关闭连接的信息
		m_Info += smtpSocket.error;
		//		m_listInfo.AddString(smtpSocket.error);
		s = "连接已经关闭\r\n";
		m_Info += s;
		//m_listInfo.AddString(s); 
		break;
	}
	UpdateData(FALSE);   //更新用户界面
}

void ForgetPassword::GetHeader()
{
	UpdateData(TRUE);
	CString sepa;
	CString sReply;
	sReply = _T("");

	//创建 "Date:" 标题行内容
	CTime now(CTime::GetCurrentTime());
	CString sDate(now.Format(_T("%a, %d %b %Y %H:%M:%S ")));
	sDate += "+0800 (CST)";

	CString sBuf(sReply);
	if (m_Attach.GetLength())
	{
		sReply.Format(_T("MIME-Version: 1.0\r\n"));
		sBuf += sReply;
	}

	//添加 From 和 to 字段
	//From: "=?GB2312?B?XXXXXXXXXX=?=" // 发信人，进行了编码
	//To: Li@163.com 

	coder.Encode(m_Addr);
	sReply.Format(_T("From: %s\r\n"), m_Addr);
	//	sReply.Format(_T("From: =?gb2312?B?%s?=\r\n"), coder.EncodedMessage());
	sBuf += sReply;

	sReply.Format(_T("To: %s\r\n"), m_Receiver);
	sBuf += sReply;

	//添加 Date字段
	//Date: Wed, 8 Apr 2004 16:16:16 +0800 // 发信的日期时间
	sReply.Format(_T("Date: %s\r\n"), sDate);
	sBuf += sReply;

	//添加 subject字段
	//Subject: =?GB2312?B?XXXXXX=?= // 主题，进行了编码
	coder.Encode(m_Title);
	sReply.Format(_T("Subject: %s\r\n"), m_Title);
	//	sReply.Format(_T("Subject: =?gb2312?B?%s?=\r\n"),coder.EncodedMessage());
	sBuf += sReply;

	//如果有，添加 Cc 字段
	if (m_CC.GetLength())
	{
		sReply.Format(_T("Cc: %s\r\n"), m_CC);
		sBuf += sReply;
	}

	//如果有，添加Bcc 字段
	if (m_BCC.GetLength())
	{
		sReply.Format(_T("Bcc: %s\r\n"), m_BCC);
		sBuf += sReply;
	}

	//如果需要，添加 Mime 字段
	//MIME-Version: 1.0               // MIME版本
	//Content-type: multipart/mixed;  // 内容类型是多部分/混合型
	//boundary = "NextPart_000_00A"  // 指定一级边界特征字符串

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

	//打开附件文件
	CFile infile;
	if (infile.Open(m_Attach, CFile::modeRead | CFile::shareDenyWrite))
	{
		DWORD dwSize = infile.GetLength();
		if (dwSize)
		{
			//读入数据
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
				coder.Encode(pszIn, dwSize); //编码
				delete[] pszIn;               //删除了输入缓冲区
				infile.Close();                //关闭输入文件

				//形成编码后的发送内容
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
				pszBody[nOutPos] = '\0'; //以空字符串结束
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


