#include "ImageLoader.h"
/*
	bmp ������ �о SImageŸ������ ��ȯ
	png�� �����Ϸ��� �˰��� ���� �ؾ���

*/

extern HDC FrontDC;

void initializeImageLoader() {

}


void ConvertBMPToSImageWithoutMask(sImage *dst, LPCWSTR dir) {
	BITMAP tmpBtm;
	dst->bitmap = (HBITMAP)LoadImage(NULL, dir, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(dst->bitmap, sizeof(BITMAP), &tmpBtm);
	dst->width = tmpBtm.bmWidth;
	dst->height = tmpBtm.bmHeight;
	dst->Image = CreateCompatibleDC(FrontDC);
	SelectObject(dst->Image, dst->bitmap);
	dst->Mask = NULL;
}

void ConvertPNGToSImage(sImage *dst, LPCWSTR dir) {
	//read png
	//convert to bmp
	//load to sImage
}