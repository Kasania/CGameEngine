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

HANDLE Console;
HWND Window;
HDC FrontDC;
HDC BackDC;
HBITMAP RenderBuffer;
int ScreenXSize, ScreenYSize;
extern RObjectArray RenderObjects;

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

	RenderObjects.Register = registerObject;
	RenderObjects.maxSize = 1000000;
	RenderObjects.nextPos = 0;
	RenderObjects.array = malloc(sizeof(RObject*) * RenderObjects.maxSize);
}

void disposeScreen() {

	for (int i = 0; i < RenderObjects.nextPos; ++i) {
		DeleteDC(RenderObjects.array[i]->img->Image);
		DeleteDC(RenderObjects.array[i]->img->Mask);
		DeleteObject(RenderObjects.array[i]->img->bitmap);
		free(RenderObjects.array[i]->img);
		free(RenderObjects.array[i]);
	}

	free(RenderObjects.array);
	DeleteDC(BackDC);
	ReleaseDC(Window, FrontDC);
	DeleteObject(RenderBuffer);
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

void RenderObject(int handleNum) {
	assert(handleNum <= RenderObjects.maxSize);
	resetBuffer();
	if (RenderObjects.array[handleNum]->img->Mask != NULL) {
		BitBlt(BackDC, RenderObjects.array[handleNum]->x, RenderObjects.array[handleNum]->y, 
			RenderObjects.array[handleNum]->img->width, RenderObjects.array[handleNum]->img->height, 
			RenderObjects.array[handleNum]->img->Mask, 0, 0, SRCPAINT);
		BitBlt(BackDC, RenderObjects.array[handleNum]->x, RenderObjects.array[handleNum]->y, 
			RenderObjects.array[handleNum]->img->width, RenderObjects.array[handleNum]->img->height, 
			RenderObjects.array[handleNum]->img->Image, 0, 0, SRCAND);
	}
	else {
		BitBlt(BackDC, RenderObjects.array[handleNum]->x, RenderObjects.array[handleNum]->y, 
			RenderObjects.array[handleNum]->img->width, RenderObjects.array[handleNum]->img->height,
			RenderObjects.array[handleNum]->img->Image, 0, 0, SRCCOPY);
	}
}

int registerObject(sImage *obj) {
	assert(RenderObjects.nextPos <= RenderObjects.maxSize);

	RObject* newObject;
	newObject = malloc(sizeof(RObject));
	newObject->img = obj;
	newObject->x = 0;
	newObject->y = 0;
	RenderObjects.array[RenderObjects.nextPos] = newObject;
	return RenderObjects.nextPos++;
}

void resetRenderingQueue() {
	RenderObjects.nextPos = 0;
}