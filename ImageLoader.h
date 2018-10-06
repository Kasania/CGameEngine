#pragma once
#include <Windows.h>

typedef struct sImage {
	HBITMAP bitmap;
	HDC Image;
	HDC Mask;
	int width;
	int height;
}sImage;

void ConvertBMPToSImageWithoutMask(sImage *dst, LPCWSTR dir);