#ifndef ANIMATION_H
#define ANIMATION_H

#include "pico/rand.h"

#include "hex-unit.hpp"

class Animation {      
   protected:
      struct repeating_timer timer;
   public:
      bool isFinished = false;
      HexUnit *current_hex_unit;
 
      // Need a default constructor and destructor to avoid "undefined reference to vtable" linker errors.
      Animation() {};
      ~Animation() {};

      // These needed to be defined as empty functions to avoid the same linker errors.
      virtual void start(HexUnit *hexUnit) {};
      virtual void stop() {};
};

class FrameAnimation : public Animation {
   public:
      int msDelayBetweenFrames = 40; // 25 FPS (not counting drawing time)
      int frameNumber = 0;

      virtual bool animateNextFrame() {
         return false;
      }

      void start(HexUnit *HexUnit);

      void stop() {
         cancel_repeating_timer(&timer);
      }

      FrameAnimation() 
      : Animation() {
      }

      ~FrameAnimation() {
         stop();
      }
};

// We have to define this once the class is defined.
bool call_animate_next_frame(struct repeating_timer *rt) {
   FrameAnimation *frame_animation = (FrameAnimation *) rt->user_data;

   frame_animation -> frameNumber++;
   frame_animation -> animateNextFrame();

   return !(frame_animation -> isFinished);
}

// We have to define the start method after the definition above.
void FrameAnimation::start (HexUnit *hexUnit) {
   // Stash the hexUnit
   current_hex_unit = hexUnit;

   // Reset so that run can be used for repeats.
   frameNumber = 0;
   isFinished = false;

   // Start our timer
   add_repeating_timer_ms(msDelayBetweenFrames, call_animate_next_frame, (void *) this, &timer);
}

class RollupAnimation : public Animation {
   protected:
      int animationPollingMs = 250;
   public:
      Animation* animations[16];
      int animation_index = 0;
      Animation *current_animation;

      void start (HexUnit *hexUnit);

      void stop() {
         cancel_repeating_timer(&timer);
      }

      ~RollupAnimation() {
         stop();
      }

      void pick_next() {
         current_animation = NULL;
         while (animation_index < 16 && !(current_animation)) {
            Animation *animation = animations[animation_index];
            if (animation) {
               current_animation = animation;
               animation -> start(current_hex_unit);
            }

            animation_index++;
         }

         if (animation_index == 16) {
            isFinished = true;
            // stop();
         }
      }
};

// Must be defined after the rollup animation class stub above.
bool check_animation(struct repeating_timer *rt) {
   RollupAnimation *rollup_animation = (RollupAnimation *) rt->user_data;

   if (!(rollup_animation -> isFinished)) {
      bool pick_next = false;

      if (rollup_animation -> current_animation) {
         if (rollup_animation -> current_animation -> isFinished) {
            pick_next = true;
         }
      }
      else {
         pick_next = true;
      }

      if (pick_next) {
         rollup_animation -> pick_next();
      }
   }

   return !(rollup_animation -> isFinished);
}

// Must be defined after the callback method above.
void RollupAnimation::start (HexUnit *hexUnit) {
   // Stash the hexUnit
   current_hex_unit = hexUnit;

   // Reset so that run can be used for repeats.
   this -> isFinished = false;
   animation_index = 0;

   add_repeating_timer_ms(this->animationPollingMs, check_animation, (void *) this, &timer);
}

// TODO: add a start method or otherwise reset things (reset method called in
// the parent start method?)

class RandomisingRollupAnimation : public RollupAnimation {
   private:
      // bit register to ensure that each animation is run exactly once.
      uint16_t used_animation_register = 0;

      // I could use numeric_limits<uint16_t>::max() apparently, but I'm
      // sticking to something simpler for now.
      int animations_run = 0;

   public:
      void start (HexUnit *hexUnit);

      void pick_next() {
         if (current_animation) {
            // This is a little bit of belt and braces, but make sure the current
            // animation isn't running.
            current_animation->stop();
            current_animation = NULL;
         }

         while (!current_animation && animations_run < 16) {
            int animation_index = get_rand_32() % 16;

            // Make sure we haven't randomly run this one already.
            if (((used_animation_register >> animation_index) & 1) == 0) {
               if (animations[animation_index]) {
                  current_animation = animations[animation_index];
                  current_animation -> start(current_hex_unit);
               }
               
               used_animation_register &= (1 << animation_index);
               animations_run++;
            }
         }

         // This should only be 16 if we kept checking all available options and
         // ran off the end. Otherwise the main scheduler callback will handle things.
         if (animations_run == 16) {
            isFinished = true;
            // stop();
         }
      }
};

// Must be defined after the rollup animation class stub above.
bool check_random_animation(struct repeating_timer *rt) {
   RandomisingRollupAnimation *rollup_animation = (RandomisingRollupAnimation *) rt->user_data;

   if (!(rollup_animation -> isFinished)) {
      bool pick_next = false;

      if (rollup_animation -> current_animation) {
         if (rollup_animation -> current_animation -> isFinished) {
            pick_next = true;
         }
      }
      else {
         pick_next = true;
      }

      if (pick_next) {
         rollup_animation -> pick_next();
      }
   }

   return !(rollup_animation -> isFinished);
}

void RandomisingRollupAnimation::start(HexUnit *hexUnit) {
   // Stash the hexUnit
   current_hex_unit = hexUnit;

   // Reset our state for a fresh run
   animations_run = 0;
   used_animation_register = 0;
   this -> isFinished = false;

   add_repeating_timer_ms(this->animationPollingMs, check_random_animation, (void *) this, &timer);
}

// TODO: Write a looping multi-unit animation to test this.
class MultiLoopAnimation : public RollupAnimation {
   public:
      int animation_cycles = 16;
      int animation_cycles_left;

      void start (HexUnit *hexUnit);

      void stop() {
         cancel_repeating_timer(&timer);
      }

      ~MultiLoopAnimation() {
         stop();
      }
};

// Must be defined after the class stub.
bool check_loop(struct repeating_timer *rt) {
   MultiLoopAnimation *loop_animation = (MultiLoopAnimation *) rt->user_data;

   if (loop_animation -> animation_cycles_left) {
      // If we have cycles left, start any animations we can
      for (Animation *animation : loop_animation -> animations) {
         if (animation) {
            if (animation -> isFinished) {
               loop_animation -> animation_cycles_left--;

               if (loop_animation -> animation_cycles_left) {
                  animation -> start(loop_animation -> current_hex_unit);
               }
            }
         }
      }
   }

   // This should only be triggered when `animation_cycles` worth of individual
   // loops have run.
   if (loop_animation -> animation_cycles_left == 0) {
      loop_animation -> isFinished = true;
      // loop_animation -> stop();
   }

   return !(loop_animation -> isFinished);
}

// Must be defined after the scheduler callback.
void MultiLoopAnimation::start (HexUnit *hexUnit) {
   // Stash the hexUnit
   current_hex_unit = hexUnit;

   // Reset so that run can be used for repeats.
   this -> isFinished = false;
   animation_cycles_left = animation_cycles;

   // Start all animations initially.
   for (Animation *animation : animations) {
      animation -> start(current_hex_unit);
   }

   // Check periodically to see if any animations are finished and loop them.
   add_repeating_timer_ms(this->animationPollingMs, check_loop, (void *) this, &timer);
}

#endif