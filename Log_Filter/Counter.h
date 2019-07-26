#pragma once
#include <map>
using namespace std;

// CCounter 对话框
class LogFileFilterView;
struct COUNTERINFO
{
	CString counterYearMonthDay;	// 记录的时间（年月日）
	int counterNum;
};

class CCounter : public CDialog
{
	DECLARE_DYNAMIC(CCounter)

public:
	CCounter(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCounter();

	CTime m_TimeStartCounter, m_TimeStopCounter;
	CString strStationNum, strStationEquipmentType, strStationEquipmentID, 
		strCounterState, strCounterNum;
	CString strJudge, strData;
	CString strCounterResult;
	map<CString,COUNTERINFO> mapCounter;
	map<CString, COUNTERINFO>::iterator iter;
	CFile* pFileIpdbg;

// 对话框数据
	enum { IDD = IDD_COUNTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CEdit m_LogTimeSpanCounter;
	CDateTimeCtrl m_CounterQueryTimeStart;
	CDateTimeCtrl m_CounterQueryTimeStop;
	afx_msg void OnBnClickedCheckcounter();
	afx_msg void OnBnClickedCancelcounter();
	void GetQueryResult(void);
	void DisplayFileReadCountInOneLine(int numFixedLine, int count);
};
