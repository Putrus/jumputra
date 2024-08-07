#include "../inc/Sequence.hpp"

namespace jp::algorithm
{
   Sequence::Sequence(const std::vector<Move>& moves, const std::shared_ptr<logic::Engine>& engine)
      : Algorithm(engine)
   {
      mMoves = moves;
   }

   void Sequence::update(float dt)
   {
      
      if (mEngine->getCharacters().empty() ||
         mCurrentMoveId >= mMoves.size())
      {
         mFinished = true;
         return;
      }
      logic::Character& character = *mEngine->characters().at(0);
      Move& move = mMoves.at(mCurrentMoveId);
      if (move.type == MoveType::Jump)
      {
         if (mCurrentMoveValue == 1.f && character.canSquat() &&
            character.getState() != logic::CharacterState::Squatting)
         {
            nextMove();
            return;
         }

         if (mCurrentMoveValue == 0.f)
         {
            if (character.canSquat())
            {
               character.setDirection(move.direction);
               character.squat();
               mCurrentMoveValue = 1.f;
            }
         }
         else if (character.getJumpPower().y >= move.value)
         {
            character.jump();
         }
      }
      else if (move.type == MoveType::Run)
      {
         mCurrentMoveValue += dt;
         if (mCurrentMoveValue >= move.value)
         {
            nextMove();
            return;
         }
         character.run(move.direction);
      }
      else
      {
         throw std::runtime_error("jp::algorithm::Sequence::update - Failed to update, wrong move type");
      }
   }

   bool Sequence::isFinished() const
   {
      return mFinished;
   }

   void Sequence::nextMove()
   {
      ++mCurrentMoveId;
      mCurrentMoveValue = 0.f;
   }
}