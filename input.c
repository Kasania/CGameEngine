#include "input.h"

extern HWND Window;

void initializeInput() {
	mouse.LB = &KeySet[VK_LBUTTON];
	mouse.RB = &KeySet[VK_RBUTTON];
}

void UpdateInput() {
	if (Window == GetForegroundWindow()) {
		for (int i = 0; i < 256; ++i) {
			if (GetAsyncKeyState(i) & 0x8000) {
				if (KeySet[i] == NonPress) KeySet[i] = Press;
				else if (KeySet[i] == Press) KeySet[i] = Hold;
			}
			else if (!GetAsyncKeyState(i)) {
				if (KeySet[i] == Press || KeySet[i] == Hold) KeySet[i] = Release;
				else if (KeySet[i] == Release) KeySet[i] = NonPress;
			}
		}

		GetCursorPos(&mouse.pos);
		ScreenToClient(Window, &mouse.pos);
	}
}

