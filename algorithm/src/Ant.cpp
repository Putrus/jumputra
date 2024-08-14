#include "../inc/Ant.hpp"

namespace jp::algorithm
{
   Ant::Ant(const std::shared_ptr<logic::Character>& character)
      : Bot(character, { Move(MoveType::Run, logic::CharacterDirection::Right, 2.f) }) {}

   void Ant::update(float dt)
   {
      Bot::update(dt);
      Move currentMove = getCurrentMove();
      std::cout << mLastPosition << " " << getCharacter()->getPosition() << std::endl;
      if (currentMove.type == MoveType::Run && mLastPosition == getCharacter()->getPosition()
         && mLastDirection != currentMove.direction)
      {
         clearMoves();
         if (currentMove.direction == logic::CharacterDirection::Left)
         {
            mMoves.push_back(Move(MoveType::Run, logic::CharacterDirection::Right, 2.f));
         }
         else
         {
            mMoves.push_back(Move(MoveType::Run, logic::CharacterDirection::Left, 2.f));
         }
      }
      else
      {
         if (mLastPosition != getCharacter()->getPosition() &&
            currentMove.direction == mLastDirection)
         {
            if (currentMove.direction == logic::CharacterDirection::Left)
            {
               mLastDirection = logic::CharacterDirection::Right;
            }
            else
            {
               mLastDirection = logic::CharacterDirection::Left;
            }
         }
         mLastPosition = getCharacter()->getPosition();  
      }
   }
}