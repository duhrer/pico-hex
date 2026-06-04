#ifndef ANIMATION_POLAR_MIXING_H
#define ANIMATION_POLAR_MIXING_H

#include "animation.hpp"
#include <stdlib.h>
#include <math.h>

#define MAX_FRAME_NUMBER 120
#define MAX_RADIUS 2

class PolarMixingAnimation : public FrameAnimation {
    private:
        MixMode mixMode;

        double fill_radius = 3;

        int radius_wavelength = 36;
        double radius_amplitude = 2;
        double radius_median = 3;
        int starting_angle = 60;
        int angle_delta = 20;
    public:
        PolarMixingAnimation() = default;

        PolarMixingAnimation(MixMode mixMode)
        :FrameAnimation()
        {
            this->mixMode = mixMode;
            msDelayBetweenFrames = 250;
        }

        bool animateNextFrame() {
            if (frameNumber > MAX_FRAME_NUMBER) {
                isFinished = true;
            }
            else {
                current_hex_unit -> clear();

                uint32_t colour1;
                uint32_t colour2;
                uint32_t colour3;

                switch (mixMode) {
                    case FLAME:
                    case PASTEL_ONE:
                        colour1 = current_hex_unit -> neopixels.Color(MAX_BRIGHTNESS, 0, 0);
                        colour2 = colour1;
                        colour3 = colour1;
                    break;

                    case PASTEL_TWO:
                        colour1 = current_hex_unit -> neopixels.Color(0, MAX_BRIGHTNESS, 0);
                        colour2 = colour1;
                        colour3 = colour1;
                    break;

                    case PASTEL_THREE:
                        colour1 = current_hex_unit -> neopixels.Color(0, 0, MAX_BRIGHTNESS);
                        colour2 = colour1;
                        colour3 = colour1;
                    break;

                    default:
                        colour1 = current_hex_unit -> neopixels.Color(MAX_BRIGHTNESS, 0, 0);
                        colour2 = current_hex_unit -> neopixels.Color(0, MAX_BRIGHTNESS, 0);
                        colour3 = current_hex_unit -> neopixels.Color(0, 0, MAX_BRIGHTNESS);
                    break;
                }

                // Make the radius oscillate in and out.
                double radians = ((2.0 * M_PI) / radius_wavelength) * frameNumber;
                double radius = radius_median + (sin(radians) * radius_amplitude);

                current_hex_unit -> fillPolarRegion(colour1, radius, starting_angle, fill_radius, mixMode);
                current_hex_unit -> fillPolarRegion(colour2, radius, (starting_angle + 120) % 360, fill_radius, mixMode);
                current_hex_unit -> fillPolarRegion(colour3, radius, (starting_angle + 240) % 360, fill_radius, mixMode);

                current_hex_unit -> show();

                starting_angle = (starting_angle + angle_delta) % 360;
            }

            return this->isFinished;
        }
};

#endif