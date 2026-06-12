#ifndef ANIMATION_POLAR_EYE_H
#define ANIMATION_POLAR_EYE_H

#include "animation.hpp"

class PolarEyeAnimation : public FrameAnimation {
    protected:
        double iris_fill_radius  = 2;
        double pupil_fill_radius = 1.5;
        double shine_fill_radius = 0.5;

        int angle = 0;
        double radius = 0;

    public:
        PolarEyeAnimation()
        : FrameAnimation()
        {
            // I'm using this pattern until I learn a better one.
            this->msDelayBetweenFrames = 100;
        }
};

#endif