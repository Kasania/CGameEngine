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

RObjectArray _renderObjects;
extern HDC FrontDC;
extern HDC BackDC;
extern int ScreenXSize, ScreenYSize;



void InitializeRenderer() {
	_renderObjects.Register = _registerRObject;
	_renderObjects.maxSize = 100000;
	_renderObjects.nextPos = 0;
	_renderObjects.array = malloc(sizeof(RObject*) * _renderObjects.maxSize);
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

void RotateRObject(int handle, float degree) {
	_renderObjects.array[handle]->rotateDegree += degree;
	if(_renderObjects.array[handle]->rotateDegree > 360) _renderObjects.array[handle]->rotateDegree -= 360;
	else if (_renderObjects.array[handle]->rotateDegree < 0) _renderObjects.array[handle]->rotateDegree += 360;
}

void SwapBuffer() {
	BitBlt(FrontDC, 0, 0, ScreenXSize, ScreenYSize, BackDC, 0, 0, SRCCOPY);
	resetBuffer();
}

void resetBuffer() {
	BitBlt(BackDC, 0, 0, ScreenXSize, ScreenYSize, FrontDC, 0, 0, BLACKNESS);
}

RObject* GetRObject(int handle) {
	return _renderObjects.array[handle];
}

void _renderRotatedRObject(int handleNum) {
	_rotateRObject(_renderObjects.array[handleNum], _renderObjects.array[handleNum]->rotateDegree);
	PlgBlt(BackDC, _renderObjects.array[handleNum]->rotatePoint, _renderObjects.array[handleNum]->img->Image,
		0, 0, _renderObjects.array[handleNum]->img->width, _renderObjects.array[handleNum]->img->height,
		NULL, 0, 0);
}

void _rotateRObject(RObject* obj,float degree) {
		/*
			0 _________1
			 |         |
			 |    O    |
			 |_________|
		    2		
			O = Center of Image
			r = Degree to rotate
			x` =  (x)*cos(r) - y*sin(r)
			y` =  (x)*sin(r) + y*cos(r)
		*/
		
	double rad = degree * PI / 180.0f;
	double cosv = cos(rad);
	double sinv = sin(rad);
	double ax = obj->img->width / 2;
	double ay = obj->img->height / 2;
	double preX, preY;
	double _X, _Y;
	for (int i = 0; i < 3; ++i) {
		if (i == 0) { preX = -ax; preY = -ay; }
		else if (i == 1) { preX = ax; preY = -ay; }
		else if (i == 2) { preX = -ax; preY = ay; }
		_X = preX * cosv - preY * sinv;
		_Y = preX * sinv + preY * cosv;
		obj->rotatePoint[i].x = (long)(obj->xPos + _X);
		obj->rotatePoint[i].y = (long)(obj->yPos + _Y);
	}
}

int _registerRObject(sImage *obj) {
	assert(_renderObjects.nextPos <= _renderObjects.maxSize);
	RObject* newObject = (RObject*)malloc(sizeof(RObject));
	if (newObject) {
		newObject->img = obj;
		newObject->xPos = newObject->img->width/2;
		newObject->yPos = newObject->img->height/2;
		
		newObject->rotatePoint = (LPPOINT)malloc( sizeof(POINT) * 3);
		newObject->rotatePoint[0].x = newObject->xPos;
		newObject->rotatePoint[0].y = newObject->yPos;
		newObject->rotatePoint[1].x = newObject->xPos + newObject->img->width;
		newObject->rotatePoint[1].y = newObject->yPos;
		newObject->rotatePoint[2].x = newObject->xPos;
		newObject->rotatePoint[2].y = newObject->yPos + newObject->img->height;
		newObject->rotateDegree = 0.0f;

		_renderObjects.array[_renderObjects.nextPos] = newObject;
	}
	return _renderObjects.nextPos++;
}

void _disposeRObjectArray() {
	for (int i = 0; i < _renderObjects.nextPos; ++i) {
		DeleteDC(_renderObjects.array[i]->img->Image);
		DeleteDC(_renderObjects.array[i]->img->Mask);
		DeleteObject(_renderObjects.array[i]->img->bitmap);
		free(_renderObjects.array[i]->rotatePoint);
		free(_renderObjects.array[i]->img);
		free(_renderObjects.array[i]);
	}
	free(_renderObjects.array);
}

void resetRenderingQueue() {
	_renderObjects.nextPos = 0;
}