// Login.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "bankmanagement.h"
#include "Login.h"
#include "afxdialogex.h"
#include "Account.h"
#include "Hello.h"
#include "ForgetPassword.h"

// Login �Ի���

IMPLEMENT_DYNAMIC(Login, CDialog)

Login::Login(CWnd* pParent /*=NULL*/)
	: CDialogEx(Login::IDD, pParent)
	, m_LogPwd(_T(""))
	, m_LogIdentify(_T(""))
	, m_LogUsername(_T(""))
{

}

Login::~Login()
{
}

void Login::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LOGIN_PWD, m_LogPwd);
	DDX_Text(pDX, IDC_LOGIN_IDENTIFY, m_LogIdentify);
	DDX_Text(pDX, IDC_LOGIN_USERNAME, m_LogUsername);

	DDX_Control(pDX, IDC_VERIFY_PIC, m_bitmap);
}


BEGIN_MESSAGE_MAP(Login, CDialog)
	ON_BN_CLICKED(IDC_LOGIN_LOGIN, &Login::OnClickedLoginLogin)
	ON_BN_CLICKED(IDC_LOGIN_CANCEL, &Login::OnClickedLoginCancel)
	ON_STN_CLICKED(IDC_FORGET_PASSWORD, &Login::OnStnClickedForgetPassword)
//	ON_STN_DBLCLK(IDC_FORGET_PASSWORD, &Login::OnDblclkForgetPassword)
	ON_WM_LBUTTONDOWN()
	ON_WM_CTLCOLOR()

	ON_EN_SETFOCUS(IDC_LOGIN_IDENTIFY, &Login::OnSetfocusLoginIdentify)
	ON_STN_CLICKED(IDC_VERIFY_PIC, &Login::OnClickedVerifyPic)
END_MESSAGE_MAP()

BOOL Login::OnInitDialog()
{
	
	this->GetParent()->SendMessage(WM_CLOSE);//�رո��Ի���
	CDialogEx::OnInitDialog();
	ModifyStyleEx(0, WS_EX_APPWINDOW);
	HICON m_hIcon;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	m_hCursor = AfxGetApp()->LoadCursor(IDR_CURSOR);
	GetDlgItem(IDC_FORGET_PASSWORD)->GetWindowRect(&m_StaticRect);
	
	ScreenToClient(&m_StaticRect);
	CFont *f;
	f = new CFont;
	f->CreateFontA(14, 5, 0, 0, FW_BOLD, TRUE, TRUE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));
	GetDlgItem(IDC_FORGET_PASSWORD)->SetFont(f);
	
	return true;
}

// Login ��Ϣ�������


void Login::OnClickedLoginLogin()
{
	//CString CurrentUser = "";//��¼�˻�����ȫ�ֺ��� 
	UpdateData(TRUE);
	//MessageBox(m_LogUsername);
	CDatabase db;
	db.Open("bankmanagement");
	CString sqlstr;
	sqlstr.Format(_T("select user_pwd from user where user_name='%s'"), m_LogUsername);
	CRecordset rs(&db);
	//MessageBox(sqlstr);
	rs.Open(CRecordset::forwardOnly, (_T("%s"), sqlstr));
	CString	pwd;
	if (m_LogIdentify.IsEmpty()||m_LogIdentify != randomseq){
		MessageBox("��֤�����");
		Login::OnClickedVerifyPic();
	}
	else if (m_LogUsername.IsEmpty())
	{
		MessageBox("�����˺ž����½����\n���˨r(�s���t)�q");
	}
	else if (rs.GetRecordCount() == 0)
	{
		MessageBox("�˺Ų����ڣ�");
	}
	else
	{
		rs.GetFieldValue(_T("user_pwd"), pwd);
		rs.Close();
		db.Close();
		if (pwd == m_LogPwd)
		{
			MessageBox("��¼�ɹ�");
			//MessageBox(CurrentUser);
			CurrentUser = m_LogUsername;
			//MessageBox(CurrentUser);
			Account dlg;
			ShowWindow(SW_HIDE);
			dlg.DoModal();
			ShowWindow(SW_SHOW);
		}
		else
		{
			MessageBox("�������");
		}
	}
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void Login::OnClickedLoginCancel()
{
	Hello dlg;
	fatherflag = 1;
	ShowWindow(SW_HIDE);
	dlg.DoModal();
	ShowWindow(SW_SHOW);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}






void Login::OnLButtonDown(UINT nFlags, CPoint point)
{
	
	if (point.x > m_StaticRect.left && point.x < m_StaticRect.right &&point.y > m_StaticRect.top  && point.y < m_StaticRect.bottom)
	{
		SetCursor(m_hCursor);
		Login::OnStnClickedForgetPassword();
	}
	
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnLButtonDown(nFlags, point);
}


HBRUSH Login::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if (pWnd->GetDlgCtrlID() == IDC_FORGET_PASSWORD)
	{
		pDC->SetTextColor(RGB(255, 0, 0));
		
	}
	
	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}






HCURSOR Login::OnQueryDragIcon()
{
	return (HCURSOR)m_hIcon;
}

BOOL  myCreateBitmap(HDC hDC, HBITMAP hbitmap,
	PBITMAPFILEHEADER &outheadbuf, long *outheadsize,
	PBITMAPINFO &outinfobuf, long *outinfosize,
	LPBYTE &outdatabuf, long *outdatasize)	//���ɵ�ɫλͼ					 
{
	BITMAP bmp;
	WORD cClrBits;
	DWORD my_biClrUsed = 0;
	outinfobuf = NULL;
	outdatabuf = NULL;
	outheadbuf = NULL;

	if (!GetObject(hbitmap, sizeof(BITMAP), (LPSTR)&bmp))
		goto errout;
	bmp.bmPlanes = 1;
	bmp.bmBitsPixel = 1;  //ǿ�Ƹ�ֵת��������ÿ����BIT��
	cClrBits = 1;  //�õ�ÿ���ض���λ		
	*outinfosize = sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)* (1 << cClrBits);
	outinfobuf = (PBITMAPINFO)GlobalAlloc(GPTR, *outinfosize);
	outinfobuf->bmiHeader.biSize = sizeof(BITMAPINFOHEADER); //��Ϣͷ��С��������ɫ�壩	
	outinfobuf->bmiHeader.biWidth = bmp.bmWidth;
	outinfobuf->bmiHeader.biHeight = bmp.bmHeight;
	outinfobuf->bmiHeader.biPlanes = bmp.bmPlanes;
	outinfobuf->bmiHeader.biBitCount = bmp.bmBitsPixel;
	my_biClrUsed = (1 << cClrBits);
	outinfobuf->bmiHeader.biClrUsed = my_biClrUsed;
	outinfobuf->bmiHeader.biCompression = BI_RGB;
	outinfobuf->bmiHeader.biSizeImage = ((outinfobuf->bmiHeader.biWidth * cClrBits + 31) & ~31)\

		/ 8 * outinfobuf->bmiHeader.biHeight;
	//ͼ���С	
	outinfobuf->bmiHeader.biClrImportant = 0;
	/////////////////////////////////�õ�λͼ����	
	// GlobalAlloc����λͼ���ݵ��ڴ�	
	// GetDIBits ����hDC ��HBITMAP�õ�λͼ���ݡ���ɫ������	
	*outdatasize = outinfobuf->bmiHeader.biSizeImage;
	outdatabuf = (LPBYTE)GlobalAlloc(GPTR, *outdatasize);  //����λͼ��С�����ڴ�	
	if (!outdatabuf)
		goto errout;
	if (!GetDIBits(//����DC��BITMAP�õ�λͼ����		
		hDC,
		hbitmap,
		0,
		(WORD)outinfobuf->bmiHeader.biHeight,
		outdatabuf,     // outdatabuf�еõ�λͼ����		
		outinfobuf,
		DIB_RGB_COLORS))

	{
		goto errout;
	}

	/////////////////////////////////�õ��ļ�ͷ	
	*outheadsize = sizeof(BITMAPFILEHEADER);
	outheadbuf = (PBITMAPFILEHEADER)GlobalAlloc(GPTR, *outheadsize);
	//����λͼ��С�����ڴ�	
	if (!outheadbuf)
		goto errout;
	outheadbuf->bfType = 0x4d42;
	outheadbuf->bfSize = (DWORD)(sizeof(BITMAPFILEHEADER)+
		outinfobuf->bmiHeader.biSize +
		my_biClrUsed * sizeof(RGBQUAD)+
		outinfobuf->bmiHeader.biSizeImage);
	outheadbuf->bfReserved1 = 0;
	outheadbuf->bfReserved2 = 0;

	outheadbuf->bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER)+
		outinfobuf->bmiHeader.biSize +
		my_biClrUsed * sizeof (RGBQUAD);
	return TRUE;

	//////////////////////������	
errout:
	if (outinfobuf) GlobalFree(outinfobuf);
	if (outdatabuf) GlobalFree(outdatabuf);
	if (outheadbuf) GlobalFree(outheadbuf);
	outinfobuf = NULL;
	outdatabuf = NULL;
	outheadbuf = NULL;
	*outheadsize = 0;
	*outinfosize = 0;
	*outdatasize = 0;
	return FALSE;
}

BOOL ShengChengYanZhenMa(CString str, CFile& file)//���ɺ�����֤��
{
	ASSERT(0 == str.GetLength() % 2);

	CWnd* pDesk = CWnd::GetDesktopWindow();
	CDC* pDC = pDesk->GetDC();

	//ÿ���ַ���λ�����ƫ��4
	CRect r(0, 0, 0, 0);
	pDC->DrawText(str, &r, DT_CALCRECT);
	const int w = r.Width() + 4;
	const int h = r.Height() + 4;
	const int iCharWidth = w * 2 / str.GetLength();

	//�����ڴ�DC��λͼ����䱳��
	CBitmap bm;
	bm.CreateCompatibleBitmap(pDC, w, h);
	CDC memdc;
	memdc.CreateCompatibleDC(pDC);
	CBitmap*pOld = memdc.SelectObject(&bm);
	memdc.FillSolidRect(0, 0, w, h, RGB(255, 255, 255));

	::SetGraphicsMode(memdc.m_hDC, GM_ADVANCED);//Ϊ������б��׼��

	for (int i = 0; i < str.GetLength() / 2; i++)
	{
		//��������
		CFont* pFont = memdc.GetCurrentFont();
		LOGFONT logFont;
		pFont->GetLogFont(&logFont);
		logFont.lfOutPrecision = OUT_TT_ONLY_PRECIS;
		logFont.lfOrientation = rand() % 90;
		CFont font;
		font.CreateFontIndirect(&logFont);
		memdc.SelectObject(&font);

		int x = iCharWidth*i + rand() % 5;
		int y = rand() % 5;
		memdc.TextOut(x, y, str.Mid(i * 2, 2));
	}

	//�����ݴ浽�ļ�(CFile��CMemFile)
	PBITMAPFILEHEADER outheadbuf;
	PBITMAPINFO outinfobuf;
	LPBYTE outdatabuf;
	long outheadsize, outinfosize, outdatasize;
	if (!myCreateBitmap(memdc.m_hDC, bm,
		outheadbuf, &outheadsize,
		outinfobuf, &outinfosize,
		outdatabuf, &outdatasize))
		return FALSE;


	file.Write(outheadbuf, outheadsize);
	file.Write(outinfobuf, outinfosize);
	file.Write(outdatabuf, outdatasize);

	memdc.SelectObject(pOld);
	bm.DeleteObject();
	memdc.DeleteDC();
}



void Login::OnSetfocusLoginIdentify()
{
	srand(GetTickCount());

	CString strFileName = "d:\out.bmp";
	CFile file;

	int a = 0, b = 0, c = 0, d = 0, sum;

	while (a == b || a == c || a == d || b == c || b == d || c == d || a == 0)
	{
		a = rand() % 10;
		b = rand() % 10;
		c = rand() % 10;
		d = rand() % 10;
	}

	sum = a * 1000 + b * 100 + c * 10 + d;
	

	randomseq.Format("%d", sum);

	file.Open(strFileName, CFile::modeCreate | CFile::modeWrite);
	ShengChengYanZhenMa(randomseq, file);
	file.Close();

	HBITMAP bitmap = (HBITMAP)LoadImage(AfxGetInstanceHandle(), strFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_bitmap.SetBitmap(bitmap);
	
}


void Login::OnStnClickedForgetPassword()/////////////////////////////////////�����̬�ؼ�
{

	ForgetPassword dlg;

	dlg.DoModal();

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
void Login::OnClickedVerifyPic()
{
	srand(GetTickCount());
	//MessageBox("122");
	CString strFileName = "d:\out.bmp";
	CFile file;

	int a = 0, b = 0, c = 0, d = 0, sum;

	while (a == b || a == c || a == d || b == c || b == d || c == d || a == 0)
	{
		a = rand() % 10;
		b = rand() % 10;
		c = rand() % 10;
		d = rand() % 10;
	}

	sum = a * 1000 + b * 100 + c * 10 + d;


	randomseq.Format("%d", sum);

	file.Open(strFileName, CFile::modeCreate | CFile::modeWrite);
	ShengChengYanZhenMa(randomseq, file);
	file.Close();

	HBITMAP bitmap = (HBITMAP)LoadImage(AfxGetInstanceHandle(), strFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_bitmap.SetBitmap(bitmap);
	
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}