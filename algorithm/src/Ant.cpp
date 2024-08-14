#include "../inc/Ant.hpp"

#include "../../core/inc/Random.hpp"

namespace jp::algorithm
{
   Ant::Ant(std::map<math::Vector2<float>, std::vector<Pheromone>>& pheromones, const std::shared_ptr<logic::Character>& character)
      : mPheromones(pheromones), Bot(character, { Move(MoveType::Run, logic::CharacterDirection::Right, 2.f) }) {}

   void Ant::update(float dt)
   {
      Bot::update(dt);
      Move currentMove = getCurrentMove();
      if (currentMove.type == MoveType::Run)
      {
         if (mLastPosition == getCharacter()->getPosition() &&
            mLastChangeDirectionPosition != getCharacter()->getPosition())
         {
            std::cout << "lastpos: " << mLastPosition << " lastchangedirpos: " << mLastChangeDirectionPosition << " pos: " << getCharacter()->getPosition() << std::endl;
            clearMoves();
            mMoves.push_back(Move(MoveType::Run, oppositeDirection(getCharacter()->getDirection()), std::numeric_limits<float>::max()));
            mLastChangeDirectionPosition = getCharacter()->getPosition();
         }

         if (mPheromones.find(getCharacter()->getPosition()) != mPheromones.end())
         {
            for (const auto& pheromone : mPheromones.at(getCharacter()->getPosition()))
            {
               if (core::Random::getFloat(0.f, 1000.f) < pheromone.getIntensity())
               {
                  clearMoves();
                  mMoves.push_back(pheromone.getMove());
                  break;
               }
            }

            if (core::Random::getFloat(0.f, 1000.f) < 100.f)
            {
               clearMoves();
               mMoves.push_back(Move::randomJump(500.f));
            }
            else
            {
               clearMoves();
               mMoves.push_back(Move(MoveType::Run, oppositeDirection(getCharacter()->getDirection()), std::numeric_limits<float>::max()));
            }
         }
         else
         {
            if (core::Random::getFloat(0.f, 1000.f) < 1.f)
            {
               clearMoves();
               mMoves.push_back(Move::randomJump(500.f));
            }
            else
            {
               clearMoves();
               mMoves.push_back(Move(MoveType::Run, oppositeDirection(getCharacter()->getDirection()), std::numeric_limits<float>::max()));
            }
         }
      }
      mLastPosition = getCharacter()->getPosition();
   }
}