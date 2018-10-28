#pragma once
#include <Windows.h>

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
	int (*Register)(sImage* obj);
	RObject** array;
}RObjectArray;

int GetRenderObjectHandle(LPCWSTR BMPdir);