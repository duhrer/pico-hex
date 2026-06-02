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

        bool animateNextFrame(HexUnit *hexUnit) {
            if (this -> frameNumber >= 36) {
                this->isFinished = true;
            }
            else {
                // hexUnit -> clear();

                hexUnit -> fill(hexUnit -> WHITE);

                // Start in the centre
                // TODO: Test it off centre
                hexUnit -> fillPolarRegion(hexUnit -> BLUE, radius, angle, iris_fill_radius);

                // Draw the pupil
                hexUnit -> fillPolarRegion(hexUnit -> BLACK, radius, angle, pupil_fill_radius);

                // Draw the "gleam"

                // Dead centre
                hexUnit -> fillPolarRegion(hexUnit -> WHITE, radius, angle, shine_fill_radius);
                
                // TODO: Move the iris around side to side
                // TODO: Periodically add a "blink".

                hexUnit -> show();

                angle = (angle + angle_delta) % 360;
            }

            return this->isFinished;
        }

};