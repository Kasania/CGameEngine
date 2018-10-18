#include "Renderer.h"

int main() {
	initialzeScreen(1760, 972);
	

	//ConvertBMPToSImageWithoutMask(&img, L".\\res\\red.bmp");
	int handle = getRenderObjectHandle(L".\\res\\red.bmp");
	while (1) {
		RenderObject(handle);
		SwapBuffer();
	}
	disposeScreen();
	return 0;
}