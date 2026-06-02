#ifndef ANIMATION_H
#define ANIMATION_H

#include "pico/rand.h"

#include "hex-unit.hpp"
// #include <list>
// #include <vector>

class Animation {      
   public:
      bool isFinished = false;

      Animation() = default;

      virtual bool run(HexUnit *hexUnit) = 0;
};

class FrameAnimation : public Animation {
   public:
      int msDelayBetweenFrames = 40; // 25 FPS (not counting drawing time)
      int frameNumber = 0;

      virtual bool animateNextFrame(HexUnit *hexUnit) = 0;

      bool run (HexUnit *hexUnit) {
         // Reset so that run can be used for repeats.
         this -> frameNumber = 0;
         this -> isFinished = false;

         while (!this -> isFinished) {
            this->isFinished = this->animateNextFrame(hexUnit);
            this->frameNumber++;
            sleep_ms(this->msDelayBetweenFrames);
         }

         return this->isFinished;
      }      
};

class RollupAnimation : public Animation {
   public:
      // https://stackoverflow.com/questions/43564387/list-for-abstact-objects
      // std::list<Animation*> animations;
      // std::vector<Animation*> animations;
      Animation* animations[16];

      bool run (HexUnit *hexUnit) {
         // Reset so that run can be used for repeats.
         this -> isFinished = false;

         for (Animation* animation : animations) 
         {
            if (animation) {
               animation -> run(hexUnit);              
            }
         }

         this->isFinished = true;

         return this->isFinished;
      }
};

class RandomisingRollupAnimation : public Animation {
   private:
      // bit register to ensure that each animation is run exactly once.
      uint16_t animations_used = 0;

   public:
      Animation* animations[16];

      bool run (HexUnit *hexUnit) {
         this -> isFinished = false;

         int animations_run = 0;

         while (animations_run < 16) {
            int animation_index = get_rand_32() % 16;

            if (((animations_used >> animation_index) & 1) == 0) {
               if (animations[animation_index]) {
                  animations[animation_index] -> run(hexUnit);
               }
               
               animation_index |= 1 << animation_index;
               animations_run++;
            }
         }

         return this->isFinished;
      }
};

#endif