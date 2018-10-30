#pragma once

#include <Windows.h>
#include <math.h>
#include <assert.h>

#define PI 3.14159265358979323846

typedef struct sImage {
	HBITMAP bitmap;
	HDC Image;
	HDC Mask;
	int width;
	int height;
}sImage;

typedef struct RenderingObject {
	sImage *img;
	int xPos;
	int yPos;
	float rotateDegree;
	POINT *rotatePoint;
}RObject;

typedef struct RenderingObjectArray {
	int maxSize;
	int nextPos;
	RObject** array;
}RObjectArray;

RObjectArray _renderObjects;

RObject* GetRObject(int handle);

void _initializeRenderObjectArray();
void RotateRObject(int handle, float degree);
void _rotateRObject(RObject* obj, float degree);
int _registerRObject(sImage *obj);
void _disposeRObjectArray();