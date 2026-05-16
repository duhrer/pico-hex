#include "animation.hpp"

class CubicCycleAnimation : public FrameAnimation {
    private:
        int colour_wheel_offset = 0;

    public:
        bool animateNextFrame(HexUnit hexUnit) {
            // Limit the number of cycles so that we will eventually switch modes.
            if (this -> frameNumber >= 14) {
                this->isFinished = true;
            }
            else {
                hexUnit.clear();

                for (int face = 0; face < 3; face++) {
                    int face_colour_index = (face + colour_wheel_offset) % 7;
                    hexUnit.fillCubicFace(hexUnit.row_colours[face_colour_index], face);
                }

                hexUnit.show();
                this -> colour_wheel_offset = (this->colour_wheel_offset + 1) % 7;
            }

            return this->isFinished;
        } 

        CubicCycleAnimation()
        : FrameAnimation()
        {
            // I'm using this pattern until I learn a better one.
            this->msDelayBetweenFrames = 1000;
        }
};