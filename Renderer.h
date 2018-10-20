#pragma once
#include "ImageLoader.h"
#include "Screen.h"
#include <stdlib.h>
#include <assert.h>

void initializeRenderer();
void resetBuffer();
void SwapBuffer();
void RenderRObject(int handle);
int registerObject(sImage *obj);
RObject* getRObject(int handle);
void resetRenderingQueue();
void disposeRObjectArray();
