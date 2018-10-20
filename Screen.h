#pragma once
#include <Windows.h>

void initializeScreen(int XSize, int YSize);
void disposeScreen();
void adjustScreenSize();

extern void disposeRObjectArray();