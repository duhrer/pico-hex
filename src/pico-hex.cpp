#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "hex-unit.hpp"

#include "animations/animation-rollup-all.cpp"

static bool keep_running = true;

int main() {
    stdio_init_all();

    HexUnit hex_unit = HexUnit();
    hex_unit.begin();

    RollupAllAnimation rollup_animation;

    while (keep_running) {
        rollup_animation.run(hex_unit);
    }
}
