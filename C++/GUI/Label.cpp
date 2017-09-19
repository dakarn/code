#include "GraphH.h"

class Label {

private:

	
	string text = "", font1 = "Arial";
	struct Location { int x = 0; int y = 0; } local;
	bool html = false , create = false , icon = false , br = false;
	HDC hdc , mem;
	HWND hwnd;
	HBITMAP image = NULL;
	HGDIOBJ bmpobj;
	RECT r;
	int offset = 0 , offseth = 0;
	DWORD typetext = FW_BOLD;
	int h = 0, w = 0, heightfont = 16, widthfont = 6;
	COLORREF body = RGB(0, 0, 0), colortext = RGB(0, 0, 0);
	SIZE weightTextRet(string tex)
	{
		SIZE size;
		GetTextExtentPoint32A(hdc, tex.c_str(), tex.length(), &size);
		return size;
	}

	vector<string> split(string text1)
	{
		vector<string>list;
		int start = 0;
		string text = text1;
		
		while (true)
		{
			size_t res1 = text.find_first_of("\n");

			if (res1 == -1) { string pos = text.substr(0, res1); list.push_back(pos); break; }

			string pos = text.substr(0, res1 );
			start = res1 + 1;
			int len = text.length();
			text = text.substr(start, len);
			
			list.push_back(pos);
		}
		return list;
	}

	COLORREF getRGB( string text )
	{
		size_t res = text.find_first_of(",");
		string t = text.substr(0, res);
		res = t.find_first_of(",");
		string t1 = t.substr(0, res);
		string t2 = t.substr(res+1, text.length());

		COLORREF rgb = RGB(stoi(t), stoi(t1), stoi(t2));
		return rgb;
	}

public:

	RECT HINT()
	{
		return r;
	}

	void show()
	{
		UpdateWindow(hwnd);
		if (hwnd == NULL) return;
		create = true;

		SIZE size = weightTextRet(text);

		w = size.cx;
		h = size.cy;

		r.left = local.x; r.top = local.y; r.right = r.left + w; r.bottom = r.top + h;

		SetBkMode(hdc, TRANSPARENT);

		HFONT font = CreateFontA(heightfont, widthfont, 0, 0, typetext, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH, font1.c_str());
		HGDIOBJ hobj1 = SelectObject(hdc, font);
   
		offset = local.x;	

		if (icon)
		{
			bmpobj = SelectObject(mem, image);
			BitBlt(hdc, local.x, local.y, 16, 16, mem, 0, 0, SRCCOPY);
			SelectObject(mem, bmpobj);
			offset += 20;
			r.right += 20;
		}

		isHtml();

		if (br)
		{
			offseth = local.y;
			vector<string>list = split(text); int len = list.size();
			for (int i = 0; i < len; ++i)
			{
				SetTextColor(hdc, colortext);
				TextOutA(hdc, offset, offseth, list[i].c_str(), list[i].length());
				offseth += 15;
			}

		} else {

			if (text != "")
			{
				if (html)
				{
					

				} else {

					SetBkMode(hdc, TRANSPARENT);
					SetTextColor(hdc, colortext);
					TextOutA(hdc, offset, local.y, text.c_str(), text.length());
				}
			}
		}

		SelectObject(hdc, hobj1);
		DeleteObject(font);

	}

	Label()
	{

	}

	Label( string str )
	{
		text = str;

		size_t res = str.find_first_of("\n");
		if (res != -1) {  }
	}

	Label( string str, string bmp = "" )
	{
		if (bmp != "") 
		{ 
			image = (HBITMAP)LoadImageA(GetModuleHandle(NULL), (LPCSTR)bmp.c_str(), IMAGE_BITMAP, 16, 16, LR_LOADFROMFILE);
			if (image != NULL)
			{
				icon = true;
				mem = CreateCompatibleDC(hdc);
			}
		}
		text = str;
		size_t res = str.find_first_of("\n");
		if (res != -1) { br = true; }
	}

	Label( LPCSTR str )
	{
		if (str != "") 
		{
			image = (HBITMAP)LoadImageA(GetModuleHandle(NULL), str, IMAGE_BITMAP, 16, 16, LR_LOADFROMFILE);
			if (image != NULL)
			{
				icon = true;
				mem = CreateCompatibleDC(hdc);
			}
		}
	}

	string getText()
	{
		return text;
	}

	void isHtml()
	{
		
	}

	void setText(string data = "")
	{
		text = data;
		size_t res = data.find_first_of("\n");
		if (res != -1) {  }
		if (create == true) { InvalidateRect(hwnd, &r, true); show(); }
	}

	HBITMAP getIcon()
	{
		return image;
	}

	void setIcon( string bmp )
	{
		if (bmp != "")
		{
			image = (HBITMAP)LoadImageA(GetModuleHandle(NULL), (LPCSTR)bmp.c_str(), IMAGE_BITMAP, 16, 16, LR_LOADFROMFILE);
			if (image != NULL)
			{
				icon = true;
				mem = CreateCompatibleDC(hdc);
			}
		}
	}

	void setColor(COLORREF rgb)
	{
		body = rgb;
		if (create == true) { InvalidateRect(hwnd, &r, true); show(); }
	}

	void setLocation(int x1, int y1)
	{
		local.x = x1; local.y = y1;
		if (create == true) { InvalidateRect(hwnd, &r, true); show(); }
	}

	void setSizeText(int height1 , int width1, string font , DWORD bold )
	{
		heightfont = height1; widthfont = width1; font1 = font; typetext = bold;
		if (create == true) { InvalidateRect(hwnd, &r, true); show(); }
	}

	void setHWND(HWND hwnd1 = NULL)
	{
		hwnd = hwnd1;
		hdc = GetDC(hwnd);
	}

	void setTextColor(COLORREF rgb)
	{
		colortext = rgb;
		if (create == true) { InvalidateRect(hwnd, &r, true); show(); }
	}

	void hide()
	{
		InvalidateRect(hwnd, &r, true);
		UpdateWindow(hwnd);
	}

	void destroy()
	{
		InvalidateRect(hwnd, &r, true);
		UpdateWindow(hwnd);
	}

	void repaint()
	{
		InvalidateRect(hwnd, &r, true); show();
	}

	void repaintMove()
	{
		RECT rt;
		int w = GetSystemMetrics(SM_CXSCREEN);
		int h = GetSystemMetrics(SM_CYSCREEN);
		GetWindowRect(hwnd, &rt);
		if (rt.left <= 0 || rt.right >= w || rt.bottom >= h) { InvalidateRect(hwnd, &r, true); show(); }
	}
};