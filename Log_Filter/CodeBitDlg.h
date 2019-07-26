#if !defined(AFX_CODEBITDLG_H__8F67FFDF_781B_4C46_A0DA_5FC914A9302E__INCLUDED_)
#define AFX_CODEBITDLG_H__8F67FFDF_781B_4C46_A0DA_5FC914A9302E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CodeBitDlg.h : header file
//
#include <map>
using namespace std; 
/////////////////////////////////////////////////////////////////////////////
// CCodeBitDlg dialog

class LogFileFilterView;
struct CODEBITINFO
{	
	CString CodeBitName;	// 码位的名称
	char CodeBitStatus;		// 码位的状态（0或1）
};

class CCodeBitDlg : public CDialog
{
// Construction
public:
	CCodeBitDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCodeBitDlg();

// Dialog Data
	//{{AFX_DATA(CCodeBitDlg)
	enum { IDD = IDD_CODEBIT };
	CListBox	m_ExpressCodeBitsSelectedList;
	CListBox	m_ExpressCodeBitsList;
	CListBox	m_ControlCodeBitsSelectedList;
	CListBox	m_ControlCodeBitsList;
	CDateTimeCtrl	m_StartQueryTime_CDateTimeCtrl;
	CDateTimeCtrl	m_EndQueryTime_CDateTimeCtrl;
	CTime	m_StartQueryTime_CTime;
	CTime	m_EndQueryTime_CTime;
	CEdit	m_LogTimeWidth;
	///////////////
	int	m_Flag_SelectAllOrDeleteSelected_ExpressCodeBits;
	int	m_Flag_SelectAllOrDeleteSelected_ControlCodeBits;
	int	m_Flag_LoadCadcomFile;	// 是否加载CADCOM文件
	int	m_CountOfControlCodeBitsSelectedList;
	int	m_CountOfExpressCodeBitsSelectedList;
	//////////
	map<int,CODEBITINFO> m_mapRecordExpressCodeBitsInfo;
	map<int,CODEBITINFO>::iterator m_iterExpressCodeBits;
	map<int,CODEBITINFO> m_mapRecordControlCodeBitsInfo;
	map<int,CODEBITINFO>::iterator m_iterControlCodeBits;
	//}}AFX_DATA
	CFile* pFileIpdbg;
	CStdioFile* pFileCadcom;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCodeBitDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//CLogFileFilterView *pMyView;

	// Generated message map functions
	//{{AFX_MSG(CCodeBitDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelectAllExpressCodeBits();
	afx_msg void OnDeleteSelectedExpressCodeBits();
	afx_msg void OnSelectAllControlCodeBits();
	afx_msg void OnDeleteSelectedControlCodeBits();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedDecreaseControlCodeBits();
	afx_msg void OnClickedIncreaseControlCodeBits();
	afx_msg void OnClickedDecreaseExpressCodeBits();
	afx_msg void OnClickedIncreaseExpressCodeBits();
	afx_msg void OnDatetimechangeQuerytimestart(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDatetimechangeQuerytimestop(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickedCheck();
	afx_msg void OnClickedCancel();
	void GetQueryCodeBit();
	void GetCodeBitMsg(CFile& rFile);
	int DisplayTheNumOfCodeBitsWithCADCOM(CStdioFile &rFile);
	int DisplayTheNumOfCodeBitsWithoutCADCOM(CFile &rFileNonCadcom);
	void DisplayFileReadCountInOneLine(int numFixedLine, int count);
	
	int HexStrToInt(char strdata, int bufSize ,char *BinaryArray);	// 字符数据转整形
	int GetBitValue(char* Ndata, map<int, CODEBITINFO> Nmap, map<int, CODEBITINFO>::iterator Niterator, 
		map<int, CODEBITINFO> *mapTmp, map<int, CODEBITINFO>::iterator iterTmp, int num, CString strTime);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CODEBITDLG_H__8F67FFDF_781B_4C46_A0DA_5FC914A9302E__INCLUDED_)
