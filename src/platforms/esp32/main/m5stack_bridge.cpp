#include <M5Stack.h>
#include "m5stack_bridge.h"

void M5Stack_Init() {
	initArduino();
	M5.begin();
}

void M5Stack_ShowMessageAndWait(char *msg) {
	M5.Lcd.fillScreen(BLACK);
	M5.Lcd.setTextSize(2);
	M5.Lcd.setCursor(10, 10);
	M5.Lcd.print(msg);
	delay(1000);
}

void M5Stack_ShowMessage(char *msg) {
	M5.Lcd.fillScreen(BLACK);
	M5.Lcd.setTextSize(2);
	M5.Lcd.setCursor(10, 10);
	M5.Lcd.print(msg);
}

int M5Stack_ButtonRead(int button) {
	printf("M5Stack_ButtonRead button:%d\n", button);
	switch(button) {
	case 0:
		return M5.BtnA.read();
	case 1:
		return M5.BtnB.read();
	case 2:
		return M5.BtnC.read();
	}
	return -1;
}
