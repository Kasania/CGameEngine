// GDI/Win32를 이용
// Console에서 2D 그래픽 출력용
// Windows에서만 동작함
/*
	Create Render Object -> Register to Rendering Queue -> Draw BufferDC -> Swap to Show
				   					  
	BitMap					
	if !Bitmap
	convert to Bitmap
	y0,y1, x0,x1						
	Transparency
*/

#include "Renderer.h"

RObjectArray RenderObjects;
extern HDC FrontDC;
extern HDC BackDC;
extern int ScreenXSize, ScreenYSize;

void initializeRenderer() {
	RenderObjects.Register = registerObject;
	RenderObjects.maxSize = 1000000;
	RenderObjects.nextPos = 0;
	RenderObjects.array = malloc(sizeof(RObject*) * RenderObjects.maxSize);
}

void resetBuffer() {
	BitBlt(BackDC, 0, 0, ScreenXSize, ScreenYSize, FrontDC, 0, 0, BLACKNESS);
}

void SwapBuffer() {
	BitBlt(FrontDC, 0, 0, ScreenXSize, ScreenYSize, BackDC, 0, 0, SRCCOPY);//Work
	resetBuffer();
}

void RenderRObject(int handleNum) {
	assert(handleNum <= RenderObjects.maxSize);
	if (RenderObjects.array[handleNum]->img->Mask != NULL) {
		BitBlt(BackDC, RenderObjects.array[handleNum]->xPos, RenderObjects.array[handleNum]->yPos, 
			RenderObjects.array[handleNum]->img->width, RenderObjects.array[handleNum]->img->height, 
			RenderObjects.array[handleNum]->img->Mask, 0, 0, SRCPAINT);
		BitBlt(BackDC, RenderObjects.array[handleNum]->xPos, RenderObjects.array[handleNum]->yPos, 
			RenderObjects.array[handleNum]->img->width, RenderObjects.array[handleNum]->img->height, 
			RenderObjects.array[handleNum]->img->Image, 0, 0, SRCAND);
	}
	else {
		BitBlt(BackDC, RenderObjects.array[handleNum]->xPos, RenderObjects.array[handleNum]->yPos, 
			RenderObjects.array[handleNum]->img->width, RenderObjects.array[handleNum]->img->height,
			RenderObjects.array[handleNum]->img->Image, 0, 0, SRCCOPY);
	}
}

int registerObject(sImage *obj) {
	assert(RenderObjects.nextPos <= RenderObjects.maxSize);

	RObject* newObject = (RObject*)malloc(sizeof(RObject));
	if (newObject) {
		newObject->img = obj;
		newObject->xPos = 0;
		newObject->yPos = 0;
		RenderObjects.array[RenderObjects.nextPos] = newObject;
	}
	return RenderObjects.nextPos++;
}

RObject* getRObject(int handle) {
	return RenderObjects.array[handle];
}

void resetRenderingQueue() {
	RenderObjects.nextPos = 0;
}

void disposeRObjectArray() {
	for (int i = 0; i < RenderObjects.nextPos; ++i) {
		DeleteDC(RenderObjects.array[i]->img->Image);
		DeleteDC(RenderObjects.array[i]->img->Mask);
		DeleteObject(RenderObjects.array[i]->img->bitmap);
		free(RenderObjects.array[i]->img);
		free(RenderObjects.array[i]);
	}

	free(RenderObjects.array);
}