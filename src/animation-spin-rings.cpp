#include "animation.hpp"

class RingSpinAnimation : public Animation {
    private:
        int r = 0;
        const int delta_r = 1;  // Cycles in 16 passes.

        int g = 128;
        const int delta_g = 2;  // Cycles in 8 passes.

        int b = 256;
        const int delta_b = -1; // Cycles in 16 passes.

    public:
        void animateNextFrame() {
            // Limit the number of cycles so that we will eventually switch modes.
            if (this -> frameNumber >= 64) {
                this->isFinished = true;
            }
            else {
                this->hexUnit.clear();

                this -> r = (this->r + MAX_BRIGHTNESS + this->delta_r) % MAX_BRIGHTNESS;
                this -> g = (this->g + MAX_BRIGHTNESS + this->delta_g) % MAX_BRIGHTNESS;
                this -> b = (this->b + MAX_BRIGHTNESS + this->delta_b) % MAX_BRIGHTNESS;

                uint32_t colour = this->hexUnit.neopixels.Color(r, g, b);

                hexUnit.setRingPixelColour(colour, 0, 0);

                for (int ring_index = 1; ring_index < 4; ring_index++) {
                    int num_cells = ring_index * 6;
                    int cell_index = this -> frameNumber % num_cells;
                    // Light two pixels on opposite sides of the centre.
                    int anticell_index = (cell_index + (num_cells / 2)) % num_cells;

                    hexUnit.setRingPixelColour(colour, ring_index, cell_index);
                    hexUnit.setRingPixelColour(colour, ring_index, anticell_index);
                }

                this->hexUnit.show();
            }
        } 

        RingSpinAnimation(HexUnit hexUnit)
        : Animation(hexUnit)
        {
            // I'm using this pattern until I learn a better one.
            this->msDelayBetweenFrames = 100;
        }
};