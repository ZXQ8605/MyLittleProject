// LogFileFilterDoc.cpp : implementation of the CLogFileFilterDoc class
//

#include "stdafx.h"
#include "LogFileFilter.h"

#include "LogFileFilterDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogFileFilterDoc

IMPLEMENT_DYNCREATE(CLogFileFilterDoc, CDocument)

BEGIN_MESSAGE_MAP(CLogFileFilterDoc, CDocument)
	//{{AFX_MSG_MAP(CLogFileFilterDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogFileFilterDoc construction/destruction

CLogFileFilterDoc::CLogFileFilterDoc()
{
	// TODO: add one-time construction code here

}

CLogFileFilterDoc::~CLogFileFilterDoc()
{
}

BOOL CLogFileFilterDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CLogFileFilterDoc serialization

void CLogFileFilterDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CLogFileFilterDoc diagnostics

#ifdef _DEBUG
void CLogFileFilterDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLogFileFilterDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLogFileFilterDoc commands
