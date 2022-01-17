// Test the font rendering with and without background colour

#include <SPI.h>
#include <TFT_eSPI_ext.h>

// Fonts in these files are available in the following sizes:
// 8, 9, 10, 11, 12, 13, 14, 16, 18, 20, 24, 28, 32, 40, 48, 60, 72 and 96
// This example uses size 32

#include <font_Arial.h>
#include <font_ArialBold.h>
#include <font_ArialItalic.h>
#include <font_ArialBoldItalic.h>

TFT_eSPI_ext tft = TFT_eSPI_ext();

uint16_t ypos = 0;
  
void setup() {
  Serial.begin(115200);
  tft.begin();
  tft.setRotation(1);

  tft.fillScreen(TFT_BLACK);
  Serial.println("Font test"); 

  tft.setTextColor(TFT_YELLOW);

  tft.setTTFFont(Arial_32);
  tft.setCursor(0, ypos);
  tft.print("Arial");
  ypos += tft.TTFLineSpace();

  tft.setCursor(0, ypos);
  tft.setTTFFont(Arial_32_Bold);
  tft.print("Arial Bold");
  ypos += tft.TTFLineSpace();

  tft.setCursor(0, ypos);
  tft.setTTFFont(Arial_32_Italic);
  tft.print("Arial Italic");
  ypos += tft.TTFLineSpace();

  tft.setCursor(0, ypos);
  tft.setTTFFont(Arial_32_Bold_Italic);
  tft.print("Arial Bold Italic");

  delay(3000);
  tft.setTextColor(TFT_YELLOW, TFT_BLUE);
  tft.fillScreen(TFT_BLACK);

  delay(1000);
  ypos = 0;
  tft.setTTFFont(Arial_32);
  tft.setCursor(0, ypos);
  tft.print("Arial");
  ypos += tft.TTFLineSpace();

  tft.setCursor(0, ypos);
  tft.setTTFFont(Arial_32_Bold);
  tft.print("Arial Bold");
  ypos += tft.TTFLineSpace();

  tft.setCursor(0, ypos);
  tft.setTTFFont(Arial_32_Italic);
  tft.print("Arial Italic");
  ypos += tft.TTFLineSpace();

  tft.setCursor(0, ypos);
  tft.setTTFFont(Arial_32_Bold_Italic);
  tft.print("Arial Bold Italic");
  ypos += tft.TTFLineSpace();

  delay(3000);
  tft.fillScreen(TFT_BLACK);
}

void loop(void) {
  // With background colour to erase ol  values
  tft.setTextColor(TFT_YELLOW, TFT_BLUE);
  tft.setTTFFont(Arial_32_Bold);

  for (int i = 100; i < 1000; i++ )
  {
    tft.setCursor(0, 0);
    tft.print(i);
    tft.print(" "); // Add space to clear stray pixels since not all glyphs are the same width
  }

  delay(2000);
}
