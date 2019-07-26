// LogFileFilterView.h : interface of the CLogFileFilterView class
//
/////////////////////////////////////////////////////////////////////////////
#include "ColorListBox.h"
#include <map>
using namespace std;


#if !defined(AFX_LOGFILEFILTERVIEW_H__EEF7CA18_A63B_4D81_A6E8_7902223F26A4__INCLUDED_)
#define AFX_LOGFILEFILTERVIEW_H__EEF7CA18_A63B_4D81_A6E8_7902223F26A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CLogFileFilterView : public CEditView
{
protected: // create from serialization only
	CLogFileFilterView();
	DECLARE_DYNCREATE(CLogFileFilterView)

// Attributes
public:
	CLogFileFilterDoc* GetDocument();

// Operations
public:
	//申明空间ListBox显示
	CColorListBox * m_pListBox;
	CRect m_rect;
	//CFile *pfileIPDBG;	//CADCOM与IPDBG文件指针
	//CFile *pfileCADCOM;
	CString strCadcomFilePath;
	CString strIpdbgFilePath;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogFileFilterView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLogFileFilterView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLogFileFilterView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void ChangeSize(CWnd* pWnd, int cx, int cy);
	//afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // debug version in LogFileFilterView.cpp
inline CLogFileFilterDoc* CLogFileFilterView::GetDocument()
   { return (CLogFileFilterDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGFILEFILTERVIEW_H__EEF7CA18_A63B_4D81_A6E8_7902223F26A4__INCLUDED_)
