#pragma once
#include "Image.h"
#include "Screen.h"
#include <stdlib.h>
//#include <assert.h>

void InitializeRenderer();
void RenderRObject(int handle);
void SwapBuffer();
void resetBuffer();
void _renderRotatedRObject(int handleNum);
