#pragma once

#include <Windows.h>
#include <math.h>
#include <assert.h>

#define PI 3.14159265358979323846
#define pow2(x) x*x

#define _RObjectMaxSize 100000

typedef struct sImage {
	HBITMAP bitmap;
	HDC Image;
	HDC Mask;
	int width;
	int height;
}sImage;

typedef struct RenderingObject {
	sImage *img;
	int diagSize;
	int xPos;
	int yPos;

	HDC RotatedImage;
	HDC RotatedMaskImage;
	HBITMAP RotatedBitmap;
	HBITMAP RotatedMaskBitmap;
	float rotateDegree;
	POINT rotatePoint[3];
}RObject;

typedef struct RenderingObjectArray {
	int maxSize;
	int nextPos;
	RObject* array[_RObjectMaxSize];
}RObjectArray;


RObjectArray _RObjects;

RObject* GetRObject(int handle);

void _initializeRenderObjectArray();
void RotateRObject(int handle, float degree);
void _rotateRObject(RObject* obj, float degree);
int _registerRObject(sImage *obj);
void _disposeRObjectArray();