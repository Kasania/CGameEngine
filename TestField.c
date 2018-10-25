#include "Renderer.h"
#include "input.h"
#include <stdio.h>
#include <time.h>

int main() {
	initializeScreen(1600, 900); 
	initializeRenderer();
	initializeInput();

	int red = getRenderObjectHandle(L".\\res\\red.bmp"); 
	int a = getRenderObjectHandle(L".\\res\\a.bmp");

	struct timespec t1;
	struct timespec t2;

	getRObject(red)->xPos = 100;
	getRObject(red)->yPos = 200;

	while (1) {
		timespec_get(&t1, TIME_UTC);
		UpdateInput();
		timespec_get(&t2, TIME_UTC);
		
		long diff = t2.tv_nsec - t1.tv_nsec;
		//printf("%ld\n", diff);

		RenderRObject(a);
		RenderRObject(red);


		if (*mouse.LB != NonPress) {
			getRObject(red)->xPos = mouse.pos.x;
			getRObject(red)->yPos = mouse.pos.y;
		}

		if (KeySet['W']) {
			getRObject(red)->yPos -= 5;
		}
		if (KeySet['S']) {
			getRObject(red)->yPos += 5;
		}
		if (KeySet['A']) {
			getRObject(red)->xPos -= 5;
		}
		if (KeySet['D']) {
			getRObject(red)->xPos += 5; 
		}

		SwapBuffer();
		
	}
	disposeScreen();
	return 0;
}