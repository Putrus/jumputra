#include "../inc/Pheromone.hpp"

namespace jp::algorithm
{
   Pheromone::Pheromone(const math::Vector2<float>& position, const Move& move, float intensity)
      : mPosition(position), mMove(move), mIntensity(intensity) {}
   
   void Pheromone::evaporate(float value)
   {
      mIntensity -= value;
   }

   void Pheromone::increaseIntensity(float value)
   {
      mIntensity = std::min(100.f, mIntensity + value);
   }

   const Move& Pheromone::getMove() const
   {
      return mMove;
   }

   const math::Vector2<float>& Pheromone::getPosition() const
   {
      return mPosition;
   }

   float Pheromone::getIntensity() const
   {
      return mIntensity;
   }
}