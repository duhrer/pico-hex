#ifndef ANIMATION_RING_SPIN_H
#define ANIMATION_RING_SPIN_H

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
        bool animateNextFrame() {
            if (this -> frameNumber > 64) {
                isFinished = true;
            }
            else {
                current_hex_unit -> clear();

                int brightness_percentage = ((current_hex_unit -> brightness) * 100) / MAX_BRIGHTNESS;

                r = (r + MAX_BRIGHTNESS + delta_r) % MAX_BRIGHTNESS;
                g = (g + MAX_BRIGHTNESS + delta_g) % MAX_BRIGHTNESS;
                b = (b + MAX_BRIGHTNESS + delta_b) % MAX_BRIGHTNESS;

                uint32_t colour = current_hex_unit -> neopixels.Color((r * brightness_percentage) / 100, (g * brightness_percentage) / 100, (b * brightness_percentage) / 100);

                current_hex_unit -> setRingPixelColour(colour, 0, 0);

                for (int ring_index = 1; ring_index < 4; ring_index++) {
                    int num_cells = ring_index * 6;
                    int cell_index = this -> frameNumber % num_cells;

                    // Clone this cell twice 120 degrees apart.
                    int second_cell_index = (cell_index + (num_cells / 3)) % num_cells;
                    int third_cell_index = (cell_index + (2 * num_cells / 3)) % num_cells;

                    current_hex_unit -> setRingPixelColour(colour, ring_index, cell_index);
                    current_hex_unit -> setRingPixelColour(colour, ring_index, second_cell_index);
                    current_hex_unit -> setRingPixelColour(colour, ring_index, third_cell_index);
                }

                current_hex_unit -> show();
            }

            return isFinished;
        } 

        RingSpinAnimation()
        : FrameAnimation()
        {
            // I'm using this pattern until I learn a better one.
            msDelayBetweenFrames = 100;
        }
};

#endif
