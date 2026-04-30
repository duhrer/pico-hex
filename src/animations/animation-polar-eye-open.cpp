#include "animation.hpp"

class PolarEyeOpenAnimation : public FrameAnimation {
    private:
        int iris_angle = 0;

        double iris_radius = 1.75;

    public:
        PolarEyeOpenAnimation()
        : FrameAnimation()
        {
            // I'm using this pattern until I learn a better one.
            this->msDelayBetweenFrames = 100;
        }

        bool animateNextFrame(HexUnit hexUnit) {
            // First two seconds are just black, Eye opens over the course of
            // two seconds, Then stays still for two seconds.
        
            if (this -> frameNumber >= 24) {
                this->isFinished = true;
            }
            // Draw the closed eye, i.e. black.
            else if (frameNumber < 8) {
                    hexUnit.clear();
                    hexUnit.show();
            }
            else {
                // hexUnit.clear();

                // Always draw the eye
                hexUnit.fill(hexUnit.WHITE);
    
                // Draw the iris
                hexUnit.fillPolarRegion(hexUnit.BLUE, iris_radius, iris_angle, 3);

                // Draw the pupil
                hexUnit.fillPolarRegion(hexUnit.BLACK, iris_radius, iris_angle, 2);

                // Draw the "gleam"
                hexUnit.fillPolarRegion(hexUnit.WHITE, iris_radius, iris_angle, 1);

                // Draw the lids over the eye using the "italic" functions.
                if (frameNumber < 16) {
                    // Frame 15, only draw black in the four "corners" of the
                    // top and bottom rows.
                    if (frameNumber == 15) {
                        hexUnit.fillItalicRow(hexUnit.BLACK, 0, 0, 1);
                        hexUnit.fillItalicRow(hexUnit.BLACK, 0, 5, 1);
                        hexUnit.fillItalicRow(hexUnit.BLACK, 6, 0, 1);
                        hexUnit.fillItalicRow(hexUnit.BLACK, 6, 5, 1);
                    }

                    // Frame 8-14, the top and bottom rows are black
                    if (frameNumber < 15) {
                        hexUnit.fillItalicRow(hexUnit.BLACK, 0);
                        hexUnit.fillItalicRow(hexUnit.BLACK, 6);
                    }

                    // Frame 13, draw black on the edges of row 1 and 5
                    if (frameNumber == 13) {
                        hexUnit.fillItalicRow(hexUnit.BLACK, 1, 0, 2);
                        hexUnit.fillItalicRow(hexUnit.BLACK, 1, 4, 2);
                        hexUnit.fillItalicRow(hexUnit.BLACK, 5, 0, 2);
                        hexUnit.fillItalicRow(hexUnit.BLACK, 5, 4, 2);
                    }

                    // Frame 8-12, rows 1 and 5 are black
                    if (frameNumber < 13) {
                        hexUnit.fillItalicRow(hexUnit.BLACK, 1);
                        hexUnit.fillItalicRow(hexUnit.BLACK, 5);
                    }

                    // Frame 11, rows 2 and 4 are partially black
                    if (frameNumber == 11) {
                        hexUnit.fillItalicRow(hexUnit.BLACK, 2, 0, 2);
                        hexUnit.fillItalicRow(hexUnit.BLACK, 2, 4, 2);
                        hexUnit.fillItalicRow(hexUnit.BLACK, 4, 0, 2);
                        hexUnit.fillItalicRow(hexUnit.BLACK, 4, 4, 2);
                    }

                    // Frame 8-10, rows 2 and 4 are black
                    if (frameNumber < 11) {
                        hexUnit.fillItalicRow(hexUnit.BLACK, 2);
                        hexUnit.fillItalicRow(hexUnit.BLACK, 4);
                    }

                    // Frame 9, draw one black square on the edges of row 3
                    if (frameNumber == 9) {
                        hexUnit.fillItalicRow(hexUnit.BLACK, 3, 0, 1);
                        hexUnit.fillItalicRow(hexUnit.BLACK, 3, 5, 1);
                    }
                    // Frame 8, draw a two square band on the edges of row 3
                    if (frameNumber == 8) {
                        hexUnit.fillItalicRow(hexUnit.BLACK, 3, 0, 2);
                        hexUnit.fillItalicRow(hexUnit.BLACK, 3, 4, 2);
                    }                   
                }

                hexUnit.show();
            }

            return this->isFinished;
        }
};