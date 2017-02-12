#include "GraphH.h"


class SelectBox {

private:

	int align[3][2];
	vector<string>list;
	vector<void(*)(int)>eventselect, eventclose, eventopen;
	string label = "";
	COLORREF colorline = RGB(166, 111, 254), colorselect = RGB(88, 80, 50), arrowup = RGB(166, 0, 0), colbr = RGB(0, 0, 0), focuscolor = RGB(255, 1, 1), colortext = RGB(0, 0, 0),
	colorbody = RGB(255, 255, 255), colorbtn = RGB(166, 247, 177), arrowclick = RGB(26, 27, 17), btnclick = RGB(130,184,111);
	int currmouse = -1, sizemax = 0, padding = 2, maxsizeword = 0 , w = 0, lenlist = 0, h = 20, ytext = 0, xtext = 0, currvalue = 0;
	RECT r;
	HWND hwnd;
	struct SizeBtn { int w = 18; int h = 18; } btns;
	HDC hdc, mem;
	HBITMAP bmpmem;
	HGDIOBJ bmpobj;
	int mousey = 0;
	bool cursorhover = false, offbtn = true, setsize = false, create = false, enabled = true, focus = false, Under = false;
	bool viewSelectMain = true , visibles = true;
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
		r1.left = r.left + w; r1.top = r.top + 2; r1.right = r1.left + btns.w - 2; r1.bottom = r1.top + r.bottom - r.top - 4;

		if (offbtn)
		{
			HBRUSH brush;
			HBRUSH fr = CreateSolidBrush(RGB(0, 0, 0));
			if (!focus) { brush = CreateSolidBrush(colorbtn); } else { brush = CreateSolidBrush(btnclick); }
			SelectObject(hdc, brush); FillRect(hdc, &r1, brush);  DeleteObject(brush);
			FrameRect(hdc, &r1, fr); DeleteObject(fr);
		}

		int h1 = r1.top + (r.bottom - r.top ) / 2;
		POINT my[3];
		HBRUSH brush = CreateSolidBrush(arrowup); HPEN pen = CreatePen(PS_SOLID, 1, arrowup);
		HGDIOBJ hobj = SelectObject(hdc, brush); HGDIOBJ hobj1 = SelectObject(hdc, pen);

		my[0].x = r.left + w + (btns.w / 2) - 1; 
		my[0].y = h1;

		my[1].x = r.left + w + 4;
		my[1].y = h1 - 4;

		my[2].x = r.left + w + btns.w - 6;
		my[2].y = h1 - 4;

		Polygon(hdc, my, 3);
		SelectObject(hdc, hobj); SelectObject(hdc, hobj1);
		DeleteObject(brush); DeleteObject(pen);
	}


	void clearMem()
	{
		if (bmpobj != NULL)
		{
			int size = lenlist*(h + padding * 2);
			BitBlt(hdc, r.left + 1, r.top + h + (padding * 2), btns.w + w - 1, size, mem, 0, 0, SRCCOPY);
			SelectObject(mem, bmpobj);
			DeleteObject(bmpmem);
			DeleteDC(mem);
		}
	}

	void showSelect()
	{
		int size = lenlist*(h+padding*2);
		if (sizemax != 0)
		{
			size = sizemax;
		}
		RECT r1;
		r1.left = r.left + 1; r1.top = r.top + h + (padding * 2); r1.right = r1.left + btns.w + w - 1; r1.bottom = r1.top + size;

		mem = CreateCompatibleDC(hdc);
		bmpmem = CreateCompatibleBitmap(hdc, btns.w + w - 1, size);
		bmpobj = SelectObject(mem, bmpmem);
		BitBlt(mem, 0, 0, btns.w + w - 1, size, hdc, r1.left, r1.top, SRCCOPY);

		HBRUSH fr = CreateSolidBrush(RGB(122, 120, 120));
		HBRUSH brush = CreateSolidBrush(RGB(241,241,241));
		SelectObject(hdc, brush); FillRect(hdc, &r1, brush);  DeleteObject(brush);
		FrameRect(hdc, &r1, fr); DeleteObject(fr);

		if (mousey != 0)
		{
			int pdn = h + (padding * 2); int result = ((mousey) - (r.top + pdn + 2)) / pdn;
			RECT r2;
			r2.left = r.left + 2; r2.right = r1.right - 1; r2.top = r1.top + (result*pdn); r2.bottom = r2.top + pdn;

			brush = CreateSolidBrush(colorline);
			HGDIOBJ hobj2 = SelectObject(hdc, brush);
			FillRect(hdc, &r2, brush);
			SelectObject(hdc, hobj2);
			DeleteObject(brush);
		}

		HFONT font = CreateFontA(16, 6, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH, "Times New Roman");
		HGDIOBJ hobj = SelectObject(hdc, font);
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(0, 0, 0));

		int offset = r1.top + padding + 2;

		for (int i = 0; i < lenlist; i++)
		{
			TextOutA(hdc, r1.left + 7, offset, list[i].c_str(), list[i].length());
			offset += h+(padding*2);
		}

		SelectObject(hdc, hobj);
		DeleteObject(font);
	}

public:

	void setHWND(HWND hwnd1 = NULL)
	{
		hwnd = hwnd1;
		hdc = GetDC(hwnd);
	}

	SelectBox(string str = "")
	{
		label = str;
	}

	RECT HINT()
	{
		return r;
	}

	void setCursorHover(bool data)
	{
		cursorhover = data;
	}

	void add(string list1)
	{
		if (!setsize && maxsizeword < list1.length())
		{
			maxsizeword = list1.length();
			SIZE zz = weightTextRet(list1);
			w = zz.cx + 40;
		}
		list.push_back(list1);
		lenlist = list.size();
		if (create) { InvalidateRect(hwnd, &r, true); show(); }
	}

	void bindWindow(string r)
	{
		if (r == "bottom::left")
		{
			align[0][0] = 1;
			align[0][1] = 0;

		}
		else if (r == "bottom::right")
		{
			align[0][1] = 1;
			align[0][0] = 0;

		}
		else if (r == "top::left")
		{
			align[1][0] = 1;
			align[1][1] = 0;

		}
		else if (r == "top::right")
		{
			align[1][1] = 1;
			align[1][0] = 0;

		}
		else if (r == "center")
		{
			align[3][0] = 1;
		}
	}

	void serSizeHeight( int i )
	{
		sizemax = i;
	}

	void add(vector<string> vec)
	{
		list.insert(vec.end(), vec.begin(), vec.end());
		lenlist = list.size();
		if (create) { InvalidateRect(hwnd, &r, true); show(); }
	}

	void setLabel(string text)
	{
		label = text;
		HFONT font = CreateFontA(17, 6, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH, "Times New Roman");
		HGDIOBJ hobj = SelectObject(hdc, font);
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(0, 0, 0));
		TextOutA(hdc, r.left + 1, r.top - 18, text.c_str(), text.length());
		SelectObject(hdc, hobj);
		DeleteObject(font);
	}

	void show()
	{
		UpdateWindow(hwnd);
		if (hwnd == NULL) return;

		r.left = local.x; r.top = local.y; r.right = r.left + w + btns.w; r.bottom = r.top + h + (padding*2);

		if (viewSelectMain)
		{
			HBRUSH brush = CreateSolidBrush(colorbody);
			HGDIOBJ hobj = SelectObject(hdc, brush);
			FillRect(hdc, &r, brush);
			SelectObject(hdc, hobj);
			DeleteObject(brush);
		}

		HFONT font = CreateFontA(16, 6, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH, "Arial");
		HGDIOBJ hobj1 = SelectObject(hdc, font);

		create = true;

		SIZE size = weightTextRet(list[currvalue]);

		double ytext = r.top+(h + (padding*2) - size.cy) / 2;

		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, colortext);
		TextOutA(hdc, r.left + padding + 2, ytext, list[currvalue].c_str(), list[currvalue].length());
		SelectObject(hdc, hobj1);
		DeleteObject(font);

		showBtn();

		if (focus) { showSelect(); }
	}

	void addEventSelect(void(*f)(int))
	{
		eventselect.push_back(f);
	}

	void addEventOpen(void(*f)(int))
	{
		eventopen.push_back(f);
	}

	void addEventClose(void(*f)(int))
	{
		eventclose.push_back(f);
	}

	void hideSelectMain( bool status )
	{
		viewSelectMain = status;
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

	void setEnabledBtn( bool status)
	{
		offbtn = status;
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

	void setColorBtnClick(COLORREF rgb)
	{
		btnclick = rgb;
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

	void setFocus()
	{
		focus = true;
		if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(focuscolor, 1); }
	}

	void Click(string type, int y, int x)
	{
		if (y >= r.top && y <= r.top + h + padding && x >= r.left && x <= r.left + w + btns.w)
		{
			if (type == "DOWN")
			{
				if (!focus) { if (!eventselect.empty()) { eventselect[0](0); } setFocus(); } else
				if (focus) 
				{
					focus = false; clearMem(); InvalidateRect(hwnd, &r, true); show(); setBorder(colbr, 1);
					if (!eventclose.empty()) { eventclose[0](0); }
				}
			}

		} else if ( focus && y >= r.top + h + (padding * 2)+2 && y <= r.top+padding+h+lenlist*(h + padding * 2) && x >= r.left+1 && x <= r.left+1+btns.w+w-1)
		{
			if (cursorhover){HCURSOR cursor = (HCURSOR)LoadImageA(NULL, (LPCSTR)IDC_HAND, IMAGE_CURSOR, 0, 0, LR_SHARED);SetCursor(cursor);}

			if (type == "DOWN") return;
		
			int pdn = h + (padding * 2);
			int result = ((y + pdn) - (r.top + pdn + 2)) / pdn;
			currvalue = result-1;

			mousey = 0;
			currmouse = -1;
			focus = false;
			clearMem();
			InvalidateRect(hwnd, &r, true); show(); setBorder(colbr, 1);
			
			if (cursorhover){HCURSOR cursor = (HCURSOR)LoadImageA(NULL, (LPCSTR)IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_SHARED);SetCursor(cursor);}

			if (!eventselect.empty()) { eventselect[0](result); }
			

		} else {

			if (focus)
			{
				focus = false;
				clearMem();
				InvalidateRect(hwnd, &r, true); show(); setBorder(colbr, 1);
				if (!eventclose.empty()) { eventclose[0](0); }
			}
		}
	}

	void Wheel(WPARAM wp, LPARAM lp)
	{

	}

	void Mouse( int y , int x )
	{
		int pdn = h + (padding * 2);
		if ( focus && y >= r.top + pdn+2 && y <= r.top + padding + h + lenlist*pdn && x >= r.left + 1 && x <= r.left + 1 + btns.w + w - 1)
		{
			mousey = y;
			int result = ((y+pdn) - (r.top + pdn + 2)) / pdn;
			
			if ( currmouse != result)
			{
				currmouse = result;
				//InvalidateRect(hwnd, &r, true); show(); setBorder(colbr, 1);
			}

			if (cursorhover)
			{
				HCURSOR cursor = (HCURSOR)LoadImageA(NULL, (LPCSTR)IDC_HAND, IMAGE_CURSOR, 0, 0, LR_SHARED);
				SetCursor(cursor);
			}
		} else {

			if (mousey != 0)
			{
				mousey = 0;
				currmouse = -1;
				InvalidateRect(hwnd, &r, true); show(); setBorder(colbr, 1);
			}
		}
	}

	void repaint()
	{
		focus = false;
		clearMem();
		InvalidateRect(hwnd, &r, true); show(); setBorder(colbr, 1);
	}

	void repaintMove()
	{
		focus = false;
		clearMem();
		RECT rt;
		int w = GetSystemMetrics(SM_CXSCREEN);
		int h = GetSystemMetrics(SM_CYSCREEN);
		GetWindowRect(hwnd, &rt);
		if (rt.left <= 0 || rt.right >= w || rt.bottom >= h) { InvalidateRect(hwnd, &r, true); show(); setBorder(colbr, 1); }
	}

	void hide( )
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

	void setEnabled( bool status )
	{
		enabled = status;
	}

	void ObBinding()
	{
		RECT rt1;
		GetWindowRect(hwnd, &rt1);
		if (align[0][0] == 1) { setLocation(15, rt1.bottom - rt1.top - h - 50); } else
		if (align[0][1] == 1) { setLocation(rt1.right - rt1.left - w - 30, rt1.bottom - rt1.top - h - 50); } else
		if (align[1][0] == 1) { setLocation(15, 10); } else
		if (align[1][1] == 1) { setLocation(rt1.right - rt1.left - w - 30, 10); } else
		if (align[3][0] == 1) { setLocation((rt1.right - rt1.left - w) / 2, (rt1.bottom - rt1.top - h) / 2); }

	}
};