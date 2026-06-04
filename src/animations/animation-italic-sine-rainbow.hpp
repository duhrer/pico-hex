#ifndef ANIMATION_ITALIC_SINE_RAINBOW_H
#define ANIMATION_ITALIC_SINE_RAINBOW_H

#include "animation.hpp"
#include <math.h>

class ItalicSineAnimation : public FrameAnimation {
    private:
        int sine_offset = 0;

        const int wavelength = 49;
        const int amplitude = 7;

    public:
        ItalicSineAnimation()
        : FrameAnimation()
        {
            this->msDelayBetweenFrames = 125;
        }

        bool animateNextFrame() {
            if (this -> frameNumber >= 256) {
                this->isFinished = true;
            }
            else {
                current_hex_unit -> clear();

                // Offset the row colours using an animated sine pattern.
                for (int row = 0; row < 7; row++) {
                    for (int column = 0; column < 7; column++) {
                        double radians = ((2.0 * M_PI) / wavelength) * (column + sine_offset);
                        int offset_row = row + (sin(radians) * amplitude);

                        uint32_t colour = (offset_row >= 0 && offset_row <= 6) ? current_hex_unit -> row_colours[offset_row] : current_hex_unit -> BLACK;
                        current_hex_unit -> setItalicPixelColour(colour, column, row);
                    }
                }

                current_hex_unit -> show();

                sine_offset++;
            }

            return this->isFinished;
        }        
};

#endif
