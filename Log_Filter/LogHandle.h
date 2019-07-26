typedef unsigned long IP_TIME;
typedef int IntegerLength;
#define MAX_REPLAY_DATA_LENGTH 1024     //数据内容存放最大值
typedef struct       //存储格式 
{
	char  m_flag;
	IP_TIME  m_time; 
	short m_len;
	char  m_data[MAX_REPLAY_DATA_LENGTH];
	long  m_position;
}REPLAY_DATA;

class CReadLogFile
{
public:
	static int GetIntegerLengthInLog(IntegerLength eIntL);
	static int ReadIntegerValueFromLog(CFile& rFile, void* pIntValue, IntegerLength eIntL);
	static bool IsReplayFileFormatBinary(CFile& rFile);
	static int ReadReplayDataFromLog(CFile& rFile, REPLAY_DATA& dataReplay);
private:
};

class CLogFileOperation
{
public:
	static int SetLogTimeWidthAndDefaultQueryTime(CFile &rFile, CEdit &m_Editcontrol, CDateTimeCtrl &timestart, CDateTimeCtrl &timestop);
	static void ChangeToTime(unsigned long mTime, char *timeTmp, int num);
	static void GetQueryTimeWin(CDateTimeCtrl &TimeStart, CDateTimeCtrl &TimeStop, CTime &startTime, CTime &stopTime);
	static void SetFileEmpty(CFile *rFile);
	static BOOL TransformLogFile(CString strFilePath, CFile* pFile, int *wrongLineNum);
	static CString OpenLogFile(CString strFilter);
	static CString ConvertFromEpochToHumanReadableDate(unsigned long logTime);
	static CString IsFindRestartRecord(CString *strRecord, CString strRecordTime, int* numExp, int* numCtrl);
private:
};
