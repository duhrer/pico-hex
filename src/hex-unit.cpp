#include "hex-unit.hpp"
#include <math.h>

#define TOTAL_NEOPIXELS 37
#define NEOPIXELS_PIN 15

HexUnit::HexUnit() {
    neopixels = Adafruit_NeoPixel(TOTAL_NEOPIXELS, NEOPIXELS_PIN, NEO_GRB + NEO_KHZ800);

    // We have to do these here so we can use the Color method from the
    // Neopixels object passed to our constructor.
    row_colours[0] = neopixels.Color(MAX_BRIGHTNESS, 0, 0);
    row_colours[1] = neopixels.Color(MAX_BRIGHTNESS, MAX_BRIGHTNESS/2, 0);
    row_colours[2] = neopixels.Color(MAX_BRIGHTNESS, MAX_BRIGHTNESS, 0);
    row_colours[3] = neopixels.Color( 0, MAX_BRIGHTNESS, 0);
    row_colours[4] = neopixels.Color( 0, 0, MAX_BRIGHTNESS);
    row_colours[5] = neopixels.Color(MAX_BRIGHTNESS/2, 0, MAX_BRIGHTNESS);
    row_colours[6] = neopixels.Color(MAX_BRIGHTNESS, 0, MAX_BRIGHTNESS);

    BLACK = neopixels.Color(0,0,0);
    WHITE = neopixels.Color(MAX_BRIGHTNESS, MAX_BRIGHTNESS, MAX_BRIGHTNESS);
    BLUE = neopixels.Color(0, MAX_BRIGHTNESS, MAX_BRIGHTNESS);
}

void HexUnit::begin() {
    neopixels.begin();
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
struct PolarCoords {
    double radius;
    int angle;
};


// Lookup table for polar coordinates for all pixels. Radius is the distance
// from the midpoint.  Along the three major axes, each unit is 5mm apart, which
// treat as the diameter of an ideal circle whose midpoint is the same as the
// (square) neopixel.

/*

    All of the angles can be derived without any measurement or calculation.
    Many of the radii must be measured or derived, but many of them are the
    same, as diagrammed here.

                     {3.0, 120}, {X, 100}, {X, 80}, {3.0, 60},
                {Y, 140}, {2.0, 120}, {Z, 90}, {2.0, 60}, {Y, 40},
         {X, 160}, {Z, 150}, {1.0, 120}, {1.0, 60}, {Z, 30}, {X, 20},
    {3.0, 180}, {2.0, 180}, {1.0, 180}, {0.0, 0}, {1.0, 0}, {2.0, 0}, {3.0, 0},
         {X, 200}, {Z, 210}, {1.0, 240}, {1.0, 300}, {Z, 330.0}, {X, 340},
                {Y, 220}, {2.0, 240}, {Z, 270}, {2.0, 300}, {Y, 320},
                     {3.0, 240}, {X, 260}, {X, 280}, {3.0, 300}

    I measured X as 13 mm, Y as 13.2 mm, Z as 8.5 mm, and then divided each
    by 5 to get the value in terms of cell radii, i.e. 2.6, 2.64, and 1.7

*/

const struct PolarCoords polar_coordinates[37] =
{
                     {3.0, 120}, {2.6, 100}, {2.6, 80}, {3.0, 60},
                {2.64, 140}, {2.0, 120}, {1.7, 90}, {2.0, 60}, {2.64, 40},
         {2.6, 160}, {1.7, 150}, {1.0, 120}, {1.0, 60}, {1.7, 30}, {2.6, 20},
    {3.0, 180}, {2.0, 180}, {1.0, 180}, {0.0, 0}, {1.0, 0}, {2.0, 0}, {3.0, 0},
         {2.6, 200}, {1.7, 210}, {1.0, 240}, {1.0, 300}, {1.7, 330}, {2.6, 340},
                {2.64, 220}, {2.0, 240}, {1.7, 270}, {2.0, 300}, {2.64, 320},
                     {3.0, 240}, {2.6, 260}, {2.6, 280}, {3.0, 300}
};

// Scale percentage should be out of 100.
uint32_t scaleColourSaturation(uint32_t original_colour, int scale_percentage) {
    uint8_t first_byte  = original_colour & 0xFF;
    uint8_t second_byte = original_colour & (0xFF << 8);
    uint8_t third_byte  = original_colour & (0xFF << 16);
    uint8_t fourth_byte = original_colour & (0xFF << 24);

    uint8_t scaled_first_byte  = first_byte * scale_percentage / 100;
    uint8_t scaled_second_byte = second_byte * scale_percentage / 100;
    uint8_t scaled_third_byte  = third_byte * scale_percentage / 100;
    uint8_t scaled_fourth_byte  = fourth_byte * scale_percentage / 100;

    uint32_t scaled_colour = scaled_first_byte | (scaled_second_byte << 8) | (scaled_third_byte << 16) | (scaled_fourth_byte << 24);

    return scaled_colour;
}

uint32_t averageColours(uint32_t colour1, uint32_t colour2) {
    uint8_t colour1_first_byte  = colour1 & 0xFF;
    uint8_t colour1_second_byte = colour1 & (0xFF << 8);
    uint8_t colour1_third_byte  = colour1 & (0xFF << 16);
    uint8_t colour1_fourth_byte = colour1 & (0xFF << 24);

    uint8_t colour2_first_byte  = colour2 & 0xFF;
    uint8_t colour2_second_byte = colour2 & (0xFF << 8);
    uint8_t colour2_third_byte  = colour2 & (0xFF << 16);
    uint8_t colour2_fourth_byte = colour2 & (0xFF << 24);

    uint8_t average_first_byte  = (colour1_first_byte + colour2_first_byte)/2;
    uint8_t average_second_byte = (colour1_second_byte + colour2_second_byte)/2;
    uint8_t average_third_byte  = (colour1_third_byte + colour2_third_byte)/2;
    uint8_t average_fourth_byte = (colour1_fourth_byte + colour2_fourth_byte)/2;

    uint32_t average_colour = average_first_byte | (average_second_byte << 8) | (average_third_byte << 16) | (average_fourth_byte << 24);

    return average_colour;
}

void HexUnit::fillPolarRegion(uint32_t fill_colour, int fill_centre_radius, int fill_centre_degrees, int fill_radius) {
    double fill_centre_radians = fill_centre_degrees * (M_PI / 180);
    for (int index = 0; index < 37; index++) {
        // Calculate the distance between two points described using polar
        // coordinates:
        // 
        // https://greenemath.com/Trigonometry/43/Polar-Equations-Graphs-IILesson.html
        PolarCoords cell_centre_coords = polar_coordinates[index];
        double cell_centre_radians = cell_centre_coords.angle * (M_PI / 180);

        float distance = sqrt(
            pow(fill_centre_radius,2) + pow(cell_centre_coords.radius, 2)
            - (2 * cell_centre_coords.radius * fill_centre_radius * cos(cell_centre_radians - fill_centre_radians))
        );

        if (round(distance) < fill_radius) {
            // 
            // https://greenemath.com/Trigonometry/43/Polar-Equations-Graphs-IILesson.html
            PolarCoords cell_centre_coords = polar_coordinates[index];
            double cell_centre_radians = cell_centre_coords.angle * (M_PI / 180);

            float distance = sqrt(
                pow(fill_centre_radius,2) + pow(cell_centre_coords.radius, 2)
                - (2 * cell_centre_coords.radius * fill_centre_radius * cos(cell_centre_radians - fill_centre_radians))
            );

            // uint32_t cell_colour = neopixels.getPixelColor(index);
            if (floor(distance) < fill_radius) {
                // TODO: Make mixing optional before we enable this
                // // Fill at 100%, mixing with whatever's there.
                // uint32_t mixed_colour = averageColours(cell_colour, fill_colour);
                // neopixels.setPixelColor(index, mixed_colour);
                neopixels.setPixelColor(index, fill_colour);
            }
            // TODO: Make mixing optional.
            // else {
            //     // Fill proportionately, mixing with whatever's there.
            //     int percentage_in_cell = (int)(distance * 100) % 100;
            //     uint32_t scaled_colour = scaleColourSaturation(fill_colour, percentage_in_cell);
    
            //     uint32_t mixed_colour = averageColours(cell_colour, scaled_colour);
            //     neopixels.setPixelColor(index, mixed_colour);
            // }
        }
    }
}


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

void HexUnit::setRemappedPixelColour(uint32_t colour, int row, int column, const int *index_map, int index_map_columns) {
    int translated_pixel_index = index_map[(row * index_map_columns) + column];
    if (translated_pixel_index >= 0 && translated_pixel_index < 37 ) {
        this->neopixels.setPixelColor(translated_pixel_index, colour);
    }
}

uint32_t HexUnit::getRemappedPixelColour(int row, int column, const int *index_map, int index_map_columns) {
    int translated_pixel_index = index_map[(row * index_map_columns) + column];
    if (translated_pixel_index < 0 || translated_pixel_index > 36 ) {
        return 0;
    }
    else {
        return this->neopixels.getPixelColor(translated_pixel_index);
    }
};

void HexUnit::setRingPixelColour(uint32_t colour, int ringIndex, int pixelIndex) {
    setRemappedPixelColour(colour, ringIndex, pixelIndex, (int *) ring_cell_indices, 18);
};

uint32_t HexUnit::getRingPixelColour(int ringIndex, int pixelIndex) {
    return getRemappedPixelColour(ringIndex, pixelIndex, (int *) ring_cell_indices, 18);
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
    that the columns
 align vertically.

*/

const int interlaced_cell_indices[4][6] = {
    {-1,  0,  1,  2,  3, -1},
    { 9, 10, 11, 12, 13, 14},
    {22, 23, 24, 25, 26, 27},
    {-1, 33, 34, 35, 36, -1}
};


/*
    Italic layout, a 7 by 7 x/y matrix where each row is 1/2 square behind the previous. 

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

void HexUnit::setItalicPixelColour(uint32_t colour, int column, int row) {
    setRemappedPixelColour(colour, row, column, (int *) italic_cell_indices, 7);
};

uint32_t HexUnit::getItalicPixelColour(int column, int row) {
    return getRemappedPixelColour(column, row, (int *) italic_cell_indices, 7);
};

void HexUnit::fillItalicRow(uint32_t colour, int row) {
    for (int column = 0; column < 7; column++) {
        setItalicPixelColour(colour, column, row);
    }
};

void HexUnit::fillItalicRow(uint32_t colour, int row, int start_column, int num_cells) {
    for (int column = start_column; column < start_column + num_cells; column++) {
        setItalicPixelColour(colour, column, row);
    }
};

void HexUnit::fillItalicRow(uint32_t colour, int row, int start_column) {
    for (int column = start_column; column < 7; column++) {
        setItalicPixelColour(colour, column, row);
    }
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

void HexUnit::setSawtoothPixelColour(uint32_t colour, int column, int row) {
    setRemappedPixelColour(colour, row, column, (int *) sawtooth_cell_indices, 7);
};

uint32_t HexUnit::getSawtoothPixelColour(int column, int row) {
    return getRemappedPixelColour(row, column, (int *) sawtooth_cell_indices, 7);
};

void HexUnit::fillSawtoothRow(uint32_t colour, int row) {
    for (int column = 0; column < 7; column++) {
        setSawtoothPixelColour(colour, column, row);
    }
};

void HexUnit::fillSawtoothRow(uint32_t colour, int row, int start_column) {
    for (int column = start_column; column < 7; column++) {
        setSawtoothPixelColour(colour, column, row);
    }
};

void HexUnit::fillSawtoothRow(uint32_t colour, int row, int start_column, int num_cells) {
    for (int column = start_column; column < start_column + num_cells; column++) {
        setSawtoothPixelColour(colour, column, row);
    }
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