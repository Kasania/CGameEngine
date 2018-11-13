#include "Renderer.h"
#include "Input.h"
#include "ImageLoader.h"
//#include <time.h>
int red;
int a;
int lena;
BOOL Running;

void Initialize() {
	InitializeScreen(1600, 900);
	InitializeRenderer();
	InitializeInput();

	red = GetRenderObjectHandle(L".\\res\\red.bmp");
	a = GetRenderObjectHandle(L".\\res\\a.bmp");
	lena = GetRenderObjectHandle(L".\\res\\lena256.bmp");

	//struct timespec t1;
	//struct timespec t2;

	GetRObject(red)->xPos = 800;
	GetRObject(red)->yPos = 400;

	GetRObject(lena)->xPos = 800;
	GetRObject(lena)->yPos = 400;
	Running = TRUE;
}

void Update() {
	if (*mouse.LB != NonPress) {
		GetRObject(lena)->xPos = mouse.pos.x;
		GetRObject(lena)->yPos = mouse.pos.y;
	}

	if (KeySet[VK_Q]==Press) {

		RotateRObject(red, 180.0f);
		//GetRObject(a)->yPos -= 5;
	}
	if (KeySet[VK_E] == Press) {

		RotateRObject(lena, -60.0f);
		//GetRObject(a)->yPos -= 5;
		
	}
	if (KeySet[VK_W]) {
		GetRObject(a)->yPos -= 5;
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
	if (KeySet[VK_ESCAPE]) {
		Running = FALSE;
	}

	//RotateRObject(a, -1.0f);
	//RotateRObject(red, 1.0f);
	//RotateRObject(lena, 2.0f);
}


void Render() {
	RenderRObject(a);
	RenderRObject(red);
	RenderRObject(lena);
	SwapBuffer();
}

int main() {
	Initialize();
	while (Running) {
		//timespec_get(&t1, TIME_UTC);
		PollInput();
		//timespec_get(&t2, TIME_UTC);
		
		//long diff = t2.tv_nsec - t1.tv_nsec;
		//printf("%ld\n", diff);
		Update();
		Render();
		
	}
	DisposeScreen();
	return 0;
}