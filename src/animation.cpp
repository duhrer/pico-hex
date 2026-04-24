#include "animation.hpp"
#include "hex-unit.hpp"

Animation::Animation(HexUnit hexUnit) {
    this->hexUnit = hexUnit;
}

void Animation::run () {
    this->hexUnit.clear();

    // Reset so that run can be used for repeats.
    this -> frameNumber = 0;
    this -> isFinished = false;

    while (!this -> isFinished) {
        this->animateNextFrame();
        this->frameNumber++;
        sleep_ms(this->msDelayBetweenFrames);
    }
}
