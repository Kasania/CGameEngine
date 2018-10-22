#include "input.h"

extern HANDLE ConsoleIn;

INPUT_RECORD ir[64];
DWORD nRead = 0;


void initializeInput() {
	mouse = ir->Event.MouseEvent;
	
}

void UpdateKeys() {//speed issue?
	FlushConsoleInputBuffer(ConsoleIn);
	ReadConsoleInput(ConsoleIn, ir, sizeof(INPUT_RECORD), &nRead);
	
	for (int i = 0; i < 64; ++i) {
		if (ir[i].EventType) {

			if (ir[i].EventType == KEY_EVENT) {

				if (ir[i].Event.KeyEvent.bKeyDown == 0) {
					KeySet[(int)ir[i].Event.KeyEvent.wVirtualKeyCode] = NonPress;
				}
				else if (ir[i].Event.KeyEvent.bKeyDown == 1) {
					KeySet[ir[i].Event.KeyEvent.wVirtualKeyCode] = Press;
				}

			}
			else if(ir[i].EventType == MOUSE_EVENT){
				mouse = ir[i].Event.MouseEvent;
			}
			ir[i].EventType = 0;
		}
	}

}

void UpdateInput() {
	FlushConsoleInputBuffer(ConsoleIn);

}

