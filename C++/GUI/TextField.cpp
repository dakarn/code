#include "GraphH.h"


class TextField {

private:
	vector<string(*)(int)>funotherlang;
	vector<void(*)(int)>funup, fundown, funchange;
	vector<void(*)(bool)>funfocus;
	string text = "", textshow = "" , texthint = "";
	RECT r;
	bool resizeLow = false , pressmouse = false;
	int offsetsimbol = 0;
	bool threadstatus = false , resize = false;
	struct Color { int r = 255; int g = 255; int b = 255; } color;
	struct Colortext { int r = 0; int g = 0; int b = 0; } colortext;
	struct Location { int x = 0; int y = 0; } local;
	int h, w, begin = 0, ytext, paddingleft = 0, xtext = 0, offsetcaret = 3;
	bool status = true, create = false, bigsimbol = false, specsimbol = false, maxlength = 4 , caps = false;
	bool movecur = false;
	long timekey = 0;
	HDC hdc;
	HWND hwnd;
	SIZE size;
	LPDWORD th;
	struct ColorBorder { COLORREF color = RGB(0,0,0); } colbr;
	COLORREF focuscolor = RGB(255,0,0), colorcaret = RGB(0,0,0);
	HANDLE thread = NULL;
	bool focus = false;
	SIZE weightTextRet(string tex)
	{
		SIZE size;
		GetTextExtentPoint32A(hdc, tex.c_str(), tex.length(), &size);
		return size;
	}

	SIZE weightTextRet(char tex)
	{
		SIZE size;
		GetTextExtentPoint32A(hdc, (LPCSTR)&tex, sizeof(tex), &size);
		return size;
	}

	long getTime()
	{
		time_t currtime;
		currtime = time(NULL);
		return currtime*1000;
	}

	void BackText()
	{
		if (offsetcaret >= w - 15) 
		{
			
			int offsetend = -1;
			string str = "";
			int offset = 0;
			for (int i = text.length() - 1; i >= 0; --i)
			{
				SIZE z1 = weightTextRet(text[i]); offset += z1.cx; str += text[i];
				if (offset >= w - 5) { offsetend = i; str += text[i]; break; }
			}

			
			if (offsetend - 1 > 0) 
			{
				reverse(str.begin(), str.end());
				textshow = text[offsetend - 1] + str.substr(0, str.length() - 1);
				text = text.substr(0, text.length() - 1);
				
			} else {

				offsetcaret -= 29; 
				text = text.substr(0, text.length() - 1);
				textshow = textshow.substr(0, textshow.length() - 1);
			}

		} else {

			text = text.substr(0, text.length() - 1);
			textshow = textshow.substr(0, textshow.length() - 1);
		}
		
		if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(focuscolor, 1); }
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
		case 219: ch = "Õ"; break;case 220: ch = "\\"; break;case 221: ch = "Ú"; break;case 222: ch = "Ý";case 192: ch = "¨";
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

	string EngNum( int ind )
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

	string RusNum( int ind )
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
		case 219: ch = "õ"; break;case 220: ch = "\\"; break;case 221: ch = "ú"; break;case 222: ch = "ý";case 192: ch = "¸";
		}
		return ch;
	}

	void IndToChar( int ind )
	{
		caps = false;
		timekey = getTime();
		string ch = "";
		int lang = LOWORD(GetKeyboardLayout(0));
		if (ind == 16) { bigsimbol = true; }

		if (lang == 1033)
		{
			ch = EngNum(ind); 
			if (GetKeyState(VK_CAPITAL) == 1 && bigsimbol) { caps = true; ch = EngNum(ind); } else
			if (bigsimbol) { ch = UPEngNum(ind); } else 
			if (GetKeyState(VK_CAPITAL)) { caps = true; ch = UPEngNum(ind); }
		}
		else if (lang == 1049) 
		{
			ch = RusNum(ind); if (GetKeyState(VK_CAPITAL) == 1) { ch = UPRusNum(ind); }
			if (bigsimbol) { ch = UPRusNum(ind); }
		}

		if (ind == 8) {	BackText(); return; }
		if (ind == 37) { Movecursor(0); return; }
		if (ind == 39) { Movecursor(1); return; }
		
		text += ch; textshow += ch; offsetsimbol++;

		if (offsetcaret >= w - 15)
		{	
			textshow = textshow.substr(1,text.length()); 
			
		}

		if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(focuscolor, 1); }
	}


	void Movecursor( int type )
	{
		
		if (type == 0) {
			
			if (offsetsimbol > 0) {

				SIZE z = weightTextRet(textshow[offsetsimbol - 1]);
				offsetcaret -= z.cx+3;
				offsetsimbol--;
				if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(focuscolor, 1); }
			}
		} else if (type == 1) { 

			if (offsetsimbol < textshow.length()) {
				SIZE z = weightTextRet(textshow[offsetsimbol]);
				offsetsimbol++;
				offsetcaret += z.cx+3;
				if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(focuscolor, 1); }
			}
		}
	}

	void showCaret( )
	{
		HFONT font = CreateFontA(23, 6, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH, "Times New Roman");
		HGDIOBJ hobj = SelectObject(hdc, font);
		string text1 = "|";
		SIZE zz = weightTextRet(text1);
		double ytext1 = (h - zz.cy) / 2;
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, colorcaret);
		TextOutA(hdc, r.left+offsetcaret, (r.top + (int)round(ytext1)) - 2, text1.c_str(), text1.length());
		SelectObject(hdc, hobj);
		DeleteObject(font);
	}

	void UPind( int ind )
	{
		if (ind == 16) { bigsimbol = false; }
	}

public:
	
	void setPadding( RECT r )
	{

	}
	
	void setFocusColor( COLORREF rgb )
	{
		focuscolor = rgb;
	}

	void setLabel(string text)
	{
		HFONT font = CreateFontA(17, 6, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH, "Times New Roman");
		HGDIOBJ hobj = SelectObject(hdc, font);
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(colortext.r, colortext.g, colortext.b));
		TextOutA(hdc, r.left + 1, r.top - 18, text.c_str(), text.length());
		SelectObject(hdc, hobj);
		DeleteObject(font);
	}


	void setHWND(HWND hwnd1 = NULL)
	{
		hwnd = hwnd1;
		hdc = GetDC(hwnd);
	}
	
	TextField( string text1 = "" )
	{
	  
	   text = text1;
	   textshow = text1;
	   
	}

	void show()
	{

		UpdateWindow(hwnd);
		if (hwnd == NULL) return;

		r.left = local.x; r.top = local.y; r.right = r.left + w; r.bottom = r.top + h;

		HBRUSH brush = CreateSolidBrush(RGB(color.r, color.g, color.b));
		HGDIOBJ hobj = SelectObject(hdc, brush);
		FillRect(hdc, &r, brush);
		SelectObject(hdc, hobj);
		DeleteObject(brush);

		HFONT font = CreateFontA(16, 6, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH, "Arial");
		HGDIOBJ hobj1 = SelectObject(hdc, font);

		SIZE zz = weightTextRet(textshow);

		create = true;

		ytext = (h - zz.cy) / 2;
		xtext = zz.cx;

		SetBkMode(hdc, TRANSPARENT);

		if (textshow != "")
		{
			if (offsetcaret <= w - 15)
			{
				offsetcaret = zz.cx + 7;
			}
		}
		else { 

			if (!focus && texthint != "")
			{
				SetTextColor(hdc, RGB(188, 188, 188));
				TextOutA(hdc, r.left + 9, r.top + (int)round((h-weightTextRet(texthint).cy)/2), texthint.c_str(), texthint.length());
			}

			offsetcaret = 7;
		}

		SetTextColor(hdc, RGB(colortext.r, colortext.g, colortext.b));
		TextOutA(hdc, r.left + 7, r.top + (int)round(ytext), textshow.c_str(), textshow.length());
		SelectObject(hdc, hobj1);
		DeleteObject(font); 
		if (focus) { showCaret(); }

		RECT r1; r1.left = r.left; r1.top = r.top; r1.right = r1.left + 6; r1.bottom = r.bottom;
		brush = CreateSolidBrush(RGB(color.r, color.g, color.b));
		HGDIOBJ hobj5 = SelectObject(hdc, brush);
		FillRect(hdc, &r1, brush);
		SelectObject(hdc, hobj5);
		DeleteObject(brush);
	
	}

	void setHint( string hint )
	{
		texthint = hint;
	}

	RECT HINT()
	{
		return r;
	}

    static DWORD WINAPI rerenderCaret( void* Param )
	{
		TextField* This = (TextField*)Param;
		return This->threadstart();
	}

	DWORD threadstart()
	{
		while (threadstatus)
		{
		    time_t tm;
			tm = time(NULL)*1000;

			if (focus && timekey < tm - 1000)
			{
				string text1 = "|";
				HFONT font = CreateFontA(23, 6, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH, "Times New Roman");
				HGDIOBJ hobj = SelectObject(hdc, font);
				SIZE zz = weightTextRet(text1); double ytext2 = (h - zz.cy) / 2;
				RECT r1; r1.left = r.left + offsetcaret+1; r1.right = r1.left + 2; r1.top = r.top + 3; 
				r1.bottom = r.top + h - 4;
				
				
				SetBkMode(hdc, TRANSPARENT);
				SetTextColor(hdc, colorcaret);
				TextOutA(hdc, r.left + offsetcaret, (r.top + (int)round(ytext2)) - 2, text1.c_str(), text1.length());
				SelectObject(hdc, hobj);
				DeleteObject(font);

				Sleep(500);

				r1.left = r.left + offsetcaret + 1; r1.right = r1.left + 2; r1.top = r.top + 3;
				r1.bottom = r.top + h - 4;
				
				InvalidateRect(hwnd, &r1, true); UpdateWindow(hwnd);
				HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
				HGDIOBJ hobj1 = SelectObject(hdc, brush);
				FillRect(hdc, &r1, brush);
				SelectObject(hdc, hobj1);
				DeleteObject(brush);
				
			}
			Sleep(500);
		}
		return 1;
	}

	void setBorder(COLORREF rgb, int bold = 1 )
	{
		RECT r1;
		HBRUSH brush1; brush1 = CreateSolidBrush(rgb);
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

	string getText()
	{
		return text;
	}

	void setText(string data = "")
	{
		text = data;
		textshow = data;
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

	void setFocus()
	{
		if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(focuscolor, 1); }

		CreateThread(NULL, NULL, rerenderCaret, (void*)this, NULL, NULL);
		
	}


	void Click(string type,WORD y, WORD x)
	{
		
		if (y >= r.top && y <= r.top + h && x >= r.left && x <= r.left + w)
		{
			if (type == "DOWN")
			{
				if (!focus) { focus = true; threadstatus = true; setFocus(); }

			} else if (resizeLow && type == "UP")
			{
				pressmouse = false;
				resizeLow = false;
				if ( x - r.left >= 40) { w = x - r.left; }
				resizeLow = false;
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
					timekey = 0;
					threadstatus = false;
					focus = false;
					if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(colbr.color, 1); }
					return;
				}
			} else if ( resizeLow && type == "UP")
			{
				pressmouse = false;
				w = x - r.left;
				resizeLow =! resizeLow;
				if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(focuscolor, 1); }	
			}
		}

		if ( resizeLow && x > r.left + w - 2 && x < r.left + w + 2)
		{
			pressmouse = true;
			HCURSOR cursor = (HCURSOR)LoadImageA(NULL, (LPCSTR)IDC_SIZEWE, IMAGE_CURSOR, 0, 0, LR_SHARED);
			SetCursor(cursor); resizeLow = true;
		}

	}

	void addEventKeyUp( void(*f)(int) )
	{
		funup.push_back(f);
	}

	void addEventKeyDown( void(*f)(int) )
	{
		fundown.push_back(f);
	}

	void addEventChange(void(*f)(int))
	{
		funchange.push_back(f);
	}

	void addEventFocus( void(*f)(bool) )
	{
		funfocus.push_back(f);
	}

	void KeyBoard( string type, int ind )
	{
		if( focus && type == "DOWN" )
		{
			IndToChar( ind );

		} else if (focus && type == "UP")
		{
			UPind(ind);
		}
	}

	void Mouse(int y, int x)
	{
		if (y >= r.top && y <= r.top + h && x >= r.left && x <= r.left + w)
		{
			if ( x > r.left + w - 2 && x < r.left + w + 2)
			{
				
					HCURSOR cursor = (HCURSOR)LoadImageA(NULL, (LPCSTR)IDC_SIZEWE, IMAGE_CURSOR, 0, 0, LR_SHARED);
					SetCursor(cursor);
				
				resizeLow = true;
				return;
			} else if ( pressmouse && resizeLow )
			{
				
					HCURSOR cursor = (HCURSOR)LoadImageA(NULL, (LPCSTR)IDC_SIZEWE, IMAGE_CURSOR, 0, 0, LR_SHARED);
					SetCursor(cursor);
				
				resizeLow = true; return;
			}
			resizeLow = false;
			
				HCURSOR cursor = (HCURSOR)LoadImageA(NULL, (LPCSTR)IDC_IBEAM, IMAGE_CURSOR, 0, 0, LR_SHARED);
				SetCursor(cursor);
			
			return;
		} else {
		
			if (pressmouse && resizeLow)
			{
				
					HCURSOR cursor = (HCURSOR)LoadImageA(NULL, (LPCSTR)IDC_SIZEWE, IMAGE_CURSOR, 0, 0, LR_SHARED);
					SetCursor(cursor); resizeLow = true;
				
			}
		
		}

	}

	void setMaxLength( int max )
	{
		maxlength = max;
	}

	void addOtherLangFun( string(*f)(int))
	{
		
	}

	void reSizeMouse( bool status )
	{
		resize = status;
	}

	void unFocus()
	{
			pressmouse = false;
			resizeLow = false;

			if (focus)
			{
				timekey = 0;
				threadstatus = false;
				focus = false;
				if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(colbr.color, 1); }
				return;
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

