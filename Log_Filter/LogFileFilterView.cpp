// LogFileFilterView.cpp : implementation of the CLogFileFilterView class
//

#include "stdafx.h"
#include "LogFileFilter.h"

#include "LogFileFilterDoc.h"
#include "LogFileFilterView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CLogFileFilterView

IMPLEMENT_DYNCREATE(CLogFileFilterView, CEditView)

BEGIN_MESSAGE_MAP(CLogFileFilterView, CEditView)
	//{{AFX_MSG_MAP(CLogFileFilterView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogFileFilterView construction/destruction

CLogFileFilterView::CLogFileFilterView()
{
	// TODO: add construction code here
	//pfileIPDBG = NULL;	
	//pfileCADCOM = NULL;
}

CLogFileFilterView::~CLogFileFilterView()
{
}

BOOL CLogFileFilterView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLogFileFilterView drawing

void CLogFileFilterView::OnDraw(CDC* pDC)
{
	CLogFileFilterDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
	
}

/////////////////////////////////////////////////////////////////////////////
// CLogFileFilterView printing

BOOL CLogFileFilterView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLogFileFilterView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLogFileFilterView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CLogFileFilterView diagnostics

#ifdef _DEBUG
void CLogFileFilterView::AssertValid() const
{
	CView::AssertValid();
}

void CLogFileFilterView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLogFileFilterDoc* CLogFileFilterView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLogFileFilterDoc)));
	return (CLogFileFilterDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLogFileFilterView message handlers


void CLogFileFilterView::OnInitialUpdate()
{
	CEditView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	m_pListBox = new CColorListBox();
	GetClientRect(&m_rect);
	m_pListBox->Create(WS_CHILD|WS_BORDER|WS_VISIBLE|WS_VSCROLL|WS_HSCROLL
		|LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED | LBS_HASSTRINGS | LBS_MULTIPLESEL, 
		m_rect,  this, IDC_LISTBOX_QUERY_RES);
	
}


int CLogFileFilterView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CEditView::OnCreate(lpCreateStruct) == -1)
		return -1;
	ModifyStyleEx(0, WS_EX_COMPOSITED);		// 查询完结果在刷新
	// TODO:  在此添加您专用的创建代码
	return 0;
}


void CLogFileFilterView::OnSize(UINT nType, int cx, int cy)
{
	CEditView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CColorListBox *pListBox = (CColorListBox*)GetDlgItem(IDC_LISTBOX_QUERY_RES);
	if(pListBox)
	{
		pListBox ->SetWindowPos(NULL,0,0,cx,cy,SWP_SHOWWINDOW);//最后一个宏参数不能是SWP_NOMOVE和SWP_NOSIZE
	}
}

