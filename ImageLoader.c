#include "ImageLoader.h"
/*
	bmp ������ �о SImageŸ������ ��ȯ
	png�� �����Ϸ��� �˰��� ���� �ؾ���

*/

extern HDC FrontDC;
extern RObjectArray _renderObjects;

void InitializeImageLoader() {
	
}

int GetRenderObjectHandle(LPCWSTR BMPpath) {
	BITMAP tmpBtm;
	sImage *dst = (sImage*)malloc(sizeof(sImage));
	if (dst) {
		dst->bitmap = (HBITMAP)LoadImage(NULL, BMPpath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_VGACOLOR);
		GetObject(dst->bitmap, sizeof(BITMAP), &tmpBtm);
		dst->width = tmpBtm.bmWidth;
		dst->height = tmpBtm.bmHeight;
		dst->Image = CreateCompatibleDC(FrontDC);
		SelectObject(dst->Image, dst->bitmap);
		dst->Mask = NULL;
	}

	return _renderObjects.Register(dst);
}

void ConvertPNGToSImage(sImage *dst, LPCWSTR dir) {
	//read png
	//convert to bmp
	//load to sImage
}