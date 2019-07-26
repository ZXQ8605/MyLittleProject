#include "string.h"

#include <fstream>

void GetLogTimeSpan(FILE &rFile);
void ChangeToTime(unsigned long mTime, char *timeTmp, int num);
void GetQueryTimeWin(CDateTimeCtrl &TimeStart, CDateTimeCtrl &TimeStop, CTime &startTime, CTime &stopTime);
