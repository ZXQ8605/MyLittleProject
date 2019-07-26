// LogFileFilterDoc.h : interface of the CLogFileFilterDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGFILEFILTERDOC_H__D08340CC_3DF9_4768_983D_B7F0AE80F223__INCLUDED_)
#define AFX_LOGFILEFILTERDOC_H__D08340CC_3DF9_4768_983D_B7F0AE80F223__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CLogFileFilterDoc : public CDocument
{
protected: // create from serialization only
	CLogFileFilterDoc();
	DECLARE_DYNCREATE(CLogFileFilterDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogFileFilterDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLogFileFilterDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLogFileFilterDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGFILEFILTERDOC_H__D08340CC_3DF9_4768_983D_B7F0AE80F223__INCLUDED_)
