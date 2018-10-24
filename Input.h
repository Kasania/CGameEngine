#pragma once

#include "Screen.h"

enum KeyStatus {
	NonPress,
	Press,
	Hold,
	Release
};

typedef struct _Mouse {
	enum KeyStatus *LB;
	enum KeyStatus *RB;
	POINT pos;
}Mouse;

enum KeyStatus KeySet[256];
Mouse mouse;
void initializeInput();
void UpdateKeys();