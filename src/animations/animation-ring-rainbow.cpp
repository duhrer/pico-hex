#include "animation.hpp"

class RingRainbowAnimation : public FrameAnimation {
    private:
        int colour_wheel_offset = 0;

    public:
        bool animateNextFrame(HexUnit *hexUnit) {
            // Limit the number of cycles so that we will eventually switch modes.
            if (this -> frameNumber >= 49) {
                this->isFinished = true;
            }
            else {
                hexUnit -> clear();

                for (int index = 0; index < 4; index++) {
                    int colour_index = (index + colour_wheel_offset) % 7;
                    uint32_t colour = hexUnit -> row_colours[colour_index];
                    hexUnit -> fillRing(colour, index);
                }

                hexUnit -> show();

                this->colour_wheel_offset = (this->colour_wheel_offset + 1) % 7;
            }

            return this->isFinished;
        } 

        RingRainbowAnimation()
        : FrameAnimation()
        {
            // I'm using this pattern until I learn a better one.
            this->msDelayBetweenFrames = 250;
        }
};