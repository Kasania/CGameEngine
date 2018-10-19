#include "Renderer.h"

int main() {
	initialzeScreen(1760, 972);

	int handle = getRenderObjectHandle(L".\\res\\red.bmp");

	while (1) {
		RenderRObject(handle);
		getRObject(handle)->xPos += 1;
		SwapBuffer();
	}
	disposeScreen();
	return 0;
}