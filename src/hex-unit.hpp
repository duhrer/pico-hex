#ifndef HEX_UNIT_H
#define HEX_UNIT_H

#include "helpful-neopixel.hpp"

// We support brightness levels as powers of two (minus one). Keep the
// brightness low to avoid shortening the life of the lights.
#define MIN_BRIGHTNESS 3
#define MAX_BRIGHTNESS 63

/*

    "Mix Mode" used in select drawing programs.

    NONE: Do not mix, last colour value set will be displayed.

    CHANNEL_SUM: Add the value of each channel to the current channel value,
    capping each at MAX_BRIGHTNESS.

    FLAME: Add the red channel to the current value.  Anything over
    MAX_BRIGHTNESS spills over to the green channel, so that the colour moves
    from dark red to solid red, to orange, to yellow.

    PASTEL_ONE: The first channel is the primary channel.  Anything over
    MAX_BRIGHTNESS spills over equally to the other two channels.

    PASTEL_TWO: The second channel is the primary channel.  Anything over
    MAX_BRIGHTNESS spills over equally to the other two channels.

    PASTEL_THREE: The third channel is the primary channel.  Anything over
    MAX_BRIGHTNESS spills over equally to the other two channels.

*/
enum MixMode {
    NONE,
    CHANNEL_SUM,
    FLAME,
    PASTEL_ONE,
    PASTEL_TWO,
    PASTEL_THREE
};

enum PastelMode {
    RED_IS_PRIMARY,
    GREEN_IS_PRIMARY,
    BLUE_IS_PRIMARY
};

class HexUnit {
    private: 
        // Generic functions used with different layout maps
        uint32_t getRemappedPixelColour(int row, int column, const int *index_map, int index_map_columns);
        void setRemappedPixelColour(uint32_t colour, int row, int column, const int *index_map, int index_map_columns);

        void updateColours();

    public:
        // Wrapped Neopixel object.
        HelpfulNeopixel neopixels;

        uint32_t BLACK;
        uint32_t WHITE;
        uint32_t BLUE;
        uint32_t row_colours[7];

        uint8_t brightness = 16;

        HexUnit();

        void begin();
        void clear();
        void show();
        void fill(uint32_t colour);

        void decreaseBrightness();
        void increaseBrightness();

        // Colour Utilities
        uint32_t sumChannelColours(uint32_t colour1, uint32_t colour2);
        uint32_t mixFlameColours(uint32_t colour1, uint32_t colour2);
        uint32_t mixPastelColours(uint32_t colour1, uint32_t colour2, enum PastelMode pastelMode);

        // Polar Layout
        void fillPolarRegion(uint32_t colour, int distanceFromCentre, int degrees, int fillRadius, enum MixMode mixMode=NONE);

        // Ring Layout
        void setRingPixelColour(uint32_t colour, int ringIndex, int pixelIndex);
        uint32_t getRingPixelColour(int ringIndex, int pixelIndex);
        void fillRing(uint32_t colour, int ringIndex);
        // void drawRingBand(uint32_t colour, int ringIndex, int pixelIndex, int bandWidth) {};

        // TODO: Figure out if templates could make these functions work for all
        // cartesian variants.

        // Interlaced Layout
        // void setInterlacedPixelColour(uint32_t colour, int column, int row) {};
        // uint32_t getInterlacedPixelColour(int column, int row) {};
        // TODO: Look up c++ optional parameters for these.
        // void fillInterlacedRow(uint32_t colour, int row);
        // void fillInterlacedRow(uint32_t colour, int row, int start_column, int num_cells);

        // Sawtooth Layout
        void setSawtoothPixelColour(uint32_t colour, int column, int row);
        uint32_t getSawtoothPixelColour(int column, int row);
        void fillSawtoothRow(uint32_t colour, int row);
        void fillSawtoothRow(uint32_t colour, int row, int start_column);
        void fillSawtoothRow(uint32_t colour, int row, int start_column, int num_cells);

        // Italic Layout
        void setItalicPixelColour(uint32_t colour, int column, int row);
        uint32_t getItalicPixelColour(int column, int row);
        void fillItalicRow(uint32_t colour, int row);
        void fillItalicRow(uint32_t colour, int row, int start_column);
        void fillItalicRow(uint32_t colour, int row, int start_column, int num_cells);
        // void fillItalicLayoutFromMatrix(uint32_t *matrix);
        // void fillItalicLayoutFromMatrix(uint32_t *matrix, int matrix_start_column, int matrix_start_row);

        void fillCubicFace(uint32_t colour, int face);
        void setCubicPixelColor(uint32_t colour, int face, int row, int column);

        // Reverse Italic Layout
        // void setReverseItalicPixelColour(uint32_t colour, int column, int row) {};
        // uint32_t getReverseItalicPixelColour(int column, int row) {};
        // void fillReverseItalicRow(uint32_t colour, int row);
        // void fillReverseItalicRow(uint32_t colour, int row, int start_column, int num_cells);
};

#endif