
// bankmanagement.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CbankmanagementApp: 
// �йش����ʵ�֣������ bankmanagement.cpp
//

class CbankmanagementApp : public CWinApp
{
public:
	CbankmanagementApp();
	
// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CbankmanagementApp theApp;