// Sky_Writing.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CSky_WritingApp:
// �аѾ\��@�����O�� Sky_Writing.cpp
//

class CSky_WritingApp : public CWinApp
{
public:
	CSky_WritingApp();

// �мg
	public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern CSky_WritingApp theApp;