#include <stdio.h>

#include "hex-unit.hpp"
#include "rollup-all.hpp"

static bool keep_running = true;

static HexUnit hex_unit = HexUnit();

int main() {
    stdio_init_all();
    
    // Initial pause to help us know that the unit has been reset.
    sleep_ms(1000);

    hex_unit.begin();

    RollupAllRandomAnimation rollup_animation;
    rollup_animation.start(&hex_unit);

    while (keep_running) {
        if (rollup_animation.isFinished) {
            rollup_animation.start(&hex_unit);
        }
        sleep_ms(500);
    }
}
