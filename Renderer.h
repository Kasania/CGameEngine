#pragma once
#include "ImageLoader.h"
#include <stdlib.h>
#include <assert.h>

void initialzeScreen(int XSize, int YSize);
void disposeScreen();
void adjustScreenSize();
void resetBuffer();
void SwapBuffer();
void RenderRObject(int handle);
int registerObject(sImage *obj);
RObject* getRObject(int handle);
void resetRenderingQueue();
