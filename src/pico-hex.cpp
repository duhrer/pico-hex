#include <math.h>
#include <string.h>
#include <stdio.h>

#include "pico/stdlib.h"

#include "hardware/gpio.h"

#include "hex-unit.hpp"

#include "animations/animation-rollup-all.hpp"

static bool keep_running = true;

#define DECREASE_BRIGHTNESS_PIN 16
#define INCREASE_BRIGHTNESS_PIN 21

static HexUnit hex_unit = HexUnit();

static bool decrease_brightness_held = false;
static bool increase_brightness_held = false;

// TODO: Get GPIO working.
void button_irq_callback(uint gpio, uint32_t event_mask) {
    bool new_decrease_brightness = gpio_get(DECREASE_BRIGHTNESS_PIN);
    bool new_increase_brightness = gpio_get(INCREASE_BRIGHTNESS_PIN);

    // holding both buttons does nothing
    if (new_decrease_brightness && new_increase_brightness) {
        keep_running = false;
    }
    else if (new_decrease_brightness && !decrease_brightness_held) {
        hex_unit.decreaseBrightness();
    }
    else if (new_increase_brightness && !increase_brightness_held) {
        hex_unit.increaseBrightness();
    }

    decrease_brightness_held = new_decrease_brightness;
    increase_brightness_held = new_increase_brightness;
}

int main() {
    stdio_init_all();
    
    // uint32_t event_mask = GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE;

    // gpio_init(DECREASE_BRIGHTNESS_PIN);
    // gpio_set_dir(DECREASE_BRIGHTNESS_PIN, GPIO_IN);
    // gpio_set_irq_enabled_with_callback(DECREASE_BRIGHTNESS_PIN, event_mask, true, &button_irq_callback);

    // gpio_init(INCREASE_BRIGHTNESS_PIN);
    // gpio_set_dir(INCREASE_BRIGHTNESS_PIN, GPIO_IN);
    // gpio_set_irq_enabled_with_callback(INCREASE_BRIGHTNESS_PIN, event_mask, true, &button_irq_callback);

    // Initial pause to help us know that the unit has been reset.
    sleep_ms(1000);

    hex_unit.begin();

    RollupAllAnimation rollup_animation;
    rollup_animation.start(&hex_unit);

    while (keep_running) {
        if (rollup_animation.isFinished) {
            rollup_animation.start(&hex_unit);
        }
        sleep_ms(500);
    }
}
