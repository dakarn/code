#include "GraphH.h"
#include <gdiplus.h>
#pragma comment(lib,"Gdiplus.lib")
using namespace Gdiplus;

class Window {

private:

	COLORREF gradstart, gradend;
	string path = "";
	HDC src , hdc;
	HBITMAP bm;
	HGDIOBJ obj;
	HWND hwnd;
	bool selfhwnd = false , fullscreen = false , gradient = false;
	RECT rt1, rtclient;
	int hWindow, wWindow;
	string typefrm;
	ULONG_PTR token;
	GdiplusStartupInput input;
	Image *bg = NULL;

	void repaintPicture()
	{
		if (typefrm == "jpg")
		{
			setBackgroundPictureJPEG((LPCWSTR)path.c_str());
		} 
		else if (typefrm == "png")
		{
			setBackgroundPicturePNG((LPCWSTR)path.c_str());
		} else 
		if (typefrm == "bmp")
		{
			setBackgroundPictureJPEG((LPCWSTR)path.c_str());
		}
	}

	void windowtoMemory()
	{
		GetWindowRect(hwnd, &rt1);
		src = CreateCompatibleDC(hdc);
		bm = CreateCompatibleBitmap(hdc, rt1.right - rt1.left, rt1.bottom - rt1.top);
		obj = SelectObject(src, bm);
		BitBlt(src, 0, 0, rt1.right - rt1.left, rt1.bottom - rt1.top, hdc, 0, 0, SRCCOPY);
	}

	void memorytoWindow()
	{
		BitBlt(hdc, 0, 0, rt1.right - rt1.left, rt1.bottom - rt1.top, src, 0, 0, SRCCOPY);
		SelectObject(src, obj);
		DeleteObject(bm);
		DeleteObject(obj);
		DeleteDC(src);
	}

	void DeleteMem()
	{
		if (obj != NULL)
		{
			DeleteObject(bm);
			DeleteObject(obj);
			DeleteDC(src);
		}
	}

	void EventSIZE()
	{
		GetWindowRect(hwnd, &rt1);
		if (!gradient) { repaintPicture(); }
	}

public:

	Window()
	{
		GdiplusStartup(&token, &input, 0);
	}

	void setSize( int w , int h )
	{

	}

	void setLocation( int y , int x )
	{

	}

	void HWND( HWND hwnd1)
	{
		hwnd = hwnd1;
		hdc = GetDC( hwnd );
	}

	void setTitle( char *text )
	{
		SetWindowTextA( hwnd , text );
	}


	void setColorBackground()
	{

	}

	void setBackgroundPictureBMP( string path )
	{
		Window::path = path;
		GetWindowRect(hwnd, &rt1);
		HBITMAP bmp = (HBITMAP)LoadImageA(GetModuleHandle(NULL), (LPCSTR)path.c_str(), IMAGE_BITMAP, rt1.right - rt1.left, rt1.bottom - rt1.top, LR_LOADFROMFILE);
		HDC hd_im = CreateCompatibleDC(hdc);
		HGDIOBJ bit = SelectObject(hd_im, bmp);
		BitBlt(hdc, 0, 0, rt1.right - rt1.left, rt1.bottom - rt1.top, hd_im, 0, 0 , SRCCOPY);
		SelectObject(hd_im, bit);
		DeleteObject(bmp);
		DeleteDC(hd_im);
		typefrm = "bmp";
	}

	void setIconTitle()
	{

	}

	void DeleteBkgPicture()
	{

	}

	void setBackgroundPictureJPEG(LPCWSTR path)
	{
		GetWindowRect(hwnd, &rt1);
		typefrm = "jpg";
		Window::path = *path;
		{
			if (bg == NULL)
			{
				GUID guidFileFormat; bg = new Image(path); bg[0].GetRawFormat(&guidFileFormat);
				if (guidFileFormat != ImageFormatJPEG) return;
			}
			Graphics g(hdc); g.SetPageUnit(UnitPixel);
			if (!fullscreen)
			{
				RectF bounds(0, 0, rt1.right - rt1.left, rt1.bottom - rt1.top); g.DrawImage(bg, bounds);
			}
			else if(fullscreen)
			{
				int w = GetSystemMetrics(SM_CXSCREEN); int h = GetSystemMetrics(SM_CYSCREEN);
                RectF bounds(0, 0, 1300, 700); bg = new Image(path); g.DrawImage(bg, bounds);
			}
		}
		
	}

	void setBackgroundPicturePNG(LPCWSTR path)
	{
		typefrm = "png";
		Window::path = *path;
		GetWindowRect(hwnd, &rt1);
		{
			Graphics g(hdc);
			g.SetPageUnit(UnitPixel);
			Rect bounds(0, 0, rt1.right - rt1.left, rt1.bottom - rt1.top);
			if (bg == NULL)
			{
				GUID guidFileFormat; bg = new Image(path); bg[0].GetRawFormat(&guidFileFormat);
				if (guidFileFormat != ImageFormatPNG) return;
			}
			g.DrawImage(bg, bounds);
		}
	}


	void create( char *classes , char *name , int w , int h , int x , int y )
	{
		hwnd = CreateWindowA(classes, name, WS_POPUP | WS_OVERLAPPEDWINDOW, x, y, w, h, NULL, NULL, NULL, NULL);
		ShowWindow(hwnd, SW_SHOW);
		UpdateWindow(hwnd);
		selfhwnd = true;
	}


	void setBackgroundGradient( COLORREF gradstart , COLORREF gradend )
	{
		RECT r3; r3.top = 0; r3.bottom = 700; r3.left = 0; r3.right = 1300;
		int w = GetSystemMetrics(SM_CXSCREEN); int h = GetSystemMetrics(SM_CYSCREEN);
		Window::gradstart = gradstart; Window::gradend = gradend;
		gradient = true;
		GetWindowRect(hwnd, &rt1);
		TRIVERTEX vertex[2];
		vertex[0].x = 0;
		vertex[0].y = 0;
		vertex[0].Red = GetRValue(Window::gradstart) << 8;
		vertex[0].Green = GetGValue(Window::gradstart) << 8;
		vertex[0].Blue = GetBValue(Window::gradstart) << 8;
		vertex[0].Alpha = 0x0000;
		if(fullscreen)
		{
			InvalidateRect(hwnd, &r3, true);
			UpdateWindow(hwnd);
			vertex[1].x = 1300; vertex[1].y = 700;
		}
		else {

			vertex[1].x = rt1.right - rt1.left;
			vertex[1].y = rt1.bottom - rt1.top;
		}
		vertex[1].Red = GetRValue(Window::gradend) << 8;
		vertex[1].Green = GetGValue(Window::gradend) << 8;
		vertex[1].Blue = GetBValue(Window::gradend) << 8;
		vertex[1].Alpha = 0x0000;
		GRADIENT_RECT r; r.UpperLeft = 0; r.LowerRight = 1;
		GradientFill(hdc, vertex, 2, &r, 1, GRADIENT_FILL_RECT_V);
		
	}

	void repaintMove()
	{
		RECT rt;
		int w = GetSystemMetrics(SM_CXSCREEN);
		int h = GetSystemMetrics(SM_CYSCREEN);
		GetWindowRect(hwnd, &rt);
		if (rt.left <= 0 || rt.right >= w || rt.bottom >= h)
		{
			if (gradient)
			{
				setBackgroundGradient(gradstart, gradend);
			}
		}
	}

	void repaint( WPARAM wp )
	{

		if (wp == SC_MINIMIZE)
		{
			
			windowtoMemory();
		}
		else if (wp == SC_MAXIMIZE)
		{
			fullscreen = true;
			DeleteMem();
			if (gradient)
			{
				setBackgroundGradient(gradstart, gradend);
			}
			else {
				repaintPicture();
			}
		}
		else if (wp == SC_RESTORE)
		{
			fullscreen = false;
			memorytoWindow();
		} 
		else if (wp == SIZE_RESTORED)
		{
			EventSIZE();
		}
	
	}

};