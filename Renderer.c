// GDI/Win32�� �̿�
// Console���� 2D �׷��� ��¿�
// Windows������ ������
/*
	Create Render Object -> Register to Rendering Queue -> Draw BufferDC -> Swap to Show
				   					  
	BitMap					Queue[0] Draws First
	if !Bitmap
	convert to Bitmap
	y0,y1, x0,x1						
	Transparency
*/

#include "Renderer.h"
#include <stdio.h>

HANDLE Console;
HWND Window;
HDC FrontDC;
HDC BackDC;
HBITMAP RenderBuffer;
int ScreenXSize, ScreenYSize;

void initialzeScreen(int XSize, int YSize) {
	ScreenXSize = XSize;
	ScreenYSize = YSize;

	system("mode con:lines=54 cols=220");
	CONSOLE_CURSOR_INFO Cursor;
	Cursor.bVisible = 0;
	Cursor.dwSize = 1;
	system("echo off");
	system("cls");

	Console = GetStdHandle(STD_OUTPUT_HANDLE);
	Window = GetConsoleWindow();
	FrontDC = GetDC(Window);
	BackDC = CreateCompatibleDC(FrontDC);
	RenderBuffer = CreateCompatibleBitmap(FrontDC, ScreenXSize, ScreenYSize);
	SelectObject(BackDC, RenderBuffer);

}

void adjustScreenSize() {
	//HKEY key;
	//Registry �۾�, �����濡�� �Ұ��� ��
	//�������� �̷�
}

void resetBuffer() {
	BitBlt(BackDC, 0, 0, ScreenXSize, ScreenYSize, FrontDC, 0, 0, BLACKNESS);
}

void SwapBuffer() {
	BitBlt(FrontDC, 0, 0, ScreenXSize, ScreenYSize, BackDC, 0, 0, SRCCOPY);//Work
}

void RenderObject(RenderingObject *obj) {
	resetBuffer();
	if (obj->img.Mask != NULL) {
		BitBlt(BackDC, obj->x, obj->y, obj->img.width, obj->img.height, obj->img.Mask, 0, 0, SRCPAINT);
		BitBlt(BackDC, obj->x, obj->y, obj->img.width, obj->img.height, obj->img.Image, 0, 0, SRCAND);
	}
	else {
		BitBlt(BackDC, obj->x, obj->y, obj->img.width, obj->img.height, obj->img.Image, 0, 0, SRCCOPY);
	}
}