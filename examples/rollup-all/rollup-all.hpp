#ifndef ANIMATION_ROLLUP_ALL_H
#define ANIMATION_ROLLUP_ALL_H

#include "animation.hpp"

#include "../cubic-cycle/cubic-cycle.hpp"

#include "../italic-fill-row/italic-fill-row.hpp"
#include "../italic-sine-rainbow/italic-sine-rainbow.hpp"

#include "../polar-flame/common/polar-flame.hpp"
#include "../polar-mixing/polar-mixing.hpp"

#include "../ring-cycle/ring-cycle.hpp"

#include "../ring-rainbow/ring-rainbow.hpp"

#include "../ring-spin/ring-spin.hpp"

#include "../rollup-eye/rollup-eye.hpp"

class RollupAllAnimation : public RandomisingRollupAnimation {
    private:
        RingCycleAnimation ring_cycle_animation;
        RingSpinAnimation ring_spin_animation;
        RingRainbowAnimation ring_rainbow_animation;

        ItalicFillAnimation italic_fill_animation;
        ItalicSineAnimation italic_sine_animation;

        RollupEyeAnimation rollup_eye_animation;

        CubicCycleAnimation cubic_cycle_animation;

        RollupPolarFlameAnimation rollup_polar_flame_animation;

        RollupPolarMixingAnimation rollup_polar_mixing_animation;

    public:
        RollupAllAnimation ()
        : RandomisingRollupAnimation()
        {
            animations[0] = &ring_cycle_animation;
            animations[1] = &ring_spin_animation;
            animations[2] = &ring_rainbow_animation;
            animations[3] = &italic_fill_animation;
            animations[4] = &italic_sine_animation;
            animations[5] = &rollup_eye_animation;
            animations[6] = &cubic_cycle_animation;
            animations[7] = &rollup_polar_flame_animation;
            animations[8] = &rollup_polar_mixing_animation;
        }
};

#endif
