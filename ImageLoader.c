#include "ImageLoader.h"
/*
	bmp 파일을 읽어서 SImage타입으로 변환
	png도 지원하려면 알고리즘 구현 해야함

*/

extern HDC FrontDC;
extern RObjectArray RenderObjects;

void initializeImageLoader() {

}

int getRenderObjectHandle(LPCWSTR BMPdir) {
	BITMAP tmpBtm;
	sImage *dst;
	dst = malloc(sizeof(sImage));
	dst->bitmap = (HBITMAP)LoadImage(NULL, BMPdir, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(dst->bitmap, sizeof(BITMAP), &tmpBtm);
	dst->width = tmpBtm.bmWidth;
	dst->height = tmpBtm.bmHeight;
	dst->Image = CreateCompatibleDC(FrontDC);
	SelectObject(dst->Image, dst->bitmap);
	dst->Mask = NULL;

	return RenderObjects.Register(dst);
}

void ConvertPNGToSImage(sImage *dst, LPCWSTR dir) {
	//read png
	//convert to bmp
	//load to sImage
}