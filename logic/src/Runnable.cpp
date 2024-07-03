#include "../inc/Runnable.hpp"

#include <chrono>
#include <utility>

namespace jp::logic
{
   constexpr float NANOSECONDS_IN_ONE_SECOND = 1000000000;

   Runnable::Runnable(const float& secondsPerUpdate) : mSecondsPerUpdate(secondsPerUpdate) {}

   void Runnable::run()
   {
      auto begin = std::chrono::steady_clock::now();
      float time = 0.f;
      while (mIsRunning)
      {
         auto end = std::chrono::steady_clock::now();
         time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() / NANOSECONDS_IN_ONE_SECOND;
         begin = std::move(end);
         while (time >= mSecondsPerUpdate)
         {
            time -= mSecondsPerUpdate;
            update(mSecondsPerUpdate);
            
            if (mSecondsPerUpdate <= 0)
            {
               break;
            }
         }
         draw();
         event();
      }
   }

   void Runnable::terminate()
   {
      mIsRunning = false;
   }
}