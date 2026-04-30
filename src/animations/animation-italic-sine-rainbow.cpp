#include "animation.hpp"
#include <math.h>

class ItalicSineAnimation : public Animation {
    private:
        int sine_offset = 0;

        const int wavelength = 49;
        const int amplitude = 7;

    public:
        ItalicSineAnimation()
        : Animation()
        {
            this->msDelayBetweenFrames = 125;
        }

        void animateNextFrame(HexUnit hexUnit) {
            if (this -> frameNumber >= 256) {
                this->isFinished = true;
            }
            else {
                hexUnit.clear();

                // Offset the row colours using an animated sine pattern.
                for (int row = 0; row < 7; row++) {
                    for (int column = 0; column < 7; column++) {
                        double radians = ((2.0 * M_PI) / wavelength) * (column + sine_offset);
                        int offset_row = row + (sin(radians) * amplitude);

                        uint32_t colour = (offset_row >= 0 && offset_row <= 6) ? hexUnit.row_colours[offset_row] : hexUnit.BLACK;
                        hexUnit.setItalicPixelColour(colour, column, row);
                    }
                }

                hexUnit.show();

                sine_offset++;
            }
        }
};
