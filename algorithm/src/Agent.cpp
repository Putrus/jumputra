#include "../inc/Agent.hpp"

#include "../../core/inc/Random.hpp"

namespace jp::algorithm
{
   constexpr float COLLISION_THRESHOLD = 0.25f;

   Agent::Agent(const algorithm::Properties& properties, const std::shared_ptr<logic::Character>& character)
      : mProperties(properties),
      Bot(character, { Move::infiniteRun(logic::CharacterDirection::Right) }) {}

   void Agent::update(float dt)
   {
      Bot::update(dt);

      math::Vector2<float> position = getPosition();
      if (finishedMoves())
      {
         if (mSegmentBeforeJump != getVisitedSegments().back())
         {
            std::shared_ptr<AgentMove> move = std::make_shared<AgentMove>(mLastPosition,
               getMoves().back(), mSegmentBeforeJump->a.y - getVisitedSegments().back()->a.y);
            mGraph[mSegmentBeforeJump->a][getVisitedSegments().back()->a] = move;
            mBackwardGraph[mSegmentBeforeJump->a][getVisitedSegments().back()->a] = move;

            for (const auto& segment : mGraph)
            {
               std::cout << segment.first << " : " << std::endl;
               for (const auto& neighbour : segment.second)
               {
                  std::cout << "{ " << neighbour.first << ", " << neighbour.second << " }" << std::endl;
               }
               std::cout << std::endl;
            }
         }

         logic::CharacterDirection runDirection = static_cast<logic::CharacterDirection>(core::Random::getInt(1, 2));
         setMove(Move::infiniteRun(runDirection));
         mLastChangeDirectionPosition = position;
      }
      else if (getCurrentMove().type == MoveType::Run)
      {
         if (mLastPosition == position &&
            mLastChangeDirectionPosition != position)
         {
            setMove(Move::infiniteRun(logic::Character::oppositeDirection(getDirection())));
            mLastChangeDirectionPosition = position;
         }
         mLastPosition = position;

         if (core::Random::getFloat(0.f, 1.f) <= mProperties.antColony.randomJumpChance)
         {
            if (getVisitedSegments().empty())
            {
               throw std::runtime_error("jp::algorithm::Agent::Update - Failed to get segment before jump, visited segments are empty");
            }
            mSegmentBeforeJump = getVisitedSegments().back();
            setMove(Move::randomSideJump(10.f, mCharacter->getProperties().character.jump.max.y));
         }
      }
   }

   void Agent::setMove(const Move& move)
   {
      if (mMoves.empty())
      {
         throw std::runtime_error("jp::algorithm::Agent::setMove - Failed to set move, moves are empty");
      }
      mFinishedMoves = false;
      mCurrentMove.id = 0;
      mCurrentMove.value = 0.f;
      mMoves.front() = move;
   }
}