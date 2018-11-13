#include "Image.h"
#include <stdio.h>

extern HDC BackDC;

RObject* GetRObject(int handle) {
	return _RObjects.array[handle];
}

void _initializeRenderObjectArray()
{
	_RObjects.maxSize = _RObjectMaxSize;
	_RObjects.nextPos = 0;
}

void RotateRObject(int handle, float degree) {
	_RObjects.array[handle]->rotateDegree += degree;
	if (_RObjects.array[handle]->rotateDegree >= 360) _RObjects.array[handle]->rotateDegree -= 360;
	else if (_RObjects.array[handle]->rotateDegree < 0) _RObjects.array[handle]->rotateDegree += 360;

	_rotateRObject(_RObjects.array[handle], _RObjects.array[handle]->rotateDegree);
}

void _rotateRObject(RObject* obj, float degree) {
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
		obj->rotatePoint[i].x = (long)( _X + obj->diagSize / 2);
		obj->rotatePoint[i].y = (long)( _Y + obj->diagSize / 2);
	}
	BitBlt(obj->RotatedImage, 0,0, obj->diagSize, obj->diagSize, obj->RotatedImage, 0, 0, WHITENESS);
	BitBlt(obj->RotatedMaskImage, 0, 0, obj->diagSize, obj->diagSize, obj->RotatedMaskImage, 0, 0, WHITENESS);

	PlgBlt(obj->RotatedImage, obj->rotatePoint, obj->img->Image,
		0, 0, obj->img->width, obj->img->height,
		NULL, 0, 0);

	PlgBlt(obj->RotatedMaskImage, obj->rotatePoint, obj->img->Image,
		0, 0, obj->img->width, obj->img->height,
		NULL, 0, 0);
}

int _registerRObject(sImage *obj) {
	assert(_RObjects.nextPos <= _RObjects.maxSize);
	RObject* newObject = (RObject*)malloc(sizeof(RObject));
	if (newObject) {
		newObject->img = obj;
		newObject->xPos = newObject->img->width / 2;
		newObject->yPos = newObject->img->height / 2;

		newObject->diagSize = (int)sqrt(pow2(newObject->img->width) + pow2(newObject->img->height));

		newObject->RotatedImage = CreateCompatibleDC(BackDC);
		newObject->RotatedBitmap = CreateCompatibleBitmap(BackDC, 
			newObject->diagSize, newObject->diagSize);
		SelectObject(newObject->RotatedImage, newObject->RotatedBitmap);

		newObject->RotatedMaskImage = CreateCompatibleDC(BackDC);
		newObject->RotatedMaskBitmap = CreateCompatibleBitmap(newObject->RotatedMaskImage,
			newObject->diagSize, newObject->diagSize);
		SelectObject(newObject->RotatedMaskImage, newObject->RotatedMaskBitmap);

		if (newObject->rotatePoint) {
			newObject->rotatePoint[0].x = newObject->xPos;
			newObject->rotatePoint[0].y = newObject->yPos;
			newObject->rotatePoint[1].x = newObject->xPos + newObject->img->width;
			newObject->rotatePoint[1].y = newObject->yPos;
			newObject->rotatePoint[2].x = newObject->xPos;
			newObject->rotatePoint[2].y = newObject->yPos + newObject->img->height;
			newObject->rotateDegree = 0.0f;
		}
		_RObjects.array[_RObjects.nextPos] = newObject;
	}
	return _RObjects.nextPos++;
}

void _disposeRObjectArray() {
	for (int i = 0; i < _RObjects.nextPos; ++i) {
		DeleteDC(_RObjects.array[i]->img->Image);
		DeleteDC(_RObjects.array[i]->img->Mask);
		DeleteDC(_RObjects.array[i]->RotatedImage);
		DeleteObject(_RObjects.array[i]->img->bitmap);
		DeleteObject(_RObjects.array[i]->RotatedBitmap);
		free(_RObjects.array[i]->img);
		free(_RObjects.array[i]);
	}
}