#include "Renderer.h"
#include "Input.h"
#include "ImageLoader.h"
//#include <time.h>

int main() {
	InitializeScreen(1600, 900); 
	InitializeRenderer();
	InitializeInput();

	int red = GetRenderObjectHandle(L".\\res\\red.bmp"); 
	int a = GetRenderObjectHandle(L".\\res\\a.bmp");
	int lena = GetRenderObjectHandle(L".\\res\\lena256.bmp");

	//struct timespec t1;
	//struct timespec t2;

	GetRObject(red)->xPos = 800;
	GetRObject(red)->yPos = 400;

	GetRObject(lena)->xPos = 800;
	GetRObject(lena)->yPos = 400;

	while (1) {
		//timespec_get(&t1, TIME_UTC);
		UpdateInput();
		//timespec_get(&t2, TIME_UTC);
		
		//long diff = t2.tv_nsec - t1.tv_nsec;
		//printf("%ld\n", diff);

		//RenderRObject(a);
		RenderRObject(red);
		
		RenderRObject(lena);
		RotateRObject(red, 1.0f);

		if (*mouse.LB != NonPress) {
			GetRObject(lena)->xPos = mouse.pos.x;
			GetRObject(lena)->yPos = mouse.pos.y;
		}

		if (KeySet[VK_W] == Press) {

			//RotateRObject(red, 180.0f);
			//GetRObject(a)->yPos -= 5;
		}
		if (KeySet[VK_Q]) {

			RotateRObject(red, 5.0f);
			//GetRObject(a)->yPos -= 5;
		}
		if (KeySet[VK_E]) {

			RotateRObject(red, -5.0f);
			//GetRObject(a)->yPos -= 5;
		}
		if (KeySet[VK_S]) {
			GetRObject(a)->yPos += 5;
		}
		if (KeySet[VK_A]) {
			GetRObject(a)->xPos -= 5;
		}
		if (KeySet[VK_D]) {
			GetRObject(a)->xPos += 5; 
		}

		SwapBuffer();
		
	}
	DisposeScreen();
	return 0;
}