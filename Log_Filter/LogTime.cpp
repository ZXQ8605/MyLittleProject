#include "stdafx.h"
#include "LogFileFilter.h"
#include "LogTime.h"
#include "LogHandle.h"

extern CString m_LogTimeSpanStr;

void GetLogTimeSpan(FILE &rFile)
{
	REPLAY_DATA dataReplay;
	unsigned long LogtimeStart = 0;
	unsigned long LogtimeStop = 0;
	int ret = 0;
	ret = ReadReplayDataFromLog(rFile, dataReplay);
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
	strftime(tmp1, sizeof(tmp1), "%Y-%m-%d %H:%M:%S", &tm);
	tick = LogtimeStop;
	tm = *localtime(&tick);
	strftime(tmp2, sizeof(tmp2), "%Y-%m-%d %H:%M:%S", &tm);
	m_LogTimeSpanStr = CString(tmp1) + "--" + CString(tmp2);
}

void ChangeToTime(unsigned long mTime, char *timeTmp, int num)
{
	char tmp1[100];
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
