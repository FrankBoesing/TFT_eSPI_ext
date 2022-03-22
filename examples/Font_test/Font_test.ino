// Test the font rendering with and without background colour

#include <SPI.h>
#include <TFT_eSPI.h>
#include <TFT_eSPI_ext.h> // Include font extension library

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
TFT_eSPI_ext etft = TFT_eSPI_ext();

uint16_t ypos = 0;
  
void setup() {
  Serial.begin(115200);
  etft.begin();
  etft.setRotation(1);

  etft.fillScreen(TFT_BLACK);
  Serial.println("Font test"); 

  // Set TFT_eSPI_ext to render font on the TFT
  etft.TTFdestination(&tft);

  etft.setTextColor(TFT_YELLOW);

  etft.setTTFFont(Arial_32);
  etft.setCursor(0, ypos);
  etft.print("Arial");
  ypos += etft.TTFLineSpace();

  etft.setCursor(0, ypos);
  etft.setTTFFont(Arial_32_Bold);
  etft.print("Arial Bold");
  ypos += etft.TTFLineSpace();

  etft.setCursor(0, ypos);
  etft.setTTFFont(Arial_32_Italic);
  etft.print("Arial Italic");
  ypos += etft.TTFLineSpace();

  etft.setCursor(0, ypos);
  etft.setTTFFont(Arial_32_Bold_Italic);
  etft.print("Arial Bold Italic");

  delay(3000);
  etft.setTextColor(TFT_YELLOW, TFT_BLUE);
  etft.fillScreen(TFT_BLACK);

  delay(1000);
  ypos = 0;
  etft.setTTFFont(Arial_32);
  etft.setCursor(0, ypos);
  etft.print("Arial");
  ypos += etft.TTFLineSpace();

  etft.setCursor(0, ypos);
  etft.setTTFFont(Arial_32_Bold);
  etft.print("Arial Bold");
  ypos += etft.TTFLineSpace();

  etft.setCursor(0, ypos);
  etft.setTTFFont(Arial_32_Italic);
  etft.print("Arial Italic");
  ypos += etft.TTFLineSpace();

  etft.setCursor(0, ypos);
  etft.setTTFFont(Arial_32_Bold_Italic);
  etft.print("Arial Bold Italic");
  ypos += etft.TTFLineSpace();

  delay(3000);
  tft.fillScreen(TFT_BLACK);
}

void loop(void) {
  // With background colour to erase ol  values
  etft.setTextColor(TFT_YELLOW, TFT_BLUE);
  etft.setTTFFont(Arial_32_Bold);

  for (int i = 100; i < 1000; i++ )
  {
    etft.setCursor(0, 0);
    etft.print(i);
    etft.print(" "); // Add space to clear stray pixels since not all glyphs are the same width
  }

  delay(2000);
}
