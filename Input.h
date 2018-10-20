#pragma once

#include "Screen.h"

enum KeyStatus {
	NonPress,
	Press,
	Hold,
	Release
};
enum KeyStatus KeySet[256];
MOUSE_EVENT_RECORD *mouse;
void initializeInput();
void UpdateKeys();