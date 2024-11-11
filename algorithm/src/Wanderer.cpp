#include "../inc/Wanderer.hpp"

#include "../../core/inc/Random.hpp"

namespace jp::algorithm
{
   constexpr float EDGE_THRESHOLD = 2.f;
   constexpr float JUMP_CHANCE = 0.01f;

   Wanderer::Wanderer(const algorithm::Properties& properties, const std::shared_ptr<logic::Character>& character)
      : mProperties(properties),
      Bot(character, { Move::infiniteRun(logic::CharacterDirection::Right) }) {}

   void Wanderer::update(float dt)
   {
      Bot::update(dt);
      math::Vector2<float> position = getPosition();
      if (finishedMoves())
      {
         afterMove(position);
      }
      else if (getCurrentMove().type == MoveType::Run && !getVisitedSegments().empty())
      {
         wander(position);
         whileWander(position);
      }
   }

   void Wanderer::afterMove(math::Vector2<float>& position)
   {
      logic::CharacterDirection runDirection = static_cast<logic::CharacterDirection>(core::Random::getInt(1, 2));
      setMove(Move::infiniteRun(runDirection));
      mLastChangeDirectionPosition = position;
   }

   void Wanderer::whileWander(math::Vector2<float>& position)
   {
      if (core::Random::getFloat(0.f, 1.f) <= JUMP_CHANCE)
      {
         mSegmentBeforeJump = getCurrentSegment();
         setMove(Move::randomSideJump(10.f, mCharacter->getProperties().character.jump.max.y));
      }
   }

   void Wanderer::setMove(const Move& move)
   {
      if (mMoves.empty())
      {
         throw std::runtime_error("jp::algorithm::Wanderer::setMove - Failed to set move, moves are empty");
      }
      mFinishedMoves = false;
      mCurrentMove.id = 0;
      mCurrentMove.value = 0.f;
      mMoves.front() = move;
   }

   void Wanderer::wander(math::Vector2<float>& position)
   {
      float leftEdgeDiff = position.x + mCharacter->getRect().width - getCurrentSegment()->a.x;
      float rightEdgeDiff = getCurrentSegment()->b.x - position.x;
      if ((mLastPosition == position &&
         mLastChangeDirectionPosition != position) ||
         leftEdgeDiff < EDGE_THRESHOLD || rightEdgeDiff < EDGE_THRESHOLD)
      {
         if (leftEdgeDiff < EDGE_THRESHOLD)
         {
            mCharacter->setPosition(getCurrentSegment()->a.x - mCharacter->getRect().width + EDGE_THRESHOLD, mCharacter->getPosition().y);
         }
         else if (rightEdgeDiff < EDGE_THRESHOLD)
         {
            mCharacter->setPosition(getCurrentSegment()->b.x - EDGE_THRESHOLD, mCharacter->getPosition().y);
         }
         position = getPosition();;
         mCharacter->setRunSpeed(0.f);
         setMove(Move::infiniteRun(logic::Character::oppositeDirection(getDirection())));
         mLastChangeDirectionPosition = position;
      }
      mLastPosition = position;
   }
}