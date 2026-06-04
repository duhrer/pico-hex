#ifndef ANIMATION_POLAR_EYE_ROLL_H
#define ANIMATION_POLAR_EYE_ROLL_H

#include "animation-polar-eye.hpp"

class PolarEyeRollAnimation : public PolarEyeAnimation {
    private:
        int angle_delta = 20;

    public:
        PolarEyeRollAnimation()
        : PolarEyeAnimation()
        {
            // I'm using this pattern until I learn a better one.
            this->msDelayBetweenFrames = 40;

            angle = 0;
            radius = 1.75;
        }

        bool animateNextFrame() {
            if (this -> frameNumber >= 36) {
                this->isFinished = true;
            }
            else {
                // current_hex_unit -> clear();

                current_hex_unit -> fill(current_hex_unit -> WHITE);

                // Start in the centre
                // TODO: Test it off centre
                current_hex_unit -> fillPolarRegion(current_hex_unit -> BLUE, radius, angle, iris_fill_radius);

                // Draw the pupil
                current_hex_unit -> fillPolarRegion(current_hex_unit -> BLACK, radius, angle, pupil_fill_radius);

                // Draw the "gleam"

                // Dead centre
                current_hex_unit -> fillPolarRegion(current_hex_unit -> WHITE, radius, angle, shine_fill_radius);
                
                // TODO: Move the iris around side to side
                // TODO: Periodically add a "blink".

                current_hex_unit -> show();

                angle = (angle + angle_delta) % 360;
            }

            return this->isFinished;
        }

};

#endif
