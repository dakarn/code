#include "GraphH.h"

class Button {


private: 
	    vector<void(*)()>eventclick, eventmove, eventdbl;
	    char * gradtype = "endtostart", *gradhv = "v";
	    COLORREF gradstart = RGB(0, 0, 0), gradend = RGB(0, 0, 0);
		string text;
		TRIVERTEX vertex[2];
		HDC hdc;
		HWND hwnd;
		RECT r;
		SIZE size;
		bool status = true, UnderMouse = false,cursorhover = false, create = false, clevent = false, WasUnder = false , press = false;
		int w = 0, h = 0, effect = -1 , border = 0;
		bool icon1 = false, enabled = true, mouse = false;
		int align[3][2];
		void weightText( string tex )
		{
			GetTextExtentPoint32A( hdc , tex.c_str() , tex.length() , &size );
		}
		struct Color { int r; int g; int b; } color;
		HBITMAP bmp;
		HDC hd_im;
		HGDIOBJ bit;
		
		void showGradient()
		{
			GRADIENT_RECT r; r.UpperLeft = 0; r.LowerRight = 1;
			GradientFill(hdc, vertex, 2, &r, 1, (strcmp(gradhv, "v") == 0 ? GRADIENT_FILL_RECT_V : GRADIENT_FILL_RECT_H));
		}

		struct Colortext { int r = 0; int g = 0; int b = 0; } colortext;
		struct Location { int x = 0; int y = 0; } local;
		struct ColorBorder { COLORREF color; } colbr;

public:

	
	
	Button( )
	{
		
	}

	void setIcon( string path, int width , int height )
	{
		icon1 = true;
		h = height; w = width;
		bmp = (HBITMAP)LoadImageA(GetModuleHandle(NULL), (LPCSTR)path.c_str(), IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
		hd_im = CreateCompatibleDC(hdc);
		bit = SelectObject(hd_im, bmp);

		if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(colbr.color, 1); }
	}

	void show()
	{
		UpdateWindow(hwnd);
		if (hwnd == NULL) return;
		create = true;

		HFONT font = CreateFontA(16, 6, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH, "Times New Roman");
		HGDIOBJ hobj1 = SelectObject(hdc, font);

		weightText(text);
		if (w == 0 || h == 0)
		{
			w = 6 + size.cx + 6;
			h = 6 + size.cy + 6;
		}

		r.left = local.x; 
		r.top = local.y;
		r.right = r.left + w;
		r.bottom = r.top + h;

		if ( effect == 0  )
		{
			showGradient();

		} else {

			if (!icon1)
			{
				HBRUSH brush; brush = CreateSolidBrush(RGB(color.r, color.g, color.b));
				HGDIOBJ hobj = SelectObject(hdc, brush);
				FillRect(hdc, &r, brush);
				SelectObject(hdc, hobj);
				DeleteObject(brush);
			} else {

				BitBlt(hdc, r.left, r.top, w, h, hd_im, 0, 0, SRCCOPY);
			}
		}


		double xtext = (w - size.cx)/2;
		double ytext = (h - size.cy)/2;

		SetBkMode(hdc, TRANSPARENT);
		SetTextColor( hdc , RGB(colortext.r, colortext.g, colortext.b));
		
		TextOutA(hdc, r.left + (int)round(xtext), r.top + (int)round(ytext),text.c_str(), text.length());
		SelectObject(hdc, hobj1);
		DeleteObject(font);
	}

	string getText()
	{
		return text;
	}

	void setText( string data = "" )
	{
		text = data;
		if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(colbr.color,1); }
	}

	void setColor( int r1, int g1, int b1 )
	{
		color.r = r1; color.g = g1; color.b = b1;
		if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(colbr.color, 1); }
	}

	void setLocation( int x1, int y1 )
	{
		local.x = x1; local.y = y1;
		if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(colbr.color, 1); }
	}

	void setSize( int w1 , int h1 )
	{
		w = w1; h = h1;
		if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(colbr.color, 1); }
	}

	void setHWND( HWND hwnd1 = NULL )
	{
		hwnd = hwnd1;
		hdc = GetDC(hwnd);
	}

	void setTextColor(int r1, int g1, int b1)
	{
		colortext.r = r1; colortext.g = g1; colortext.b = b1;
		if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(colbr.color, 1); }
	}

	void setBorder( COLORREF rgb , int bold = 1 )
	{
		border = 1;
		RECT r1;
		colbr.color = rgb;
		HBRUSH brush1 = CreateSolidBrush(rgb);
		HGDIOBJ hobj = SelectObject(hdc, brush1);
		r1.left = local.x;
		r1.top = local.y;
		r1.right = r.left+w;
		r1.bottom = r.top+bold;
		FillRect(hdc, &r1, brush1);

		r1.left = local.x;
		r1.top = local.y+h-bold;
		r1.right = r.left + w;
		r1.bottom = r.top+h;
		FillRect(hdc, &r1, brush1);

		r1.left = local.x;
		r1.top = local.y;
		r1.right = r.left + bold;
		r1.bottom = r.top + h;
		FillRect(hdc, &r1, brush1);

		r1.left = local.x+w-bold;
		r1.top = local.y;
		r1.right = r.left + w;
		r1.bottom = r.top + h;
		FillRect(hdc, &r1, brush1);

		SelectObject(hdc, hobj);
		DeleteObject(brush1);
	}

	void bindWindow( string r )
	{
		if (r == "bottom::left")
		{
			align[0][0] = 1;
			align[0][1] = 0;

		} else if (r == "bottom::right")
		{
			align[0][1] = 1;
			align[0][0] = 0;

		} else if (r == "top::left")
		{
			align[1][0] = 1;
			align[1][1] = 0;

		}
		else if (r == "top::right")
		{
			align[1][1] = 1;
			align[1][0] = 0;

		} else if (r == "center")
		{
			align[3][0] = 1;
		}
	}

	RECT HINT()
	{
		return r;
	}

	void addEventClick( void(*f)())
	{
		eventclick.push_back(f);
	}

	void Click( string event , int y , int x )
	{
		if (!status)
		{
			press = false;
			if (r.left > x || r.right < x || r.top > y || r.top + h < y) { WasUnder = false; if (effect == -1) { color.r = color.r - 30; color.g = color.g - 30; color.b = color.b - 30; } }
			if (!mouse) { if (effect == -1) { color.r = color.r - 30; color.g = color.g - 30; color.b = color.b - 30; } }
			if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(colbr.color, 1); } status = true;
		}

		if (status && (y >= r.top && y <= r.top + h) && (x >= r.left && x <= r.left + w))
		{
			size_t res = event.find_first_of("#");

			if (res != string::npos)
			{
				string pos = event.substr(res + 1, event.length());
				if (pos == "up")
				{
					press = false;
					status = true;
					if (cursorhover)
					{
						HCURSOR cursor = (HCURSOR)LoadImageA(NULL, (LPCSTR)IDC_HAND, IMAGE_CURSOR, 0, 0, LR_SHARED); SetCursor(cursor);
				    }
					
					if (!eventclick.empty()) { eventclick[0](); }

				} else if (pos == "down")
				{
					press = true;
					if (cursorhover)
					{
						HCURSOR cursor = (HCURSOR)LoadImageA(NULL, (LPCSTR)IDC_HAND, IMAGE_CURSOR, 0, 0, LR_SHARED); SetCursor(cursor);
					}
					if (!mouse) { if (effect == -1) { color.r = color.r + 30; color.g = color.g + 30; color.b = color.b + 30; } }
					status = false;
					if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(colbr.color, 2); }
				}

			}
		}
	}

	void addEventMouse( void(*f)())
	{
		mouse = true;
		eventmove.push_back(f);
	}


	RECT getRECT()
	{
		return r;
	}

	void Mouse( int y , int x )
	{
		if (mouse)
		{
	
			if ( !UnderMouse && y >= r.top && y <= r.top + h && x >= r.left && x <= r.left + w)
			{
				UnderMouse = true;
				WasUnder = true;
				
				if (effect == -1) { color.r = color.r + 30; color.g = color.g + 30; color.b = color.b + 30; }
				if ( create ) { InvalidateRect(hwnd, &r, true); show(); setBorder(colbr.color, 1); }
			    
				  
			} else if( r.left > x || r.right < x || r.top > y || r.top + h < y )
			{
				UnderMouse = false;
				
				if ( !press && WasUnder)
				{
					WasUnder = false; if (effect == -1) { color.r = color.r - 30; color.g = color.g - 30; color.b = color.b - 30; }
					if (create) { InvalidateRect(hwnd, &r, true); show(); setBorder(colbr.color, 1); }
				}
			}
			else if (cursorhover)
			{
				if (y >= r.top && y <= r.top + h && x >= r.left && x <= r.left + w)
				{
					HCURSOR cursor = (HCURSOR)LoadImageA(NULL, (LPCSTR)IDC_HAND, IMAGE_CURSOR, 0, 0, LR_SHARED);
					SetCursor(cursor);
				}
			}
			
		}
	}

	void DBLClick( int y, int x)
	{
	}

	void destroy()
	{
		InvalidateRect( hwnd , &r , true );
		UpdateWindow(hwnd);
		if (icon1) 
		{
			DeleteObject(bit);
			DeleteDC(hd_im);
			DeleteObject(bmp);
		}
	}

	void addEventDBLClick( void(*f)() )
	{
		eventdbl.push_back(f);
	}

	RECT bindToMenu()
	{
		return r;
	}

	void setDisabled( )
	{
		enabled = false;
	}

	void setEnabled( )
	{
		enabled = true;
	}


	void UnGradient()
	{
		effect = -1;
	}

	void setEffectGradient(COLORREF start, COLORREF end, char *type, char *gradhv)
	{
		gradstart = start;  gradend = end; effect = 0; gradtype = type; Button::gradhv = gradhv;
		if (strcmp(gradtype, "endtostart") == 0)
		{
			vertex[0].x = local.x;vertex[0].y = local.y;vertex[0].Red = GetRValue(gradstart) << 8;vertex[0].Green = GetGValue(gradstart) << 8;
			vertex[0].Blue = GetBValue(gradstart) << 8;vertex[0].Alpha = 0x0000;
			vertex[1].x = local.x + w;vertex[1].y = local.y + h;vertex[1].Red = GetRValue(gradend) << 8;
			vertex[1].Green = GetGValue(gradend) << 8;vertex[1].Blue = GetBValue(gradend) << 8;vertex[1].Alpha = 0x0000;
		}
		else if (strcmp(gradtype, "starttoend") == 0)
		{
			vertex[0].x = local.x;vertex[0].y = local.y;vertex[0].Red = GetRValue(gradend) << 8;
			vertex[0].Green = GetGValue(gradend) << 8;vertex[0].Blue = GetBValue(gradend) << 8;vertex[0].Alpha = 0x0000;
			vertex[1].x = local.x + w;vertex[1].y = local.y + h;vertex[1].Red = GetRValue(gradstart) << 8;
			vertex[1].Green = GetGValue(gradstart) << 8;vertex[1].Blue = GetBValue(gradstart) << 8;vertex[1].Alpha = 0x0000;
		}

		if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(colbr.color, 1); }
	}

	void setCursorHover( bool data )
	{
		cursorhover = data;
	}

	void DragAndDrop()
	{

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
		GetWindowRect(hwnd,&rt);
		if (rt.left <= 0 || rt.right >= w || rt.bottom >= h) { InvalidateRect(hwnd, &r, true); show(); setBorder(colbr.color, 1); }
	}

	void ObBinding()
	{
		RECT rt1;
		GetWindowRect(hwnd, &rt1);
		if (align[0][0] == 1) { setLocation(15, rt1.bottom - rt1.top - h - 50); } else
		if (align[0][1] == 1) { setLocation(rt1.right-rt1.left-w-30, rt1.bottom-rt1.top-h-50); } else
		if (align[1][0] == 1) { setLocation(15, 10); } else
		if (align[1][1] == 1) { setLocation(rt1.right - rt1.left - w - 30, 10); } else
		if (align[3][0] == 1) { setLocation((rt1.right - rt1.left - w) / 2, (rt1.bottom - rt1.top - h) / 2); }
				
	}
};



