// GDI/Win32를 이용
// Console에서 2D 그래픽 출력용
// Windows에서만 동작함
/*
	Create Render Object -> Register to Rendering Queue -> Draw BufferDC -> Swap to Show
				   					  
	BitMap					Queue[0] Draws First
	if !Bitmap
	convert to Bitmap
	y0,y1, x0,x1						
	Transparency
*/

#include <Windows.h>
typedef struct sImage {
	BITMAP bitmap;
	HDC Image;
	HDC Mask;
	int width;
	int height;
}sImage;

typedef struct RenderingObject {
	sImage img;
	int x;
	int y;
}RenderingObject;

typedef struct RenderingQueueObject {
	RenderingObject obj;
	void(*Render)(RenderingObject obj);
	struct RenderingQueueObject *prev;
	struct RenderingQueueObject *next;
}RenderingQueueObject;

typedef struct RenderingQueue {
	long size;
	RenderingQueueObject * HEAD;
}RenderingQueue;

void initialzeScreen(int XSize, int YSize);
void adjustScreenSize();
void RenderObject(RenderingObject obj);

HANDLE Console;
HWND Window;
HDC FrontDC;
HDC BackDC;
HBITMAP RenderBuffer;
int ScreenXSize, ScreenYSize;

void initialzeScreen(int XSize, int YSize) {
	ScreenXSize = XSize;
	ScreenYSize = YSize;

	Console = GetStdHandle(STD_OUTPUT_HANDLE);
	Window = GetConsoleWindow();
	FrontDC = GetDC(Window);
	BackDC = CreateCompatibleDC(FrontDC);
	RenderBuffer = CreateCompatibleBitmap(FrontDC, ScreenXSize, ScreenYSize);
	CONSOLE_CURSOR_INFO Cursor;
	Cursor.bVisible = 0;
	Cursor.dwSize = 1;
	system("echo off");
	system("cls");
	SMALL_RECT size = { 0,0,77,47 };
	SetConsoleWindowInfo(Console, TRUE, &size);

	//adjustScreenSize();	
	//RenderingQueueObject rqo;
	//rqo.Render = RenderObject;
	//rqo.Render(rqo.obj);

}

void adjustScreenSize() {
	//HKEY key;
	//Registry 작업, 사지방에서 불가능 함
	//나중으로 미룸
}

void RenderObject(RenderingObject obj) {
	if (obj.img.Mask != NULL) {
		BitBlt(BackDC, obj.x, obj.y, obj.img.width, obj.img.height, obj.img.Mask, 0, 0, SRCPAINT);
		BitBlt(BackDC, obj.x, obj.y, obj.img.width, obj.img.height, obj.img.Image, 0, 0, SRCAND);
	}
	else {
		BitBlt(BackDC, obj.x, obj.y, obj.img.width, obj.img.height, obj.img.Image, 0, 0, SRCCOPY);
	}
}