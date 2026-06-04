#ifndef ANIMATION_ROLLUP_EYE_H
#define ANIMATION_ROLLUP_EYE_H

#include "animation.hpp"

#include "animation-polar-eye-open.hpp"
#include "animation-polar-eye-saccade.hpp"
#include "animation-polar-eye-roll.hpp"
#include "animation-polar-eye-close.hpp"

class RollupEyeAnimation : public RollupAnimation {
    private:
        PolarEyeOpenAnimation polar_eye_open_animation;
        PolarEyeSaccadeAnimation polar_eye_saccade_animation;
        PolarEyeRollAnimation polar_eye_roll_animation;
        PolarEyeCloseAnimation polar_eye_close_animation;

    public:
        RollupEyeAnimation()
        :RollupAnimation()
        {
            animations[0] =&polar_eye_open_animation;
            animations[1] = &polar_eye_saccade_animation;
            animations[2] = &polar_eye_roll_animation;
            animations[3] = &polar_eye_close_animation;

            // animations.push_back(&polar_eye_open_animation);
            // animations.push_back(&polar_eye_saccade_animation);
            // animations.push_back(&polar_eye_roll_animation);
            // animations.push_back(&polar_eye_close_animation);
        }

};

#endif
