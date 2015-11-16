// Login.cpp : 实现文件
//

#include "stdafx.h"
#include "bankmanagement.h"
#include "Login.h"
#include "afxdialogex.h"
#include "Account.h"
#include "Hello.h"
#include "ForgetPassword.h"

// Login 对话框

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
	
	this->GetParent()->SendMessage(WM_CLOSE);//关闭父对话框
	CDialogEx::OnInitDialog();
	ModifyStyleEx(0, WS_EX_APPWINDOW);
	HICON m_hIcon;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_hCursor = AfxGetApp()->LoadCursor(IDR_CURSOR);
	GetDlgItem(IDC_FORGET_PASSWORD)->GetWindowRect(&m_StaticRect);
	
	ScreenToClient(&m_StaticRect);
	CFont *f;
	f = new CFont;
	f->CreateFontA(14, 5, 0, 0, FW_BOLD, TRUE, TRUE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));
	GetDlgItem(IDC_FORGET_PASSWORD)->SetFont(f);
	
	return true;
}

// Login 消息处理程序


void Login::OnClickedLoginLogin()
{
	//CString CurrentUser = "";//登录账户，改全局函数 
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
		MessageBox("验证码错误");
		Login::OnClickedVerifyPic();
	}
	else if (m_LogUsername.IsEmpty())
	{
		MessageBox("不输账号就想登陆？！\n别逗了╮(╯▽╰)╭");
	}
	else if (rs.GetRecordCount() == 0)
	{
		MessageBox("账号不存在！");
	}
	else
	{
		rs.GetFieldValue(_T("user_pwd"), pwd);
		rs.Close();
		db.Close();
		if (pwd == m_LogPwd)
		{
			MessageBox("登录成功");
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
			MessageBox("密码错误！");
		}
	}
	// TODO:  在此添加控件通知处理程序代码
}


void Login::OnClickedLoginCancel()
{
	Hello dlg;
	fatherflag = 1;
	ShowWindow(SW_HIDE);
	dlg.DoModal();
	ShowWindow(SW_SHOW);
	// TODO:  在此添加控件通知处理程序代码
}






void Login::OnLButtonDown(UINT nFlags, CPoint point)
{
	
	if (point.x > m_StaticRect.left && point.x < m_StaticRect.right &&point.y > m_StaticRect.top  && point.y < m_StaticRect.bottom)
	{
		SetCursor(m_hCursor);
		Login::OnStnClickedForgetPassword();
	}
	
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnLButtonDown(nFlags, point);
}


HBRUSH Login::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if (pWnd->GetDlgCtrlID() == IDC_FORGET_PASSWORD)
	{
		pDC->SetTextColor(RGB(255, 0, 0));
		
	}
	
	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}






HCURSOR Login::OnQueryDragIcon()
{
	return (HCURSOR)m_hIcon;
}

BOOL  myCreateBitmap(HDC hDC, HBITMAP hbitmap,
	PBITMAPFILEHEADER &outheadbuf, long *outheadsize,
	PBITMAPINFO &outinfobuf, long *outinfosize,
	LPBYTE &outdatabuf, long *outdatasize)	//生成单色位图					 
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
	bmp.bmBitsPixel = 1;  //强制赋值转换出来的每像素BIT数
	cClrBits = 1;  //得到每像素多少位		
	*outinfosize = sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)* (1 << cClrBits);
	outinfobuf = (PBITMAPINFO)GlobalAlloc(GPTR, *outinfosize);
	outinfobuf->bmiHeader.biSize = sizeof(BITMAPINFOHEADER); //信息头大小（不含调色板）	
	outinfobuf->bmiHeader.biWidth = bmp.bmWidth;
	outinfobuf->bmiHeader.biHeight = bmp.bmHeight;
	outinfobuf->bmiHeader.biPlanes = bmp.bmPlanes;
	outinfobuf->bmiHeader.biBitCount = bmp.bmBitsPixel;
	my_biClrUsed = (1 << cClrBits);
	outinfobuf->bmiHeader.biClrUsed = my_biClrUsed;
	outinfobuf->bmiHeader.biCompression = BI_RGB;
	outinfobuf->bmiHeader.biSizeImage = ((outinfobuf->bmiHeader.biWidth * cClrBits + 31) & ~31)\

		/ 8 * outinfobuf->bmiHeader.biHeight;
	//图像大小	
	outinfobuf->bmiHeader.biClrImportant = 0;
	/////////////////////////////////得到位图数据	
	// GlobalAlloc分配位图数据的内存	
	// GetDIBits 根据hDC 和HBITMAP得到位图数据、调色板数据	
	*outdatasize = outinfobuf->bmiHeader.biSizeImage;
	outdatabuf = (LPBYTE)GlobalAlloc(GPTR, *outdatasize);  //根据位图大小分配内存	
	if (!outdatabuf)
		goto errout;
	if (!GetDIBits(//根据DC和BITMAP得到位图数据		
		hDC,
		hbitmap,
		0,
		(WORD)outinfobuf->bmiHeader.biHeight,
		outdatabuf,     // outdatabuf中得到位图数据		
		outinfobuf,
		DIB_RGB_COLORS))

	{
		goto errout;
	}

	/////////////////////////////////得到文件头	
	*outheadsize = sizeof(BITMAPFILEHEADER);
	outheadbuf = (PBITMAPFILEHEADER)GlobalAlloc(GPTR, *outheadsize);
	//根据位图大小分配内存	
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

	//////////////////////错误处理	
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

BOOL ShengChengYanZhenMa(CString str, CFile& file)//生成汉字验证码
{
	ASSERT(0 == str.GetLength() % 2);

	CWnd* pDesk = CWnd::GetDesktopWindow();
	CDC* pDC = pDesk->GetDC();

	//每个字符的位置随机偏移4
	CRect r(0, 0, 0, 0);
	pDC->DrawText(str, &r, DT_CALCRECT);
	const int w = r.Width() + 4;
	const int h = r.Height() + 4;
	const int iCharWidth = w * 2 / str.GetLength();

	//建立内存DC和位图并填充背景
	CBitmap bm;
	bm.CreateCompatibleBitmap(pDC, w, h);
	CDC memdc;
	memdc.CreateCompatibleDC(pDC);
	CBitmap*pOld = memdc.SelectObject(&bm);
	memdc.FillSolidRect(0, 0, w, h, RGB(255, 255, 255));

	::SetGraphicsMode(memdc.m_hDC, GM_ADVANCED);//为字体倾斜作准备

	for (int i = 0; i < str.GetLength() / 2; i++)
	{
		//设置字体
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

	//将内容存到文件(CFile或CMemFile)
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


void Login::OnStnClickedForgetPassword()/////////////////////////////////////点击静态控件
{

	ForgetPassword dlg;

	dlg.DoModal();

	// TODO:  在此添加控件通知处理程序代码
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
	
	// TODO:  在此添加控件通知处理程序代码
}