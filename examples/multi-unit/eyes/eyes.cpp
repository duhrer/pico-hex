#include <math.h>
#include <string.h>
#include <stdio.h>

#include "pico/stdlib.h"

#include "hex-unit.hpp"

#include "../../rollup-eye/rollup-eye.hpp"

static bool keep_running = true;

static HexUnit hex_unit = HexUnit(2);

// TODO: This does not survive a reset. Figure out why.

int main() {
    stdio_init_all();
    
    // Initial pause to help us know that the unit has been reset.
    sleep_ms(1000);

    hex_unit.begin();

    RollupEyeAnimation left_eye_animation = RollupEyeAnimation(0);
    RollupEyeAnimation right_eye_animation = RollupEyeAnimation(1);

    left_eye_animation.start(&hex_unit);
    right_eye_animation.start(&hex_unit);

    while (keep_running) {
        if (left_eye_animation.isFinished && right_eye_animation.isFinished) {
            left_eye_animation.start(&hex_unit);
            right_eye_animation.start(&hex_unit);
        }
        sleep_ms(500);
    }
}
