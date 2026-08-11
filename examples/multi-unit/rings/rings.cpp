#include <math.h>
#include <string.h>
#include <stdio.h>

#include "pico/stdlib.h"

#include "hex-unit.hpp"

#include "../../ring-spin/ring-spin.hpp"

static bool keep_running = true;

static HexUnit hex_unit = HexUnit(2);

int main() {
    stdio_init_all();
    
    // Initial pause to help us know that the unit has been reset.
    sleep_ms(1000);

    hex_unit.begin();

    RingSpinAnimation first_unit_animation;
    RingSpinAnimation second_unit_animation = RingSpinAnimation(1);

    first_unit_animation.start(&hex_unit);
    second_unit_animation.start(&hex_unit);

    while (keep_running) {
        if (first_unit_animation.isFinished && second_unit_animation.isFinished) {
            first_unit_animation.start(&hex_unit);
            second_unit_animation.start(&hex_unit);
        }

        sleep_ms(500);
    }
}
