// Demo the font rendering on TFT or the sprite

#include <SPI.h>
#include <TFT_eSPI.h>
#include <TFT_eSPI_ext.h>

// Fonts in these files are available in the following sizes:
// 8, 9, 10, 11, 12, 13, 14, 16, 18, 20, 24, 28, 32, 40, 48, 60, 72 and 96
// This example uses size 32

#include <font_Arial.h>
#include <font_ArialBold.h>
#include <font_ArialItalic.h>
#include <font_ArialBoldItalic.h>

TFT_eSPI     tft = TFT_eSPI();
TFT_eSprite  img = TFT_eSprite(&tft);

// TFT_eSPI_ext will inherit the TFT_eSPI class functions so the created "etft" instance
// can call both the extension font class and the "tft" instance TFT_eSPI base class functions.
// So tft.fillScreen(TFT_BLUE) and etft.fillScreen(TFT_BLUE) do the same thing!
// TFT_eSPI_ext functions can only be called using the "etft" instance
TFT_eSPI_ext etft = TFT_eSPI_ext(&tft);

uint16_t ypos = 0;
  
void setup() {
  Serial.begin(115200);
  etft.begin();
  etft.setRotation(1);

  etft.fillScreen(TFT_BLACK);
  Serial.println("Font test"); 

  etft.setTTFont(Arial_32_Bold);
  // Using TTF metrics for set font create a sprite of size to hold 999
  // The sprite will be tightly cropped to the font cap height.
  // Descenders will be lost in this case, use TTFlineSpace() to get
  // line spacing height where descenders must be rendered.
  img.createSprite(etft.TTFtextWidth("999"), etft.TTFtextHeight("9"));

}

void loop(void) {
  // With background colour to erase old text
  etft.setTextColor(TFT_YELLOW, TFT_BLUE);
  etft.setTTFont(Arial_32_Bold);

  // Set TFT_eSPI_ext to render font on the TFT
  etft.TTFdestination(&tft);
  
  uint32_t dt = millis();
  for (int i = 100; i < 1000; i++ )
  {
    etft.setCursor(0, 0);
    etft.print(i);
    etft.print(" "); // Add space to clear stray pixels since not all glyphs are the same width
    //delay(250);
  }
  Serial.print("TFT render time = "); Serial.println(millis()-dt);
  delay(2000);


  // Without background colour (sprite can be filled to erase od text)
  etft.setTextColor(TFT_YELLOW);

  // Set TFT_eSPI_ext to render font in a sprite
  etft.TTFdestination(&img);
  
  dt = millis();
  for (int i = 100; i < 1000; i++ )
  {
    img.fillSprite(TFT_RED); // Clear sprite
    etft.setCursor(0, 0);
    etft.print(i);
    img.pushSprite(0,80);
    //delay(250);
  }
  // In this demo case the sprite occupies a smaller area on the TFT, so should be a bit faster
  Serial.print("Sprite render time = "); Serial.println(millis()-dt);
  delay(2000);
}
