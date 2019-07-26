#include "string.h"
#include <fstream>

void SetControlTime(CFile &rFile, CEdit &m_Editcontrol, CDateTimeCtrl &timestart, CDateTimeCtrl &timestop);
void ChangeToTime(unsigned long mTime, char *timeTmp, int num);
void GetQueryTimeWin(CDateTimeCtrl &TimeStart, CDateTimeCtrl &TimeStop, CTime &startTime, CTime &stopTime);
void SetFileEmpty(CFile *rFile);
BOOL TransformLogFile(CString strFilePath, CFile* pFile);
CString OpenLogFile(CString strFilter);
