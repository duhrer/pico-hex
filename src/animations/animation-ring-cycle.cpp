#include "animation.hpp"

class RingCycleAnimation : public Animation {
    private:
        int ring_index = 4;

        int r = 0;
        const int delta_r = 1;  // Cycles in 16 passes.

        int g = 128;
        const int delta_g = 2;  // Cycles in 8 passes.

        int b = 256;
        const int delta_b = -1; // Cycles in 16 passes.

    public:
        void animateNextFrame(HexUnit hexUnit) {
            // Limit the number of cycles so that we will eventually switch modes.
            if (this -> frameNumber >= 32) {
                this->isFinished = true;
            }
            else {
                hexUnit.clear();

                this -> r = (this->r + MAX_BRIGHTNESS + this->delta_r) % MAX_BRIGHTNESS;
                this -> g = (this->g + MAX_BRIGHTNESS + this->delta_g) % MAX_BRIGHTNESS;
                this -> b = (this->b + MAX_BRIGHTNESS + this->delta_b) % MAX_BRIGHTNESS;

                uint32_t colour = hexUnit.neopixels.Color(r, g, b);

                hexUnit.fillRing(colour, this->ring_index);

                hexUnit.show();
                this -> ring_index = (4 + (this->ring_index) - 1) % 4;
            }
        } 

        RingCycleAnimation()
        : Animation()
        {
            // I'm using this pattern until I learn a better one.
            this->msDelayBetweenFrames = 80;
        }
};