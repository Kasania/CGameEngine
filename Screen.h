#pragma once
#include <Windows.h>

void InitializeScreen(int XSize, int YSize);
void DisposeScreen();
void _adjustScreenSize();

extern void _disposeRObjectArray();