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
	delay(3000);
}
