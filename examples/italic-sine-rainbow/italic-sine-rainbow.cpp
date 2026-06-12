#include <math.h>
#include <string.h>
#include <stdio.h>

#include "pico/stdlib.h"

#include "hex-unit.hpp"

#include "italic-sine-rainbow.hpp"

static bool keep_running = true;

static HexUnit hex_unit = HexUnit();

int main() {
    stdio_init_all();
    
    // Initial pause to help us know that the unit has been reset.
    sleep_ms(1000);

    hex_unit.begin();

    ItalicSineAnimation italic_sine_animation;

    italic_sine_animation.start(&hex_unit);

    while (keep_running) {
        if (italic_sine_animation.isFinished) {
            italic_sine_animation.start(&hex_unit);
        }
        sleep_ms(500);
    }
}
