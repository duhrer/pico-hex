#ifndef HEX_UNIT_H
#define HEX_UNIT_H

#include "Adafruit_NeoPixel.hpp"

#define MAX_BRIGHTNESS 16

class HexUnit {
    public:
        // Underlying Neopixel object.
        Adafruit_NeoPixel neopixels;

        HexUnit();

        void clear();
        void show();
        void fill(uint32_t colour);

        // Polar Layout
        // void fillPolarRegion(uint32_t colour, int distanceFromCentre, int degrees, int fillRadius) {};

        // Ring Layout
        void setRingPixelColour(uint32_t colour, int ringIndex, int pixelIndex);
        uint32_t getRingPixelColour(int ringIndex, int pixelIndex);
        void fillRing(uint32_t colour, int ringIndex);
        // void drawRingBand(uint32_t colour, int ringIndex, int pixelIndex, int bandWidth) {};

        // Interlaced Layout
        // void setInterlacedPixelColour(uint32_t colour, int column, int row) {};
        // uint32_t colour getInterlacedPixelColour(int column, int row) {};

        // Sawtooth Layout
        // void setSawtoothPixelColour(uint32_t colour, int column, int row) {};
        // uint32_t colour getSawtoothPixelColour(int column, int row) {};

        // Italic Layout
        // void setItalicPixelColour(uint32_t colour, int column, int row) {};
        // uint32_t colour getItalicPixelColour(int column, int row) {};

        // Reverse Italic Layout
        // void setReverseItalicPixelColour(uint32_t colour, int column, int row) {};
        // uint32_t colour getReverseItalicPixelColour(int column, int row) {};
};

#endif