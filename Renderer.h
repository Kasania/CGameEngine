#pragma once
#include "ImageLoader.h"
#include <stdlib.h>
#include <assert.h>

void initialzeScreen(int XSize, int YSize);
void disposeScreen();
void adjustScreenSize();
void resetBuffer();
void SwapBuffer();
void RenderObject(int handle);
int registerObject(sImage *obj);
void resetRenderingQueue();
