#pragma once


// CColorListBox

class CColorListBox : public CListBox
{
	DECLARE_DYNAMIC(CColorListBox)

public:
	CColorListBox();
	virtual ~CColorListBox();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct/*lpDrawItemStruct*/);
	virtual void PreSubclassWindow();
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpDrawItemStruct/*lpMeasureItemStruct*/);
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

public:
	int width;
	CFont   font1, font2;
	int AddString(LPCTSTR s);
	void updateWidth(LPCTSTR s);
};


