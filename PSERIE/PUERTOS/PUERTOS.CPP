// puertos.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "puertos.h"
#include <conio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CPuertosApp

BEGIN_MESSAGE_MAP(CPuertosApp, CWinApp)
	//{{AFX_MSG_MAP(CPuertosApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPuertosApp construction

CPuertosApp::CPuertosApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPuertosApp object

CPuertosApp theApp;
void PASCAL EXPORT outport(int dir,int dato)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// normal function body here
	//_outp(dir,dato);
	CString s;
	s.Format("dir= %d dato=%d",dir,dato);
	//MessageBox(NULL,s);
	MessageBox(NULL,s,"DLL DE C++",0);
}
extern "C" int PASCAL EXPORT intport(int dir)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// normal function body here
	return _inp(dir);
}

extern "C" void PASCAL EXPORT caracter(char *c)
{
	MessageBox(NULL,c,c,0);
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
}
	// normal function body here
	//_outp(dir,dato);
//	CString s;
//	s.Format("dir= %s",c);
	//MessageBox(NULL,s);
