#include "animation.hpp"

#include "animation-polar-eye-open.cpp"
#include "animation-polar-eye-saccade.cpp"
#include "animation-polar-eye-roll.cpp"
#include "animation-polar-eye-close.cpp"

class RollupEyeAnimation : public Animation {
    private:
        PolarEyeOpenAnimation polar_eye_open_animation;
        PolarEyeSaccadeAnimation polar_eye_saccade_animation;
        PolarEyeRollAnimation polar_eye_roll_animation;
        PolarEyeCloseAnimation polar_eye_close_animation;

    public:
        // Override default run method
        void run (HexUnit hexUnit) {

            polar_eye_open_animation.run(hexUnit);
            polar_eye_saccade_animation.run(hexUnit);
            polar_eye_roll_animation.run(hexUnit);
            polar_eye_close_animation.run(hexUnit);

            this->isFinished = true;
        }        

        // Empty required frame animation method
        void animateNextFrame(HexUnit hexUnit) {
        }
};
