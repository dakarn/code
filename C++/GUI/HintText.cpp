#include "GraphH.h"

class HintText {

private:

	long getTime()
	{
		time_t currtime;
		currtime = time(NULL);
		return currtime * 1000;
	}

	long timeclick;
	struct Location { int x = 0; int y = 0; } local;
	vector<string>text;
	vector<RECT>rectangle;
	vector<bool>undermove;
	int under = -1;
	HDC hdc, mem;
	HWND hwnd;
	RECT r;
	HBITMAP bmpmem;
	HGDIOBJ bmpobj;
	bool threadstatus = false;
	int len = 0, h, w;
    COLORREF colorbr = RGB(90, 90, 90),  body = RGB(254, 254, 254), colortext = RGB(59, 59, 59);
	SIZE weightTextRet(string tex)
	{
		SIZE size;
		GetTextExtentPoint32A(hdc, tex.c_str(), tex.length(), &size);
		return size;
	}

	void showShadow()
	{
		RECT r1 = r;
		GRADIENT_RECT r2; r2.UpperLeft = 0; r2.LowerRight = 1;
		TRIVERTEX vertex[2];
		vertex[0].x = r.left + 8;
		vertex[0].y = r.top + h - 1;
		vertex[0].Red = 80 << 8;
		vertex[0].Green = 80 << 8;
		vertex[0].Blue = 80 << 8;
		vertex[0].Alpha = 0x0000;
		vertex[1].x = r.left + w + 3;
		vertex[1].y = r.top + h + 3;
		vertex[1].Red = 250 << 8;
		vertex[1].Green = 250 << 8;
		vertex[1].Blue = 250 << 8;
		vertex[1].Alpha = 0x0000;
		GradientFill(hdc, vertex, 2, &r2, 1, GRADIENT_FILL_RECT_V);

		vertex[0].x = r.left + w -1;
		vertex[0].y = r.top + 4;
		vertex[0].Red = 140 << 8;
		vertex[0].Green = 140 << 8;
		vertex[0].Blue = 140 << 8;
		vertex[0].Alpha = 0x0000;
		vertex[1].x = r.left + w + 3;
		vertex[1].y = r.top + h + 2;
		vertex[1].Red = 200 << 8;
		vertex[1].Green = 200 << 8;
		vertex[1].Blue = 200 << 8;
		vertex[1].Alpha = 0x0000;
		GradientFill(hdc, vertex, 2, &r2, 1, GRADIENT_FILL_RECT_H);
	}

	void show( string str , int i )
	{
		if (  local.y >= rectangle[i].top && local.y <= rectangle[i].bottom && local.x >= rectangle[i].left && local.x <= rectangle[i].right)
		{
			
			//if (timeclick > getTime() - 1000) return;

			UpdateWindow(hwnd);
			if (hwnd == NULL) return;

			HFONT font = CreateFontA(16, 6, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH, "Arial");
			HGDIOBJ hobj1 = SelectObject(hdc, font);

			SIZE size = weightTextRet(str);
			w = 4 + size.cx + 4; h = 3 + size.cy + 3;

			r.left = local.x; r.top = local.y + 20; r.right = r.left + w; r.bottom = local.y + h + 20;

			RECT cl; GetClientRect(hwnd,&cl);
			if( cl.right < r.right)
			{
				r.left = cl.right - w - 5; r.right = cl.right - 5;
			} else if (cl.bottom < r.bottom)
			{
				r.top = cl.bottom - h - 30; r.bottom = cl.bottom - 30;
			}
	
			mem = CreateCompatibleDC(hdc);
			bmpmem = CreateCompatibleBitmap(hdc, w+3, h+3);
			bmpobj = SelectObject(mem, bmpmem);
			BitBlt(mem, 0, 0, w+3, h+3, hdc, r.left, r.top, SRCCOPY);

			showShadow();

			HBRUSH brush = CreateSolidBrush(body);
			HGDIOBJ hobj = SelectObject(hdc, brush);
			FillRect(hdc, &r, brush);
			SelectObject(hdc, hobj);
			DeleteObject(brush);

			SetBkMode(hdc, TRANSPARENT);
			SetTextColor(hdc, colortext);
			TextOutA(hdc, r.left + 4, r.top + 3, str.c_str(), str.length());
			SelectObject(hdc, hobj1);
			DeleteObject(font);

			HBRUSH  brush1 = CreateSolidBrush(colorbr);
			HGDIOBJ hobj2 = SelectObject(hdc, brush1);
			FrameRect(hdc, &r, brush1);
			SelectObject(hdc, hobj2);
			DeleteObject(brush1);
		}
	}

	static DWORD WINAPI rerenderCaret(void* Param)
	{
		HintText* This = (HintText*)Param;
		return This->threadstart();
	}

	DWORD threadstart()
	{
		while (threadstatus)
		{
			for (int i = 0; i < len; ++i)
			{
				if ( local.y > rectangle[i].top && local.y < rectangle[i].bottom && local.x > rectangle[i].left && local.x < rectangle[i].right)
				{	
					if ( !undermove[i] )
					{
						undermove[i] = true;
						under = i;
						Sleep(500);
						show(text[i], i );
					}
					
				} else if ( undermove[i] && (rectangle[i].left > local.x || rectangle[i].right < local.x || rectangle[i].top > local.y || rectangle[i].bottom < local.y))
				{
					undermove[i] = false;
					if (bmpmem != NULL)
					{
						BitBlt(hdc, r.left, r.top, w+3, h+3, mem, 0, 0, SRCCOPY);
						SelectObject(mem,bmpobj);
						DeleteObject(bmpmem);
						DeleteDC(mem);		
					}	
				}
			}

			Sleep(50);
		}
		return 1;
	}


public:

	void setHWND(HWND hwnd1 = NULL)
	{
		hwnd = hwnd1;
		hdc = GetDC(hwnd);
	}

	HintText()
	{
		
	}

	void add( string str, RECT rect)
	{
		if (len == 0) { threadstatus = true; CreateThread(NULL, NULL, rerenderCaret, (void*)this, NULL, NULL); }
		text.push_back(str);
		undermove.push_back(false);
		rectangle.push_back(rect);
		len = text.size();
	}

	void ObServer( UINT message, WORD y, WORD x )
	{
		switch (message)
		{
		 case WM_MOUSEMOVE:

			local.x = x; local.y = y;

		 break;
		 case WM_LBUTTONDOWN:
			
			 timeclick = getTime();

			 if (bmpmem != NULL)
			 {
				 BitBlt(hdc, r.left, r.top, w+3, h+3, mem, 0, 0, SRCCOPY);
				 SelectObject(mem, bmpobj);
				 DeleteObject(bmpmem);
				 DeleteDC(mem);
			 }

		 break;
		}
	}

	
};