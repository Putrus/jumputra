#include "../inc/Bot.hpp"

namespace jp::algorithm
{
   Bot::Bot(const std::shared_ptr<logic::Character>& character, const std::vector<Move>& moves/* = {}*/)
      : mCharacter(character), Movable(moves) {}

   void Bot::update(float dt)
   {
      if (mCurrentMove.id >= mMoves.size())
      {
         mFinishedMoves = true;
         return;
      }

      Move& currentMove = mMoves.at(mCurrentMove.id);
      if (currentMove.type == MoveType::Jump)
      {
         if (mCurrentMove.value == 1.f && mCharacter->canSquat() &&
            mCharacter->getState() != logic::CharacterState::Squatting)
         {
            addVisitedHorizontalSegment();
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
            addVisitedHorizontalSegment();
            mCharacter->jump();
         }
      }
      else if (currentMove.type == MoveType::Run)
      {
         mCurrentMove.value += dt;
         if (mCurrentMove.value >= currentMove.value)
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

   const std::shared_ptr<logic::Character>& Bot::getCharacter() const
   {
      return mCharacter;
   }

   math::Vector2<float> Bot::getPosition() const
   {
      return mCharacter->getPosition();
   }

   logic::CharacterDirection Bot::getDirection() const
   {
      return mCharacter->getDirection();
   }

   const std::vector<std::shared_ptr<logic::Segment>>& Bot::getVisitedHorizontalSegments() const
   {
      return mVisitedHorizontalSegments;
   }

   std::shared_ptr<logic::Segment> Bot::getPreviousVisitedHorizontalSegment() const
   {
      if (mVisitedHorizontalSegments.size() < 2)
      {
         return nullptr;
      }
      return mVisitedHorizontalSegments.at(mVisitedHorizontalSegments.size() - 2);
   }

   std::shared_ptr<logic::Segment> Bot::getCurrentVisitedHorizontalSegment() const
   {
      if (mVisitedHorizontalSegments.empty())
      {
         return nullptr;
      }
      return mVisitedHorizontalSegments.back();
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

   Move Bot::getFirstMove() const
   {
      if (mMoves.empty())
      {
         return Move();
      }
      return mMoves.front();
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

   logic::CharacterDirection Bot::oppositeDirection(logic::CharacterDirection direction) const
   {
      if (direction == logic::CharacterDirection::Left)
      {
         return logic::CharacterDirection::Right;
      }
      else if (direction == logic::CharacterDirection::Right)
      {
         return logic::CharacterDirection::Left;
      }
      else
      {
         return logic::CharacterDirection::Up;
      }
   }

   void Bot::addVisitedHorizontalSegment()
   {
      if (mVisitedHorizontalSegments.empty() || mVisitedHorizontalSegments.back() != mCharacter->getLastHorizontalSegment())
      {
         mVisitedHorizontalSegments.push_back(mCharacter->getLastHorizontalSegment());
      }
   }
}