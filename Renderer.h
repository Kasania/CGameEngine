#pragma once
#include "ImageLoader.h"

typedef struct RenderingObject {
	sImage img;
	int x;
	int y;
}RenderingObject;

typedef struct RenderingQueueObject {
	RenderingObject obj;
	void(*Render)(RenderingObject obj);
	struct RenderingQueueObject *prev;
	struct RenderingQueueObject *next;
}RenderingQueueObject;

typedef struct RenderingQueue {
	long size;
	RenderingQueueObject * HEAD;
}RenderingQueue;

void initialzeScreen(int XSize, int YSize);
void adjustScreenSize();
void RenderObject(RenderingObject obj);
void SwapBuffer();
