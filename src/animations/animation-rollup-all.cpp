#include "animation.hpp"

#include "animation-ring-cycle.cpp"
#include "animation-ring-spin.cpp"

// #include "animation-italic-scrolling.cpp"

#include "animation-italic-fill-row.cpp"
#include "animation-italic-sine-rainbow.cpp"

// #include "animation-sawtooth-scrolling.cpp"

#include "animation-rollup-eye.cpp"

class RollupAllAnimation : public Animation {
    private:
        // TODO: Make a rollup for these
        RingCycleAnimation ring_cycle_animation;
        RingSpinAnimation ring_spin_animation;

        // TODO: Make a rollup for these
        ItalicFillAnimation italic_fill_animation;
        ItalicSineAnimation italic_sine_animation;

        // TODO: Make a rollup and add other stages
        RollupEyeAnimation rollup_eye_animation;

    public:
        // Override default run method
        void run (HexUnit hexUnit) {
            ring_cycle_animation.run(hexUnit);
            ring_spin_animation.run(hexUnit);

            italic_fill_animation.run(hexUnit);
            italic_sine_animation.run(hexUnit);

            rollup_eye_animation.run(hexUnit);

            this->isFinished = true;
        }        

        // Empty required frame animation method
        void animateNextFrame(HexUnit hexUnit) {
        }

};
