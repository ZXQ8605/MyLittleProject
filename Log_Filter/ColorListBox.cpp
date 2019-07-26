// ColorListBox.cpp : 实现文件
//

#include "stdafx.h"
#include "LogFileFilter.h"
#include "ColorListBox.h"

#define LISTBOX_MAX_LEN 200


// CColorListBox

IMPLEMENT_DYNAMIC(CColorListBox, CListBox)

CColorListBox::CColorListBox()
{
	width = 0;
	font1.CreateFontA(16, // nHeight 
		0, // nWidth 
		0, // nEscapement 
		0, // nOrientation 
		FW_NORMAL, // nWeight 
		FALSE, // bItalic 
		FALSE, // bUnderline 
		0, // cStrikeOut 
		ANSI_CHARSET, // nCharSet 
		OUT_DEFAULT_PRECIS, // nOutPrecision 
		CLIP_DEFAULT_PRECIS, // nClipPrecision 
		DEFAULT_QUALITY, // nQuality 
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
		_T("宋体"));
	font2.CreateFontA(16, // nHeight 
		0, // nWidth 
		0, // nEscapement 
		0, // nOrientation 
		FW_BOLD, // nWeight 
		FALSE, // bItalic 
		FALSE, // bUnderline 
		0, // cStrikeOut 
		ANSI_CHARSET, // nCharSet 
		OUT_DEFAULT_PRECIS, // nOutPrecision 
		CLIP_DEFAULT_PRECIS, // nClipPrecision 
		DEFAULT_QUALITY, // nQuality 
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
		_T("宋体"));
}

CColorListBox::~CColorListBox()
{
}


BEGIN_MESSAGE_MAP(CColorListBox, CListBox)

END_MESSAGE_MAP()



// CColorListBox 消息处理程序




void CColorListBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct/*lpDrawItemStruct*/)
{

	// TODO:  添加您的代码以绘制指定项
	if(lpDrawItemStruct->itemID == -1)
	{
		return;
	}
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC); 
	CRect rect(lpDrawItemStruct->rcItem);
	COLORREF crRedText = RGB(255,0,0);
	COLORREF crBlackText=RGB(0,0,0); 
	CString lpStr;
	
	CFont* pOldFont = pDC->SelectObject(GetFont());
	GetText(lpDrawItemStruct->itemID,lpStr );   //得到串
	if(lpStr.Find("软件重启") >= 0)
	{
		pDC->SelectObject(&font2); //启用新字体// 
		pDC->SetTextColor(crRedText);  
	}
	else
	{
		pDC->SelectObject(&font1); //启用新字体//
		pDC->SetTextColor(crBlackText); 
	}
	DrawText(lpDrawItemStruct->hDC,lpStr, -1, &lpDrawItemStruct->rcItem, 
		DT_LEFT | DT_SINGLELINE);// restore DC colorsc
	
}


void CColorListBox::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	CListBox::PreSubclassWindow();
}


void CColorListBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct/*lpMeasureItemStruct*/)
{
	// TODO:  添加您的代码以确定指定项的大小
}


BOOL CColorListBox::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	// TODO: 在此添加专用代码和/或调用基类
	//dwStyle |= LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED | LBS_HASSTRINGS;
	return CListBox::Create(dwStyle, rect, pParentWnd, nID);
}


int CColorListBox::AddString(LPCTSTR s)
{
	int result = CListBox::AddString(s);
	if(result < 0)
		return result;
	updateWidth(s);
	return result;
}


void CColorListBox::updateWidth(LPCTSTR s)
{
	CClientDC dc(this);

	CFont * pFont = CListBox::GetFont();
	dc.SelectObject(pFont);

	CSize sz = dc.GetTextExtent(s, _tcslen(s));
	sz.cx += 3 * ::GetSystemMetrics(SM_CXBORDER);
	if(sz.cx > width)
	{ /* extend */
		width = sz.cx;
		//保证重绘之后的字符串不被截断，在原有的宽度上再增大
		width = width*4/3;
		CListBox::SetHorizontalExtent(width);
	} /* extend */
}
