#include "Renderer.h"

extern HDC BackDC;
extern HBITMAP RenderBuffer;

int main() {
	initialzeScreen(1760, 972);
	

	sImage img;

	ConvertBMPToSImageWithoutMask(&img, L".\\res\\red.bmp");
	RenderingObject obj;
	obj.img = img;
	obj.x = 0;
	obj.y = 0;
	while (1) {
		
		RenderObject(&obj);
		obj.x+=1;
		SwapBuffer();
	}

	return 0;
}