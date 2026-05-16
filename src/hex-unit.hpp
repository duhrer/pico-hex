#ifndef HEX_UNIT_H
#define HEX_UNIT_H

#include "Adafruit_NeoPixel.hpp"

// We support brightness levels as powers of two (minus one). Keep the
// brightness low to avoid shortening the life of the lights.
#define MIN_BRIGHTNESS 3
#define MAX_BRIGHTNESS 63

class HexUnit {
    private: 
        // Generic functions used with different layout maps
        uint32_t getRemappedPixelColour(int row, int column, const int *index_map, int index_map_columns);
        void setRemappedPixelColour(uint32_t colour, int row, int column, const int *index_map, int index_map_columns);

        void updateColours();

        public:
        // Underlying Neopixel object.
        Adafruit_NeoPixel neopixels;

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

        // Polar Layout
        void fillPolarRegion(uint32_t colour, int distanceFromCentre, int degrees, int fillRadius);

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