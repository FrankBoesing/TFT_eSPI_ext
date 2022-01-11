
#include <TFT_eSPI_ext.h>

TFT_eSPI_ext tft = TFT_eSPI_ext();
TFT_eSPI_Button Button1;

#include "screens.h" // Must include after any button instances have been created

void setup() {
  Serial.begin(115200);
  Serial.println(""); Serial.println("");
  Serial.println("TFT_eSPI_ext library test!");

  tft.init();
  Button1.initButton(&tft,400, 30, 141, 43, 0xFFFF, 0x2A54, 0xFFFF, "SETUP", 2);

  tft.setRotation(1);
  tft.fillScreen(TFT_GREEN);

  Screen2();
}

void loop(void) {
}
