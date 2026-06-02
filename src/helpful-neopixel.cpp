#include "helpful-neopixel.hpp"

/*

    Because we're extending the class, we can have acces to the protected
    offsets we need to figure out the channel data from a packed uint32_t value.

    uint8_t           rOffset;    ///< Red index within each 3- or 4-byte pixel
    uint8_t           gOffset;    ///< Index of green byte
    uint8_t           bOffset;    ///< Index of blue byte
    uint8_t           wOffset;    ///< Index of white (==rOffset if no white)

*/

struct ColourChannels HelpfulNeopixel::channelsFromColour(uint32_t colour) {
    // I have no idea what the offsets are supposed to mean, I don't think they
    // relate directly to the colours.
    // uint8_t w = (colour >> (wOffset * 8)) & 255;
    // uint8_t r = (colour >> (rOffset * 8)) & 255;
    // uint8_t g = (colour >> (gOffset * 8)) & 255;
    // uint8_t b = (colour >> (bOffset * 8)) & 255;

    uint8_t w = (colour >> 24) & 255;
    uint8_t r = (colour >> 16) & 255;
    uint8_t g = (colour >> 8) & 255;
    uint8_t b = colour & 255;


    struct ColourChannels colourChannels = { r, g, b, w };
    return colourChannels;
}

uint32_t HelpfulNeopixel::colourFromChannels(struct ColourChannels channels) {
    return Color(channels.r, channels.g, channels.b);
}