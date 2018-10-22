#include "Renderer.h"
#include "input.h"
#include <stdio.h>

int main() {
	initializeScreen(1600, 900); 
	initializeRenderer();
	initializeInput();

	int handle = getRenderObjectHandle(L".\\res\\red.bmp"); 

	while (1) {

		UpdateKeys();
		RenderRObject(handle);

		if (mouse.dwButtonState) {
		getRObject(handle)->xPos = mouse.dwMousePosition.X * 3;
		getRObject(handle)->yPos = mouse.dwMousePosition.Y * 5;
		}
		if (KeySet['D'] == Press) {
			getRObject(handle)->yPos += 10; 
		}

		SwapBuffer();
		
	}
	disposeScreen();
	return 0;
}