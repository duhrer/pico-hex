#ifndef ANIMATION_RING_CYCLE_H
#define ANIMATION_RING_CYCLE_H

#include "animation.hpp"

class RingCycleAnimation : public FrameAnimation {
    private:
        int ring_index = 4;

        int r = 0;
        const int delta_r = 16;  // Cycles in 16 passes.

        int g = 128;
        const int delta_g = 32;  // Cycles in 8 passes.

        int b = 256;
        const int delta_b = -16; // Cycles in 16 passes.

    public:
        bool animateNextFrame() {
            // Limit the number of cycles so that we will eventually switch modes.
            if (this -> frameNumber >= 32) {
                this->isFinished = true;
            }
            else {
                current_hex_unit -> clear();

                int brightness_percentage = (current_hex_unit -> brightness * 100) / MAX_BRIGHTNESS;

                this -> r = (this->r + MAX_BRIGHTNESS + this->delta_r) % MAX_BRIGHTNESS;
                this -> g = (this->g + MAX_BRIGHTNESS + this->delta_g) % MAX_BRIGHTNESS;
                this -> b = (this->b + MAX_BRIGHTNESS + this->delta_b) % MAX_BRIGHTNESS;

                uint32_t colour = current_hex_unit -> neopixels.Color((r * brightness_percentage) / 100, (g * brightness_percentage) / 100, (b * brightness_percentage) / 100);

                current_hex_unit -> fillRing(colour, this->ring_index);

                current_hex_unit -> show();
                this -> ring_index = (4 + (this->ring_index) - 1) % 4;
            }

            return this->isFinished;
        } 

        RingCycleAnimation()
        : FrameAnimation()
        {
            // I'm using this pattern until I learn a better one.
            this->msDelayBetweenFrames = 80;
        }
};

#endif
