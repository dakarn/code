#include "resource.h"
#include "Varrior.h"
#include <winsock2.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <tchar.h>
#include <cstdlib>
#include <WinBase.h>
#include <math.h>
#include <cstring>
#include <string>
#include <iostream>
#include <ctime>
#include <sstream>
#include "Window.cpp"
#include "SelectBox.cpp"
#include "Label.cpp"
#include "HintText.cpp"
#include "Button.cpp"
#include "TextField.cpp"
#include "TextArea.cpp"
#include "List.cpp"
#include "Toggle.cpp"
#include "PopupMenu.cpp"
#include "ProgressBar.cpp"
#include "CounterField.cpp"
#pragma comment(lib,"wsock32.lib")
#pragma comment(lib,"Ws2_32.lib")
using namespace std;


void R( );
void RA( int a , char *s );
void TG( bool status );
void InitMain( LPCWSTR className );
void menuselect( int a);

HDC src;
HDC hdc1;
HBITMAP bm;
HGDIOBJ obj;
void getTime();
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE hInsti;
HWND hwnd;
SOCKET client;
sockaddr_in dest;
#define PORT 128
#define SERVERADDR "127.0.0.1"
char buff[14];
char otvet[40000];
bool statusConnect = false;
char timec[50];
string textsend;
Window window;
Button button1, button;
TextField tf;
TextArea ta;//"Полностью анонимный прокси сервис с отключенными логам огромный и постоянно обновляющийся прокси лист IP-адресов. Этот тип анонимных прокси идеально подходит для рассылки(приглашения в группы vkontakte.ru), парсинга(google,yandex) и работы с icq, ftp");
List list;
SelectBox select1;
Toggle toggle;
ProgressBar progress;
CounterField counter;
HintText hint;
Label l1("The File GUI Label Interface", "C:\\films.bmp");
PopupMenu menu;


void rr(char *str) { MessageBoxA(NULL, str, NULL, NULL); }

void getTime()
{
	time_t currtime = time(0);
	DWORD start = GetTickCount();
	sprintf(timec, "%I64d", currtime);
}


void InitMain(LPCWSTR className)
{
	
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_OWNDC;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInsti;
	wcex.hIcon = LoadIcon(hInsti, MAKEINTRESOURCE(IDI_WIN32));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = className;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	RegisterClassEx(&wcex);

	
}



int Proc() {

	
	while ( recv(client, otvet, sizeof(otvet), 0) != SOCKET_ERROR )
	{
	
	}

	
	closesocket(client);
    return 1;
}

string getFormatTime()
{

	SYSTEMTIME timer;
	WORD s , m , h;
	GetLocalTime(&timer);
	char second[8] , minute[8] , hour[8];

	s = timer.wSecond;
	if (s < 10) { sprintf(second, "0%d", s); } else { sprintf(second, "%d", s); }

	m = timer.wMinute;
	if (m < 10) { sprintf(minute, "0%d", m); } else { sprintf(minute, "%d", m); }

	h = timer.wHour;
	if (h < 10) { sprintf(hour, "0%d", h); } else { sprintf(hour, "%d", h);  }
	
	string res; 
	return res.append(hour).append(":").append(minute).append(":").append(second);
	
	
}


boolean Connect()
{
	statusConnect = true;
	return false;
}


