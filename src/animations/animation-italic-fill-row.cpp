#include "animation.hpp"

#include "letters.h"

class ItalicFillAnimation : public Animation {
    private:
        int dividing_column = 3;
        int column_delta = -1;

    // uint8_t *generate_matrix_for_string(char input_string[])
    public:
        // ItalicFillAnimation(HexUnit hexUnit)
        // : Animation(hexUnit)
        ItalicFillAnimation()
        : Animation()
        {
            this->msDelayBetweenFrames = 100;
        }

        // Scroll text from left to right.
        void animateNextFrame(HexUnit hexUnit) {
            if (this -> frameNumber >= 112) {
                this->isFinished = true;
            }
            else {
                hexUnit.clear();

                for (int row = 0; row < 7; row++) {
                    uint32_t main_colour = hexUnit.row_colours[row];
                    uint32_t alternate_colour = hexUnit.row_colours[6-row];

                    if (dividing_column > 0) {
                        // Fill the whole row with the primary colour.
                        hexUnit.fillItalicRow(main_colour, row);
                    }

                    // Overwrite half the row with a secondary colour.
                    hexUnit.fillItalicRow(alternate_colour, row, dividing_column);

                    // Draw a clear dividing line between the two areas
                    if (dividing_column > 0 && dividing_column < 6) {
                        hexUnit.setItalicPixelColour(hexUnit.BLACK, dividing_column, row);
                    }
                }

                hexUnit.show();

                if (dividing_column == 0 || dividing_column == 6) {
                    column_delta *= -1;
                }
                dividing_column += column_delta;
            }
        }
};

