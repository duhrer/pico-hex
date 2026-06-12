#ifndef ANIMATION_POLAR_FLAME_H
#define ANIMATION_POLAR_FLAME_H

#include "animation.hpp"
#include <stdlib.h>
#include <vector>
#include <algorithm>

#define STARTING_SPARKS 1800
#define MAX_FRAME_NUMBER STARTING_SPARKS/9

struct PolarCoords {
    int radius;
    int angle;
    uint8_t energy;
};

class PolarFlameAnimation : public FrameAnimation {
    private:
        std::vector<PolarCoords> sparks;
        int sparksLeft = STARTING_SPARKS;

        MixMode mix_mode;

        void addSparks() {
            // Generate new sparks on the outer edge, but use randomness to skew
            // the angle and choose whether to add a spark.
            int percent_chance_to_add = 65;
            for (int a = 0; a < 18; a++) {
                bool addSpark = ((rand() % 100) <= percent_chance_to_add);
                if (addSpark && sparksLeft) {
                    int skew = (rand() % 11) - 5;
                    int degrees = (a * 20) + skew;

                    uint8_t energy;
                    switch (mix_mode) {
                        case MixMode::FLAME:
                            energy = MAX_BRIGHTNESS / 4;
                            break;
                        default:
                            energy = MAX_BRIGHTNESS / 2;
                            break;
                    }

                    PolarCoords newCoords = {
                        3,
                        degrees,
                        energy
                    };
                    sparks.push_back(newCoords);

                    sparksLeft--;
                }
            }
        }

    public:
        PolarFlameAnimation(MixMode mixMode = MixMode::FLAME)
        : FrameAnimation()
        {
            this->mix_mode = mixMode;
            this->msDelayBetweenFrames = 125;
        }

        void start (HexUnit *hexUnit) {
            this -> sparksLeft = STARTING_SPARKS;
            sparks.clear();
            addSparks();

            FrameAnimation::start(hexUnit);
        }

        bool animateNextFrame() {
            // Check the current frame against our hard stop to avoid locking up.
            // TODO: Remove this if we can figure out why it was originally needed.
            if (frameNumber > MAX_FRAME_NUMBER) {
                isFinished = true;
            }
            else {
                // Move all existing sparks inwards and reduce their energy.
                for (std::vector<PolarCoords>::iterator coords = sparks.begin(); coords != sparks.end(); ++coords) {
                    coords -> radius -= 0.25;
                    coords -> angle += (rand() % 11 - 5);
                    coords -> energy = (coords -> energy) * 3 / 4; 
                }

                // Purge sparks that are past the event horizon
                sparks.erase(
                    std::remove_if(
                        sparks.begin(), sparks.end(),
                        [](PolarCoords & coords) { return coords.radius < 0 || coords.energy == 0; }
                    ),
                    sparks.end()
                );

                if (sparksLeft != 0) {
                    addSparks();
                }

                current_hex_unit -> clear();
                if (sparks.empty()) {
                    this->isFinished = true;
                }
                else {
                    // Set the base colour for the whole unit first.
                    uint32_t base_colour;
                    switch (mix_mode) {
                        case MixMode::PASTEL_ONE:
                            base_colour = current_hex_unit -> neopixels.Color(MAX_BRIGHTNESS / 2, 0, 0);
                            break;
                        case MixMode::PASTEL_TWO:
                            base_colour = current_hex_unit -> neopixels.Color(0, MAX_BRIGHTNESS / 2, 0);
                            break;
                        case MixMode::PASTEL_THREE:
                            base_colour = current_hex_unit -> neopixels.Color(0, 0, MAX_BRIGHTNESS / 2);
                            break;
                        // Covers FLAME, NONE, and MIX
                        default:
                            base_colour = current_hex_unit -> neopixels.Color(MAX_BRIGHTNESS, MAX_BRIGHTNESS / 4, 0);
                            break;
                    }
                    current_hex_unit -> fill(base_colour);
                
                    // Mix the extra energy from the sparks into the unit.
                    for (PolarCoords coords : sparks) {
                        uint32_t colour;
                        switch (mix_mode) {
                            case MixMode::PASTEL_TWO:
                                colour = current_hex_unit -> neopixels.Color(0, coords.energy, 0);
                                break;
                            case MixMode::PASTEL_THREE:
                                colour = current_hex_unit -> neopixels.Color(0, 0, coords.energy);
                                break;
                            // Covers FLAME, PASTEL_ONE, NONE, and MIX
                            default:
                                colour = current_hex_unit -> neopixels.Color(coords.energy, 0, 0);
                                break;
                        }

                        current_hex_unit -> fillPolarRegion(colour, coords.radius, coords.angle, 1.5, mix_mode);
                    }
                }
                current_hex_unit -> show();
            }

            return this->isFinished;
        }
};

class RollupPolarFlameAnimation : public RollupAnimation {
    private:
        PolarFlameAnimation flame_mode_animation = PolarFlameAnimation(MixMode::FLAME);
        PolarFlameAnimation pastel_mode_one_animation = PolarFlameAnimation(MixMode::PASTEL_ONE);
        PolarFlameAnimation pastel_mode_two_animation = PolarFlameAnimation(MixMode::PASTEL_TWO);
        PolarFlameAnimation pastel_mode_three_animation = PolarFlameAnimation(MixMode::PASTEL_THREE);

    public:
        RollupPolarFlameAnimation()
        : RollupAnimation()
        {
            animations[0] = &flame_mode_animation;
            animations[1] = &pastel_mode_three_animation;
            animations[2] = &pastel_mode_one_animation;
            animations[3] = &pastel_mode_two_animation;
        }

};

#endif