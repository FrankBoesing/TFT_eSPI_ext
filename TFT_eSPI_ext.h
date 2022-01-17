#pragma once
//#include <Arduino.h> // This causes problems with Arduino Nano Connect (board package bug)

typedef struct
{
  const unsigned char *index;
  const unsigned char *unicode;
  const unsigned char *data;
  unsigned char version;
  unsigned char reserved;
  unsigned char index1_first;
  unsigned char index1_last;
  unsigned char index2_first;
  unsigned char index2_last;
  unsigned char bits_index;
  unsigned char bits_width;
  unsigned char bits_height;
  unsigned char bits_xoffset;
  unsigned char bits_yoffset;
  unsigned char bits_delta;
  unsigned char line_space;
  unsigned char cap_height;
} tftfont_t;

#ifdef __cplusplus
#include <TFT_eSPI.h>

#define inherited TFT_eSPI

class TFT_eSPI_ext : public TFT_eSPI
{
public:
  size_t write(uint8_t c)
  {
    if (font)
    {
      if (c == '\n')
      {
        cursor_y += font->line_space;
        cursor_x = 0;
      }
      else
      {
        drawFontChar(c);
      }
      return 1;
    }
    else
      return inherited::write(c);
  }

  void setTTFFont(const tftfont_t &f)
  {
    font = &f;
    setTextFont(255);
  }

  void drawFontChar(uint16_t c)
  {

    uint32_t bitoffset;
    const uint8_t *data;

    if (c >= font->index1_first && c <= font->index1_last)
    {
      bitoffset = c - font->index1_first;
      bitoffset *= font->bits_index;
    }
    else if (c >= font->index2_first && c <= font->index2_last)
    {
      bitoffset = c - font->index2_first + font->index1_last - font->index1_first + 1;
      bitoffset *= font->bits_index;
    }
    else if (font->unicode)
    {
      return; // TODO: implement sparse unicode
    }
    else
    {
      return;
    }

    data = font->data + fetchbits_unsigned(font->index, bitoffset, font->bits_index);
    bitoffset = 0;
    uint32_t encoding = fetchbits_unsigned(data, bitoffset, 3);
    if (encoding != 0)
      return;

    uint32_t width = fetchbits_unsigned(data, bitoffset, font->bits_width);
    uint32_t height = fetchbits_unsigned(data, bitoffset, font->bits_height);

    int16_t xoffset = fetchbits_signed(data, bitoffset, font->bits_xoffset);
    int16_t yoffset = fetchbits_signed(data, bitoffset, font->bits_yoffset);
    uint32_t delta = fetchbits_unsigned(data, bitoffset, font->bits_delta);

    if (last_cursor_x != cursor_x)
    {
      bg_cursor_x = cursor_x;
    }

    // horizontally, we draw every pixel, or none at all
    if (cursor_x < 0)
    {
      cursor_x = 0;
      bg_cursor_x = 0;
    }
    int16_t origin_x = cursor_x + xoffset;

    if (origin_x < 0)
    {
      cursor_x -= xoffset;
      origin_x = 0;
    }

    if (origin_x + (int16_t)width > _width)
    {
      if (!textwrapX)
        return;
      origin_x = 0;
      bg_cursor_x = 0;
      if (xoffset >= 0)
      {
        cursor_x = 0;
      }
      else
      {
        cursor_x = -xoffset;
      }
      cursor_y += font->line_space;
    }

    if (cursor_y >= _height)
      return;
    cursor_x += delta;

    last_cursor_x = cursor_x;

    if (height == 0)
    {
      // White space character
      if (textcolor != textbgcolor) fillRect(bg_cursor_x, cursor_y, delta, font->line_space, textbgcolor);
      bg_cursor_x += delta;
      return;
    }

    int16_t linecount = height;
    uint32_t y = cursor_y + font->cap_height - height - yoffset;
    int32_t bg_width = (origin_x  +  width) - bg_cursor_x;

    // Fill top section
    if (textcolor != textbgcolor) fillRect(bg_cursor_x, cursor_y, bg_width, y - cursor_y, textbgcolor);

    startWrite();
    while (linecount)
    {
      uint32_t xsize, bits, n, x;

      if (fetchbit(data, bitoffset) == 0)
      {
        n = 1;
      }
      else
      {
        n = 2 + fetchbits_unsigned(data, bitoffset, 3);
      }

      // Fill n lines
      if (textcolor != textbgcolor) fillRect(bg_cursor_x, y, bg_width, n, textbgcolor);

      x = 0;
      do
      {
        xsize = width - x;
        if (xsize > 32)
          xsize = 32;
        bits = fetchbits_unsigned(data, bitoffset, xsize);
        if (bits != 0)
          drawFontBits(bits, xsize, origin_x + x, y, n);
        x += xsize;
      } while (x < width);
      y += n;
      linecount -= n;
    }
    endWrite();
    // Fill bottom section
    if (textcolor != textbgcolor) fillRect(bg_cursor_x, y, bg_width, (cursor_y + font->line_space) - y, textbgcolor);
    bg_cursor_x = origin_x  +  width;
  }

// Measure the dimensions for a single character
void TTFmeasureChar(unsigned char c, uint32_t* w, uint32_t* h) {
	if (!font) return;

  *h = font->cap_height;
  *w = 0;

  if (c == 0xa0) c = ' '; // Treat non-breaking space as normal space

  uint32_t bitoffset;
  const uint8_t *data;

  if (c >= font->index1_first && c <= font->index1_last) {
    bitoffset = c - font->index1_first;
    bitoffset *= font->bits_index;
  }
  else if (c >= font->index2_first && c <= font->index2_last) {
    bitoffset = c - font->index2_first + font->index1_last - font->index1_first + 1;
    bitoffset *= font->bits_index;
  }
  else if (font->unicode) {
    return; // TODO: implement sparse unicode
  }
  else {
    return;
  }

  data = font->data + fetchbits_unsigned(font->index, bitoffset, font->bits_index);
  bitoffset = 0;
  uint32_t encoding = fetchbits_unsigned(data, bitoffset, 3);

  if (encoding != 0) return;

  //uint32_t width =
  fetchbits_unsigned(data, bitoffset, font->bits_width);
  //uint32_t height =
  fetchbits_unsigned(data, bitoffset, font->bits_height);
  //int16_t xoffset =
  fetchbits_signed(data, bitoffset, font->bits_xoffset);
  //int16_t yoffset =
  fetchbits_signed(data, bitoffset, font->bits_yoffset);
  uint32_t delta = fetchbits_unsigned(data, bitoffset, font->bits_delta);
  *w = delta;
}

uint32_t TTFtextWidth(const char* text, int16_t num) {
	uint32_t maxH = 0;
	uint32_t currH = 0;
  int16_t i = 0;
	char c;
	if (num == 0) num = 0xffff;
	while ( i < num && (c=text[i]) != 0) {
		if (c == '\n') {
			// For multi-line strings, retain max width
			if (currH > maxH)
				maxH = currH;
			currH = 0;
		}
		else {
			uint32_t h, w;
			TTFmeasureChar(c, &w, &h);
			currH += w;
		}
    i++;
	}
	uint32_t h = maxH > currH ? maxH : currH;
	return h;
}

// Return the height of a text string
// - num =  max characters to process, or 0 for entire string (null-terminated)
uint16_t TTFtextHeight(const char* text, int16_t num) {
	int16_t lines = 0;
  int16_t i = 0;
  char c;
	if (num == 0) num = 0xffff;
  while ( i < num && (c=text[i]) != 0)
	{
		if (c == '\n') lines++;
    i++;
	}
	return (lines * TTFLineSpace() + TTFontCapHeight());
}

	uint16_t TTFLineSpace() { return (font) ? font->line_space : 0; }

protected:
  const tftfont_t *font = nullptr;
	uint16_t TTFontCapHeight() { return (font) ? font->cap_height : 0; }

  int32_t bg_cursor_x;
  int32_t last_cursor_x = 0;

private:
  inline uint32_t fetchbit(const uint8_t *p, uint32_t &index)
  {
    uint32_t r = (p[index >> 3] & (0x80 >> (index & 7)));
    index++;
    return r;
  }

  uint32_t fetchbits_unsigned(const uint8_t *p, uint32_t &index, uint32_t required)
  {
    uint32_t val;
    uint8_t *s = (uint8_t *)&p[index >> 3];
    val = s[0] << 24 | (s[1] << 16) | (s[2] << 8) | s[3];
    val <<= index & 7;               // shift out used bits
    if (32 - (index & 7) < required) // need to get more bits
      val |= (s[4] >> (8 - (index & 7)));
    val >>= 32 - required; // right align the bits
    index += required;
    return val;
  }

  int32_t fetchbits_signed(const uint8_t *p, uint32_t &index, uint32_t required)
  {
    uint32_t val = fetchbits_unsigned(p, index, required);
    if (val & (1 << (required - 1)))
      return (int32_t)val - (1 << required);
    return val;
  }

  void drawFontBits(uint32_t bits, uint32_t numbits, uint32_t x, uint32_t y, uint32_t repeat)
  {
    bits <<= 32 - numbits; // left align bits
    do
    {
      uint32_t w = __builtin_clz(bits); // skip over leading zeros
      if (w > numbits)
        w = numbits;
      numbits -= w;
      x += w;
      bits <<= w;
      w = __builtin_clz(~bits); //count leading ones
      if (w > 0)
      {
        if (w > numbits)
          w = numbits;
        numbits -= w;
        bits <<= w;
        setWindow(x, y, x + w - 1, y + repeat - 1); // write a block of pixels w x repeat sized
        x += w;
        w *= repeat;
        pushBlock(textcolor, w);
      }
    } while (bits > 0 && numbits > 0);
  }

};

#undef inherited
#endif
