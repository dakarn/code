#include "GraphH.h"

class PopupMenu {


private :

	bool create = false, bindElem = false;
	struct Location { int x = 0; int y = 0; } local;
	COLORREF ColorBorder = RGB(85,85,85), ColorLine= RGB(120,120,120) , ColorText = RGB(0,0,0), ColorMenu = RGB(255,255,255) , ColorStroke = RGB(22,22,22);
	vector<void(*)(int,string)>funopen, funclose, funselect;
	RECT r;
	vector<RECT>bind;
	vector<string>bindtype;
	HDC hdc;
	HWND hwnd;
	int countElementMenu = 0 , w = 180 , h = 0;
	vector<string> listmenutitle , iconbmp , addstroke;
	HBITMAP *bmp = new HBITMAP[40];
	HBITMAP srcbmp;
	HDC *hd_im = new HDC[40];
	HDC mem;
	HGDIOBJ *bit = new HGDIOBJ[40];
	HGDIOBJ objsrc;

	
	void showShadow()
	{
		BLENDFUNCTION bfn;
		bfn.BlendOp = AC_SRC_OVER;
		bfn.BlendFlags = 0;
		bfn.SourceConstantAlpha = 255;
		bfn.AlphaFormat = AC_SRC_ALPHA;

		HDC mem1 = CreateCompatibleDC(hdc);
		HBITMAP bmp1 = CreateCompatibleBitmap(hdc, w-5, 4);
		HGDIOBJ obj = SelectObject(mem1, bmp1);

		RECT r1;
		r1.left = 0;
		r1.top = 0;
		r1.right = 175;
		r1.bottom = 4;

		HBRUSH brush = CreateSolidBrush(RGB(24,24,24));
		HGDIOBJ obj1 = SelectObject(mem1, brush);
		FillRect(mem1, &r1, brush);
		SelectObject(mem1,obj1);
		DeleteObject(brush);

		BitBlt(hdc, r.left+8, r.top+h-1, w-5, 4, mem, 0, 0, SRCCOPY );
		SelectObject(mem1, obj);
		DeleteObject(bmp1);
		DeleteDC(mem1);
		
	}


	void loadBMP(string path, int x, int y , int index)
	{
      
		StretchBlt(hdc, x, y, 16, 16, hd_im[index], 0, 0, 16, 16, SRCCOPY);
		
	}

public:

	void addStroke( COLORREF rgb )
	{
		addstroke.push_back("1");
	}

	void destroy()
	{
		free(bmp);
		DeleteObject( bmp );
	}

	void bindMenu( int item , PopupMenu popup )
	{
		
	}

	void setHWND(HWND hwnd1 = NULL)
	{
		hwnd = hwnd1;
		hdc = GetDC(hwnd);
	}

	void bindToElem( RECT rect, char *type )
	{
		bindElem = true; bind.push_back( rect );
		bindtype.push_back(type);
	}

	PopupMenu(COLORREF text, COLORREF line, COLORREF menucolor, COLORREF border = RGB(140, 140, 140))
	{
		ColorMenu = menucolor; ColorText = text; ColorBorder = border; ColorLine = line;
	}

	PopupMenu()
	{
		
	}

	void add(string title , string icon = "" )
	{
		listmenutitle.push_back( title );
		iconbmp.push_back(icon);
		if( icon != "" )
		{ 
			bmp[countElementMenu] = (HBITMAP)LoadImageA(GetModuleHandle(NULL), (LPCSTR)icon.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			hd_im[countElementMenu] = CreateCompatibleDC(hdc);
			bit[countElementMenu] = SelectObject(hd_im[countElementMenu], bmp[countElementMenu]);
		}
		countElementMenu++;
	}

	void close()
	{
		if (!funclose.empty()) { funclose[0](0,"none"); }
		UpdateWindow(hwnd);
		create = false;
		BitBlt(hdc, local.x, local.y, 180, h, mem, 0, 0, SRCCOPY);
		SelectObject(mem, objsrc);
		DeleteObject(srcbmp);
		DeleteDC(mem);
	}

	void addEventSelect(void(*f)(int,string))
	{
		funselect.push_back( f );
		create = false;
	}

	void addEventClose(void(*f)(int,string))
	{
		funclose.push_back(f);
		create = false;
	}

	void addEventOpen(void(*f)(int,string))
	{
		funopen.push_back(f);
	}

	void show()
	{
		UpdateWindow(hwnd);
		if (hwnd == NULL) return;

		h = listmenutitle.size() * 27;

		r.left = local.x;
		r.top = local.y;
		r.right = r.left + w;
		r.bottom = r.top + h;

		//showShadow();

		HBRUSH brush; brush = CreateSolidBrush(ColorMenu);
		SelectObject(hdc, brush);
		FillRect(hdc, &r, brush);
		DeleteObject(brush);

		setBorder(ColorBorder,1);

		HFONT font = CreateFontA(16, 6, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH, "Times New Roman");
		SelectObject(hdc, font);

		create = true;
		int offseth = 6;
		int  offw = 8;
		for (int i = 0; i < listmenutitle.size(); i++)
		{
			if (iconbmp[i] != "") { offw = 36; loadBMP( iconbmp[i] , r.left + 7 , r.top + offseth , i ); }

			SetBkColor(hdc, ColorMenu);
			SetTextColor(hdc, ColorText);
			TextOutA(hdc, r.left + offw, r.top + offseth, listmenutitle[i].c_str(), listmenutitle[i].length());
			offseth += 27;
		}

		DeleteObject(font);

	}

	void setBorder(COLORREF rgb, int bold = 1)
	{
		RECT r1;
		ColorBorder = rgb;
		HBRUSH brush1; brush1 = CreateSolidBrush(rgb);
		SelectObject(hdc, brush1);
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

		DeleteObject(brush1);
	}

	void offset(int x1, int y1)
	{

	}

	void Mouse(int y, int x)
	{
		if ((y >= r.top && y <= r.top + h) && (x >= r.left && x <= r.left + w))
		{
			
		}
		
	}

	void Click(int y, int x)
	{
		if (y >= r.top && y <= r.top + h && x >= r.left && x <= r.left + w)
		{
			for (int i = 0; i < listmenutitle.size(); i++)
			{
				if ((r.top + (i * 27)) < y && y < (r.top + (i * 27) + 27))
				{	
					 if (!funselect.empty()) { funselect[0](i,listmenutitle[i]); }
					 UpdateWindow(hwnd);
					 BitBlt(hdc, local.x, local.y, 180, h, mem, 0, 0, SRCCOPY);
					 SelectObject(mem, objsrc);
					 DeleteObject(srcbmp);
					 DeleteDC(mem);	
				}
			}

		} else {
			if (create)
			{
				if (!funclose.empty()) { funclose[0](0, "none"); }
				create = false;
				UpdateWindow(hwnd);
				BitBlt(hdc, local.x, local.y, 180, h, mem, 0, 0, SRCCOPY);
				SelectObject(mem, objsrc);
				DeleteObject(srcbmp);
				DeleteDC(mem);
			}
		}
	}


	void RClick(int y, int x)
	{
		if (bindElem && !create)
		{
			int len = bind.size();
			for (int i = 0; i < len; ++i)
			{
				if (y > bind[i].top && y < bind[i].bottom && x > bind[i].left && x < bind[i].right)
				{	
					if (!funopen.empty()) { funopen[0](i,bindtype[i]); }
					UpdateWindow(hwnd);
					h = listmenutitle.size() * 27;
					local.x = x; local.y = y;
					mem = CreateCompatibleDC(hdc);
					srcbmp = CreateCompatibleBitmap(hdc, w, h);
					objsrc = SelectObject(mem, srcbmp);
					BitBlt(mem, 0, 0, w, h, hdc, x, y, SRCCOPY);
					show();
					
				}
			}

		} else if(create){

			if ( y >= r.top && y <= r.bottom && x >= r.left && x <= r.right ) { } else {
				
				if (!funclose.empty()) { funclose[0](0,"none"); }
				UpdateWindow(hwnd);
				create = false;
				BitBlt(hdc, local.x, local.y, w, h, mem, 0, 0, SRCCOPY);
				local.x = x; local.y = y;
				SelectObject(mem, objsrc);
				DeleteObject(srcbmp);
				DeleteDC(mem);
				Sleep(100);
				RClick(y, x);
			}
		}
	}
};