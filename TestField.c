#include "Renderer.h"

int main() {
	initialzeScreen(1720, 960);
	

	sImage img;

	ConvertBMPToSImageWithoutMask(&img, L".\\res\\a.bmp");
	RenderingObject obj;
	obj.img = img;
	obj.x = 0;
	obj.y = 0;

	RenderObject(obj);//dosen't work
	SwapBuffer();
	SwapBuffer();

	return 0;
}