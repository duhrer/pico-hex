#ifndef ANIMATION_ROLLUP_ALL_H
#define ANIMATION_ROLLUP_ALL_H

#include "animation.hpp"

#include "animation-ring-cycle.hpp"
#include "animation-ring-spin.hpp"
#include "animation-ring-rainbow.hpp"

// #include "animation-italic-scrolling.hpp"

#include "animation-italic-fill-row.hpp"
#include "animation-italic-sine-rainbow.hpp"

// #include "animation-sawtooth-scrolling.hpp"

#include "animation-rollup-eye.hpp"

#include "animation-cubic-cycle.hpp"

#include "animation-polar-flame.hpp"

#include "animation-rollup-mixing.hpp"

class RollupAllAnimation : public RandomisingRollupAnimation {
    private:
        // TODO: Make a rollup for these
        RingCycleAnimation ring_cycle_animation;
        RingSpinAnimation ring_spin_animation;
        RingRainbowAnimation ring_rainbow_animation;

        // TODO: Make a rollup for these
        ItalicFillAnimation italic_fill_animation;
        ItalicSineAnimation italic_sine_animation;

        RollupEyeAnimation rollup_eye_animation;

        CubicCycleAnimation cubic_cycle_animation;

        PolarFlameAnimation polar_flame_animation;

        RollupMixingAnimation rollup_polar_mixing_animation;

    public:
        RollupAllAnimation ()
        : RandomisingRollupAnimation()
        {
            // TODO: make sure this is switching and repeating as expected.

            animations[0] = &ring_cycle_animation;
            animations[1] = &ring_spin_animation;
            animations[2] = &ring_rainbow_animation;
            animations[3] = &italic_fill_animation;
            animations[4] = &italic_sine_animation;
            animations[5] = &rollup_eye_animation;
            animations[6] = &cubic_cycle_animation;
            animations[7] = &polar_flame_animation;
            animations[8] = &rollup_polar_mixing_animation;
            
            // https://stackoverflow.com/questions/43564387/list-for-abstact-objects
            // animations.push_back(&ring_cycle_animation);
            // animations.push_back(&ring_spin_animation);
            // animations.push_back(&italic_fill_animation);
            // animations.push_back(&italic_sine_animation);
            // animations.push_back(&rollup_eye_animation);
        }
};

#endif
