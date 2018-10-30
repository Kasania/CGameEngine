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

void InitializeRenderer() {
	_initializeRenderObjectArray();
}

void RenderRObject(int handleNum) {
	assert(handleNum <= _renderObjects.maxSize);
	if (_renderObjects.array[handleNum]->rotateDegree!=0.0f) {
		_renderRotatedRObject(handleNum);
		return;
	}
	int _x = _renderObjects.array[handleNum]->xPos - _renderObjects.array[handleNum]->img->width / 2;
	int _y = _renderObjects.array[handleNum]->yPos - _renderObjects.array[handleNum]->img->height / 2;

	if (_renderObjects.array[handleNum]->img->Mask != NULL) {
		BitBlt(BackDC, _x, _y, 
			_renderObjects.array[handleNum]->img->width, _renderObjects.array[handleNum]->img->height, 
			_renderObjects.array[handleNum]->img->Mask, 0, 0, SRCPAINT);
		BitBlt(BackDC, _x, _y, 
			_renderObjects.array[handleNum]->img->width, _renderObjects.array[handleNum]->img->height, 
			_renderObjects.array[handleNum]->img->Image, 0, 0, SRCAND);
	}
	else {
		BitBlt(BackDC, _x, _y, 
			_renderObjects.array[handleNum]->img->width, _renderObjects.array[handleNum]->img->height,
			_renderObjects.array[handleNum]->img->Image, 0, 0, SRCCOPY);
	}
}

void SwapBuffer() {
	BitBlt(FrontDC, 0, 0, ScreenXSize, ScreenYSize, BackDC, 0, 0, SRCCOPY);
	resetBuffer();
}

void resetBuffer() {
	BitBlt(BackDC, 0, 0, ScreenXSize, ScreenYSize, FrontDC, 0, 0, BLACKNESS);
}

void _renderRotatedRObject(int handleNum) {
	_rotateRObject(_renderObjects.array[handleNum], _renderObjects.array[handleNum]->rotateDegree);
	PlgBlt(BackDC, _renderObjects.array[handleNum]->rotatePoint, _renderObjects.array[handleNum]->img->Image,
		0, 0, _renderObjects.array[handleNum]->img->width, _renderObjects.array[handleNum]->img->height,
		NULL, 0, 0);
}

void resetRenderingQueue() {
	_renderObjects.nextPos = 0;
}