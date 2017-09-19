#include "GraphH.h"

class List {

private:

	int sizebtn = 9, lenlist = 0, end = 0, scrollpanew = 10, scrollpaneh = 9;
	vector<string>listitem;
	HDC hdc;
	HWND hwnd;
	RECT r, scroll, scroll1;
	bool status = true, create = false;
	SIZE size;
	int w = 150, h, activeitem = -1;
	bool enabled = true;
	struct Colortext { int r = 0; int g = 0; int b = 0; } colortext;
	struct Location { int x = 0; int y = 0; } local;
	COLORREF colbr = RGB(251, 0, 0), colln = RGB(184, 180, 187) , colorscroll = RGB(188, 188, 199);
	int padding = 22, sizeitem = 0, beginstr = 0, endstr = 0, bgcord = 0, slidersize = 0, endslider = 0, slidery = 0;
	vector<void(*)(int, char*)>funrun, funscroll;
	int maxsizeword = 0, offseth = 3;
	bool setsize = false, vertscroll = false, horscroll = false;

	void weightText(string tex)
	{
		GetTextExtentPoint32A(hdc, tex.c_str(), tex.length(), &size);
	}
	SIZE weightTextRet(string tex)
	{
		SIZE size;
		GetTextExtentPoint32A(hdc, tex.c_str(), tex.length(), &size);
		return size;
	}
	struct Color { int r; int g; int b; } color;

public:

	List()
	{
		
	}

	void setPadding(int num)
	{

	}

	void setHWND(HWND hwnd1 = NULL)
	{
		hwnd = hwnd1;
		hdc = GetDC(hwnd);
	}

	void setColor(int r1, int g1, int b1)
	{
		color.r = r1; color.g = g1; color.b = b1;
		if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(colbr, 1); }
	}

	void setLocation(int x1, int y1)
	{
		local.x = x1; local.y = y1;
		if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(colbr, 1); }
	}

	void setBorder(COLORREF rgb, int bold = 1)
	{
		RECT r1;
		colbr = rgb;
		HBRUSH brush1 = CreateSolidBrush(rgb);
		HGDIOBJ hobj = SelectObject(hdc, brush1);
		r1.left = local.x;
		r1.top = local.y;
		r1.right = r.left + w;
		r1.bottom = r.top + bold;
		FillRect(hdc, &r1, brush1);

		r1.left = local.x;
		r1.top = local.y + h - bold;
		r1.right = r.left + w;
		r1.bottom = r.top + h;
		FillRect(hdc, &r1, brush1);

		r1.left = local.x;
		r1.top = local.y;
		r1.right = r.left + bold;
		r1.bottom = r.top + h;
		FillRect(hdc, &r1, brush1);

		r1.left = local.x + w - bold;
		r1.top = local.y;
		r1.right = r.left + w;
		r1.bottom = r.top + h;
		FillRect(hdc, &r1, brush1);

		SelectObject(hdc, hobj);
		DeleteObject(brush1);
	}


	void add(string list)
	{
		if (!setsize && maxsizeword < list.length())
		{
			maxsizeword = list.length();
			SIZE zz = weightTextRet(list);
			w = zz.cx + 40;
		}
		listitem.push_back(list);
		lenlist = listitem.size();
		if (create) { InvalidateRect(hwnd, &r, true); show(); }
	}

	void add(vector<string> vec)
	{
		listitem.insert(vec.end(), vec.begin(), vec.end());
		lenlist = listitem.size();
		if (create) { InvalidateRect(hwnd, &r, true); show(); }
	}

	void add(char *str[])
	{
		int i = 0;
		for (i; i < sizeof(str); i++)
		{
			listitem.push_back(str[i]);
		}
		lenlist = listitem.size();
		if (create) { InvalidateRect(hwnd, &r, true); show(); }
	}

	void clearID(int index)
	{
		if (lenlist > index && create) { listitem.erase(listitem.begin() + index); lenlist = listitem.size(); InvalidateRect(hwnd, &r, true); show(); }
	}

	void clearAll()
	{
		listitem.erase(listitem.begin(), listitem.end()); lenlist = listitem.size();
		InvalidateRect(hwnd, &r, true); show();
	}

	void setColorLine(COLORREF rgb)
	{
		colln = rgb;
	}

	void setImageBack()
	{

	}

	void setIcon()
	{

	}

	void show()
	{
		UpdateWindow(hwnd);
		if (hwnd == NULL) return;

		if (!setsize) { h = lenlist * padding; }
		if ((lenlist * padding) + 3 - 2 >= h) { vertscroll = true; }

		offseth = 3; r.left = local.x; r.top = local.y; r.right = r.left + w; r.bottom = r.top + h;

		HBRUSH brush; brush = CreateSolidBrush(RGB(color.r, color.g, color.b)); SelectObject(hdc, brush); FillRect(hdc, &r, brush); DeleteObject(brush);

		setBorder(colbr, 1);

		if (activeitem > -1)
		{
			bgcord = beginstr * padding;
			if (r.top + (activeitem * padding) + 1 - bgcord > r.top) { bgcord--; }

			if (r.top + (activeitem * padding) + 1 - bgcord > r.top && r.top + (activeitem * padding) + 1 - bgcord < r.top + h - 10)
			{
				RECT ract; ract.left = r.left + 1;
				if (!vertscroll) { ract.right = r.right - 1; }
				else { ract.right = r.right - 10; }

				if (activeitem == 0)
				{
					ract.top = r.top + (activeitem * padding) + 1 - bgcord - 1;  ract.bottom = r.top + (activeitem * padding + padding) - bgcord + 1;
				}
				else if (activeitem + 1 == listitem.size())
				{
					ract.top = r.top + (activeitem * padding);  ract.bottom = r.top + (activeitem * padding + 21);
				}
				else {
					ract.top = r.top + (activeitem * padding) - bgcord;  ract.bottom = r.top + (activeitem * padding + padding) - bgcord;
				}
				HBRUSH brush = CreateSolidBrush(colln); HGDIOBJ hobj = SelectObject(hdc, brush); FillRect(hdc, &ract, brush); 
				SelectObject(hdc, hobj); DeleteObject(brush);
			}
		}

		HFONT font = CreateFontA(16, 6, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH, "Times New Roman");
	    HGDIOBJ obj11 = SelectObject(hdc, font);

		create = true;
		endslider = 0;

		for (int i = beginstr; i < lenlist; i++)
		{
			endstr = i;
			endslider++;
			if (offseth >= h - 5) { vertscroll = true; break; }
			SetBkMode(hdc, TRANSPARENT);
			if (activeitem == i) { SetBkColor(hdc, colln); }
			SetTextColor(hdc, RGB(9, 9, 9));
			TextOutA(hdc, r.left + 3, r.top + offseth, listitem[i].c_str(), listitem[i].length());
			offseth += padding;
		}

		SelectObject(hdc, obj11);
		DeleteObject(font);

		if (vertscroll)
		{
			slidersize = (int)round((h)/(lenlist/(endslider-1)));
			
			scroll.left = r.left + w - scrollpanew; scroll.top = local.y + 1; scroll.right = r.left + w - 1; scroll.bottom = r.top + h - 1;
			HBRUSH brush = CreateSolidBrush(RGB(88, 88, 99)); HGDIOBJ obj1 = SelectObject(hdc, brush); FillRect(hdc, &scroll, brush);
			SelectObject(hdc, obj1); DeleteObject(brush);

			scroll.left = r.left + w - 8; scroll.top = r.top + 11 + slidery; scroll.right = r.left + w - 3; scroll.bottom = r.top + slidersize + slidery;
			brush = CreateSolidBrush(colorscroll); HGDIOBJ obj2 = SelectObject(hdc, brush); FillRect(hdc, &scroll, brush); 
			SelectObject(hdc, obj2); DeleteObject(brush);

			scroll1.left = r.left + w - scrollpanew; scroll1.top = local.y + 1; scroll1.right = r.left + w - 1; scroll1.bottom = r.top + scrollpaneh;
			brush = CreateSolidBrush(RGB(33, 43, 44)); HGDIOBJ obj3 = SelectObject(hdc, brush); FillRect(hdc, &scroll1, brush); 
			SelectObject(hdc, obj3); DeleteObject(brush);
			scroll1.left = r.left + w - scrollpanew; scroll1.top = r.top + h - scrollpaneh; scroll1.right = r.left + w - 1; scroll1.bottom = r.top + h - 1;
			brush = CreateSolidBrush(RGB(33, 43, 44)); HGDIOBJ obj4 = SelectObject(hdc, brush); FillRect(hdc, &scroll1, brush); 
			SelectObject(hdc, obj4 ); DeleteObject(brush);
		}

		
	}

	RECT bindToMenu()
	{
		return r;
	}

	void setLabel(string text)
	{
		
		HFONT font = CreateFontA(17, 6, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH, "Times New Roman");
		HGDIOBJ hobj = SelectObject(hdc, font);
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(0, 0, 0));
		TextOutA(hdc, r.left + 1, r.top - 18, text.c_str(), text.length());
		SelectObject(hdc, hobj );
		DeleteObject(font);
	}

	void addEventDoScroll(void(*f)(int, char*))
	{
		funscroll.push_back(f);
	}

	void setSize(int w, int h)
	{
		lenlist = listitem.size();
		setsize = true;
		List::h = h; List::w = w;
	}

	void addEventSelect(void(*f)(int, char*))
	{
		funrun.push_back(f);
	}

	string getElement(int index)
	{
		for (int i = 0; i < lenlist; i++)
		{
			if (index == i) { return listitem[i]; }
		}
		return "false";
	}

	RECT HINT()
	{
		return r;
	}

	int getCurrentElement()
	{
		return activeitem;
	}

	void setCurrentElement(int index)
	{
		if (index > -1 && index + 1 <= listitem.size()) activeitem = index;
	}


	int getID(string list)
	{
		for (int i = 0; i < lenlist; i++)
		{
			if (list == listitem[i]) { return i; }
		}
		return -1;
	}

	void search(string list)
	{

	}

	int sizeList()
	{
		return lenlist;
	}

	void setDisabled()
	{
		enabled = false;
	}

	void setEnabled()
	{
		enabled = true;
	}

	void Wheel(WPARAM wp, LPARAM lp)
	{
		RECT pos;
		GetWindowRect( hwnd , &pos );

		if ( HIWORD(lp)-pos.top >= r.top+30 && HIWORD(lp)-pos.top <= r.top+h+30 && LOWORD(lp)-pos.left >= r.left+10 && LOWORD(lp)-pos.left <= r.left+w+scrollpanew-3)
		{
			if (GET_WHEEL_DELTA_WPARAM(wp) < 0)
			{
				if (endstr == lenlist - 1) { return; }
					
				beginstr++;
				slidery += round((h-18)/lenlist);
				
			}
			else if (GET_WHEEL_DELTA_WPARAM(wp) > 0)
			{
				if (beginstr == 0) return;
				slidery -= round((h - 18)/lenlist);
				beginstr--;
			}
			if (create) { InvalidateRect(hwnd, &r, true); show(); }
		}
	}

	void propertiesScroll()
	{

	}

	void setScrollNum( int index )
	{
		beginstr = index;
		if (create) { InvalidateRect(hwnd, &r, true); show(); }
	}

	void Click(int y, int x)
	{
		if ((y >= r.top && y <= r.top + h) && (x >= r.left && x <= r.left + w))
		{
			if (vertscroll)
			{
				if ((y >= r.top + 1 && y <= r.top + 8) && (x >= r.left + w - 8 && x <= r.left + w - 1))
				{
					if (beginstr == 0) return;
					slidery -= round(h / lenlist);
					beginstr--;
					if (create) { InvalidateRect(hwnd, &r, true); show(); }
					return;
				}
				else if ((y >= r.top + h - 8 && y <= r.top + h + 8) && (x >= r.left + w - 8 && x <= r.left + w - 1))
				{
					if (endstr == lenlist - 1) { return; }
					slidery += round(h / lenlist);
					beginstr++;	
					if (create) { InvalidateRect(hwnd, &r, true); show(); }
					return;
				}
				else if ((y >= r.top + 9 && y <= r.top + h - 9) && (x >= r.left + w - 8 && x <= r.left + w - 1))
				{
					
					if (y >= r.top + slidersize+slidery)
					{
						slidery += slidersize - 11; beginstr += endslider-1;
					} else if (y <= r.top + slidery)
					{
						slidery -= slidersize - 11; beginstr -= endslider-1;
					}
					if (create) { InvalidateRect(hwnd, &r, true); show(); }
					return;
				}
				

			}

			if (offseth - 2 <= y - r.top) { return; }

			for (int i = 0; i < lenlist; i++)
			{
				if ((r.top + (i*padding)) < y + bgcord && y + bgcord < (r.top + (i*padding) + padding))
				{
					if (activeitem != i && create) { activeitem = i; InvalidateRect(hwnd, &r, true); show(); }
					if (lenlist>0) { funrun[0](activeitem, (char*)listitem[i].c_str()); }
				}
			}
		}
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
};