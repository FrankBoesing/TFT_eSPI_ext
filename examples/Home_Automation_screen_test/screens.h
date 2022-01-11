/*
 This code was automatically generated from graphic elements in a PowerPoint presentation

 Autogenerate code written by Kris Kasprzak kris.kasprzak@yahoo.com
 Use this code without warranty

 Rev  Date         Author     Desc
 1.0  06/06/2020   Kasprzak   Initial code
 1.1  01/08/2022   Frank B    variable tft size,
                              some improvements
*/

#pragma once

#include <font_Arial.h> // Size: 8, 11, 15
#include <font_ArialBold.h> // Size: 8, 11, 13, 15

// Hints:
//	- add tft.setRotation(1) or tft.setRotation(3) for landscape mode
//	- for texts, you may want to specify the background color:
//		tft.setTextColor(ForeColor, BackColor);
//	- note, displays handle rotations differently so you may have to swap fillScreenVGradient for fillScreenHGradient

// Rounded rectangles will be turned into Adafruit buttons
// add code for touch screen processing

void Screen1(void)
{
	tft.fillScreen(0xFFFF);

// Rectangle 5
	tft.fillRect(61, 59, 375, 204, 0xF800);
	tft.fillRect(61, 59, 375, 14, 0x4398);
	tft.fillRect(61, 262, 375, 14, 0x4398);
// Isosceles Triangle 6
	tft.fillTriangle(324, 145, 420, 145, 372, 76, 0xFFE0);
// Oval 7
	tft.fillCircle(372, 122, 10, 0x0000);

// TextBox 19
	tft.setTextColor(0xFFFF);
	tft.setTTFFont(Arial_14_Bold);
	tft.setCursor(104, 107);
	tft.print(F("Warning"));

// TextBox 20
	tft.setTTFFont(Arial_14);
	tft.setCursor(108, 167);
	tft.print(F("Restart the system."));
}

void Screen2(void)
{
	tft.fillScreen(0x0000);

// TextBox 2
	tft.fillRect(0, 0, 479, 60, 0x39C7);
	tft.setTextColor(0xFFFF);
	tft.setTTFFont(Arial_13_Bold);
	tft.setCursor(10, 12);
	tft.print(F("HOME AUTOMATION"));

// Rectangle 5
	tft.fillRectHGradient(13, 79, 220, 228, 0x0861, 0x4A69);
	tft.setTTFFont(Arial_11_Bold);
	tft.setCursor(13, 79);
	tft.print(F("TIME"));

// Rectangle 11
	tft.fillRectHGradient(245, 78, 110, 230, 0x0861, 0x4A69);
	tft.setCursor(245, 78);
	tft.print(F("TEMP"));

// Rectangle 12
	tft.fillRectHGradient(361, 78, 110, 230, 0x0861, 0x4A69);
	tft.setCursor(361, 78);
	tft.print(F("%RH"));

// TextBox 19
	tft.setTTFFont(Arial_11);
	tft.setCursor(29, 101);
	tft.print(F("8:44 PM"));

// TextBox 27
	tft.setCursor(265, 159);
	tft.print(F("82.1"));

// TextBox 29
	tft.setCursor(266, 280);
	tft.print(F("80.2"));

// TextBox 30
	tft.setCursor(381, 280);
	tft.print(F("32"));

// Table 8
	tft.drawFastHLine(12, 136, 220, 0xFFFF);
	tft.fillRect(12, 136, 112, 43, 0x010C);
	tft.setTTFFont(Arial_8_Bold);
	tft.setCursor(23, 149 );
	tft.print(F("Door"));

	tft.fillRect(124, 136, 109, 43, 0x010C);
	tft.setCursor(135, 149 );
	tft.print(F("Status"));

	tft.drawFastHLine(12, 179, 220, 0xFFFF);
	tft.setTTFFont(Arial_8);
	tft.setCursor(18, 187 );
	tft.print(F("Front"));

	tft.setTextColor(0x058A);
	tft.setCursor(130, 187 );
	tft.print(F("Closed"));

	tft.drawFastHLine(12, 205, 220, 0xFFFF);
	tft.setTextColor(0xFFFF);
	tft.setCursor(18, 213 );
	tft.print(F("Back"));

	tft.setTextColor(0x058A);
	tft.setCursor(130, 213 );
	tft.print(F("Closed"));

	tft.drawFastHLine(12, 231, 220, 0xFFFF);
	tft.setTextColor(0xFFFF);
	tft.setCursor(18, 239 );
	tft.print(F("Garage"));

	tft.setTextColor(0xF800);
	tft.setCursor(130, 239 );
	tft.print(F("Open"));

	tft.drawFastHLine(12, 257, 220, 0xFFFF);
	tft.setTextColor(0xFFFF);
	tft.setCursor(18, 265 );
	tft.print(F("Side"));

	tft.setTextColor(0x058A);
	tft.setCursor(130, 265 );
	tft.print(F("Closed"));

	tft.drawFastHLine(12, 283, 220, 0xFFFF);
	tft.setTextColor(0xFFFF);
	tft.setCursor(18, 291 );
	tft.print(F("Porch"));

	tft.setTextColor(0xF800);
	tft.setCursor(130, 291 );
	tft.print(F("Closed"));

	tft.drawFastHLine(12, 309, 220, 0xFFFF);
	tft.drawFastHLine(12, 136, 220, 0xFFFF);
	tft.drawFastVLine(12, 136, 171, 0xFFFF);
	tft.drawFastVLine(124, 136, 171, 0xFFFF);
	tft.drawFastVLine(233, 136, 171, 0xFFFF);

// TextBox 32
	tft.setTextColor(0xFFFF);
	tft.setTTFFont(Arial_11);
	tft.setCursor(382, 159);
	tft.print(F("55"));

// TextBox 33
	tft.setCursor(266, 219);
	tft.print(F("79.8"));

// TextBox 34
	tft.setCursor(381, 219);
	tft.print(F("51"));

// TextBox 23
	tft.setTTFFont(Arial_11_Bold);
	tft.setCursor(380, 257);
	tft.print(F("NOW"));

// TextBox 24
	tft.setCursor(381, 136);
	tft.print(F("MAX"));

// TextBox 25
	tft.setCursor(380, 196);
	tft.print(F("MIN"));

// TextBox 26
	tft.setCursor(262, 257);
	tft.print(F("NOW"));

// TextBox 28
	tft.setCursor(263, 136);
	tft.print(F("MAX"));

// TextBox 31
	tft.setCursor(262, 196);
	tft.print(F("MIN"));

  Button1.drawButton();
}

// End of the auto-generated code
