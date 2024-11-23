#include "../inc/Bot.hpp"

namespace jp::algorithm
{
   Bot::Bot(const std::shared_ptr<logic::Character>& character, const std::vector<Move>& moves/* = {}*/)
      : mPositionBeforeMoves(character->getPosition()), mCharacter(character), mFinishedCharacter(*character), Movable(moves) {}

   void Bot::update(float dt)
   {
      if (mCurrentMove.id >= mMoves.size())
      {
         if (mFinishedMoves == false)
         {
            mCharacter->stop();
            mFinishedCharacter = *mCharacter;
            mFinishedMoves = true;
         }
         return;
      }

      Move& currentMove = mMoves.at(mCurrentMove.id);
      if (currentMove.type == MoveType::Jump)
      {
         if (mCurrentMove.value == 1.f && mCharacter->canSquat() &&
            mCharacter->getState() != logic::CharacterState::Squatting)
         {
            nextMove();
            return;
         }

         if (mCurrentMove.value == 0.f)
         {
            if (mCharacter->canSquat())
            {
               mCharacter->setDirection(currentMove.direction);
               mCharacter->squat();
               mCurrentMove.value = 1.f;
            }
         }
         else if (mCharacter->getJumpPower().y >= currentMove.value)
         {
            mCharacter->jump();
         }
      }
      else if (currentMove.type == MoveType::Run)
      {
         mCurrentMove.value += dt;
         if (mCurrentMove.value > currentMove.value && mCharacter->canSquat())
         {
            nextMove();
            return;
         }
         mCharacter->run(currentMove.direction);
      }
      else
      {
         throw std::runtime_error("jp::algorithm::Bot::update - Failed to update, wrong current move type");
      }   
   }

   void Bot::reset(const math::Rect<float>& rect, const std::vector<Move>& moves)
   {
      mCharacter->reset(rect);
      mFinishedCharacter.reset(rect);
      mMoves = moves;
      mFinishedMoves = false;
      mPositionBeforeMoves = rect.getPosition();
   }

   const std::shared_ptr<logic::Character>& Bot::getCharacter() const
   {
      return mCharacter;
   }

   const std::shared_ptr<logic::Segment>& Bot::getCurrentSegment() const
   {
      if (getVisitedSegments().empty())
      {
         throw std::runtime_error("jp::algorithm::Bot::getCurrentSegments - Failed to get current segment, visited segments are empty");
      }
      return getVisitedSegments().back();
   }

   math::Vector2<float> Bot::getPosition() const
   {
      return mCharacter->getPosition();
   }

   math::Vector2<float> Bot::getPositionBeforeMoves() const
   {
      return mPositionBeforeMoves;
   }

   logic::CharacterDirection Bot::getDirection() const
   {
      return mCharacter->getDirection();
   }

   const logic::Character& Bot::getFinishedCharacter() const
   {
      return mFinishedCharacter;
   }

   const std::vector<std::shared_ptr<logic::Segment>>& Bot::getVisitedSegments() const
   {
      return mCharacter->getVisitedSegments();
   }

   bool Bot::isSegmentVisited(const std::shared_ptr<logic::Segment>& segment, size_t size) const
   {
      auto visitedSegments = getVisitedSegments();
      size = std::min(visitedSegments.size(), size);
      for (size_t i = 0; i < size; ++i)
      {
         if (segment == getVisitedSegments().at(i))
         {
            return true;
         }
      }
      return false;
   }

   bool Bot::finishedMoves() const
   {
      return mFinishedMoves;
   }

   Move Bot::getCurrentMove() const
   {
      if (mCurrentMove.id < mMoves.size())
      {
         return mMoves.at(mCurrentMove.id);
      }
      else
      {
         return Move();
      }
   }

   void Bot::clearMoves()
   {
      mMoves.clear();
      mCurrentMove.id = 0;
      mCurrentMove.value = 0.f;
   }

   void Bot::nextMove()
   {
      ++mCurrentMove.id;
      mCurrentMove.value = 0.f;
   }
}