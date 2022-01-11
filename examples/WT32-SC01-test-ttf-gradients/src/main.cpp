
#include <TFT_eSPI_ext.h>

// The following comment is more relevant to enhancing the library?
// If these can be included in a sketch then a "how to" is needed.
// More than 900 Fonts available here:
// https://github.com/FrankBoesing/fonts/tree/master/ofl

TFT_eSPI_ext tft = TFT_eSPI_ext();

#include "screens.h" // Must include after tft instance created

/*
Things are undefined here in the Arduino environment - maybe was in platformio.ini?
TFT_eSPI will switch on backlight so delete this and leave user to add own code
void setBacklight(char brightness) //0..100
{
    const float fact = ((1 << BACKLIGHT_RESOLUTION) - 1) / 100.0f;
    if (brightness > 100) brightness = 100;
    ledcWrite(BACKLIGHT_CHANNEL, fact * brightness );
}
*/

void setup() {

  Serial.begin(115200);
  Serial.println(""); Serial.println("");
  Serial.println("TFT_eSPI_ext library test!");

  tft.init();
  tft.fillScreen(TFT_BLACK);
  tft.setRotation(1);

/*
Things are undefined here in the Arduino environment
TFT_eSPI will switch on backlight so delete this and leave user to add own code

  ledcSetup(BACKLIGHT_CHANNEL, BACKLIGHT_FREQ, BACKLIGHT_RESOLUTION);
  ledcAttachPin(TFT_BL, BACKLIGHT_CHANNEL);
  setBacklight(20);
*/

  Screen2();
}

void loop(void) {
}
