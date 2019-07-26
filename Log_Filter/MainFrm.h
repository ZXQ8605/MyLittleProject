// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////


#if !defined(AFX_MAINFRM_H__C448626A_E27D_4BB2_A4C7_B948F10E6F98__INCLUDED_)
#define AFX_MAINFRM_H__C448626A_E27D_4BB2_A4C7_B948F10E6F98__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
//	CFile* pFileIpdbg;	// 用于IPDBG格式转换
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSelectCadcom();
	afx_msg void OnSelectIpdbg();
	afx_msg void OnCodebit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTrainnumwin();
	afx_msg void OnPoorsperation();
	afx_msg void OnCounter();
	afx_msg void OnMasterconnection();
	afx_msg void OnChange();
	afx_msg void OnResultconserve();
	afx_msg void OnClose();
	afx_msg void OnCleanscreen();
	
	//afx_msg void OnTimer(UINT_PTR nIDEvent);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__C448626A_E27D_4BB2_A4C7_B948F10E6F98__INCLUDED_)
