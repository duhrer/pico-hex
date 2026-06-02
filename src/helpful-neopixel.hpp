#ifndef HELPFUL_NEOPIXEL_H
#define HELPFUL_NEOPIXEL_H

#include "Adafruit_NeoPixel.hpp"

// Wrapper around the Adafruit neopixel library to make it possible to determine
// the colour channels from a given uint32_t value.

struct ColourChannels {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t w;
};

class HelpfulNeopixel : public Adafruit_NeoPixel {
    public:
        HelpfulNeopixel(uint16_t n, uint16_t pin=0, neoPixelType type=NEO_GRB + NEO_KHZ800)
        :Adafruit_NeoPixel(n, pin, type)
        {
            // No unique value-add at the moment.
        }

        HelpfulNeopixel() = default;

        struct ColourChannels channelsFromColour(uint32_t colour);
        uint32_t colourFromChannels(struct ColourChannels channels);
        
};

#endif
