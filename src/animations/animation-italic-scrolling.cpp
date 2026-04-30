#include "animation.hpp"

#include "letters.h"

class ItalicScrollingTextAnimation : public FrameAnimation {
    private:
        uint8_t *matrix;
        int matrix_columns;

        // Relative location of first column of output, which starts out of
        // bounds on the right and moves left.
        int output_column_offset = 0;

    // uint8_t *generate_matrix_for_string(char input_string[])
    public:
        ItalicScrollingTextAnimation(char *string)
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
        bool animateNextFrame(HexUnit hexUnit) {
            // TODO: Display a single letter
            hexUnit.clear();

            for (int row = 0; row < 7; row++) {
                // hexUnit.fillItalicRow(row_colours[row], row);
                for (int column = 0; column < 7; column++) {
                    int offset_column = (column + output_column_offset) % 7;
                    if (offset_column < 6 && (LETTER_Q[row][offset_column] != 0)) {
                        // hexUnit.setItalicPixelColour(BLACK, column, row);
                        // hexUnit.setItalicPixelColour(WHITE, column, row);
                        hexUnit.setItalicPixelColour(hexUnit.row_colours[row], column, row);
                    }
                }
            }

            hexUnit.show();

            // TODO: Display a series of single letters that don't move.

            // TODO: Scroll a single letter with simple wrapping.

            // TODO: Scroll multiple letters.

            // TODO: Test the composition functions.
            // if (output_column_offset < 7) {
            //     hexUnit.clear();

            //     // If output_column_offset is 6, we should be drawing column 0
            //     // of the matrix in row 6, and nothing in the other columns.
            //     //
            //     // If output_column_offset is -6, we should be drawing columns
            //     // 0-6.  If output_column_offset is -10, we should be drawing
            //     // columns 4-10.
            //     for (int row = 0; row < 7; row++) {
            //         for (int column = 0; column < 7; column++) {
            //             int matrix_column = column  - output_column_offset;
            //             if (matrix_column > 0 && matrix_column < matrix_columns) {
            //                 // Couldn't get multidimensional array notation
            //                 // working, so I used the pointer offset.
            //                 // https://www.geeksforgeeks.org/cpp/multidimensional-pointer-arithmetic-in-cc/
            //                 // element_data = *( (int *)buffer + offset );
            //                 uint8_t saturation = *((uint8_t *) matrix + ((row * matrix_columns) + column));

            //                 if (saturation > 0) {
            //                     hexUnit.setItalicPixelColour(row_colours[row], column, row);
            //                 }
            //             }
            //         }
            //     }

            //     hexUnit.show();
            // }

            output_column_offset = (7 + (output_column_offset + 1)) % 7;

            // TODO: Finish when we're done scrolling.

            return this->isFinished;
        }
};

