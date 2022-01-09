

#include <TFT_eSPI.h>
#include <TFT_eSPI_ext.h>

#include "screens.h"

// More than 900 Fonts available here:
// https://github.com/FrankBoesing/fonts/tree/master/ofl

//TFT_eSPI tft = TFT_eSPI();
TFT_eSPI_ext tft = TFT_eSPI_ext();


void setBacklight(char brightness) //0..100
{
    const float fact = ((1 << BACKLIGHT_RESOLUTION) - 1) / 100.0f;
    if (brightness > 100) brightness = 100;
    ledcWrite(BACKLIGHT_CHANNEL, fact * brightness );
}

void setup() {

  Serial.begin(115200);
  Serial.println(""); Serial.println("");
  Serial.println("TFT_eSPI_ext library test!");

  tft.init();
  // tft.fillScreen(TFT_BLACK);
  tft.setRotation(1);


  ledcSetup(BACKLIGHT_CHANNEL, BACKLIGHT_FREQ, BACKLIGHT_RESOLUTION);
  ledcAttachPin(TFT_BL, BACKLIGHT_CHANNEL);
  setBacklight(20);
  Screen2();
}

void loop(void) {
}
