#include "Header.h"

void menuopen(int i, string name) { if (i == 0) { tf.setFocus(); } else if (i == 1) { ta.setFocus(); } }
void menuclose(int i, string name) { tf.unFocus(); }
void BT() {  }
void R() { progress.nextPercent(); }
void R1() { progress.previousPercent(); }
void RA(int index, char *s) {} //char ee[22]; sprintf(ee, "%d", index); MessageBoxA(NULL, ee, NULL, NULL); }
void TG( bool status ){ }
void menuselect( int a ){ char ee[22]; sprintf(ee, "%d", a); MessageBoxA(NULL,ee,NULL,NULL); }

int __stdcall WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{



	hInsti = hInst;
	InitMain(L"window");

	hwnd = CreateWindow(L"window", L"ChatSocket", WS_POPUP | WS_OVERLAPPEDWINDOW , 300, 100, 700, 500, NULL, NULL, hInst, NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	window.HWND(hwnd);


	menu.setHWND(hwnd);
	menu.add("Cut");
	menu.add("Copy");
	menu.add("Paste");
	menu.add("Delete");
	menu.addEventOpen( menuopen );
	menu.addEventClose(menuclose);

	l1.setHWND(hwnd);
	l1.setLocation(20,10);
	l1.show();
	hint.add("The Label",l1.HINT());

	button1.setHWND( hwnd );
	button1.setColor(187,203,117);
	button1.setSize( 160 , 40 );
	button1.setText("Отправить письмо");
	button1.setLocation( 24 , 390 );
	button1.setCursorHover(true);
	button1.setEffectGradient(RGB(11,99,11),RGB(44,222,44),"endtostart","v");
	button1.UnGradient();
	button1.show();
	button1.setBorder(RGB(50, 50, 50), 1);
	button1.addEventMouse(BT);
	button1.addEventClick(R);
	hint.setHWND(hwnd);
	hint.add("The Button", button1.HINT());


	button.setHWND(hwnd);
	button.setColor(187, 203, 117);
	button.setSize(160, 40);
	button.setText("Выйти из чата");
	button.setLocation(494, 390);
	button.setCursorHover(true);
	button.show();
	button.setBorder(RGB(50, 50, 50), 1);
	button.addEventMouse(BT);
	button.addEventClick(R1);
	button.setCursorHover( true );
	hint.add("The Button N2 - Class Button", button.HINT());


	select1.setHWND(hwnd);
	select1.add("Adding");
	select1.add("ffding");
	select1.add("StartAdd");
	select1.add("DeleteAd");
	select1.add("Adding");
	select1.add("ffding");
	select1.add("StartAdd");
	select1.add("DeleteAd");
	select1.setLocation(560,150);
	select1.show();
	select1.setLabel("Команда:");
	select1.setBorder(RGB(50, 50, 50), 1);




	tf.setHWND( hwnd);
	tf.setLocation( 24 , 60);
	tf.setSize( 200 , 26 );
	tf.setHint("Введите текст");
	tf.show();
	tf.setBorder(RGB(0,0,0), 1 );
	tf.setLabel("Ваше имя:");
	menu.bindToElem(tf.HINT(),"TextField");


	ta.setHWND(hwnd);
	ta.setLocation(24, 140);
	ta.setSize(280, 146);
	ta.show();
	ta.setBorder(RGB(0, 0, 0), 1);
	ta.setLabel("Ваше сообщение:");
	menu.bindToElem(ta.HINT(), "TextArea");


	list.setHWND(hwnd);
	list.add("Pushback");
	list.add("Query");
	list.add("Sending");
	list.add("Exit");
	list.add("Pushback");
	list.add("Query");
	list.add("Pushback");
	list.add("Sending");
	list.add("Exit");
	list.add("Pushback");
	list.add("Query");
	list.add("Sending");
	list.add("Exit");
	list.add("Pushback");
	list.add("Sending");
	list.add("Exit");
	list.add("Pushback");
	list.add("Query");
	list.add("Sending");
	list.add("Exit");
	list.add("Pushback");
	list.add("Query");
	list.add("Pushback");
	list.add("Sending");
	list.add("Exit");
	list.add("Pushback");
	list.add("Query");
	list.setSize(150,200);
	list.setColor( 255,255,255);
	list.setLocation( 360 , 60 );
	list.setCurrentElement(1);
	list.setColorLine(RGB(89,89,254));
	list.show();
	list.setLabel("Выберите действие:");
	list.addEventSelect( RA );


	counter.setHWND(hwnd);
	counter.setSize(40, 30);
	counter.setLocation(600,60);
	counter.setColor(RGB(255, 255, 255));
	counter.setStep(1);
	counter.show();
	counter.setBorder(RGB(0,0,0),1);
	counter.setLabel("Сколько?");


	progress.setHWND(hwnd);
	progress.setColor(RGB(11,255,11));
	progress.setBackColor(RGB(245,244,245));
	progress.setLocation(24,320);
	progress.setSize(640,20);
	progress.setLabel("Loading...");
	progress.setValue( 33 );
	progress.setEffectGradient(RGB(12, 116, 12), RGB(22, 199, 22), "starttoend","v");
	progress.show();
	progress.setBorder(RGB(22,33,22),1);

	

	WSAStartup(0x202, (WSADATA *)&buff[0]);
	client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	dest.sin_family = AF_INET;
	dest.sin_port = htons(PORT);
	dest.sin_addr.s_addr = inet_addr(SERVERADDR);



	getTime();

	textsend = "getresultQuery:hello<name>"; textsend.append( timec ).append("<value>");

	HACCEL hc = LoadAccelerators(hInst, 0);
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hc, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}


	return (int)msg.wParam;

}


void repaintElem()
{
	button1.repaint();
	button.repaint();
	tf.repaint();
	ta.repaint();
	select1.repaint();
	l1.repaint();
	list.repaint();
	progress.repaint();
	counter.repaint();
}


void repaintMove()
{
	select1.repaintMove();
	button1.repaintMove();
	button.repaintMove();
	tf.repaintMove();
	ta.repaintMove();
	l1.repaintMove();
	list.repaintMove();
	progress.repaintMove();
	counter.repaintMove();
}


void repaintBinding()
{
	button1.ObBinding();
	button.ObBinding();
}


LRESULT __stdcall WndProc(HWND hwnd, UINT message, WPARAM wp, LPARAM lp)
{
	PAINTSTRUCT ps;
	HDC dc;
	

	switch (message)
	{

	case WM_SYSCOMMAND:
		
		window.repaint( wp );
		return DefWindowProc(hwnd, message, wp, lp);
		
	break;
	case WM_KEYUP:

		tf.KeyBoard("UP",LOWORD(wp));
		ta.KeyBoard("UP", LOWORD(wp));

	break;
	case WM_KEYDOWN:


		tf.KeyBoard("DOWN",LOWORD(wp));
		ta.KeyBoard("DOWN", LOWORD(wp));

	break;
	case WM_DESTROY:

		PostQuitMessage(0);

	break;
	case WM_CLOSE:

		PostQuitMessage(0);

	break;
	case WM_MOUSEWHEEL:

		list.Wheel( wp , lp );

	break;
	case WM_MOVE:

		repaintMove();

	break;
	case WM_SIZE:

		window.repaint(wp);
		repaintElem();
		repaintBinding();
		
	break;
	case WM_MOUSEMOVE:





		button1.Mouse(HIWORD(lp), LOWORD(lp));
		button.Mouse(HIWORD(lp), LOWORD(lp));
		tf.Mouse(HIWORD(lp), LOWORD(lp));
		ta.Mouse(HIWORD(lp), LOWORD(lp));
		counter.Mouse(HIWORD(lp), LOWORD(lp));
		hint.ObServer(message , HIWORD(lp), LOWORD(lp));
		menu.Mouse(HIWORD(lp), LOWORD(lp));
		select1.Mouse(HIWORD(lp), LOWORD(lp));

	break;
	case WM_COMMAND:

	  switch (LOWORD(wp))
	  {

        case 2:
		
		    textsend = timec; textsend.append("<tag>LoginCI(").append(getFormatTime()).append("):  <message>Hello - Client on C++");
			if (statusConnect) { send(client, textsend.c_str(), textsend.length(), 0); }

		break;
	  }

	break;
	case WM_RBUTTONUP:

		menu.RClick(HIWORD(lp), LOWORD(lp));

	break;
	case WM_PAINT:

		dc = BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);

	break;
	case WM_LBUTTONUP:

		select1.Click("UP", HIWORD(lp), LOWORD(lp));
		menu.Click(HIWORD(lp), LOWORD(lp));
		button1.Click("Click#up", HIWORD(lp), LOWORD(lp));
		button.Click("Click#up", HIWORD(lp), LOWORD(lp));
		counter.Click("UP", HIWORD(lp), LOWORD(lp));
		ta.Click("UP" , HIWORD(lp), LOWORD(lp));
		tf.Click("UP",HIWORD(lp), LOWORD(lp));

	break;
	case WM_LBUTTONDOWN:

		select1.Click("DOWN", HIWORD(lp), LOWORD(lp));
		button1.Click("Click#down", HIWORD(lp), LOWORD(lp));
		button.Click("Click#down", HIWORD(lp), LOWORD(lp));
		ta.Click("DOWN",HIWORD(lp), LOWORD(lp));
		tf.Click("DOWN",HIWORD(lp), LOWORD(lp));
		list.Click(HIWORD(lp), LOWORD(lp));
		toggle.Click(HIWORD(lp), LOWORD(lp));
		counter.Click("DOWN",HIWORD(lp), LOWORD(lp));
		hint.ObServer(message, HIWORD(lp), LOWORD(lp));
		
	break;
	case WM_CREATE:

	break;
	case WM_LBUTTONDBLCLK:

		button1.DBLClick(HIWORD(lp), LOWORD(lp));
		
	break;
	default: return DefWindowProc(hwnd, message, wp, lp);

	}

	return 0;
}