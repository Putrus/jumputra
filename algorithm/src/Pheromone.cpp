#include "../inc/Pheromone.hpp"

namespace jp::algorithm
{
   Pheromone::Pheromone(Move move, float intensity)
      : mMove(move), mIntensity(intensity) {}
   
   void Pheromone::evaporate(float dt)
   {
      mIntensity -= dt;
   }

   void Pheromone::increaseIntensity(float value)
   {
      mIntensity += value;
   }

   Move Pheromone::getMove() const
   {
      return mMove;
   }

   float Pheromone::getIntensity() const
   {
      return mIntensity;
   }
}