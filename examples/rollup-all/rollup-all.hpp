#ifndef ANIMATION_ROLLUP_ALL_H
#define ANIMATION_ROLLUP_ALL_H

#include "animation.hpp"

#include "../cubic-cycle/cubic-cycle.hpp"

#include "../italic-fill-row/italic-fill-row.hpp"
#include "../italic-sine-rainbow/italic-sine-rainbow.hpp"

#include "../polar-flame/common/polar-flame.hpp"
#include "../polar-mixing/polar-mixing.hpp"

#include "../ring-rainbow/ring-rainbow.hpp"

#include "../ring-spin/ring-spin.hpp"

#include "../rollup-eye/rollup-eye.hpp"

class RollupAllRandomAnimation : public RollupAnimation {
    private:
        RingSpinAnimation ring_spin_animation;
        RingRainbowAnimation ring_rainbow_animation;

        ItalicFillAnimation italic_fill_animation;
        ItalicSineAnimation italic_sine_animation;

        RollupEyeAnimation rollup_eye_animation;

        CubicCycleAnimation cubic_cycle_animation;

        RollupPolarFlameAnimation rollup_polar_flame_animation;

        RollupPolarMixingAnimation rollup_polar_mixing_animation;

    public:
        RollupAllRandomAnimation (int unit_number=0)
        : RollupAnimation(unit_number)
        {
            ring_spin_animation.unit_number = unit_number;
            ring_rainbow_animation.unit_number = unit_number;
            italic_fill_animation.unit_number = unit_number;
            italic_sine_animation.unit_number = unit_number;
            rollup_eye_animation.unit_number = unit_number;
            cubic_cycle_animation.unit_number = unit_number;
            rollup_polar_flame_animation.unit_number = unit_number;
            rollup_polar_mixing_animation.unit_number = unit_number;           

            animations[0] = &ring_spin_animation;
            animations[1] = &ring_rainbow_animation;
            animations[2] = &italic_fill_animation;
            animations[3] = &italic_sine_animation;
            animations[4] = &rollup_eye_animation;
            animations[5] = &cubic_cycle_animation;
            animations[6] = &rollup_polar_flame_animation;
            animations[7] = &rollup_polar_mixing_animation;
        }
};

#endif
