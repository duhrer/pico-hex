#ifndef ANIMATION_POLAR_EYE_CLOSE_H
#define ANIMATION_POLAR_EYE_CLOSE_H

#include "animation-polar-eye.hpp"

class PolarEyeCloseAnimation : public PolarEyeAnimation {
    public:
        PolarEyeCloseAnimation()
        : PolarEyeAnimation()
        {
            // I'm using this pattern until I learn a better one.
            this->msDelayBetweenFrames = 100;

            angle = 0;
            radius = 1.75;
        }

        bool animateNextFrame() {
            // First two seconds are just black, Eye opens over the course of
            // two seconds, Then stays still for two seconds.
        
            if (this -> frameNumber >= 24) {
                this->isFinished = true;
            }
            // Draw the closed eye, i.e. black.
            else if (frameNumber > 16) {
                    current_hex_unit -> clear();
                    current_hex_unit -> show();
            }
            else {
                // current_hex_unit -> clear();

                // Always draw the eye
                current_hex_unit -> fill(current_hex_unit -> WHITE);
    
                // Draw the iris
                current_hex_unit -> fillPolarRegion(current_hex_unit -> BLUE, radius, angle, iris_fill_radius);

                // Draw the pupil
                current_hex_unit -> fillPolarRegion(current_hex_unit -> BLACK, radius, angle, pupil_fill_radius);

                // Draw the "gleam"
                current_hex_unit -> fillPolarRegion(current_hex_unit -> WHITE, radius, angle, shine_fill_radius);

                // Draw the lids over the eye using the "italic" functions.
                if (frameNumber > 7) {
                    // Frame 8, only draw black in the four "corners" of the
                    // top and bottom rows.
                    if (frameNumber == 8) {
                        current_hex_unit -> fillItalicRow(current_hex_unit -> BLACK, 0, 0, 1);
                        current_hex_unit -> fillItalicRow(current_hex_unit -> BLACK, 0, 5, 1);
                        current_hex_unit -> fillItalicRow(current_hex_unit -> BLACK, 6, 0, 1);
                        current_hex_unit -> fillItalicRow(current_hex_unit -> BLACK, 6, 5, 1);
                    }

                    // Frame 9-16, the top and bottom rows are black
                    if (frameNumber >= 9) {
                        current_hex_unit -> fillItalicRow(current_hex_unit -> BLACK, 0);
                        current_hex_unit -> fillItalicRow(current_hex_unit -> BLACK, 6);
                    }

                    // Frame 10, draw black on the edges of row 1 and 5
                    if (frameNumber == 10) {
                        current_hex_unit -> fillItalicRow(current_hex_unit -> BLACK, 1, 0, 2);
                        current_hex_unit -> fillItalicRow(current_hex_unit -> BLACK, 1, 4, 2);
                        current_hex_unit -> fillItalicRow(current_hex_unit -> BLACK, 5, 0, 2);
                        current_hex_unit -> fillItalicRow(current_hex_unit -> BLACK, 5, 4, 2);
                    }

                    // Frame 11-16, rows 1 and 5 are black
                    if (frameNumber >= 11) {
                        current_hex_unit -> fillItalicRow(current_hex_unit -> BLACK, 1);
                        current_hex_unit -> fillItalicRow(current_hex_unit -> BLACK, 5);
                    }

                    // Frame 12, rows 2 and 4 are partially black
                    if (frameNumber == 12) {
                        current_hex_unit -> fillItalicRow(current_hex_unit -> BLACK, 2, 0, 2);
                        current_hex_unit -> fillItalicRow(current_hex_unit -> BLACK, 2, 4, 2);
                        current_hex_unit -> fillItalicRow(current_hex_unit -> BLACK, 4, 0, 2);
                        current_hex_unit -> fillItalicRow(current_hex_unit -> BLACK, 4, 4, 2);
                    }

                    // Frame 13-16, rows 2 and 4 are black
                    if (frameNumber >= 13) {
                        current_hex_unit -> fillItalicRow(current_hex_unit -> BLACK, 2);
                        current_hex_unit -> fillItalicRow(current_hex_unit -> BLACK, 4);
                    }

                    // Frame 14, draw one black square on the edges of row 3
                    if (frameNumber == 14) {
                        current_hex_unit -> fillItalicRow(current_hex_unit -> BLACK, 3, 0, 1);
                        current_hex_unit -> fillItalicRow(current_hex_unit -> BLACK, 3, 5, 1);
                    }
                    // Frame 8, draw a two square band on the edges of row 3
                    if (frameNumber >= 15) {
                        current_hex_unit -> fillItalicRow(current_hex_unit -> BLACK, 3, 0, 2);
                        current_hex_unit -> fillItalicRow(current_hex_unit -> BLACK, 3, 4, 2);
                    }                   
                }

                current_hex_unit -> show();
            }

            return this->isFinished;
        }
};

#endif