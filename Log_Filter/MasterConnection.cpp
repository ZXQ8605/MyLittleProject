// MasterConnection.cpp : 实现文件
//

#include "stdafx.h"
#include "LogFileFilter.h"
#include "MasterConnection.h"
#include "afxdialogex.h"
#include "LogFile.h"
#include "LogHandle.h"
#include "MainFrm.h"
#include "LogFileFilterDoc.h"
#include "LogFileFilterView.h"


// CMasterConnection 对话框

IMPLEMENT_DYNAMIC(CMasterConnection, CDialog)

CMasterConnection::CMasterConnection(CWnd* pParent /*=NULL*/)
	: CDialog(CMasterConnection::IDD, pParent)
{
	pFileIpdbg = new CFile;
}

CMasterConnection::~CMasterConnection()
{
	delete pFileIpdbg;
}

void CMasterConnection::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LOGTIMESPANMASTER, m_LogTimeSpanMaster);
	DDX_Control(pDX, IDC_QUERYTIMESTARTMASTER, m_MasterQueryTimeStart);
	DDX_Control(pDX, IDC_QUERYTIMESTOPMASTER, m_MasterQueryTimeStop);
}


BEGIN_MESSAGE_MAP(CMasterConnection, CDialog)
	ON_BN_CLICKED(IDC_CHECKMASTER, &CMasterConnection::OnBnClickedCheckmaster)
	ON_BN_CLICKED(IDC_CANCELMASTER, &CMasterConnection::OnBnClickedCancelmaster)
END_MESSAGE_MAP()


// CMasterConnection 消息处理程序


BOOL CMasterConnection::OnInitDialog()
{
	CDialog::OnInitDialog();
	CMainFrame *pMain = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	CLogFileFilterView *pView = (CLogFileFilterView *)pMain->GetActiveView();
	if(pView->strIpdbgFilePath.IsEmpty())
	{
		MessageBox("open file failed");
		return FALSE;
	}
	pFileIpdbg->Open(pView->strIpdbgFilePath, CFile::modeRead | CFile::typeBinary);
	int resSetTime = CLogFileOperation::SetLogTimeWidthAndDefaultQueryTime(*pFileIpdbg, m_LogTimeSpanMaster, m_MasterQueryTimeStart, m_MasterQueryTimeStop);
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
	// TODO:  在此添加额外的初始化
	pMain = NULL;
	pView = NULL;
	delete pView;
	delete pMain;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CMasterConnection::OnBnClickedCheckmaster()
{
	CDialog::OnOK();
	CMainFrame *pMain = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	CLogFileFilterView *pView = (CLogFileFilterView *)pMain->GetActiveView();
	CLogFileOperation::GetQueryTimeWin(m_MasterQueryTimeStart, m_MasterQueryTimeStop, m_TimeStartMaster, m_TimeStopMaster);
	if(m_TimeStartMaster > m_TimeStopMaster)
	{
		MessageBox("起始时间大于结束时间，请重新设置");
		return;
	}
	pView->m_pListBox->AddString("分析主连接信息:");
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


void CMasterConnection::OnBnClickedCancelmaster()
{
	CDialog::OnCancel(); 
}


void CMasterConnection::GetQueryResult(void)
{
	CMainFrame *pMain = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	CLogFileFilterView *pMyView = (CLogFileFilterView *)pMain->GetActiveView();
	///pMyView->pfileIPDBG->Open(pMyView->strIpdbgFilePath, CFile::modeRead | CFile::typeBinary);
	REPLAY_DATA dataReplay;
	CString strJudge, strData;
	CString strMasterResult;
	int nNum = 0;
	while(pFileIpdbg->GetPosition() < pFileIpdbg->GetLength())
	{
		int readSize = CReadLogFile::ReadReplayDataFromLog(*pFileIpdbg, dataReplay);
		if (readSize <= 0)
		{
			MessageBox("Read log record error! Please Confirm that the record is complete");
			return;
		}
		strJudge = (CString)dataReplay.m_data;
		strData = strJudge;
		strJudge.MakeLower();
		CTime logTime(dataReplay.m_time);
		char bufTmpTime[100] = {0};
		CString strTmpTime, strTmpData;
		CLogFileOperation::ChangeToTime(dataReplay.m_time, bufTmpTime, 100);
		strTmpTime.Format("%s", bufTmpTime);
		if(logTime < m_TimeStartMaster)
		{
			continue;
		}
		if (logTime > m_TimeStopMaster)
		{
			break;
		}
		if(strData.Find("[USER]: create queue,USER.queue_handle") >= 0)
		{
			strMasterResult =  strTmpTime + "时，软件重启";
			pMyView->m_pListBox->AddString(strMasterResult);
		}
		else if(strJudge.Find("master") != -1)
		{
			strTmpData = strData.Mid(strlen("[IP_DBG 2018-07-24  14:51:09]"));
			strMasterResult = strTmpTime + strTmpData;
			pMyView->m_pListBox->AddString(strMasterResult);
			nNum++;
		}
	}
	if(nNum == 0)
	{
		CString strQueryRes = m_TimeStartMaster.Format("%Y-%m-%d %H:%M:%S") + "--" 
			+ m_TimeStopMaster.Format("%Y-%m-%d %H:%M:%S") + " 无主连接信息";
		pMyView->m_pListBox->AddString(strQueryRes);
	}
	if(pMyView->m_pListBox->GetCount() > 1 && 
		pMyView->m_pListBox->SetTopIndex(pMyView->m_pListBox->GetCount() -1))
	{
		MessageBox("Set scroll bar error!");
	}
	//fseek(pView->pfileIPDBG, 0, SEEK_SET);
	//pMyView->pfileIPDBG->Close();
	pMain = NULL;
	pMyView = NULL;
	delete pMyView;
	delete pMain;
}
