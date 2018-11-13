#include "Renderer.h"

void InitializeRenderer() {
	_initializeRenderObjectArray();
}

void RenderRObject(int handleNum) {
	assert(handleNum <= _RObjects.maxSize);
	if (_RObjects.array[handleNum]->rotateDegree!=0.0f) {
		_renderRotatedRObject(handleNum);
	}
	else {
		_renderDefaultRObject(handleNum);
	}
}

void SwapBuffer() {
	BitBlt(FrontDC, 0, 0, ScreenXSize, ScreenYSize, BackDC, 0, 0, SRCCOPY);
	resetBuffer();
}

void resetBuffer() {
	BitBlt(BackDC, 0, 0, ScreenXSize, ScreenYSize, FrontDC, 0, 0, BLACKNESS);
}

void _renderDefaultRObject(int handleNum) {
	int _x = _RObjects.array[handleNum]->xPos - _RObjects.array[handleNum]->img->width / 2;
	int _y = _RObjects.array[handleNum]->yPos - _RObjects.array[handleNum]->img->height / 2;

	if (_RObjects.array[handleNum]->img->Mask != NULL) {
		BitBlt(BackDC, _x, _y,
			_RObjects.array[handleNum]->img->width, _RObjects.array[handleNum]->img->height,
			_RObjects.array[handleNum]->img->Mask, 0, 0, SRCPAINT);
		BitBlt(BackDC, _x, _y,
			_RObjects.array[handleNum]->img->width, _RObjects.array[handleNum]->img->height,
			_RObjects.array[handleNum]->img->Image, 0, 0, SRCAND);
	}
	else {
		BitBlt(BackDC, _x, _y,
			_RObjects.array[handleNum]->img->width, _RObjects.array[handleNum]->img->height,
			_RObjects.array[handleNum]->img->Image, 0, 0, SRCCOPY);
	}
}

void _renderRotatedRObject(int handleNum) {
	int _x = _RObjects.array[handleNum]->xPos - _RObjects.array[handleNum]->diagSize/ 2;
	int _y = _RObjects.array[handleNum]->yPos - _RObjects.array[handleNum]->diagSize / 2;

	RObject* Target = _RObjects.array[handleNum];
	BitBlt(BackDC, _x, _y, Target->diagSize, Target->diagSize, Target->RotatedMaskImage, 0, 0, MERGEPAINT);
	BitBlt(BackDC, _x, _y, Target->diagSize, Target->diagSize, Target->RotatedImage, 0, 0, SRCAND);

}
