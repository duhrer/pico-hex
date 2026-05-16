#include "animation.hpp"

#include "animation-ring-cycle.cpp"
#include "animation-ring-spin.cpp"
#include "animation-ring-rainbow.cpp"

// #include "animation-italic-scrolling.cpp"

#include "animation-italic-fill-row.cpp"
#include "animation-italic-sine-rainbow.cpp"

// #include "animation-sawtooth-scrolling.cpp"

#include "animation-rollup-eye.cpp"

#include "animation-cubic-cycle.cpp"

class RollupAllAnimation : public RollupAnimation {
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

    public:
        RollupAllAnimation ()
        : RollupAnimation()
        {
            animations[0] = &ring_cycle_animation;
            animations[1] = &ring_spin_animation;
            animations[2] = &ring_rainbow_animation;
            animations[3] = &italic_fill_animation;
            animations[4] = &italic_sine_animation;
            animations[5] = &rollup_eye_animation;
            animations[6] = &cubic_cycle_animation;
 
            // https://stackoverflow.com/questions/43564387/list-for-abstact-objects
            // animations.push_back(&ring_cycle_animation);
            // animations.push_back(&ring_spin_animation);
            // animations.push_back(&italic_fill_animation);
            // animations.push_back(&italic_sine_animation);
            // animations.push_back(&rollup_eye_animation);
        }
};
