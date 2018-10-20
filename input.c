#include "input.h"

extern HANDLE ConsoleIn;

INPUT_RECORD ir[64];
LPDWORD nRead;


void initializeInput() {
	mouse = &ir->Event.MouseEvent;
}

void UpdateKeys() {//change to ReadConsoleInput
	FlushConsoleInputBuffer(ConsoleIn);
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
	ReadConsoleInput(ConsoleIn, ir, sizeof(INPUT_RECORD), &nRead);
	
}

void UpdateInput() {
	FlushConsoleInputBuffer(ConsoleIn);

}

