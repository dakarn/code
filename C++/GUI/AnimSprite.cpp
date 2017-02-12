#include "GraphH.h" 

class Animate {

private:

	int w, h;
	struct Location { int x = 0; int y = 0; } local;
	HDC hdc;
	HWND hwnd;
	RECT r;
	HBITMAP *bmp = new HBITMAP[200];
	HDC *hdim = new HDC[200];
	HGDIOBJ *bit = new HGDIOBJ[200];
	vector<int>savespeed;
	bool create = false;

public:

	void setHWND(HWND hwnd1 = NULL)
	{
		hwnd = hwnd1;
		hdc = GetDC(hwnd);
	}


	void setWidth()
	{

	}

	void setHeight()
	{

	}

	void add( string path , int speed )
	{

	}

	void pause()
	{

	}

	void run()
	{

	}

	void setLocation(int x1, int y1)
	{
		local.x = x1; local.y = y1;
	}

	void del()
	{

	}


};