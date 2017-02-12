#include "GraphH.h"


class Toggle {


private:
	string text;
	HDC hdc;
	HWND hwnd;
	RECT r;
	bool active = true;
	SIZE sz;
	int h = 0, w = 0;
	bool create = false;
	bool enabled = true;
	vector<void(*)(bool)>funrun;
	SIZE weightText(string tex)
	{
		SIZE size;
		GetTextExtentPoint32A(hdc, tex.c_str(), tex.length(), &size);
		return size;
	}

	struct Colortext { int r = 0; int g = 0; int b = 0; } colortext;
	struct Location { int x = 0; int y = 0; } local;
	COLORREF colbr = RGB(160, 160, 160);
	COLORREF dis = RGB(230, 230, 230), enb = RGB(100, 100, 100);

public:

	Toggle()
	{

	}

	bool getStatus()
	{
		return active;
	}

	void setStatus( bool status )
	{
		active = status;
	}

	void setColorDisEnb( COLORREF rgb , COLORREF enb1 )
	{
		dis = rgb; enb = enb1;
	}

	void show()
	{
		UpdateWindow(hwnd);
		if (hwnd == NULL) return;

		sz = weightText(text);

		if ( !create ) {
			h = sz.cy + 10;
			w = sz.cx + 16;
		}

		r.left = local.x;
		r.top = local.y;
		r.right = local.x + w;
		r.bottom = local.y + h;

		COLORREF colorcur;
		if (active) { colorcur = enb; } else { colorcur = dis; }

		HBRUSH brush = CreateSolidBrush( colorcur );
		SelectObject(hdc, brush);
		FillRect(hdc, &r, brush);
		DeleteObject(brush);

		HFONT font = CreateFontA(16, 6, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH, "Times New Roman");
		SelectObject(hdc, font);

		create = true;

		SetBkColor(hdc, colorcur );
		SetTextColor(hdc, RGB(colortext.r, colortext.g, colortext.b));
		TextOutA(hdc, r.left + 8, r.top + 5, text.c_str(), text.length());
		DeleteObject(font);


	}

	void setText(string data = "")
	{
		sz = weightText(text);
		text = data;
		h = sz.cy + 10;
		w = sz.cx + 16;
		if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(colbr, 1); }
	}

	void setLocation(int x1, int y1)
	{
		local.x = x1; local.y = y1;
		if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(colbr, 1); }
	}

	void setHWND(HWND hwnd1 = NULL)
	{
		hwnd = hwnd1;
		hdc = GetDC(hwnd);
	}

	void setTextColor(int r1, int g1, int b1)
	{
		colortext.r = r1; colortext.g = g1; colortext.b = b1;
		if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(colbr, 1); }
	}

	void setBorder(COLORREF rgb, int bold = 1)
	{
		RECT r1;
		colbr = rgb;
		HBRUSH brush1; brush1 = CreateSolidBrush(rgb);
		SelectObject(hdc, brush1);
		r1.left = local.x;
		r1.right = r1.left + w;
		r1.top = local.y;
		r1.bottom = r1.top + bold;
		FillRect(hdc, &r1, brush1);

		r1.left = local.x;
		r1.top = local.y + h - bold;
		r1.right = r.left + w;
		r1.bottom = r.top + h;
		FillRect(hdc, &r1, brush1);

		r1.left = local.x;
		r1.top = local.y;
		r1.right = r.left + bold;
		r1.bottom = local.y + h;
		FillRect(hdc, &r1, brush1);

		r1.left = local.x + w - bold;
		r1.top = local.y;
		r1.right = r1.left + bold;
		r1.bottom = r.top + h;
		FillRect(hdc, &r1, brush1);

		DeleteObject(brush1);
	}

	void addEventChange(void (*f)(bool))
	{
		funrun.push_back( f );
	}

	void Click(int y, int x)
	{
		if ( (y >= r.top && y <= r.top + h) && (x >= r.left && x <= r.left + w))
		{
			if (active) { active = false; } else { active = true; }
			if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(colbr, 1); }
			if (!funrun.empty()) { funrun[0]( active ); }
		}
	}
	
	RECT HINT()
	{
		return r;
	}

	void hide()
	{
		InvalidateRect(hwnd, &r, true);
	}

	void setDisabled()
	{
		enabled = false;
	}

	void setEnabled()
	{
		enabled = true;
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
