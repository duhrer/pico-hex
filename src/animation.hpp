#ifndef ANIMATION_H
#define ANIMATION_H

#include "hex-unit.hpp"

class Animation {      
   public:
      bool isFinished = false;

      HexUnit hexUnit;

      int msDelayBetweenFrames = 40; // 25 FPS (not counting drawing time)
      int frameNumber = 0;

      Animation(HexUnit hexUnit);

      virtual void animateNextFrame() = 0;

      void run();
};

/*
    TODO: Make a bunch of animations, such as:

    1. A ring clock.
    2. A series of colour mixing bodies that move through a polar layout based
       on gravity.
    3. scrolling text in interlaced, sawtooth, italic, and reverse italic
       layouts
    4. An animated "eye" that opens, looks around, and closes.
    5. A ring version of our colour mixing algo, where r, g, and b "bands" move
       within the ring.

*/

#endif