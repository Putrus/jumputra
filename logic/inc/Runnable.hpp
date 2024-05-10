#pragma once

#include "Updatable.hpp"

namespace jp::logic
{
   class Runnable : public logic::Updatable
   {
   public:
      Runnable(const float& secondsPerUpdate);

      void run();

      virtual void update(float dt) = 0;

      virtual void draw() = 0;
      virtual void event() = 0;

   protected:
      void terminate();

   private:
      const float &mSecondsPerUpdate;
      bool mIsRunning = true;
   };
}