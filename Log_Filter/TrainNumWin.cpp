// TrainNumWin.cpp : 实现文件
//
#include "stdafx.h"
#include "LogFileFilter.h"
#include "TrainNumWin.h"
#include "afxdialogex.h"
#include "LogHandle.h"
#include "MainFrm.h"
#include "LogFileFilterDoc.h"
#include "LogFileFilterView.h"


// CTrainNumWin 对话框

IMPLEMENT_DYNAMIC(CTrainNumWin, CDialog)

CTrainNumWin::CTrainNumWin(CWnd* pParent /*=NULL*/)
	: CDialog(CTrainNumWin::IDD, pParent)
{
	pFileIpdbg = new CFile;
}

CTrainNumWin::~CTrainNumWin()
{
	delete pFileIpdbg;
}

void CTrainNumWin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LOGTIMESPANWIN, m_LogTimeSpanWin);
	DDX_Control(pDX, IDC_QUERYTIMESTARTWIN, m_WinQueryTimeStart);
	DDX_Control(pDX, IDC_QUERYTIMESTOPWIN, m_WinQueryTimeStop);
}


BEGIN_MESSAGE_MAP(CTrainNumWin, CDialog)
	//ON_COMMAND(ID_TRAINNUMWIN, &CTrainNumWin::OnTrainnumwin)
	ON_BN_CLICKED(IDC_CHECK, &CTrainNumWin::OnClickedCheck)
	ON_COMMAND(IDC_CANCEL, &CTrainNumWin::OnCancel)
END_MESSAGE_MAP()


// CTrainNumWin 消息处理程序


BOOL CTrainNumWin::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CMainFrame *pMain = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	CLogFileFilterView *pView = (CLogFileFilterView *)pMain->GetActiveView();
	if(pView->strIpdbgFilePath.IsEmpty())
	{
		MessageBox("open file failed");
	}
	pFileIpdbg->Open(pView->strIpdbgFilePath, CFile::modeRead | CFile::typeBinary);
	int resSetTime = CLogFileOperation::SetLogTimeWidthAndDefaultQueryTime(*pFileIpdbg, m_LogTimeSpanWin, m_WinQueryTimeStart, m_WinQueryTimeStop);
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

void CTrainNumWin::OnClickedCheck()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
	CMainFrame *pMain = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	CLogFileFilterView *pView = (CLogFileFilterView *)pMain->GetActiveView();
	
	CLogFileOperation::GetQueryTimeWin(m_WinQueryTimeStart, m_WinQueryTimeStop, m_TimeStartWin, m_TimeStopWin);
	if(m_TimeStartWin > m_TimeStopWin)
	{
		MessageBox("起始时间大于结束时间，请重新设置");
		return;
	}
	pView->m_pListBox->AddString("分析车次窗信息:");
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


void CTrainNumWin::OnCancel()
{
	// TODO: 在此添加命令处理程序代码
	CDialog::OnCancel(); 
}


void CTrainNumWin::GetQueryResult(void)
{
	CMainFrame *pMain = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	CLogFileFilterView *pMyView = (CLogFileFilterView *)pMain->GetActiveView();
	//pMyView->pfileIPDBG->Open(pMyView->strIpdbgFilePath, CFile::modeRead | CFile::typeBinary);
	REPLAY_DATA dataReplay;
	int nNum = 0;
	//while(!feof(pView->pfileIPDBG))
	while(pFileIpdbg->GetPosition() < pFileIpdbg->GetLength())
	{
		int readSize = CReadLogFile::ReadReplayDataFromLog(*pFileIpdbg, dataReplay);
		if (readSize <= 0)
		{
			MessageBox("Read log record error! Please Confirm that the record is complete");
			return;
		}
		CTime logTime(dataReplay.m_time);
		strJudge = (CString)dataReplay.m_data;
		char bufTmpTime[100] = {0};
		int nFirstWin = strJudge.Find("[RPYTID]");
		CString strTmpTime, strStationContentTmp;
		CLogFileOperation::ChangeToTime(dataReplay.m_time, bufTmpTime, 100);
		strTmpTime.Format("%s", bufTmpTime);
		char strTmp[100];
		if(logTime < m_TimeStartWin)
		{	// 日志时间小于查询时间时，跳过该条记录去查询后面的记录
			continue;
		}
		if (logTime > m_TimeStopWin)
		{	// 日志时间大于查询时间时，结束while循环
			break;
		}
		if(strJudge.Find("[USER]: create queue,USER.queue_handle") >= 0)
		{
			if(!mapStationNumWin.empty())
			{
				mapStationNumWin.clear();
			}
			strQueryResult = strTmpTime + "时，软件重启";
			pMyView->m_pListBox->AddString(strQueryResult);
		}
		if(nFirstWin >= 0)
		{
			strData = strJudge.Mid(nFirstWin + strlen("[RPYTID]"), 
				dataReplay.m_len - nFirstWin - strlen("[RPYTID]"));
			strStationNum = strData.Left(4);//4字节站号
			strStationEquipmentType = strData.Mid(12, 4);//跳过4字节0与4字节预留,读取4字节站场设备类型
			strStationEquipmentID = strData.Mid(16, 4);//4字节站场设备ID
			strStationEquipmentStatus = strData.Mid(20, 8);//8字节站场设备状态
			strStationContent = strData.Mid(strData.Find('[')+1, strData.Find(']')-strData.Find('[')-1);//车次窗内容
			CLogFileOperation::ChangeToTime(dataReplay.m_time, bufTmpTime, 100);
			strTmpTime.Format("%s", bufTmpTime);
			sprintf_s(strTmp, sizeof(strTmp), "%d-%d-%d", strtol(strStationNum, NULL, 16), 
				strtol(strStationEquipmentType, NULL, 16), strtol(strStationEquipmentID, NULL, 16));
			//mapStationNumWin是否有该设备的记录
			iter = mapStationNumWin.find((CString)strTmp);
			int ret = strStationContent.Replace("\r\n", "");
			if(mapStationNumWin.empty())
			{
				strStationContentTmp = "新增车次窗:";
				mapStationNumWin[(CString)strTmp] = strStationContent;
			}
			else
			{	// map不为空
				if(iter != mapStationNumWin.end())
				{	// mapStationNumWin中有该设备的记录，此时通过车次窗的内容来判断当前为修改车次窗，新增车次窗，还是删除车次窗
					if ((iter->second.IsEmpty()) &&
 						!strStationContent.IsEmpty())//车次窗内容从[]==>[停（或其他）]
					{
						strStationContentTmp = "新增车次窗:";
						mapStationNumWin[(CString)strTmp]  = strStationContent;
					}
					else if ((!iter->second.IsEmpty()) &&
						strStationContent.IsEmpty())//车次窗内容从[停（或其他）]==>[])
					{
						strStationContentTmp = "删除车次窗";
						mapStationNumWin[(CString)strTmp] = strStationContent;
					}
					else if((!iter->second.IsEmpty()) &&
						(!strStationContent.IsEmpty()) &&
						(iter->second.Compare(strStationContent) != 0))
					{
						strStationContentTmp = "修改车次窗:";
						mapStationNumWin[(CString)strTmp] = strStationContent;
					}
					else if (!iter->second.Compare(strStationContent))
					{	// 该设备的信息重复打印时，跳过该条记录的显示
						continue;
					}
				}
				else
				{	// map不为空，但没有该设备,直接在map中添加该记录
					strStationContentTmp = "新增车次窗:";
					mapStationNumWin[(CString)strTmp] = strStationContent;
				}
			}
			strQueryResult = strTmpTime + " 设备(" + (CString)strTmp + ")" +
				strStationContentTmp + strStationContent;
			pMyView->m_pListBox->AddString(strQueryResult);
			nNum++;
		}
	}
	if(nNum == 0)
	{
		CString strNoQueryReult = m_TimeStartWin.Format("%Y-%m-%d %H:%M:%S") + "--" + 
			m_TimeStopWin.Format("%Y-%m-%d %H:%M:%S") + " 无车次窗信息";
		pMyView->m_pListBox->AddString(strNoQueryReult);
	}
	if(pMyView->m_pListBox->GetCount() > 1 && 
		pMyView->m_pListBox->SetTopIndex(pMyView->m_pListBox->GetCount() -1))
	{
		MessageBox("Set scroll bar error!");
	}
	pMain = NULL;
	pMyView = NULL;
	delete pMyView;
	delete pMain;
}
