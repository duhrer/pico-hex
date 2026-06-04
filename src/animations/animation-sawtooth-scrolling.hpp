#ifndef ANIMATION_SAWTOOTH_SCROLLING_H
#define ANIMATION_SAWTOOTH_SCROLLING_H

#include "animation.hpp"

#include "letters.h"

class SawtoothScrollingTextAnimation : public FrameAnimation {
    private:
        uint8_t *matrix;
        int matrix_columns;

        // Relative location of first column of output, which starts out of
        // bounds on the right and moves left.
        int output_column_offset = 0;

    // uint8_t *generate_matrix_for_string(char input_string[])
    public:
        SawtoothScrollingTextAnimation(char *string)
        : FrameAnimation()
        {
            // I'm using this pattern until I learn a better one.
            this->msDelayBetweenFrames = 250;

            // TODO: One of the next two calls wedges the class.
            // matrix = generate_matrix_for_string(string);

            // TODO: We may need a struct so we don't have to calculate this
            // matrix_columns = sizeof(matrix) / (sizeof(uint8_t) * 7);
        }

        // Scroll text from left to right.
        bool animateNextFrame() {
            // Display a single letter
            current_hex_unit -> clear();

            for (int row = 0; row < 7; row++) {
                current_hex_unit -> fillSawtoothRow(current_hex_unit -> row_colours[row], row);
 
                for (int column = 0; column < 7; column++) {
                    int offset_column = (column + output_column_offset) % 7;
                    if (offset_column < 6 && (LETTER_S[row][offset_column] != 0)) {
                        current_hex_unit -> setSawtoothPixelColour(current_hex_unit -> BLACK, column, row);
                    }
                }
            }

            current_hex_unit -> show();

            output_column_offset = (7 + (output_column_offset + 1)) % 7;

            // TODO: Finish when we're done scrolling.

            return this->isFinished;
        }
};

#endif
