// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "LogFileFilter.h"
#include "CodeBitDlg.h"
#include "PoorSperation.h"
#include "TrainNumWin.h"
#include "Counter.h"
#include "MainFrm.h"
#include "MasterConnection.h"
#include "LogFileFilterDoc.h"
#include "LogFileFilterView.h"
#include "Loghandle.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_SELECT_CADCOM, OnSelectCadcom)
	ON_COMMAND(ID_SELECT_IPDBG, OnSelectIpdbg)
	ON_COMMAND(ID_CODEBIT, OnCodebit)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_TRAINNUMWIN, &CMainFrame::OnTrainnumwin)
	ON_COMMAND(ID_POORSPERATION, &CMainFrame::OnPoorsperation)
	ON_COMMAND(ID_COUNTER, &CMainFrame::OnCounter)
	ON_COMMAND(ID_MASTERCONNECTION, &CMainFrame::OnMasterconnection)
	ON_COMMAND(ID_CHANGE, &CMainFrame::OnChange)
	ON_COMMAND(ID_RESULTCONSERVE, &CMainFrame::OnResultconserve)
//	ON_COMMAND(ID_APP_EXIT, &CMainFrame::OnAppExit)
	ON_WM_CLOSE()
	ON_COMMAND(ID_CLEANSCREEN, &CMainFrame::OnCleanscreen)
	ON_WM_TIMER()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

 //FILE* CMainFrame ::g_FileIpdbg = NULL;
 //FILE* CMainFrame ::g_FileCadcom = NULL; 

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
	//pFileIpdbg->Close();
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	SetTimer(TIMER1, 50, 0);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}


#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnSelectCadcom() 
{
	CString strFilter =  "文本文件(*.txt; *.com)| *.txt; *.com||";
	CLogFileFilterView *pMyView = (CLogFileFilterView*)GetActiveView();
	pMyView->strCadcomFilePath = CLogFileOperation::OpenLogFile(strFilter);
	if (!pMyView->strCadcomFilePath.IsEmpty())
	{
		pMyView->m_pListBox->AddString(pMyView->strCadcomFilePath);
	}
	if(pMyView->m_pListBox->GetCount() > 1 && 
		pMyView->m_pListBox->SetTopIndex(pMyView->m_pListBox->GetCount() -1))
	{
		MessageBox("Set scroll bar error!");
	}
	pMyView = NULL;
	delete pMyView;
}

void CMainFrame::OnSelectIpdbg() 
{
	CString strFilter = "文本文件(*.txt; *.log)| *.txt; *.log||";
	CLogFileFilterView *pMyView = (CLogFileFilterView*)GetActiveView();
	pMyView->strIpdbgFilePath = CLogFileOperation::OpenLogFile(strFilter);
	if (!pMyView->strIpdbgFilePath.IsEmpty())
	{
		pMyView->m_pListBox->AddString(pMyView->strIpdbgFilePath);
	}
	if(pMyView->m_pListBox->GetCount() > 1 && 
		pMyView->m_pListBox->SetTopIndex(pMyView->m_pListBox->GetCount() -1))
	{
		MessageBox("Set scroll bar error!");
	}
	pMyView = NULL;
	delete pMyView;
}

void CMainFrame::OnCodebit() 
{
	CLogFileFilterView *pMyView = (CLogFileFilterView*)GetActiveView();
	if(pMyView->strIpdbgFilePath.IsEmpty())
	{
		MessageBox("请选择IPDBG日志文件");
		return;
	}
	CCodeBitDlg dlg;
	dlg.DoModal();
	pMyView = NULL;
	delete pMyView;
}

void CMainFrame::OnTrainnumwin()
{
	CLogFileFilterView *pMyView = (CLogFileFilterView*)GetActiveView();
	if(pMyView->strIpdbgFilePath.IsEmpty())
	{
		MessageBox("请选择IPDBG日志文件");
		return;
	}
	CTrainNumWin dlg;
	dlg.DoModal();
	pMyView = NULL;
	delete pMyView;
}

void CMainFrame::OnPoorsperation()
{
	CLogFileFilterView *pMyView = (CLogFileFilterView*)GetActiveView();
	if(pMyView->strIpdbgFilePath.IsEmpty())
	{
		MessageBox("请选择IPDBG日志文件");
		return;
	}
	CPoorSperation dlg;
	dlg.DoModal();
	pMyView = NULL;
	delete pMyView;
}

void CMainFrame::OnCounter()
{
	CLogFileFilterView *pMyView = (CLogFileFilterView*)GetActiveView();
	if(pMyView->strIpdbgFilePath.IsEmpty())
	{
		MessageBox("请选择IPDBG日志文件");
		return;
	}
	CCounter dlg;
	dlg.DoModal();
	pMyView = NULL;
	delete pMyView;
}

void CMainFrame::OnMasterconnection()
{
	// TODO: 在此添加命令处理程序代码
	CLogFileFilterView *pMyView = (CLogFileFilterView*)GetActiveView();
	if(pMyView->strIpdbgFilePath.IsEmpty())
	{
		MessageBox("请选择IPDBG日志文件");
		return;
	}	CMasterConnection dlg;
	dlg.DoModal();
	pMyView = NULL;
	delete pMyView;
}

void CMainFrame::OnChange()
{
	CLogFileFilterView *pMyView = (CLogFileFilterView*)GetActiveView();
	if(pMyView->strIpdbgFilePath.IsEmpty())
	{
		MessageBox("请选择IPDBG日志文件");
		return;
	}
	CFile *pFileIpdbg = new CFile;
	CFileException e;
	int wrongLineNum = 0;
	if(!pFileIpdbg->Open(pMyView->strIpdbgFilePath, CFile::modeRead | CFile::typeBinary))
	{
		TRACE(_T("File could not be opened %d\n"), e.m_cause);
		MessageBox("open file failed");
		return;
	}
	if(!CLogFileOperation::TransformLogFile(pMyView->strIpdbgFilePath, pFileIpdbg, &wrongLineNum))
	{
		char buf[20] = {0};
		sprintf_s(buf, 100, "第%d行转换失败！", wrongLineNum);
		pMyView->m_pListBox->AddString((CString)buf);
	}
	pMyView->m_pListBox->AddString("转换成功");
	if(pMyView->m_pListBox->GetCount() > 1 && 
		pMyView->m_pListBox->SetTopIndex(pMyView->m_pListBox->GetCount() -1))
	{
		MessageBox("Set scroll bar error!");
	}
	pFileIpdbg->Close();
	pMyView = NULL;
	delete pMyView;
	delete pFileIpdbg;
}

void CMainFrame::OnResultconserve()
{
	CLogFileFilterView *pMyView = (CLogFileFilterView*)GetActiveView();
	CFile* pChangeFile = new CFile;
	CFileException e;
	if(pMyView->m_pListBox->GetCount() == 0)
	{
		MessageBox("查询结果为空，保存失败!");
		return;
	}
	char tmp[100] = {0};
	CString strLogName;
	CString strFilter = "文本文件(*.LOG)| *.LOG||";
	CFileDialog filedlg(
		false,
		".LOG",
		_T("查询结果"),
		OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		strFilter,
		NULL);
	if(filedlg.DoModal() == IDOK)
	{
		pMyView->m_pListBox->AddString("保存查询结果");
		if(!pChangeFile->Open(filedlg.GetPathName(), CFile::modeCreate|CFile::modeWrite, &e))
		{
			TRACE(_T("File could not be opened %d\n"), e.m_cause);
			MessageBox("open file failed");
			return;
		}
		int countOfClientListBox = pMyView->m_pListBox->GetCount();
		int iQueryResultRowCount = 0;
		CString strClientListBoxQueryResultRow;
		countOfClientListBox=pMyView->m_pListBox->GetCount();
		for(iQueryResultRowCount = 0; iQueryResultRowCount < countOfClientListBox; iQueryResultRowCount++)
		{
			pMyView->m_pListBox->GetText(iQueryResultRowCount,strClientListBoxQueryResultRow);
			if(strClientListBoxQueryResultRow.Find("\n") < 0)
			{
				strClientListBoxQueryResultRow += "\n";
			}
			pChangeFile->Write(strClientListBoxQueryResultRow, strlen(strClientListBoxQueryResultRow));
		}
		pChangeFile->Close();
	}
	if(pMyView->m_pListBox->GetCount() > 1 && 
		pMyView->m_pListBox->SetTopIndex(pMyView->m_pListBox->GetCount() -1))
	{
		MessageBox("Set scroll bar error!");
	}
	delete pChangeFile;
	pMyView = NULL;
	delete pMyView;
}

void CMainFrame::OnClose()
{
	CFrameWnd::OnClose();
}

void CMainFrame::OnCleanscreen()
{
	CLogFileFilterView *pMyView = (CLogFileFilterView*)GetActiveView();
	pMyView->m_pListBox->ResetContent();
	pMyView = NULL;
	delete pMyView;
}

