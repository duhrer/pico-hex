#ifndef ANIMATION_POLAR_EYE_SACCADE
#define ANIMATION_POLAR_EYE_SACCADE

#include "animation-polar-eye.hpp"

class PolarEyeSaccadeAnimation : public PolarEyeAnimation {
    private:
        double max_radius = 3;
        double radius_delta = 0.5;
    public:
        PolarEyeSaccadeAnimation()
        : PolarEyeAnimation()
        {
            // I'm using this pattern until I learn a better one.
            this->msDelayBetweenFrames = 50;

            angle = 0;
            radius = 1.75;
        }

        bool animateNextFrame() {
            if (this -> frameNumber > 24) {
                this->isFinished = true;
            }
            else {
                current_hex_unit -> clear();

                current_hex_unit -> fill(current_hex_unit -> WHITE);

                // Start in the centre
                current_hex_unit -> fillPolarRegion(current_hex_unit -> BLUE, radius, angle, iris_fill_radius);

                // Draw the pupil
                current_hex_unit -> fillPolarRegion(current_hex_unit -> BLACK, radius, angle, pupil_fill_radius);

                // Draw the "gleam"
                current_hex_unit -> fillPolarRegion(current_hex_unit -> WHITE, radius, angle, shine_fill_radius);
                
                current_hex_unit -> show();

                // Move the iris around side to side
                double new_radius = (radius + radius_delta);
                if (new_radius < 0 ) {
                    radius_delta *= -1.0;
                    angle = (angle + 180) % 360;
                }
                else if (new_radius > max_radius) {
                    radius_delta *= -1.0;
                }
                else {
                    radius = new_radius;
                }
            }

            return this->isFinished;
        }
};

#endif
