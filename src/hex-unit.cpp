#include "hex-unit.hpp"
#include <math.h>

#define TOTAL_NEOPIXELS 37
#define NEOPIXELS_PIN 10

// TODO: Add variables for the number of hex units.
HexUnit::HexUnit() {
    neopixels = HelpfulNeopixel(TOTAL_NEOPIXELS, NEOPIXELS_PIN, NEO_GRB + NEO_KHZ800);

    // We have to initialise the colours now because we need the Color method
    // from the neopixel object (for now).
    updateColours();
}

void HexUnit::updateColours() {
    row_colours[0] = neopixels.Color(brightness, 0, 0);
    row_colours[1] = neopixels.Color(brightness, brightness/2, 0);
    row_colours[2] = neopixels.Color(brightness, brightness, 0);
    row_colours[3] = neopixels.Color( 0, brightness, 0);
    row_colours[4] = neopixels.Color( 0, 0, brightness);
    row_colours[5] = neopixels.Color(brightness/2, 0, brightness);
    row_colours[6] = neopixels.Color(brightness, 0, brightness);

    BLACK = neopixels.Color(0,0,0);
    WHITE = neopixels.Color(brightness, brightness, brightness);
    BLUE = neopixels.Color(0, brightness, brightness);

    clear();
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

// TODO: Add optional unit offset to all drawing functions.

// We only support filling everything because anything else should use a
// layout-specific drawing function. Does not handle any kind of mixing.
void HexUnit::fill(uint32_t colour) {
    neopixels.fill(colour);
}

void HexUnit::decreaseBrightness() {
    if (brightness >= 4) {
        // We're aiming for a power of two minus one.
        brightness = ((brightness + 1)/2) - 1;

        updateColours();
    }
}

void HexUnit::increaseBrightness() {
    // We're aiming for a power of two minus one.
    if (brightness <= 128) {
        brightness *= ((brightness + 1) * 2) - 1;

        updateColours();
    }
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
X, 80}, {3.0, 60},
                {Y, 140}, {2.0, 120}, {Z, 90}, {2.0, 60}, {Y, 40},
         {X, 160}, {Z, 150}, {1.0, 120}, {1.0, 60}, {Z, 30}, {X, 20},
    {3.0, 180}, {2.0, 180}, {1.0, 180}, {0.0, 0}, {1.0, 0}, {2.0, 0}, {3.0, 0},
         {X, 200}, {Z, 210}, {1.0, 240}, {1.0, 300}, {Z, 330.0}, {X, 340},
                {Y, 220}, {2.0, 240}, {Z, 270}
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

// Scale a colour proportionately. Scale percentage should be out of 100.
uint32_t scaleColourSaturation(uint32_t original_colour, int scale_percentage) {
    uint8_t first_byte  = original_colour & 0xFF;
    uint8_t second_byte = original_colour >> 8 & 0xFF;
    uint8_t third_byte  = original_colour >> 16 & 0xFF;
    uint8_t fourth_byte = original_colour >> 24 & 0xFF;

    uint8_t scaled_first_byte  = (first_byte * scale_percentage) / 100;
    uint8_t scaled_second_byte = (second_byte * scale_percentage) / 100;
    uint8_t scaled_third_byte  = (third_byte * scale_percentage) / 100;
    uint8_t scaled_fourth_byte  = (fourth_byte * scale_percentage) / 100;

    uint32_t scaled_colour = scaled_first_byte | (scaled_second_byte << 8) | (scaled_third_byte << 16) | (scaled_fourth_byte << 24);

    return scaled_colour;
}

// Add each channel, discarding anything over the max. It costs us next to
// nothing to handle four bytes, so we do. Used for CHANNEL_SUM mixing mode.
uint32_t HexUnit::sumChannelColours(uint32_t colour1, uint32_t colour2) {
    uint8_t colour1_first_byte  = colour1 & 0xFF;
    uint8_t colour1_second_byte = colour1 >> 8 & 0xFF;
    uint8_t colour1_third_byte  = colour1 >> 16 & 0xFF;
    uint8_t colour1_fourth_byte = colour1 >> 24 & 0xFF;

    uint8_t colour2_first_byte  = colour2 & 0xFF;
    uint8_t colour2_second_byte = colour2 >> 8 & 0xFF;
    uint8_t colour2_third_byte  = colour2 >> 16 & 0xFF;
    uint8_t colour2_fourth_byte = colour2 >> 24 & 0xFF;

    uint8_t sum_first_byte  = fmin((colour1_first_byte + colour2_first_byte), MAX_BRIGHTNESS);
    uint8_t sum_second_byte = fmin((colour1_second_byte + colour2_second_byte), MAX_BRIGHTNESS);
    uint8_t sum_third_byte  = fmin((colour1_third_byte + colour2_third_byte), MAX_BRIGHTNESS);
    uint8_t sum_fourth_byte = fmin((colour1_fourth_byte + colour2_fourth_byte), MAX_BRIGHTNESS);

    uint32_t summed_colour = sum_first_byte | (sum_second_byte << 8) | (sum_third_byte << 16) | (sum_fourth_byte << 24);

    return summed_colour;
}

// Mix so that blue is zeroed, and anything over 255 on the red channel spills
// over to green.  This should result in a transition from red -> orange ->
// yellow as energy is added. White is ignored/zeroed. Used for FLAME mixing
// mode.
uint32_t HexUnit::mixFlameColours(uint32_t colour1, uint32_t colour2) {
    struct ColourChannels channels1 = neopixels.channelsFromColour(colour1);
    struct ColourChannels channels2 = neopixels.channelsFromColour(colour2);

    struct ColourChannels combinedChannels = { 0, 0, 0, 0 };
    int combined_green = channels1.g + channels2.g;
    if (combined_green > MAX_BRIGHTNESS) {
        combinedChannels.g = MAX_BRIGHTNESS;
    }
    else {
        combinedChannels.g = combined_green;
    }

    int combined_red = channels1.r + channels2.r;
    if (combined_red > MAX_BRIGHTNESS) {
        combinedChannels.r = MAX_BRIGHTNESS;
        int remainder = combined_red - MAX_BRIGHTNESS;
        if ((remainder + combinedChannels.g) > MAX_BRIGHTNESS) {
            int second_remainder = (remainder + combinedChannels.g) - MAX_BRIGHTNESS;

            combinedChannels.g = MAX_BRIGHTNESS;

            // still not sure I like having the white peaks.
            combinedChannels.b = second_remainder < MAX_BRIGHTNESS ? second_remainder : MAX_BRIGHTNESS;
        }
        else {
            combinedChannels.g += remainder;
        }
    }
    else {
        combinedChannels.r = combined_red;
    }

    return neopixels.colourFromChannels(combinedChannels);
}

// Mix in "pastel mode", i.e. anything over MAX_BRIGHTNESS in the primary
// channel ups the other two channels, so that the net result is "whiter".
uint32_t HexUnit::mixPastelColours(uint32_t colour1, uint32_t colour2, enum PastelMode pastelMode) {
    ColourChannels channels1 = neopixels.channelsFromColour(colour1);
    ColourChannels channels2 = neopixels.channelsFromColour(colour2);

    ColourChannels combined = { 0, 0, 0, 0 };

    int combined_primary = 0;
    int current_non_primary_channel_level = 0;

    int new_primary_level = 0;
    int new_nonprimary_channel_level = 0;

    if (pastelMode == RED_IS_PRIMARY) {
        combined_primary = channels1.r + channels2.r;
        current_non_primary_channel_level = (channels1.g + channels2.g + channels1.b + channels2.b) / 4;
    }
    else if (pastelMode == GREEN_IS_PRIMARY) {
        combined_primary = channels1.g + channels2.g;
        current_non_primary_channel_level = (channels1.r + channels2.r + channels1.b + channels2.b) / 4;
    }
    else if (pastelMode == BLUE_IS_PRIMARY) {
        combined_primary = channels1.b + channels2.b;
        current_non_primary_channel_level = (channels1.r + channels2.r + channels1.g + channels2.g) / 4;
    }

    if (combined_primary > MAX_BRIGHTNESS) {
        new_primary_level = MAX_BRIGHTNESS;
        // Divide the overflow between the two channels.
        int remainder = (combined_primary - MAX_BRIGHTNESS) / 2;
        new_nonprimary_channel_level = (remainder + current_non_primary_channel_level) > MAX_BRIGHTNESS ? MAX_BRIGHTNESS : (remainder + current_non_primary_channel_level);
    }
    else {
        new_primary_level = combined_primary;
        new_nonprimary_channel_level = current_non_primary_channel_level;
    }

    combined.r = pastelMode == RED_IS_PRIMARY ? new_primary_level : new_nonprimary_channel_level;
    combined.g = pastelMode == GREEN_IS_PRIMARY ? new_primary_level : new_nonprimary_channel_level;
    combined.b = pastelMode == BLUE_IS_PRIMARY ? new_primary_level : new_nonprimary_channel_level;

    return neopixels.colourFromChannels(combined);
}

void HexUnit::fillPolarRegion(uint32_t fill_colour, int fill_centre_radius, int fill_centre_degrees, int fill_radius, enum MixMode mixMode) {
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

        // Here's the formula provided on this page:
        // https://raw.org/math/calculate-the-intersection-area-of-two-circles/
        //
        // d = the distance between the two centres (calculated above).
        // r1 = the radius of the pixel, i.e. 1.
        // r2 = the radius of the circle we're drawing i.e. fill_radius.
        //
        // Arr = r1 squared, i.e. 1
        // Brr = r2 squared.
        //
        // tA = 2 * acos((Arr + d * d - Brr) / (2 * d * r1))
        // tB = 2 * acos((Brr + d * d - Arr) / (2 * d * r2))
        //
        // Given all that, the area is:
        // 0.5 * (Arr * (tA - sin (tA)) + Brr * (tB - sin(tB))
        //
        // The area of the pixel is 1 * 1 * PI, so we divide the area by PI to
        // determine how much of the colour should be added to the pixel.

        // This page provides another formula which relies less on order of
        // operations (parentheses, melon farmer, do you use them?).
        // https://www.researchgate.net/figure/Area-of-overlapping-between-two-circles-of-different-sizes_fig3_275550769
        //
        // d = the distance between the two centres (calculated above).
        // r1 = the radius of the pixel, i.e. 1.
        // r2 = the radius of the circle we're drawing i.e. fill_radius.
        //
        // Arr = r1 squared, i.e. 1
        // Brr = r2 squared.
        //
        // area = (Arr * acos((d * d) + Arr - Brr / (2 * d * r1)) +
        //        (Brr * acos(((d * d) + Brr - Arr)/(2 * d * r2)) -
        //        (0.5 * sqrt((r1 + r2 -d)(d + r1 - r2)(d - r1 + r2)(d + r1 + r2)))



        // There's overlap if the distance is less than the sum of the two radii
        // (and the radii of the pixel is always 0.5).  If the distance is zero,
        // then there's perfect overlap and the pixel gets 100% of the region's
        // energy. Otherwise, we use the above formula to calculate how much
        // energy to contribute to this pixel.
        // TODO: "eye" animation seems blown out, check old logic.
        // if (distance < (fill_radius + 0.5)) {
        if (distance < fill_radius) {
            int percentage_in_cell;
            // TODO: Use the full formula above if this isn't sufficiently good-looking.
            if (distance < (fill_radius / 2)) {
                percentage_in_cell = 100;
            }
            else {
                percentage_in_cell = 75;
            }

            uint32_t scaled_colour = scaleColourSaturation(fill_colour, percentage_in_cell);

            // No mixing, only fill nearly full hits, and fill them at 100%.
            if (mixMode == MixMode::NONE) {
                neopixels.setPixelColor(index, scaled_colour);
            }
            else {
                uint32_t pixel_colour = neopixels.getPixelColor(index);
                uint32_t mixed_colour;

                switch (mixMode) {
                    case MixMode::FLAME:
                        mixed_colour = mixFlameColours(scaled_colour, pixel_colour);
                        break;
                    case MixMode::PASTEL_ONE:
                        mixed_colour = mixPastelColours(scaled_colour, pixel_colour, RED_IS_PRIMARY);
                        break;
                    case MixMode::PASTEL_TWO:
                        mixed_colour = mixPastelColours(scaled_colour, pixel_colour, GREEN_IS_PRIMARY);
                        break;
                    case MixMode::PASTEL_THREE:
                        mixed_colour = mixPastelColours(scaled_colour, pixel_colour, BLUE_IS_PRIMARY);
                        break;
                    default:
                        mixed_colour = sumChannelColours(scaled_colour, pixel_colour);
                        break;                    
                }

                neopixels.setPixelColor(index, mixed_colour);
                // neopixels.setPixelColor(index, neopixels.Color(0, 0, MAX_BRIGHTNESS));
            }
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

/*

    A layout to treat the unit as three faces of a cube with optional coloured
    vertices. Face 1:

          00  01  02
        04  05  06
      09  10  11

    Face 2:

      22  23  24
        28  29  30
          33  34  35

    Face 3:
         08
       13  14
     19  20  21
       26  27
         32

    Vertices:
                      03
                    07
                  12
    15  16  17  18 
                  25 
                    31
                      36         
*/

// All faces except for the vertices are arranged from top to bottom and left to
// right, to support setting individual pixel values by row and column.
const int cubic_cell_indices[4][10] = {
    {0, 1, 2, 4, 5, 6, 9, 10, 11, -1},
    {22, 23, 24, 28, 29, 30, 33, 34, 35, -1},
    {19, 13, 8, 26, 20, 14, 32, 27, 21, -1},
    {3, 7, 12, 15, 16, 17, 18, 25, 31, 36}
};

void HexUnit::fillCubicFace(uint32_t colour, int face) {
    for (int face_cell_index = 0; face_cell_index < 10; face_cell_index++) {
        int real_cell_index = cubic_cell_indices[face][face_cell_index];
        if (real_cell_index != -1) {
            neopixels.setPixelColor(real_cell_index, colour);
        }
    }
}

void HexUnit::setCubicPixelColor(uint32_t colour, int face, int row, int column) {
    int cell_index = cubic_cell_indices[face][(row * 3) + column];

    if (cell_index != -1) {
        neopixels.setPixelColor(cell_index, colour);
    }
}

// I could add row and column filling options depending, but this seems
// sufficient for now.