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
            int percent_chance_to_add = 60;
            for (int a = 0; a < 18; a++) {
                bool addSpark = ((rand() % 100) <= percent_chance_to_add);
                if (addSpark && sparksLeft) {
                    int skew = (rand() % 11) - 5;
                    int degrees = (a * 20) + skew;
                    PolarCoords newCoords = {
                        3,
                        degrees,
                        MAX_BRIGHTNESS / 4
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
            this->msDelayBetweenFrames = 100;
        }

        bool run (HexUnit *hexUnit) {
            this -> sparksLeft = STARTING_SPARKS;
            sparks.clear();
            addSparks();

            return FrameAnimation::run(hexUnit);
        }

        bool animateNextFrame(HexUnit *hexUnit) {
            // Move all existing sparks inwards, purge any with a negative radius.
            for (std::vector<PolarCoords>::iterator coords = sparks.begin(); coords != sparks.end(); ++coords) {
                coords -> radius--;
                coords -> angle += (rand() % 11 - 5);
            }

            // Purge sparks that are past the event horizon
            sparks.erase(
                std::remove_if(
                    sparks.begin(), sparks.end(),
                    [](PolarCoords & coords) { return coords.radius < 0; }
                ),
                sparks.end()
            );

            if (sparksLeft >= 0) {
                addSparks();
            }

            hexUnit -> clear();
            if (sparks.empty()) {
                this->isFinished = true;
            }
            else {
                // Render all sparks to the hex unit.
                for (PolarCoords coords : sparks) {
                    // uint32_t colour = hexUnit -> neopixels.Color(coords.energy, coords.energy / 2, 0);
                    uint32_t colour = hexUnit -> neopixels.Color(coords.energy, 0, 0);
                    hexUnit->fillPolarRegion(colour, coords.radius, coords.angle, 1.5, MixMode::FLAME);
                }
            }
            hexUnit -> show();

            return this->isFinished;
        }
};
