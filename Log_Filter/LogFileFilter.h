// LogFileFilter.h : main header file for the LOGFILEFILTER application
//

#if !defined(AFX_LOGFILEFILTER_H__95B27394_4E8D_42A2_985A_8A67D71033FC__INCLUDED_)
#define AFX_LOGFILEFILTER_H__95B27394_4E8D_42A2_985A_8A67D71033FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLogFileFilterApp:
// See LogFileFilter.cpp for the implementation of this class
//


class CLogFileFilterApp : public CWinApp
{
public:
	CLogFileFilterApp();

	//定义IPDBG与CADCOM的文件指针
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogFileFilterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CLogFileFilterApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGFILEFILTER_H__95B27394_4E8D_42A2_985A_8A67D71033FC__INCLUDED_)
