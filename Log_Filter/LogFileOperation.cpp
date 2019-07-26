#include "stdafx.h"
#include "LogHandle.h"
#include "LogFileOperation.h"
#include "LogFileFilterDoc.h"
#include "LogFileFilterView.h"


CLogFileOperation::CLogFileOperation(void)
{
}


CLogFileOperation::~CLogFileOperation(void)
{
}


void SetControlTime(FILE &rFile, CEdit &m_Editcontrol, CDateTimeCtrl &timestart, CDateTimeCtrl &timestop)
{
	REPLAY_DATA dataReplay;
	CString m_LogTimeSpanStr;
	unsigned long LogtimeStart = 0;
	unsigned long LogtimeStop = 0;
	int ret = ReadReplayDataFromLog(rFile, dataReplay);
	LogtimeStart = dataReplay.m_time;
	do
	{
		LogtimeStop = dataReplay.m_time;
		ret = ReadReplayDataFromLog(rFile, dataReplay);
	}while(ret != 0);
	//UNIX时间戳转换为正常时间
	char tmp1[100], tmp2[100];
	time_t tick = LogtimeStart;
	struct tm tm;
	tm = *localtime(&tick);
	timestart.SetFormat("yyyy-MM-dd HH:mm:ss");
	timestop.SetFormat("yyyy-MM-dd HH:mm:ss");
	CTime t_Start(LogtimeStart);
	timestart.SetTime(&t_Start);
	CTime t_Stop(LogtimeStop);
	timestop.SetTime(&t_Stop);
	strftime(tmp1, sizeof(tmp1), "%Y-%m-%d %H:%M:%S", &tm);
	tick = LogtimeStop;
	tm = *localtime(&tick);
	strftime(tmp2, sizeof(tmp2), "%Y-%m-%d %H:%M:%S", &tm);
	m_LogTimeSpanStr = CString(tmp1) + "--" + CString(tmp2);
	m_Editcontrol.SetWindowText(m_LogTimeSpanStr);
	fseek(&rFile, 0, SEEK_SET);
}

void ChangeToTime(unsigned long mTime, char *timeTmp, int num)
{
	time_t tick = mTime;
	struct tm tm;
	tm = *localtime(&tick);
	strftime(timeTmp, num, "%Y-%m-%d %H:%M:%S", &tm);
}

void GetQueryTimeWin(CDateTimeCtrl &TimeStart, CDateTimeCtrl &TimeStop, CTime &startTime, CTime &stopTime)
{
	//获取显示的时间
	TimeStart.GetTime(startTime);
	TimeStop.GetTime(stopTime);
}

void SetFileEmpty(FILE *rFile)
{
	if (rFile != NULL)
	{
		rFile = NULL;
	}
}

BOOL TransformLogFile(CString strFilePath, FILE* pFile)
{
	if (strFilePath.IsEmpty())
	{
		return FALSE;
	}
	//CMainFrame *pMain = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	//CLogFileFilterView *pView = (CLogFileFilterView *)pMain->GetActiveView();
	CString logNameNew, strData, strChange;
	CString strFilter = "文本文件(*.LOG)| *.LOG||";
	logNameNew = strFilePath.Mid(0, (strlen(strFilePath)-strlen(".LOG")));
	logNameNew +=  "_NEW.LOG";
	CFileDialog filedlg(
		false,
		".LOG",
		_T(logNameNew),
		OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		strFilter,
		NULL);
	if(filedlg.DoModal() == IDOK)
	{
		FILE *rFileIpdbgChange = fopen(filedlg.GetPathName(), "w+b");
		REPLAY_DATA dataReplay = {0};
		ReadReplayDataFromLog(*pFile, dataReplay);
		while(!feof(pFile))
		{
			CTime logTime(dataReplay.m_time);
			strData = (CString)dataReplay.m_data;
			char bufTmpTime[100] = {0};
			CString strTmpTime;
			ChangeToTime(dataReplay.m_time, bufTmpTime, 100);
			strTmpTime.Format("%s", bufTmpTime);
			strChange = strTmpTime + strData;
			fwrite(strChange, strlen(strChange), 1, rFileIpdbgChange);
			ReadReplayDataFromLog(*pFile, dataReplay);
		}
		fclose(rFileIpdbgChange);
		fseek(pFile, 0, SEEK_SET);
		return TRUE;
	}
	return FALSE;
}

BOOL OpenLogFile(CString strFilter, char *pFilePath)
{
	if(strFilter.IsEmpty() || pFilePath == NULL)
	{
		return FALSE;
	}
	CString strFilePath = "";
	CFileDialog filedlg(
		true,
		NULL,
		NULL,
		OFN_NOCHANGEDIR,
		strFilter,
		NULL);
	if(filedlg.DoModal() == IDOK)
	{
		strFilePath = filedlg.GetPathName();
	}
	else
	{
		if(strFilePath.IsEmpty())
		{
			return FALSE;
		}
	}
	strcpy(pFilePath, strFilePath);
	return TRUE;
}

