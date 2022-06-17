// puertos.h : main header file for the PUERTOS DLL
//

#if !defined(AFX_PUERTOS_H__21576220_F087_4206_81F8_317EA6354A48__INCLUDED_)
#define AFX_PUERTOS_H__21576220_F087_4206_81F8_317EA6354A48__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPuertosApp
// See puertos.cpp for the implementation of this class
//

class CPuertosApp : public CWinApp
{
public:
	CPuertosApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPuertosApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CPuertosApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//void PASCAL EXPORT caracter(LPSTR c);

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PUERTOS_H__21576220_F087_4206_81F8_317EA6354A48__INCLUDED_)
