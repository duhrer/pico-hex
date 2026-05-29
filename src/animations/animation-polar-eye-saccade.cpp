#include "animation.hpp"

class PolarEyeSaccadeAnimation : public FrameAnimation {
    private:
        int iris_angle = 0;
        double iris_radius = 1.75;
        double max_iris_radius = 3;
        double iris_radius_delta = 0.5; // cycles to roundtrip
    public:
        PolarEyeSaccadeAnimation()
        : FrameAnimation()
        {
            // I'm using this pattern until I learn a better one.
            this->msDelayBetweenFrames = 50;
        }

        bool animateNextFrame(HexUnit *hexUnit) {
            if (this -> frameNumber > 24) {
                this->isFinished = true;
            }
            else {
                // hexUnit -> clear();

                hexUnit -> fill(hexUnit -> WHITE);

                // Start in the centre
                hexUnit -> fillPolarRegion(hexUnit -> BLUE, iris_radius, iris_angle, 3);

                // Draw the pupil
                hexUnit -> fillPolarRegion(hexUnit -> BLACK, iris_radius, iris_angle, 2);

                // Draw the "gleam"
                hexUnit -> fillPolarRegion(hexUnit -> WHITE, iris_radius, iris_angle, 1);
                
                hexUnit -> show();

                // Move the iris around side to side
                double new_iris_radius = (iris_radius + iris_radius_delta);
                if (new_iris_radius < 0 ) {
                    iris_radius_delta *= -1.0;
                    iris_angle = (iris_angle + 180) % 360;
                }
                else if (new_iris_radius > max_iris_radius) {
                    iris_radius_delta *= -1.0;
                }
                else {
                    iris_radius = new_iris_radius;
                }
            }

            return this->isFinished;
        }
};