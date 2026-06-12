#include <math.h>
#include <string.h>
#include <stdio.h>

#include "pico/stdlib.h"

#include "hex-unit.hpp"

#include "cubic-cycle.hpp"

static bool keep_running = true;

static HexUnit hex_unit = HexUnit();

int main() {
    stdio_init_all();
    
    // Initial pause to help us know that the unit has been reset.
    sleep_ms(1000);

    hex_unit.begin();

    CubicCycleAnimation cubic_cycle_animation;

    cubic_cycle_animation.start(&hex_unit);

    while (keep_running) {
        if (cubic_cycle_animation.isFinished) {
            cubic_cycle_animation.start(&hex_unit);
        }
        sleep_ms(500);
    }
}
