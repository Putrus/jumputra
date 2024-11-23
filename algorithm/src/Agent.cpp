#include "../inc/Agent.hpp"

#include "../../core/inc/Random.hpp"

namespace jp::algorithm
{
   constexpr float COLLISION_THRESHOLD = 1.f;

   Agent::Agent(const algorithm::Properties& properties, const std::shared_ptr<logic::Character>& character, QGraph& graph)
      : mGraph(graph), Wanderer(properties, character) {}

   void Agent::afterMove(math::Vector2<float>& position)
   {
      auto currentSegment = getCurrentSegment();
      auto visitedSegments = getVisitedSegments();
      if (currentSegment != mSegmentBeforeJump)
      {
         float reward = mSegmentBeforeJump->a.y - getCurrentSegment()->a.y;

         mGraph.insertEdge(mSegmentBeforeJump, currentSegment,
            std::make_shared<EdgeMove>(mLastPosition, getMoves().back(), reward, mJumpTime));
         std::cout << getPosition() << std::endl;
         // if (getPosition().y < mTMPBestPosition.y)
         // {
         //    mTMPBestPosition = getPosition();
         // }
      }

      mDestinationAction = nullptr;
      if (core::Random::getFloat(0.f, 1.f) > mProperties.qLearning.epsilon)
      {
         mDestinationAction = mGraph.getBestAction(currentSegment);
      }

      if (!mDestinationAction)
      {
         Wanderer::afterMove(position);
      }
      else if (mDestinationAction->position.x > getPosition().x)
      {
         setMove(Move::infiniteRun(logic::CharacterDirection::Right));
      }
      else
      {
         setMove(Move::infiniteRun(logic::CharacterDirection::Left));
      }
   }

   void Agent::whileWander(math::Vector2<float>& position)
   {
      // if (mTMPTime > 500)
      // {
      //    std::cout << "---------------------------------------------" << std::endl;
      //    std::cout << mGraph << std::endl;
      //    std::cout << "Position: " << getPosition() << std::endl;
      //    std::cout << "Best position: " << mTMPBestPosition << std::endl;
      //    mTMPBestPosition = math::Vector2<float>(0.f, 90000.f);
      //    mTMPTime = 0.f;
      // }
      // mTMPTime += 0.016f;
      if (!mDestinationAction)
      {
         if (core::Random::getFloat(0.f, 1.f) <= mProperties.qLearning.randomJumpChance)
         {
            mSegmentBeforeJump = getCurrentSegment();
            setMove(Move::randomSideJump(10.f, mCharacter->getProperties().character.jump.max.y));
            mJumpTime = 0.f;
         }
      }
      else if (std::abs(getPosition().x - mDestinationAction->position.x) < COLLISION_THRESHOLD)
      {
         mSegmentBeforeJump = getCurrentSegment();
         mCharacter->setPosition(mDestinationAction->position);
         mLastPosition = mCharacter->getPosition();
         setMove(mDestinationAction->move);
         mJumpTime = 0.f;
      }
   }
}