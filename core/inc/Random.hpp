#pragma once

#include <random>

namespace jp::core
{
   class Random
   {
   public:
      static int getInt(int min, int max);
      static float getFloat(float min, float max);

   private:
      static std::mt19937& getGenerator();
   };
}