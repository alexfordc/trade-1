
// CTP_mfc.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCTP_mfcApp: 
// �йش����ʵ�֣������ CTP_mfc.cpp
//

class CCTP_mfcApp : public CWinApp
{
public:
	CCTP_mfcApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCTP_mfcApp theApp;