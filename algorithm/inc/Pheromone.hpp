#pragma once

#include "Move.hpp"

namespace jp::algorithm
{
   class Pheromone
   {
   public:
      Pheromone(const math::Vector2<float>& position, const Move& move,
         float intensity, const std::shared_ptr<logic::Segment>& segment);

      void evaporate(float value);
      void increaseIntensity(float value);

      const Move& getMove() const;
      const math::Vector2<float>& getPosition() const;
      float getIntensity() const;
      const std::shared_ptr<logic::Segment>& getSegment() const;

   private:
      math::Vector2<float> mPosition;
      Move mMove;
      float mIntensity = 0.f;
      std::shared_ptr<logic::Segment> mSegment;
   };
}