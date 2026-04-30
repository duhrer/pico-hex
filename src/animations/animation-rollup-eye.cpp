#include "animation.hpp"

#include "animation-polar-eye-open.cpp"
#include "animation-polar-eye-saccade.cpp"
#include "animation-polar-eye-roll.cpp"
#include "animation-polar-eye-close.cpp"

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
