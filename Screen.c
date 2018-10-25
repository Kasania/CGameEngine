#include "Screen.h"
#include <stdio.h>
HANDLE ConsoleOut;

HWND Window;
HDC FrontDC;
HDC BackDC;
HBITMAP RenderBuffer;
int ScreenXSize, ScreenYSize;

void initializeScreen(int XSize, int YSize) {
	ScreenXSize = XSize ;
	ScreenYSize = YSize ;

	ConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Window = GetConsoleWindow();

	CONSOLE_CURSOR_INFO Cursor;
	Cursor.bVisible = 0;
	Cursor.dwSize = 0;
	SetConsoleCursorInfo(ConsoleOut, &Cursor);

	system("echo off");
	system("cls");

	adjustScreenSize();

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
	
}

void adjustScreenSize() {

	//independency from buffersize
	CONSOLE_FONT_INFO font = { 0 };

	GetCurrentConsoleFont(ConsoleOut, FALSE, &font);
	
	COORD consoleBuffer;
	consoleBuffer.X = ScreenXSize / font.dwFontSize.X;
	consoleBuffer.Y = ScreenYSize / font.dwFontSize.Y;

	SMALL_RECT consoleSize;
	consoleSize.Left = 0;
	consoleSize.Top = 0;
	consoleSize.Right = consoleBuffer.X - 1;
	consoleSize.Bottom = consoleBuffer.Y - 1;
	SetWindowPos(Window, HWND_TOP, 0, 0, ScreenXSize, ScreenYSize, SWP_NOSIZE);// Value?
	
	SetConsoleWindowInfo(ConsoleOut, TRUE, &consoleSize);
	SetConsoleScreenBufferSize(ConsoleOut, consoleBuffer);
	
	/*int e = GetLastError();
	printf("%d", e);*/
}