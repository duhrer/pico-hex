#include "animation.hpp"

class PolarEyeRollAnimation : public FrameAnimation {
    private:
        int iris_angle = 0;
        int iris_angle_delta = 20;

        double iris_radius = 1.75;

    public:
        PolarEyeRollAnimation()
        : FrameAnimation()
        {
            // I'm using this pattern until I learn a better one.
            this->msDelayBetweenFrames = 40;
        }

        bool animateNextFrame(HexUnit hexUnit) {
            if (this -> frameNumber >= 36) {
                this->isFinished = true;
            }
            else {
                // hexUnit.clear();

                hexUnit.fill(hexUnit.WHITE);

                // Start in the centre
                // TODO: Test it off centre
                hexUnit.fillPolarRegion(hexUnit.BLUE, iris_radius, iris_angle, 3);

                // Draw the pupil
                hexUnit.fillPolarRegion(hexUnit.BLACK, iris_radius, iris_angle, 2);

                // Draw the "gleam"

                // Dead centre
                hexUnit.fillPolarRegion(hexUnit.WHITE, iris_radius, iris_angle, 1);
                
                // TODO: Move the iris around side to side
                // TODO: Periodically add a "blink".

                hexUnit.show();

                iris_angle = (iris_angle + iris_angle_delta) % 360;
            }

            return this->isFinished;
        }

};