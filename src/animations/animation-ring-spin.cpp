#include "animation.hpp"

class RingSpinAnimation : public FrameAnimation {
    private:
        int r = MAX_BRIGHTNESS;
        const int delta_r = 16;  // Cycles in 16 passes.

        int g = MAX_BRIGHTNESS / 4;
        const int delta_g = 32;  // Cycles in 8 passes.

        int b = MAX_BRIGHTNESS / 2;
        const int delta_b = -16; // Cycles in 16 passes.

    public:
        bool animateNextFrame(HexUnit *hexUnit) {
            if (this -> frameNumber > 64) {
                this->isFinished = true;
            }
            else {
                hexUnit -> clear();

                int brightness_percentage = (hexUnit -> brightness * 100) / MAX_BRIGHTNESS;

                this -> r = (this->r + MAX_BRIGHTNESS + this->delta_r) % MAX_BRIGHTNESS;
                this -> g = (this->g + MAX_BRIGHTNESS + this->delta_g) % MAX_BRIGHTNESS;
                this -> b = (this->b + MAX_BRIGHTNESS + this->delta_b) % MAX_BRIGHTNESS;

                uint32_t colour = hexUnit -> neopixels.Color((r * brightness_percentage) / 100, (g * brightness_percentage) / 100, (b * brightness_percentage) / 100);

                hexUnit -> setRingPixelColour(colour, 0, 0);

                for (int ring_index = 1; ring_index < 4; ring_index++) {
                    int num_cells = ring_index * 6;
                    int cell_index = this -> frameNumber % num_cells;

                    // Clone this cell twice 120 degrees apart.
                    int second_cell_index = (cell_index + (num_cells / 3)) % num_cells;
                    int third_cell_index = (cell_index + (2 * num_cells / 3)) % num_cells;

                    hexUnit -> setRingPixelColour(colour, ring_index, cell_index);
                    hexUnit -> setRingPixelColour(colour, ring_index, second_cell_index);
                    hexUnit -> setRingPixelColour(colour, ring_index, third_cell_index);
                }

                hexUnit -> show();
            }

            return this->isFinished;
        } 

        RingSpinAnimation()
        : FrameAnimation()
        {
            // I'm using this pattern until I learn a better one.
            this->msDelayBetweenFrames = 100;
        }
};