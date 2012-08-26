// TelePathy.h : main header file for the TELEPATHY application
//

#if !defined(AFX_TELEPATHY_H__2DD1E912_F3FC_40E8_B498_81A420F3984D__INCLUDED_)
#define AFX_TELEPATHY_H__2DD1E912_F3FC_40E8_B498_81A420F3984D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTelePathyApp:
// See TelePathy.cpp for the implementation of this class
//

class CTelePathyApp : public CWinApp
{
public:
	CTelePathyApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelePathyApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTelePathyApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TELEPATHY_H__2DD1E912_F3FC_40E8_B498_81A420F3984D__INCLUDED_)
