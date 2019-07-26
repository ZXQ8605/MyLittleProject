// PoorSperation.cpp : 实现文件
//

#include "stdafx.h"
#include "LogFileFilter.h"
#include "PoorSperation.h"
#include "afxdialogex.h"
#include "LogFile.h"
#include "LogHandle.h"
#include "MainFrm.h"
#include "LogFileFilterDoc.h"
#include "LogFileFilterView.h"


// CPoorSperation 对话框

IMPLEMENT_DYNAMIC(CPoorSperation, CDialog)

CPoorSperation::CPoorSperation(CWnd* pParent /*=NULL*/)
	: CDialog(CPoorSperation::IDD, pParent)
{
	pFileIpdbg = new CFile;
}

CPoorSperation::~CPoorSperation()
{
	delete pFileIpdbg;
}

void CPoorSperation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LOGTIMESPANPOOR, m_LogTimeSpanPoor);
	DDX_Control(pDX, IDC_QUERYTIMESTARTPOOR, m_PoorQueryTimeStart);
	DDX_Control(pDX, IDC_QUERYTIMESTOPPOOR, m_PoorQueryTimeStop);
}


BEGIN_MESSAGE_MAP(CPoorSperation, CDialog)
	ON_BN_CLICKED(IDC_CHECKPOOR, &CPoorSperation::OnClickedCheckpoor)
	ON_BN_CLICKED(IDC_CANCELPOOR, &CPoorSperation::OnClickedCancelpoor)
END_MESSAGE_MAP()


// CPoorSperation 消息处理程序


BOOL CPoorSperation::OnInitDialog()
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
	int resSetTime = CLogFileOperation::SetLogTimeWidthAndDefaultQueryTime(*pFileIpdbg, m_LogTimeSpanPoor, m_PoorQueryTimeStart, m_PoorQueryTimeStop);
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

void CPoorSperation::OnClickedCheckpoor()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
	CMainFrame *pMain = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	CLogFileFilterView *pView = (CLogFileFilterView *)pMain->GetActiveView();
	CLogFileOperation::GetQueryTimeWin(m_PoorQueryTimeStart, m_PoorQueryTimeStop, m_TimeStart, m_TimeStop);
	if(m_TimeStart > m_TimeStop)
	{
		MessageBox("起始时间大于结束时间，请重新设置");
		return;
	}
	pView->m_pListBox->AddString("分析分路不良信息:");
	GetQueryResult();
	pMain = NULL;
	pView = NULL;
	delete pView;
	delete pMain;
}

void CPoorSperation::OnClickedCancelpoor()
{
	CDialog::OnCancel();
}

void CPoorSperation::GetQueryResult(void)
{
	CMainFrame *pMain = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	CLogFileFilterView *pMyView = (CLogFileFilterView *)pMain->GetActiveView();
	//pMyView->pfileIPDBG->Open(pMyView->strIpdbgFilePath, CFile::modeRead | CFile::typeBinary);
	REPLAY_DATA dataReplay;
	struct BADSHUNTINFO BadShuntInfoTmp;
	char strType[4] = {0}, strTypeMap[4] = {0}, bufConfirmInfo[10] = {0};
	int nNum = 0;
	CString strQueryRes, strConfirmInfo, strPoorType;
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
		int nFirstWin = strJudge.Find("[RPYBAD]");
		char bufTmpTime[100] = {0};
		CString strTmpTime, strStationContentTmp;
		CLogFileOperation::ChangeToTime(dataReplay.m_time, bufTmpTime, 100);
		strTmpTime.Format("%s", bufTmpTime);
		char strTmp[100] = {0};
		BOOL m_BADflag = FALSE;
		if(logTime < m_TimeStart){continue;}
		if (logTime > m_TimeStop){break;}
		if(strJudge.Find("[USER]: create queue,USER.queue_handle") >= 0)
		{
			if(!mapPoorSperation.empty())
			{
				mapPoorSperation.clear();
			}
			nNum = 0;
			CString strResatrtRes = strTmpTime + "时，软件重启";
			pMyView->m_pListBox->AddString(strResatrtRes);
		}
		if(nFirstWin >= 0)
		{
			nNum++;
			strData = strJudge.Mid(nFirstWin + strlen("[RPYTID]"), 
				dataReplay.m_len - nFirstWin - strlen("[RPYTID]"));
			strStationNum = strData.Left(4);	// 4字节站号
			strStationEquipmentType = strData.Mid(4, 4);	// 4字节站场设备类型
			strStationEquipmentID = strData.Mid(8, 4);	// 4字节站场设备ID
			strPoorSperationType = strData.Mid(12, 4);	// 4字节分路不良类型
			strPoorSperationConfirm = strData.Mid(16, 4);	// 4字节确认信息
			CLogFileOperation::ChangeToTime(dataReplay.m_time, bufTmpTime, 100);
			strTmpTime.Format("%s", bufTmpTime);
			sprintf_s(strTmp, sizeof(strTmp), "%d-%d-%d", strtol(strStationNum, NULL, 16), 
			strtol(strStationEquipmentType, NULL, 16), strtol(strStationEquipmentID, NULL, 16));
			//mapPoorSperation中是否有该设备的记录
			iter = mapPoorSperation.find((CString)strTmp);
			//int ret = strPoorSperationConfirm.Replace("\r\n", "");
			mapNum = strtol(strPoorSperationType, NULL, 16);
			if(mapPoorSperation.empty())
			{
				strStationContentTmp = "新增分路不良";
				BadShuntInfoTmp.badShuntType = mapNum;
				BadShuntInfoTmp.badShuntConfirm = GetBadShuntConfirmInfo(strPoorSperationConfirm);
				mapPoorSperation[(CString)strTmp] = BadShuntInfoTmp;
				strPoorType = JudgeBADType(mapNum);
				if(strPoorType.IsEmpty())
				{
					MessageBox("识别分录不良类型失败！");
				}
				strQueryRes = strTmpTime + " 设备(" + (CString)strTmp + ")" +
					strStationContentTmp + strPoorType + BadShuntInfoTmp.badShuntConfirm;
			}
			else
			{	// mapPoorSperation存在该设备的记录时
				if(iter != mapPoorSperation.end())
				{
					if (iter->second.badShuntType != 0 && !iter->second.badShuntConfirm.IsEmpty() && mapNum == 0)
					{
						strStationContentTmp = "删除分路不良";	// BADSHUNTINFO不为空，但分路不良类型为零，故为删除分路不良
						iter->second.badShuntType = mapNum;
						iter->second.badShuntConfirm = GetBadShuntConfirmInfo(strPoorSperationConfirm);	// badShuntConfirm置为空
					}
					else if (iter->second.badShuntType != 0 && mapNum != 0 &&
						iter->second.badShuntType != mapNum)	// 不为零，且不相等
					{
						strStationContentTmp = "变更分路不良";
						iter->second.badShuntType = mapNum;
						iter->second.badShuntConfirm = GetBadShuntConfirmInfo(strPoorSperationConfirm);
					}
					else if (iter->second.badShuntType != 0 && mapNum != 0 && iter->second.badShuntType == mapNum && 
						iter->second.badShuntConfirm.Compare(GetBadShuntConfirmInfo(strPoorSperationConfirm)))
					{	// 确认信息不同，将确认信息重新赋值
						iter->second.badShuntConfirm = GetBadShuntConfirmInfo(strPoorSperationConfirm);
					}
					else if (iter->second.badShuntType == 0 && !iter->second.badShuntConfirm.IsEmpty()
						&& iter->second.badShuntConfirm.IsEmpty() && mapNum != 0)
					{	// 存在该设备，但之前的分路不良信息已删除，但保留了该设备的记录,此时认为是新增分路不良
						strStationContentTmp = "新增分路不良";
						iter->second.badShuntType = mapNum;
						iter->second.badShuntConfirm = GetBadShuntConfirmInfo(strPoorSperationConfirm);
					}
					else if (iter->second.badShuntType == mapNum && iter->second.badShuntConfirm.Compare(GetBadShuntConfirmInfo(strPoorSperationConfirm)))
					{	// 重复发送分路不良信息时,跳过该条记录的显示
						continue;
					}
					strPoorType = JudgeBADType(mapNum);
					strQueryRes = strTmpTime + " 设备(" + (CString)strTmp + ")" +
						strStationContentTmp + strPoorType + iter->second.badShuntConfirm;

				}
				else
				{	// map不为空，但没有该设备,在map中添加该设备的信息
					strStationContentTmp = "新增分路不良";
					BadShuntInfoTmp.badShuntType = mapNum;
					BadShuntInfoTmp.badShuntConfirm = GetBadShuntConfirmInfo(strPoorSperationConfirm);
					mapPoorSperation[(CString)strTmp] = BadShuntInfoTmp;
					/*if(!JudgeBADType(mapNum, strPoorType))
					{
						MessageBox("识别分录不良类型失败！");
					}*/
					strPoorType = JudgeBADType(mapNum);
					strQueryRes = strTmpTime + " 设备(" + (CString)strTmp + ")" +
						strStationContentTmp + strPoorType + BadShuntInfoTmp.badShuntConfirm;
				}
			}
			if (!strStationContentTmp.IsEmpty())
			{
				pMyView->m_pListBox->AddString(strQueryRes);
			}
		}
	}
	if(nNum == 0)
	{
		CString strNoQueryRes = m_TimeStart.Format("%Y-%m-%d %H:%M:%S") + "--" +
			m_TimeStop.Format("%Y-%m-%d %H:%M:%S") + " 无分路不良信息";
		pMyView->m_pListBox->AddString(strNoQueryRes);
	}
	if(pMyView->m_pListBox->GetCount() > 1 && 
		pMyView->m_pListBox->SetTopIndex(pMyView->m_pListBox->GetCount() -1))
	{
		MessageBox("Set scroll bar error!");
	}
	//fseek(pMyView->pfileIPDBG, 0, SEEK_SET);
	//pMyView->pfileIPDBG->Close();
	pFileIpdbg->SeekToBegin();
	pMain = NULL;
	pMyView = NULL;
	delete pMyView;
	delete pMain;
}
CString CPoorSperation::JudgeBADType(int num)
{
	CString str;
	if (num <= 0)
	{
		str.Empty();
	}
	if(num >= 8)
	{
		num -= 8;
		str += "(反位)";
	}
	if(num >= 4)
	{
		num -= 4;
		str += "(定位)";
	}
	if(num >= 2)
	{
		num -= 2;
		str += "(岔前)";
	}
	if(num >= 1)
	{
		num -= 1;
		str += "(区段)";
	}
	return str;
}

CString CPoorSperation::GetBadShuntConfirmInfo(CString strBANDShuntconfirmInfo)
{
	if (strBANDShuntconfirmInfo.IsEmpty())
	{
		//return false;
	}
	CString str;
	if(strtol(strBANDShuntconfirmInfo, NULL, 16) == 0)
	{
		str = "(未确认)";
	}
	else if(strtol(strBANDShuntconfirmInfo, NULL, 16) == 1)
	{
		str = "(已确认)";
	}
	return str;
}
