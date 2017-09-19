#include "GraphH.h"


class CounterField {

private:

	int align[3][2];
	vector<void(*)(int)>event;
	string text = "10"; string paddingText = "centre";
	COLORREF arrtemp = RGB(166,0,0), arrowdown = RGB(166, 0, 0), arrowup = RGB(166, 0, 0), colbr = RGB(0, 0, 0), focuscolor = RGB(255, 1, 1), colortext = RGB(0, 0, 0),
	colorbody = RGB(255, 255, 255), colorbtn = RGB(166, 247, 177), arrowclick = RGB(26, 27, 17);
	int padding = 2, w, h, maxvalue = 330, minvalue = 0, ytext = 0, xtext = 0, currvalue = 0, step = 1;
	RECT r;
	HWND hwnd;
	struct SizeBtn { int w = 18; int h = 18; } sizebtn;
	HDC hdc;
	bool visibles = true, create = false, enabled = true , focus = false , Under = false;
	struct Location { int x = 0; int y = 0; } local;

	SIZE weightTextRet(string tex)
	{
		SIZE size;
		GetTextExtentPoint32A(hdc, tex.c_str(), tex.length(), &size);
		return size;
	}

	void showBtn()
	{

		RECT r1;
		HBRUSH fr = CreateSolidBrush(RGB(0, 0, 0));
		r1.left = r.left + w; r1.top = r.top+2; r1.right = r1.left + sizebtn.w - 2; r1.bottom = r1.top + h - (h / 2) - 1;
		HBRUSH brush = CreateSolidBrush(colorbtn);
		SelectObject(hdc, brush); FillRect(hdc, &r1, brush);  DeleteObject(brush);
		FrameRect(hdc, &r1, fr); DeleteObject(fr);

		fr = CreateSolidBrush(RGB(0, 0, 0));
		r1.left = r.left + w; r1.top = local.y + (h / 2); r1.right = r1.left + sizebtn.w - 2; r1.bottom = r.top + h - 2;
		brush = CreateSolidBrush(colorbtn); SelectObject(hdc, brush);
		FillRect(hdc, &r1, brush); DeleteObject(brush);
		FrameRect(hdc, &r1, fr);  DeleteObject(fr);

	}

	void drawTriangle()
	{
		POINT my[3];
		HBRUSH brush = CreateSolidBrush(arrowup); HPEN pen = CreatePen(PS_SOLID, 1, arrowup);
	    HGDIOBJ hobj = SelectObject(hdc, brush); HGDIOBJ hobj1 = SelectObject(hdc, pen);
		my[0].x = r.left + w + (sizebtn.w/2)-2; my[0].y = r.top + 6; 
		my[1].x = r.left + w + 3; my[1].y = r.top + sizebtn.h - 8;
		my[2].x = r.left + w + sizebtn.w - 6 ; my[2].y = r.top + sizebtn.h - 8;
		Polygon(hdc, my, 3);
		SelectObject(hdc, hobj); SelectObject(hdc, hobj1);
		DeleteObject(brush); DeleteObject(pen);
	
		brush = CreateSolidBrush(arrowdown); pen = CreatePen(PS_SOLID, 1, arrowdown);
		SelectObject(hdc, brush); SelectObject(hdc, pen);
		my[0].x = r.left + w + (sizebtn.w / 2) - 2; my[0].y = r.bottom - 6;
		my[1].x = r.left + w + 3; my[1].y = r.top + sizebtn.h + 2;
		my[2].x = r.left + w + sizebtn.w - 6; my[2].y = r.top + sizebtn.h + 2;
		Polygon(hdc, my, 3);
		SelectObject(hdc,hobj); SelectObject(hdc, hobj1);
		DeleteObject(brush); DeleteObject(pen);
	}

public:

	void setHWND(HWND hwnd1 = NULL)
	{
		hwnd = hwnd1;
		hdc = GetDC(hwnd);
	}

	CounterField( int i = 0 )
	{
		text = to_string(i);
		
	}

	RECT HINT()
	{
		return r;
	}

	void show()
	{
		UpdateWindow(hwnd);
		if (hwnd == NULL) return;

		r.left = local.x; r.top = local.y; r.right = r.left + w + sizebtn.w; r.bottom = r.top + h;

		HBRUSH brush; brush = CreateSolidBrush(colorbody);
		HGDIOBJ hobj = SelectObject(hdc, brush);
		FillRect(hdc, &r, brush);
		SelectObject(hdc, hobj);
		DeleteObject(brush);

		HFONT font = CreateFontA(16, 6, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH, "Arial");
	    HGDIOBJ hobj1 = SelectObject(hdc, font);

		SIZE zz = weightTextRet(text);

		create = true;

		ytext = (h - zz.cy) / 2;
		xtext = (w - zz.cx) / 2;

		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, colortext);

		if (paddingText == "left") { TextOutA(hdc, r.left + 3, r.top + (int)round(ytext), text.c_str(), text.length()); } else
		if (paddingText == "centre") { TextOutA(hdc, r.left + xtext, r.top + (int)round(ytext), text.c_str(), text.length()); } else
		if (paddingText == "right") { TextOutA(hdc, r.left + w - (text.length()*7) - 3, r.top + (int)round(ytext), text.c_str(), text.length()); }
		SelectObject(hdc, hobj1);
		DeleteObject(font);

		showBtn();
		drawTriangle();

	}

	void setLabel(string text)
	{
		HFONT font = CreateFontA(17, 6, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH, "Times New Roman");
		HGDIOBJ hobj = SelectObject(hdc, font);
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(0, 0, 0));
		TextOutA(hdc, r.left + 1, r.top - 18, text.c_str(), text.length());
		SelectObject(hdc, hobj);
		DeleteObject(font);
	}

	void propertiesBtn( int w , int h , COLORREF rgb , COLORREF arrow )
	{
		colorbtn = rgb; sizebtn.h = h; sizebtn.w = w; 
		CounterField::arrowup = arrow; CounterField::arrowdown = arrow; arrtemp = arrow;
	}

	void setBorder(COLORREF rgb, int bold = 1)
	{
		RECT r1;
		HBRUSH brush1 = CreateSolidBrush(rgb);
		HGDIOBJ hobj = SelectObject(hdc, brush1);
		FrameRect(hdc, &r, brush1);
		SelectObject(hdc, hobj);
		DeleteObject(brush1);
		
	}

	string getNumberString( )
	{
		return text;
	}

	int getNumberInt( )
	{
		return stoi(text);
	}

	void setMaxValue(int max)
	{
		maxvalue = max;
	}

	void setColor(COLORREF rgb)
	{
		colorbody = rgb;
		if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(colbr, 1); }
	}

	void setColorText(COLORREF rgb)
	{
		colortext = rgb;
		if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(colbr, 1); }
	}

	void setColorBtn(COLORREF rgb)
	{
		colorbtn = rgb;
		if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(colbr, 1); }
	}

	void setLocation(int x1, int y1)
	{
		local.x = x1; local.y = y1;
		if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(colbr, 1); }
	}

	void setSize(int w1, int h1)
	{
		w = w1; h = h1;
		if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(colbr, 1); }
	}

	void setUP( )
	{
		if (currvalue > maxvalue-1 ) return;
		currvalue += step;
		text = to_string(currvalue);
		if (create == true) { InvalidateRect(hwnd, &r, true); show(); if (focus) { setBorder(focuscolor, 1); } else { setBorder(colbr, 1); } }
		if (event.size()>0) { event[0](1); }
	}

	void setDOWN()
	{
		if (currvalue < minvalue+1) { return; }
		currvalue -= step;
		text = to_string(currvalue);
		if (create == true) { InvalidateRect(hwnd, &r, true); show(); if (focus) { setBorder(focuscolor, 1); } else { setBorder(colbr, 1); } }
		if (event.size()>0) { event[0](0); }
	}

	void setStep( int index )
	{
		step = index;
	}

	void setNumber(int i = 0 )
	{
		text = to_string(i);
		if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(colbr, 1); }
	}

	void setFocus()
	{
		focus = true;
		if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(focuscolor, 1); }
	}

	void Click( string type , int y, int x)
	{
		if (y >= r.top && y <= r.top + h && x >= r.left && x <= r.left + w + sizebtn.w)
		{
			if (!focus) { setFocus(); }

			if (type == "DOWN")
			{
				Under = true;
				clickUP(y, x);
				clickDOWN(y, x);
			} else if (type == "UP") {

				arrowup = arrtemp;
				arrowdown = arrtemp;
				if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(focuscolor, 1); }
			}
		} else {

			if (focus)
			{
				Under = false;
				focus = false;
				arrowup = arrtemp;
				arrowdown = arrtemp;
				if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(colbr, 1); }
			}
		}

	}

	void Mouse(int y, int x)
	{

	}

	void alignText( string align )
	{
		paddingText = align;
	}

	void clickUP( int y , int x)
	{
		if (y >= r.top + 2 && y <= r.top + h - (h / 2) - 1 && x > r.left + w && x < r.right - 2)
		{
			arrowup = arrowclick;
			setUP();
		}
	}

	void clickDOWN( int y , int x)
	{
		if ( y >= r.top + h - (h / 2) - 2 && y <= r.bottom - 4 && x > r.left + w && x < r.right - 2)
		{
			arrowdown = arrowclick;
			setDOWN();
		}
	}

	void addEventUPDOWN( void(*f)(int))
	{
		event.push_back(f);
	}


	void repaint()
	{
		InvalidateRect(hwnd, &r, true); show(); setBorder(colbr, 1);
	}

	void repaintMove()
	{
		RECT rt;
		int w = GetSystemMetrics(SM_CXSCREEN);
		int h = GetSystemMetrics(SM_CYSCREEN);
		GetWindowRect(hwnd, &rt);
		if (rt.left <= 0 || rt.right >= w || rt.bottom >= h) { InvalidateRect(hwnd, &r, true); show(); setBorder(colbr, 1); }
	}

	void hide()
	{
		visibles = false;
	}

	void visible()
	{
		visibles = true;
	}

	void destroy()
	{
		hwnd = NULL;
		DeleteDC(hdc);
	}

	void setEnabled(bool status)
	{
		enabled = status;
	}

	void ObBinding()
	{
		RECT rt1;
		GetWindowRect(hwnd, &rt1);
		if (align[0][0] == 1) { setLocation(15, rt1.bottom - rt1.top - h - 50); }
		else
		if (align[0][1] == 1) { setLocation(rt1.right - rt1.left - w - 30, rt1.bottom - rt1.top - h - 50); }
		else
		if (align[1][0] == 1) { setLocation(15, 10); }
		else
		if (align[1][1] == 1) { setLocation(rt1.right - rt1.left - w - 30, 10); }
		else
		if (align[3][0] == 1) { setLocation((rt1.right - rt1.left - w) / 2, (rt1.bottom - rt1.top - h) / 2); }
	}
};