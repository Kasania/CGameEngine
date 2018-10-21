#include "Screen.h"
#include <stdio.h>
HANDLE ConsoleOut;
HANDLE ConsoleIn;

HWND Window;
HDC FrontDC;
HDC BackDC;
HBITMAP RenderBuffer;
int ScreenXSize, ScreenYSize;

DWORD ConsoleDefaultMode;
CONSOLE_FONT_INFOEX font = { sizeof(font) };

COORD consoleBuffer;
SMALL_RECT consoleSize;

void initializeScreen(int XSize, int YSize) {
	ScreenXSize = XSize ;
	ScreenYSize = YSize ;

	ConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleIn = GetStdHandle(STD_INPUT_HANDLE);
	Window = GetConsoleWindow();

	/*CONSOLE_CURSOR_INFO Cursor;
	Cursor.bVisible = 0;
	Cursor.dwSize = 0;
	SetConsoleCursorInfo(ConsoleOut, &Cursor);*/

	system("echo off");
	system("cls");

	adjustScreenSize();

	GetConsoleMode(ConsoleIn, &ConsoleDefaultMode);
	SetConsoleMode(ConsoleIn, ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT | ENABLE_EXTENDED_FLAGS);
	FrontDC = GetDC(Window);
	BackDC = CreateCompatibleDC(FrontDC);
	RenderBuffer = CreateCompatibleBitmap(FrontDC, ScreenXSize, ScreenYSize);
	SelectObject(BackDC, RenderBuffer);
	
}

void disposeScreen() {
	disposeRObjectArray();
	
	DeleteDC(BackDC);
	ReleaseDC(Window, FrontDC);
	DeleteObject(RenderBuffer);
	SetConsoleMode(ConsoleIn, ConsoleDefaultMode);
	
}

void adjustScreenSize() {

	GetCurrentConsoleFontEx(ConsoleOut, FALSE, &font);
	font.dwFontSize.X = 3;
	font.dwFontSize.Y = 5;
	SetCurrentConsoleFontEx(ConsoleOut, FALSE, &font);

	consoleBuffer.X = ScreenXSize / font.dwFontSize.X;
	consoleBuffer.Y = ScreenYSize / font.dwFontSize.Y;

	consoleSize.Left = 0;
	consoleSize.Top = 0;
	consoleSize.Right = consoleBuffer.X - 1;
	consoleSize.Bottom = consoleBuffer.Y - 1;
	SetWindowPos(Window, HWND_TOP, 0, 0, ScreenXSize + 36, ScreenYSize + 72, SWP_SHOWWINDOW);// Value?
	
	//SetConsoleWindowInfo(ConsoleOut, TRUE, &consoleSize);
	/*int e = GetLastError();
	printf("%d", e);*/
	
	SetConsoleScreenBufferSize(ConsoleOut, consoleBuffer);
}