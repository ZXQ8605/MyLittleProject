; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCodeBitDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "LogFileFilter.h"
LastPage=0

ClassCount=6
Class1=CLogFileFilterApp
Class2=CLogFileFilterDoc
Class3=CLogFileFilterView
Class4=CMainFrame

ResourceCount=3
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Resource2=IDD_ABOUTBOX
Class6=CCodeBitDlg
Resource3=IDD_CODEBIT

[CLS:CLogFileFilterApp]
Type=0
HeaderFile=LogFileFilter.h
ImplementationFile=LogFileFilter.cpp
Filter=N

[CLS:CLogFileFilterDoc]
Type=0
HeaderFile=LogFileFilterDoc.h
ImplementationFile=LogFileFilterDoc.cpp
Filter=N
LastObject=CLogFileFilterDoc

[CLS:CLogFileFilterView]
Type=0
HeaderFile=LogFileFilterView.h
ImplementationFile=LogFileFilterView.cpp
Filter=C


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame




[CLS:CAboutDlg]
Type=0
HeaderFile=LogFileFilter.cpp
ImplementationFile=LogFileFilter.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
Command17=ID_SELECT_CADCOM
Command18=ID_SELECT_IPDBG
Command19=ID_CODEBIT
Command20=ID_TRAINNUMWIN
Command21=ID_POORSPERATION
Command22=ID_COUNTER
Command23=ID_MASTERCONNECTION
CommandCount=23

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[DLG:IDD_CODEBIT]
Type=1
Class=CCodeBitDlg
ControlCount=22
Control1=IDC_CHOOSECTRCODE,button,1342373897
Control2=IDC_CHOOSECTRSOME,button,1342242825
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_LOGTIMESPAN,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_QUERYTIMESTART,SysDateTimePick32,1342242848
Control8=IDC_STATIC,static,1342308352
Control9=IDC_QUERYTIMESTOP,SysDateTimePick32,1342242848
Control10=IDC_STATIC,static,1342308352
Control11=IDC_CHOOSEEXPCODE,button,1342373897
Control12=IDC_CHOOSEEXPSOME,button,1342242825
Control13=IDC_BUTTON1,button,1342242816
Control14=IDC_BUTTON2,button,1342242816
Control15=IDC_BUTTON3,button,1342242816
Control16=IDC_BUTTON4,button,1342242816
Control17=IDC_CHECK,button,1342242816
Control18=IDC_CANCEL,button,1342242816
Control19=IDC_EXPCODELIST,listbox,1352728835
Control20=IDC_EXPCODESELECTLIST,listbox,1352728835
Control21=IDC_CTRCODELIST,listbox,1352728835
Control22=IDC_CTRCODESELECTLIST,listbox,1352728835

[CLS:CCodeBitDlg]
Type=0
HeaderFile=CodeBitDlg.h
ImplementationFile=CodeBitDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CCodeBitDlg

