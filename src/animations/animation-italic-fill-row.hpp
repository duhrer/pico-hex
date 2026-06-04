#ifndef ANIMATION_ITALIC_FILL_H
#define ANIMATION_ITALIC_FILL_H

#include "animation.hpp"
#include "letters.h"

class ItalicFillAnimation : public FrameAnimation {
    private:
        int dividing_column = 3;
        int column_delta = -1;

    // uint8_t *generate_matrix_for_string(char input_string[])
    public:
        // ItalicFillAnimation(HexUnit hexUnit)
        // : Animation(hexUnit)
        ItalicFillAnimation()
        : FrameAnimation()
        {
            this->msDelayBetweenFrames = 100;
        }

        // Scroll text from left to right.
        bool animateNextFrame() {
            if (this -> frameNumber >= 112) {
                this->isFinished = true;
            }
            else {
                current_hex_unit -> clear();

                for (int row = 0; row < 7; row++) {
                    uint32_t main_colour = current_hex_unit -> row_colours[row];
                    uint32_t alternate_colour = current_hex_unit -> row_colours[6-row];

                    if (dividing_column > 0) {
                        // Fill the whole row with the primary colour.
                        current_hex_unit -> fillItalicRow(main_colour, row);
                    }

                    // Overwrite half the row with a secondary colour.
                    current_hex_unit -> fillItalicRow(alternate_colour, row, dividing_column);

                    // Draw a clear dividing line between the two areas
                    if (dividing_column > 0 && dividing_column < 6) {
                        current_hex_unit -> setItalicPixelColour(current_hex_unit -> BLACK, dividing_column, row);
                    }
                }

                current_hex_unit -> show();

                if (dividing_column == 0 || dividing_column == 6) {
                    column_delta *= -1;
                }
                dividing_column += column_delta;
            }

            return this->isFinished;
        }
};

#endif
