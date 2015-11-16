#pragma once


// Hello 对话框

class Hello : public CDialogEx
{
	DECLARE_DYNAMIC(Hello)

public:
	Hello(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Hello();

// 对话框数据
	enum { IDD = IDD_HELLO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedHelloLogin();
	afx_msg void OnClickedHelloRegist();
//	afx_msg void OnDoubleclickedHelloLogin();
	afx_msg void OnClickedHelloManager();
	//afx_msg void OnClickedButton3();
	afx_msg BOOL OnInitDialog();
	//afx_msg void OnPaint();
	
};
