#pragma once
#include "Image.h"
#include "Screen.h"
#include <stdlib.h>


void InitializeRenderer();
void RenderRObject(int handle);
void SwapBuffer();
void resetBuffer();
void _renderDefaultRObject(int handleNum);
void _renderRotatedRObject(int handleNum);
