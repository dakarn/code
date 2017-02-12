#include "GraphH.h"


class TextArea {

private:
	string text;
	RECT r;
	bool resizeLow = false, pressmouse = false;
	struct Color { int r = 255; int g = 255; int b = 255; } color;
	struct Colortext { int r = 0; int g = 0; int b = 0; } colortext;
	struct Location { int x = 0; int y = 0; } local;
	int h, w , offsetcaretw = 3, offsetcareth = 7;
	long timekey;
	bool status = true , create = false , threadstatus = false;
	HDC hdc;
	HWND hwnd;
	SIZE size;
	LPDWORD th;
	struct ColorBorder { COLORREF color = RGB(0, 0, 0); } colbr;
	HANDLE thread = NULL;
	vector<string> listsplit;
	bool rows = false;
	SIZE sizeofrows;
	int offsetw = 4; int offseth = 3; int fwidth = 0;
	bool focus = false;
	COLORREF focuscolor = RGB(255, 0, 0);

	void weightText(string tex)
	{
		GetTextExtentPoint32A(hdc, tex.c_str(), tex.length(), &size);
	}

	void weightTextRows(string tex)
	{
		GetTextExtentPoint32A(hdc, tex.c_str(), tex.length(), &sizeofrows);
	}

	long getTime()
	{
		time_t currtime = time(0);
		return GetTickCount();
	}

	string UPRusNum(int ind)
	{
		string ch = "";
		switch (ind)
		{
		case 32: ch = " ";break;case 48: ch = "0"; break;case 49: ch = "1"; break;case 50: ch = "2"; break;case 51: ch = "3"; break;case 52: ch = "4"; break;case 53: ch = "5"; break;
		case 54: ch = "6"; break;case 55: ch = "7"; break;case 56: ch = "8"; break;case 57: ch = "9";
		case 65: ch = "Ô"; break;case 68: ch = "Â"; break;case 83: ch = "Û"; break;case 66: ch = "È"; break;case 67: ch = "Ñ"; break;case 69: ch = "Ó"; break;
		case 70: ch = "À"; break;case 71: ch = "Ï"; break;case 72: ch = "Ð"; break;case 73: ch = "Ø"; break;case 74: ch = "Ù"; break;case 75: ch = "Ë"; break;
		case 76: ch = "Ä"; break;case 77: ch = "Ü"; break;case 78: ch = "Å"; break;case 79: ch = "Ù"; break;case 80: ch = "Ç"; break;case 81: ch = "É"; break;
		case 82: ch = "Ê"; break;case 84: ch = "Å"; break;case 85: ch = "Ã"; break;case 86: ch = "Ì"; break;case 87: ch = "Ö"; break;case 88: ch = "×"; break;
		case 89: ch = "Í"; break;case 90: ch = "ß";
		case 187: ch = "="; break;case 188: ch = ","; break;case 189: ch = "-"; break;case 190: ch = "."; break;case 191: ch = "/"; break;case 186: ch = ";"; break;
		case 219: ch = "["; break;case 220: ch = "\\"; break;case 221: ch = "]"; break;case 222: ch = "'";case 192: ch = "`";
		}
		return ch;
	}

	string UPEngNum(int ind)
	{
		string ch = "";
		switch (ind)
		{
		case 32: ch = " ";break;case 48: ch = "0"; break;case 49: ch = "1"; break;case 50: ch = "2"; break;case 51: ch = "3"; break;case 52: ch = "4"; break;case 53: ch = "5"; break;
		case 54: ch = "6"; break;case 55: ch = "7"; break;case 56: ch = "8"; break;case 57: ch = "9";
		case 65: ch = "A"; break;case 68: ch = "D"; break;case 83: ch = "S"; break;case 66: ch = "B"; break;case 67: ch = "C"; break;case 69: ch = "E"; break;
		case 70: ch = "F"; break;case 71: ch = "G"; break;case 72: ch = "H"; break;case 73: ch = "P"; break;case 74: ch = "J"; break;case 75: ch = "K"; break;
		case 76: ch = "L"; break;case 77: ch = "M"; break;case 78: ch = "N"; break;case 79: ch = "O"; break;case 80: ch = "P"; break;case 81: ch = "Q"; break;
		case 82: ch = "R"; break;case 84: ch = "T"; break;case 85: ch = "U"; break;case 86: ch = "V"; break;case 87: ch = "W"; break;case 88: ch = "X"; break;
		case 89: ch = "Y"; break;case 90: ch = "Z";
		case 187: ch = "="; break;case 188: ch = ","; break;case 189: ch = "-"; break;case 190: ch = "."; break;case 191: ch = "/"; break;case 186: ch = ";"; break;
		case 219: ch = "["; break;case 220: ch = "\\"; break;case 221: ch = "]"; break;case 222: ch = "'";case 192: ch = "`";
		}
		return ch;
	}

	string RusNum(int ind)
	{
		string ch = "";
		switch (ind)
		{
		case 32: ch = " ";break;case 48: ch = "0"; break;case 49: ch = "1"; break;case 50: ch = "2"; break;case 51: ch = "3"; break;case 52: ch = "4"; break;case 53: ch = "5"; break;
		case 54: ch = "6"; break;case 55: ch = "7"; break;case 56: ch = "8"; break;case 57: ch = "9";
		case 65: ch = "ô"; break;case 68: ch = "â"; break;case 83: ch = "û"; break;case 66: ch = "è"; break;case 67: ch = "ñ"; break;case 69: ch = "ó"; break;
		case 70: ch = "à"; break;case 71: ch = "ï"; break;case 72: ch = "ð"; break;case 73: ch = "ø"; break;case 74: ch = "î"; break;case 75: ch = "ë"; break;
		case 76: ch = "ä"; break;case 77: ch = "ü"; break;case 78: ch = "ò"; break;case 79: ch = "ù"; break;case 80: ch = "ç"; break;case 81: ch = "é"; break;
		case 82: ch = "ê"; break;case 84: ch = "å"; break;case 85: ch = "ã"; break;case 86: ch = "ì"; break;case 87: ch = "ö"; break;case 88: ch = "÷"; break;
		case 89: ch = "í"; break;case 90: ch = "ÿ";
		case 187: ch = "="; break;case 188: ch = ","; break;case 189: ch = "-"; break;case 190: ch = "."; break;case 191: ch = "/"; break;case 186: ch = ";"; break;
		case 219: ch = "["; break;case 220: ch = "\\"; break;case 221: ch = "]"; break;case 222: ch = "'";case 192: ch = "`";
		}
		return ch;
	}

	string EngNum(int ind)
	{
		string ch = "";
		switch (ind)
		{
		case 32: ch = " ";break;case 48: ch = "0"; break;case 49: ch = "1"; break;case 50: ch = "2"; break;case 51: ch = "3"; break;case 52: ch = "4"; break;case 53: ch = "5"; break;
		case 54: ch = "6"; break;case 55: ch = "7"; break;case 56: ch = "8"; break;case 57: ch = "9";
		case 65: ch = "a"; break;case 68: ch = "d"; break;case 83: ch = "s"; break;case 66: ch = "b"; break;case 67: ch = "c"; break;case 69: ch = "e"; break;
		case 70: ch = "f"; break;case 71: ch = "g"; break;case 72: ch = "h"; break;case 73: ch = "i"; break;case 74: ch = "j"; break;case 75: ch = "k"; break;
		case 76: ch = "l"; break;case 77: ch = "m"; break;case 78: ch = "n"; break;case 79: ch = "o"; break;case 80: ch = "p"; break;case 81: ch = "q"; break;
		case 82: ch = "r"; break;case 84: ch = "t"; break;case 85: ch = "u"; break;case 86: ch = "v"; break;case 87: ch = "w"; break;case 88: ch = "x"; break;
		case 89: ch = "y"; break;case 90: ch = "z";
		case 187: ch = "="; break;case 188: ch = ","; break;case 189: ch = "-"; break;case 190: ch = "."; break;case 191: ch = "/"; break;case 186: ch = ";"; break;
		case 219: ch = "["; break;case 220: ch = "\\"; break;case 221: ch = "]"; break;case 222: ch = "'";case 192: ch = "`";
		}
		return ch;
	}

	void IndToChar(int ind)
	{
		timekey = getTime();
		string ch = "";
		int lang = LOWORD(GetKeyboardLayout(0));

		if (lang == 1033)
		{
			ch = EngNum(ind);
		}
		else if (lang == 1049) { ch = RusNum(ind); }

		text += ch;

		if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(focuscolor, 1); }
	}

	SIZE weightTextRet(string tex)
	{
		SIZE size;
		GetTextExtentPoint32A(hdc, tex.c_str(), tex.length(), &size);
		return size;
	}

	static DWORD WINAPI rerenderCaret(void* Param)
	{
		TextArea* This = (TextArea*)Param;
		return This->threadstart();
	}

	DWORD threadstart()
	{
		while (threadstatus)
		{
			if (focus && timekey < getTime() - 600)
			{
				Sleep(500);
			}
			Sleep(600);
		}
		return 1;
	}

	void showCaret()
	{
		HFONT font = CreateFontA(23, 6, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH, "Times New Roman");
		HGDIOBJ obj = SelectObject(hdc, font);
		string text1 = "|";
		SIZE zz = weightTextRet(text1);
		double ytext1 = (h - zz.cy) / 2;
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(0, 0, 0));
		TextOutA(hdc, r.left + offsetcaretw, r.top + offseth - 4, text1.c_str(), text1.length());
		SelectObject(hdc, obj);
		DeleteObject(font);
	}

public:

	void setFocusColor(COLORREF rgb)
	{
		focuscolor = rgb;
	}

	void setHWND(HWND hwnd1 = NULL)
	{
		hwnd = hwnd1;
		hdc = GetDC(hwnd);
	}

	TextArea(string text1 = "")
	{
		split(text1," "); 
		
		for (vector<string>::iterator it = listsplit.begin(); it != listsplit.end(); it++)
		{
			string is = *it;
		}
		text = text1;
	}

	RECT bindToMenu()
	{
		return r;
	}

	void setFocus()
	{
		if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(focuscolor, 1); }

		CreateThread(NULL, NULL, rerenderCaret, (void*)this, NULL, NULL);
		string text = "|";
		HFONT font = CreateFontA(23, 6, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH, "Times New Roman");
		HGDIOBJ obj = SelectObject(hdc, font);
		SetBkColor(hdc, RGB(color.r, color.g, color.b));
		SetTextColor(hdc, RGB(0,0,0));
		TextOutA(hdc, r.left + offsetcaretw, r.top + offseth-4, text.c_str(), text.length());
		SelectObject(hdc, obj);
		DeleteObject(font);
	}


	void split( string text , string ch )
	{
		size_t res = text.find_first_of(ch);
		int start = 0;
		if (res == string::npos) return;

		rows = true;
		int len = text.length();

		while (true)
		{
			text = text.substr(start, len);
			size_t res1 = text.find_first_of(ch);
			string pos = text.substr(0, res1+1);
			start = res1+1;
			if (res1 == string::npos) 
			{ 
				string pos = text.substr(0, text.length()); listsplit.push_back(pos); break;
			}
			listsplit.push_back( pos );
		}

	}

	void setLabel( string text )
	{
	
		HFONT font = CreateFontA(17, 6, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH, "Times New Roman");
		HGDIOBJ obj = SelectObject(hdc, font);
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(colortext.r, colortext.g, colortext.b));
		TextOutA(hdc, r.left + 1, r.top - 18, text.c_str(), text.length());
		SelectObject(hdc, obj);
		DeleteObject(font);
	}


	void show()
	{
		UpdateWindow(hwnd);
		if (hwnd == NULL) return;

		r.left = local.x; r.top = local.y; r.right = r.left + w; r.bottom = r.top + h;

		HBRUSH brush; brush = CreateSolidBrush(RGB(color.r, color.g, color.b));
		HGDIOBJ hobj = SelectObject(hdc, brush); FillRect(hdc, &r, brush);
		SelectObject(hdc, hobj);
		DeleteObject(brush);

		create = true;

		HFONT font = CreateFontA(16, 6, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH, "Arial");
		HGDIOBJ obj1 = SelectObject(hdc, font);

		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(colortext.r, colortext.g, colortext.b));

		if (rows)
		{

			for (int i = 0; i < listsplit.size(); i++)
			{
				weightTextRows(listsplit[i]); fwidth += sizeofrows.cx; 

				if (fwidth >= w-6) { fwidth = sizeofrows.cx; offseth += 18; offsetw = 6; }
				if (offseth >= h - 15) { break; }
				
				TextOutA(hdc, r.left + offsetw, r.top + offseth, listsplit[i].c_str(), listsplit[i].length());

				offsetw += sizeofrows.cx;
			}

		} else {

			TextOutA(hdc, r.left + 3, r.top + 3, text.c_str(), text.length());
		}

		SIZE zz = weightTextRet(text);
		if (text != "") { if (offsetcaretw <= w - 10) { offsetcaretw = zz.cx + 7; } else { offsetcaretw = 7; } } else { offsetcaretw = 7; }

		SelectObject(hdc, obj1);
		DeleteObject(font);
		if (focus) { showCaret(); }
	
	}

	RECT HINT()
	{
		return r;
	}

	void setBorder(COLORREF rgb, int bold = 1)
	{
		RECT r1;
		HBRUSH brush1 = CreateSolidBrush(rgb);
		HGDIOBJ obj = SelectObject(hdc, brush1);
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
		SelectObject(hdc, obj);
		DeleteObject(brush1);
	}

	void Click( string type , int y, int x)
	{
		
		if ( (y >= r.top && y <= r.top + h) && (x >= r.left && x <= r.left + w))
		{
			if (type == "DOWN")
			{
				if (!focus) { threadstatus = true; focus = true; setFocus(); }

			} else if (resizeLow && type == "UP")
			{
				pressmouse = false;
				resizeLow = false;
				if (x - r.left >= 40) { w = x - r.left; }
				if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(focuscolor, 1); }
			}

			HCURSOR cursor = (HCURSOR)LoadImageA(NULL, (LPCSTR)IDC_IBEAM, IMAGE_CURSOR, 0, 0, LR_SHARED); SetCursor(cursor);
		} else {

			if (type == "DOWN")
			{
				pressmouse = false;
				resizeLow = false;

				if (focus)
				{
					threadstatus = false;
					focus = false;
					if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(colbr.color, 1); }
				}
			} else if (resizeLow && type == "UP")
			{
				pressmouse = false;
				w = x - r.left;
				resizeLow = !resizeLow;
				if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(focuscolor, 1); }
			}
		}
		if (resizeLow && x > r.left + w - 2 && x < r.left + w + 2)
		{
			pressmouse = true;
			HCURSOR cursor = (HCURSOR)LoadImageA(NULL, (LPCSTR)IDC_SIZEWE, IMAGE_CURSOR, 0, 0, LR_SHARED);
			SetCursor(cursor); resizeLow = true;
		}
	}


	void setText(string data = "")
	{
		text = data;
		if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(colbr.color, 1); }
	}

	void setColor(int r1, int g1, int b1)
	{
		color.r = r1; color.g = g1; color.b = b1;
		if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(colbr.color, 1); }
	}

	void setLocation(int x1, int y1)
	{
		local.x = x1; local.y = y1;
		if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(colbr.color, 1); }
	}

	void setSize(int w1, int h1)
	{
		w = w1; h = h1;
		if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(colbr.color, 1); }
	}

	void Mouse(int y, int x)
	{
		if (y >= r.top && y <= r.top + h && x >= r.left && x <= r.left + w)
		{
			if (x > r.left + w - 2 && x < r.left + w + 2)
			{
				HCURSOR cursor = (HCURSOR)LoadImageA(NULL, (LPCSTR)IDC_SIZEWE, IMAGE_CURSOR, 0, 0, LR_SHARED);
				SetCursor(cursor); resizeLow = true;
				return;
			} else if (pressmouse && resizeLow)
			{
				HCURSOR cursor = (HCURSOR)LoadImageA(NULL, (LPCSTR)IDC_SIZEWE, IMAGE_CURSOR, 0, 0, LR_SHARED);
				SetCursor(cursor); resizeLow = true; return;
			}
			resizeLow = false;
			HCURSOR cursor = (HCURSOR)LoadImageA(NULL, (LPCSTR)IDC_IBEAM, IMAGE_CURSOR, 0, 0, LR_SHARED);
			SetCursor(cursor);
		} else {

			if (pressmouse && resizeLow)
			{
				HCURSOR cursor = (HCURSOR)LoadImageA(NULL, (LPCSTR)IDC_SIZEWE, IMAGE_CURSOR, 0, 0, LR_SHARED);
				SetCursor(cursor); resizeLow = true;
			}

		}

	}

	void KeyBoard(string type, int ind)
	{
		if (focus && type == "DOWN")
		{
			IndToChar(ind);
		}
	}


	void repaint()
	{
		InvalidateRect(hwnd, &r, true); show(); setBorder(colbr.color, 1);
	}

	void repaintMove()
	{
		RECT rt;
		int w = GetSystemMetrics(SM_CXSCREEN);
		int h = GetSystemMetrics(SM_CYSCREEN);
		GetWindowRect(hwnd, &rt);
		if (rt.left <= 0 || rt.right >= w || rt.bottom >= h) { InvalidateRect(hwnd, &r, true); show(); setBorder(colbr.color, 1); }
	}
};
