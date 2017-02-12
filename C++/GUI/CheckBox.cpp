#include "GraphH.h"

class CheckBox {


private:

	string label = "";
	vector<string>text;
	vector<bool>enables;
	int w = 0, h = 0 , sizetext = 16 , lenlist = 0;
	COLORREF colbr = RGB(0, 0, 0), colorback = RGB(220, 220, 220), active = RGB(184, 180, 187), colotext = RGB(0, 0, 0);
	struct Location { int x = 0; int y = 0; } local;
	HDC hdc;
	HWND hwnd;
	RECT r;
	vector<void(*)()>funselect, funupselect;
	bool create = false, border = false;
	SIZE weightTextRet(string tex)
	{
		SIZE size;
		GetTextExtentPoint32A(hdc, tex.c_str(), tex.length(), &size);
		return size;
	}


public:

	CheckBox()
	{

	}

	void add(string str)
	{
		text.push_back(str);
		lenlist = text.size();
		if (create) { InvalidateRect(hwnd, &r, true); show(); }
	}

	void add(char *str)
	{
		text.push_back(str);
		lenlist = text.size();
		if (create) { InvalidateRect(hwnd, &r, true); show(); }
	}

	void show()
	{

	}

};