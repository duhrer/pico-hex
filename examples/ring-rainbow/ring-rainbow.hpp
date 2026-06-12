#ifndef ANIMATION_RING_RAINBOW_H
#define ANIMATION_RING_RAINBOW_H

#include "animation.hpp"

class RingRainbowAnimation : public FrameAnimation {
    private:
        int colour_wheel_offset = 0;

    public:
        bool animateNextFrame() {
            // Limit the number of cycles so that we will eventually switch modes.
            if (this -> frameNumber >= 49) {
                this->isFinished = true;
            }
            else {
                current_hex_unit -> clear();

                for (int index = 0; index < 4; index++) {
                    int colour_index = (index + colour_wheel_offset) % 7;
                    uint32_t colour = current_hex_unit -> row_colours[colour_index];
                    current_hex_unit -> fillRing(colour, index);
                }

                current_hex_unit -> show();

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

#endif
