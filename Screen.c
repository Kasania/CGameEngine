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


void initializeScreen(int XSize, int YSize) {
	ScreenXSize = XSize;
	ScreenYSize = YSize;
	//TODO : convert to line, column

	CONSOLE_CURSOR_INFO Cursor;
	Cursor.bVisible = 0;
	Cursor.dwSize = 0;
	system("mode con:lines=200 cols=635");
	system("echo off");
	system("cls");

	GetCurrentConsoleFontEx(ConsoleOut, FALSE, &font);
	font.dwFontSize.X = 3;
	font.dwFontSize.Y = 5;
	SetCurrentConsoleFontEx(ConsoleOut, FALSE, &font);
	//printf("%d, %d", font.dwFontSize.X, font.dwFontSize.Y);

	

	ConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleIn = GetStdHandle(STD_INPUT_HANDLE);

	GetConsoleMode(ConsoleIn, &ConsoleDefaultMode);
	SetConsoleMode(ConsoleIn, ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT | ENABLE_EXTENDED_FLAGS);

	Window = GetConsoleWindow();
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
	//HKEY key;
	//Registry 작업, 사지방에서 불가능 함
	//나중으로 미룸
}