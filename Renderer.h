#pragma once
#include "ImageLoader.h"
#include "Screen.h"
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define PI 3.14159265358979323846

void InitializeRenderer();
void RenderRObject(int handle);
void RotateRObject(int handle, float degree);
void SwapBuffer();
void resetBuffer();
RObject* GetRObject(int handle);

void _renderRotatedRObject(int handleNum);
void _rotateRObject(RObject* obj,float degree);
int _registerRObject(sImage *obj);
void _disposeRObjectArray();
//void resetRenderingQueue();
