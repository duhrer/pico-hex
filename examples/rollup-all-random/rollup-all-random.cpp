#include <stdio.h>

#include "hex-unit.hpp"

#include "rollup-all-random.hpp"

static bool keep_running = true;

int main() {
    stdio_init_all();
    
    // Initial pause to help us know that the unit has been reset.
    sleep_ms(1000);

    while (keep_running) {
        static HexUnit hex_unit = HexUnit();
        hex_unit.begin();

        RollupAllRandomAnimation rollup_animation;
        rollup_animation.start(&hex_unit);

        while (!rollup_animation.isFinished) {
            sleep_ms(500);
        }
    }
}
