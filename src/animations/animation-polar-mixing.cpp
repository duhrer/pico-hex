#include "animation.hpp"
#include <stdlib.h>

#define MAX_FRAME_NUMBER 120
#define MAX_RADIUS 2

class PolarMixingAnimation : public FrameAnimation {
    private:
        MixMode mixMode;
        int fill_radius = 3;
        double radius = MAX_RADIUS;
        double radius_delta = -0.25;
        int starting_angle = 60;
        int angle_delta = 20;
    public:
        PolarMixingAnimation() = default;

        PolarMixingAnimation(MixMode mixMode)
        :FrameAnimation()
        {
            this->mixMode = mixMode;
            this->msDelayBetweenFrames = 125;
        }

        bool animateNextFrame(HexUnit *hexUnit) {
            if (frameNumber > MAX_FRAME_NUMBER) {
                this->isFinished = true;
            }
            else {
                hexUnit -> clear();

                uint32_t colour1;
                uint32_t colour2;
                uint32_t colour3;

                switch (mixMode) {
                    case FLAME:
                    case PASTEL_ONE:
                        colour1 = hexUnit -> neopixels.Color(MAX_BRIGHTNESS, 0, 0);
                        colour2 = colour1;
                        colour3 = colour1;
                    break;

                    case PASTEL_TWO:
                        colour1 = hexUnit -> neopixels.Color(0, MAX_BRIGHTNESS, 0);
                        colour2 = colour1;
                        colour3 = colour1;
                    break;

                    case PASTEL_THREE:
                        colour1 = hexUnit -> neopixels.Color(0, 0, MAX_BRIGHTNESS);
                        colour2 = colour1;
                        colour3 = colour1;
                    break;

                    default:
                        colour1 = hexUnit -> neopixels.Color(MAX_BRIGHTNESS, 0, 0);
                        colour2 = hexUnit -> neopixels.Color(0, MAX_BRIGHTNESS, 0);
                        colour3 = hexUnit -> neopixels.Color(0, 0, MAX_BRIGHTNESS);
                    break;
                }

                hexUnit -> fillPolarRegion(colour1, radius, starting_angle, fill_radius, mixMode);
                hexUnit -> fillPolarRegion(colour1, radius, (starting_angle + 120) % 360, fill_radius, mixMode);
                hexUnit -> fillPolarRegion(colour1, radius, (starting_angle + 240) % 360, fill_radius, mixMode);

                hexUnit -> show();

                if (radius <= 0 && radius >= MAX_RADIUS) {
                    radius_delta *= -1;
                }

                radius += radius_delta;

                starting_angle = (starting_angle + angle_delta) % 360;
            }

            return this->isFinished;
        }
};
