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

        bool animateNextFrame(HexUnit *hexUnit) {
            if (this -> frameNumber > 24) {
                this->isFinished = true;
            }
            else {
                hexUnit -> clear();

                hexUnit -> fill(hexUnit -> WHITE);

                // Start in the centre
                hexUnit -> fillPolarRegion(hexUnit -> BLUE, radius, angle, iris_fill_radius);

                // Draw the pupil
                hexUnit -> fillPolarRegion(hexUnit -> BLACK, radius, angle, pupil_fill_radius);

                // Draw the "gleam"
                hexUnit -> fillPolarRegion(hexUnit -> WHITE, radius, angle, shine_fill_radius);
                
                hexUnit -> show();

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