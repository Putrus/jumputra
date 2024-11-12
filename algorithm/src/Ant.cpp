#include "../inc/Ant.hpp"

#include "../../core/inc/Random.hpp"

namespace jp::algorithm
{
   constexpr float COLLISION_THRESHOLD = 1.f;

   Ant::Ant(const algorithm::Properties& properties, const std::shared_ptr<logic::Character>& character, AntGraph& antGraph)
      : mGraph(antGraph), Wanderer(properties, character) {}

   void Ant::afterMove(math::Vector2<float>& position)
   {
      auto currentSegment = getCurrentSegment();
      auto visitedSegments = getVisitedSegments();
      if (currentSegment != mSegmentBeforeJump)
      {
         float heightDiff = mSegmentBeforeJump->a.y - getCurrentSegment()->a.y;
         float intensity = std::max(heightDiff + std::abs(mSegmentBeforeJump->a.x - getCurrentSegment()->a.x),
            mProperties.antColony.minIntensity);

         if (isSegmentVisited(currentSegment, visitedSegments.size() - 1))
         {
            intensity = heightDiff > 0 ? mProperties.antColony.minIntensity : 0.f;
         }

         mGraph.insertPheromone(mSegmentBeforeJump, getCurrentSegment(),
            std::make_shared<Pheromone>(mLastPosition, getMoves().back(), intensity, mJumpTime));
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
            mJumpTime = 0.f;
         }
      }
      else if (std::abs(getPosition().x - mDestinationPheromone->position.x) < COLLISION_THRESHOLD)
      {
         mSegmentBeforeJump = getCurrentSegment();
         setMove(mDestinationPheromone->move);
         mJumpTime = 0.f;
      }
   }
}