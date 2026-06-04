#ifndef ANIMATION_POLAR_FLAME_H
#define ANIMATION_POLAR_FLAME_H

#include "animation.hpp"
#include <stdlib.h>
#include <vector>
#include <algorithm>

#define STARTING_SPARKS 1800

struct PolarCoords {
    int radius;
    int angle;
    uint8_t energy;
};

class PolarFlameAnimation : public FrameAnimation {
    private:
        std::vector<PolarCoords> sparks;
        int sparksLeft = STARTING_SPARKS;

        void addSparks() {
            // Generate new sparks on the outer edge, but use randomness to skew
            // the angle and choose whether to add a spark.
            int percent_chance_to_add = 65;
            for (int a = 0; a < 18; a++) {
                bool addSpark = ((rand() % 100) <= percent_chance_to_add);
                if (addSpark && sparksLeft) {
                    int skew = (rand() % 11) - 5;
                    int degrees = (a * 20) + skew;

                    uint8_t energy = MAX_BRIGHTNESS / 4;

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
        PolarFlameAnimation()
        : FrameAnimation()
        {
            this->msDelayBetweenFrames = 125;
        }

        void start (HexUnit *hexUnit) {
            this -> sparksLeft = STARTING_SPARKS;
            sparks.clear();
            addSparks();

            FrameAnimation::start(hexUnit);
        }

        bool animateNextFrame() {
            // Move all existing sparks inwards, purge any with a negative radius.
            for (std::vector<PolarCoords>::iterator coords = sparks.begin(); coords != sparks.end(); ++coords) {
                coords -> radius -= 0.125;
                coords -> angle += (rand() % 11 - 5);
            }

            // Purge sparks that are past the event horizon
            sparks.erase(
                std::remove_if(
                    sparks.begin(), sparks.end(),
                    [](PolarCoords & coords) { return coords.radius < 0 || coords.energy == 0; }
                ),
                sparks.end()
            );

            if (sparksLeft >= 0) {
                addSparks();
            }

            current_hex_unit -> clear();
            if (sparks.empty()) {
                this->isFinished = true;
            }
            else {
                // Set the base colour for the whole unit first.
                uint32_t base_colour = current_hex_unit -> neopixels.Color(MAX_BRIGHTNESS, MAX_BRIGHTNESS / 4, 0);
                current_hex_unit -> fill(base_colour);
            
                // Mix the extra energy from the sparks into the unit.
                for (PolarCoords coords : sparks) {
                    uint32_t colour = current_hex_unit -> neopixels.Color(coords.energy, 0, 0);
                    current_hex_unit -> fillPolarRegion(colour, coords.radius, coords.angle, 1.5, MixMode::FLAME);
                }
            }
            current_hex_unit -> show();

            return this->isFinished;
        }
};

#endif