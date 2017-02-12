#include "GraphH.h"
#include <gdiplus.h>
#pragma comment(lib,"Gdiplus.lib")
using namespace Gdiplus;

class Picture {

private:

	int align[3][2];
	string path = "";
	struct Location { int x = 0; int y = 0; } local;
	HDC hdc;
	HWND hwnd;
	RECT r;
	SIZE size;
	bool create = false;
	int w = 0, h = 0;

public:

	Picture( string path )
	{
		Picture::path = path;
	}

	RECT bindToMenu()
	{
		return r;
	}

	void show()
	{
		UpdateWindow(hwnd);
		if (hwnd == NULL) return;
		create = true;
	}

	void load( string path)
	{
		Picture::path = path;
	}

	void setLocation(int x1, int y1)
	{
		local.x = x1; local.y = y1;
		if (create == true) { InvalidateRect(hwnd, &r, true); show(); }
	}

	void setHWND(HWND hwnd1 = NULL)
	{
		hwnd = hwnd1;
		hdc = GetDC(hwnd);
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

	RECT HINT()
	{
		return r;
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