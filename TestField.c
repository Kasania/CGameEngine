#include "Renderer.h"
#include "input.h"
#include <stdio.h>
#include <time.h>

int main() {
	initializeScreen(1600, 900); 
	initializeRenderer();
	initializeInput();

	int handle = getRenderObjectHandle(L".\\res\\red.bmp"); 

	struct timespec t1;
	struct timespec t2;

	while (1) {
		timespec_get(&t1, TIME_UTC);
		UpdateKeys();
		timespec_get(&t2, TIME_UTC);
		
		long diff = t2.tv_nsec - t1.tv_nsec;
		//printf("%ld\n", diff);

		RenderRObject(handle);

		if (*mouse.LB != NonPress) {
			getRObject(handle)->xPos = mouse.pos.x;
			getRObject(handle)->yPos = mouse.pos.y;
		}

		if (KeySet['W']) {
			getRObject(handle)->yPos -= 5;
		}
		if (KeySet['S']) {
			getRObject(handle)->yPos += 5;
		}
		if (KeySet['A']) {
			getRObject(handle)->xPos -= 5;
		}
		if (KeySet['D']) {
			getRObject(handle)->xPos += 5; 
		}

		SwapBuffer();
		
	}
	disposeScreen();
	return 0;
}