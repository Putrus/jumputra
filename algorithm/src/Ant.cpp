#include "../inc/Ant.hpp"

#include "../../core/inc/Random.hpp"

namespace jp::algorithm
{
   constexpr float COLLISION_THRESHOLD = 1.f;

   Ant::Ant(const algorithm::Properties& properties, const std::shared_ptr<logic::Character>& character, AntGraph& antGraph)
      : mGraph(antGraph), Wanderer(properties, character) {}

   void Ant::afterMove(math::Vector2<float>& position)
   {
      if (getCurrentSegment() != mSegmentBeforeJump && !(getVisitedSegments().size() > 2 &&
         getVisitedSegments().at(getVisitedSegments().size() - 3) == getCurrentSegment()))
      {
         if (!mDestinationPheromone)
         {
            float intensity = std::max(mSegmentBeforeJump->a.y - getCurrentSegment()->a.y +
               std::abs(mSegmentBeforeJump->a.x - getCurrentSegment()->a.x), mProperties.antColony.minIntensity);
            bool visited = false;
            for (size_t i = 0; i < getVisitedSegments().size() - 1; ++i)
            {
               if (getCurrentSegment() == getVisitedSegments().at(i))
               {
                  visited = true;
                  break;
               }
            }

            if (visited)
            {
               intensity = mProperties.antColony.minIntensity;
            }
            mGraph.insertPheromone(mSegmentBeforeJump, getCurrentSegment(),
               std::make_shared<Pheromone>(mLastPosition, getMoves().back(), intensity, 1.f));
         }
         else
         {
            bool visited = false;
            float intensity = std::max(mSegmentBeforeJump->a.y - getCurrentSegment()->a.y, mProperties.antColony.minIntensity);
            for (size_t i = 0; i < getVisitedSegments().size() - 1; ++i)
            {
               if (getCurrentSegment() == getVisitedSegments().at(i))
               {
                  visited = true;
                  break;
               }
            }

            if (visited)
            {
               intensity = mProperties.antColony.minIntensity;
            }
            mGraph.insertPheromone(mSegmentBeforeJump, getCurrentSegment(),
               std::make_shared<Pheromone>(mLastPosition, getMoves().back(), intensity, 1.f));
         }
      }

      mDestinationPheromone = mGraph.getDestinationPheromone(getCurrentSegment());
      if (!mDestinationPheromone)
      {
         Wanderer::afterMove(position);
      }
      else if (mDestinationPheromone->position.x > getPosition().x)
      {
         setMove(Move::infiniteRun(logic::CharacterDirection::Right));
      }
      else
      {
         setMove(Move::infiniteRun(logic::CharacterDirection::Left));
      }
   }

   void Ant::whileWander(math::Vector2<float>& position)
   {
      if (!mDestinationPheromone)
      {
         if (core::Random::getFloat(0.f, 1.f) <= mProperties.antColony.randomJumpChance)
         {
            mSegmentBeforeJump = getCurrentSegment();
            setMove(Move::randomSideJump(10.f, mCharacter->getProperties().character.jump.max.y));
         }
      }
      else if (std::abs(getPosition().x - mDestinationPheromone->position.x) < COLLISION_THRESHOLD)
      {
         mSegmentBeforeJump = getCurrentSegment();
         setMove(mDestinationPheromone->move);
      }
   }
}