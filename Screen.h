#pragma once
#include <Windows.h>

HWND Window;
HDC FrontDC;
HDC BackDC;
int ScreenXSize, ScreenYSize;

void InitializeScreen(int XSize, int YSize);
void DisposeScreen();
void _adjustScreenSize();

extern void _disposeRObjectArray();
