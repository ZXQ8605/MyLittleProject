// Counter.cpp : 实现文件
//

#include "stdafx.h"
#include "LogFileFilter.h"
#include "Counter.h"
#include "stdafx.h"
#include "LogFile.h"
#include "LogHandle.h"
#include "MainFrm.h"
#include "LogFileFilterDoc.h"
#include "LogFileFilterView.h"

// CCounter 对话框

IMPLEMENT_DYNAMIC(CCounter, CDialog)

CCounter::CCounter(CWnd* pParent /*=NULL*/)
	: CDialog(CCounter::IDD, pParent)
{
	pFileIpdbg = new CFile;
}

CCounter::~CCounter()
{
	delete pFileIpdbg;
}

void CCounter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LOGTIMESPANCOUNTER, m_LogTimeSpanCounter);
	DDX_Control(pDX, IDC_QUERYTIMESTARTCOUNTER, m_CounterQueryTimeStart);
	DDX_Control(pDX, IDC_QUERYTIMESTOPCOUNTER, m_CounterQueryTimeStop);
}

BEGIN_MESSAGE_MAP(CCounter, CDialog)
	ON_BN_CLICKED(IDC_CHECKCOUNTER, &CCounter::OnBnClickedCheckcounter)
	ON_BN_CLICKED(IDC_CANCELCOUNTER, &CCounter::OnBnClickedCancelcounter)
END_MESSAGE_MAP()


// CCounter 消息处理程序



BOOL CCounter::OnInitDialog()
{
	CDialog::OnInitDialog();
	// TODO:  在此添加额外的初始化
	CMainFrame *pMain = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	CLogFileFilterView *pView = (CLogFileFilterView *)pMain->GetActiveView();
	if(pView->strIpdbgFilePath.IsEmpty())
	{
		MessageBox("open file failed");
		return FALSE;
	}
	pFileIpdbg->Open(pView->strIpdbgFilePath, CFile::modeRead | CFile::typeBinary);
	int resSetTime = CLogFileOperation::SetLogTimeWidthAndDefaultQueryTime(*pFileIpdbg, m_LogTimeSpanCounter, m_CounterQueryTimeStart, m_CounterQueryTimeStop);
	if (!resSetTime)
	{
		if (resSetTime == -1)
		{
			MessageBox("Open file failed!");
		}
		else
		{
			MessageBox("Read file error, Please confirm the record!");
		}
		return FALSE;
	}
	pFileIpdbg->SeekToBegin();
	pMain = NULL;
	pView = NULL;
	delete pView;
	delete pMain;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CCounter::OnBnClickedCheckcounter()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
	CMainFrame *pMain = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	CLogFileFilterView *pView = (CLogFileFilterView *)pMain->GetActiveView();

	CLogFileOperation::GetQueryTimeWin(m_CounterQueryTimeStart, m_CounterQueryTimeStop, m_TimeStartCounter, m_TimeStopCounter);
	if(m_TimeStartCounter > m_TimeStopCounter)
	{
		MessageBox("起始时间大于结束时间，请重新设置");
		return;
	}
	pView->m_pListBox->AddString("分析计数器信息:");
	//根据查询时间查询结果
	GetQueryResult();
	if(pView->m_pListBox->GetCount() > 1 &&
		pView->m_pListBox->SetTopIndex(pView->m_pListBox->GetCount() -1))
	{
		MessageBox("Set scroll bar error!");
	}
	pMain = NULL;
	pView = NULL;
	delete pView;
	delete pMain;
}

void CCounter::OnBnClickedCancelcounter()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}

void CCounter::GetQueryResult(void)
{
	CMainFrame *pMain = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	CLogFileFilterView *pMyView = (CLogFileFilterView *)pMain->GetActiveView();
	REPLAY_DATA dataReplay;
	COUNTERINFO counterDateAndNum;
	char strType[4] = {0};
	char strTypeMap[4] = {0};
	int mapNum = 0;
	int nNum = 0;
	int NumOfRowsRead = 0;
	int NumFixedLine = pMyView->m_pListBox->GetCount();
	while(pFileIpdbg->GetPosition() < pFileIpdbg->GetLength())
	{
		int readSize = CReadLogFile::ReadReplayDataFromLog(*pFileIpdbg, dataReplay);
		if (readSize <= 0)
		{
			MessageBox("Read log record error! Please Confirm that the record is complete");
			return;
		}
		DisplayFileReadCountInOneLine(NumFixedLine, NumOfRowsRead++);
		CTime logTime(dataReplay.m_time);
		strJudge = (CString)dataReplay.m_data;
		char strTmp[100], bufCounterDate[100];
		CString strPoorType, strTmpCount, strCounterDate;
		int nFirstWin = strJudge.Find("[RPYCNT]");
		CString strStationContentTmp;
		static unsigned long lastRecordTime = 0;
		static int acceptableErrorNum = 0;
		static CString strLastRecord;
		CString strRecordTime = CLogFileOperation::ConvertFromEpochToHumanReadableDate(dataReplay.m_time);
		/************************道岔自动单锁问题测试代码**********************/
		if (dataReplay.m_time - lastRecordTime >= 5)
		{	// 第一条记录给lastRecordTime赋值，但不打印
			//lastRecordTime = dataReplay.m_time;
			pMyView->m_pListBox->AddString(strLastRecord);
			pMyView->m_pListBox->AddString(strJudge);
		}
		lastRecordTime = dataReplay.m_time;
		strLastRecord = strJudge;
		/**********************************************/
		if(logTime < m_TimeStartCounter)
		{
			pMyView->m_pListBox->UpdateWindow();
			continue;
		}
		if ((logTime > m_TimeStopCounter))
		{
			break;
		}
		if(strJudge.Find("[USER]: create queue,USER.queue_handle") >= 0)
		{
			if(!mapCounter.empty())
			{
				mapCounter.clear();
			}
			strCounterResult = strRecordTime + "时，软件重启";
			pMyView->m_pListBox->AddString(strCounterResult);
		}
		if (nFirstWin < 0)
		{
			pMyView->m_pListBox->UpdateWindow();
			continue;
		}
		strData = strJudge.Mid(nFirstWin + strlen("[RPYCNT]"),
			dataReplay.m_len - nFirstWin - strlen("[RPYCNT]"));
		strStationNum = strData.Left(4);
		strStationEquipmentType = strData.Mid(4, 4);
		strStationEquipmentID = strData.Mid(8, 4);
		strCounterState = strData.Mid(12, 4);
		strCounterNum = strData.Mid(16, 4);
		sprintf_s(bufCounterDate, sizeof(bufCounterDate), "%d-%d-%d", logTime.GetYear(), logTime.GetMonth(), logTime.GetDay());
		strCounterDate.Format("%s", bufCounterDate);
		sprintf_s(strTmp, sizeof(strTmp), "%d-%d-%d", strtol(strStationNum, NULL, 16),
			strtol(strStationEquipmentType, NULL, 16), strtol(strStationEquipmentID, NULL, 16));
		// 查询mapCounter是否存在当前设备的记录，有的话返回存放该设备记录的地址，没有的话返回end()
		iter = mapCounter.find((CString)strTmp);
		mapNum = strtol(strCounterNum, NULL, 16);
		if(mapCounter.empty())
		{
			//strStationContentTmp = "";
			counterDateAndNum.counterYearMonthDay = strCounterDate;
			counterDateAndNum.counterNum = mapNum;
			mapCounter[(CString)strTmp] = counterDateAndNum;
		}
		else
		{
			if(iter != mapCounter.end())
			{	// 与前一次计数信息作对比
				if (!iter->second.counterYearMonthDay.Compare(strCounterDate))
				{
					if(mapNum != iter->second.counterNum)
					{
						if (mapNum > iter->second.counterNum)
						{
							strTmpCount.Format("%d", (mapNum - iter->second.counterNum));
							strTmpCount = "(+" + strTmpCount + ")";
						}
						else
						{
							strTmpCount.Format("%d", (iter->second.counterNum - mapNum));
							strTmpCount = "(-" + strTmpCount + ")";
						}
						iter->second.counterNum = mapNum;
					}
					else if(mapNum == iter->second.counterNum)
					{
						continue;
					}
				}
				else
				{
					iter->second.counterYearMonthDay = strCounterDate;
					iter->second.counterNum = mapNum;
				}
			}
			else
			{	// map不为空，但没有该设备,直接在map中添加该记录
				counterDateAndNum.counterYearMonthDay = strCounterDate;
				counterDateAndNum.counterNum = mapNum;
				mapCounter[(CString)strTmp] = counterDateAndNum;
			}
		}
		strCounterNum.Format("%d", mapNum);
		strCounterResult = strRecordTime + " 设备(" + strTmp + ")状态(" + strCounterState +
			") 计数值" +  strCounterNum +  strTmpCount;
		pMyView->m_pListBox->AddString(strCounterResult);
		nNum++;
		pMyView->m_pListBox->UpdateWindow();
	}
	if(nNum == 0)
	{
		CString strNoQueryRes = m_TimeStartCounter.Format("%Y-%m-%d %H:%M:%S") + "--"+
			m_TimeStopCounter.Format("%Y-%m-%d %H:%M:%S") + " 无计数器信息";
		pMyView->m_pListBox->AddString(strNoQueryRes);
	}
	if(pMyView->m_pListBox->GetCount() > 1 &&
		pMyView->m_pListBox->SetTopIndex(pMyView->m_pListBox->GetCount() -1))
	{
		MessageBox("Set scroll bar error!");
	}
	pFileIpdbg->SeekToBegin();
	pMain = NULL;
	pMyView = NULL;
	delete pMyView;
	delete pMain;
}

void CCounter::DisplayFileReadCountInOneLine(int numFixedLine, int count)
{
	CMainFrame *pMain = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	CLogFileFilterView *pView = (CLogFileFilterView *)pMain->GetActiveView();
	CString strFileCount;
	strFileCount.Format("查询计数器信息中:%d", count);
	pView->m_pListBox->DeleteString(numFixedLine-1);
	pView->m_pListBox->InsertString(numFixedLine-1, strFileCount);
	delete pView;
	delete pMain;
	pMain = NULL;
	pView = NULL;
}
