#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "hex-unit.hpp"

#include "animation-cycle-rings.cpp"
#include "animation-spin-rings.cpp"

static bool keep_running = true;

int main() {
    stdio_init_all();

    HexUnit hex_unit = HexUnit();

    RingSpinAnimation ring_spin_animation = RingSpinAnimation(hex_unit);
    RingCycleAnimation ring_cycle_animation = RingCycleAnimation(hex_unit);

    while (keep_running) {
        ring_spin_animation.run();

        // TODO: Figure out why we can't switch
        // ring_cycle_animation.run();
    }
}
