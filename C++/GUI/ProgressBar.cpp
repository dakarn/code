#include "GraphH.h"


class ProgressBar {

private:

	struct LineBarPos { int pos1 = 0; int pos2 = 40; int pos3 = 0; } lbp;
	HDC mem;
	string label = "";
	COLORREF colbr = RGB(0, 0, 0), colorback = RGB(220,220,220), body = RGB(184, 180, 187) , colotext = RGB(0,0,0);
	COLORREF gradstart = RGB(0, 0, 0), gradend = RGB(0, 0, 0) , colorlinebar = RGB(153,233,153);
	int w, h, padding = 0, effect = -1, posLine = 1, curvalue = 0, maxvalue = 100, eventpos = -1, degree = -1, pensize = 0;
	struct Location { int x = 0; int y = 0; } local;
	char * gradtype = "up" , *gradhv = "v";
	HDC hdc;
	HWND hwnd;
	TRIVERTEX vertex[2], vertex1[2];
	RECT r;
	vector<void(*)()>funfinish,funstart,funpos;
	bool create = false , border = false , evstart = false , evfinish = false, evpos = false , oneshow = false;
	bool threadstatus = false , linebars = false;
	SIZE weightTextRet(string tex)
	{
		SIZE size;
		GetTextExtentPoint32A(hdc, tex.c_str(), tex.length(), &size);
		return size;
	}

	void showGradient( )
	{

		vertex[1].x = local.x + (int)((curvalue*w) / maxvalue);
		GRADIENT_RECT r; r.UpperLeft = 0; r.LowerRight = 1;
		GradientFill( hdc , vertex , 2 , &r, 1 , (strcmp(gradhv,"v")==0?GRADIENT_FILL_RECT_V:GRADIENT_FILL_RECT_H ));
	}


	void showPen()
	{
		
		RECT r1;
		r1.left = local.x; r1.top = local.y; r1.right = r.left + (int)((curvalue*w)/maxvalue); r1.bottom = r.top + h;

		HBRUSH brush = CreateSolidBrush(body);
		HGDIOBJ hobj = SelectObject(hdc, brush);
		FillRect(hdc, &r1, brush);
		SelectObject(hdc,hobj);
		DeleteObject(brush);
	}

	void showLabel()
	{
		if (label == "") return;

		HFONT font = CreateFontA(16, 6, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH, "Times New Roman");
		HGDIOBJ hobj = SelectObject(hdc, font);

		SIZE zz = weightTextRet(label);
		double xtext = (w - zz.cx) / 2; double ytext = (h - zz.cy) / 2;

		RECT r1;
		r1.left = local.x + (int)xtext; r1.top = local.y + (int)ytext; r1.right = 0; r1.bottom = 0;

		SetBkMode(hdc,TRANSPARENT);
		SetTextColor(hdc, RGB(11,22,11));
		TextOutA(hdc, r1.left , r1.top , label.c_str(), label.length());
		SelectObject(hdc,hobj);
		DeleteObject(font);
	}

	void showDegree( RECT r1 )
	{

		HBRUSH brush = CreateSolidBrush(colorback);
		SelectObject(hdc, brush);
		RoundRect(hdc, r1.left,r1.top,r1.right,r1.bottom, degree , degree);
		DeleteObject(brush);
	}

	void showDarking()
	{
		HGDIOBJ hobj;
		RECT r2;
		COLORREF ff = RGB(121, 255, 121);
		r2.left = local.x; r2.top = local.y; r2.right = r.left + (int)round(((curvalue*w) / maxvalue)); r2.bottom = r2.top + h - (h / 2) - 1;
		HBRUSH brush = CreateSolidBrush(ff);
		hobj = SelectObject(hdc, brush);
		FillRect(hdc, &r2, brush);
		SelectObject(hdc, hobj);
		DeleteObject(brush);

		r2.left = local.x; r2.top = local.y + (h / 2) - 1; r2.right = r.left + (int)round(((curvalue*w) / maxvalue)); r2.bottom = r2.top + h - (h / 2);
		brush = CreateSolidBrush(body);
		hobj = SelectObject(hdc, brush);
		FillRect(hdc, &r2, brush);
		SelectObject(hdc, hobj);
		DeleteObject(brush);
	}

	static DWORD WINAPI LineBar(void* Param)
	{
		ProgressBar* This = (ProgressBar*)Param;
		return This->threadstart();
	}

	void viewLineBars()
	{
		
		GRADIENT_RECT r1; r1.UpperLeft = 0; r1.LowerRight = 1;
		vertex1[0].y = r.top + 1;
		vertex1[0].Red = GetRValue(body) << 8;
		vertex1[0].Green = GetGValue(body) << 8;
		vertex1[0].Blue = GetBValue(body) << 8;
		vertex1[0].Alpha = 0x0000;
		vertex1[1].y = r.top + h - 1;
		vertex1[1].Red = GetRValue(colorlinebar) << 8;
		vertex1[1].Green = GetGValue(colorlinebar) << 8;
		vertex1[1].Blue = GetBValue(colorlinebar) << 8;
		vertex1[1].Alpha = 0x0000;
		vertex1[0].x = r.left + posLine + lbp.pos1;
		vertex1[1].x = r.left + posLine + lbp.pos2;
		GradientFill(hdc, vertex1, 2, &r1, 1, GRADIENT_FILL_RECT_H);

		vertex1[0].y = r.top + 1;
		vertex1[0].Red = GetRValue(colorlinebar) << 8;
		vertex1[0].Green = GetGValue(colorlinebar) << 8;
		vertex1[0].Blue = GetBValue(colorlinebar) << 8;
		vertex1[0].Alpha = 0x0000;
		vertex1[1].y = r.top + h - 1;
		vertex1[1].Red = GetRValue(body) << 8;
		vertex1[1].Green = GetGValue(body) << 8;
		vertex1[1].Blue = GetBValue(body) << 8;
		vertex1[1].Alpha = 0x0008;

		vertex1[0].x = r.left + posLine + lbp.pos2;
		vertex1[1].x = r.left + posLine + (lbp.pos2*2);
		GradientFill(hdc, vertex1, 2, &r1, 1, GRADIENT_FILL_RECT_H);
		
	}

	DWORD threadstart()
	{
		while (threadstatus)
		{	
			if ((int)((curvalue*w) / maxvalue) <= posLine + 84) { lbp.pos3 = 1; } else 
			if (4 >= posLine && lbp.pos3 == 1 ) { posLine = 1; lbp.pos3 = 0; }
			
			if (lbp.pos3 == 0) { posLine += 5; } else { posLine -= 5; }
			
			Sleep(100);
			show(); setBorder(colbr, 1);
		}
		return 1;
	}

public:

	ProgressBar()
	{

	}

	void previousPercent()
	{
		if (curvalue <= 0) return;
		curvalue--;
		setValue(curvalue);
	}

	void nextPercent()
	{
		if (curvalue >= 100) return;
		curvalue++;
		setValue(curvalue);
	}

	void setLabel( string str )
	{
		label = str;
		if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(colbr, 1); }
	}

	int getValue()
	{
		return curvalue;
	}

	void setLineBar()
	{
		if (effect == 0) return;
		linebars = true; threadstatus = true;
		CreateThread(NULL, NULL, LineBar, (void*)this, NULL, NULL);
	}

	void setValue( int value )
	{
		
		curvalue = value;
		if (value == 0)
		{
			if (!funstart.empty()) { funstart[0](); }
		} else if (value == maxvalue)
		{
			if (!funfinish.empty()) { funfinish[0](); }
		} else if (value == eventpos)
		{
			if (!funpos.empty()) { funpos[0](); }
		}
		if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(colbr, 1); }
	}

	void setHWND(HWND hwnd1 = NULL)
	{
		hwnd = hwnd1;
		hdc = GetDC(hwnd);
		if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(colbr, 1); }
	}

	void setColor( COLORREF rgb )
	{
		body = rgb;
		if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(colbr, 1); }
	}

	void setLocation(int x1, int y1)
	{
		local.x = x1; local.y = y1;
		if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(colbr, 1); }
	}

	void setSize( int w1 , int h1 )
	{
		w = w1; h = h1;
		if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(colbr, 1); }
	}

	void show()
	{
		UpdateWindow(hwnd);
		if (hwnd == NULL) return;
		create = true;


		r.left = local.x; r.top = local.y; r.right = r.left + w; r.bottom = r.top + h;
	
		
		if (degree == -1)
		{
			HBRUSH	brush = CreateSolidBrush(colorback);
			HGDIOBJ hobj = SelectObject(hdc, brush);
			FillRect(hdc, &r, brush);
			SelectObject(hdc,hobj);
			DeleteObject(brush);

			if (effect == 0)
			{
				showGradient();

			} else if (effect == 1)
			{
				showDarking();

			} else {
				
				showPen();
			}
		}
		else {
			
			showDegree( r );
			RECT r1;
			r1.left = local.x ; r1.top = local.y ; r1.right = r.left + (int)((curvalue*w) / maxvalue); r1.bottom = r.top + h;
			HBRUSH brush = CreateSolidBrush(body);
			HGDIOBJ hobj = SelectObject(hdc, brush);
			RoundRect(hdc, r1.left, r1.top, r1.right, r1.bottom, degree, degree);
			SelectObject(hdc, hobj);
			DeleteObject(brush);
		}
		
		if (linebars) { viewLineBars();  }
		showLabel();

	}

	RECT HINT()
	{
		return r;
	}

	void Corner( int degre )
	{
		degree = degre;
	}

	void  setBackColor( COLORREF rgb )
	{
		colorback = rgb;
		if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(colbr, 1); }
	}

	void setBorder(COLORREF rgb, int bold = 1)
	{
		RECT r1;
		colbr = rgb;
		HBRUSH brush1; brush1 = CreateSolidBrush(rgb);
		HGDIOBJ hobj = SelectObject(hdc, brush1);

		if (degree == -1)
		{
			FrameRect(hdc, &r, brush1);
			SelectObject(hdc, hobj);
			DeleteObject(brush1);
		} else {
			RECT r1; r1.left = local.x; r1.top = local.y; r1.right = r.left + (int)((curvalue*w) / maxvalue); r1.bottom = r.top + h;
			RoundRect(hdc, r1.left, r1.top, r1.right, r1.bottom, degree, degree);
			SelectObject(hdc, hobj);
			DeleteObject(brush1); show();
		}

	}

	void setMaxValue( int max )
	{
		maxvalue = max;
	}

	void addEventFinish( void(*f)())
	{
		evfinish = true;
		funfinish.push_back(f);
	}


	void addEventPosition( int proc , void(*f)() )
	{
		evpos = true;
		funpos.push_back(f);
	}

	void addEventNull( void(*f)() )
	{
		evstart = true;
		funstart.push_back(f);
	}

	void setEffectDarking( )
	{
		effect = 1;
		if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(colbr, 1); }
	}

	void setEffectGradient( COLORREF start , COLORREF end , char *type , char *gradhv )
	{
		gradstart = start;  gradend = end; effect = 0; gradtype = type; ProgressBar::gradhv = gradhv;
		if (strcmp(gradtype, "endtostart") == 0)
		{
			vertex[0].x = local.x;
			vertex[0].y = local.y;
			vertex[0].Red = GetRValue(gradstart) << 8;
			vertex[0].Green = GetGValue(gradstart) << 8;
			vertex[0].Blue = GetBValue(gradstart) << 8;
			vertex[0].Alpha = 0x0000;
			vertex[1].x = local.x + (int)((curvalue*w) / maxvalue);
			vertex[1].y = local.y + h;
			vertex[1].Red = GetRValue(gradend) << 8;
		    vertex[1].Green = GetGValue(gradend) << 8;vertex[1].Blue = GetBValue(gradend) << 8;vertex[1].Alpha = 0x0000;
		}
		else if (strcmp(gradtype, "starttoend") == 0)
		{
			vertex[0].x = local.x;
			vertex[0].y = local.y;
			vertex[0].Red = GetRValue(gradend) << 8;
			vertex[0].Green = GetGValue(gradend) << 8;
			vertex[0].Blue = GetBValue(gradend) << 8;
			vertex[0].Alpha = 0x0000;

			vertex[1].x = local.x + (int)((curvalue*w) / maxvalue);
			vertex[1].y = local.y + h;
			vertex[1].Red = GetRValue(gradstart) << 8;
			vertex[1].Green = GetGValue(gradstart) << 8;
			vertex[1].Blue = GetBValue(gradstart) << 8;
			vertex[1].Alpha = 0x0000;
		}

		if (create == true) { InvalidateRect(hwnd, &r, true); show(); setBorder(colbr, 1); }
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