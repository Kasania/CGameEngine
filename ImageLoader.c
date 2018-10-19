#include "ImageLoader.h"
/*
	bmp ������ �о SImageŸ������ ��ȯ
	png�� �����Ϸ��� �˰��� ���� �ؾ���

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