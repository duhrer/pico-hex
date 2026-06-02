#include "animation.hpp"

#include "animation-polar-mixing.cpp"

class RollupMixingAnimation : public RollupAnimation {
    private:
            PolarMixingAnimation none    = PolarMixingAnimation(MixMode::NONE);
            PolarMixingAnimation sum     = PolarMixingAnimation(MixMode::CHANNEL_SUM);
            PolarMixingAnimation flame   = PolarMixingAnimation(MixMode::FLAME);
            PolarMixingAnimation pastel1 = PolarMixingAnimation(MixMode::PASTEL_ONE);
            PolarMixingAnimation pastel2 = PolarMixingAnimation(MixMode::PASTEL_TWO);
            PolarMixingAnimation pastel3 = PolarMixingAnimation(MixMode::PASTEL_THREE);

    public:
        RollupMixingAnimation()
        : RollupAnimation()
        {
            animations[0] = &sum;
            animations[1] = &flame;
            animations[2] = &pastel1;
            animations[3] = &pastel2;
            animations[4] = &pastel3;
            animations[5] = &none;
        }
};
