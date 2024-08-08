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

   bool Bot::finishedMoves() const
   {
      return mFinishedMoves;
   }

   void Bot::nextMove()
   {
      ++mCurrentMove.id;
      mCurrentMove.value = 0.f;
   }
}