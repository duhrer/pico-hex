#include <math.h>
#include <string.h>
#include <stdio.h>

#include "pico/stdlib.h"

#include "hex-unit.hpp"

#include "polar-mixing.hpp"

static bool keep_running = true;

static HexUnit hex_unit = HexUnit();

int main() {
    stdio_init_all();
    
    // Initial pause to help us know that the unit has been reset.
    sleep_ms(1000);

    hex_unit.begin();
    RollupPolarMixingAnimation rollup_polar_mixing_animation;

    rollup_polar_mixing_animation.start(&hex_unit);

    while (keep_running) {
        if (rollup_polar_mixing_animation.isFinished) {
            rollup_polar_mixing_animation.start(&hex_unit);
        }
        sleep_ms(500);
    }
}
