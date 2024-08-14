#include "../inc/Random.hpp"

namespace jp::core
{
   int Random::getInt(int min, int max)
   {
      std::uniform_int_distribution<int> distrib(min, max);

      return distrib(getGenerator());
   }

   float Random::getFloat(float min, float max)
   {
      std::uniform_real_distribution<float> distrib(min, max);

      return distrib(getGenerator());
   }

   std::mt19937& Random::getGenerator()
   {
      static std::mt19937 mRandomGenerator(std::random_device{}());
      return mRandomGenerator;
   }
}