#include "hex-unit.hpp"

#define TOTAL_NEOPIXELS 37
#define NEOPIXELS_PIN 15

HexUnit::HexUnit() {
    neopixels = Adafruit_NeoPixel(TOTAL_NEOPIXELS, NEOPIXELS_PIN, NEO_RGB + NEO_KHZ800);
}

void HexUnit::clear() {
    neopixels.clear();
}

void HexUnit::show() {
    neopixels.show();
}

// We only support filling everything because anything else should use a
// layout-specific drawing function. Does not handle any kind of mixing.
void HexUnit::fill(uint32_t colour) {
    neopixels.fill(colour);
}

/*

    The base layout of the hex unit pixel indexes is:

          00  01  02  03
        04  05  06  07  08
      09  10  11  12  13  14
    15  16  17  18  19  20  21
      22  23  24  25  26  27
        28  29  30  31  32
          33  34  35  36

    This class remaps this layout to more easily display different types of
    visualisations.

*/

// "Polar" layout, where positions are tracked in terms of the distance
// (radius) and direction (angle) relative to cell 18.

// TODO: Class for polar coordinates

// TODO: Lookup table for polar coordinates for all pixels.

/*
    "ring" layout, where all pixels are tracked in terms of ring and ring index.

    0: 18
    1: 11, 12, 19, 25, 24, 17
    2: 05, 06, 07, 13, 20, 26, 31, 30, 29, 23, 16, 10
    3: 00, 01, 02, 03, 08, 14, 21, 27, 32, 36, 35, 34, 33, 28, 22, 15, 09, 04

*/

const int ring_cell_indices[4][18] = {
    { 18, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
    { 11, 12, 19, 25, 24, 17, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
    {  5,  6,  7, 13, 20, 26, 31, 30, 29, 23, 16, 10, -1, -1, -1, -1, -1, -1 },
    {  0,  1,  2,  3,  8, 14, 21, 27, 32, 36, 35, 34, 33, 28, 22, 15,  9,  4 }
};

void HexUnit::setRingPixelColour(uint32_t colour, int ringIndex, int pixelIndex) {
    int translated_pixel_index = ring_cell_indices[ringIndex][pixelIndex];
    if (translated_pixel_index >= 0 && translated_pixel_index < 37 ) {
        this->neopixels.setPixelColor(translated_pixel_index, colour);
    }
};

uint32_t HexUnit::getRingPixelColour(int ringIndex, int pixelIndex) {
    int translated_pixel_index = ring_cell_indices[ringIndex][pixelIndex];
    if (translated_pixel_index < 0 || translated_pixel_index > 36 ) {
        return 0;
    }
    else {
        return this->neopixels.getPixelColor(translated_pixel_index);
    }
};

void HexUnit::fillRing(uint32_t colour, int ringIndex) {
    int end_index = ringIndex > 0 ? (ringIndex * 6) : 1;
    for (int pixel_index = 0 ; pixel_index < end_index; pixel_index++) {
        this->setRingPixelColour(colour, ringIndex, pixel_index);
    }
};

// TODO: This needs to support mixing, which means we need colour utility functions.
// void HexUnit::drawRingBand(uint32_t colour, int ringIndex, int pixelIndex, int bandWidth) {
// };


/*
    "Interlaced" layout, a 6 by 4 x/y matrix, where every other row is used so
    that the columns align vertically.

    -1  00  01  02  03  -1
    09  10  11  12  13  14
    22  23  24  25  26  27
    -1  33  34  35  36  -1

*/

const int interlaced_cell_indices[4][6] = {
    {-1,  0,  1,  2,  3, -1},
    { 9, 10, 11, 12, 13, 14},
    {22, 23, 24, 25, 26, 27},
    {-1, 33, 34, 35, 36, -1}
};


/*

    "Sawtooth" layout, a 7 by 7 x/y matrix with alternating shifted rows.

    -1  -1  00  01  02  03  -1
    -1  04  05  06  07  08  -1
    -1  09  10  11  12  13  14
    15  16  17  18  19  20  21
    -1  22  23  24  25  26  27
    -1  28  29  30  31  32  -1 
    -1  -1  33  34  35  36  -1
*/

const int sawtooth_cell_indices[7][7] = {
    { -1,  -1,   0,   1,   2,   3,  -1},
    { -1,   4,   5,   6,   7,   8,  -1},
    { -1,   9,  10,  11,  12,  13,  14},
    { 15,  16,  17,  18,  19,  20,  21},
    { -1,  22,  23,  24,  25,  26,  27},
    { -1,  28,  29,  30,  31,  32,  -1},
    { -1,  -1,  33,  34,  35,  36,  -1}
};


/*
    Italic layout, a 7 by 7 x/y matrix where each row is 1/2 square behind the previous. 

    00  01  02  03  -1  -1  -1
    04  05  06  07  08  -1  -1
    09  10  11  12  13  14  -1
    15  16  17  18  19  20  21
    -1  22  23  24  25  26  27
    -1  -1  28  29  30  31  32
    -1  -1  -1  33  34  35  36

*/

const int italic_cell_indices[7][7] = {
    {  0,   1,   2,   3,  -1,  -1,  -1},
    {  4,   5,   6,   7,   8,  -1,  -1},
    {  9,  10,  11,  12,  13,  14,  -1},
    { 15,  16,  17,  18,  19,  20,  21},
    { -1,  22,  23,  24,  25,  26,  27},
    { -1,  -1,  28,  29,  30,  31,  32},
    { -1,  -1,  -1,  33,  34,  35,  36}
};
/*
    Reverse italic layout, a 7 by 7 x/y matrix where each row is 1/2 square in
    front of the previous.

    -1  -1  -1  00  01  02  03
    -1  -1  04  05  06  07  08
    -1  09  10  11  12  13  14
    15  16  17  18  19  20  21
    22  23  24  25  26  27  -1
    28  29  30  31  32  -1  -1
    33  34  35  36  -1  -1  -1
*/

const int reverse_italic_cell_indices[7][7] = {
    { -1,  -1,  -1,   0,   1,   2,   3},
    { -1,  -1,   4,   5,   6,   7,   8},
    { -1,   9,  10,  11,  12,  13,  14},
    { 15,  16,  17,  18,  19,  20,  21},
    { 22,  23,  24,  25,  26,  27,  -1},
    { 28,  29,  30,  31,  32,  -1,  -1},
    { 33,  34,  35,  36,  -1,  -1,  -1}
};